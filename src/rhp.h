
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
 *
 */

/* relative horizontal positioning in a single c source file.
 * this is used to draw structure and organisation in data but
 * the spring-embedders are good at density and change in data.
 * during layout memory usage may almost double and all that
 * extra memory is free()'ed at deinit().
 * at drawing the memory usage is much lower.
 * this can also be compiled as a lib.
 * this barycenter is also a trial-and-error algo and nobody knows
 * how to steer it to get good resuls. It may find good solutions
 * which are difficult to understand for humans in a drawing.
 * cpu temperature goes up 60% with large graph data.
 * theoretical limit is 2G nodes + 2G edges
 * practical limit is 2M nodes + 2M edges
 * current average graph has 1000-10000 nodes+edges
 * The layout theory is described in this book :
 * Graph Drawing And Applications For Software And Knowledge Engineers
 * ISBN10 9810248792 or ISBN13 9789810248796
 * Kozo Sugiyama, World Scientific Publishing Co Pte Ltd
 */

#ifndef RHP_H
#define RHP_H 1

/* stdint is used for the int64_t data type or use (long long int) 64 bits */
#include <stdint.h>

/* version info example "1.0" */
extern char *rhp_version (void);

/* init layouter
 * this must be done before any of the other routines below.
 * when the logname is NULL or (char *)0 no log output file is created.
 * when there is a logname specified a file with that name is created
 * and log messages are written to it. at deinit() the file is closed.
 * the log file is a human readable descriprion what the layouter is doing.
 * log messages with a '!' are error messages and always put on stderr.
 * if loglevel has a value then log messages are generated if there
 * is a logname and if loglevel > 1 then memory log messages are generated.
 * if logname is "" then output is stdout
 */
extern void rhp_init (char *logname, int loglevel);

/* de-init lyouter and free() all memory and close optional logfile.
 * after deinit() routines below do not react anymore until init() is done.
 */
extern void rhp_deinit (void);

/* add node at level
 * the num must be a uniq node number in 32bits int range
 * the level must be the relative vertical level of the node
 * the data can be used to pass additional data casted on
 * this data is not used by layouter but presented again
 * at calls done via rhp_node_foreach()
 * this routine returns 0 if everything is oke
 * this routine returns 1 at error
 * errors are num or level is below zero or too high
 * or node did already exist with given node number
 */
extern int rhp_addnode (int num, int level, void *data);

/* add edge from node number fnode to tnode
 * the fnode and tnode numbers are the from and to nodes
 * to create a directed edge between and both must have
 * been defined earlir with rhp_addnode().
 * the num must be a uniq edge number to identify this edge.
 * the data can be used to pass additional data casted on
 * this data is not used by layouter but presented again
 * at calls done via rhp_edge_foreach()
 * the to-node must be 1 one level more the the from-node.
 * if all oke then this return status (int) 0
 * this returns 1 if node numbers are out of range,
 * or nodes are not defined earlier or if the lenght
 * of the edge is longer then 1 one relative level.
 * when edges or nodes are rejected the the layout()
 * can continue with the nodes+edges passed on.
 */
extern int rhp_addedge (int num, int fnode, int tnode, void *data);

/* run layouter
 * the options can be 0 - not implemented yet
 * runs the barycenter to determine relative horzintal position
 * with lowest edge crossing count but there must be at least
 * one node in the graph data.
 * when there are 0 or 1 edges the crossing count is zero.
 * when there are 1 or 2 nodes the crossing count is zero.
 * to get the result node posions use rhp_node_foreach()
 * int nodeweightadjust = 0 for left node weight adjust
 * int nodeweightadjust = 1 for average node weight adjust
 */
extern void rhp_layout (int options, int nodeweightadjust);

/* get layouter data during iteration
 * this runs the supplied callback() routine at every iteration
 * of the layout. When the initial edge crossing count is zero
 * then this routine is never called.
 * the callback must return 0 to continue layouting or can
 * return 1 to stop the layouter algorithm.
 * when the callback() function runs the layouter pauses
 * and waits for the callback() to finish.
 * the callback routine gets the current iteration in iter,
 * the max. number of iterarion in maxiter, the current
 * edge crossings in ncross and the previous edge crossings
 * count in previous_ncross. the reduction number is the
 * amount of edge crossing reduction in percentage or
 * greater then 100% when there was an edge cross increase.
 * with this data the callback() routine can decide to stop
 * the layouer.
 * the better parameter is 1 if new drawing improved on
 * edge crossings or 0 if not improved.
 * the numbers improvements and notimprovements are the
 * number of times the drawing did improve or not-improve.
 * bot these numbers can be 0 and stay zero during layout.
 * the ratio of these improvement numbers can indicate if
 * it makes sense to continue layout similar as the difference
 * between crossing improvement numbers when that gets low.
 * the callback() routine can run rhp_node_foreach() and
 * rhp_edge_foreach() to get the details of the current
 * graph drawing status and use it to snapshot or draw it
 * as a continuous changing drawing during layout to see
 * the layout algorithm lowering the number of edge crossings.
 * if there is no callback() routine supplied (NULL) then
 * error message is printed and the routine call is ignored.
 */
extern void
rhp_layout_callback (int (*getlayoutdata)
		     (int iter, int maxiter, uint64_t ncross, uint64_t previous_ncross, uint64_t reduction, int better, int improvements, int notimprovements));

/* get node data and the calculated positions
 * this runs a supplied callback routine for every node
 * the callback routine gets the node number as supplied,
 * the level as supplied and the calculated pos position.
 * the data is the supplied data and can be used similar.
 * when the callback function needs to stop the iteration
 * over the node list then it must return a non-zero status
 * and that status is returned by rho_node_foreach()
 * return is 0 from this routine if everything is oke or no data.
 */
extern int rhp_node_foreach (int (*getnodedata) (int num, int level, int pos, void *data));

/* instead of foreach() get level of given node or -1 at error */
extern int rhp_node_get_level (int num);

/* instead of foreach() get position of given node or -1 at error */
extern int rhp_node_get_position (int num);

/* instead of foreach() get data of given node or -1 at error */
extern void *rhp_node_get_data (int num);

/* get edge data
 * this runs a supplied callback routine for every edge
 * the callback routine gets the edge number as supplied,
 * with the from-node number, level and position in fnum,
 * flevel and fpos and same for the to-node in tnum, tlevel
 * and tpos and the 64-bits signed int number of edge cossings
 * of this edge with other edges and the supplied data to use.
 * when the callback function needs to stop the iteration
 * over the edge list then it must return a non-zero status
 * and that status is returned by rho_node_foreach()
 * return is 0 from this routine if everything is oke or no data.
 */
extern int rhp_edge_foreach (int (*getedgedata) (int num, int fnum, int flevel, int fpos, int tnum, int tlevel, int tpos, int64_t ecross, void *data));

/* calculate initial crossings
 * this returns the initial graph edge crossings as 64bits number
 */
extern int64_t rhp_initial_crossings (void);

/* calculate crossings
 * this returns the current graph edge crossings as 64bits number
 */
extern int64_t rhp_current_crossings (void);

/* calculate crossings at level
 * this returns the graph edge crossings as 64bits number for specified level
 */
extern int64_t rhp_current_crossings_at_level (int level);

/* get number of nodes in specified level */
extern int rhp_nodes_in_level (int level);

/* get number of nodes in layouter for all levels */
extern int rhp_nodes_in_layout (void);

/* get number of edges in layouter for all levels */
extern int rhp_edges_in_layout (void);

/* emscripten can cross compile llvm to javascript as this source.
 * node-ffi can interface this to javascript using node.js
 */

#endif

/* End. */
