
/*
 *  Copyright 2021
 *  (C) Universitaet Passau 1986-1991 (34 year old c-source)
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

/* this is a re-work of 1 file part of graphlet program */

/* graphviz dot does layout in multiple steps of parts of the graph
 * todo this is prepared for similar task but need more updates.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>		/* for CHAR_BIT is 8 definition */

#include "main.h"
#include "hier.h"
#include "uniqnode.h"
#include "sugi.h"
#include "dpmem.h"

struct mmatrix {
	int level;		/* upper level */
	int nrows;		/* nr. of rows (in upper level) */
	int ncols;		/* nr. of cols (in level+1) */
	int nbytes;		/* bytes used for matrix */
	int *mi0;		/* row node id's level i */
	int nmi0;		/* how many byte's in mi0 */
	int *m0i;		/* col node id's level (i+1) */
	int nm0i;		/* how many bytes in m0i */
	int bbytes;		/* bytes for double barycenter values */
	double *b;		/* buffer barycenter values */
	unsigned char *bits;	/* matrix bits */
};

static inline void setbit(unsigned char a[], int k)
{
	if (k == 0) {
		printf("setbit(0)\n");
		fflush(stdout);
	} else {
		a[k / CHAR_BIT] |= (1 << (k % CHAR_BIT));
	}
	return;
}

static inline void clearbit(unsigned char a[], int k)
{
	if (k == 0) {
		printf("clearbit(0)\n");
		fflush(stdout);
	} else {
		a[k / CHAR_BIT] &= ~(1 << (k % CHAR_BIT));
	}
	return;
}

static inline int testbit(struct mmatrix *m, unsigned char a[], int k)
{
	int ret = 0;
	unsigned int mask = 0;
	unsigned int mask2 = 0;
	unsigned int i = 0;

	if (k == 0) {
		printf("testbit(0)\n");
		fflush(stdout);
	}

	/* todo here tofix */
	if (k > ((m->ncols + 1) * (m->nrows + 1))) {
		printf("%s(): k=%d max is %d\n", __func__, k, ((m->ncols + 1) * (m->nrows + 1)));
	}

	/* compiler issue: the use of << is undefined here */
	/* issue CHAR_BIT is often 8 but does not have to be 8 */
	mask = (k % CHAR_BIT);

	/*old:  mask2 = (1 << mask); */
	mask2 = 1;
	for (i = 0; i < mask; i++) {
		mask2 = (mask2 * 2);
	}
	ret = ((a[k / CHAR_BIT]) & mask2);
	/*old  return ((a[k / CHAR_BIT] & (1 << (k % CHAR_BIT))) != 0); */
	return (ret);
}

/* i cols, j rows */
static inline int mget(struct mmatrix *m, int i, int j)
{
	return (testbit(m, m->bits, ((i * (m->ncols + 0)) + j)));
}

/* i is the from-node, j is the to-node, value is 1 for edge, otherwise 0 */
static inline void mget_set(struct mmatrix *m, int i, int j, int value)
{
	if (value) {
		setbit(m->bits, ((i * (m->ncols + 0)) + j));
	} else {
		clearbit(m->bits, ((i * (m->ncols + 0)) + j));
	}
	return;
}

static int number_of_crossings2(struct mmatrix *m, int r, int c)
{
	int j = 0;
	int k = 0;
	int alpha = 0;
	int beta = 1;
	int result = 0;

	for (j = 1; j <= r - 1; j++) {
		for (k = j + 1; k <= r; k++) {
			for (alpha = 1; alpha <= c - 1; alpha++) {
				for (beta = alpha + 1; beta <= c; beta++) {
					/* here 1*0=0, 0*1=0, 0*0=0 or 1*1=1 */
					result = result + ((mget(m, j, beta) * mget(m, k, alpha)));
				}
			}
		}
	}
	return (result);
}

/*
 * crossings
 * computes the number of crossings
 * algorithm:
 * matrix[i][j] represents the number of edges between position i on the upper
 * level and position j on the lower level, call it (i,j).
 * The edges crossing edge (i,j) from right to left are exactly those
 * edges (k,l) with k > i and l < j. You get the number of those edges
 * by adding all elements of the submatrix[k][l] with k > i and l < j.
 * The product of the elements of the submatrix and m[i][j] yields the
 * number of crossings.
 * To compute all crossings you must iterate over all elements of the matrix.
 * This computation time is linear in the size of the matrix.
 */

static int number_of_crossings3(struct mmatrix *m, int r, int c)
{
	int j = 0;
	int k = 0;
	int alpha = 0;
	int beta = 1;
	int result2 = 0;

	if (0) {
		result2 = number_of_crossings2(m, r, c);
	}

	for (j = 1; j <= (r - 1); j++) {
		for (k = (j + 1); k <= r; k++) {
			for (alpha = 1; alpha <= (c - 1); alpha++) {

				/* */
				if (mget(m, k, alpha)) {
					for (beta = alpha + 1; beta <= c; beta++) {
						/* */
						if (mget(m, j, beta)) {
							result2++;
						}
					}
				}
				/* */

			}
		}
	}

	return (result2);
}

/* number of crossings in whole graph */
static int number_of_crossings_a(struct gml_graph *g, struct mmatrix **mm)
{
	int ktot = 0;
	int k = 0;
	int i = 0;

	for (i = 0; i < g->maxlevel; i++) {
		if (mm[i]) {
			k = number_of_crossings3(mm[i], mm[i]->nrows, mm[i]->ncols);
			/* save number of edge crossings at level */
			g->numce[i] = k;
			ktot = ktot + k;
		}
	}

	return (ktot);
}

/* configure matrix data for level l in the graph */
static void make_matrix(struct gml_graph *g, int l, struct mmatrix *m)
{
	struct gml_nlist *nl = NULL;
	struct gml_elist *el = NULL;
	int i = 0;
	int j = 0;
	int c = 0;
	int r = 0;

	/* add node numbers in the 0 position */

	nl = g->nodelist;

	while (nl) {
		/* if (level(n) == l) */
		if (nl->node->rely == l) {
			/* rows */
			i = nl->node->relx;
			m->mi0[i] = nl->node->nr;	/* uniq node number, not id */
		} else if (nl->node->rely == (l + 1)) {
			/* columns */
			j = nl->node->relx;
			m->m0i[j] = nl->node->nr;	/* uniq node number, not id */
		}
		nl = nl->next;
	}

	/* matrix bits config, first init then set bits. */
	r = m->nrows;
	c = m->ncols;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			mget_set(m, i, j, 0);
		}
	}

	nl = g->nodelist;

	while (nl) {
		/* if (level(n) == l) */
		if (nl->node->rely == l) {
			/* outgoing edges : for_sourcelist (n, e) */
			el = nl->node->outgoing_e;
			while (el) {
				/* skip the horizontal edges */
				if (el->edge->hedge == 0) {
					/* from-node rel. x pos */
					i = nl->node->relx;
					/* to-node rel. x pos */
					j = el->edge->to_node->relx;
					/* set this is edge */
					mget_set(m, i, j, 1);
				}
				el = el->next;
			}
		}
		nl = nl->next;
	}

	if (0) {
		printf("make_matrix(): initial matrix level %d (%dx%d)\n", m->level, m->nrows, m->ncols);
		fflush(stdout);

		printf("\nm->bits():\n");
		fflush(stdout);

		r = m->nrows;
		c = m->ncols;

		for (i = 1; i <= r; i++) {
			for (j = 1; j <= c; j++) {
				if (mget(m, i, j)) {
					printf("0");
				} else {
					printf("1");
				}
			}
			printf("\n");
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}

	return;
}

 /* find node with given id number */
static struct gml_node *su_find_node_with_number(struct gml_graph *g, int nr)
{
	if (g) {
	}
	/* NULL for the global database or g for local database */
	/* uniqnode2() is the work nodes db in nodelist */
	return (uniqnode2(NULL, nr));
}

static void store_new_positions(struct gml_graph *g, struct mmatrix *m, int l)
{
	struct gml_node *n = NULL;
	int i = 0;

	if (m == NULL) {
		return;
	}

	for (i = 1; i <= m->nrows; i++) {
		/* rows */
		n = su_find_node_with_number(g, m->mi0[i]);
		if (n) {
			if (0) {
				printf("node nr=%d from x=%d to x=%d y=%d\n", n->nr, n->relx, i, l);
			}
			/* offset is 1, make it into 0..n */
			n->relx = (i - 1);
		} else {
			printf("%s(): no node with nr=%d found (0)\n", __func__, m->mi0[i]);
		}
	}

	for (i = 1; i <= m->ncols; i++) {
		/* columns */
		n = su_find_node_with_number(g, m->m0i[i]);
		if (n) {
			if (0) {
				printf("node nr=%d from x=%d to x=%d y=%d\n", n->nr, n->relx, i, l + 1);
			}
			/* offset is 1, make it into 0..n */
			n->relx = (i - 1);
		} else {
			printf("%s(): no node with nr=%d found (1)\n", __func__, m->m0i[i]);
		}
	}

	return;
}

/* copy matrix m1 to m2 */
static void copy_m(struct mmatrix *m1, struct mmatrix *m2)
{
	if (m1 && m2) {
		m2->level = m1->level;	/* upper level */
		m2->nrows = m1->nrows;	/* nr. of rows (in upper level) */
		m2->ncols = m1->ncols;	/* nr. of cols (in level+1) */
		m2->nbytes = m1->nbytes;	/* bytes used for matrix */
		(void)memmove(m2->bits, m1->bits, m1->nbytes);	/* matrix bits */
		(void)memmove(m2->mi0, m1->mi0, m1->nmi0);	/* row node id's level i */
		m2->nmi0 = m1->nmi0;	/* how many byte's in mi0 */
		(void)memmove(m2->m0i, m1->m0i, m1->nm0i);	/* col node id's level (i+1) */
		m2->nm0i = m1->nm0i;	/* how many bytes in m0i */
		m2->bbytes = m1->bbytes;	/* bytes for double barycenter values */
		(void)memmove(m2->b, m1->b, m1->bbytes);	/* barycenter values */
	}
	return;
}

/* are m1,m2 equal? */
static int equal_m(struct mmatrix *m1, struct mmatrix *m2, int r, int c)
{
	int i = 0;
	int j = 0;

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (mget(m1, i, j) != mget(m2, i, j)) {
				return (0);	/* FALSE */
			}
		}
	}

	return (1);		/* TRUE */
}

/* is whole graph equal */
static int equal_a(struct gml_graph *g, struct mmatrix **mm1, struct mmatrix **mm2)
{
	int l = 0;

	if (mm1 == NULL || mm2 == NULL) {
		return (0);
	}

	for (l = 0; l < g->maxlevel; l++) {
		if (equal_m(mm1[l], mm2[l], mm1[l]->nrows /* old g->nnodes_of_level[l] */ ,
			    mm1[l]->ncols /* old g->nnodes_of_level[l + 1] */ ) ==
		    0 /* FALSE */ ) {
			return (0);	/* FALSE */
		}
	}

	return (1);		/* TRUE */
}

/* copy whole graph */
static inline void copy_a(struct gml_graph *g, struct mmatrix **mm1, struct mmatrix **mm2)
{
	int i = 0;

	for (i = 0; i < g->maxlevel; i++) {
		copy_m(mm1[i], mm2[i]);
	}

	return;
}

static void exch_rows(struct mmatrix *m, int r1, int r2)
{
	int j = 0;
	int id1 = 0;
	int id2 = 0;
	int bit1 = 0;
	int bit2 = 0;

	/*
	 * h = m[r1][j];
	 * m[r1][j] = m[r2][j];
	 * m[r2][j] = h;
	 */

	/* swap node id numbers */
	id1 = m->mi0[r1];
	id2 = m->mi0[r2];
	m->mi0[r1] = id2;
	m->mi0[r2] = id1;

	/* swap matrix bits */
	for (j = 1; j <= m->ncols; j++) {
		bit1 = mget(m, r1, j);
		bit2 = mget(m, r2, j);
		mget_set(m, r1, j, bit2);
		mget_set(m, r2, j, bit1);
	}

	return;
}

static void exch_columns(struct mmatrix *m, int c1, int c2)
{
	int i = 0;
	int id1 = 0;
	int id2 = 0;
	int bit1 = 0;
	int bit2 = 0;

	/*
	 * h = m[i][c1];
	 * m[i][c1] = m[i][c2];
	 * m[i][c2] = h;
	 */

	/* swap node id numbers */
	id1 = m->m0i[c1];
	id2 = m->m0i[c2];
	m->m0i[c1] = id2;
	m->m0i[c2] = id1;

	/* swap matrix bits */
	for (i = 1; i <= m->nrows; i++) {
		bit1 = mget(m, i, c1);
		bit2 = mget(m, i, c2);
		mget_set(m, i, c1, bit2);
		mget_set(m, i, c2, bit1);
	}

	return;
}

static int reverse_r(struct mmatrix *m, int r1, int r2)
{
	int i = 0;
	int j = 0;
	int ch = 0;

	for (i = r1, j = r2; i < j; i++, j--) {
		ch++;
		exch_rows(m, i, j);
	}

	return (ch);
}

static int reverse_c(struct mmatrix *m, int c1, int c2)
{
	int i = 0;
	int j = 0;
	int ch = 0;

	for (i = c1, j = c2; i < j; i++, j--) {
		ch++;
		exch_columns(m, i, j);
	}

	return (ch);
}

static double row_barycenter(struct mmatrix *m, int i, int maxval)
{
	int j = 0;
	int r1 = 0;		/* sum */
	int r2 = 0;		/* div */

	for (j = 1; j <= maxval; j++) {
		if (mget(m, i, j)) {
			r1 = r1 + j;
			r2++;
		}
	}

	if (r2 == 0) {
		return (0.0);
	} else {
		return ((double)r1 / (double)r2);
	}
}

static double column_barycenter(struct mmatrix *m, int j, int maxval)
{
	int i = 0;
	int r1 = 0;		/* sum */
	int r2 = 0;		/* div */

	for (i = 1; i <= maxval; i++) {
		if (mget(m, i, j)) {
			r1 = r1 + i;
			r2++;
		}
	}

	if (r2 == 0) {
		return (0.0);
	} else {
		return ((double)r1 / (double)r2);
	}
}

/* reverse rows */
static int r_r(struct mmatrix *m1, struct mmatrix *m2, int max_r, int max_c)
{
	int i = 0;
	int j = 0;
	int ch = 0;

	for (i = 1; i <= max_r; i++) {
		m1->b[i] = row_barycenter(m1, i, max_c);
	}

	for (i = 1; i < max_r; i++) {
		j = i;

		while ((j < max_r) && (m1->b[j + 1] == m1->b[j])) {
			j++;
		}

		if (j > i) {
			ch += reverse_r(m1, i, j);

			if (m2 != NULL) {
				ch += reverse_c(m2, i, j);
			}

			i = j;
		}

	}

	return (ch);
}

/* reverse columns */
static int r_c(struct mmatrix *m1, struct mmatrix *m2, int max_r, int max_c)
{
	int i = 0;
	int j = 0;
	int ch = 0;

	for (i = 1; i <= max_c; i++) {
		m1->b[i] = column_barycenter(m1, i, max_r);
	}

	for (i = 1; i < max_c; i++) {
		j = i;

		while ((j < max_c) && (m1->b[j + 1] == m1->b[j])) {
			j++;
		}

		if (j > i) {
			ch += reverse_c(m1, i, j);

			if (m2 != NULL) {
				ch += reverse_r(m2, i, j);
			}

			i = j;
		}

	}

	return (ch);
}

/* barycenter rows */
static int b_r(struct mmatrix *m1, struct mmatrix *m2, int max_r, int max_c)
{
	double tmpb = 0.0;
	int i = 0;
	int j = 0;
	int k = 0;
	int ch = 0;

	for (i = 1; i <= max_r; i++) {
		m1->b[i] = row_barycenter(m1, i, max_c);
	}

	for (j = max_r; j > 1; j--) {
		if (m1->b[j] != 0.0) {
			for (i = 1; i < j; i++) {
				if (m1->b[i] != 0.0) {
					k = i + 1;
					while (m1->b[k] == 0.0) {
						k++;
					}
					if (m1->b[i] > m1->b[k]) {
						ch++;
						/* exch_double */
						tmpb = m1->b[k];
						m1->b[k] = m1->b[i];
						m1->b[i] = tmpb;
						exch_rows(m1, i, k);
						if (m2 != NULL) {
							ch++;
							/* exchange cols from i to k */
							exch_columns(m2, i, k);
						}
					}
				}
			}
		}
	}

	return (ch);
}

/* barycenter cols */
static int b_c(struct mmatrix *m1, struct mmatrix *m2, int max_r, int max_c)
{
	double tmpb = 0.0;
	int i = 0;
	int j = 0;
	int k = 0;
	int ch = 0;

	for (i = 1; i <= max_c; i++) {
		m1->b[i] = column_barycenter(m1, i, max_r);
	}

	for (j = max_c; j > 1; j--) {
		if (m1->b[j] != 0.0) {
			for (i = 1; i < j; i++) {
				if (m1->b[i] != 0.0) {
					k = i + 1;

					while (m1->b[k] == 0.0) {
						k++;
					}

					if (m1->b[i] > m1->b[k]) {
						ch++;
						/* exch_double */
						tmpb = m1->b[k];
						m1->b[k] = m1->b[i];
						m1->b[i] = tmpb;
						/* exchange cols from i to k */
						exch_columns(m1, i, k);
						if (m2 != NULL) {
							ch++;
							exch_rows(m2, i, k);
						}
					}
				}
			}
		}
	}

	return (ch);
}

/* test if array is sorted, 1 if sorted from hight-to-low */
static int sorted(double *vector, int maxval)
{
	int i = 0;

	for (i = 1; i < maxval; i++) {
		/* but ignore 0.0 values */
		if ((vector[i] > vector[i + 1]) && (vector[i + 1] != 0.0)) {
			return (0);	/* FALSE */
		}
	}

	return (1);		/* TRUE */
}

static inline int phase1_down(struct gml_graph *g, struct mmatrix **mm)
{
	int i = 0;
	int ch = 0;

	/* from level0 down to level max */
	for (i = 0; i < g->maxlevel - 1; i++) {
		ch += b_c(mm[i], mm[i + 1], mm[i]->nrows, mm[i]->ncols);
	}

	ch += b_c(mm[g->maxlevel - 1], NULL, mm[g->maxlevel - 1]->nrows, mm[g->maxlevel - 1]->ncols);

	return (ch);
}

static inline int phase1_up(struct gml_graph *g, struct mmatrix **mm)
{
	int i = 0;
	int ch = 0;

	if (mm == NULL) {
		return (0);
	}

	/* from level max up to level0 */
	for (i = (g->maxlevel - 1); i > 0; i--) {
		ch += b_r(mm[i], mm[i - 1], mm[i]->nrows /* old g->nnodes_of_level[i] */ ,
			  mm[i]->ncols /* old g->nnodes_of_level[i + 1] */ );
	}

	ch += b_r(mm[0], NULL, mm[0]->nrows /* g->nnodes_of_level[0] */ ,
		  mm[0]->ncols /* g->nnodes_of_level[1] */ );

	return (ch);
}

/* */
static inline int phase2_down(struct gml_graph *g, struct mmatrix **mm)
{
	int l = 0;		/* Level */
	int i = 0;
	int ch = 0;

	for (l = 0; l < (g->maxlevel - 1); l++) {

		for (i = 1; i <= mm[l]->ncols /* g->nnodes_of_level[l + 1] */ ; i++) {
			mm[l]->b[i] = column_barycenter(mm[l], i, mm[l]->nrows /* g->nnodes_of_level[l] */ );
		}

		if (sorted(mm[l]->b, mm[l]->ncols /* g->nnodes_of_level[l + 1] */ ) ==
		    1 /* TRUE */ ) {
			/* reverse columns */
			ch += r_c(mm[l], mm[l + 1], mm[l]->nrows /* g->nnodes_of_level[l] */ ,
				  mm[l]->ncols /* g->nnodes_of_level[l + 1] */ );
		} else {
			return (ch);
		}

	}

	for (i = 1; i <= g->nnodes_of_level[g->maxlevel]; i++) {
		mm[g->maxlevel - 1]->b[i] = column_barycenter(mm[g->maxlevel - 1], i, mm[g->maxlevel - 1]->nrows
							      /* g->nnodes_of_level[g->maxlevel - 1] */ );
	}

	if (sorted(mm[g->maxlevel - 1]->b, mm[g->maxlevel - 1]->ncols /* g->nnodes_of_level[g->maxlevel] */ ) ==
	    1 /* TRUE */ ) {
		/* reverse columns */
		ch += r_c(mm[g->maxlevel - 1], NULL, mm[g->maxlevel - 1]->nrows /* g->nnodes_of_level[g->maxlevel - 1] */ ,
			  mm[g->maxlevel - 1]->ncols /* g->nnodes_of_level[g->maxlevel] */ );
	}

	return (ch);
}

/* */
static inline int phase2_up(struct gml_graph *g, struct mmatrix **mm)
{
	int l = 0;		/* Level */
	int i = 0;
	int ch = 0;

	if (g) {
	}

	for (l = (g->maxlevel - 1); l > 0; l--) {

		for (i = 1; i <= /* g->nnodes_of_level[l] */ mm[l]->nrows; i++) {
			mm[l]->b[i] = row_barycenter(mm[l], i,	/* g->nnodes_of_level[l + 1] */
						     mm[l]->ncols);
		}

		if (sorted(mm[l]->b, /* g->nnodes_of_level[l] */ mm[l]->nrows) ==
		    1 /* TRUE */ ) {
			/* reverse rows */
			ch += r_r(mm[l], mm[l - 1], mm[l]->nrows /* g->nnodes_of_level[l] */ ,
				  mm[l]->ncols /* g->nnodes_of_level[l + 1] */ );
		} else {
			return (ch);
		}

	}

	for (i = 1; i <= mm[0]->nrows /* g->nnodes_of_level[0] */ ; i++) {
		mm[0]->b[i] = row_barycenter(mm[0], i, mm[0]->ncols /* g->nodes_of_level[1] */ );
	}

	/* if level0 is sorted, r_r */
	if (sorted(mm[0]->b, mm[0]->nrows /* g->nnodes_of_level[0] */ ) ==
	    1 /* TRUE */ ) {
		/* reverse rows */
		ch += r_r(mm[0], NULL, mm[0]->nrows /* g->nnodes_of_level[0] */ ,
			  mm[0]->ncols /* g->nnodes_of_level[1] */ );
	}

	return (ch);
}

/* convert large number to easier human string */
static const char *humansize(int bytes)
{
	static char output[200];
	char *suffix[] = { "", "K", "M", "G", "T" };
	char length = sizeof(suffix) / sizeof(suffix[0]);
	int i = 0;
	double dblbytes = bytes;

	if (bytes > 1000) {
		for (i = 0; (bytes / 1000) > 0 && i < length - 1; i++, bytes /= 1000)
			dblbytes = bytes / 1000.0;
	}

	memset(output, 0, 200);
	snprintf(output, (200 - 1), "%.01lf %s", dblbytes, suffix[i]);

	return output;
}

/* here if maxlevel >1 */
static void bc_n(struct gml_graph *g, int it1value, int it2value)
{
	char charbuffer[64];
	struct mmatrix **a = NULL;
	struct mmatrix **a1 = NULL;
	struct mmatrix **a2 = NULL;
	struct mmatrix **as = NULL;
	int i = 0;
	int ks = 0;
	int k = 0;
	int n1 = 0;
	int n2 = 0;
	int cht = 0;
	int ch1 = 0;
	int ch2 = 0;
	int r1 = 0;
	int r2 = 0;
	int r3 = 0;
	int rr1 = 0;
	int rr2 = 0;
	int rr3 = 0;
	int it1 = 20;		/* iterations phase1 */
	int it2 = 40;		/* iterations pahse2 */

	if (it1value == 0) {
		it1 = 20;
	} else {
		it1 = it1value;
	}

	if (it2value == 0) {
		it2 = 40;
	} else {
		it2 = it2value;
	}

	/* the whole graph structures */
	a = dp_calloc(1, g->maxlevel * sizeof(struct mmatrix *));
	a1 = dp_calloc(1, g->maxlevel * sizeof(struct mmatrix *));
	a2 = dp_calloc(1, g->maxlevel * sizeof(struct mmatrix *));
	as = dp_calloc(1, g->maxlevel * sizeof(struct mmatrix *));

	/* get matrix struct */
	for (i = 0; i < g->maxlevel; i++) {
		a[i] = dp_calloc(1, sizeof(struct mmatrix));
		a1[i] = dp_calloc(1, sizeof(struct mmatrix));
		a2[i] = dp_calloc(1, sizeof(struct mmatrix));
		as[i] = dp_calloc(1, sizeof(struct mmatrix));
	}

	/* get data inside struct */
	for (i = 0; i < g->maxlevel; i++) {
		/* upper level */
		a[i]->level = i;
		a1[i]->level = i;
		a2[i]->level = i;
		as[i]->level = i;

		/* number of rows */
		a[i]->nrows = g->nnodes_of_level[i];
		a1[i]->nrows = g->nnodes_of_level[i];
		a2[i]->nrows = g->nnodes_of_level[i];
		as[i]->nrows = g->nnodes_of_level[i];

		/* number of columns */
		a[i]->ncols = g->nnodes_of_level[i + 1];
		a1[i]->ncols = g->nnodes_of_level[i + 1];
		a2[i]->ncols = g->nnodes_of_level[i + 1];
		as[i]->ncols = g->nnodes_of_level[i + 1];

		/* buffer for barycenter values */
		if (a[i]->nrows > a[i]->ncols) {
			a[i]->bbytes = ((a[i]->nrows + 1) * sizeof(double));
			a1[i]->bbytes = ((a1[i]->nrows + 1) * sizeof(double));
			a2[i]->bbytes = ((a2[i]->nrows + 1) * sizeof(double));
			as[i]->bbytes = ((as[i]->nrows + 1) * sizeof(double));
		} else {
			a[i]->bbytes = ((a[i]->ncols + 1) * sizeof(double));
			a1[i]->bbytes = ((a1[i]->ncols + 1) * sizeof(double));
			a2[i]->bbytes = ((a2[i]->ncols + 1) * sizeof(double));
			as[i]->bbytes = ((as[i]->ncols + 1) * sizeof(double));
		}

		a[i]->b = dp_calloc(1, a[i]->bbytes);
		a1[i]->b = dp_calloc(1, a1[i]->bbytes);
		a2[i]->b = dp_calloc(1, a2[i]->bbytes);
		as[i]->b = dp_calloc(1, as[i]->bbytes);

		/* number of bytes used */
		a[i]->nmi0 = ((a[i]->nrows + 1) * sizeof(int));
		a1[i]->nmi0 = ((a[i]->nrows + 1) * sizeof(int));
		a2[i]->nmi0 = ((a[i]->nrows + 1) * sizeof(int));
		as[i]->nmi0 = ((a[i]->nrows + 1) * sizeof(int));

		/* row node id's (int's) */
		a[i]->mi0 = dp_calloc(1, a[i]->nmi0);
		a1[i]->mi0 = dp_calloc(1, a1[i]->nmi0);
		a2[i]->mi0 = dp_calloc(1, a2[i]->nmi0);
		as[i]->mi0 = dp_calloc(1, as[i]->nmi0);

		/* number of bytes used */
		a[i]->nm0i = ((a[i]->ncols + 1) * sizeof(int));
		a1[i]->nm0i = ((a[i]->ncols + 1) * sizeof(int));
		a2[i]->nm0i = ((a[i]->ncols + 1) * sizeof(int));
		as[i]->nm0i = ((a[i]->ncols + 1) * sizeof(int));

		/* col node id's (int's) */
		a[i]->m0i = dp_calloc(1, a[i]->nm0i);
		a1[i]->m0i = dp_calloc(1, a1[i]->nm0i);
		a2[i]->m0i = dp_calloc(1, a2[i]->nm0i);
		as[i]->m0i = dp_calloc(1, as[i]->nm0i);

		/* bits array for the matrix */
		a[i]->nbytes = 1 + ((((a[i]->nrows + 1) * (a[i]->ncols + 1)) + CHAR_BIT) / CHAR_BIT);
		a1[i]->nbytes = 1 + ((((a1[i]->nrows + 1) * (a1[i]->ncols + 1)) + CHAR_BIT) / CHAR_BIT);
		a2[i]->nbytes = 1 + ((((a2[i]->nrows + 1) * (a2[i]->ncols + 1)) + CHAR_BIT) / CHAR_BIT);
		as[i]->nbytes = 1 + ((((as[i]->nrows + 1) * (as[i]->ncols + 1)) + CHAR_BIT) / CHAR_BIT);

		a[i]->bits = dp_calloc(1, a[i]->nbytes);
		a1[i]->bits = dp_calloc(1, a1[i]->nbytes);
		a2[i]->bits = dp_calloc(1, a2[i]->nbytes);
		as[i]->bits = dp_calloc(1, as[i]->nbytes);
	}

	/* fill the matrix with data for all levels */
	for (i = 0; i < g->maxlevel; i++) {
		make_matrix(g, i, a[i]);
	}

	copy_a(g, a, as);
	ks = number_of_crossings_a(g, as);

	printf("bc_n(++): initial crossings is %d\n", ks);
	fflush(stdout);

	/* update status text line */
	memset(charbuffer, 0, 64);
	snprintf(charbuffer, (64 - 1), "initial crossings is %d", ks);
	update_status_text_cross(charbuffer);

	g->sugi_icrossings = ks;	/* sugiyama initial crossings */

	if (ks > 0) {

		/* Phase1 */
		ch1 = 0;

		/* first does alwasy improve */
		ch1 += phase1_down(g, a);
		copy_a(g, a, as);
		ch1 += phase1_up(g, a);
		copy_a(g, a, as);

		/* loop phase1 */
		n1 = 0;
		do {

			copy_a(g, a, a1);

			ch1 += phase1_down(g, a);
			k = number_of_crossings_a(g, a);

			if (k < ks) {
				/* reduced crossings, save the new state */
				ks = k;
				copy_a(g, a, as);
			}

			ch1 += phase1_up(g, a);

			k = number_of_crossings_a(g, a);

			if (k < ks) {
				ks = k;
				copy_a(g, a, as);

			}
			cht += ch1;

			printf("bc_n(++): current crossings phase1 is %d (%d:%d) ch1=%d cht=%d\n", ks, n1, n2, ch1, cht);
			fflush(stdout);

			/* update status text line */
			memset(charbuffer, 0, 64);
			snprintf(charbuffer, (64 - 1), "phase 1 crossings is now %d", ks);
			update_status_text_cross(charbuffer);

			if (ks == 0) {
				break;
			}

			/* check if number of crossings changed */
			r1 = r2;
			r2 = r3;
			r3 = ks;
			if (r1 == r2) {
				if (r2 == r3) {
					break;
				}
			}

		}
		while (++n1 < it1 && (equal_a(g, a, a1) == 0 /* FALSE */ ));

		/* if matrices differ, save state */
		if (equal_a(g, a, as) == 0 /* FALSE */ ) {
			copy_a(g, as, a);
		}

		if (ks > 0) {
			/* Phase2 */
			n2 = 0;
			cht += ch1;

			do {
				ch2 = 0;

				copy_a(g, a, a2);
				ch2 += phase2_down(g, a);
				n1 = 0;

				do {
					ch1 = 0;
					copy_a(g, a, a1);
					ch1 += phase1_down(g, a);
					k = number_of_crossings_a(g, a);
					if (k < ks) {
						ks = k;
						copy_a(g, a, as);
					}

					ch1 += phase1_up(g, a);
					k = number_of_crossings_a(g, a);
					if (k < ks) {
						ks = k;
						copy_a(g, a, as);
					}

					if (ks == 0) {
						break;
					}

					/* check if number of crossings changed */
					rr1 = rr2;
					rr2 = rr3;
					rr3 = ks;
					if (rr1 == rr2) {
						if (rr2 == rr3) {
							break;
						}
					}

				}
				while (++n1 < it1 && equal_a(g, a, a1) == 0 /* FALSE */ );

				ch2 += phase2_up(g, a);

				n1 = 0;
				do {
					copy_a(g, a, a1);
					ch1 += phase1_up(g, a);
					k = number_of_crossings_a(g, a);
					if (k < ks) {
						ks = k;
						copy_a(g, a, as);
					}

					ch1 += phase1_down(g, a);
					k = number_of_crossings_a(g, a);
					if (k < ks) {
						ks = k;
						copy_a(g, a, as);
					}

					cht += ch1;

					printf
					    ("bc_n(++): current crossings phase2 is %d (%d:%d) ch1=%d ch2=%d cht=%d\n",
					     ks, n1, n2, ch1, ch2, cht);
					fflush(stdout);

					/* update status text line */
					memset(charbuffer, 0, 64);
					snprintf(charbuffer, (64 - 1), "phase 2 crossings is now %d", ks);
					update_status_text_cross(charbuffer);

					if (ks == 0) {
						break;
					}

					/* check if number of crossings changed */
					rr1 = rr2;
					rr2 = rr3;
					rr3 = ks;
					if (rr1 == rr2) {
						if (rr2 == rr3) {
							break;
						}
					}

				}
				while (++n1 < it1 && equal_a(g, a, a1) == 0 /* FALSE */ );

				cht += ch1;
				cht += ch2;

				if (ks == 0) {
					break;
				}

				/* check if number of crossings changed */
				r1 = r2;
				r2 = r3;
				r3 = ks;
				if (r1 == r2) {
					if (r2 == r3) {
						break;
					}
				}

			}
			while (++n2 < it2 && equal_a(g, a, a2) == 0 /* FALSE */ );
		}
	}

	/* sugiyama final crossings */
	g->sugi_fcrossings = ks;

	/* sugiyama changes made */
	g->sugi_changes = cht;

	printf("bc_n(++): final crossings is %d after %d (%s) changes made\n", ks, cht, humansize(cht));
	fflush(stdout);

	/* update status text line */
	memset(charbuffer, 0, 64);
	snprintf(charbuffer, (64 - 1), "final crossings is now %d", ks);
	update_status_text_cross(charbuffer);

	for (i = 0; i < g->maxlevel; i += 2) {
		/* set new node positions for 2 levels */
		store_new_positions(g, as[i], i);
	}

	if (i == g->maxlevel) {
		store_new_positions(g, as[g->maxlevel - 1], (g->maxlevel - 1));
	}

	for (i = 0; i < g->maxlevel; i++) {
		if (a[i]) {
			a[i]->b = dp_free(a[i]->b);
			if (a[i]->b) {
			}
			a[i]->mi0 = dp_free(a[i]->mi0);
			if (a[i]->mi0) {
			}
			a[i]->m0i = dp_free(a[i]->m0i);
			if (a[i]->m0i) {
			}
			a[i]->bits = dp_free(a[i]->bits);
			if (a[i]->bits) {
			}
		}
		if (a1[i]) {
			a1[i]->b = dp_free(a1[i]->b);
			if (a1[i]->b) {
			}
			a1[i]->mi0 = dp_free(a1[i]->mi0);
			if (a1[i]->mi0) {
			}
			a1[i]->m0i = dp_free(a1[i]->m0i);
			if (a1[i]->m0i) {
			}
			a1[i]->bits = dp_free(a1[i]->bits);
			if (a1[i]->bits) {
			}
		}
		if (a2[i]) {
			a2[i]->b = dp_free(a2[i]->b);
			if (a2[i]->b) {
			}
			a2[i]->mi0 = dp_free(a2[i]->mi0);
			if (a2[i]->mi0) {
			}
			a2[i]->m0i = dp_free(a2[i]->m0i);
			if (a2[i]->m0i) {
			}
			a2[i]->bits = dp_free(a2[i]->bits);
			if (a2[i]->bits) {
			}
		}
		if (as[i]) {
			as[i]->b = dp_free(as[i]->b);
			if (as[i]->b) {
			}
			as[i]->mi0 = dp_free(as[i]->mi0);
			if (as[i]->mi0) {
			}
			as[i]->m0i = dp_free(as[i]->m0i);
			if (as[i]->m0i) {
			}
			as[i]->bits = dp_free(as[i]->bits);
			if (as[i]->bits) {
			}
		}
	}

	for (i = 0; i < g->maxlevel; i++) {
		a[i] = dp_free(a[i]);
		if (a[i]) {
		}
		a1[i] = dp_free(a1[i]);
		if (a1[i]) {
		}
		a2[i] = dp_free(a2[i]);
		if (a2[i]) {
		}
		as[i] = dp_free(as[i]);
		if (as[i]) {
		}
	}

	a = dp_free(a);
	if (a) {
	}
	a1 = dp_free(a1);
	if (a1) {
	}
	a2 = dp_free(a2);
	if (a2) {
	}
	as = dp_free(as);
	if (as) {
	}

	return;
}

/*
This algorithm is for routing hierarchies of elements.  A "good route" is
one that has a minimum number of link crossings.  An algorithm that was
truly optimal (for minimizing link crossings) would be combinatorial and
therefore cost prohibitive; therefore, this algorithm uses a heuristic
approach that finds a route with close to the minimum number of crossings
in a reasonable amount of time.

This algorithm assumes that all the elements form a directed acyclic graph
(DAG), which means (1) that links flow one way between elements and (2) for
any given node there is no way to get back to the node if, starting at the
node, you traverse the links going from node to node.  This algorithm also
assumes that AT MOST only ONE link may exist between a pair of nodes.

-------------------------------------------------------------------------------

OVERVIEW OF ALGORITHM

All elements that do not have any parents are placed in the first row (row 0).
Elements are assigned to rows, where the row number for each child is equal to
the [maximum(row number of all its parents) + 1].  Crossovers are determined
by examining links between elements on adjacent rows, so if a parent is in a
row that is not adjacent to its child's row, "dummy" nodes are created on the
rows in between the parent and child, and the parent and child are connected
via these dummy nodes.

Once the elements (now called nodes) are assigned to individual rows, the
rows are sorted (repeatedly) in order to minimize link crossings.  The
sort criteria involves attempting to both center children under parents and
to center parents over children.  The sort orders are then tweaked by swapping
nodes that have the same sort value.

After the column orders are finalized, the nodes are spread out so they are
more or less centered above their children and below their parents.  When
centering children below parents, a row of children is sorted by which node
has the greatest number of parents.  These get first choice of where to be
placed under the parents (actually, dummy nodes get first preference, then
all of the others).  Centering parents above children is analogous.

When done with node placement, there may be some empty columns, and the
numbering scheme may not start at 0.  Therefore, the empty columns must
be eliminated and every node needs its column renumbered, starting at 0.

Then you are done.

-------------------------------------------------------------------------------

REALIZATION MATRIX

When it comes to both sorting nodes and horizontally spacing the nodes, two
adjacent rows are always involved.  For example, if we are sorting row[i]
based on the children of row[i]'s nodes, then row[i+1] is also involved
at this step.  These two rows are called the "i-th realization", and form
the "i-th realization matrix".  A realization matrix shows the parent-child
relationships between adjacent rows, with the parents on the rows and the
children on the columns.  If there is a parent-child relationship, a 1 is
stored in the matrix at the position, else a 0 is stored.

An example:

                            A     B     C  D
                            \ \  / \  / /  |
                             \ /\  / \ /   |
                             /\ / \  / \   |
                            / /\   /\    \ |
                           //   \ /   \   \|
                          E      F     G   H

   E  F  G  H
A  0  1  1  0    In this example, parent 'A' has children 'F' and 'G',
B  1  0  0  1                     parent 'B' has children 'E' and 'H',
C  1  1  0  0                     parent 'C' has children 'E' and 'F',
D  0  0  0  1                 and parent 'D' has child 'H'.

-------------------------------------------------------------------------------

ROW AND COLUMN BARYCENTERS

Two other important concepts are the "row barycenter" and the "column
barycenter" for a node.  The "row barycenter" is the basically the average
of the positions of a node's children.  The "column barycenter" is the average
of the positions of a node's parents.  These numbers tell us where a node
would like to be positioned in its row, depending whether we are positioning
relative to children or parents.

For example, using the above realization matrix, we can calculate the row
barycenters for A, B, C, and D, and the column barycenters for E, F, G, and H.
Since the row barycenter of a node is equal to the sum of the positions of
the node's children divided by the number of children of the node, the row
barycenter for A is (1 + 2)/2 = 1.5.  This assumes that we start numbering
rows and columns at 0.  Similarly, the column barycenter of a node is equal
to the sum of the positions of the node's parents divided by the number of
parents of the node.  So, the column barycenter of F is (0 + 2)/2 = 1.0.
The complete example is as follows:

                             Row
      |  E    F    G    H  | Barys
------+--------------------+-----
A     |  0    1    1    0  | 1.5
B     |  1    0    0    1  | 1.5
C     |  1    1    0    0  | 0.5
D     |  0    0    0    1  | 3.0
------+--------------------+-----
Col   | 1.5  1.0  0.0  2.0 |
Barys |                    |

If we were to sort the child nodes here by their column barycenters, the new
order would be G, F, E, H.  If we were to sort the parent nodes here by their
row barycenters, then the order would be C, A, B, D (if two or more nodes have
the same value, be sure to keep the same precedence that already exists
between them, e.g., make sure that order after sorting is not C, B, A, D).

If a node has no parents then it can't have a column barycenter.  This case
should never happen, as all nodes that have no parents should be in the first
level of the hierarchy, and these nodes would only be represented in
realization matrix 0, and they would only have row barycenters.

If a node has no children then it can't have a row barycenter.  In this case,
while sorting based on row barycenters, sort AROUND these nodes, i.e., do
not change their positions at all.  For example, if we had the following:

                             Row
      |  W    X    Y    Z  | Barys
------+--------------------+-----
Q     |  0    1    1    1  | 2.0
R     |  0    0    0    0  | ???
S     |  1    0    0    0  | 0.0
T     |  0    1    0    1  | 2.0
------+--------------------+-----
Col   | 2.0  1.5  0.0  1.5 |
Barys |                    |

and we were to sort by row barycenters, the resulting order should be S, R,
Q, T.  Notice how R stayed in its position, and even though Q and T had the
same barycentric value, Q stayed before T.

The whole reason for sorting rows and columns by their barycenters is to
decrease the number of crossovers.

-------------------------------------------------------------------------------

CROSSOVERS

The realization matrix is also used to count the number of crossovers between
two adjacent rows of nodes.  For each row, starting with the second row, if
a row element has a 1, then sum up all of the matrix elements that are above
AND to the right of this element.  Looking again at the first example:

                            A     B     C  D
                            \ \  / \  / /  |
                             \ /\  / \ /   |
                             /\ / \  / \   |
                            / /\   /\    \ |
                           //   \ /   \   \|
                          E      F     G   H

                             Row
      |  E    F    G    H  | Barys
------+--------------------+-----
A     |  0    1    1    0  | 1.5
B     |  1    0    0    1  | 1.5
C     |  1    1    0    0  | 0.5
D     |  0    0    0    1  | 3.0
------+--------------------+-----
Col   | 1.5  1.0  0.0  2.0 |
Barys |                    |

Starting with the second row (parent B's row), position B-E has a 1.  Looking
at positions above and to the right, we see positions A-F and A-G both have
a 1, so the number of crossovers is currently = 2.  Position B-H has a 1, but
there are no elements above and to the right, so crossovers is still = 2.
For parent row of C, position C-E crosses over with B-H, A-F, and A-G, so
crossovers = 5.  C-F crosses over with B-H and A-G, so crossovers = 7.  For
parent row D, position D-H doesn't cross over with any other link.  So for
this realization matrix representing these two rows, the number of crossovers
is 7.

The total number of crossovers for the whole graph would be the sum of the
crossovers from each matrix realization.

-------------------------------------------------------------------------------

NODE CENTERING

After the nodes for each row have their final sort order, the nodes need to
be assigned to grid positions.  Their initial grid position will be their
column position, by which we mean their array position in the row.  From now
on, when we take a row or column barycenter, we will be using grid positions
instead of column positions.

Note:  The following examples will be based on centering children with respect
to their parents' positions.  Centering parents based on their children's
positions is analogous.

When positioning the nodes on a row based on their parents' positions, the
nodes must be initially sorted to see which nodes get first choice.  The dummy
nodes go first, and the rest of nodes are sorted in descending order based on
the number of parents the node has.  If a dummy node has a parent that has
multiple dummy nodes, all of these dummy nodes are again sorted by how close
to the center of the parent's children they are.  This is a confusing
statement, best illustrated by example:

            P1              P2
             \              |
               \  __________^__________
                 \|    |    |    |    |
                  C1   D1   D2   C2   D3

Here, parent P1 has one child, C1.  Parent P2 has five children, and three of
the child nodes are dummy nodes: D1, D2, and D3.  C1 is child 0 of P2, D1 is
child 1 of P2, D2 is child 2 of P2, C2 is child 3 of P2, and D3 is child 4 of
P2.  The child midpoint underneath the parent is equal to
(the number of children - 1) / 2, so (5 - 1) / 2 = 2.  Since the dummy nodes
go first, the initial order is D1, D2, D3, C1 (because it has 2 parents), and
finally C2.  All of the dummy nodes have the same parent, so we will sort them
based on how far away they are from the parent's child midpoint.  D1 is child
1 of P2, so it is 1 away.  D2 is child 2 of P2, so it is 0 away.  D3 is child
4 of P2, so it is 2 away.  Therefore, the final order for choosing positions
is D2, D1, D3, C1, C2.

In a situation similar to the dummy nodes, if a non-dummy node has a only one
parent, and that parent has other children with just one parent, then these
one parent child nodes that have the same parent need additional sorting in
the exact same manner that we just did the dummy nodes.

The whole purpose behind this is so that the left most node doesn't get first
choice.  If it did, we would get graphs that look like:

                 A                                     A
                 |                                     |
                 |_________       instead of      _____^_____
                 |    |    |                      |    |    |
                 B    C    D                      B    C    D

Anyway, once we have a sort order for the nodes of a row, we place the nodes
in their preferred positions.  Using the previous example, assume that P1
is in grid position 2 and P2 is in grid position 5.  D2 gets first choice,
and its column barycenter (based now on parent grid positions, not column
positions) is 5, so we place D2 in position 5.  D1 is next, its barycenter
is also 5.  We can't give it 5 since that position is occupied, so we give
it the closest possible position we can, which in this case is 4.  D3 is next,
and its barycenter is also 5.  The closest position that we can give it is
position 7, since we must allow room for C2.  C1 is next, and its barycenter
is (2 + 5)/2 = 3.5, which we round to 3.  Position 3 is open, so we go ahead
and give it position 3.  C2 is last, and its barycenter is 5.  However, the
first position available to it based on its left neighbor is position 6, so
we assign it position 6.

-------------------------------------------------------------------------------

GOING 'UP' OR 'DOWN' THE GRAPH

"Going down the graph" means taking each realization matrix situation,
starting with Realization Matrix 0, and performing some action on it, then
going to the next realization matrix, and continuing until all of the
realization matrices have been visited.

"Going up the graph" is analogous, except you start at the bottom with the
last realization matrix and work up to Realization Matrix 0.
*/

void reduce_crossings2(struct gml_graph *g, int it1v, int it2v)
{

	/* number of crossing edges at level */
	if (g->numce) {
		g->numce = dp_free(g->numce);
		if (g->numce) {
		}
	}

	g->numce = (int *)dp_calloc(1, ((g->maxlevel + 1) * sizeof(int)));

	/* with too complex graph data at least this message is on console before cpu get roasted. */
	printf("%s(): starting barycenter algorithm for graph with %d nodes, %d edges in %d levels ... wait\n", __func__, g->nnodes,
	       g->nedges, g->maxlevel);
	fflush(stdout);

	if (g->maxlevel == 0) {
		/* if graph has only 1 or more nodes */
		return;
	}

	if (g->nnodes < 2) {
		return;
	}

	if (g->nedges < 2) {
		return;
	}

	bc_n(g, it1v, it2v);

	return;
}

/* end */
