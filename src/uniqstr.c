
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

/* needed to get strdup()
#define _GNU_SOURCE
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "splay-tree.h"
#include "main.h"
#include "uniqstr.h"

/* strdup issue here and gcc-6.3.0
#ifndef HAVE_STRDUP
extern char *strdup (const char *str);
#endif
*/

static splay_tree uniqstr_splaytree = NULL;

void clear_uniqstr(void)
{
	uniqstr_splaytree = splay_tree_delete(uniqstr_splaytree);
	return;
}

char *uniqstr(char *str)
{
	char *s = NULL;
	splay_tree_node spn;
	if (str == NULL) {
		return (NULL);
	}
	if (strlen(str) == 0) {
		return ("");
	}
	spn = splay_tree_lookup(uniqstr_splaytree, (splay_tree_key) str);
	if (spn) {
		return ((char *)spn->key);
	}
	if (uniqstr_splaytree == NULL) {
		uniqstr_splaytree = splay_tree_new(splay_tree_compare_strings, splay_tree_free_key, NULL);
	}
	/* similar as strdup */
	s = calloc(1, (strlen(str) + 1));
	if (s == NULL) {
		return (NULL);
	}
	strcpy(s, str);
	splay_tree_insert(uniqstr_splaytree, (splay_tree_key) s, 0);
	return (s);
}

/* end */
