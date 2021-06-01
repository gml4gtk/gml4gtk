
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
#include "vcg.h"
#include "vcgun.h"

/* by uniq number of node */
static splay_tree vcguniqnode_splaytree = NULL;

void clear_vcguniqnode(void)
{
	vcguniqnode_splaytree = splay_tree_delete(vcguniqnode_splaytree);
	return;
}

void vcguniqnode_add(struct vcgn *node)
{
	splay_tree_node spn;
	if (node == NULL) {
		/* shouldnothappen */
		return;
	}
	if (vcguniqnode_splaytree == NULL) {
		vcguniqnode_splaytree = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	}
	spn = splay_tree_lookup(vcguniqnode_splaytree, (splay_tree_key) node->name);
	if (spn) {
		/* shouldnothappen */
		printf("%s(): node `%s' does already exist\n", __func__, node->name);
		fflush(stdout);
		return;
	} else {
		splay_tree_insert(vcguniqnode_splaytree, (splay_tree_key) node->name, (splay_tree_value) node);
	}
	return;
}

struct vcgn *vcguniqnode(char *name)
{
	splay_tree_node spn;
	if (vcguniqnode_splaytree == NULL) {
		return (NULL);
	}
	spn = splay_tree_lookup(vcguniqnode_splaytree, (splay_tree_key) name);
	if (spn) {
		return ((struct vcgn *)spn->value);
	} else {
		return (NULL);
	}
}

/* end */
