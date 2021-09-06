
/*
 *  Copyright 2021
 *  (C) Universitaet Passau 1986-1991
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
#include <math.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "pos.h"
#include "pos2.h"
#include "dot.tab.h"
#include "dpmem.h"

/* min. distance between 2 nodes */
static int mindist = 1;

/* current startnode nr field */
static int csn = 0;

/* node list of part of graph */
static struct gml_nlist *cnodelist = NULL;
static struct gml_nlist *cnodelisttail = NULL;

/* number of nodes at level */
static int *cnnodes_of_level = NULL;

/* max. x,y in part of graph */
static int cmaxx = 0;
static int cmaxy = 0;

/* widest x level */
static int cwidestnnodes = 0;

/* x width at position */
static int *cwpos = NULL;

/* lists per pos. */
static struct gml_nlist **cposnodes = NULL;

/* hor pos */
static int *chpos = NULL;

/* hor pos */
static struct gml_nlist **clevelnodes = NULL;

/* */
struct node_data {
	struct gml_node *node;
	int priority;
	int done;
};

/* nodes in one level */
static struct node_data *nl = NULL;

static int is_dummy(struct gml_node *node)
{
	if (node->dummy) {
		return (1);
	} else {
		return (0);
	}
}

static int is_elabel(struct gml_node *node)
{
	if (node->elabel) {
		return (1);
	} else {
		return (0);
	}
}

/* how many connection edges from previous level */
static int upper_connectivity(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result;

	result = 0;

	if (node == NULL) {
		/* shouldnothappen */
		return (0);
	}

	/* incoming edges for_targetlist(node,edge) */
	el = node->incoming_e;

	while (el) {
		/* skip hor. edges */
		if (el->edge->hedge == 0) {
			/* only in this part of graph */
			if (el->edge->from_node->startnode == csn) {
				result++;
			}
		}
		el = el->next;
	}

	return (result);
}

/* how many connection edges to next level */
static int lower_connectivity(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result = 0;

	result = 0;

	if (node == NULL) {
		/* shouldnothappen */
		return (0);
	}

	/* outgoing edges for_sourcelist(node,edge) */
	el = node->outgoing_e;

	while (el) {
		/* skip hor. edges */
		if (el->edge->hedge == 0) {
			/* only in this part of graph */
			if (el->edge->to_node->startnode == csn) {
				result++;
			}
		}
		el = el->next;
	}

	return (result);
}

/* avg x pos of incoming edges */
static int upper_barycenter(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result = 0;
	double r = 0.0;

	if (node == NULL) {
		/* shouldnothappen */
		return (0);
	}

	/* incoming edges x sum for_targetlist(node,edge) */
	el = node->incoming_e;

	while (el) {
		/* skip hor. edges */
		if (el->edge->hedge == 0) {
			/* only in this part of graph */
			if (el->edge->from_node->startnode == csn) {
				result += (el->edge->from_node->absx);
			}
		}
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		if (upper_connectivity(node) == 0) {
			r = 0.0;
		} else {
			r = (result / upper_connectivity(node));
		}
	}

	r = round(r);

	return ((int)r);
}

/* avg x pos of outgoing edges */
static int lower_barycenter(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result = 0;
	double r = 0.0;

	if (node == NULL) {
		/* shouldnothappen */
		return (0);
	}

	/* get avg. x pos of outgoing edges for_sourcelist(node,edge) */
	el = node->outgoing_e;

	while (el) {
		/* skip hor. edges */
		if (el->edge->hedge == 0) {
			/* only in this part of graph */
			if (el->edge->to_node->startnode == csn) {
				result += (el->edge->to_node->absx);
			}
		}
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		if (lower_connectivity(node) == 0) {
			r = 0.0;
		} else {
			r = (result / lower_connectivity(node));
		}
	}

	r = round(r);

	return ((int)r);
}

static void sort(int n)
{
	int i = 0;
	int j = 0;
	struct node_data h;

	for (j = n - 1; j > 0; j--) {
		for (i = 0; i < j; i++) {
			/* issue here */
			if (nl[i].node && nl[i + 1].node) {
				if (nl[i].node->relx > nl[i + 1].node->relx) {
					/* swap */
					h = nl[i];
					nl[i] = nl[i + 1];
					nl[i + 1] = h;
				}
			}
		}
	}

	return;
}

/* */
static void make_node_list_up(int l)
{
	struct gml_nlist *gnl = NULL;
	struct gml_node *n = NULL;
	int i = 0;

	/* for_all_nodes(g,n) */
	gnl = cnodelist;
	i = 0;

	while (gnl) {
		n = gnl->node;

		if (n->absy == l) {
			nl[i].node = n;
			nl[i].done = 0;	/* FALSE */
			/* give edge label nodes hight prio too */
			if ((is_dummy(n) == 1) || (is_elabel(n) == 1)) {	/* */
				/* higer value then the highest node in this level */
				/*old nl[i].priority = (cnnodes_of_level[l + 1] + 1000 */
				nl[i].priority = (100000 - n->relx);
			} else {
				nl[i].priority = lower_connectivity(n);
			}
			i++;
		}
		gnl = gnl->next;
	}

	sort(cnnodes_of_level[l]);

	return;
}

/* */
static void make_node_list_down(int l)
{
	struct gml_nlist *gnl = NULL;
	struct gml_node *n = NULL;
	int i = 0;

	/* for_all_nodes(g,n) */
	gnl = cnodelist;

	while (gnl) {
		n = gnl->node;
		if (n->absy == l) {
			nl[i].node = n;
			nl[i].done = 0;	/* FALSE */
			/* give edge labels lso high prio */
			if ((is_dummy(n) == 1) || (is_elabel(n) == 1)) {	/* */
				/* give dummy node uniq high number */
				/*old  nl[i].priority = (cnnodes_of_level[l - 1] + 1000 */
				nl[i].priority = (100000 - n->relx);
			} else {
				nl[i].priority = upper_connectivity(n);
			}
			i++;
		}
		gnl = gnl->next;
	}

	sort(cnnodes_of_level[l]);

	return;
}

/* get number of node with highest prio which is not done yet */
static int find_next(int n)
{
	int index = 0;
	int i = 0;
	int highest_priority = 0;

	for (i = 0; i < n; i++) {
		if ((nl[i].priority >= highest_priority)
		    && (nl[i].done == 0 /* FALSE */ )) {
			index = i;
			highest_priority = nl[i].priority;
		}
	}

	return (index);
}

static void do_down(int l)
{
	int i = 0;
	int index = 0;
	int j = 0;
	int optimal_position = 0;
	int distance = 0;
	int possible_distance = 0;

	for (i = 0; i < cnnodes_of_level[l]; i++) {
		index = find_next(cnnodes_of_level[l]);

		optimal_position = upper_barycenter(nl[index].node);

		if (optimal_position == 0) {
			optimal_position = nl[index].node->absx;
		}

		if (optimal_position < nl[index].node->absx) {
			distance = nl[index].node->absx - optimal_position;

			possible_distance = 0;
			j = index;

			do {
				if (j > 0) {
					possible_distance += nl[j].node->absx - nl[j - 1].node->absx - mindist;
				} else {
					/* j==0, no nodes at left */
					possible_distance += nl[j].node->absx - mindist;
				}
				j--;
			}
			while ((j >= 0) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == 0) {
					d = distance;
				} else {
					if (nl[j].node->absx - nl[j - 1].node->absx - mindist < distance) {
						d = nl[j].node->absx - nl[j - 1].node->absx - mindist;
					} else {
						d = distance;
					}
				}

				for (k = j; k <= index; k++) {
					nl[k].node->absx -= d;
				}

				j--;
				distance -= d;
			}
		} else {
			distance = optimal_position - nl[index].node->absx;

			possible_distance = 0;
			j = index;

			do {
				if (j < cnnodes_of_level[l] - 1) {
					possible_distance += nl[j + 1].node->absx - nl[j].node->absx - mindist;
				} else {
					/* j == cnnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < cnnodes_of_level[l]) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == cnnodes_of_level[l] - 1) {
					d = distance;
				} else {
					if (nl[j + 1].node->absx - nl[j].node->absx - mindist < distance) {
						d = nl[j + 1].node->absx - nl[j].node->absx - mindist;
					} else {
						d = distance;
					}
				}

				for (k = index; k <= j; k++) {
					nl[k].node->absx += d;
				}

				j++;
				distance -= d;
			}
		}
		nl[index].done = 1;	/* TRUE */
	}

	return;
}

static void do_up(int l)
{
	int i = 0;
	int index = 0;
	int j = 0;
	int optimal_position = 0;
	int distance = 0;
	int possible_distance = 0;

	for (i = 0; i < cnnodes_of_level[l]; i++) {
		index = find_next(cnnodes_of_level[l]);

		optimal_position = lower_barycenter(nl[index].node);

		if (optimal_position == 0) {
			optimal_position = nl[index].node->absx;
		}

		if (optimal_position < nl[index].node->absx) {
			distance = nl[index].node->absx - optimal_position;

			possible_distance = 0;
			j = index;
			do {
				if (j > 0) {
					possible_distance += nl[j].node->absx - nl[j - 1].node->absx - mindist;
				} else {
					/* j == 0, no nodes links */
					possible_distance += nl[0].node->absx - mindist;
				}
				j--;
			}
			while ((j >= 0) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == 0) {
					d = distance;
				} else {
					if (nl[j].node->absx - nl[j - 1].node->absx - mindist < distance) {
						d = nl[j].node->absx - nl[j - 1].node->absx - mindist;
					} else {
						d = distance;
					}
				}

				for (k = j; k <= index; k++) {
					nl[k].node->absx -= d;
				}

				j--;
				distance -= d;
			}
		} else {
			/* optimal_position >= nl[index].node->absx */
			distance = optimal_position - nl[index].node->absx;

			possible_distance = 0;
			j = index;
			do {
				if (j < cnnodes_of_level[l] - 1) {
					possible_distance += nl[j + 1].node->absx - nl[j].node->absx - mindist;
				} else {
					/* j == cnnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < cnnodes_of_level[l]) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == cnnodes_of_level[l] - 1) {
					d = distance;
				} else {
					if (nl[j + 1].node->absx - nl[j].node->absx - mindist < distance) {
						d = nl[j + 1].node->absx - nl[j].node->absx - mindist;
					} else {
						d = distance;
					}
				}

				for (k = index; k <= j; k++) {
					nl[k].node->absx += d;
				}

				j++;
				distance -= d;
			}
		}
		nl[index].done = 1;	/* TRUE */
	}

	return;
}

/* determine relative node pos. from the barycenter rel. node pos. */
static void improve_positions2local(struct gml_graph *g)
{
	int i = 0;
	int count = 0;
	int ii = 0;
	int sl = 0;

	/* start level is 0 */
	sl = 0;

	/* min. node dist */
	mindist = 1;

	/* number of up/down sweeps */
	count = 1;

	for (ii = 0; ii < count; ii++) {

		/* DOWN */
		for (i = sl; i < g->maxlevel; i++) {
			if (cnnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(1, cnnodes_of_level[i] * sizeof(struct node_data));
				make_node_list_down(i);
				do_down(i);
				nl = dp_free(nl);
				if (nl) {
				}
			}
		}

		/* UP */
		for (i = (g->maxlevel - 1); i >= sl; i--) {
			if (cnnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(1, cnnodes_of_level[i] * sizeof(struct node_data));
				make_node_list_up(i);
				do_up(i);
				nl = dp_free(nl);
				if (nl) {
				}
			}
		}

	}

	/* top+bottom update */
	if ((sl + 2) < g->maxlevel) {

		for (i = sl + 2; i >= sl; i--) {
			if (cnnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(1, cnnodes_of_level[i] * sizeof(struct node_data));
				make_node_list_up(i);
				do_up(i);
				nl = dp_free(nl);
				if (nl) {
				}
			}
		}
	}

	for (i = (g->maxlevel - 2); i <= g->maxlevel; i++) {
		if (i >= 0) {
			if (cnnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(1, cnnodes_of_level[i] * sizeof(struct node_data));
				make_node_list_down(i);
				do_down(i);
				nl = dp_free(nl);
				if (nl) {
				}
			}
		}
	}

	return;
}

/* create nodes-at-level-count */
static void make_cnnodes_at_level(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;

	cnnodes_of_level = (int *)dp_calloc(1, ((g->maxlevel + 1) * sizeof(int)));

	gnl = cnodelist;

	while (gnl) {
		cnnodes_of_level[gnl->node->rely] = cnnodes_of_level[gnl->node->rely] + 1;
		gnl = gnl->next;
	}

	return;
}

 /* clear nodes-at-level-count */
static void clear_cnnodes_at_level(void)
{

	/* number of nodes at level */
	if (cnnodes_of_level) {
		cnnodes_of_level = dp_free(cnnodes_of_level);
		if (cnnodes_of_level) {
		}
	}

	return;
}

 /* copy part of graph */
static void make_cnodelist(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;
	struct gml_nlist *newnl = NULL;

	gnl = g->nodelist;

	while (gnl) {

		/* check if node belongs to part of graph */
		if (gnl->node->startnode == csn) {
			/* copy node in new list */
			newnl = (struct gml_nlist *)dp_calloc(1, sizeof(struct gml_nlist));
			newnl->node = gnl->node;
			if (cnodelist == NULL) {
				cnodelist = newnl;
				cnodelisttail = newnl;
			} else {
				cnodelisttail->next = newnl;
				cnodelisttail = newnl;
			}
		}
		gnl = gnl->next;
	}

	if (yydebug || 0) {
		printf("%s(): nodes in graph part with startnode %d are:\n", __func__, csn);
		gnl = cnodelist;
		while (gnl) {
			printf("%s(): node %d level=%d startnode %d\n", __func__, gnl->node->nr, gnl->node->rely, csn);
			gnl = gnl->next;
		}
	}

	return;
}

/* done with this part of graph */
static void clear_cnodelist(void)
{
	struct gml_nlist *gnl = NULL;
	struct gml_nlist *gnlnext = NULL;

	gnl = cnodelist;

	while (gnl) {
		gnlnext = gnl->next;
		gnl = dp_free(gnl);
		if (gnl) {
		}
		gnl = gnlnext;
	}

	/* node list of part of graph */
	cnodelist = NULL;
	cnodelisttail = NULL;

	return;
}

/* move image of this part of graph */
static void move0(void)
{
	struct gml_nlist *gnl = NULL;
	int mx = 0;

	/* find min. x pos in-use */
	mx = 1000 * 1000;	/* just some high value */

	gnl = cnodelist;

	while (gnl) {
		if (gnl->node->absx < mx) {
			mx = gnl->node->absx;
		}
		gnl = gnl->next;
	}

	/* move whole drawing to the left */
	gnl = cnodelist;

	while (gnl) {
		gnl->node->absx = (gnl->node->absx - mx);
		gnl = gnl->next;
	}

	return;
}

/* */
static void make_cposnodes(void)
{
	struct gml_nlist *lnl = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;
	int lmaxw = 0;
	int maxrx = 0;

	/* widest x level */
	cwidestnnodes = 0;

	/* x width at position */
	cwpos = NULL;

	/* lists per pos. */
	cposnodes = NULL;

	/* extra check max rel. x pos. */
	lnl = cnodelist;

	while (lnl) {
		if (lnl->node->absx > maxrx) {
			maxrx = lnl->node->absx;
		}
		lnl = lnl->next;
	}

	/* pos2.c has moved node in x dir. */
	cwidestnnodes = maxrx;

	/* x width at position */
	cwpos = (int *)dp_calloc(1, (cwidestnnodes + 1) * sizeof(int));

	/* lists with nodes up to down at position */
	cposnodes = (struct gml_nlist **)dp_calloc(1, (cwidestnnodes + 1) * sizeof(struct gml_nlist *));

	/* create for every postion the list of nodes at that position */
	lnl = cnodelist;

	while (lnl) {
		i = lnl->node->absx;

		if (yydebug || 0) {
			printf("%s(): node \"%s\" at absx %d\n", __func__, lnl->node->nlabel, lnl->node->absx);
		}

		newl = (struct gml_nlist *)dp_calloc(1, sizeof(struct gml_nlist));

		newl->node = lnl->node;

		if (cposnodes[i] == NULL) {
			cposnodes[i] = newl;
			newl->next = NULL;
		} else {
			newl->next = cposnodes[i];
			cposnodes[i] = newl;
		}

		lnl = lnl->next;
	}

	/* determine the max width of a element at vertical pos. */
	for (i = 0; i < (cwidestnnodes + 1); i++) {
		lmaxw = 0;

		/* lists per pos. */
		lnl = cposnodes[i];

		while (lnl) {
			if (lnl->node->bbx > lmaxw) {
				lmaxw = lnl->node->bbx;
			}
			lnl = lnl->next;
		}

		cwpos[i] = lmaxw;
	}

	return;
}

/* */
static void clear_cposnodes(void)
{
	int i = 0;
	struct gml_nlist *lnl = NULL;
	struct gml_nlist *nlnext = NULL;

	/* width of positions */
	if (cwpos) {
		cwpos = dp_free(cwpos);
		if (cwpos) {
		}
	}

	for (i = 0; i < (cwidestnnodes + 1); i++) {
		/* lists per pos. */
		lnl = cposnodes[i];

		while (lnl) {
			nlnext = lnl->next;
			lnl = dp_free(lnl);
			if (lnl) {
			}
			lnl = nlnext;
		}

		cposnodes[i] = NULL;
	}

	cposnodes = dp_free(cposnodes);
	if (cposnodes) {
	}

	return;
}

/* y positioning */
static void make_clevelnodes(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;
	int lmaxh = 0;

	chpos = (int *)dp_calloc(1, ((g->maxlevel + 1) * sizeof(int)));

	clevelnodes = (struct gml_nlist **)dp_calloc(1, ((g->maxlevel + 1) * sizeof(struct gml_nlist *)));

	lnl = cnodelist;

	while (lnl) {
		i = lnl->node->absy;

		if (yydebug || 0) {
			printf("%s(): at \"%s\" absx %d absy %d\n", __func__, lnl->node->nlabel, lnl->node->absx, lnl->node->absy);
		}

		newl = dp_calloc(1, sizeof(struct gml_nlist));

		newl->node = lnl->node;

		if (clevelnodes[i] == NULL) {
			clevelnodes[i] = newl;
			newl->next = NULL;
		} else {
			newl->next = clevelnodes[i];
			clevelnodes[i] = newl;
		}

		lnl = lnl->next;
	}

	/* determine the max width of a element at vertical pos. */
	for (i = 0; i < (g->maxlevel + 1); i++) {

		lmaxh = 0;

		/* lists per pos. */
		lnl = clevelnodes[i];

		while (lnl) {
			if (yydebug || 0) {
				printf("%s(): scan \"%s\"\n", __func__, lnl->node->nlabel);
			}
			if (lnl->node->bby > lmaxh) {
				lmaxh = lnl->node->bby;
			}
			lnl = lnl->next;
		}

		chpos[i] = lmaxh;
	}

	return;
}

static void clear_clevelnodes(struct gml_graph *g)
{
	int i = 0;
	struct gml_nlist *lnl = NULL;
	struct gml_nlist *lnl2 = NULL;
	struct gml_nlist *nlnext = NULL;

	/* width of positions */
	if (chpos) {
		chpos = dp_free(chpos);
		if (chpos) {
		}
	}

	if (clevelnodes) {

		for (i = 0; i < (g->maxlevel + 1); i++) {
			/* lists per pos. */
			lnl = clevelnodes[i];

			while (lnl) {
				nlnext = lnl->next;
				lnl2 = dp_free(lnl);
				if (lnl2) {
				}
				lnl = nlnext;
			}

			clevelnodes[i] = NULL;	/* */
		}

		clevelnodes = dp_free(clevelnodes);
		if (clevelnodes) {
		}
	}

	return;
}

/* determine final (x,y) pos */
static void cfinalxy(struct gml_graph *g)
{
	struct gml_nlist *lnl = NULL;
	int hw = 0;
	int xoff = 0;
	int yoff = 0;
	int i = 0;
	int ecount = 0;

	/* x positioning */
	make_cposnodes();

	cmaxx = 0;
	xoff = 0;

	/* scan hor. to adjust the x positions. */
	for (i = 0; i < (cwidestnnodes + 1); i++) {
		/* x spacing between the hor. levels */
		xoff = xoff + xspacing;

		/* determine half-way of the xpos. */
		if (cwpos[i] == 0) {
			/* if only dummy nodes */
			hw = xspacing / 2;
		} else {
			hw = (cwpos[i] / 2);
		}

		/* update with current x */
		hw = hw + xoff;

		lnl = cposnodes[i];

		/* scan the nodes at this x pos. */
		while (lnl) {
			/* center the node around the half-way */
			lnl->node->finx = (hw - (lnl->node->bbx / 2));

			if ((lnl->node->finx + lnl->node->bbx) > cmaxx) {
				cmaxx = (lnl->node->finx + lnl->node->bbx);
			}

			lnl = lnl->next;
		}

		/* set x0,x1 pos in the nodes */
		lnl = cposnodes[i];

		/* scan the nodes at this x pos. */
		while (lnl) {
			/* */
			lnl->node->lx0 = xoff;
			lnl->node->lx1 = xoff + cwpos[i];
			lnl = lnl->next;
		}

		/* x spacing between the hor. levels */
		xoff = xoff + xspacing;

		/* x to next pos. */
		xoff = xoff + cwpos[i];
	}

	/* */
	clear_cposnodes();

	/* y positioning */
	make_clevelnodes(g);

	cmaxy = 0;
	yoff = 0;

	/* number of edges between level n and n+1 */
	if (g->nume) {
		g->nume = (int *)dp_free((int *)g->nume);
	}
	g->nume = (int *)dp_calloc(1, (g->maxlevel + 1) * sizeof(int));

	/* scan vert. to adjust the y positions. */
	for (i = 0; i < (g->maxlevel + 1); i++) {

		/* determine half-way of the ypos. */
		if (chpos[i] == 0) {
			/* if only dummy nodes */
			hw = (yspacing / 2);
		} else {
			hw = (chpos[i] / 2);
		}

		/* update half-way with current y */
		hw = hw + yoff;

		if (yydebug || 0) {
			printf("%s(): at level %d y size is %d from %d to %d and half-way is %d\n", __func__, i, chpos[i], yoff,
			       yoff + chpos[i], hw);
		}

		/* nodes at this relative y level */
		lnl = clevelnodes[i];

		ecount = 0;

		/* scan the nodes at this y pos. */
		while (lnl) {

			if (lnl->node->rely != i) {
				printf("%s(): wrong level for node \"%s\" at level %d versus rely=%d\n", __func__, lnl->node->name,
				       i, lnl->node->rely);
			}
			/* set start, end of y level */
			lnl->node->ly0 = yoff;
			lnl->node->ly1 = (yoff + chpos[i]);

			/* center the node around the half-way */
			lnl->node->finy = (hw - (lnl->node->bby / 2));

			if (yydebug || 0) {
				printf("%s(): node \"%s\" at y-pos=%d level %d\n", __func__, lnl->node->name, lnl->node->finy,
				       lnl->node->rely);
			}

			/* update drawing max y pos used */
			if ((lnl->node->finy + lnl->node->bby) > cmaxy) {
				cmaxy = (lnl->node->finy + lnl->node->bby);
			}

			/* give dummy nodes a vertical size of the level */
			if (lnl->node->dummy) {
				lnl->node->bby = chpos[i];
				/* if only dummy nodes at level, use spacing */
				if (chpos[i] == 0) {
					lnl->node->bby = yspacing;
				}
			}

			/* number of edges between level n and n+1 */
			ecount = ecount + lnl->node->outdegree;

			lnl = lnl->next;
		}

		g->nume[i] = ecount;

		/* y spacing between the vert. levels */
		yoff = yoff + yspacing;

		/* yspacing depends on number of edges at this level 
		 * turned off, does increase y too much
		 * yoff = yoff + (ecount * 2);
		 */
		/* yspacing depends on number of crossing edges at this level
		 * temp test
		 */
		yoff = yoff + (1 * (g->numce[i] / 16));

		/* y to next pos. */
		yoff = yoff + chpos[i];
	}

	clear_clevelnodes(g);

	/* clear number of edges between level n and n+1 */
	clear_nume_r(g);

	return;
}

/* move whole part to new x offset position */
static void movefinal(int xoffset)
{
	struct gml_nlist *gnl = NULL;

	gnl = cnodelist;

	while (gnl) {
		gnl->node->finx = gnl->node->finx + xoffset;
		gnl->node->lx0 = gnl->node->lx0 + xoffset;
		gnl->node->lx1 = gnl->node->lx1 + xoffset;
		/* x,y size of raster */
		gnl->node->lxsize = (gnl->node->lx1 - gnl->node->lx0);
		gnl->node->lysize = (gnl->node->ly1 - gnl->node->ly0);

		/* extra check */
		if (gnl->node->lxsize < 0) {
			printf("%s(): lxsize=%d fixme\n", __func__, gnl->node->lxsize);
		}
		if (gnl->node->lysize < 0) {
			printf("%s(): lysize=%d fixme\n", __func__, gnl->node->lysize);
		}
		gnl = gnl->next;
	}

	return;
}

/* dummy nodes can be centered, or left/right most placed */
static void tunedummy(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;

	gnl = g->nodelist;

	while (gnl) {
		if (gnl->node->dummy) {
			x1 = gnl->node->finx;
			if (gnl->node->incoming_e && gnl->node->outgoing_e) {
				x2 = gnl->node->incoming_e->edge->from_node->finx + gnl->node->incoming_e->edge->from_node->bbx / 2;
				x3 = gnl->node->outgoing_e->edge->to_node->finx + gnl->node->outgoing_e->edge->to_node->bbx / 2;
				if ((x1 == x2) && (x1 == x3)) {
					/* no move */
				} else {
					if ((x2 < x1) && (x3 < x1)) {
						/* to left */
						gnl->node->finx = gnl->node->lx0;
					}
					if ((x2 > x1) && (x3 > x1)) {
						/* to right */
						gnl->node->finx = gnl->node->lx1;
					}
				}
			} else {
				/* shouldnothappen */
				printf("%s(): dummy node with in_e %p and out_e %p\n", __func__, (void *)gnl->node->incoming_e,
				       (void *)gnl->node->outgoing_e);
			}
		}
		gnl = gnl->next;
	}

	return;
}

/* move some nodes up/down */
static void tunenodes(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;

	gnl = g->nodelist;

	while (gnl) {
		/* only at real nodes */
		if (gnl->node->dummy == 0) {
			if (gnl->node->hashedge) {
				/* do not move node with hor. edge */
			} else {
				if (gnl->node->indegree > 0 && gnl->node->outdegree == 0) {
					/* move up */
					gnl->node->finy = gnl->node->ly0;
				}
				if (gnl->node->indegree == 0 && gnl->node->outdegree > 0) {
					/* move down */
					gnl->node->finy = (gnl->node->ly1 - gnl->node->bby);
				}
				if (gnl->node->indegree > 0 && gnl->node->outdegree > 0) {
					if (gnl->node->indegree == gnl->node->outdegree) {
						/* no movement
						 *
						 */
					} else {
						if (gnl->node->indegree > gnl->node->outdegree) {
							/* move up */
							gnl->node->finy = gnl->node->ly0;
						}
						if (gnl->node->outdegree > gnl->node->indegree) {
							/* move down */
							gnl->node->finy = (gnl->node->ly1 - gnl->node->bby);
						}
					}
				}
			}
		}
		gnl = gnl->next;
	}

	return;
}

/* position in parts of graph at each step */
void improve_positions2(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;
	int i = 0;
	int xoffset = 0;

	/* copy the rel(x,y) pos into abs(x,y) and modify the absx pos here */
	gnl = g->nodelist;

	while (gnl) {
		gnl->node->absx = gnl->node->relx;
		gnl->node->absy = gnl->node->rely;
		gnl->node->finx = 0;
		gnl->node->finy = 0;
		gnl->node->lx0 = -1;	/* undefined */
		gnl->node->ly0 = -1;
		gnl->node->lx1 = -1;
		gnl->node->ly1 = -1;
		if (gnl->node->startnode < 0) {
			printf("%s(): node %d %s has no startnode\n", __func__, gnl->node->nr, gnl->node->name);
		}
		if (yydebug || 0) {
			printf("%s(): node \"%s\" is at level %d position %d startnode %d\n", __func__, gnl->node->nlabel,
			       gnl->node->rely, gnl->node->relx, gnl->node->startnode);
		}
		gnl = gnl->next;
	}

	/* offset in drawing of part of graph */
	xoffset = 0;

	printf("%s(): %d startnodes\n", __func__, g->nstartnodes);

	for (i = 0; i < g->nstartnodes; i++) {
		/* set current startnode */
		csn = g->startnodes[i];

		if (yydebug || 0) {
			printf("%s(): step %d for startnode=%d\n", __func__, i, csn);
		}

		/* print progress info */
		if ((i == 0) || (i == g->nstartnodes / 2) || (i == g->nstartnodes - 1)) {
			printf("%s(): positioning step %d of %d start nr=%d\n", __func__, i + 1, g->nstartnodes, csn);
			fflush(stdout);
		}

		/* max. x in part of graph */
		cmaxx = 0;

		/* copy part of graph */
		make_cnodelist(g);

		/* create nodes-at-level-count */
		make_cnnodes_at_level(g);

		/* run up/down placement */
		improve_positions2local(g);

		/* move image of this part of graph */
		move0();

		/* set final x,y */
		cfinalxy(g);

		/* tune dummy nodes */
		tunedummy(g);

		/* tune nodes */
		tunenodes(g);

		/* move */
		movefinal(xoffset);

		/* update for next */
		xoffset = xoffset + cmaxx + xspacing;

		/* clear nodes-at-level-count */
		clear_cnnodes_at_level();

		/* done with this part of graph */
		clear_cnodelist();
	}

	/* position level 0, single nodes if any */
	if (g->nsinglenodes) {
		/* done in finalxy() in main.c */
	}

	/* run extra check */
	gnl = g->nodelist;
	while (gnl) {
		/* check undefined */
		if ((gnl->node->lx0 == -1) || (gnl->node->ly0 == -1) || (gnl->node->lx1 == -1) || (gnl->node->ly1 == -1)
		    ) {
			printf("%s(): node level undefined\n", __func__);
		}
		gnl = gnl->next;
	}

	return;
}

/* end */
