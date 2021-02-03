
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

/* how much double values may differ when seen as same */
#define LOWVAL (0.01)

struct suginode {
	int id;			/* uniq node number */
	int level;		/* rel. y level */
	int pos;		/* rel. x position */
	int *outgoing;		/* outgoing edges */
	int outdegree;		/* number of outgoing edges */
	int *incoming;		/* incoming edges */
	int indegree;		/* number of incoming edges */
	double barydown;	/* barycenter value */
	double baryup;		/* barycenter value */
};

/* set to 1 for debug output */
static int s3debug = 0;

/* max level in use */
static int gmaxlevel = 0;

/* number of levels */
static int gnlevels = 0;

/* node data arrays */
static struct suginode **sugidata = NULL;

/* nodes at level */
static struct gml_nlist **glevelnodes = NULL;
static struct gml_nlist **glevelnodesend = NULL;

/* number of nodes at level */
static int *nglevelnodes = NULL;

/* bool set if going downwards from level n+1 to level n, else upwards */
static int down = 0;

/* cur. crossings */
static int curcross = 0;

/* how many nodes at level */
static int levellength(int level)
{
	if (level < 0) {
		printf("%s(): level %d is out of range\n", __func__, level);
		fflush(stdout);
		return (0);
	}
	if (level > gmaxlevel) {
		printf("%s(): level %d is out of range\n", __func__, level);
		fflush(stdout);
		return (0);
	}
	return (nglevelnodes[level]);
}

/* renumber pos field of nodes at one level */
static void renumber(struct suginode *a)
{
	int i = 0;
	for (i = 0; i < levellength(a[0].level); i++) {
		(a + i)->pos = i;	/* a[i].pos */
	}
	return;
}

/* return 0 if graph has no crossings */
static int check0(struct gml_graph *g)
{
	int sum = 0;
	int i = 0;
	for (i = 0; i < gnlevels; i++) {
		/* add number of crossings at level i */
		sum += g->numce[i];
	}
	return (sum);
}

/* get pos. of node with nr in array b with nodes */
static int posat(struct suginode *b, int nr)
{
	int ret = 0;
	int i = 0;
	/* check all nodes in b */
	for (i = 0; i < levellength(b[0].level); i++) {
		if (i != b[i].pos) {
			printf("%s(): at level %d pos %d but found pos %d\n", __func__, b[0].level, i, b[i].pos);
		}
		if (b[i].id == nr) {
			break;
		}
	}
	/* check this is the found node and get position */
	if (b[i].id == nr) {
		ret = b[i].pos;
	} else {
		/* shouldnothappen */
		printf("%s(): node %d not found at level %d\n", __func__, nr, b[0].level);
		fflush(stdout);
		ret = -1;
	}
	return (ret);
}

/* median value of one node */
static void medianvalue(struct suginode *a, struct suginode *b)
{
	int *lookat = NULL;
	int nlookat = 0;
	int i = 0;
	int nn = 0;
	int p = 0;
	double val = 0.0;

	if (down) {
		/* look at outgoing edges */
		lookat = a->outgoing;
		nlookat = a->outdegree;
	} else {
		/* look at incoming edges */
		lookat = a->incoming;
		nlookat = a->indegree;
		a->baryup = 1.0;
	}

	/* if no degree, place node most left */
	if (nlookat == 0) {
		if (down) {
			a->barydown = (-1.0);
		} else {
			a->baryup = (-1.0);
		}
		return;
	}

	/* for every degree */
	for (i = 0; i < nlookat; i++) {
		/* get number of connecting node */
		nn = lookat[i];
		/* get pos. of connecting node in edge */
		p = posat(b, nn);
		/* sum positions */
		val = (val + (double)p);
	}

	/* mult, to get better resoultion */
	val = (val * 100);

	/* avg., div. by degree */
	val = (val / (double)nlookat);

	if (down) {
		a->barydown = (val);
	} else {
		a->baryup = (val);
	}

	return;
}

/* compare bary values */
static int comparevalue(const void *a, const void *b)
{
	struct suginode *x = (struct suginode *)a;
	struct suginode *y = (struct suginode *)b;
	double baryx = 0.0;
	double baryy = 0.0;
	if (down) {
		baryx = x->barydown;
		baryy = y->barydown;
	} else {
		baryx = x->baryup;
		baryy = y->baryup;
	}
	/* if (baryx == baryy) */
	if (fabs(baryx - baryy) <= LOWVAL) {
		return (0);
	}
	if (baryx > baryy) {
		return (1);
	}
	/* baryx < baryy */
	return (-1);
}

/* */
static int twovertcross(struct suginode *a, struct suginode *b, struct suginode *cc)
{
	int i = 0;
	int j = 0;
	int sum = 0;
	int c = 0;
	int d = 0;
	if (s3debug || 0) {
		printf("node %d level %d has %d children, node %d level %d has %d children\n", a->id, a->level, a->outdegree, b->id,
		       b->level, b->outdegree);
	}
	if (a->outdegree == 0) {
		return (0);
	}
	if (b->outdegree == 0) {
		return (0);
	}
	for (i = 0; i < a->outdegree; i++) {
		for (j = 0; j < b->outdegree; j++) {
			/* get pos of outgoing nodes */
			c = posat(cc, a->outgoing[i]);
			d = posat(cc, b->outgoing[j]);
			if (c > d) {
				sum++;
			}
		}
	}
	return (sum);
}

/* */
static int levelcross(struct suginode *a, struct suginode *b)
{
	int cross = 0;
	int i = 0;
	int j = 0;
	int t = 0;
	if (s3debug || 0) {
		printf("%s(): down=%d level-a=%d level-b=%d\n", __func__, down, a[0].level, b[0].level);
	}
	if (down) {
		/* down==1 */
		i = levellength(b[0].level);
		t = levellength(a[0].level);
		if (i == 0 || t == 0) {
			/*shouldnothappen */
			return (0);
		}

		for (i = 0; i < t - 1; i++) {
			for (j = i + 1; j < t; j++) {
				cross = cross + twovertcross((a + i), (a + j), b);
			}
		}

	} else {
		/* down==0 */
		i = levellength(a[0].level);
		t = levellength(b[0].level);
		if (i == 0 || t == 0) {
			/*shouldnothappen */
			return (0);
		}
		for (i = 0; i < (t - 1); i++) {
			for (j = (i + 1); j < t; j++) {
				cross = cross + twovertcross((b + i), (b + j), a);
			}
		}

	}
	return (cross);
}

/* check eq bary values in t nodes at this level */
static int equals(struct suginode *a, int t)
{
	int res = 0;
	int i = 0;
	struct suginode *temp = NULL;
	double baryx = 0.0;
	double baryy = 0.0;
	temp = calloc(1, sizeof(struct suginode));
	if (temp == NULL) {
		return (0);
	}
	/* scan all nodes at this level */
	for (i = 0; i < (t - 1); i++) {
		if (down) {
			baryx = (a + i)->barydown;
			baryy = (a + i + 1)->barydown;
		} else {
			baryx = (a + i)->baryup;
			baryy = (a + i + 1)->baryup;
		}
		/* if (baryx == baryy) swap nodes */
		if (fabs(baryx - baryy) <= LOWVAL) {
			/* copy node in (a+i) to temp */
			memcpy(temp, a + i, sizeof(struct suginode));
			/* copy node in (a+i+1) to (a+i) */
			memcpy(a + i, a + i + 1, sizeof(struct suginode));
			/* copy node in temp to (a+i+1) */
			memcpy(a + i + 1, temp, sizeof(struct suginode));
			/* indicate that changes were made */
			res++;
		}
	}
	free(temp);
	temp = NULL;
	/* return 0 if no changes made, <>0 if changed */
	return (res);
}

/* sort between level a and level b 
 * if going up from level 1 to n, a=level-1, b=level-0
 */
static void mediansort(struct gml_graph *g, struct suginode *a, struct suginode *b)
{
	int nc = 0;
	int t = 0;
	int tb = 0;
	int i = 0;
	int p = 0;
	int la = 0;
	int ld = 0;
	struct suginode *dummy = NULL;

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
		printf("%s(): a-level 0 nodes at level %d\n", __func__, a[0].level);
		return;
	}

	/* only 1 node at this level then no crossings */
	if (t == 1) {
		return;
	}

	/* how many nodes at level of b */
	tb = levellength(b[0].level);

	if (tb == 0) {
		printf("%s(): b-level 0 nodes at level %d\n", __func__, b[0].level);
		return;
	}

	/* a-level is 1, b-level is 0, at [1...gmaxlevel] down=0; */
	/* a-level is (gmaxlevel - 1), b-level is (gmaxlevel - 2) at [.gmaxlevel...1] */
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
	dummy = calloc(1, (t * sizeof(struct suginode)));

	if (dummy == NULL) {
		/* shouldnothappen */
		return;
	}

	/* calc node median of every node at level a */
	for (i = 0; i < t; i++) {
		/* get i'th node in array a and search in array b */
		medianvalue((a + i), b);
		if (s3debug || 0) {
			/* print node bary value */
			if (down) {
				printf("%s(): barydown=%f node %d\n", __func__, a[i].barydown, a[i].id);
			} else {
				printf("%s(): baryup=%f node %d\n", __func__, a[i].baryup, a[i].id);
			}
		}
	}

	/* copy a to dummy as backup */
	(void)memcpy(dummy, sugidata[a[0].level], (t * sizeof(struct suginode)));

	if (s3debug || 0) {
		printf("%s(): sorting %d nmemb\n", __func__, t);
	}

	/* sort on barycenter value if more then 1 member */
	if (t > 1) {
		/* sort on avg. in/out positions of connecting nodes */
		qsort(sugidata[a[0].level], t, sizeof(struct suginode), comparevalue);
		/* nodes may have changed positions, re-number the pos field */
		renumber(a);
	}

	la = levelcross(a, b);
	renumber(dummy);
	ld = levelcross(dummy, b);

	if (s3debug || 0) {
		printf("%s(): crossings level-a=%d is %d versus %d in dummy\n", __func__, a[0].level, la, ld);
	}

	/* save this crossing count */
	g->numce[a[0].level] = la;

	if (la == 0) {
		free(dummy);
		dummy = NULL;
		return;
	}

	/* if crossings in a > in dummy, use dummy backup */
	if (la > ld) {
		/* dummy backup is better: less crossings */
		/* copy dummy to a */
		memcpy(sugidata[a[0].level], dummy, (t * sizeof(struct suginode)));
		renumber(a);
		/* save this crossing count */
		g->numce[a[0].level] = ld;
		if (ld == 0) {
			free(dummy);
			dummy = NULL;
			return;
		}
	}

	/* now swap nodes with equal bary at this level */
	for (p = 0; p < 5; p++) {
		/* copy a to dummy as backup */
		memcpy(dummy, sugidata[a[0].level], (t * sizeof(struct suginode)));

		/* swap nodes with same barycenter and return number of nodes swapped */
		nc = equals(sugidata[a[0].level], t);

		if (nc == 0) {
			/* no changes made to node positions in this level */
			break;
		}

		/* changes were made, so re-number node pos */
		renumber(a);

		la = levelcross(a, b);

		if (la == 0) {
			/* save this crossing count */
			g->numce[a[0].level] = la;
			break;
		}

		ld = levelcross(dummy, b);

		/* save this crossing count */
		g->numce[a[0].level] = la;

		if (la >= ld) {
			/* dummy backup has less crossings, continue with dummy */
			/* copy dummy to a */
			memcpy(sugidata[a[0].level], dummy, (t * sizeof(struct suginode)));
			renumber(a);
			/* save this crossing count */
			g->numce[a[0].level] = ld;
			if (ld == 0) {
				break;
			}
		}
	}

	free(dummy);
	dummy = NULL;

	return;
}

/* create lists of nodes per level */
static void cp_make_levelnodes(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;

	glevelnodes = calloc(1, (gnlevels * sizeof(struct gml_nlist *)));

	if (glevelnodes == NULL) {
		return;
	}

	glevelnodesend = calloc(1, (gnlevels * sizeof(struct gml_nlist *)));

	if (glevelnodesend == NULL) {
		return;
	}

	nglevelnodes = calloc(1, (gnlevels * sizeof(int)));

	if (nglevelnodes == NULL) {
		return;
	}

	lnll = g->nodelist;

	while (lnll) {
		/* rel. y level set by dfs/bfs */
		i = lnll->node->rely;

		newl = calloc(1, sizeof(struct gml_nlist));

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
	for (i = 0; i < gnlevels; i++) {
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

	if (g) {
	}

	if (glevelnodes == NULL) {
		return;
	}

	for (i = 0; i < gnlevels; i++) {
		/* lists per pos. */
		lnll = glevelnodes[i];
		while (lnll) {
			nlnext = lnll->next;
			free(lnll);
			lnll = NULL;
			lnll = nlnext;
		}

		glevelnodes[i] = NULL;
		glevelnodesend[i] = NULL;
	}

	free(glevelnodes);
	glevelnodes = NULL;

	free(glevelnodesend);
	glevelnodesend = NULL;

	return;
}

/* clear number of nodes for every level */
static void clr_nglevelnodes(void)
{

	free(nglevelnodes);
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

	sugidata = calloc(1, (gnlevels * sizeof(struct suginode *)));

	if (sugidata == NULL) {
		return;
	}

	/* create nodes on level */
	cp_make_levelnodes(g);

	for (i = 0; i < gnlevels; i++) {

		if (s3debug) {
			printf("%s(): level %d has %d nodes\n", __func__, i, nglevelnodes[i]);
		}

		sugidata[i] = calloc(1, (nglevelnodes[i] * sizeof(struct suginode)));

		if (sugidata[i] == NULL) {
			return;
		}

		sugidata[i][0].level = i;

		/* get list of nodes at level i */
		lnll = glevelnodes[i];

		count = 0;
		while (lnll) {
			/* set node uniq number starting at 1 */
			sugidata[i][count].id = lnll->node->nr;
			sugidata[i][count].level = lnll->node->rely;
			sugidata[i][count].pos = count;
			if (s3debug) {
				printf("%s(): node %d has %d parents, %d children\n", __func__, lnll->node->nr,
				       lnll->node->indegree, lnll->node->outdegree);
			}
			/* set incoming edges if any */
			if (lnll->node->indegree) {
				sugidata[i][count].indegree = lnll->node->indegree;
				sugidata[i][count].incoming = calloc(1, (lnll->node->indegree * sizeof(int)));
				if (sugidata[i][count].incoming == NULL) {
					return;
				}
				k = 0;
				el = lnll->node->incoming_e;
				while (el) {
					/* skip the hor. edges */
					if (el->edge->hedge == 0) {
						/* set number of to node */
						sugidata[i][count].incoming[k] = el->edge->from_node->nr;
						if (el->edge->to_node->nr != lnll->node->nr) {
							printf("%s(): fixme(1)\n", __func__);
						}
						k++;
					}
					el = el->next;
				}
				/* indegree without hor. edges */
				sugidata[i][count].indegree = k;
			} else {
				sugidata[i][count].indegree = 0;
				sugidata[i][count].incoming = NULL;
			}
			/* set outgoing edges if any */
			if (lnll->node->outdegree) {
				sugidata[i][count].outdegree = lnll->node->outdegree;
				sugidata[i][count].outgoing = calloc(1, (lnll->node->outdegree * sizeof(int)));
				if (sugidata[i][count].outgoing == NULL) {
					return;
				}
				k = 0;
				el = lnll->node->outgoing_e;
				while (el) {
					/* skip hor. edges */
					if (el->edge->hedge == 0) {
						/* set number of from node */
						sugidata[i][count].outgoing[k] = el->edge->to_node->nr;
						if (el->edge->from_node->nr != lnll->node->nr) {
							printf("%s(): fixme(2)\n", __func__);
						}
						k++;
					}
					el = el->next;
				}
				/* outdegree without hor. edges */
				sugidata[i][count].outdegree = k;
			} else {
				sugidata[i][count].outdegree = 0;
				sugidata[i][count].outgoing = NULL;
			}
			count++;
			lnll = lnll->next;
		}

	}			/* to next level */

	if (s3debug || 0) {
		printf("%s(): sugidata[i][0].level values are ", __func__);
		for (i = 0; i < gnlevels; i++) {
			printf("%d ", sugidata[i][0].level);
		}
		printf("\n");
	}

	clr_levelnodes(g);

	return;
}

/* clear data in tree data */
static void clr_data(struct gml_graph *g)
{
	int i = 0;
	int j = 0;

	if (g) {
	}

	/* copy new node positions */
	for (i = 0; i < gnlevels; i++) {
		/* scan nodes at level [i] */
		for (j = 0; j < nglevelnodes[i]; j++) {
			if (sugidata[i][j].outdegree) {
				free(sugidata[i][j].outgoing);
				sugidata[i][j].outgoing = NULL;
			}
			if (sugidata[i][j].indegree) {
				free(sugidata[i][j].incoming);
				sugidata[i][j].incoming = NULL;
			}
		}
		free(sugidata[i]);
		sugidata[i] = NULL;
	}

	free(sugidata);
	sugidata = NULL;

	/* clear number of nodes at level */
	clr_nglevelnodes();

	return;
}

/* start */
static void barycenter_4(struct gml_graph *g, int it1v, int it2v)
{
	int i = 0;
	int j = 0;
	int k = 0;
	struct gml_node *n = NULL;
	int ic = 0;
	int ic16 = 0;
	int prevcross = 0;
	int wcross = 0;
	int count = 0;

	if (it1v) {
	}
	if (it2v) {
	}

	/* set higest level in use and number of levels */
	gmaxlevel = g->maxlevel;
	gnlevels = (gmaxlevel + 1);

	/* copy data */
	cp_data(g);

	/* print raw data */
	if (s3debug || 0) {
		for (i = 0; i < gnlevels; i++) {
			/* scan nodes at level [i] */
			for (j = 0; j < nglevelnodes[i]; j++) {
				printf("%s(): node %d has %d indegree, %d outdegree\n", __func__, sugidata[i][j].id,
				       sugidata[i][j].indegree, sugidata[i][j].outdegree);
			}
		}
	}

	/* scan layout, but not unlimited long */
	for (k = 0; k < 1000; k++) {

		/* from top to bottom */
		for (j = 1; j < gmaxlevel; j++) {
			mediansort(g, sugidata[j], sugidata[j - 1]);
		}

		curcross = check0(g);
		if (curcross == 0) {
			/* no edge crossings */
			break;
		}

		/* from bottom to top */
		for (j = gmaxlevel; j > 0; j--) {
			mediansort(g, sugidata[j - 1], sugidata[j]);
		}

		curcross = check0(g);
		if (ic == 0) {
			printf("%s(): %d initial crossings\n", __func__, curcross);
			fflush(stdout);
			ic = curcross;
			ic = ic / 32;
		}
		if (k % 100) {
			printf("%s(): %d current crossings\n", __func__, curcross);
			fflush(stdout);
		}
		/* some way to prevent endless long layout time */
		if (prevcross == 0) {
			prevcross = curcross;
		} else {
			if (curcross == prevcross) {
				if (wcross == 0) {
					wcross = curcross;
				} else {
					if (wcross == curcross) {
						break;
					} else {
						wcross = 0;
					}
				}
			}
			if ((prevcross - curcross) < ic16) {
				break;
			}
			prevcross = curcross;
		}

		/* from top to bottom */
		for (j = 1; j < gmaxlevel; j++) {
			mediansort(g, sugidata[j - 1], sugidata[j]);
		}

		curcross = check0(g);
		if (curcross == 0) {
			/* no edge crossings */
			break;
		}
		/* from bottom to top */
		for (j = gmaxlevel; j > 0; j--) {
			mediansort(g, sugidata[j], sugidata[j - 1]);
		}
		curcross = check0(g);
		if (curcross == 0) {
			/* no edge crossings */
			break;
		}

	}

	printf("%s(): %d final   crossings\n", __func__, curcross);
	fflush(stdout);

	/* copy new node positions */
	for (i = 0; i < gnlevels; i++) {
		count = 0;
		/* scan nodes at level [i] */
		for (j = 0; j < nglevelnodes[i]; j++) {
			/* extra check, must be same */
			if (count != sugidata[i][j].pos) {
				printf("%s(): at level %d pos %d found pos %d\n", __func__, i, count, sugidata[i][j].pos);
			}
			/* find the node with this id */
			n = uniqnode2(g, sugidata[i][j].id);
			if (n) {
				if (sugidata[i][j].level == n->rely) {
					/* oke and set node rel. x pos */
					n->relx = sugidata[i][j].pos;
				} else {
					/* shpuldnothappen */
					printf("%s(): node %d moved from level %d to level %d\n", __func__, n->nr, n->rely,
					       sugidata[i][j].level);
				}
			} else {
				/* shpuldnothappen */
				printf("%s(): node id %d not found\n", __func__, sugidata[i][j].id);
			}
			count++;
		}
	}

	/* clear data */
	clr_data(g);

	fflush(stdout);

	return;
}

void reduce_crossings4(struct gml_graph *g, int it1v, int it2v)
{
	int i = 0;
	int tsum = 0;

	/* number of crossing edges at level */
	if (g->numce == NULL) {
		g->numce = (int *)calloc(1, (g->maxlevel + 1) * sizeof(int));
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
	       g->nedges, g->maxlevel + 1);
	fflush(stdout);

	if (g->nnodes < 2) {
		/* only 1 node, not much todo */
		return;
	}

	if (g->nedges < 2) {
		/* only 1 level, not much todo */
		return;
	}

	barycenter_4(g, it1v, it2v);

	/* calc total number of crossings */
	for (i = 0; i < g->maxlevel; i++) {
		tsum += g->numce[i];
	}

	/* sugiyama final crossings */
	g->sugi_fcrossings = tsum;

	/* sugiyama changes made (not determined) */
	g->sugi_changes = 0;

	/* sugiyama initial crossings (not determined) */
	g->sugi_icrossings = 0;

	return;
}

/* end */
