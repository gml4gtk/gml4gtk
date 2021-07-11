
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
#include "pos3.h"
#include "dpmem.h"

/* min. distance between 2 nodes */
static int xmindist = 1;
static int ymindist = 1;

/* level step size, 1 or 2 */
static int ssize = 1;

struct node_data {
	struct gml_node *node;
	int priority;
	int done;
};

/* */
static struct node_data *nl = NULL;

/* */
static struct node_data **dl = NULL;

/* index in in dl */
static int *cix = NULL;

/* y size of levels */
static int *szy = NULL;

/* how many connection edges from previous level */
static int upper_connectivity(struct gml_node *node)
{
	return (node->indegree);
}

/* how many connection edges to next level */
static int lower_connectivity(struct gml_node *node)
{
	return (node->outdegree);
}

/* avg x pos of incoming edges */
static int upper_barycenter(struct gml_node *node)
{
	struct gml_elist *el = NULL;
	int result = 0;
	double r = 0.0;
	int abx = 0;

	/* incoming edges x sum for_targetlist(node,edge) */
	el = node->incoming_e;

	while (el) {
		if (ssize == 1) {
			/* todo testing +bbx/2 */
			abx = el->edge->from_node->absx + (el->edge->from_node->bbx / 2);
		} else {
			abx = el->edge->from_node->incoming_e->edge->from_node->absx;
		}
		result = result + abx;
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		r = (result / upper_connectivity(node));
	}

	if (1) {
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
	int abx = 0;

	/* get avg. x pos of outgoing edges for_sourcelist(node,edge) */
	el = node->outgoing_e;

	while (el) {
		if (ssize == 1) {
			/* todo testing +bbx/2 */
			abx = el->edge->to_node->absx + (el->edge->to_node->bbx / 2);
		} else {
			abx = el->edge->to_node->outgoing_e->edge->to_node->absx;
		}
		result = result + abx;
		el = el->next;
	}

	if (result == 0) {
		r = (0.0);
	} else {
		r = (result / lower_connectivity(node));
	}

	if (1) {
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
			} else {
				printf("%s(): nil nodes nl[i].node=%p nl[i + 1].node=%p\n", __func__, (void *)nl[i].node,
				       (void *)nl[i + 1].node);
			}
		}
	}

	return;
}

/* prepare level */
static void make_node_list_up(struct gml_graph *g, int l)
{
	int i = 0;

	nl = dl[l];

	if (nl == NULL) {
		printf("%s(): nil nl at level %d\n", __func__, l);
		return;
	}

	for (i = 0; i < g->nnodes_of_level[l]; i++) {
		nl[i].done = 0;
		if (nl[i].node->dummy) {
			nl[i].priority = 1000 * nl[i].node->relx;	// (100000 + nl[i].node->relx);
//                      nl[i].priority = (1000 * (g->nnodes_of_level[l+2] + 1));
		} else {
			nl[i].priority = lower_connectivity(nl[i].node);
		}
	}
	return;
}

/* prepare level */
static void make_node_list_down(struct gml_graph *g, int l)
{
	int i = 0;

	nl = dl[l];

	if (nl == NULL) {
		printf("%s(): nil nl at level %d\n", __func__, l);
		fflush(stdout);
		return;
	}

	for (i = 0; i < g->nnodes_of_level[l]; i++) {
		nl[i].done = 0;
		if (nl[i].node->dummy) {
			nl[i].priority = 1000 * nl[i].node->relx;	//(100000 + nl[i].node->relx);
		} else {
			nl[i].priority = upper_connectivity(nl[i].node);
		}
	}

	return;
}

/* get number of node with highest prio which is not done yet */
static int find_next(int n)
{
	int nindex = 0;
	int i = 0;
	int highest_priority = 0;

	for (i = 0; i < n; i++) {
		if (nl) {
			if (nl[i].priority >= highest_priority) {
				if (nl[i].done == 0) {
					nindex = i;
					highest_priority = nl[i].priority;
				}
			}
		}
	}

	return (nindex);
}

static void do_down(struct gml_graph *g, int l)
{
	int i = 0;
	int index = 0;
	int j = 0;
	int optimal_position = 0;
	int distance = 0;
	int possible_distance = 0;

	if (nl == NULL) {	/*shuldnothappen */
		return;
	}

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
					possible_distance +=
					    nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist;
				} else {
					/* j==0, no nodes at left */
					possible_distance += (nl[j].node->absx + nl[j].node->bbx) /* XXX +bbx? */ -xmindist;
				}
				j--;
			}
			while ((j >= 0) && (nl[j].done == 0));

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
					if (nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist < distance) {
						d = nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist;
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
					possible_distance += nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist;
				} else {
					/* j == g->nnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < g->nnodes_of_level[l]) && (nl[j].done == 0));

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
					if (nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist < distance) {
						d = nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist;
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
					possible_distance +=
					    nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist;
				} else {
					/* j == 0, no nodes links */
					possible_distance += (nl[0].node->absx + nl[0].node->bbx) /* XXX +bbx? */ -xmindist;
				}
				j--;
			}
			while ((j >= 0) && (nl[j].done == 0));

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
					if (nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist < distance) {
						d = nl[j].node->absx - (nl[j - 1].node->absx + nl[j - 1].node->bbx) - xmindist;
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
					possible_distance += nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist;
				} else {
					/* j == g->nnodes_of_level[l]-1, no nodes rechts */
					possible_distance += distance;
				}
				j++;
			}
			while ((j < g->nnodes_of_level[l]) && (nl[j].done == 0));

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
					if (nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist < distance) {
						d = nl[j + 1].node->absx - (nl[j].node->absx + nl[j].node->bbx) - xmindist;
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

/* build data */
static void pos3init(struct gml_graph *g)
{
	struct node_data *pnl = NULL;
	struct gml_nlist *gnl = NULL;
	struct gml_node *n = NULL;
	int i = 0;
	int j = 0;
	int my = 0;
	int yoff = 0;

	dl = dp_calloc(1, ((g->maxlevel + 1) * sizeof(struct node_data *)));

	if (dl == NULL) {
		return;
	}

	for (i = 0; i <= g->maxlevel; i++) {
		dl[i] = dp_calloc(1, ((g->nnodes_of_level[i] + 1) * sizeof(struct node_data)));
		if (dl[i] == NULL) {
			return;
		}
	}

	cix = dp_calloc(1, ((g->maxlevel + 1) * sizeof(int)));

	if (cix == NULL) {
		return;
	}

	/* for_all_nodes(g,n) */
	gnl = g->nodelist;
	while (gnl) {
		n = gnl->node;
		pnl = dl[n->rely];
		pnl[cix[n->rely]].node = n;
		pnl[cix[n->rely]].done = 0;
		pnl[cix[n->rely]].priority = 0;
		cix[n->rely]++;
		gnl = gnl->next;
	}

	for (i = 0; i <= g->maxlevel; i++) {
		nl = dl[i];
		if (g->nnodes_of_level[i]) {
			sort(g->nnodes_of_level[i]);
		}
	}

	/* calc max y-size at every level */
	szy = dp_calloc(1, ((g->maxlevel + 1) * sizeof(int)));

	if (szy == NULL) {
		return;
	}

	/* y offset */
	yoff = 0;

	for (i = 0; i <= g->maxlevel; i++) {
		nl = dl[i];
		my = 0;
		/* determine needed y size of this level */
		for (j = 0; j < g->nnodes_of_level[i]; j++) {
			if (nl[j].node->bby > my) {
				/* node with largest y size */
				my = nl[j].node->bby;
			}
		}
		/* set this max. y as y size of this level */
		szy[i] = my;
		/* place the nodes */
		for (j = 0; j < g->nnodes_of_level[i]; j++) {
			/* node places centered halfway of level */
			nl[j].node->absy = yoff + ((szy[i] / 2) - (nl[j].node->bby / 2));
			nl[j].node->ly0 = yoff;
			nl[j].node->ly1 = (yoff + szy[i] /* XXX + ymindist */ );
			if (nl[j].node->dummy) {
				nl[j].node->bby = szy[i] + ymindist;
			}
		}
		yoff = yoff + my + ymindist;
	}

	return;
}

/* clear data */
static void pos3clear(struct gml_graph *g)
{
	struct node_data *pnl = NULL;
	int i = 0;

	if (dl) {
		for (i = 0; i <= g->maxlevel; i++) {
			pnl = dl[i];
			if (pnl) {
				dp_free(pnl);
				dl[i] = NULL;
			}
		}
		dp_free(dl);
	}

	if (cix) {
		dp_free(cix);
	}

	cix = NULL;

	if (szy) {
		dp_free(szy);
	}

	szy = NULL;

	dl = NULL;
	nl = NULL;

	return;
}

/* left most layout */
static void pos3leftmost(struct gml_graph *g)
{
	int i = 0;
	int j = 0;
	int mx = 0;

	/* left most layout setting all node x pos. to minimum needed value */
	for (i = 0; i < g->maxlevel; i++) {
		nl = dl[i];
		if (nl) {
			mx = 0;
			for (j = 0; j < g->nnodes_of_level[i]; j++) {
				if (nl[j].node) {
					nl[j].node->absx = mx;
					mx = mx + xmindist + nl[j].node->bbx;
				}
			}
		}
	}

	return;
}

/* fix dummy nodes */
static void pos3fixdummy(struct gml_graph *g, int level)
{
	int j = 0;
	int x0 = 0;
	int x1 = 0;

	nl = dl[level];

	if (nl == NULL) {
		return;
	}

	for (j = 0; j < g->nnodes_of_level[level]; j++) {
		/* do not move edge labels, only dummy nodes */
		if (nl[j].node->elabel == 0) {
			/* do not move if hor. edges */
			if (nl[j].node->incoming_e && nl[j].node->outgoing_e) {
				if (nl[j].node->incoming_e->edge->hedge == 0 && nl[j].node->outgoing_e->edge->hedge == 0) {
					/* this is a vertical edge */
					x0 = nl[j].node->incoming_e->edge->from_node->absx +
					    (nl[j].node->incoming_e->edge->from_node->bbx / 2);
					x1 = nl[j].node->outgoing_e->edge->to_node->absx +
					    (nl[j].node->outgoing_e->edge->to_node->bbx / 2);
					nl[j].node->absx = ((x0 + x1) / 2);
				}
			}
		}

	}

	return;
}

/* XXX todo this does not work as expected */
/* determine relative node pos. from the barycenter rel. node pos. */
static void improve_positions_3(struct gml_graph *g)
{
	struct gml_nlist *gnl = NULL;
	int i = 0;
	int count = 0;
	int ii = 0;
	int sl = 0;
	int mx = 0;
	int mylevel = 0;

	/* step size */
	ssize = 1;

	/* min. node dist, minimum 1 */
	xmindist = xspacing;
	ymindist = yspacing;

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
		gnl->node->ly0 = 0;
		gnl->node->ly1 = 0;
		if (gnl->node->dummy) {
			gnl->node->bbx = 0;
			gnl->node->bby = 0;
		}
		gnl = gnl->next;
	}

	/* build data */
	pos3init(g);

	/* left most layout */
	pos3leftmost(g);

	/* number of up/down sweeps */
	count = 2;

	for (ii = 0; ii < count; ii++) {

		/* from to of drawing to bottom */
		for (i = sl; i < g->maxlevel; i = i + ssize) {
			mylevel = i;
			if (g->nnodes_of_level[i]) {
				make_node_list_down(g, i);
				do_down(g, i);
			}
		}

		/* from bottom of drawing to top */
		for (i = mylevel; i > sl; i = i - ssize) {
			if (g->nnodes_of_level[i]) {
				make_node_list_up(g, i);
				do_up(g, i);
			}
		}
	}

	if ((sl + 2) < g->maxlevel) {
		for (i = sl; i < g->maxlevel; i = i + ssize) {
			if (g->nnodes_of_level[i]) {
				make_node_list_up(g, i);
				do_up(g, i);
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

	/* tune in-between levels with dummy nodes */
	if (ssize == 2 || 0) {
		ssize = 2;
		for (i = sl; i < g->maxlevel; i = i + ssize) {
			pos3fixdummy(g, (i + 1));
		}
	}

	/* clear all data */
	pos3clear(g);

	return;
}

/* switched between different modes */
void improve_positions3(struct gml_graph *g)
{
	printf("%s(): positioning mode is %d\n", __func__, postype);
	fflush(stdout);

	/* this can happen */
	if (g->nnodes_of_level == NULL) {
		return;
	}

	improve_positions_3(g);

	return;
}

/* end */
