
/*
 *  Copyright t lefering
 *  (C) Universitaet Passau 1986-1991
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
#include "pos3.h"
#include "dpmem.h"
#include "dot.tab.h"

/* min. distance between 2 nodes */
static int mindist = 1;

struct node_data {
	struct gml_node *node;
	int priority;
	int done;
};

static struct node_data *nl = NULL;

static int is_dummy(struct gml_node *node)
{
	if (node->dummy) {
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

	/* incoming edges for_targetlist(node,edge) */
	el = node->incoming_e;

	while (el) {
		result++;
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

	/* outgoing edges for_sourcelist(node,edge) */
	el = node->outgoing_e;

	while (el) {
		result++;
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

	/* incoming edges x sum for_targetlist(node,edge) */
	el = node->incoming_e;

	while (el) {
		result += (el->edge->from_node->absx);	/*old relx); */
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		r = (result / upper_connectivity(node));
	}

	if (0) {
		r = round(r);
	}

	return ((int)r);
}

/* avg x pos of outgoing edges */
static int lower_barycenter(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result = 0;
	double r = 0.0;

	/* get avg. x pos of outgoing edges for_sourcelist(node,edge) */
	el = node->outgoing_e;

	while (el) {
		result += (el->edge->to_node->absx);	/*old  relx); */
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		r = (result / lower_connectivity(node));
	}

	if (0) {
		r = round(r);
	}

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

static void make_node_list_up(struct gml_graph *g, int l)
{
	struct gml_nlist *gnl = NULL;
	struct gml_node *n = NULL;
	int i = 0;

	/* for_all_nodes(g,n) */
	gnl = g->nodelist;

	while (gnl) {
		n = gnl->node;

		if (n->absy == l) {
			nl[i].node = n;
			nl[i].done = 0;	/* FALSE */
			if (is_dummy(n)) {
				/* higer value then the highest node in this level */
				/*old nl[i].priority = (g->nnodes_of_level[l + 1] + 1000 */
				nl[i].priority = (100000 - n->relx);
			} else {
				nl[i].priority = lower_connectivity(n);
			}
			i++;
		}
		gnl = gnl->next;
	}

	sort(g->nnodes_of_level[l]);

	return;
}

static void make_node_list_down(struct gml_graph *g, int l)
{
	struct gml_nlist *gnl = NULL;
	struct gml_node *n = NULL;
	int i = 0;

	/* for_all_nodes(g,n) */
	gnl = g->nodelist;

	while (gnl) {
		n = gnl->node;
		if (n->absy == l) {
			nl[i].node = n;
			nl[i].done = 0;	/* FALSE */
			if (is_dummy(n)) {
				/* give dummy node uniq high number */
				/*old  nl[i].priority = (g->nnodes_of_level[l - 1] + 1000 */
				nl[i].priority = (100000 - n->relx);
			} else {
				nl[i].priority = upper_connectivity(n);
			}
			i++;
		}
		gnl = gnl->next;
	}

	sort(g->nnodes_of_level[l]);

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

static void do_down(struct gml_graph *g, int l)
{
	int i = 0;
	int index = 0;
	int j = 0;
	int optimal_position = 0;
	int distance = 0;
	int possible_distance = 0;

	for (i = 0; i < g->nnodes_of_level[l]; i++) {
		index = find_next(g->nnodes_of_level[l]);

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
				if (j < g->nnodes_of_level[l] - 1) {
					possible_distance += nl[j + 1].node->absx - nl[j].node->absx - mindist;
				} else {
					/* j == g->nnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < g->nnodes_of_level[l]) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == g->nnodes_of_level[l] - 1) {
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

static void do_up(struct gml_graph *g, int l)
{
	int i = 0;
	int index = 0;
	int j = 0;
	int optimal_position = 0;
	int distance = 0;
	int possible_distance = 0;

	for (i = 0; i < g->nnodes_of_level[l]; i++) {
		index = find_next(g->nnodes_of_level[l]);

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
				if (j < g->nnodes_of_level[l] - 1) {
					possible_distance += nl[j + 1].node->absx - nl[j].node->absx - mindist;
				} else {
					/* j == g->nnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < g->nnodes_of_level[l]) && !(nl[j].done));

			if (possible_distance < distance) {
				distance = possible_distance;
			}

			j = index;
			while (distance > 0) {
				int d = 0;
				int k = 0;

				if (j == g->nnodes_of_level[l] - 1) {
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
static void improve_positions1(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;
	int i = 0;
	int count = 0;
	int ii = 0;
	int mx = 0;
	int sl = 0;

	/* this can happen */
	if (g->nnodes_of_level == NULL) {
		return;
	}

	if (g->nsinglenodes) {
		/* single nodes in level 0 and skip this level */
		sl = 1;
	} else {
		/* start level is 0 */
		sl = 0;
	}

	/* copy the rel(x,y) pos into abs(x,y) and modify the absx pos here */
	gnl = g->nodelist;

	while (gnl) {
		gnl->node->absx = gnl->node->relx;
		gnl->node->absy = gnl->node->rely;
		gnl->node->finx = 0;
		gnl->node->finy = 0;
		gnl = gnl->next;
	}

	/* XXX tofix todo these params */

	/* min. node dist, minimum 1 */
	mindist = 1;

	/* number of up/down sweeps */
	count = 1;

	for (ii = 0; ii < count; ii++) {

		/* DOWN */
		for (i = sl; i <= g->maxlevel; i++) {
			if (g->nnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(g->nnodes_of_level[i], sizeof(struct node_data));
				make_node_list_down(g, i);
				do_down(g, i);
				dp_free(nl);
				nl = NULL;
			}
		}

		/* UP */
		for (i = (g->maxlevel - 1); i >= sl; i--) {
			if (g->nnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(g->nnodes_of_level[i], sizeof(struct node_data));
				make_node_list_up(g, i);
				do_up(g, i);
				dp_free(nl);
				nl = NULL;
			}
		}

	}

	/* top+bottom update */
	if ((sl + 2) < g->maxlevel) {

		for (i = sl + 2; i >= sl; i--) {
			if (g->nnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(g->nnodes_of_level[i], sizeof(struct node_data));
				make_node_list_up(g, i);
				do_up(g, i);
				dp_free(nl);
				nl = NULL;
			}
		}
	}

	for (i = g->maxlevel - 2; i <= g->maxlevel; i++) {
		if (i >= 0) {
			if (g->nnodes_of_level[i]) {
				nl = (struct node_data *)dp_calloc(g->nnodes_of_level[i], sizeof(struct node_data));
				make_node_list_down(g, i);
				do_down(g, i);
				dp_free(nl);
				nl = NULL;
			}
		}
	}

	/* left-align the image */

	/* find min. x pos in-use */
	mx = 1024 * 1024;	/* just some high value */

	if (g->nsinglenodes) {
		/* single nodes in level 0 and skip this level */

		gnl = g->nodelist;

		while (gnl) {
			/* only level 1...n */
			if (gnl->node->rely) {
				if (gnl->node->absx < mx) {
					mx = gnl->node->absx;
				}
			}
			gnl = gnl->next;
		}

		/* move whole drawing to the left */
		gnl = g->nodelist;

		while (gnl) {
			/* only level 1...n */
			if (gnl->node->rely) {
				gnl->node->absx = (gnl->node->absx - mx);
			}
			gnl = gnl->next;
		}

	} else {
		/* no single nodes and level 0 is in use for the drawing */

		gnl = g->nodelist;

		while (gnl) {
			if (gnl->node->absx < mx) {
				mx = gnl->node->absx;
			}
			gnl = gnl->next;
		}

		/* move whole drawing to the left */
		gnl = g->nodelist;

		while (gnl) {
			gnl->node->absx = (gnl->node->absx - mx);
			gnl = gnl->next;
		}

	}

	return;
}

/* switch between different modes
 * pos.c and pos2.c set in absx,absy relative coords
 * which are turned into real coords in finalxy()
 * pos3 set in absx,absy real coords and finalxy3()
 * copies that to finx,finy
 */
void improve_positions(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;

	printf("%s(): positioning mode is %d\n", __func__, postype);
	fflush(stdout);

	switch (postype) {
	case 1:
		improve_positions1(g);
		break;
	case 2:
		improve_positions2(g);
		break;
	case 3:
		improve_positions3(g);
		break;
	default:
		/* shouldnothappen */
		improve_positions1(g);
		break;
	}

	if (yydebug || 0) {
		gnl = g->nodelist;

		while (gnl) {
			printf("%s(): node \"%s\" at level %d is at abs(%d,%d) fin(%d,%d) ly0=%d ly1=%d\n", __func__,
			       gnl->node->name, gnl->node->rely, gnl->node->absx, gnl->node->absy, gnl->node->finx, gnl->node->finy,
			       gnl->node->ly0, gnl->node->ly1);
			gnl = gnl->next;
		}

	}

	return;
}

/* end */
