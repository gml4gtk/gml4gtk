
/*
 *  Copyright 2021
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

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpun.h"

/* by uniq number of node */
static splay_tree uniqnode_splaytree = NULL;

void clear_dpuniqnode(void)
{
	uniqnode_splaytree = splay_tree_delete(uniqnode_splaytree);
	return;
}

void dpuniqnode_add(struct dpnode *node)
{
	splay_tree_node spn;
	if (node == NULL) {
		/* shouldnothappen */
		return;
	}
	if (uniqnode_splaytree == NULL) {
		uniqnode_splaytree = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree, (splay_tree_key) node->name);
	if (spn) {
		/* shouldnothappen */
		printf("dot %s(): node `%s' does already exist\n", __func__, node->name);
		fflush(stdout);
		return;
	} else {
		splay_tree_insert(uniqnode_splaytree, (splay_tree_key) node->name, (splay_tree_value) node);
	}
	return;
}

struct dpnode *dpuniqnode(char *name)
{
	splay_tree_node spn;
	if (uniqnode_splaytree == NULL) {
		return (NULL);
	}
	spn = splay_tree_lookup(uniqnode_splaytree, (splay_tree_key) name);
	if (spn) {
		return ((struct dpnode *)spn->value);
	} else {
		return (NULL);
	}
}

/* end */
