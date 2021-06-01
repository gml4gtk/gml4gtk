
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

#include "splay-tree.h"
#include "main.h"
#include "uniqgraph.h"

/* by uniq number of subgraph and 0 is rootgraph */
static splay_tree uniqgraph_splaytree = NULL;

/* */
void clear_uniqgraph(struct gml_graph *g)
{
	if (g) {
	}
	uniqgraph_splaytree = splay_tree_delete(uniqgraph_splaytree);
	return;
}

/* */
void uniqgraph_add(struct gml_graph *g, int sgnum)
{
	splay_tree_node spn = NULL;
	if (g == NULL) {
		/* shouldnothappen */
		return;
	}
	if (uniqgraph_splaytree == NULL) {
		uniqgraph_splaytree = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}
	spn = splay_tree_lookup(uniqgraph_splaytree, (splay_tree_key) sgnum);
	if (spn) {
		/* shouldnothappen */
		printf("%s(): graph does already exist\n", __func__);
		fflush(stdout);
		return;
	} else {
		splay_tree_insert(uniqgraph_splaytree, (splay_tree_key) sgnum, (splay_tree_value) g);
	}
	return;
}

/* */
struct gml_graph *uniqgraph(int sgnum)
{
	splay_tree_node spn = NULL;
	if (uniqgraph_splaytree == NULL) {
		uniqgraph_splaytree = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}
	spn = splay_tree_lookup(uniqgraph_splaytree, (splay_tree_key) sgnum);
	if (spn) {
		return ((struct gml_graph *)spn->value);
	} else {
		return (NULL);
	}
}

/* end */
