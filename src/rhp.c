
/*
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
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 * Copyright mooigrap authors
 */

/* updated: it now allows empty levels, see if(0) { rhp_log() } */

/* modified from GNU GCC versions splay tree database */

/* A splay-tree datatype.
   Copyright (C) 1998 Free Software Foundation, Inc.
   Contributed by Mark Mitchell

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* For an easily readable description of splay-trees, see:

     Lewis, Harry R. and Denenberg, Larry.  Data Structures and Their
     Algorithms.  Harper-Collins, Inc.  1991.

  verified it is no problem to run this splay tree nested
  inside another splay tree, nested inside a splay tree etc.

  splay is fast because it is based on the real-world observation
  that a search in data is done with a key the next search is often
  with a similar key value so splay changes root of the tree everytime.
*/

/*
 * relative horizontal positioning:
 * based on GNU GPL source from Matthias Stallman
 * api is described in rhp.h
 * demo program how to use is in mainrhp.c
 * Copyright (C) 2008, 2011 Matthias Stallmann, Saurabh Gupta.
 * See also https://github.com/mfms-ncsu
 * "Crossing Minimization in K-layer Graphs"
 * Saurabh Gupta 2008 - 74 pagina's
 * This source can be "compiled" to javascript using llvm emscripten
 * and that resuls in working running javascript. tested and verified.
 */

/*
 * core edge crossing reduction graph barycenter in c in a single file.
 * this is a barycenter algo as in graph layout not as in astronomy.
 * This rhp relative-horizontal-positioning is the part which uses
 * temporary so much extra memory to save a copy of the graph positions
 * and so much cpu usage to try different graph layout configurations.
 * This rhp is a new experimental idea to do it this way which has few
 * benefits from other ways how it is done and currently as simple as
 * possible as a start, so it has toedoe to improve it.
 *
 * limits:
 * because it depends on datatype (signed int) the maximum value for
 * number of nodes/edges/levels is for each (2^31 - 1) is 2147483647
 * the number of edge crossings in the graph depends on the datatype
 * (signed long int) maximum of (2^63 -1) that is 9223372036854775807
 *
 * This is approx. 3000 lines text and 2000 lines program source code.
 * The global routines available are in rhp.h
 * All routines are static and this needs only the c-lib functions:
 * fclose, fflush, fopen, free, malloc, qsort, stderr/stdout, vfprintf
 *
 * The global routines are pedantic about the data supplied.
 * The input are nodes+edges in vertical relative levels
 * and a pointer to a struct with more data.
 * At top of drawing must be level 0 and downward the other
 * levels n. The edges must point downward and exactly span
 * one (1) level, that is the to-node must be one level higher
 * then the from node. The graph can have zero edges but not
 * zero nodes. In every level is a node supposed to be normally.
 * First init() must be done, then filling the nodes and then
 * the edges, after that running the layout() routine and using
 * node_foreach() with a callback() function the relative
 * x position of the nodes within the level are available.
 * When that is done the data is not needed anymore and with
 * a deinit() routine all memory is free()'ed and there are
 * no memory leaks.
 *
 * When init() has a filename supplied then a log file is written
 * to that file and errors are printed with a '!' also on stderr.
 *
 * To fprintf() 64bits in c99 mode inttypes.h is used with these defs:
 * #define PRIu64       "I64u" // unsigned int
 * #define PRIi64       "I64i" // signed int
 * #define PRIx64       "I64x" // hexadecimal
 * This seems to be the preferred portable way to print 64bits ints.
 * This has a internal splay database with the nodes+edges data.
 *
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
T     |  0    1    0    1  | 2.0                    ,
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

/* config.h must have set HAVE_INTTYPES_H */
#include "config.h"

#ifndef HAVE_INTTYPES_H
#warning "this file needs inttypes.h for PRIi64 printf macro's and c99 mode with -std=c99 option"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>		/* this needs c99 mode with gcc -std=c99 */
#include <stddef.h>		/* for ptrdiff_t etc. */

#include "splay-tree.h"
#include "rhp.h"
#include "dpmem.h"

/* main place tp wrap malloc/free */
static void *mymalloc(size_t n, char *f, int l)
{
	if (f) {
	}
	if (l) {
	}
	return (dp_calloc(1, n));
}

static void myfree(void *ptr, char *f, int l)
{
	if (f) {
	}
	if (l) {
	}
	if (ptr) {
		dp_free(ptr);
	}
	return;
}

/* struct def forward decl */
struct rhpedge;

/* int64_t or ptrdiff_t or long long int (64-bits) */
typedef long long int rhp_spkey;
typedef long long int rhp_spval;

/* */
struct rhp_spn {
	rhp_spkey key;
	rhp_spval value;
	struct rhp_spn *l;
	struct rhp_spn *r;
};

/* */
struct rhp_sp {
	struct rhp_spn *root;
	int delval;		/* if set delete the value with a free() call */
};

/* node info */
struct rhpnode {
	int num;		/* internal number */
	int innum;		/* number as supplied */
	int level;		/* relative level of node */
	void *data;		/* extra data as supplied */
	int position;		/* relative x position within level */
	int up_degree;		/* number of edges connecting to this node */
	int down_degree;	/* number of edges connecting to this node */
	struct rhpedge **up_edges;	/* edges connecting to this node */
	struct rhpedge **down_edges;	/* edges connecting to this node */
	int weight;		/* weight of a node determines position */
	int64_t up_crossings;	/* */
	int64_t down_crossings;	/* */
};

/* edge info */
struct rhpedge {
	int num;		/* internal number */
	int innum;		/* number as supplied */
	struct rhpnode *fn;	/* from node number */
	struct rhpnode *tn;	/* to node number */
	void *data;		/* extra data as supplied */
	struct rhpnode *up_node;	/* */
	struct rhpnode *down_node;	/* */
	int64_t crossings;	/* */
};

/* level info */
struct rhplevel {
	int number_of_nodes;	/* number of nodes in this level */
	int number_adjustments;	/* number of nodes in level weight adjustments done */
	struct rhpnode **nodes;	/* nodes in this level */
};

/* edge crossing info */
struct rhp_inter_layer_struct {
	int number_of_edges;	/* number of edges in level */
	struct rhpedge **eedges;	/* edges in level */
	int64_t number_of_crossings;	/* number of crossings in level 64bit */
};

/* level node order info */
struct rhp_order_struct {
	int num_layers;
	int *num_nodes_on_layer;
	struct rhpnode ***node_ptr_on_layer;
};

/* more verbose log output if set */
static int rhp_verbose = 0;

/* set if init() is done */
static int rhp_inited = 0;

/* stream to write log info or stdout */
static FILE *rhp_logstream = NULL;

/* name of log file */
static char *rhp_logname = NULL;

/* set if logging is needed */
static int rhp_dolog = 0;

/* master node+edge list as from input */
static struct rhp_sp *rhp_sp_master_node_list = (struct rhp_sp *)0;
static struct rhp_sp *rhp_sp_master_edge_list = (struct rhp_sp *)0;

/* master nodelist sorted on positions after layout */
static struct rhp_sp *rhp_sp_master_node_list_sorted = (struct rhp_sp *)0;

/* uniq node+edge numbers */
static int rhp_uniq_nodenum = 0;
static int rhp_uniq_edgenum = 0;
static int rhp_number_of_nodes = 0;
static int rhp_number_of_edges = 0;
static int rhp_number_of_isolated_nodes = 0;

/* max and number of levels */
static int rhp_maxlevel = 0;
static int rhp_nlevels = 0;

/* number of (initial) crossings in graph (this should be a 64bits int)*/
static int64_t rhp_crossings = (signed long int)(-1);
static int64_t rhp_start_crossings = (signed long int)(-1);

/* layers data */
static struct rhp_sp *rhp_sp_layers = (struct rhp_sp *)0;

/* crossing edges layers info */
static struct rhp_sp *rhp_sp_between_layers = (struct rhp_sp *)0;

/* order status info */
static struct rhp_order_struct *rhp_best_crossings_order = (struct rhp_order_struct *)0;

/* iteration counts */
static int rhp_iter = 0;
static int rhp_maxiter = 0;

/* optional callback() routine during layouet */
static int (*rhp_getlayoutdata)(int iter, int maxiter, uint64_t ncross,
				uint64_t previous_ncross, uint64_t reduction, int better, int improvements, int notimprovements);

/* number of iterations improves or not-improved */
static int rhp_improvements = 0;
static int rhp_notimprovements = 0;

/* node weight adjustment if set to 1 do avg mode, else left mode */
static int rhp_adjustweight = 0;

/* malloc free counter */
static int64_t rhp_n_malloc = 0;
static int64_t rhp_n_free = 0;

/* forward decl. */
static void *rhp_free(void *ptr, const char *func, int line);
static void *rhp_malloc(size_t n, const char *func, int line);
static struct rhp_sp *rhp_sp_new(int delval);
static int rhp_sp_has_data(struct rhp_sp *sp);
static struct rhp_spn *rhp_sp_min(struct rhp_sp *sp);
static struct rhp_sp *rhp_sp_delete(struct rhp_sp *sp);
static void rhp_tree_delete_helper(struct rhp_sp *sp, struct rhp_spn *node);
static void rhp_sp_insert(struct rhp_sp *sp, rhp_spkey key, rhp_spval value);
static struct rhp_spn *rhp_sp_next(struct rhp_sp *sp, rhp_spkey key);
static struct rhp_spn *rhp_sp_lookup(struct rhp_sp *sp, rhp_spkey key);
static inline void rhp_sp_sp_rr(struct rhp_spn **pp, struct rhp_spn *p, struct rhp_spn *n);
static inline void rhp_sp_sp_rl(struct rhp_spn **pp, struct rhp_spn *p, struct rhp_spn *n);
static void rhp_sp_sp(struct rhp_sp *sp, rhp_spkey key);
static void rhp_log(char *format, ...);
static void rhp_empty_best_crossings_order(void);
static void rhp_empty_sp_master_node_list(void);
static void rhp_empty_sp_master_edge_list(void);
static void rhp_empty_sp_layers(void);
static void rhp_empty_sp_between_layers(void);
static void rhp_allocatelayers(void);
static void rhp_allocateadjacencylists(void);
static int rhp_countisolatednodes(void);
static void rhp_initcrossings(void);
static struct rhp_inter_layer_struct *rhp_makeinterlayer(int upper_layer);
static int rhp_count_down_edges(int layer_number);
static void rhp_updateallcrossings(void);
static void rhp_updateallpositions(void);
static void rhp_updatenodepositions(int layer);
static void rhp_updatecrossingsforlayer(int layer);
static void rhp_updatecrossingsbetweenlayers(int layer_number);
static int rhp_compare_down_edges(const void *ptr_i, const void *ptr_j);
static void rhp_sortbydownnodeposition(struct rhpedge **edge_array, int num_edges);
static void rhp_add_edges_to_array(struct rhpedge **edge_array, struct rhpedge **edges_to_add, int num_edges, int start_pos);
static int64_t rhp_count_inversions_down(struct rhpedge **edge_array, int num_of_edges, int diff);
static int64_t rhp_insert_and_count_inversions_down(struct rhpedge
						    **edge_array, int starting_index, int diff);
static int64_t rhp_numberofcrossings(void);
static void rhp_order_init(void);
static void rhp_barycenter(void);
static int rhp_terminate(void);
static int rhp_end_of_iteration(void);
static int rhp_barycenterupsweep(int lowlevel, int hilevel);
static int rhp_barycenterdownsweep(int lowlevel, int hilevel);
static int rhp_barycenterweights(int layer, int orientation);
static void rhp_barycenterweights_adjust(int layer, int orientation);
static void rhp_node_weight(struct rhpnode *node, int orientation);
static int rhp_compare_weights(const void *ptr_i, const void *ptr_j);
static void rhp_layersort(int layer);
static void rhp_updatecrossingsforlayer(int layer);
static void rhp_save_order(void);
static void rhp_restore_order(void);

/* create new sorted nodelist */
static void rhp_sorted_nodelist(void);

/* version info */
char *rhp_version(void)
{
	return ((char *)"1.7");
}

/* init with optional filename to log to or stdout if filename is "" */
void rhp_init(char *logname, int loglevel)
{

	/* set if init() is done */
	if (rhp_inited) {
		/* should not happen */
		rhp_log("%s(): rhp_deinit() not done and doing it now shouldnothappen!\n", __func__);
		rhp_deinit();
		/* now re-start with fresh init() */
	}

	/* stream to write log info or stdout if name is "" */
	rhp_logstream = NULL;

	/* set if logging is needed */
	rhp_dolog = 0;

	/* name of log file */
	rhp_logname = NULL;

	/* option */
	if (logname) {
		if (strlen(logname) == 0) {
			/* log stream to stdout */
			rhp_logstream = stdout;
		} else {
			/* log stream to named file or stdout at error */
			rhp_logstream = fopen(logname, "wb");
			if (rhp_logstream == NULL) {
				rhp_logstream = stdout;
			}
		}
		/* set if logging is needed */
		rhp_dolog = loglevel;
		rhp_log("%s(): starting logfile!\n", __func__);
	}

	/* master node+edge list as from input */
	rhp_sp_master_node_list = rhp_sp_new(1);
	rhp_sp_master_edge_list = rhp_sp_new(1);

	/* uniq node+edge numbers */
	rhp_uniq_nodenum = 0;
	rhp_uniq_edgenum = 0;
	rhp_number_of_nodes = 0;
	rhp_number_of_edges = 0;
	rhp_number_of_isolated_nodes = 0;

	/* crossing edges layers info */
	rhp_sp_between_layers = rhp_sp_new(1);

	/* max and number of levels */
	rhp_maxlevel = 0;
	rhp_nlevels = 0;

	/* number of (initial) crossings in graph */
	rhp_crossings = (int64_t) (-1);
	rhp_start_crossings = (int64_t) (-1);

	/* no order info */
	rhp_best_crossings_order = (struct rhp_order_struct *)0;

	/* no optional callback() routine during layouet */
	rhp_getlayoutdata = NULL;

	/* number of iterations improves or not-improved */
	rhp_improvements = 0;
	rhp_notimprovements = 0;

	/* print some machine info */
	rhp_log("%s(): sizeof (int) is %d bytes (expect 4)\n", __func__, (int)sizeof(int));
	rhp_log("%s(): sizeof (long long) is %d bytes (expect 8)\n", __func__, (int)sizeof(long long));
	rhp_log("%s(): sizeof (int64_t) is %d bytes (expect 8)\n", __func__, (int)sizeof(int64_t));
	rhp_log("%s(): sizeof (intptr_t) is %d bytes (expect 8)\n", __func__, (int)sizeof(intptr_t));
	rhp_log("%s(): sizeof (struct rhp_spn) is %d bytes\n", __func__, (int)sizeof(struct rhp_spn));
	rhp_log("%s(): sizeof (struct rhp_sp) is %d bytes\n", __func__, (int)sizeof(struct rhp_sp));
	rhp_log("%s(): sizeof (struct rhpnode) is %d bytes\n", __func__, (int)sizeof(struct rhpnode));
	rhp_log("%s(): sizeof (struct rhpedge) is %d bytes\n", __func__, (int)sizeof(struct rhpedge));
	rhp_log("%s(): sizeof (struct rhplevel) is %d bytes\n", __func__, (int)sizeof(struct rhplevel));
	rhp_log("%s(): sizeof (struct rhp_inter_layer_struct) is %d bytes\n", __func__, (int)sizeof(struct rhp_inter_layer_struct));
	rhp_log("%s(): sizeof (struct rhp_order_struct) is %d bytes\n", __func__, (int)sizeof(struct rhp_order_struct));

	/* set if init() is done */
	rhp_inited = 1;

	return;
}

/* */
void rhp_deinit(void)
{

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return;
	}

	rhp_log("%s():\n", __func__);

	/* empty crossing order info */
	rhp_empty_best_crossings_order();

	/* empty data inside layers */
	rhp_empty_sp_layers();

	/* empty data inside node+edge list */
	rhp_empty_sp_between_layers();
	rhp_empty_sp_master_node_list();
	rhp_empty_sp_master_edge_list();

	/* empty layers itself */
	rhp_sp_layers = rhp_sp_delete(rhp_sp_layers);

	/* clear order info. can be 0 at only init/deinit */
	if (rhp_best_crossings_order) {
		rhp_best_crossings_order = (struct rhp_order_struct *)rhp_free((void *)
									       rhp_best_crossings_order, __func__, __LINE__);
	}

	/* master node+edge list as from input */
	rhp_sp_master_node_list = rhp_sp_delete(rhp_sp_master_node_list);
	rhp_sp_master_edge_list = rhp_sp_delete(rhp_sp_master_edge_list);
	rhp_sp_master_node_list_sorted = rhp_sp_delete(rhp_sp_master_node_list_sorted);

	/* crossing edges layers info */
	rhp_sp_between_layers = rhp_sp_delete(rhp_sp_between_layers);

	/* uniq node+edge numbers */
	rhp_uniq_nodenum = 0;
	rhp_uniq_edgenum = 0;
	rhp_number_of_nodes = 0;
	rhp_number_of_edges = 0;
	rhp_number_of_isolated_nodes = 0;

	/* max and number of levels */
	rhp_maxlevel = 0;
	rhp_nlevels = 0;

	/* number of (initial) crossings in graph */
	rhp_crossings = (int64_t) (-1);
	rhp_start_crossings = (int64_t) (-1);

	/* no optional callback() routine during layouet */
	rhp_getlayoutdata = NULL;

	/* number of iterations improves or not-improved */
	rhp_improvements = 0;
	rhp_notimprovements = 0;

	/* check malloc/free balance */
	if (rhp_n_malloc != rhp_n_free) {
		/* fixup needed here */
		if (rhp_dolog > 1) {
			rhp_log("%s(): done %" PRIu64 " malloc and %" PRIu64
				" free and delta is %" PRIi64 " shouldnothappen!\n",
				__func__, rhp_n_malloc, rhp_n_free, (rhp_n_malloc - rhp_n_free));
		}

	}

	rhp_n_malloc = 0;
	rhp_n_free = 0;

	/* check opt logfile */
	if (rhp_dolog) {
		rhp_log("%s(): closing logfile\n", __func__);
		/* name of log file */
		if (rhp_logname) {
			/* glibc fclose() does not set some ptr's to 0 creating valgrind error messages */
			(void)fclose(rhp_logstream);
			rhp_logname = NULL;
		}
	}

	/* set if logging is needed */
	rhp_dolog = 0;

	/* set if init() is done */
	rhp_inited = 0;

	return;
}

/* return 0 if oke, or 1 at error */
int rhp_addnode(int num, int level, void *data)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpnode *nn = (struct rhpnode *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() mus be done shouldnothappen!\n", __func__);
		return (1);
	}

	/* validate input */
	if (num < 0) {
		rhp_log("%s(): number %d is below zero and node skipped shouldnothappen!\n", __func__, num);
		return (1);
	}

	if (level < 0) {
		rhp_log("%s(): level %d is below zero and node skipped shouldnothappen!\n", __func__, level);
		return (1);
	}

	/* check if node already existed */
	spn = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) num);

	if (spn) {
		rhp_log("%s(): node number %d already existed, skipped this add shouldnothappen!\n", __func__, num);
		return (1);
	}

	/* create fresh node data info */
	nn = (struct rhpnode *)rhp_malloc(sizeof(struct rhpnode), __func__, __LINE__);

	/* set the info n */
	nn->num = (rhp_uniq_nodenum);
	rhp_uniq_nodenum = (rhp_uniq_nodenum + 1);
	nn->innum = num;
	nn->level = level;
	nn->data = data;

	/* insert node in database indexed on initial supplied number */
	rhp_sp_insert(rhp_sp_master_node_list, (splay_tree_key) num, (splay_tree_value) nn);

	/* keep track of max. level seen */
	if (level >= rhp_maxlevel) {
		rhp_maxlevel = level;
		rhp_nlevels = (rhp_maxlevel + 1);
	}

	rhp_log("%s(): added node %d level %d data=%p now maxlevel=%d\n", __func__, num, level, (void *)data, rhp_maxlevel);

	return (0);
}

/* return 0 if oke or 1 at error */
int rhp_addedge(int num, int fnode, int tnode, void *data)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhp_spn *spnf = (struct rhp_spn *)0;
	struct rhp_spn *spnt = (struct rhp_spn *)0;
	struct rhpnode *fn = (struct rhpnode *)0;
	struct rhpnode *tn = (struct rhpnode *)0;
	struct rhpedge *ne = (struct rhpedge *)0;
	int edgelen = 0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() mus be done shouldnothappen!\n", __func__);
		return (1);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): there are no nodes in database skipping edge %d->%d shouldnothappen!\n", __func__, fnode, tnode);
		return (1);
	}

	/* validate input */
	if (num < 0) {
		rhp_log("%s(): number %d is below zero and edge skipped shouldnothappen!\n", __func__, num);
		return (1);
	}

	if (fnode < 0) {
		rhp_log("%s(): from node number %d is below zero and edge skipped shouldnothappen!\n", __func__, fnode);
		return (1);
	}

	if (tnode < 0) {
		rhp_log("%s(): to node number %d is below zero and edge skipped shouldnothappen!\n", __func__, tnode);
		return (1);
	}

	/* check if edge already existed */
	spn = rhp_sp_lookup(rhp_sp_master_edge_list, (splay_tree_key) num);

	if (spn) {
		rhp_log
		    ("%s(): edge number %d does already exists from %d->%d and skipped shouldnothappen!\n",
		     __func__, num, fnode, tnode);
		return (1);
	}

	/* check if node exist */
	spnf = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) fnode);

	if (spnf == (struct rhp_spn *)0) {
		rhp_log
		    ("%s(): from node %d is not in database in edge from %d->%d and skipped shouldnothappen!\n",
		     __func__, fnode, fnode, tnode);
		return (1);
	}

	/* get the node info */
	fn = (struct rhpnode *)spnf->value;

	spnt = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) tnode);

	if (spnt == (struct rhp_spn *)0) {
		rhp_log
		    ("%s(): to node %d is not in database in edge from %d->%d and skipped shouldnothappen!\n",
		     __func__, tnode, fnode, tnode);
		return (1);
	}

	/* get the node info */
	tn = (struct rhpnode *)spnt->value;

	/* check for exact 1 level len of edge */
	edgelen = (tn->level - fn->level);

	if (edgelen != 1) {
		rhp_log
		    ("%s(): edge len is %d at %d->%d from level %d->%d and should be 1 shouldnothappen!\n",
		     __func__, edgelen, fnode, tnode, fn->level, tn->level);
		return (1);
	}

	/* edge must point downwards */
	if (tn->level < fn->level) {
		rhp_log
		    ("%s(): edge len %d at %d->%d from level %d->%d should be downward shouldnothappen!\n",
		     __func__, edgelen, fnode, tnode, fn->level, tn->level);
		return (1);
	}

	/* create fresh edge info */
	ne = (struct rhpedge *)rhp_malloc(sizeof(struct rhpedge), __func__, __LINE__);

	/* set the info */
	ne->num = rhp_uniq_edgenum;	/* internal uniq edge number */
	rhp_uniq_edgenum = (rhp_uniq_edgenum + 1);
	ne->innum = num;	/* incoming edge number */
	ne->fn = fn;		/* from-node */
	ne->tn = tn;		/* to-node */
	ne->data = data;	/* opt. extra data */
	ne->up_node = tn;	/* highest node level */
	ne->down_node = fn;	/* lowest node level */
	ne->crossings = (int64_t) 0;	/* crossings of edge */

	/* insert the edge in database initially indexed on supplied number */
	rhp_sp_insert(rhp_sp_master_edge_list, (rhp_spkey) num, (rhp_spval) ne);

	rhp_log("%s(): added edge %d from node %d to node %d data=%p\n", __func__, num, fnode, tnode, (void *)data);

	return (0);
}

/* run layouter */
void rhp_layout(int options, int nodeweightadjust)
{
	int64_t redu = 0;

	/* to implement */
	if (options) {
	}

	if (nodeweightadjust) {
		/* 0 is leftish node weight adjust, 1 is avg. node weight adjust */
		rhp_adjustweight = 1;
	}

	else {
		rhp_adjustweight = 0;
	}

	rhp_log("%s(): start with rhp_adjustweight %d\n", __func__, rhp_adjustweight);

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return;
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): there is no node data shouldnothappen!\n", __func__);
		return;
	}

	/* no edges is oke but there must be at least 1 node */

	/* number of iterations improves or not-improved */
	rhp_improvements = 0;
	rhp_notimprovements = 0;

	rhp_log("%s(): setting initial edge crossings is %" PRIi64 " %" PRIi64
		"\n", __func__, (int64_t) rhp_start_crossings, (int64_t) rhp_crossings);

	/* setup data structs and calculate initial crossings */
	rhp_crossings = rhp_initial_crossings();

	rhp_log("%s(): configured initial edge crossings is %" PRIi64 " %" PRIi64
		"\n", __func__, (int64_t) rhp_start_crossings, (int64_t) rhp_crossings);

	/* save status arrays initialize */
	rhp_order_init();

	/* reduce edge crossings */
	if (rhp_start_crossings) {
		rhp_barycenter();
	}

	/* calculate percentage of edge crossing reduction */
	if (rhp_start_crossings) {
		redu = ((100 * rhp_crossings) / rhp_start_crossings);
		redu = (100 - redu);
	} else {
		redu = 0;
	}

	/* create new sorted nodelist */
	rhp_sorted_nodelist();

	rhp_log("%s(): end and final edge crossings is %" PRIi64
		" after %d iterations and started with %" PRIi64
		" crossings reducing edge crossings with %" PRIu64 " percent\n",
		__func__, (int64_t) rhp_crossings, rhp_iter, rhp_start_crossings, redu);

	return;
}

/* get layouter data during iteration */
void rhp_layout_callback(int (*getlayoutdata)
			  (int iter, int maxiter, uint64_t ncross,
			   uint64_t previous_ncross, uint64_t reduction, int better, int improvements, int notimprovements))
{

	/* check for callback() */
	if(getlayoutdata == NULL) {
		rhp_log("%s(): no callback routine shouldnothappen!\n", __func__);
		return;
	}

	/* set the callback routine to use */
	rhp_getlayoutdata = getlayoutdata;

	return;
}

/* get node data */
int rhp_node_foreach(int (*getnodedata)
		      (int num, int level, int pos, void *data))
{
	struct rhp_spn *spn =(struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int status = 0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (getnodedata == NULL) {
		/* no callback() nothing todo */
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list_sorted) == 0) {
		/* no data nothing todo */
		return (0);
	}

	status = 0;

	spn = rhp_sp_min(rhp_sp_master_node_list_sorted);

	while (spn) {
		nd = (struct rhpnode *)spn->value;
		rhp_log("%s(): node %d level %d pos %d\n", __func__, nd->innum, nd->level, nd->position);
		status = (*getnodedata) (nd->innum, nd->level, nd->position, nd->data);
		if (status) {
			break;
		}
		spn = rhp_sp_next(rhp_sp_master_node_list_sorted, spn->key);
	}

	return (status);
}

/* instead of foreach() get level of given node or -1 at error */
int rhp_node_get_level(int num)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (-1);
	}

	/* master node list is sorted on innum, input number
	 * master_node_list_sorted is sorted on internal number
	 */
	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		return (-1);
	}

	/* check if node exist */
	spn = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) num);

	if (spn == (struct rhp_spn *)0) {
		/* not in database */
		rhp_log("%s(): could not find node %d in master_node_list!\n", __func__, num);
		return (-1);
	}

	nd = (struct rhpnode *)spn->value;
	rhp_log("%s(): node %d level %d pos %d\n", __func__, nd->innum, nd->level, nd->position);

	return (nd->level);
}

/* instead of foreach() get position of given node or -1 at error */
int rhp_node_get_position(int num)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (-1);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		return (-1);
	}

	/* check if node exist */
	spn = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) num);

	if (spn == (struct rhp_spn *)0) {
		/* not in database */
		rhp_log("%s(): could not find node %d in master_node_list!\n", __func__, num);
		return (-1);
	}

	nd = (struct rhpnode *)spn->value;
	rhp_log("%s(): node %d level %d pos %d\n", __func__, nd->innum, nd->level, nd->position);

	return (nd->position);
}

/* instead of foreach() get data of given node or -1 at error */
void *rhp_node_get_data(int num)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return ((void *)-1);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		return ((void *)-1);
	}

	/* check if node exist */
	spn = rhp_sp_lookup(rhp_sp_master_node_list, (splay_tree_key) num);

	if (spn == (struct rhp_spn *)0) {
		/* not in database */
		rhp_log("%s(): could not find node %d in master_node_list!\n", __func__, num);
		return ((void *)-1);
	}

	nd = (struct rhpnode *)spn->value;
	rhp_log("%s(): node %d level %d pos %d\n", __func__, nd->innum, nd->level, nd->position);

	return (nd->data);
}

/* get edge data via callback routine */
int rhp_edge_foreach(int (*getedgedata)
		      (int num, int fnum, int flevel, int fpos, int tnum, int tlevel, int tpos, int64_t ecross, void *data))
{
	struct rhp_spn *spn =(struct rhp_spn *)0;
	struct rhpedge *ed = (struct rhpedge *)0;
	int status = 0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (getedgedata == NULL) {
		/* no callback() nothing todo */
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_edge_list) == 0) {
		/* no data nothing todo */
		return (0);
	}

	/* status 0 means no errors */
	status = 0;

	spn = rhp_sp_min(rhp_sp_master_edge_list);

	while (spn) {
		ed = (struct rhpedge *)spn->value;
		status =
		    (*getedgedata) (ed->innum, ed->fn->innum, ed->fn->level,
				    ed->fn->position, ed->tn->innum, ed->tn->level, ed->tn->position, ed->crossings, ed->data);
		if (status) {
			break;
		}
		spn = rhp_sp_next(rhp_sp_master_edge_list, spn->key);
	}

	return (status);
}

/* setup data structs and calculate initial crossings */
int64_t rhp_initial_crossings(void)
{
	rhp_log("%s(): start crossings %" PRIi64 "\n", __func__, (int64_t) rhp_start_crossings);

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return ((int64_t) 0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		rhp_start_crossings = (int64_t) 0;
		return ((int64_t) rhp_start_crossings);
	}

	/* at no edges there are no edge crossings */
	if (rhp_sp_has_data(rhp_sp_master_edge_list) == 0) {
		/* no edges is oke */
		rhp_start_crossings = (int64_t) 0;
		/* data structs below must be build */
	}

	/* if already inited then oke. */
	if (rhp_start_crossings >= 0) {
		rhp_log("%s(): already inited start crossings %" PRIi64 "\n", __func__, (int64_t) rhp_start_crossings);
		/* data structs below must be build */
		return (rhp_start_crossings);
	}

	rhp_log("%s(): allocate layers\n", __func__);

	/* create layers and count nodes in layers */
	rhp_allocatelayers();

	/* handle edges */
	rhp_allocateadjacencylists();

	/* get number of single nodes */
	rhp_number_of_isolated_nodes = rhp_countisolatednodes();

	rhp_log("%s(): %" PRIi64 " single nodes\n", __func__, (int64_t) rhp_number_of_isolated_nodes);

	/* init data for edge crossing counting */
	rhp_initcrossings();

	/* set for every level number of edge crossings */
	rhp_updateallcrossings();

	/* sum all levels edge crossings for the whole graph */
	rhp_start_crossings = rhp_numberofcrossings();

	/* node data without the extra storage for the connects */
	rhp_log("%s(): using %" PRIu64 " bytes for the node data core part\n",
		__func__, (rhp_number_of_nodes * sizeof(struct rhpnode)));
	rhp_log("%s(): using %" PRIu64 " bytes for the edge data\n", __func__, (rhp_number_of_edges * sizeof(struct rhpedge)));

	return ((int64_t) rhp_start_crossings);
}

/* calculate crossings */
int64_t rhp_current_crossings(void)
{

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return ((int64_t) 0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		rhp_crossings = (int64_t) 0;
		return ((int64_t) rhp_crossings);
	}

	/* at no edges there are no edge crossings */
	if (rhp_sp_has_data(rhp_sp_master_edge_list) == 0) {
		/* no edges is oke */
		rhp_crossings = (int64_t) 0;
		return ((int64_t) rhp_crossings);
	}

	/* if not inited yet */
	if (rhp_start_crossings < 0) {
		rhp_crossings = rhp_initial_crossings();
	} else {
		/* now calculate crossings */
		if (rhp_number_of_edges == 1) {
			/* at one edge there cannot be crossing edges */
			rhp_crossings = (int64_t) 0;
		} else {
			rhp_crossings = (int64_t) 0;
			/* do actual re-cualculation of crossings */
			/* set for every level number of edge crossings */
			rhp_updateallcrossings();
			/* sum all levels edge crossings for the whole graph */
			rhp_crossings = rhp_numberofcrossings();
		}
	}

	return ((int64_t) rhp_crossings);
}

/* calculate crossings at level */
int64_t rhp_current_crossings_at_level(int level)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		return (0);
	}

	if (level < 0) {
		rhp_log("%s(): level %d is below 0 shouldnothappen!\n", __func__, level);
		return (0);
	}

	if (level > rhp_maxlevel) {
		rhp_log("%s(): level %d is above max level %dshouldnothappen!\n", __func__, level, rhp_maxlevel);
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_between_layers) == 0) {
		/* no data can happen when there were no edges and that is oke. */
		return ((uint64_t) 0);
	}

	if (rhp_nlevels == 0) {
		/* nothing todo */
		rhp_log("%s(): no levels shouldnothappen!\n", __func__);
		return ((uint64_t) 0);
	}

	spn = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) level);

	if (spn) {
		is = (struct rhp_inter_layer_struct *)spn->value;
		return ((uint64_t) is->number_of_crossings);
	} else {
		rhp_log("%s(): could not get data for level %d shouldnothappen!\n", __func__, level);
	}

	return ((uint64_t) 0);
}

/* get number of nodes in level */
int rhp_nodes_in_level(int level)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		return (0);
	}

	if (level < 0) {
		rhp_log("%s(): level %d is below 0 shouldnothappen!\n", __func__, level);
		return (0);
	}

	if (level > rhp_maxlevel) {
		rhp_log("%s(): level %d is above max level %dshouldnothappen!\n", __func__, level, rhp_maxlevel);
		return (0);
	}

	/* empty layer info */
	if (rhp_sp_has_data(rhp_sp_layers) == 0) {
		/* nothing todo. */
		return (0);
	}

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

	/* nodes in level */
	if (spn) {
		rl = (struct rhplevel *)spn->value;
		return (rl->number_of_nodes);
	} else {
		rhp_log("%s(): could not find data for level %d shouldnothappen!\n", __func__, level);
	}

	return (0);
}

/* get number of nodes in layouter */
int rhp_nodes_in_layout(void)
{
	int c = 0;
	struct rhp_spn *spn = (struct rhp_spn *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data nothing todo */
		return (0);
	}

	/* count */
	c = 0;

	spn = rhp_sp_min(rhp_sp_master_node_list);

	while (spn) {
		c = (c + 1);
		spn = rhp_sp_next(rhp_sp_master_node_list, spn->key);
	}

	return (c);
}

/* get number of edges in layouter */
int rhp_edges_in_layout(void)
{
	int c = 0;
	struct rhp_spn *spn = (struct rhp_spn *)0;

	/* check on inited */
	if (rhp_inited == 0) {
		rhp_log("%s(): first rhp_init() must be done shouldnothappen!\n", __func__);
		return (0);
	}

	if (rhp_sp_has_data(rhp_sp_master_edge_list) == 0) {
		/* no data nothing todo */
		return (0);
	}

	/* count */
	c = 0;

	spn = rhp_sp_min(rhp_sp_master_edge_list);

	while (spn) {
		c = (c + 1);
		spn = rhp_sp_next(rhp_sp_master_edge_list, spn->key);
	}

	return (c);
}

/****zz1****/

/* or wrap to free() */
static void *rhp_free(void *ptr, const char *func, int line)
{

	if (ptr == (void *)0) {
		rhp_log("%s(): nil ptr from %s line %d shouldnothappen!\n", __func__, (char *)func, line);
		return ((void *)0);
	}

	if (ptr) {
		myfree(ptr, (char *)func, line);
		rhp_n_free = (rhp_n_free + 1);

		if (rhp_dolog > 1) {
			rhp_log("%p\t%s\tline %d\trhp_free()\tmemtrace\n", (void *)ptr, func, line);
		}
	}

	return ((void *)0);
}

/* or wrap to calloc() */
static void *rhp_malloc(size_t n, const char *func, int line)
{
	void *ptr = (void *)0;

	if (n == 0) {
		rhp_log("%s(): 0 bytes to malloc from %s line %d shouldnothappen!\n", __func__, (char *)func, line);
		return ((void *)0);
	}

	rhp_n_malloc = (rhp_n_malloc + 1);

	ptr = mymalloc(n, (char *)func, line);

	if (rhp_dolog > 1) {
		rhp_log("%p\t%s\tline %d\trhp_malloc(%" PRIu64 ")\tmemtrace\n", (void *)ptr, func, line, (uint64_t) n);
	}

	return ((void *)ptr);
}

/* gcc splay gnu gpl version 3 fsf */
static struct rhp_sp *rhp_sp_new(int delval)
{
	struct rhp_sp *newsp = (struct rhp_sp *)0;

	/* new splay */
	newsp = rhp_malloc(sizeof(struct rhp_sp), __func__, __LINE__);

	/* empty data */
	newsp->root = (struct rhp_spn *)0;

	/* if set sp_delete() deletes the value */
	newsp->delval = delval;

	return ((struct rhp_sp *)newsp);
}

/* return 1 if splay has data */
static int rhp_sp_has_data(struct rhp_sp *sp)
{

	if (sp == (struct rhp_sp *)0) {
		/* no splay at all is no data */
		return (0);
	}

	if (sp->root == (struct rhp_spn *)0) {
		/* nil root is no data */
		return (0);
	}

	/* tree has data */
	return (1);
}

/* */
static struct rhp_spn *rhp_sp_min(struct rhp_sp *sp)
{
	struct rhp_spn *nspn = (struct rhp_spn *)0;

	if (sp == (struct rhp_sp *)0) {
		/* no tree */
		return ((struct rhp_spn *)0);
	}

	if (sp->root == (struct rhp_spn *)0) {
		/* no data */
		return ((struct rhp_spn *)0);
	}

	nspn = sp->root;

	if (nspn) {

		while (nspn->l) {
			nspn = nspn->l;
		}

	}

	return ((struct rhp_spn *)nspn);
}

/* */
static void rhp_sp_insert(struct rhp_sp *sp, rhp_spkey key, rhp_spval value)
{
	struct rhp_spn *newspn = (struct rhp_spn *)0;

	if (sp == (struct rhp_sp *)0) {
		return;
	}

	if (sp->root == (struct rhp_spn *)0) {

		/* sp->root==0 this is first entry */
		newspn = rhp_malloc(sizeof(struct rhp_spn), __func__, __LINE__);

		sp->root = newspn;

		sp->root->l = (struct rhp_spn *)0;
		sp->root->r = (struct rhp_spn *)0;

		sp->root->key = key;
		sp->root->value = value;

		if (rhp_verbose) {
			rhp_log("%s(): sp (%p) sp->root (%p) is %" PRIi64
				" at first entry\n", __func__, (void *)sp, (void *)sp->root, (uint64_t) sp->root->key);
		}

		return;
	}

	/* */
	rhp_sp_sp(sp, key);

	if (sp->root->key == key) {
		if (sp->delval) {
			if (sp->root->value) {
				(void)rhp_free((void *)sp->root->value, __func__, __LINE__);
				sp->root->value = (rhp_spval) 0;
			}
		}
		sp->root->value = value;
		return;
	}

	newspn = rhp_malloc(sizeof(struct rhp_spn), __func__, __LINE__);

	/* set data for this node */
	newspn->key = key;
	newspn->value = value;

	if (sp->root->key < key) {
		newspn->l = sp->root;
		newspn->r = newspn->l->r;
		newspn->l->r = (struct rhp_spn *)0;
	} else {
		newspn->r = sp->root;
		newspn->l = newspn->r->l;
		newspn->r->l = (struct rhp_spn *)0;
	}

	sp->root = newspn;

	if (rhp_verbose) {
		rhp_log("%s(): sp (%p) sp->root (%p) is %" PRIi64 " at next entry\n",
			__func__, (void *)sp, (void *)sp->root, (uint64_t) sp->root->key);
	}

	return;
}

/* Deallocate NODE (a member of SP), and all its sub-trees.  */
static void rhp_tree_delete_helper(struct rhp_sp *sp, struct rhp_spn *node)
{

	if (node == NULL) {
		return;
	}

	/* recurse */
	rhp_tree_delete_helper(sp, node->l);
	rhp_tree_delete_helper(sp, node->r);

	if (sp->delval) {
		if (node->value) {
			(void)rhp_free((void *)node->value, __func__, __LINE__);
			node->value = (rhp_spval) 0;
		}
	}

	rhp_free((void *)node, __func__, __LINE__);

	return;
}

/* */
static struct rhp_sp *rhp_sp_delete(struct rhp_sp *sp)
{
	if (sp) {
		rhp_tree_delete_helper(sp, sp->root);
		rhp_free((void *)sp, __func__, __LINE__);
	}

	return ((struct rhp_sp *)0);
}

/* */
static struct rhp_spn *rhp_sp_next(struct rhp_sp *sp, rhp_spkey key)
{
	struct rhp_spn *n = (struct rhp_spn *)0;

	if (sp == (struct rhp_sp *)0) {
		return ((struct rhp_spn *)0);
	}

	if (sp->root == (struct rhp_spn *)0) {
		return ((struct rhp_spn *)0);
	}

	rhp_sp_sp(sp, key);

	if (sp->root->key > key) {
		return ((struct rhp_spn *)sp->root);
	}

	n = sp->root->r;

	if (n) {

		while (n->l) {
			n = n->l;
		}

	}

	return ((struct rhp_spn *)n);
}

/* */
static struct rhp_spn *rhp_sp_lookup(struct rhp_sp *sp, rhp_spkey key)
{
	char *s = "not-found";
	if (sp == (struct rhp_sp *)0) {
		return ((struct rhp_spn *)0);
	}

	if (sp->root == (struct rhp_spn *)0) {
		return ((struct rhp_spn *)0);
	}

	if (sp->root->key == key) {
		return ((struct rhp_spn *)sp->root);
	}

	rhp_sp_sp(sp, key);

	if (sp->root == (struct rhp_spn *)0) {
		return ((struct rhp_spn *)0);
	}

	if (sp->root->key == key) {
		s = "found";
	} else {
		s = "not-found";
	}

	if (rhp_verbose) {
		rhp_log("%s(): %s in sp (%p) at %" PRIi64 " when search for %" PRIi64
			"\n", __func__, s, (void *)sp, (uint64_t) sp->root->key, (uint64_t) key);
	}

	if (sp->root->key == key) {
		return ((struct rhp_spn *)sp->root);
	}

	return ((struct rhp_spn *)0);
}

/* */
static inline void rhp_sp_sp_rl(struct rhp_spn **pp, struct rhp_spn *p, struct rhp_spn *n)
{
	struct rhp_spn *tmp = (struct rhp_spn *)0;
	tmp = n->r;
	n->r = p;
	p->l = tmp;
	*pp = n;
	return;
}

/* */
static inline void rhp_sp_sp_rr(struct rhp_spn **pp, struct rhp_spn *p, struct rhp_spn *n)
{
	struct rhp_spn *tmp = (struct rhp_spn *)0;
	tmp = n->l;
	n->l = p;
	p->r = tmp;
	*pp = n;
	return;
}

/* Bottom up splay of key.  */
static void rhp_sp_sp(struct rhp_sp *sp, rhp_spkey key)
{
	struct rhp_spn *n = (struct rhp_spn *)0;
	struct rhp_spn *c = (struct rhp_spn *)0;

	if (sp == (struct rhp_sp *)0) {
		return;
	}

	if (sp->root == (struct rhp_spn *)0) {
		return;
	}

label:

	n = sp->root;
	if (n == (struct rhp_spn *)0) {
		return;
	}

	if (rhp_verbose) {
		rhp_log("%s(): at %" PRIi64 " when search for %" PRIi64 "\n", __func__, (uint64_t) n->key, (uint64_t) key);
	}

	if (key == n->key) {
		return;
	}

	if (key < n->key) {
		c = n->l;
	} else {
		c = n->r;
	}

	if (c == (struct rhp_spn *)0) {
		if (rhp_verbose) {
			rhp_log("%s(): c=<nil> at %" PRIi64 " when search for %" PRIi64
				"\n", __func__, (uint64_t) sp->root->key, (uint64_t) key);
		}
		return;
	}

	if ((key == c->key) || ((key < c->key) && (c->l == (struct rhp_spn *)0))
	    || ((key > c->key) && (c->r == (struct rhp_spn *)0))) {
		if (key < n->key) {
			rhp_sp_sp_rl(&sp->root, n, c);
		} else {
			rhp_sp_sp_rr(&sp->root, n, c);
		}
		return;
	}

	if ((key < n->key) && (key < c->key)) {
		rhp_sp_sp_rl(&n->l, c, c->l);
		rhp_sp_sp_rl(&sp->root, n, n->l);
	} else if ((key > n->key) && (key > c->key)) {
		rhp_sp_sp_rr(&n->r, c, c->r);
		rhp_sp_sp_rr(&sp->root, n, n->r);
	} else if ((key < n->key) && (key > c->key)) {
		rhp_sp_sp_rr(&n->l, c, c->r);
		rhp_sp_sp_rl(&sp->root, n, n->l);
	} else if ((key > n->key) && (key < c->key)) {
		rhp_sp_sp_rl(&n->r, c, c->l);
		rhp_sp_sp_rr(&sp->root, n, n->r);
	} else {
		/* == handled at start of label */
	}

	goto label;
	return;
}

/* print to log */
static void rhp_log(char *format, ...)
{
	va_list ap;
	char *p = (char *)0;
	char *q = (char *)0;

	/* lines with '!' are printed on stderr, do a strchr() */
	p = format;

	q = (char *)0;
	while ((*p)) {
		if ((*p) == '!') {
			q = p;
		}
		p = (p + 1);
	}

	/* if a '!' found print on stderr */
	if (q) {
		va_start(ap, format);
		vfprintf(stderr, format, ap);
		va_end(ap);
		fflush(stderr);
	}

	if (rhp_dolog == 0) {
		/* no logging active */
		return;
	}

	if (rhp_logstream == NULL) {
		/* no stream to log to */
		return;
	}

	va_start(ap, format);
	vfprintf(rhp_logstream, format, ap);
	va_end(ap);

	fflush(rhp_logstream);

	return;
}

/* empty data inside order info */
static void rhp_empty_best_crossings_order(void)
{
	int level = 0;

	rhp_log("%s():\n", __func__);

	/* if no data nothing todo */
	if (rhp_best_crossings_order == (struct rhp_order_struct *)0) {
		rhp_log("%s(): no data\n", __func__);
		return;
	}

	/* number of nodes on level */
	rhp_best_crossings_order->num_nodes_on_layer =
	    (int *)rhp_free((void *)rhp_best_crossings_order->num_nodes_on_layer, __func__, __LINE__);

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		if (rhp_best_crossings_order->node_ptr_on_layer[level]) {
			rhp_best_crossings_order->node_ptr_on_layer[level] = (struct rhpnode * *)rhp_free((void *)
													  rhp_best_crossings_order->
													  node_ptr_on_layer[level],
													  __func__, __LINE__);
		}
	}

	/* nodes on layer */
	if (rhp_best_crossings_order->node_ptr_on_layer) {
		rhp_best_crossings_order->node_ptr_on_layer =
		    (struct rhpnode * **)rhp_free((void *)rhp_best_crossings_order->node_ptr_on_layer, __func__, __LINE__);
	}

	return;
}

/* empty data inside node list */
static void rhp_empty_sp_master_node_list(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;

	rhp_log("%s():\n", __func__);

	spn = rhp_sp_min(rhp_sp_master_node_list);

	while (spn) {
		nd = (struct rhpnode *)spn->value;

		/* edges connecting to this node */
		if (nd->up_edges) {
			nd->up_edges = rhp_free((void *)nd->up_edges, __func__, __LINE__);
			nd->up_degree = 0;
		}

		if (nd->down_edges) {
			nd->down_edges = rhp_free((void *)nd->down_edges, __func__, __LINE__);
			nd->down_degree = 0;
		}

		spn = rhp_sp_next(rhp_sp_master_node_list, spn->key);
	}

	/* sorted list */
	spn = rhp_sp_min(rhp_sp_master_node_list_sorted);

	while (spn) {
		(void)rhp_free((void *)spn->value, __func__, __LINE__);
		spn->value = (rhp_spval) 0;
		spn = rhp_sp_next(rhp_sp_master_node_list_sorted, spn->key);
	}

	return;
}

  /* empty data inside edge list */
static void rhp_empty_sp_master_edge_list(void)
{
	rhp_log("%s():\n", __func__);
	return;
}

/* empty edge crossing info */
static void rhp_empty_sp_between_layers(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;

	rhp_log("%s(): data is %d\n", __func__, rhp_sp_has_data(rhp_sp_between_layers));

	spn = rhp_sp_min(rhp_sp_between_layers);

	while (spn) {
		is = (struct rhp_inter_layer_struct *)spn->value;

		rhp_log("%s(): free eedges %p\n", __func__, (void *)is->eedges);

		/* */
		if (is->eedges) {
			is->eedges = rhp_free((void *)is->eedges, __func__, __LINE__);
		}

		spn = rhp_sp_next(rhp_sp_between_layers, spn->key);
	}

	return;
}

/* empty data inside layers */
static void rhp_empty_sp_layers(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int level = 0;
	int i = 0;

	rhp_log("%s(): %d levels to clear in sp %p\n", __func__, rhp_nlevels, (void *)rhp_sp_layers);

	/* only if there is layer data */
	if (rhp_sp_layers == NULL) {
		return;
	}

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		if (spn == (struct rhp_spn *)0) {
			/* if here is only 1 level with single nodes, no edges then oke to skip */
			/* only log message if there are sp_layers */
			if (rhp_nlevels > 1) {
				rhp_log("%s(): could not get data for level %d shouldnothappen!\n", __func__, level);
			}
			continue;
		}

		/* clear nodes in level */
		rl = (struct rhplevel *)spn->value;

		rhp_log("%s(): clear level %d with %d nodes %p\n", __func__, level, rl->number_of_nodes, (void *)rl->nodes);

		if (rl->nodes) {

			/* empty inside nodes */
			for (i = 0; i < rl->number_of_nodes; i++) {
				nd = rl->nodes[i];

				if (nd->up_degree) {
					nd->up_edges = rhp_free((void *)nd->up_edges, __func__, __LINE__);
					nd->up_degree = 0;
				}

				if (nd->down_degree) {
					nd->down_edges = rhp_free((void *)nd->down_edges, __func__, __LINE__);
					nd->down_degree = 0;
				}
			}

			rl->nodes = rhp_free((void *)rl->nodes, __func__, __LINE__);
			rl->number_of_nodes = 0;
		}

	}

	return;
}

/* alloc layers info structs and set number of nodes in level */
static void rhp_allocatelayers(void)
{
	int i = 0;
	int ii = 0;
	struct rhplevel *rl = (struct rhplevel *)0;
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhp_spn *spnn = (struct rhp_spn *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int level = 0;
	size_t bt = (size_t)0;

	/* overall count of nodes */
	rhp_number_of_nodes = 0;

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		return;
	}

	if (rhp_nlevels == 0) {
		rhp_log("%s(): no levels shouldnothappen!\n", __func__);
		return;
	}

	if (rhp_sp_layers != (struct rhp_sp *)0) {
		rhp_log("%s(): rhp_sp_layers %p shouldnothappen!\n", __func__, (void *)rhp_sp_layers);
	}

	/* layer data */
	rhp_sp_layers = rhp_sp_new(1);

	/* create empty layer info */
	for (i = 0; i < rhp_nlevels; i++) {
		rl = (struct rhplevel *)rhp_malloc(sizeof(struct rhplevel), __func__, __LINE__);
		bt = (bt + sizeof(struct rhplevel));
		rl->number_of_nodes = 0;
		rl->nodes = (struct rhpnode **)0;
		rhp_log("%s(): creating entry for level %d\n", __func__, i);
		rhp_sp_insert(rhp_sp_layers, (rhp_spkey) i, (rhp_spval) rl);
	}

	/* scan the nodes and update count of nodes in each level */
	spnn = rhp_sp_min(rhp_sp_master_node_list);

	while (spnn) {
		nd = (struct rhpnode *)spnn->value;

		level = nd->level;

		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		/* update count of nodes in level and add node */
		rl = (struct rhplevel *)spn->value;

		/* update count of nodes in this level */
		rl->number_of_nodes = (rl->number_of_nodes + 1);

		/* update overall count of nodes */
		rhp_number_of_nodes = (rhp_number_of_nodes + 1);

		rhp_log("%s(): now counted %d nodes in level %d total %d\n", __func__, rl->number_of_nodes, i, rhp_number_of_nodes);

		spnn = rhp_sp_next(rhp_sp_master_node_list, spnn->key);
	}

	/* */
	for (i = 0; i < rhp_nlevels; i++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) i);

		/* update count of nodes in level and add node */
		rl = (struct rhplevel *)spn->value;

		if (rl->number_of_nodes) {
			rhp_log("%s(): there are %d nodes in level %d\n", __func__, rl->number_of_nodes, i);
			rl->nodes = (struct rhpnode **)
			    rhp_malloc((rl->number_of_nodes * sizeof(struct rhpnode *)), __func__, __LINE__);
			bt = (bt + (rl->number_of_nodes * sizeof(struct rhpnode *)));
		} else {
			rhp_log("%s(): there are no nodes in level %d\n", __func__, i);
		}

		rl->number_of_nodes = 0;
	}

	/* put node data in levels */
	spnn = rhp_sp_min(rhp_sp_master_node_list);

	while (spnn) {
		nd = (struct rhpnode *)spnn->value;

		level = nd->level;

		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		if (spn == (struct rhp_spn *)0) {
			rhp_log("%s(): no spn level %d shouldnothappen!\n", __func__, level);
			return;
		}

		rl = (struct rhplevel *)spn->value;

		/* set node data */
		if (rl->nodes) {
			rl->nodes[rl->number_of_nodes] = nd;
			rl->number_of_nodes = (rl->number_of_nodes + 1);
		} else {
			rhp_log
			    ("%s(): should have been nodes[] for node %d level %d shouldnothappen!\n",
			     __func__, nd->innum, nd->level);
		}

		/* */
		spnn = rhp_sp_next(rhp_sp_master_node_list, spnn->key);
	}

	/* total count of nodes */
	i = 0;

	/* log end result */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		rl = (struct rhplevel *)spn->value;

		if (rl->number_of_nodes == 0) {
			if (0) {
				rhp_log("%s(): level %d has no nodes shouldnothappen!\n", __func__, level);
			}
		} else {
			rhp_log("%s(): level %d has %d nodes", __func__, level, rl->number_of_nodes);

			/* scan the nodes in this level */
			if (rl->nodes) {
				rhp_log("%s", " with numbers");
				for (ii = 0; ii < rl->number_of_nodes; ii++) {
					rhp_log(" %d", rl->nodes[ii]->innum);
				}
			}

			rhp_log("%s", "\n");
		}

		/* update total count of nodes in all levels */
		i = (i + rl->number_of_nodes);
	}

	rhp_log
	    ("%s(): in %d levels (0...%d) are %d nodes and %d number_of_nodes\n",
	     __func__, rhp_nlevels, rhp_maxlevel, i, rhp_number_of_nodes);
	rhp_log("%s(): using %" PRIu64 " bytes for the level data\n", __func__, (uint64_t) bt);

	return;
}

  /* handle edges */
static void rhp_allocateadjacencylists(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhpedge *re = (struct rhpedge *)0;
	struct rhpnode *upper_node = (struct rhpnode *)0;
	struct rhpnode *lower_node = (struct rhpnode *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	int level = 0;
	int pos = 0;
	int i = 0;
	size_t bt = (size_t)0;

	/* overall count of edges */
	rhp_number_of_edges = 0;

	if (rhp_sp_has_data(rhp_sp_master_edge_list) == 0) {
		/* no edges is oke */
		return;
	}

	/* scan edges */
	spn = rhp_sp_min(rhp_sp_master_edge_list);

	while (spn) {
		re = (struct rhpedge *)spn->value;

		/* overall count of edges */
		rhp_number_of_edges = (rhp_number_of_edges + 1);

		/* update node edge connect degree */
		if (re->fn->level > re->tn->level) {
			/* this should have been checked at edge creation */
			rhp_log("%s(): uppernode is above lowernode shouldnothappen!\n", __func__);
			upper_node = re->fn;
			lower_node = re->tn;
		} else {
			upper_node = re->tn;
			lower_node = re->fn;
		}

		/* update degrees */
		upper_node->down_degree = (upper_node->down_degree + 1);
		lower_node->up_degree = (lower_node->up_degree + 1);

		spn = rhp_sp_next(rhp_sp_master_edge_list, spn->key);
	}

	/* */
	bt = 0;

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		if (spn == (struct rhp_spn *)0) {
			rhp_log("%s(): no spn level %d shouldnothappen!\n", __func__, level);
			return;
		}

		/* start pos in level is 0 */
		pos = 0;

		/* scan nodes in level */
		rl = (struct rhplevel *)spn->value;

		if (rl->nodes) {

			for (i = 0; i < rl->number_of_nodes; i++) {
				nd = rl->nodes[i];

				/* set node initial position based on input order */
				nd->position = pos;

				rhp_log
				    ("%s(): node %d pos %d in level %d has up/down degree %d/%d\n",
				     __func__, nd->innum, pos, level, nd->up_degree, nd->down_degree);

				if (nd->up_degree) {
					nd->up_edges =
					    (struct rhpedge *
					     *)rhp_malloc((nd->up_degree * sizeof(struct rhpedge *)), __func__, __LINE__);
					bt = (bt + (nd->up_degree * sizeof(struct rhpedge *)));
				}

				if (nd->down_degree) {
					nd->down_edges =
					    (struct rhpedge *
					     *)rhp_malloc((nd->down_degree * sizeof(struct rhpedge *)), __func__, __LINE__);
					bt = (bt + (nd->down_degree * sizeof(struct rhpedge *)));
				}

				/* next pos in level */
				pos = (pos + 1);

				/* updated below */
				nd->up_degree = 0;
				nd->down_degree = 0;
			}

		}
	}

	rhp_log("%s(): using %" PRIu64
		" additional more bytes for the node data and total now %" PRIu64
		" bytes\n", __func__, (long long)bt, (long long)(bt + (rhp_number_of_nodes * sizeof(struct rhpnode))));

	/* add edge data to nodes */
	spn = rhp_sp_min(rhp_sp_master_edge_list);

	while (spn) {
		re = (struct rhpedge *)spn->value;

		/* */
		if (re->fn->level > re->tn->level) {
			/* this should have been checked at edge creation */
			rhp_log("%s(): uppernode is above lowernode shouldnothappen!\n", __func__);
			upper_node = re->fn;
			lower_node = re->tn;
		} else {
			upper_node = re->tn;
			lower_node = re->fn;
		}

		/* */
		upper_node->down_edges[upper_node->down_degree] = re;
		upper_node->down_degree = (upper_node->down_degree + 1);

		/* */
		lower_node->up_edges[lower_node->up_degree] = re;
		lower_node->up_degree = (lower_node->up_degree + 1);

		/* */
		spn = rhp_sp_next(rhp_sp_master_edge_list, spn->key);
	}

	/* */
	rhp_log("%s(): number_of_edges is %d\n", __func__, rhp_number_of_edges);

	/* scan nodes and print the connections */
	spn = rhp_sp_min(rhp_sp_master_node_list);

	while (spn) {
		nd = (struct rhpnode *)spn->value;

		rhp_log("%s(): node %d has up/down degree %d/%d", __func__, nd->innum, nd->up_degree, nd->down_degree);

		if (nd->up_edges) {

			rhp_log(" up connected with edge number");
			for (i = 0; i < nd->up_degree; i++) {
				re = (struct rhpedge *)nd->up_edges[i];
				rhp_log(" %d", re->innum);
			}

		}

		if (nd->down_edges) {

			rhp_log(" down connected with edge number");

			for (i = 0; i < nd->down_degree; i++) {
				re = (struct rhpedge *)nd->down_edges[i];
				rhp_log(" %d", re->innum);
			}

		}

		rhp_log("%s", "\n");

		/* */
		spn = rhp_sp_next(rhp_sp_master_node_list, spn->key);
	}

	return;
}

/* count nodes without connections */
static int rhp_countisolatednodes(void)
{
	struct rhpnode *nd = (struct rhpnode *)0;
	struct rhp_spn *spn = (struct rhp_spn *)0;
	int c = 0;

	rhp_number_of_isolated_nodes = 0;

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		/* no data */
		rhp_log("%s(): no nodes shouldnothappen!\n", __func__);
		return (0);
	}

	spn = rhp_sp_min(rhp_sp_master_node_list);

	while (spn) {
		nd = (struct rhpnode *)spn->value;

		if ((nd->up_degree == 0) && (nd->down_degree == 0)) {
			c = (c + 1);
		}

		spn = rhp_sp_next(rhp_sp_master_node_list, spn->key);
	}

	rhp_log("%s(): %d nodes without edge connections found\n", __func__, c);

	return (c);
}

/* init data for edge crossing counting */
static void rhp_initcrossings(void)
{
	int i = 0;
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;

	rhp_log("%s(): rhp_nlevels is %d\n", __func__, rhp_nlevels);

	if (rhp_nlevels == 0) {
		rhp_log("%s(): no levels shouldnothappen!\n", __func__);
		return;
	}

	for (i = 0; i < rhp_nlevels; i++) {
		is = rhp_makeinterlayer(i);
		rhp_sp_insert(rhp_sp_between_layers, (rhp_spkey) i, (rhp_spval) is);
	}

	return;
}

/* */
static struct rhp_inter_layer_struct *rhp_makeinterlayer(int upper_layer)
{
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;
	size_t bt = (size_t)0;

	/* fresh info for edge crossings */
	is = (struct rhp_inter_layer_struct *)
	    rhp_malloc(sizeof(struct rhp_inter_layer_struct), __func__, __LINE__);
	bt = (bt + (sizeof(struct rhp_inter_layer_struct)));

	/* */
	is->number_of_edges = rhp_count_down_edges(upper_layer);

	/* indicate unknown number of crossings in level 64bit */
	is->number_of_crossings = (int64_t) - 1;

	/* optional storage of edge ptr's */
	if (is->number_of_edges) {
		is->eedges = (struct rhpedge **)
		    rhp_malloc((is->number_of_edges * sizeof(struct rhpedge *)), __func__, __LINE__);
		bt = (bt + (is->number_of_edges * sizeof(struct rhpedge *)));
	}

	rhp_log("%s(): using %" PRIu64 " bytes for the interlevels\n", __func__, (long long)bt);

	return ((struct rhp_inter_layer_struct *)is);
}

/* */
static int rhp_count_down_edges(int layer_number)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *lv = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int count = 0;
	int i = 0;

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) layer_number);

	if (spn == (struct rhp_spn *)0) {
		rhp_log("%s(): no data for level %d shouldnothappen!\n", __func__, layer_number);
		return (0);
	}

	lv = (struct rhplevel *)spn->value;

	if (lv == (struct rhplevel *)0) {
		rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, layer_number);
		return (0);
	}

	/* */
	if (lv->nodes == (struct rhpnode **)0) {
		if (0) {
			rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", __func__, layer_number);
		}
		return (0);
	}

	/* */
	count = 0;

	/* scan nodes in this level */
	if (lv->nodes) {

		for (i = 0; i < lv->number_of_nodes; i++) {
			nd = lv->nodes[i];
			/* */
			count = (count + nd->down_degree);
		}

	}

	rhp_log("%s(): down_degree count is %d at level %d\n", __func__, count, layer_number);

	return (count);
}

/* */
static void rhp_updateallcrossings(void)
{
	int i = 0;
	struct rhp_spn *spnb = (struct rhp_spn *)0;
	struct rhp_inter_layer_struct *is = NULL;

	/* update node positions */
	rhp_updateallpositions();

	/* make sure crossing count is preset to 0 */
	for (i = 1; i < rhp_nlevels; i++) {

		/* */
		spnb = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) i);

		if (spnb) {
			is = (struct rhp_inter_layer_struct *)spnb->value;
			is->number_of_crossings = 0;
		} else {
			rhp_log("%s(): could not find level %d shouldnothappen!\n", __func__, i);
		}

	}

	for (i = 1; i < rhp_nlevels; i++) {
		/* update at every level total number of edge crossings */
		rhp_updatecrossingsbetweenlayers(i);
	}

	return;
}

/* */
static void rhp_updateallpositions(void)
{
	int i = 0;

	rhp_log("%s(): updating all node positions in %d levels\n", __func__, rhp_nlevels);

	for (i = 0; i < rhp_nlevels; i++) {
		rhp_updatenodepositions(i);
	}

	return;
}

/* */
static void rhp_updatenodepositions(int layer_number)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *lv = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int pos = 0;
	int i = 0;

	rhp_log("%s(): updating node positions for level %d\n", __func__, layer_number);

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) layer_number);

	if (spn == (struct rhp_spn *)0) {
		if (0) {
			rhp_log("%s(): no data for level %d shouldnothappen!\n", __func__, layer_number);
		}
		return;
	}

	/* */
	lv = (struct rhplevel *)spn->value;

	if (lv == (struct rhplevel *)0) {
		rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, layer_number);
		return;
	}

	/* */
	if (lv->nodes == (struct rhpnode **)0) {
		if (0) {
			rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", __func__, layer_number);
		}
		return;
	}

	/* */
	pos = 0;

	/* scan nodes in this level */
	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];
		/* position within layer */
		nd->position = pos;
		rhp_log("%s(): node %d level %d pos %d weight %d\n", __func__, nd->innum, nd->level, nd->position, nd->weight);
		pos = (pos + 1);
	}

	return;
}

/* */
static void rhp_updatecrossingsforlayer(int layer)
{

	rhp_updatenodepositions(layer);

	/* this is correct */
	if (layer > 0) {
		rhp_updatecrossingsbetweenlayers(layer);
	}

	/* */
	if (layer < (rhp_nlevels - 1)) {
		rhp_updatecrossingsbetweenlayers(layer + 1);
	}

	return;
}

/* */
static void rhp_updatecrossingsbetweenlayers(int upper_layer)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhp_spn *spnb = (struct rhp_spn *)0;
	struct rhplevel *lv = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;
	int ix = 0;
	int i = 0;
	int ii = 0;
	int64_t ncross = (int64_t) 0;

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) upper_layer);

	if (spn == (struct rhp_spn *)0) {
		if (0) {
			rhp_log("%s(): no data for level %d shouldnothappen!\n", __func__, upper_layer);
		}
		return;
	}

	/* */
	lv = (struct rhplevel *)spn->value;

	if (lv == (struct rhplevel *)0) {
		rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, upper_layer);
		return;
	}

	/* */
	if (lv->nodes == (struct rhpnode **)0) {
		if (0) {
			rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", __func__, upper_layer);
		}
		/* */
		spnb = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) upper_layer);

		if (spnb) {
			is = (struct rhp_inter_layer_struct *)spnb->value;
			ncross = 0;
			is->number_of_crossings = ncross;
		} else {
			rhp_log("%s(): could not find level %d in between_layers shouldnothappen!\n", __func__, upper_layer);
		}
		return;
	}

	/* */
	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];

		/* only sort if there is something to sort */
		if (nd->down_degree > 1) {
			rhp_sortbydownnodeposition(nd->down_edges, nd->down_degree);
		}

		/* */
		if (nd->down_degree > 0) {
			spnb = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) upper_layer);

			if (spnb) {
				is = (struct rhp_inter_layer_struct *)spnb->value;
				/* copy from between->edges to node->down_edges node->down_degree items starting with index ix */
				rhp_add_edges_to_array(is->eedges, nd->down_edges, nd->down_degree, ix);
			}

		}

		/* */
		ix = (ix + nd->down_degree);
	}

	/* init */
	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];

		nd->down_crossings = (int64_t) 0;

		if (nd->down_degree > 0) {
			for (ii = 0; ii < nd->down_degree; ii++) {
				nd->down_edges[ii]->crossings = (int64_t) 0;
			}
		}

	}

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) (upper_layer - 1));

	if (spn == (struct rhp_spn *)0) {
		if (0) {
			rhp_log("%s(): no data for level %d shouldnothappen!\n", __func__, (upper_layer - 1));
		}
		return;
	}

	/* */
	lv = (struct rhplevel *)spn->value;

	if (lv == (struct rhplevel *)0) {
		rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, (upper_layer - 1));
		return;
	}

	/* */
	if (lv->nodes == (struct rhpnode **)0) {
		if (0) {
			rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", __func__, (upper_layer - 1));
		}
		return;
	}

	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];
		nd->up_crossings = (int64_t) 0;
	}

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) (upper_layer));

	if (spn == (struct rhp_spn *)0) {
		if (0) {
			rhp_log("%s(): no data for level %d shouldnothappen!\n", (upper_layer));
		}
		return;
	}

	/* */
	lv = (struct rhplevel *)spn->value;

	rhp_log("%s(): level %d has %d nodes:\n", __func__, upper_layer, lv->number_of_nodes);

	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];

		rhp_log("%s():   node %d down-degree %d connected to edges:", __func__, nd->innum, nd->down_degree);

		if (nd->down_degree > 0) {
			for (ii = 0; ii < nd->down_degree; ii++) {
				rhp_log(" %d", nd->down_edges[ii]->innum);
			}
		}

		rhp_log("%s", "\n");
	}

	/* */
	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) (upper_layer - 1));

	if (spn == (struct rhp_spn *)0) {
		if (0) {
			rhp_log("%s(): no data for level %d shouldnothappen!\n", (upper_layer - 1));
		}
		return;
	}

	/* */
	lv = (struct rhplevel *)spn->value;

	if (lv == (struct rhplevel *)0) {
		rhp_log("%s(): no nodes in level %d shouldnothappen!\n", (upper_layer - 1));
		return;
	}

	/* */
	if (lv->nodes == (struct rhpnode **)0) {
		if (0) {
			rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", (upper_layer - 1));
		}
		return;
	}

	rhp_log("%s(): level %d has %d nodes:", __func__, (upper_layer - 1), lv->number_of_nodes);

	for (i = 0; i < lv->number_of_nodes; i++) {
		nd = lv->nodes[i];
		rhp_log(" %d", nd->innum);
	}

	rhp_log("%s", "\n");

	/* */
	spnb = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) upper_layer);

	if (spnb) {
		is = (struct rhp_inter_layer_struct *)spnb->value;
		ncross = rhp_count_inversions_down(is->eedges, is->number_of_edges, 1);

		is->number_of_crossings = ncross;
	} else {
		rhp_log("%s(): could not find level %d in between_layers shouldnothappen!\n", __func__, upper_layer);
	}

	rhp_log("%s(): %" PRIi64 " crossings at level %d\n", __func__, (int64_t) ncross, upper_layer);

	return;
}

/* */
static int rhp_compare_down_edges(const void *ptr_i, const void *ptr_j)
{
	struct rhpedge **entry_ptr_i = (struct rhpedge * *)0;
	struct rhpedge **entry_ptr_j = (struct rhpedge * *)0;
	struct rhpedge *edge_i = (struct rhpedge *)0;
	struct rhpedge *edge_j = (struct rhpedge *)0;
	entry_ptr_i = (struct rhpedge * *)ptr_i;
	entry_ptr_j = (struct rhpedge * *)ptr_j;
	edge_i = *entry_ptr_i;
	edge_j = *entry_ptr_j;

	/* possible here to abs() and compare and return 0 at almost at same pos */

	/* position is an int */
	if (edge_i->down_node->position > edge_j->down_node->position) {
		return (1);
	} else if (edge_i->down_node->position < edge_j->down_node->position) {
		return (-1);
	} else {
		/* == pos */
		return (0);
	}
}

/* */
static void rhp_sortbydownnodeposition(struct rhpedge **edge_array, int num_edges)
{

	/* there can be multiple entries with same pos as key */
	qsort(edge_array, num_edges, sizeof(struct rhpedge *), rhp_compare_down_edges);

	return;
}

/* copy to edge_array from edges_to_add num_edges items starting at offset start_pos in edge_array */
static void rhp_add_edges_to_array(struct rhpedge **edge_array, struct rhpedge **edges_to_add, int num_edges, int start_pos)
{
	int edges_added = 0;

	if (num_edges <= 0) {
		rhp_log("%s(): %d num_edges is too low shouldnothappen!\n", __func__, num_edges);
		return;
	}

	for (edges_added = 0; edges_added < num_edges; edges_added++) {
		edge_array[(start_pos + edges_added)] = edges_to_add[edges_added];
	}

	return;
}

/* diff=1 means increment edge crossing count with 1 at every edge crossing */
static int64_t rhp_count_inversions_down(struct rhpedge **edge_array, int num_of_edges, int diff)
{
	int64_t number_of_inversions = (int64_t) 0;
	int i = 0;

	/* for every edge */
	for (i = 1; i < num_of_edges; i++) {
		/* now start at eedges[i] position and increment edge crossing count with 1 */
		number_of_inversions = (number_of_inversions + rhp_insert_and_count_inversions_down(edge_array, i, diff));
	}

	return ((int64_t) number_of_inversions);
}

/* at every edge */
static int64_t rhp_insert_and_count_inversions_down(struct rhpedge **edge_array, int starting_index, int diff)
{
	int64_t number_of_crossings = (int64_t) 0;
	int ix = 0;
	struct rhpedge *edge_to_insert = (struct rhpedge *)0;
	struct rhpedge *edge_one = (struct rhpedge *)0;
	struct rhpedge *edge_two = (struct rhpedge *)0;
	struct rhpnode *up_node_one = (struct rhpnode *)0;
	struct rhpnode *up_node_two = (struct rhpnode *)0;
	struct rhpnode *down_node_one = (struct rhpnode *)0;
	struct rhpnode *down_node_two = (struct rhpnode *)0;

	/* crossings at this edge */
	number_of_crossings = (int64_t) 0;

	/* check param */
	if (starting_index <= 0) {
		rhp_log("%s(): starting_index is %d shouldnothappen!\n", __func__, starting_index);
		return ((int64_t) number_of_crossings);
	}

	/* */
	ix = (starting_index - 1);

	/* */
	edge_to_insert = edge_array[starting_index];

	/* check param */
	if (edge_array[ix] == (struct rhpedge *)0) {
		rhp_log("%s(): edge_array[%d] is nil and starting_index is %d shouldnothappen!\n", __func__, ix, starting_index);
		return ((int64_t) number_of_crossings);
	}

	/* compare the position of the edges */
	while ((ix >= 0)
	       && (edge_array[ix]->down_node->position > edge_to_insert->down_node->position)) {
		/* one more edge crossing */
		number_of_crossings = (number_of_crossings + 1);

		/* */
		edge_one = edge_array[ix];
		edge_two = edge_to_insert;

		/* */
		edge_one->crossings += diff;
		edge_two->crossings += diff;

		/* */
		up_node_one = edge_one->up_node;
		up_node_two = edge_two->up_node;

		/* */
		down_node_one = edge_one->down_node;
		down_node_two = edge_two->down_node;

		/* */
		up_node_one->down_crossings = (up_node_one->down_crossings + diff);
		up_node_two->down_crossings = (up_node_two->down_crossings + diff);

		/* */
		down_node_one->up_crossings = (down_node_one->up_crossings + diff);
		down_node_two->up_crossings = (down_node_two->up_crossings + diff);

		/* */
		edge_array[(ix + 1)] = edge_array[ix];

		/* until 0 */
		ix = (ix - 1);
	}

	edge_array[ix + 1] = edge_to_insert;

	rhp_log("%s() at edge %d are %" PRIi64 " crossings\n", __func__, edge_to_insert->innum, number_of_crossings);

	return ((int64_t) number_of_crossings);
}

/* sum in all levels total number of edge crossings determinated in rhp_updateallcrossings() */
static int64_t rhp_numberofcrossings(void)
{
	struct rhp_spn *spnb = (struct rhp_spn *)0;
	struct rhp_inter_layer_struct *is = (struct rhp_inter_layer_struct *)0;
	int i = 1;
	int64_t crossings = 0;

	/* if there is only 1 level there cannot be crossing edges */
	if (rhp_nlevels < 2) {
		rhp_log("%s(): graph has no edge crossings because low number of levels which is %d\n", __func__, rhp_nlevels);
		return (0);
	}

	/* if there is only 1 or 0 edges then there cannot be crossing edges */
	if (rhp_number_of_edges < 2) {
		rhp_log
		    ("%s(): graph has no edge crossings because low number of edge which is %d\n", __func__, rhp_number_of_edges);
		return (0);
	}

	for (i = 1; i < rhp_nlevels; i++) {
		/* */
		spnb = rhp_sp_lookup(rhp_sp_between_layers, (rhp_spkey) i);

		if (spnb) {
			is = (struct rhp_inter_layer_struct *)spnb->value;
			crossings = (crossings + is->number_of_crossings);
		} else {
			rhp_log("%s(): could not find level %d shouldnothappen!\n", __func__, i);
		}

	}

	rhp_log("%s(): graph has %" PRIi64
		" edge crossings in %d levels and %d edges\n", __func__, crossings, rhp_nlevels, rhp_number_of_edges);

	return ((int64_t) crossings);
}

/****zz2****/

/* init save layout order */
static void rhp_order_init(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	int level = 0;
	size_t tb = (size_t)0;

	rhp_log("%s(): rhp_nlevels is %d\n", __func__, rhp_nlevels);

	/* main info */
	rhp_best_crossings_order = (struct rhp_order_struct *)rhp_malloc(sizeof(struct rhp_order_struct), __func__, __LINE__);
	tb = (tb + sizeof(struct rhp_order_struct));

	/* how many levels */
	rhp_best_crossings_order->num_layers = rhp_nlevels;

	/* how many nodes in every level */
	rhp_best_crossings_order->num_nodes_on_layer = (int *)rhp_malloc((rhp_nlevels * sizeof(int)), __func__, __LINE__);
	tb = (tb + (rhp_nlevels * sizeof(int)));

	/* nodes on level */
	rhp_best_crossings_order->node_ptr_on_layer =
	    (struct rhpnode * **)rhp_malloc((rhp_nlevels * sizeof(struct rhpnode **)), __func__, __LINE__);
	tb = (tb + (rhp_nlevels * sizeof(struct rhpnode **)));

	if (rhp_sp_has_data(rhp_sp_layers) == 0) {
		/* if there is only 1 level with single nodes, no edges then nlevels is 1 and this is oke. */
		if (rhp_nlevels > 1) {
			rhp_log("%s(): there is no level data for %d levels shouldnothappen!\n", __func__, rhp_nlevels);
		}
		return;
	}

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		/* nodes in level */
		if (spn == (struct rhp_spn *)0) {
			rhp_log
			    ("%s(): could not get data for level %d in sp_layers=%p shouldnothappen!\n",
			     __func__, level, (void *)rhp_sp_layers);
			continue;
		}

		/* level data */
		rl = (struct rhplevel *)spn->value;

		rhp_best_crossings_order->num_nodes_on_layer[level] = rl->number_of_nodes;

		/* only if there are nodes in level which normally is so. */
		if (rl->number_of_nodes) {
			/* fresh buffer */
			rhp_best_crossings_order->node_ptr_on_layer[level] =
			    (struct rhpnode * *)rhp_malloc((rl->number_of_nodes * sizeof(struct rhpnode *)), __func__, __LINE__);
			tb = (tb + (rl->number_of_nodes * sizeof(struct rhpnode *)));
		}

	}

	/* create initial copy of the node status */
	rhp_save_order();

	rhp_log("%s(): using %" PRIu64 " bytes for the order data\n", __func__, (long long)tb);

	return;
}

/* mirror node setting in backup */
static void rhp_save_order(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int level = 0;
	int i = 0;

	/* how many levels */
	rhp_best_crossings_order->num_layers = rhp_nlevels;

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		if (spn == (struct rhp_spn *)0) {
			rhp_log("%s(): could not get data for level %d shouldnothappen!\n", __func__, level);
			continue;
		}

		/* nodes in level */
		rl = (struct rhplevel *)spn->value;

		rhp_log("%s(): level %d has nodes:", __func__, level);

		/* scan all nodes in this level */
		for (i = 0; i < rl->number_of_nodes; i++) {
			/* get node from layout level */
			nd = rl->nodes[i];
			/* copy node into backup */
			rhp_best_crossings_order->node_ptr_on_layer[level][i] = nd;
			rhp_log(" %d", nd->innum);
		}
		rhp_log("\n");
	}

	return;
}

/* mirror backup setting to nodes */
static void rhp_restore_order(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	int level = 0;
	int i = 0;

	rhp_log("%s(): \n", __func__);

	/* how many levels */
	rhp_best_crossings_order->num_layers = rhp_nlevels;

	/* scan the levels */
	for (level = 0; level < rhp_nlevels; level++) {
		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

		/* nodes in level */
		if (spn == (struct rhp_spn *)0) {
			rhp_log("%s(): could not get data for level %d shouldnothappen!\n", __func__, level);
			continue;
		}

		/* level data */
		rl = (struct rhplevel *)spn->value;

		/* scan all nodes in this level */
		for (i = 0; i < rl->number_of_nodes; i++) {
			/* get node from layout level */
			nd = rhp_best_crossings_order->node_ptr_on_layer[level][i];
			/* copy node from backup */
			rl->nodes[i] = nd;
			/* set node position */
			nd->position = i;
		}

	}

	return;
}

/****zz3****/

/* */
static void rhp_barycenter(void)
{
	int64_t redu = (int64_t) 0;

	/* maxiter can be made better depending on levels, nodes+edge etc and/or configurable */
	rhp_iter = 0;
	rhp_maxiter = 255;

	rhp_log("%s(): starting barycenter with %" PRIi64 " edge crossings at start\n", __func__, rhp_start_crossings);

	/* at least once */
	do {

		/* return if max iterations have been reached */
		if (rhp_barycenterupsweep(1, (rhp_nlevels - 2))) {
			return;
		}

		if (rhp_barycenterdownsweep(1, (rhp_nlevels - 2))) {
			return;
		}

	}
	while (rhp_terminate() == 0 /* false */ );

	/* */
	rhp_log("%s(): ending barycenter with %" PRIi64
		" edge crossings and started with %" PRIi64
		" edge crossings at start\n", __func__, rhp_crossings, rhp_start_crossings);

	/* calculate percentage of edge crossing reduction */
	if (rhp_start_crossings) {
		redu = ((100 * rhp_crossings) / rhp_start_crossings);
		redu = (100 - redu);
	} else {
		redu = 0;
	}

	rhp_log("%s(): reduced edge crossings with %" PRIi64 " percent from %"
		PRIi64 "->%" PRIi64 "\n", __func__, redu, rhp_start_crossings, rhp_crossings);

	return;
}

/* return 1 to stop barycenter main sweeping */
static int rhp_terminate(void)
{
	uint64_t redu = (uint64_t) 0;
	int64_t rhp_cur_crossings = (int64_t) 0;
	int status = 0;
	int better = 0;

	/* get current number of crossings */
	rhp_cur_crossings = rhp_numberofcrossings();

	/* update iteration count */
	rhp_iter = (rhp_iter + 1);

	rhp_log("%s(): changed from %" PRIi64 " to %" PRIi64 " crossings\n", __func__, rhp_crossings, rhp_cur_crossings);

	if (rhp_cur_crossings < rhp_crossings) {
		/* better */
		better = 1;
		rhp_improvements = (rhp_improvements + 1);
	} else {
		better = 0;
		rhp_notimprovements = (rhp_notimprovements + 1);
	}

	/* run callback routine if set */
	if (rhp_getlayoutdata) {
		/* calculate percentage of edge crossing reduction */
		if (rhp_crossings) {
			redu = ((100 * rhp_cur_crossings) / rhp_crossings);
			redu = (100 - redu);
		} else {
			redu = 0;
		}

		/* run the callback */
		status =
		    rhp_getlayoutdata(rhp_iter, rhp_maxiter, rhp_cur_crossings,
				      rhp_crossings, redu, better, rhp_improvements, rhp_notimprovements);

		/* if to stop */
		if (status) {
			rhp_log
			    ("%s(): stop barycenter because status %d from callback routine at %"
			     PRIu64 " crossings\n", __func__, status, rhp_cur_crossings);
			/* save this status */
			rhp_save_order();
			/* set current crossings */
			rhp_crossings = rhp_cur_crossings;
			/* stop barycenter */
			return (1);
		}
	}

	/* stop if no crossings anymore */
	if ((rhp_cur_crossings == 0) || (rhp_crossings == 0)) {
		rhp_log("%s(): stop barycenter because of no edge crossings cur=%"
			PRIu64 " old=%" PRIu64 "\n", __func__, rhp_cur_crossings, rhp_crossings);
		/* save this status */
		rhp_save_order();
		/* set current crossings */
		rhp_crossings = rhp_cur_crossings;
		/* stop barycenter */
		return (1);
	}

	/* this can be done better on amount of change,
	 * avg. number of crossings per level or
	 * low cross count compared to nodes+edge
	 * or configurable setting
	 * or sweep level range can be changed here for the next sweeps
	 * to limit to a specific difficult part
	 * or other barycenter params can be changed on-the-fly
	 * etc.
	 */

	if (rhp_crossings > rhp_cur_crossings) {
		/* now less crossings save this status */
		rhp_save_order();
		/* set current crossings */
		rhp_crossings = rhp_cur_crossings;
		/* check if no crossings anymore */
		if (rhp_crossings == 0) {
			/* stop barycenter */
			return (1);
		}

		/* check if max iteration reached */
		if (rhp_iter > rhp_maxiter) {
			/* stop barycenter */
			return (1);
		} else {
			/* continue barycenter */
			return (0);
		}
	} else {
		if (rhp_crossings != rhp_cur_crossings) {
			/* now more crossings and continue with saved best status */
			rhp_restore_order();
		} else {
			rhp_save_order();
		}
		/* check if max iteration reached */
		if (rhp_iter > rhp_maxiter) {
			/* stop barycenter */
			return (1);
		}

		/* continue barycenter */
		return (0);
	}
}

/* return 1 to stop barycenter single sweep */
static int rhp_end_of_iteration(void)
{
	/* no stop here to allow bot up+down to run */
	return (0);
}

/* sweep from lo to hi level */
static int rhp_barycenterupsweep(int lowlevel, int hilevel)
{
	int layer = 0;
	int nadj = 0;

	for (layer = lowlevel; layer < hilevel; layer++) {
		nadj = 0;

		/* set node weight */
		nadj = rhp_barycenterweights(layer, 0 /* DOWNWARD */ );

		if (nadj) {
			/* there are nodes weight (-1) to adjust */
			rhp_barycenterweights_adjust(layer, 0 /* DOWNWARD */ );
		}

		/* sort depending on node weight */
		rhp_layersort(layer);

		/* get number of edge crossings */
		rhp_updatecrossingsforlayer(layer);

		if (rhp_end_of_iteration()) {
			/* stop main barycenter sweeps */
			return (1);	/* true */
		}

	}

	/* return 0 to keep sweeping */
	return (0);
}

/* sweep from hi to lo level */
static int rhp_barycenterdownsweep(int lowlevel, int hilevel)
{
	int layer = 0;
	int nadj = 0;

	/* also to layer==0 */
	for (layer = hilevel; layer >= (lowlevel - 1); layer--) {
		nadj = 0;

		/* set node weights */
		nadj = rhp_barycenterweights(layer, 1 /* UPWARD */ );

		if (nadj) {
			/* there are nodes weight (-1) to adjust */
			rhp_barycenterweights_adjust(layer, 1 /* UPWARD */ );
		}

		/* sort nodes depending on weight */
		rhp_layersort(layer);

		/* get edge crossing count */
		rhp_updatecrossingsforlayer(layer);

		if (rhp_end_of_iteration()) {
			/* stop main barycenter sweeps */
			return (1);	/* true */
		}

	}

	/* return 0 to keep sweeping */
	return (0);
}

/*
 * 0 is orientation DOWNWARD
 * 1 is orientation UPWARD
 */
static int rhp_barycenterweights(int level, int orientation)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	int i = 0;
	int n_node_adjust = 0;

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

	if (spn == (struct rhp_spn *)0) {
		rhp_log("%s(): could not find data for level %d shouldnothappen!\n", __func__, level);
		return (0);
	}

	rl = (struct rhplevel *)spn->value;

	rhp_log("%s(): weights for %d nodes in level %d mode %d\n", __func__, rl->number_of_nodes, level, orientation);

	/* number of node which need adjust */
	n_node_adjust = 0;

	for (i = 0; i < rl->number_of_nodes; i++) {
		/* for every node in this level new weight */
		rhp_node_weight(rl->nodes[i], orientation);

		/* check node weight set */
		if (rl->nodes[i]->weight == (int)(-1)) {
			/* this node needs adjust */
			n_node_adjust = (n_node_adjust + 1);
		}
	}

	if (n_node_adjust) {
		rhp_log
		    ("%s(): iteration %d %d nodes need adjust from %d nodes in level %d mode %d\n",
		     __func__, rhp_iter, n_node_adjust, rl->number_of_nodes, level, orientation);
	}

	/* set number of node adjustments todo */
	rl->number_adjustments = n_node_adjust;

	return (n_node_adjust);
}

/* adjust nodes with weight (-1) */
static void rhp_barycenterweights_adjust(int level, int orientation)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;
	struct rhpnode *node = (struct rhpnode *)0;
	int number_of_weights = 0;
	int total_weight = 0;
	int i = 0;

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

	if (spn == (struct rhp_spn *)0) {
		rhp_log("%s(): could not find data for level %d shouldnothappen!\n", __func__, level);
		return;
	}

	rl = (struct rhplevel *)spn->value;

	rhp_log
	    ("%s(): to adjust %d weights for %d nodes in level %d orientation %d\n",
	     __func__, number_of_weights, rl->number_of_nodes, level, orientation);

	for (i = 0; i < rl->number_of_nodes; i++) {

		/* adjust if -1 weight based on avg */
		if (rl->nodes[i]->weight == (int)(-1)) {
			node = rl->nodes[i];

			/* if set to 1 do avg mode, else left mode */
			if (rhp_adjustweight) {

				/* */
				number_of_weights = 0;
				total_weight = 0;

				if (i <= 0) {
					/* */
				}

				if (i > 0) {
					number_of_weights = (number_of_weights + 1);
					total_weight = (total_weight + rl->nodes[i - 1]->weight);
				}

				if ((i < (rl->number_of_nodes - 1))
				    && (rl->nodes[i + 1]->weight >= 0)) {
					number_of_weights = (number_of_weights + 1);
					total_weight = (total_weight + rl->nodes[i + 1]->weight);
				}

				if (number_of_weights > 0) {
					node->weight = (100 * total_weight);
					node->weight = (int)(node->weight / number_of_weights);
				} else {
					/* leftmost node has a right neighbor with weight of -1 */
					node->weight = 0;
				}

				rhp_log("%s(): adjusted node[%d] weight from -1 to %d (avg mode)\n", __func__, i, node->weight);
			} else {
				/* left mode */

				if (i <= 0) {
					/* do not go more left then minimum 0 */
					node->weight = 0;
				} else {
					/* take weight of node left from this one */
					node->weight = rl->nodes[i - 1]->weight;
				}

				rhp_log("%s(): adjusted node[%d] weight from -1 to %d (leftish mode)\n", __func__, i, node->weight);
			}

		}

	}

	return;
}

/*
 * 0 is orientation DOWNWARD
 * 1 is orientation UPWARD
 */
static void rhp_node_weight(struct rhpnode *node, int orientation)
{
	int total_degree1 = 0;
	int total_degree2 = 0;
	int total_degree = 0;
	int total_of_positions = 0;
	int adj_index = 0;

	/* this influences positioning and can be done better */
	rhp_log("%s(): at node %d up degree %d down degree %d mode %d\n", __func__,
		node->innum, node->up_degree, node->down_degree, orientation);

	if ((node->up_degree + node->down_degree) == 0) {
		/* isolated nodes to the far left */
		node->weight = 0;
		rhp_log("%s(): node %d has weight set (0) isolated node special mode %d\n", __func__, node->innum, orientation);
		return;
	}

	if (orientation != 1 /* UPWARD */ ) {
		/* is DOWNWARD, BOTH, NONE */
		total_degree1 = node->down_degree;
		for (adj_index = 0; adj_index < node->down_degree; adj_index++) {
			total_of_positions = (total_of_positions + node->down_edges[adj_index]->down_node->position);
		}
	}

	if (orientation != 0 /* DOWNWARD */ ) {
		/* is UPWARD, BOTH, NONE */
		total_degree2 = node->up_degree;
		for (adj_index = 0; adj_index < node->up_degree; adj_index++) {
			total_of_positions = (total_of_positions + node->up_edges[adj_index]->up_node->position);
		}
	}

	/* */
	total_degree = (total_degree1 + total_degree2);

	/* */
	if (total_degree > 0) {
		node->weight = (100 * total_of_positions);
		node->weight = (int)(node->weight / total_degree);
	} else {
		/* special: no edges in the given orientation and needs to be fixed later on based on avg etc. */
		node->weight = (int)(-1);
		rhp_log
		    ("%s(): node %d has weight set (-1) special degree=(%d+%d) mode %d\n",
		     __func__, node->innum, total_degree1, total_degree2, orientation);
	}

	rhp_log("%s(): node %d has now weight %d mode %d\n", __func__, node->innum, node->weight, orientation);

	return;
}

/* sort on the (double) weight of a node, same weight may happen more then pnce */
static int rhp_compare_weights(const void *ptr_i, const void *ptr_j)
{
	struct rhpnode **entry_ptr_i = (struct rhpnode **)0;
	struct rhpnode **entry_ptr_j = (struct rhpnode * *)0;
	struct rhpnode *node_i = (struct rhpnode *)0;
	struct rhpnode *node_j = (struct rhpnode *)0;
	int diff = 0;
	entry_ptr_i = (struct rhpnode * *)ptr_i;
	entry_ptr_j = (struct rhpnode **)ptr_j;
	node_i = *entry_ptr_i;
	node_j = *entry_ptr_j;

	/* a abs() to compare if are almost the same */
	diff = (node_i->weight > node_j->weight);

	if (diff < 0) {
		diff = (int)(0 - diff);
	}

	if (diff < 1) {
		/* +/- 1 considered same */
		return (0);
	}

	if (node_i->weight > node_j->weight) {
		return (1);
	} else if (node_i->weight < node_j->weight) {
		return (-1);
	} else {
		return (0);
	}
}

/* */
static void rhp_layersort(int level)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *rl = (struct rhplevel *)0;

	spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) level);

	if (spn == (struct rhp_spn *)0) {
		rhp_log("%s(): could not find data for level %d shouldnothappen!\n", __func__, level);
		return;
	}

	rl = (struct rhplevel *)spn->value;

	/* sort depending on node weight */
	qsort(rl->nodes, rl->number_of_nodes, sizeof(struct rhpnode *), rhp_compare_weights);

	/* set the new node positions */
	rhp_updatenodepositions(level);

	rhp_log("%s(): sorted level %d and updated node positions\n", __func__, level);

	return;
}

/* create new sorted nodelist */
static void rhp_sorted_nodelist(void)
{
	struct rhp_spn *spn = (struct rhp_spn *)0;
	struct rhplevel *lv = (struct rhplevel *)0;
	struct rhpnode *nd = (struct rhpnode *)0;
	struct rhpnode *nn = (struct rhpnode *)0;
	int i = 0;
	int ii = 0;
	int num = 0;

	rhp_log("%s(): %d levels\n", __func__, rhp_nlevels);

	if (rhp_nlevels == 0) {
		rhp_log("%s(): no levels shouldnothappen!\n", __func__);
		return;
	}

	if (rhp_sp_has_data(rhp_sp_master_node_list) == 0) {
		rhp_log("%s(): no node data shouldnothappen!\n", __func__);
		return;
	}

	/* special case: only nodes in 1 level 0 */
	if (rhp_nlevels == 1) {
		num = 0;

		rhp_sp_master_node_list_sorted = rhp_sp_new(1);

		spn = rhp_sp_min(rhp_sp_master_node_list);

		while (spn) {
			nd = (struct rhpnode *)spn->value;

			rhp_log("%s(): node %d level %d pos %d\n", __func__, nd->innum, nd->level, nd->position);

			/* create fresh node data info */
			nn = (struct rhpnode *)rhp_malloc(sizeof(struct rhpnode), __func__, __LINE__);

			/* set the info n */
			nn->num = num;
			nn->innum = nd->innum;
			nn->level = nd->level;
			nn->data = nd->data;
			nn->position = nd->position;
			nn->up_degree = nd->up_degree;
			nn->down_degree = nd->down_degree;
			nn->up_edges = nd->up_edges;
			nn->down_edges = nd->down_edges;
			nn->weight = nd->weight;
			nn->up_crossings = nd->up_crossings;
			nn->down_crossings = nd->down_crossings;

			rhp_log("%s(): node %d level %d pos %d weight %d at %d\n",
				__func__, nd->innum, nd->level, nd->position, nd->weight, num);

			/* insert node in database indexed on position number */
			rhp_sp_insert(rhp_sp_master_node_list_sorted, (splay_tree_key) num, (splay_tree_value) nn);

			num = (num + 1);

			spn = rhp_sp_next(rhp_sp_master_node_list, spn->key);
		}

		return;
	}

	/* multi level drawing */
	num = 0;

	rhp_sp_master_node_list_sorted = rhp_sp_new(1);

	for (i = 0; i < rhp_nlevels; i++) {

		spn = rhp_sp_lookup(rhp_sp_layers, (rhp_spkey) i);

		if (spn == (struct rhp_spn *)0) {
			if (0) {
				rhp_log("%s(): no data for level %d shouldnothappen!\n", __func__, i);
			}
			continue;
		}

		/* */
		lv = (struct rhplevel *)spn->value;

		if (lv == (struct rhplevel *)0) {
			rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, i);
			continue;
		}

		/* */
		if (lv->nodes == (struct rhpnode **)0) {
			if (0) {
				rhp_log("%s(): no data for nodes in level %d shouldnothappen!\n", __func__, i);
			}
			continue;
		}

		if (lv->number_of_nodes == 0) {
			rhp_log("%s(): no nodes in level %d shouldnothappen!\n", __func__, i);
			continue;
		}

		/* scan nodes in this level */
		for (ii = 0; ii < lv->number_of_nodes; ii++) {
			nd = lv->nodes[ii];

			/* create fresh node data info */
			nn = (struct rhpnode *)rhp_malloc(sizeof(struct rhpnode), __func__, __LINE__);

			/* set the info n */
			nn->num = num;
			nn->innum = nd->innum;
			nn->level = nd->level;
			nn->data = nd->data;
			nn->position = nd->position;
			nn->up_degree = nd->up_degree;
			nn->down_degree = nd->down_degree;
			nn->up_edges = nd->up_edges;
			nn->down_edges = nd->down_edges;
			nn->weight = nd->weight;
			nn->up_crossings = nd->up_crossings;
			nn->down_crossings = nd->down_crossings;

			rhp_log("%s(): node %d level %d pos %d weight %d at %d\n",
				__func__, nd->innum, nd->level, nd->position, nd->weight, num);

			/* insert node in database indexed on position number */
			rhp_sp_insert(rhp_sp_master_node_list_sorted, (splay_tree_key) num, (splay_tree_value) nn);

			num = (num + 1);
		}

	}

	return;
}

/* End. */
