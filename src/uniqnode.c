
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
 * node database
 * uniqnode() is used for raw node data
 * uniqnode2() is used for work node data in nodelist
 * uniqnode() is indexed on node number and node id for gml graph data
 */

#include "config.h"

#include <stdio.h>

#include "splay-tree.h"
#include "main.h"
#include "uniqnode.h"

/* by uniq number of node */
static splay_tree uniqnode_splaytree = NULL;

/* by uniq number of node */
static splay_tree uniqnode_splaytree2 = NULL;

/* by id number of node */
static splay_tree uniqnodeid_splaytree = NULL;

/* */
void clear_uniqnode(struct gml_graph *g)
{
	if (g) {
	}
	uniqnode_splaytree = splay_tree_delete(uniqnode_splaytree);
	uniqnodeid_splaytree = splay_tree_delete(uniqnodeid_splaytree);
	return;
}

/* */
void clear_uniqnode2(struct gml_graph *g)
{
	if (g) {
	}
	uniqnode_splaytree2 = splay_tree_delete(uniqnode_splaytree2);
	return;
}

/* */
void uniqnode_add(struct gml_graph *g, struct gml_node *node)
{
	splay_tree_node spn = NULL;
	if (g) {
	}
	if (node == NULL) {
		/* shouldnothappen */
		return;
	}
	if (uniqnode_splaytree == NULL) {
		uniqnode_splaytree = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}
	if (uniqnodeid_splaytree == NULL) {
		uniqnodeid_splaytree = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree, (splay_tree_key) node->nr);
	if (spn) {
		/* shouldnothappen */
		printf("uniqnode_add(): node does already exist\n");
		fflush(stdout);
		return;
	} else {
		splay_tree_insert(uniqnode_splaytree, (splay_tree_key) node->nr, (splay_tree_value) node);
		splay_tree_insert(uniqnodeid_splaytree, (splay_tree_key) node->id, (splay_tree_value) node);
	}
	return;
}

/* */
void uniqnode_add2(struct gml_graph *g, struct gml_node *node)
{
	splay_tree_node spn = NULL;
	if (g) {
	}
	if (node == NULL) {
		/* shouldnothappen */
		return;
	}
	if (uniqnode_splaytree2 == NULL) {
		uniqnode_splaytree2 = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree2, (splay_tree_key) node->nr);
	if (spn) {
		/* shouldnothappen */
		printf("uniqnode_add2(): node does already exist\n");
		fflush(stdout);
		return;
	} else {
		splay_tree_insert(uniqnode_splaytree2, (splay_tree_key) node->nr, (splay_tree_value) node);
	}
	return;
}

/* */
struct gml_node *uniqnode(struct gml_graph *g, int nr)
{
	splay_tree_node spn = NULL;
	if (g) {
	}
	if (uniqnode_splaytree == NULL) {
		return (NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree, (splay_tree_key) nr);
	if (spn) {
		return ((struct gml_node *)spn->value);
	} else {
		return (NULL);
	}
}

/* */
struct gml_node *uniqnode2(struct gml_graph *g, int nr)
{
	splay_tree_node spn = NULL;
	if (g) {
	}
	if (uniqnode_splaytree2 == NULL) {
		return (NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree2, (splay_tree_key) nr);
	if (spn) {
		return ((struct gml_node *)spn->value);
	} else {
		return (NULL);
	}
}

/* */
struct gml_node *uniqnodeid(struct gml_graph *g, int nr)
{
	splay_tree_node spn = NULL;
	if (g) {
	}
	if (uniqnodeid_splaytree == NULL) {
		return (NULL);
	}
	spn = splay_tree_lookup(uniqnodeid_splaytree, (splay_tree_key) nr);
	if (spn) {
		return ((struct gml_node *)spn->value);
	} else {
		return (NULL);
	}
}

/* end */
