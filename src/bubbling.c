
/*
 *  Copyright t lefering
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  These are the four essential freedoms with GNU GPL software:
 *  1: freedom to run the program, for any purpose
 *  2: freedom to study how the program works, and change it to make it do what you wish
 *  3: freedom to redistribute copies to help your Free Software friends
 *  4: freedom to distribute copies of your modified versions to your Free Software friends
 *   ,           ,
 *  /             \
 * ((__-^^-,-^^-__))
 * `-_---'  `---_-'
 *  `--|o`   'o|--'
 *      \  `  /
 *       ): :(
 *       :o_o:
 *        "-"
 *
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "sugi.h"
#include "bubbling.h"
#include "pos.h"
#include "hier.h"
#include "uniqnode.h"
#include "dpmem.h"

/* bubbling has a mem leak and splay tree used to track and free all mem. */

static splay_tree bubbling_splaytree = NULL;

static void bubbling_free(void *ptr)
{
	if (ptr) {
		splay_tree_remove(bubbling_splaytree, (splay_tree_value) ptr);
	}
	return;
}

static void *bubbling_calloc(int nn, size_t sz)
{
	void *ret;
	ret = dp_calloc(nn, sz);
	if (bubbling_splaytree == NULL) {
		bubbling_splaytree = splay_tree_new(splay_tree_compare_pointers, splay_tree_free_key, NULL);
	}
	splay_tree_insert(bubbling_splaytree, (splay_tree_value) ret, 0);
	return (ret);
}

struct node_bubble {
	struct gml_node *node;
	struct node_bubble *next;
};

struct node_bubble *first_elem = NULL;

/* init top level nodes */
static int input_bubbling(struct gml_graph *g)
{
	struct gml_nlist *nl;
	struct gml_node *node;
	int bubble = 1000000;
	int i = 0;

	/* for_all_nodes (g, node) */
	nl = g->nodelist;

	while (nl) {
		node = nl->node;

		/* select nodes at top of drawing */
		if (node->y == 0) {
			node->x = bubble;
			bubble = bubble + 1000000;
			i++;
		}
		nl = nl->next;
	}

	return (i);
}

static void insert_node_bubble(struct gml_node *node)
{
	struct node_bubble *new_n;
/* #warning "memleak" here */
	new_n = (struct node_bubble *)bubbling_calloc(1, sizeof(struct node_bubble));

	new_n->node = node;
	new_n->next = first_elem;

	first_elem = new_n;

	return;
}

static struct node_bubble *first_bubbling(struct gml_graph *g, int act_level)
{
	struct gml_node *node;
	struct gml_node *source;
	struct gml_edge *edge;
	struct gml_elist *el;
	struct gml_nlist *nl;
	int bubble = 0;
	int count = 0;

	first_elem = NULL;

	/*  for_all_nodes (g, node) */
	nl = g->nodelist;

	while (nl) {
		node = nl->node;

		bubble = 0;
		count = 0;

		if (node->y == act_level) {

			/* for_targetlist (node, edge) */
			el = node->incoming_e;

			while (el) {
				edge = el->edge;

				source = edge->from_node;

				if (source->y == (act_level - 1)) {
					bubble = bubble + source->x;
					count++;
				}

				el = el->next;
			}

			if (count > 0) {
				node->x = bubble / count;
			} else {
				node->x = 1000000;
			}

			insert_node_bubble(node);

		}

		nl = nl->next;
	}

	return (first_elem);
}

static void third_bubbling(struct gml_graph *g, int act_level)
{
	struct gml_node *node;
	struct gml_node *source;
	struct gml_node *target;
	struct gml_edge *edge;
	struct gml_elist *el;
	struct gml_nlist *nl;
	int bubble = 0;
	int count = 0;

	/* for_all_nodes (g, node) */
	nl = g->nodelist;

	while (nl) {
		node = nl->node;

		bubble = 0;
		count = 0;

		if (node->y == act_level) {

			/* incoming edges for node */
			/* for_targetlist (node, edge) */
			el = node->incoming_e;

			while (el) {
				edge = el->edge;

				/* take source node of incoming edge */
				source = edge->from_node;

				if (source->y == (act_level - 1)) {
					bubble = bubble + source->x;
					count++;
				}
				el = el->next;
			}

			/* outgoing edges for node */
			/* for_sourcelist (node, edge) */
			el = node->outgoing_e;

			while (el) {
				edge = el->edge;

				/* take target node of outgoing edge */
				target = edge->to_node;

				if (target->y == (act_level + 1)) {
					bubble = bubble + target->x;
					count++;
				}
				el = el->next;
			}

			if (count > 0) {
				/* node with edges */
				node->x = bubble / count;
			} else {
				/* standalone node */
				node->x = 1000000;
			}

		}

		nl = nl->next;
	}

	return;
}

/* how many bubble nodes in list */
static int count_bnodes(struct node_bubble *thelist)
{
	struct node_bubble *ptr = NULL;
	int nr = 0;
	if (thelist == NULL) {
		return (0);
	}
	ptr = thelist;

	while (ptr) {
		nr++;
		ptr = ptr->next;
	}

	return (nr);
}

static void sort_levellist(struct node_bubble * *blist)
{
	struct node_bubble *bnode;
	struct node_bubble *help_bnode;
	struct gml_node *save_node;
	int nr = 0;
	int count = 0;

	/* how many bubble nodes in list */
	count = count_bnodes(*blist);

	while (count - 1 >= 1) {
		bnode = *blist;
		help_bnode = bnode->next;

		nr = count - 1;

		while (nr >= 1) {
			if (bnode->node->x >= help_bnode->node->x) {
				save_node = bnode->node;
				bnode->node = help_bnode->node;
				help_bnode->node = save_node;
			}

			if (nr > 1) {
				bnode = help_bnode;
				help_bnode = help_bnode->next;
			}

			nr--;
		}

		count--;
	}

	return;
}

static void new_bubbles(struct node_bubble *bnodes)
{
	int new_bub = 1;
	struct node_bubble *kill;

	while (bnodes != NULL) {
		bnodes->node->x = new_bub;
		new_bub++;
		kill = bnodes;
		bnodes = bnodes->next;
		bubbling_free(kill);
	}

	return;
}

static void new_bubble2(struct node_bubble *bnodes)
{
	int new_bub = 1000000;
	struct node_bubble *ptr;
	struct node_bubble *ptrnext;
	ptr = bnodes;
	while (ptr) {
		ptr->node->x = new_bub;
		new_bub = new_bub + 1000000;
		ptrnext = ptr->next;
		/* mem error here free (ptr); */
		ptr = ptrnext;
	}

	return;
}

/* */
void give_horizontal_place(struct gml_graph *g, int choose)
{
	int levelnr = 0;
	struct gml_node *node;
	struct gml_nlist *nl;

	/* scan all levels */
	while (levelnr <= (g->maxlevel - 1)) {

		first_elem = NULL;

		/* for_all_nodes (g, node) */
		nl = g->nodelist;

		while (nl) {
			node = nl->node;
			if (node->y == levelnr) {
				insert_node_bubble(node);
			}
			nl = nl->next;
		}

		sort_levellist(&first_elem);

		/* update node x pos */
		if (choose == 1) {
			/* increment by 1 with choose==1 */
			new_bubbles(first_elem);
		} else {
			/* by 100000 with choose==2 */
			new_bubble2(first_elem);
		}

		levelnr++;
	}

	return;
}

void graph_bubbling(struct gml_graph *g)
{
	int act_level = 0;
	int loops = 4;		/* how many times 3rd bubbling */
	int help;
	int remember = 0;
	int i;
	struct node_bubble *blist;

	/* init top level nodes */
	i = input_bubbling(g);

	/* if only 1 toplevel node */
	if (i == 1) {
		remember = 1;
	}

	act_level = 1;

	/* scan all levels */
	while ((g->maxlevel - 1) >= act_level) {

		blist = first_bubbling(g, act_level);

		if (remember == 1) {
			new_bubble2(blist);
		}

		/* how many bubble nodes in list */
		if (count_bnodes(blist) == 1) {
			remember = 1;
		} else {
			remember = 0;
		}

		act_level++;
	}

	/*
	 *
	 */
	if (1) {

		act_level = 1;

		help = 1;

		while (help <= loops) {
			while ((g->maxlevel - 1) >= act_level) {
				third_bubbling(g, act_level);
				act_level++;
			}

			if ((help / 3) * 3 == help) {
				give_horizontal_place(g, 2);
			}

			help++;
			act_level = 1;
		}

	}

	/*
	 *
	 */
	if (1) {

		act_level = 1;

		while ((g->maxlevel - 1) >= act_level) {
			third_bubbling(g, act_level);
			act_level = act_level + 2;
		}

		act_level = 2;

		while ((g->maxlevel - 1) >= act_level) {
			third_bubbling(g, act_level);
			act_level = act_level + 2;
		}
	}

	/* make sure all extra memory is free'ed */
	bubbling_splaytree = splay_tree_delete(bubbling_splaytree);

	return;
}

void clear_bubbling(struct gml_graph *g)
{
	if (g) {
	}
	first_elem = NULL;
	/* make sure all extra memory is free'ed */

	if (bubbling_splaytree) {
		bubbling_splaytree = splay_tree_delete(bubbling_splaytree);
	}

	return;
}

/* end */
