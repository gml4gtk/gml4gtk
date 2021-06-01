
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
#include <math.h>		/* for fabs() */

#include "main.h"
#include "hier.h"
#include "uniqnode.h"
#include "sugi.h"
#include "dpmem.h"

/* updated qsort() to stable qsort() see https://nullprogram.com/blog/2014/08/29/ */

/* how much double values may differ when seen as same */
#define LOWVAL (0.01)

/* set to 1 for debug output */
static int s3debug = 0;

/* max level */
static int gmaxlevel = 0;

struct vertex {
	int id;			/* uniq node number */
	int level;		/* rel. y level */
	int *child;		/* outgoing edges */
	int no_of_child;	/* number of outgoing edges */
	int *parent;		/* incoming edges */
	int no_of_parent;	/* number of incoming edges */
	double barydown;	/* barycenter value */
	double baryup;		/* barycenter value */
	int x;			/* final rel. x pos */
	int y;			/* final rel. y pos */
	int qsortpos;		/* position for qsort */
};

/* node data arrays */
static struct vertex **tree = NULL;

/* extra crossings check */
static int doublecheck = 0;

/* */
static int nooflevels = 4;

/* nodes at level */
static struct gml_nlist **glevelnodes = NULL;
static struct gml_nlist **glevelnodesend = NULL;

/* number of nodes at level */
static int *nglevelnodes = NULL;

/* bool going down */
static int down = 0;

/* */
#define BARY(x)     (down ? x->barydown : x->baryup)
#define UN_BARY(x)  (down ? x->baryup   : x->barydown)

static int mediancomp(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x == *y) {
		return (0);
	}

	if (*x > *y) {
		return (1);
	}

	return (-1);
}

/* compare bary values */
static int comparevalue(const void *a, const void *b)
{
	struct vertex *x = (struct vertex *)a;
	struct vertex *y = (struct vertex *)b;
	/* if (BARY(x) == BARY(y)) */
	if (fabs(BARY(x) - BARY(y)) <= LOWVAL) {
		/* using pos. this changes the qsort() into stable qsort() */
		return (y->qsortpos - x->qsortpos);
	}
	if (BARY(x) > BARY(y)) {
		return (1);
	}
	return (-1);
}

/* a=child/parent numbers, b=id of node, c=no_of_child/parents */
static int *intchr(int *a, int b, int c)
{
	int i = 0;
	/* find pos. of node id in b in child/parent nodes */
	while (i < c) {
		if (b == a[i]) {
			return (a + i);
		}
		i++;
	}
	/* notfound shouldnothappen */
	return ((int *)0);
}

/* how many nodes at level */
static int levellength(int level)
{
	if (level < 0) {
		printf("%s(): level %d out of range\n", __func__, level);
		fflush(stdout);
		return (0);
	}
	if (level > gmaxlevel) {
		printf("%s(): level %d out of range\n", __func__, level);
		fflush(stdout);
		return (0);
	}
	return (nglevelnodes[level]);
}

/* median barycenter value of one node.
 * often the average is used of the positions of connecting nodes.
 * the median value is the middle number in a sorted list of positions:
 * example: 1 2 6 7 12
 * the median is the number 6 in the middle.
 * the average is 1+2+6+7+12/5 = 5.6
 * some tools have options to changed the way this barycenter is determined for different layouts.
 * qsort() is not stable sort which means that equal values can be swapped.
 * turn qsort into stable qsort adding position data.
 */
static void medianvalue(struct vertex *a)
{
	int la = 0;
	int ll = 0;
	int i = 0;
	int j = 0;
	double left = 0;
	double right = 0;
	double m = 0.0;
	int *orders = NULL;
	struct vertex *adjacent = NULL;

	if (a == NULL) {
		return;
	}

	/* get next level */
	if (down) {
		la = (a[0].level + 1);
		adjacent = tree[la];
		ll = levellength(adjacent[0].level);
	} else {
		la = (a[0].level - 1);
		if (la < 0) {
			printf("%s(): la=%d is out of range\n", __func__, la);
			fflush(stdout);
			return;
		}
		adjacent = tree[la];
		ll = levellength(adjacent[0].level);
	}

	/* no nodes at adj. */
	if (ll == 0) {
		if (down) {
			a->barydown = (-1.0);
		} else {
			a->baryup = (-1);
		}
		return;
	}

	orders = dp_calloc(1, ((ll + 1) * sizeof(int)));

	if (orders == NULL) {
		return;
	}

#define RELATIVE(x) (down ? x->child : x->parent)
#define LENGTH(x)   (down ? x->no_of_child : x->no_of_parent)

	j = 0;

	for (i = 1; i <= ll; i++) {
		/* find pos. of node id in b in child/parent nodes */
		if (intchr(RELATIVE(a), adjacent[i - 1].id, LENGTH(a))) {
			orders[j] = i;
			j++;
		}
	}

	if (s3debug) {
		printf("%s(): %d nmemb\n", __func__, j);
	}

	/* sort if more then 1 item to sort */
	if (j > 1) {
		/* to make this stable qsort() it needs extra position data field */
		qsort(orders, j, sizeof(int), mediancomp);
	}

	if (j == 0) {
		if (down) {
			a->barydown = (-1.0);
		} else {
			a->baryup = (-1.0);
		}
		dp_free(orders);
		orders = NULL;
		return;
	}

	if (j % 2) {
		if (down) {
			a->barydown = ((double)orders[(j - 1) / 2]);
		} else {
			a->baryup = ((double)orders[(j - 1) / 2]);
		}
		dp_free(orders);
		orders = NULL;
		return;
	}

	if (j == 2) {
		if (down) {
			a->barydown = (((double)orders[0] + (double)orders[1]) / 2.0);
		} else {
			a->baryup = (((double)orders[0] + (double)orders[1]) / 2.0);
		}
		dp_free(orders);
		orders = NULL;
		return;
	}

	left = (double)orders[j / 2 - 1] - (double)orders[0];
	right = (double)orders[j - 1] - (double)orders[j / 2];

	m = 1.0 * ((double)orders[j / 2 - 1] * right + 1.0 * (double)orders[j / 2] * left) / (left + right);

	if (down) {
		a->barydown = m;
	} else {
		a->baryup = m;
	}

	dp_free(orders);
	orders = NULL;

	return;
}

/* */
static int twovertcross(struct vertex *a, struct vertex *b, int *sorted, int k)
{
	int i = 0;
	int j = 0;
	int sum = 0;
	int *c = NULL;
	int *d = NULL;
	if (s3debug) {
		printf("node %d has %d children, node %d has %d children\n", a->id, a->no_of_child, b->id, b->no_of_child);
	}
	if (a->no_of_child == 0) {
		return (0);
	}
	if (b->no_of_child == 0) {
		return (0);
	}
	for (i = 0; i < a->no_of_child; i++) {
		for (j = 0; j < b->no_of_child; j++) {
			c = intchr(sorted, a->child[i], k);
			d = intchr(sorted, b->child[j], k);
			if ((c - sorted) > (d - sorted)) {
				sum++;
			}
		}
	}
	return sum;
}

/* */
static int levelcross(struct vertex *a)
{
	int lb = 0;
	int i = 0;
	int j = 0;
	int t = 0;
	int k = 0;
	int sum = 0;
	struct vertex *b = NULL;
	int *sorted = NULL;

	if ((a[0].level != 0) && ((down == 0) || (doublecheck != 0))) {
		lb = a[0].level - 1;
		if (lb < 0) {
			printf("%s(): lb is %d out of range\n", __func__, lb);
			fflush(stdout);
			return (0);
		}
		b = tree[lb];
		if (b == NULL) {
			printf("%s(): tree[%d] is null\n", __func__, lb);
			fflush(stdout);
			return (0);
		}
		k = levellength(a[0].level);
		sorted = (int *)dp_calloc(1, ((k + 2) * sizeof(int)));
		if (sorted == NULL) {
			return (0);
		}
		for (i = 0; i < k; i++) {
			sorted[i] = a[i].id;
		}
		t = levellength(b[0].level);
		for (i = 0; i < t - 1; i++) {
			for (j = i + 1; j < t; j++) {
				sum += twovertcross(b + i, b + j, sorted, k);
			}
		}
		dp_free(sorted);
		sorted = NULL;
		if (s3debug) {
			printf("%s(): sum(1) is %d\n", __func__, sum);
		}
		return (sum);
	}

	if ((a[0].level < (nooflevels - 1)) && ((down != 0) || (doublecheck != 0))) {
		lb = a[0].level + 1;
		b = tree[lb];
		k = levellength(b[0].level);
		sorted = (int *)dp_calloc(1, ((k + 2) * sizeof(int)));
		if (sorted == NULL) {
			return (0);
		}
		for (i = 0; i < k; i++) {
			sorted[i] = b[i].id;
		}
		t = levellength(a[0].level);
		for (i = 0; i < t - 1; i++) {
			for (j = i + 1; j < t; j++) {
				sum += twovertcross(a + i, a + j, sorted, k);
			}
		}
		dp_free(sorted);
		sorted = NULL;
		if (s3debug) {
			printf("%s(): sum(2) is %d\n", __func__, sum);
		}
		return (sum);
	}

	if (s3debug || 1) {
		printf("%s(): sum(3) is %d out of range\n", __func__, sum);
	}
	return (sum);
}

/* check eq bary values in t nodes at this level */
static int equals(struct vertex *a, int t)
{
	int res = 0;
	int i = 0;
	struct vertex *temp = NULL;
	temp = dp_calloc(1, sizeof(struct vertex));
	if (temp == NULL) {
		return (0);
	}
	for (i = 0; i < t - 1; i++) {
		/* if (BARY((a+i)) == BARY((a+i+1))) */
		if (fabs(BARY((a + i)) - BARY((a + i + 1))) <= LOWVAL) {
			memcpy(temp, a + i, sizeof(struct vertex));
			memcpy(a + i, a + i + 1, sizeof(struct vertex));
			memcpy(a + i + 1, temp, sizeof(struct vertex));
			/* indicate that changes were made */
			res++;
			if (s3debug) {
				printf("%s(): swap\n", __func__);
			}
		}
	}
	dp_free(temp);
	temp = NULL;
	/* return 0 if no changes made, <>0 if changed */
	return (res);
}

/* sort between level a and level b */
static void mediansort(struct gml_graph *g, struct vertex *a, struct vertex *b)
{
	int t = 0;
	int tb = 0;
	int i = 0;
	int p = 0;
	int la = 0;
	int ld = 0;
	struct vertex *dummy = NULL;
	struct vertex *dummy2 = NULL;
	struct vertex *temp = NULL;

	if (a == NULL) {	/* shouldnothappen */
		return;
	}
	if (b == NULL) {	/* shouldnothappen */
		return;
	}

	if (a[0].level == b[0].level) {
		printf("%s(): a %p and b %p have same level %d out of range\n", __func__, (void *)a, (void *)b, a[0].level);
		fflush(stdout);
		return;
	}

	if (a[0].level < 0 || a[0].level > gmaxlevel) {
		printf("%s(): level-a %d out of range 0...%d\n", __func__, a[0].level, gmaxlevel);
		fflush(stdout);
		return;
	}

	if (b[0].level < 0 || b[0].level > gmaxlevel) {
		printf("%s(): level-b %d out of range 0...%d\n", __func__, b[0].level, gmaxlevel);
		fflush(stdout);
		return;
	}

	/* how many nodes at level of a */
	t = levellength(a[0].level);

	if (t == 0) {
		/* this can happen but shouldnot XXX fixme */
		return;
		printf("%s(): a-level 0 nodes at level %d\n", __func__, a[0].level);
	}

	/* how many nodes at level of b */
	tb = levellength(b[0].level);

	if (tb == 0) {
		/* this can happen but shouldnot XXX fixme */
		return;
		printf("%s(): b-level 0 nodes at level %d\n", __func__, b[0].level);
	}

	/* XXX */
	if (a[0].level >= b[0].level) {
		down = 0;
	} else {
		down = 1;
	}

	if (s3debug || 0) {
		printf("%s(): level-a=%d has %d nodes, level-b=%d has %d nodes, down=%d\n", __func__, a[0].level, t, b[0].level, tb,
		       down);
	}

	/* buffer for test result */
	dummy = dp_calloc(1, ((t + 1) * sizeof(struct vertex)));

	if (dummy == NULL) {
		/* shouldnothappen */
		return;
	}

	dummy2 = dummy;

	/* calc node median of every node at level a */
	for (i = 0; i < t; i++) {
		medianvalue(a + i);
		if (s3debug || 0) {
			/* print node bary value */
			if (down) {
				printf("%s(): barydown=%f node %d\n", __func__, (a + i)->barydown, (a + i)->id);
			} else {
				printf("%s(): baryup=%f node %d\n", __func__, (a + i)->baryup, (a + i)->id);
			}
		}
	}

	/* copy a to dummy as backup */
	memcpy(dummy, a, ((t + 1) * sizeof(struct vertex)));

	if (s3debug || 0) {
		printf("%s(): sorting %d nmemb\n", __func__, t);
	}

	/* sort on barycenter value if more then 1 member */
	if (t > 1) {
		/* set pos to change qsort() into stable qsort */
		for (i = 0; i < t; i++) {
			tree[a[0].level]->qsortpos = i;
		}
		qsort(tree[a[0].level], t, sizeof(struct vertex), comparevalue);
	}

	la = levelcross(a);
	ld = levelcross(dummy);

	if (s3debug || 0) {
		printf("%s(): crossings level-a=%d is %d in a versus %d in dummy\n", __func__, a[0].level, la, ld);
	}

	/* save this crossing count */
	g->numce[a[0].level] = la;

	if (la == 0) {
		dp_free(dummy2);
		dummy2 = NULL;
		return;
	}

	/* if crossings in a > in dummy, use dummy backup */
	if (la > ld) {
		/* dummy bacup is better: less crossings */
		temp = a;
		/* copy dummy to a */
		memcpy(a, dummy, ((t + 1) * sizeof(struct vertex)));	/* tree[a[0].level] = dummy; */
		a = dummy;
		dummy = temp;
		/* save this crossing count */
		g->numce[a[0].level] = ld;
		if (ld == 0) {
			dp_free(dummy2);
			dummy2 = NULL;
			return;
		}
	}

	for (p = 0; p < 15; p++) {
		/* copy a to dummy as backup */
		memcpy(dummy, a, ((t + 1) * sizeof(struct vertex)));

		/* swap nodes with same barycenter */
		if (equals(a, t) == 0) {
			/* no changes made to node positions in this level */
			break;
		}

		la = levelcross(a);

		if (la == 0) {
			break;
		}

		ld = levelcross(dummy);

		/* save this crossing count */
		g->numce[a[0].level] = la;

		if (la >= ld) {
			/* dummy backup has less crossings, continue with dummy */
			temp = a;
			/* copy dummy to a */
			memcpy(a, dummy, ((t + 1) * sizeof(struct vertex)));	/* tree[a[0].level] = dummy; */
			a = dummy;
			dummy = temp;
			/* save this crossing count */
			g->numce[a[0].level] = ld;
			if (ld == 0) {
				break;
			}
		}
	}

	dp_free(dummy2);
	dummy2 = NULL;

	return;
}

/* return 0 if graph has no crossings */
static int check0(struct gml_graph *g)
{
	int sum = 0;
	int i = 0;
	for (i = 0; i < (g->maxlevel + 1); i++) {
		sum += g->numce[i];
		if (sum) {
			break;
		}
	}
	return (sum);
}

/* create lists of nodes per level */
static void cp_make_levelnodes(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;

	glevelnodes = dp_calloc(1, (g->maxlevel + 1) * sizeof(struct gml_nlist *));

	if (glevelnodes == NULL) {
		return;
	}

	glevelnodesend = dp_calloc(1, (g->maxlevel + 1) * sizeof(struct gml_nlist *));

	if (glevelnodesend == NULL) {
		return;
	}

	nglevelnodes = dp_calloc(1, (g->maxlevel + 1) * sizeof(int));

	if (nglevelnodes == NULL) {
		return;
	}

	lnll = g->nodelist;

	while (lnll) {
		/* rel. y level set by dfs/bfs */
		i = lnll->node->rely;

		newl = dp_calloc(1, sizeof(struct gml_nlist));

		if (newl == NULL) {
			return;
		}

		newl->node = lnll->node;

		if (glevelnodes[i] == NULL) {
			glevelnodes[i] = newl;
			glevelnodesend[i] = newl;
		} else {
			glevelnodesend[i]->next = newl;
			glevelnodesend[i] = newl;
		}

		/* number of nodes at this level */
		nglevelnodes[i]++;

		lnll = lnll->next;
	}

	/* extra check */
	for (i = 0; i < (g->maxlevel + 1); i++) {
		if (nglevelnodes[i] == 0) {
			/* shouldnothappen */
			printf("%s(): level %d has no nodes\n", __func__, i);
			fflush(stdout);
		}
	}

	return;
}

/* clear nodes at level */
static void clr_levelnodes(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	int i = 0;

	if (glevelnodes == NULL) {
		return;
	}

	for (i = 0; i < (g->maxlevel + 1); i++) {
		/* lists per pos. */
		lnll = glevelnodes[i];
		while (lnll) {
			nlnext = lnll->next;
			dp_free(lnll);
			lnll = NULL;
			lnll = nlnext;
		}

		glevelnodes[i] = NULL;
		glevelnodesend[i] = NULL;
	}

	dp_free(glevelnodes);
	glevelnodes = NULL;

	dp_free(glevelnodesend);
	glevelnodesend = NULL;

	dp_free(nglevelnodes);
	nglevelnodes = NULL;

	return;
}

/* copy data into tree data */
static void cp_data(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_nlist *lnll = NULL;
	int i = 0;
	int count = 0;
	int k = 0;

	tree = dp_calloc(1, ((g->maxlevel + 2) * sizeof(struct vertex *)));

	if (tree == NULL) {
		return;
	}

	/* create nodes on level */
	cp_make_levelnodes(g);

	for (i = 0; i < (g->maxlevel + 1); i++) {

		if (s3debug) {
			printf("%s(): level %d has %d nodes\n", __func__, i, nglevelnodes[i]);
		}

		tree[i] = dp_calloc(1, ((nglevelnodes[i] + 1) * sizeof(struct vertex)));

		if (tree[i] == NULL) {
			return;
		}

		tree[i][0].level = i;

		/* get list of nodes at level i */
		lnll = glevelnodes[i];

		count = 0;
		while (lnll) {
			/* set node uniq number starting at 1 */
			tree[i][count].id = lnll->node->nr;
			tree[i][count].level = lnll->node->rely;
			if (s3debug) {
				printf("%s(): node %d has %d parents, %d children\n", __func__, lnll->node->nr,
				       lnll->node->indegree, lnll->node->outdegree);
			}
			/* set incoming edges if any */
			if (lnll->node->indegree) {
				tree[i][count].no_of_parent = lnll->node->indegree;
				tree[i][count].parent = dp_calloc(1, ((lnll->node->indegree + 0) * sizeof(int)));
				if (tree[i][count].parent == NULL) {
					return;
				}
				k = 0;
				el = lnll->node->incoming_e;
				while (el) {
					/* skip hor. edges */
					if (el->edge->hedge == 0) {
						/* set number of to node */
						tree[i][count].parent[k] = el->edge->from_node->nr;
						if (el->edge->to_node->nr != lnll->node->nr) {
							printf("%s(): fixme(1)\n", __func__);
						}
						k++;
					}
					el = el->next;
				}
				tree[i][count].no_of_parent = k;
			} else {
				tree[i][count].no_of_parent = 0;
				tree[i][count].parent = NULL;
			}
			/* set outgoing edges if any */
			if (lnll->node->outdegree) {
				tree[i][count].no_of_child = lnll->node->outdegree;
				tree[i][count].child = dp_calloc(1, ((lnll->node->outdegree + 0) * sizeof(int)));
				if (tree[i][count].child == NULL) {
					return;
				}
				k = 0;
				el = lnll->node->outgoing_e;
				while (el) {
					/* skip hor. edges */
					if (el->edge->hedge == 0) {
						/* set number of from node */
						tree[i][count].child[k] = el->edge->to_node->nr;
						if (el->edge->from_node->nr != lnll->node->nr) {
							printf("%s(): fixme(2)\n", __func__);
						}
						k++;
					}
					el = el->next;
				}
				tree[i][count].no_of_child = k;
			} else {
				tree[i][count].no_of_child = 0;
				tree[i][count].child = NULL;
			}
			count++;
			lnll = lnll->next;
		}

		/* last entry has id 0 */
		tree[i][count].id = 0;
	}			/* to next level */

	if (s3debug || 0) {
		printf("%s(): tree[i][0].level values are ", __func__);
		for (i = 0; i < (g->maxlevel + 1); i++) {
			printf("%d ", tree[i][0].level);
			if (tree[i][0].level == -1) {
				tree[i][0].level = i;
			}
		}
		printf("\n");
	}

	return;
}

/* clear data in tree data */
static void clr_data(struct gml_graph *g)
{
	int i = 0;
	int j = 0;

	/* copy new node positions */
	for (i = 0; i <= g->maxlevel; i++) {
		if (tree[i]) {
			/* scan nodes at level [i] */
			j = 0;
			while (tree[i][j].id != 0) {
				if (tree[i][j].child) {
					dp_free(tree[i][j].child);
					tree[i][j].child = NULL;
				}
				if (tree[i][j].parent) {
					dp_free(tree[i][j].parent);
					tree[i][j].parent = NULL;
				}
				/* to next x pos */
				j++;
			}
			dp_free(tree[i]);
			tree[i] = NULL;
		}

	}

	if (tree) {
		dp_free(tree);
		tree = NULL;
	}

	/* clear nodes at level */
	clr_levelnodes(g);

	return;
}

/* start */
static void barycenter_3(struct gml_graph *g, int it1v, int it2v)
{
	int i = 0;
	int j = 0;
	int k = 0;
	struct gml_node *n = NULL;

	if (it1v) {
	}
	if (it2v) {
	}

	/* copy data */
	cp_data(g);

	/* higest level in use */
	i = g->maxlevel;
	gmaxlevel = g->maxlevel;
	nooflevels = g->maxlevel;

	/* print raw data */
	if (s3debug || 0) {
		for (i = 0; i <= g->maxlevel; i++) {
			/* scan nodes at level [i] */
			if (tree[i]) {
				j = 0;
				while (tree[i][j].id != 0) {
					printf("%s(): node %d has %d parents, %d children\n", __func__, tree[i][j].id,
					       tree[i][j].no_of_parent, tree[i][j].no_of_child);
					/* to next x pos */
					j++;
				}
			}
		}
	}

	for (k = 0; k < 15; k++) {
		/* do some extra check bool */
		doublecheck = (k % 4) * ((k + 1) % 4);
		/* from top to bottom */
		for (j = 1; j < i; j++) {
			mediansort(g, tree[j], tree[j - 1]);
		}
		/* from bottom to top */
		for (j = i - 1; j > 0; j--) {
			mediansort(g, tree[j - 1], tree[j]);
		}
		if (check0(g) == 0) {
			/* no edge crossings */
			break;
		}
		/* from top to bottom */
		for (j = 1; j < i; j++) {
			mediansort(g, tree[j - 1], tree[j]);
		}
		/* from bottom to top */
		for (j = i - 1; j > 0; j--) {
			mediansort(g, tree[j], tree[j - 1]);
		}
		if (check0(g) == 0) {
			/* no edge crossings */
			break;
		}
	}

	/* copy new node positions */
	for (i = 0; i < (g->maxlevel + 1); i++) {
		/* scan nodes at level [i] */
		if (tree[i]) {
			j = 0;
			while (tree[i][j].id != 0) {
				tree[i][j].y = i;	/* rel. y pos. */
				tree[i][j].x = j;	/* rel. x pos. */
				/* find the node with this id */
				n = uniqnode2(g, tree[i][j].id);
				if (n) {
					if (tree[i][j].y == n->rely) {
						/* oke and set node rel. x pos */
						n->relx = tree[i][j].x;
					} else {
						/* shpuldnothappen */
						printf("%s(): node %d moved from level %d to level %d\n", __func__, n->nr, n->rely,
						       tree[i][j].y);
					}
				} else {
					/* shpuldnothappen */
					printf("%s(): node id %d not found\n", __func__, tree[i][j].id);
				}
				/* to next x pos */
				j++;
			}
		}
	}

	/* clear data in tree */
	clr_data(g);

	return;
}

void reduce_crossings3(struct gml_graph *g, int it1v, int it2v)
{
	int i = 0;
	int tsum = 0;

	/* number of crossing edges at level */
	if (g->numce == NULL) {
		g->numce = (int *)dp_calloc(1, (g->maxlevel + 1) * sizeof(int));
		if (g->numce == NULL) {
			return;
		}
	}

	if (g->maxlevel == 0) {
		/* if graph has only 1 or more nodes */
		return;
	}

	/* with too complex graph data at least this message is on console before cpu get roasted. */
	printf("%s(): starting barycenter algorithm for graph with %d nodes, %d edges in %d levels ... wait\n", __func__, g->nnodes,
	       g->nedges, g->maxlevel);
	fflush(stdout);

	if (g->nnodes < 2) {
		/* only 1 node, not much todo */
		return;
	}

	if (g->nedges < 2) {
		/* only 1 level, not much todo */
		return;
	}

	barycenter_3(g, it1v, it2v);

	/* (not determined) */
	g->sugi_icrossings = 0;	/* sugiyama initial crossings */

	/* calc total number of crossings */
	for (i = 0; i < g->maxlevel; i++) {
		tsum += g->numce[i];
	}

	/* sugiyama final crossings */
	g->sugi_fcrossings = tsum;

	/* sugiyama changes made (not determined) */
	g->sugi_changes = 0;

	return;
}

/* end */
