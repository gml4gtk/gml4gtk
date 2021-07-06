
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

/**
 * @file: skip-list.h
 */

#ifndef SKIP_LIST_H
#define SKIP_LIST_H 1

/* */
#define SKIP_LIST_MAX_LEVEL 32

/* needed for type unintptr_t or use long long int */
#include <stdint.h>

/* how many bytes can a splay key to index on have max. */
/* typedef unsigned long long int skip_list_key; */
typedef uintptr_t skip_list_key;

/* how many bytes can a splay value have max. */
/* typedef unsigned long long int skip_list_value; */
typedef uintptr_t skip_list_value;

/* Forward declaration for a tree.  */
typedef struct skip_list_t *skip_list;

/* The nodes in the splay tree.  */
struct skip_list_node_n {

	/* The key.  */
	skip_list_key key;

	/* The value.  */
	skip_list_value value;

	/* linkage */
	struct skip_list_node_n *next[1];
};

/* Forward declaration for a node in the tree.  */
typedef struct skip_list_node_n *skip_list_node;

/* The type of a function which compares two skip-list keys.  The
   function should return values as for qsort.  */
typedef int (*skip_list_compare_fn)(skip_list_key, skip_list_key);

/* The type of a function used to deallocate any resources associated
   with the key.  */
typedef void (*skip_list_delete_key_fn)(skip_list_key);

/* The type of a function used to deallocate any resources associated
   with the value.  */
typedef void (*skip_list_delete_value_fn)(skip_list_value);

struct skip_list_t {

	/* level */
	int level;

	/* The root of the tree.  */
	struct skip_list_node_n *head;

	/* The comparision function.  */
	skip_list_compare_fn comp;

	/* The deallocate-key function.  NULL if no cleanup is necessary.  */
	skip_list_delete_key_fn delete_key;

	/* The deallocate-value function.  NULL if no cleanup is necessary.  */
	skip_list_delete_value_fn delete_value;
};

extern skip_list skip_list_new(skip_list_compare_fn fnc, skip_list_delete_key_fn fndk, skip_list_delete_value_fn fndv);
extern skip_list skip_list_delete(skip_list sp);
extern skip_list_node skip_list_lookup(skip_list sp, skip_list_key key);

extern void skip_list_insert(skip_list sp, skip_list_key k, skip_list_value v);
extern void skip_list_remove(skip_list sp, skip_list_key key);

extern int skip_list_has_data(skip_list sp);

extern void skip_list_free_value(skip_list_value value);
extern void skip_list_free_key(skip_list_key key);

extern int skip_list_compare_ints(skip_list_key k1, skip_list_key k2);
extern int skip_list_compare_pointers(skip_list_key k1, skip_list_key k2);
extern int skip_list_compare_strings(skip_list_key k1, skip_list_key k2);

#endif

/* end. */
