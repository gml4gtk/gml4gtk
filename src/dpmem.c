
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

/* wrappers for malloc/calloc/realloc/free
 * when there is no more memory no crash
 * but a message and call to exit()
 * malloc is redirected to calloc.
 *
 * This is needed because gcc-11 -fanalyzer option generates warnings at every
 * malloc/callon in the source but wrapping it this way stops these messages.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpmem.h"

static splay_tree memdata = NULL;

static void memcheck_free(void *ptr);
static void *memcheck_calloc(size_t nmemb, size_t size);
static void *memcheck_realloc(void *ptr, size_t size);

/* */
void dp_free(void *ptr)
{
	char *p = NULL;
	if (ptr) {
		memcheck_free(ptr);
	} else {
		printf("%s(): nil ptr\n", __func__);
		if (0) {
			/* this is a segv to use with gdb then bt command where it came from. */
			*p = 1;
		}
	}
	return;
}

/* */
void *dp_malloc(size_t n)
{
	/* malloc() does not happen in gml4gtk but in the bison parser code. */
	if (n == 0) {
		printf("%s(): 0 malloc\n", __func__);
	}
	return (dp_calloc(1, n));
}

/* */
void *dp_calloc(size_t nmemb, size_t size)
{
	void *ret = NULL;
	if ((nmemb * size) == 0) {
		/* shouldnothappen */
		printf("%s(): nmemb=%d, size=%d 0 bytes\n", __func__, (int)nmemb, (int)size);
	}
	ret = memcheck_calloc(nmemb, size);
	if (ret == NULL) {
		printf("%s(): no memory\n", __func__);
		exit(1);
	}
	return (ret);
}

/* */
void *dp_realloc(void *ptr, size_t n)
{
	void *ret = NULL;
	/* realloc() does not happen in gml4gtk but in the bison parser code. */
	ret = memcheck_realloc(ptr, n);
	/* with size 0, return NULL is oke. */
	if (n) {
		if (ret == NULL) {
			printf("%s(): nil realloc\n", __func__);
			exit(1);
		}
	}
	return (ret);
}

#ifdef MEMCHECK
/* extra memory checking */

/* A splay-tree datatype.
   Copyright (C) 1998-2021 Free Software Foundation, Inc.
   Contributed by Mark Mitchell (mark@markmitchell.com).

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
the Free Software Foundation, 51 Franklin Street - Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* For an easily readable description of splay-trees, see:

     Lewis, Harry R. and Denenberg, Larry.  Data Structures and Their
     Algorithms.  Harper-Collins, Inc.  1991.  */

/* custom splay() using calloc/free */

/* splay routines */
static splay_tree m_splay_tree_new(splay_tree_compare_fn fnc, splay_tree_delete_key_fn fndk, splay_tree_delete_value_fn fndv);
static splay_tree m_splay_tree_delete(splay_tree sp);
static void m_splay_tree_insert(splay_tree sp, splay_tree_key k, splay_tree_value v);
static void m_splay_tree_remove(splay_tree sp, splay_tree_key key);
static splay_tree_node m_splay_tree_lookup(splay_tree sp, splay_tree_key k);
static splay_tree_node m_splay_tree_min(splay_tree sp);

/* Return the immediate successor KEY, or NULL if there is no
   successor.  KEY need not be present in the tree.  */
static splay_tree_node m_splay_tree_successor(splay_tree sp, splay_tree_key key);

/* return 1 if splay tree has data, otherwise 0 */
static int m_splay_tree_has_data(splay_tree sp);

/* free() wrappers to free key/value */
static void m_splay_tree_free_key(splay_tree_key key);
static int m_splay_tree_compare_pointers(splay_tree_key k1, splay_tree_key k2);

/* forward decl. */
static struct splay_tree_node_n *m_splay(splay_tree sp, splay_tree_key key);

/* delete whole sp tree */
static splay_tree m_splay_tree_delete(splay_tree sp)
{
	splay_tree_node spn = (splay_tree_node) 0;
	splay_tree_key *keys = (splay_tree_key *) 0;
	int count = 0;
	int i = 0;

	if (sp == (splay_tree) 0) {
		return ((splay_tree) 0);
	}

	/* if there is data */
	if (sp->root) {
		/* for every node, this can not cause stack smashing.
		 * this is slowest way possible but splay_tree_delete() does almost never happen.
		 * gcc realloc()'s array with pointers to free() but using realloc()
		 * may cause unexpected high memory usage, thats why avoiding realloc() use.
		 */
		spn = m_splay_tree_min(sp);
		while (spn) {
			count++;
			spn = m_splay_tree_successor(sp, spn->key);
		}

		count++;

		keys = calloc(1, (count * sizeof(splay_tree_key)));

		if (keys) {
			spn = m_splay_tree_min(sp);
			i = 0;
			while (spn) {
				keys[i] = (splay_tree_key) spn->key;
				i++;
				spn = m_splay_tree_successor(sp, spn->key);
			}

			for (i = 0; i < count; i++) {
				m_splay_tree_remove(sp, (splay_tree_key) keys[i]);
				keys[i] = (splay_tree_key) 0;
			}
			free(keys);
		}

	}

	/* wipe the pointers in the struct to make valgrind happy */
	sp->root = (splay_tree_node) 0;

	/* The comparision function.  */
	sp->comp = (splay_tree_compare_fn) 0;

	/* The deallocate-key function.  NULL if no cleanup is necessary.  */
	sp->delete_key = (splay_tree_delete_key_fn) 0;

	/* The deallocate-value function.  NULL if no cleanup is necessary.  */
	sp->delete_value = (splay_tree_delete_value_fn) 0;

	free((void *)sp);

	return ((splay_tree) 0);
}

/* Allocate a new splay tree, using COMPARE_FN to compare nodes,
   DELETE_KEY_FN to deallocate keys, and DELETE_VALUE_FN to deallocate
   values.  */

static splay_tree
m_splay_tree_new(splay_tree_compare_fn compare_fn, splay_tree_delete_key_fn delete_key_fn,
		 splay_tree_delete_value_fn delete_value_fn)
{
	splay_tree sp = (splay_tree) 0;

	/* there must be a compare function, the free() functions are optional */
	if (compare_fn == (splay_tree_compare_fn) 0) {
		return ((splay_tree) 0);
	}

	sp = (splay_tree) calloc(1, sizeof(struct splay_tree_t));

	if (sp == (splay_tree) 0) {
		return ((splay_tree) 0);
	}

	/* set root node to use and the functions */
	sp->root = (splay_tree_node) 0;
	sp->comp = compare_fn;
	sp->delete_key = delete_key_fn;
	sp->delete_value = delete_value_fn;

	return ((splay_tree) sp);
}

/* Insert a new node (associating KEY with DATA) into SP.  If a
   previous node with the indicated KEY exists, its data is not replaced
   with the new value.  */

static void m_splay_tree_insert(splay_tree sp, splay_tree_key key, splay_tree_value value)
{
	splay_tree_node spn = (splay_tree_node) 0;
	int comparison = 0;

	if (sp == (splay_tree) 0) {
		/* no tree */
		return;
	}

	spn = m_splay_tree_lookup(sp, key);

	if (spn != (splay_tree_node) 0) {
		/* did already exist */
		return;
	}

	/* Create a new node, and insert it at the root.  */
	spn = (splay_tree_node) calloc(1, sizeof(struct splay_tree_node_n));

	if (spn == (splay_tree_node) 0) {
		/* shouldnothappen */
		return;
	}

	/* set node data */
	spn->key = key;
	spn->value = value;

	if (sp->root == (splay_tree_node) 0) {
		/* first entry */
		sp->root = spn;
		return;
	}

	/* add in tree */
	comparison = (*sp->comp) (sp->root->key, key);

	if (comparison < 0) {
		spn->left = sp->root;
		spn->right = spn->left->right;
		spn->left->right = (splay_tree_node) 0;
	} else {
		/* > or == */
		spn->right = sp->root;
		spn->left = spn->right->left;
		spn->right->left = (splay_tree_node) 0;
	}

	sp->root = spn;

	return;
}

/* Remove KEY from SP.  It is not an error if it did not exist.  */
static void m_splay_tree_remove(splay_tree sp, splay_tree_key key)
{
	splay_tree_node spn = (splay_tree_node) 0;
	splay_tree_node node = (splay_tree_node) 0;
	splay_tree_node left = (splay_tree_node) 0;
	splay_tree_node right = (splay_tree_node) 0;

	if (sp == (splay_tree) 0) {
		/* no tree */
		return;
	}

	if (sp->root == (splay_tree_node) 0) {
		/* no data */
		return;
	}

	spn = m_splay_tree_lookup(sp, key);

	if (spn == (splay_tree_node) 0) {
		return;
	}

	/* found entry to delete now in spn */
	node = sp->root;
	left = sp->root->left;
	right = sp->root->right;

	/* One of the children is now the root.  Doesn't matter much
	   which, so long as we preserve the properties of the tree.  */
	if (left) {
		sp->root = left;
		/* If there was a right child as well, hang it off the
		   right-most leaf of the left child.  */
		if (right) {
			while (left->right) {
				left = left->right;
			}
			left->right = right;
		}
	} else {
		sp->root = right;
	}

	/* free() key if needed */
	if (sp->delete_key) {
		/* avoid free(0) */
		if (node->key) {
			(*sp->delete_key) (node->key);
		}
		node->key = (splay_tree_key) 0;
	}

	/* free() value if needed */
	if (sp->delete_value) {
		/* avoid free(0) */
		if (node->value) {
			(*sp->delete_value) (node->value);
		}
		node->value = (splay_tree_value) 0;
	}

	/* free() node itself and wipe the pointers */
	node->left = (splay_tree_node) 0;
	node->right = (splay_tree_node) 0;

	free((void *)node);

	return;
}

/* Lookup KEY in SP, returning VALUE if present, and NULL
   otherwise.  */
static splay_tree_node m_splay_tree_lookup(splay_tree sp, splay_tree_key key)
{
	splay_tree_node spn = (splay_tree_node) 0;

	if (sp == (splay_tree) 0) {
		/* no tree */
		return ((splay_tree_node) 0);
	}

	if (sp->root == (splay_tree_node) 0) {
		/* no data */
		return ((splay_tree_node) 0);
	}

	if ((*sp->comp) (sp->root->key, key) == 0) {
		/* found */
		return ((splay_tree_node) sp->root);
	}

	spn = m_splay(sp, key);

	if (spn) {

		if ((*sp->comp) (sp->root->key, key) == 0) {
			/* found */
			return ((splay_tree_node) sp->root);
		}
	}

	/* not found */
	return ((splay_tree_node) 0);
}

/* Return the node in SP with the smallest key.  */
static splay_tree_node m_splay_tree_min(splay_tree sp)
{
	splay_tree_node n = (splay_tree_node) 0;

	/* <nil> splaytree */
	if (sp == (splay_tree) 0) {
		return ((splay_tree_node) 0);
	}

	/* no data */
	if (sp->root == (splay_tree_node) 0) {
		return ((splay_tree_node) 0);
	}

	n = sp->root;

	/* scan l */
	while (n->left) {
		n = n->left;
	}

	return ((splay_tree_node) n);
}

/* return 1 if splay tree has data, otherwise 0 */
static int m_splay_tree_has_data(splay_tree sp)
{
	if (sp == (splay_tree) 0) {
		return (0);
	}
	if (sp->root) {
		return (1);
	} else {
		return (0);
	}
}

/* Return the immediate successor KEY, or NULL if there is no
   successor.  KEY need not be present in the tree.  */

static splay_tree_node m_splay_tree_successor(splay_tree sp, splay_tree_key key)
{
	int comparison = 0;
	splay_tree_node node = (splay_tree_node) 0;

	if (sp == (splay_tree) 0) {
		/* no tree */
		return ((splay_tree_node) 0);
	}

	/* If the tree is empty, there is certainly no successor.  */
	if (sp->root == (splay_tree_node) 0) {
		return ((splay_tree_node) 0);
	}

	/* Splay the tree around KEY.  That will leave either the KEY
	   itself, its predecessor, or its successor at the root.  */
	node = m_splay(sp, key);

	if (node == (splay_tree_node) 0) {
		return ((splay_tree_node) 0);
	}

	/* */
	comparison = (*sp->comp) (sp->root->key, key);

	/* If the successor is at the root, just return it.  */
	if (comparison > 0) {
		return ((splay_tree_node) sp->root);
	}

	/* Otherwise, find the leftmost element of the right subtree.  */
	node = sp->root->right;

	if (node) {
		while (node->left) {
			node = node->left;
		}
	}

	return ((splay_tree_node) node);
}

static void m_splay_tree_free_key(splay_tree_key key)
{
	if (key) {
		free((void *)key);
	}
	return;
}

/* Splay-tree comparison function, treating the keys as pointers.
   Note this is possibly not portable on all systems according to standards
   and may have undefined results. there seems no good solution for this.
   (a char datatype does not have to be a single byte in c for example)
*/

static int m_splay_tree_compare_pointers(splay_tree_key k1, splay_tree_key k2)
{
	/* 0==0 */
	if ((k1 == (splay_tree_key) 0) && (k2 == (splay_tree_key) 0)) {
		return (0);
	}
	/* possible undefined results at this, says the c standard. has to be understood as (signed char *) */
	if ((char *)k1 < (char *)k2) {
		return ((int)-1);
	} else if ((char *)k1 > (char *)k2) {
		return (1);
	} else {
		return (0);
	}
}

/* */
static struct splay_tree_node_n *m_splay(splay_tree sp, splay_tree_key key)
{
	struct splay_tree_node_n *t = (struct splay_tree_node_n *)0;
	struct splay_tree_node_n *l = (struct splay_tree_node_n *)0;
	struct splay_tree_node_n *r = (struct splay_tree_node_n *)0;
	struct splay_tree_node_n *y = (struct splay_tree_node_n *)0;
	int comparevalue = 0;
	int comparevalue2 = 0;
	struct splay_tree_node_n tmp = {
		/* The key.  */
		(splay_tree_key) 0,
		/* The value.  */
		(splay_tree_value) 0,
		/* The left and right children, respectively.  */
		(struct splay_tree_node_n *)0,	/* left */
		(struct splay_tree_node_n *)0	/* right */
	};

	/* no tree */
	if (sp == (splay_tree) 0) {
		return ((struct splay_tree_node_n *)0);
	}

	/* no data in root. return 0 */
	if (sp->root == (struct splay_tree_node_n *)0) {
		return ((struct splay_tree_node_n *)0);
	}

	/* current root */
	t = sp->root;

	tmp.left = (struct splay_tree_node_n *)0;
	tmp.right = (struct splay_tree_node_n *)0;

	l = &tmp;
	r = &tmp;

labelstart:

	/* */
	comparevalue = (*sp->comp) (key, t->key);

	if (comparevalue < 0) {

		if (t->left == (struct splay_tree_node_n *)0) {
			goto labelend;
		}

		/* */
		comparevalue2 = (*sp->comp) (key, t->left->key);

		if (comparevalue2 < 0) {

			y = t->left;
			t->left = y->right;
			y->right = t;
			t = y;

			if (t->left == (struct splay_tree_node_n *)0) {
				goto labelend;
			}
		}

		/* */
		r->left = t;
		r = t;
		t = t->left;

	} else if (comparevalue > 0) {

		if (t->right == (struct splay_tree_node_n *)0) {
			goto labelend;
		}

		/* */
		comparevalue2 = (*sp->comp) (key, t->right->key);

		if (comparevalue2 > 0) {

			/* */
			y = t->right;
			t->right = y->left;
			y->left = t;
			t = y;

			if (t->right == (struct splay_tree_node_n *)0) {
				goto labelend;
			}
		}

		/* */
		l->right = t;
		l = t;
		t = t->right;
	} else {
		/* here if (comparevalue == 0) */
		goto labelend;
	}

	goto labelstart;

labelend:

	l->right = t->left;
	r->left = t->right;
	t->left = tmp.right;
	t->right = tmp.left;

	sp->root = t;

	return ((struct splay_tree_node_n *)t);
}

/* end */

static void memcheck_free(void *ptr)
{
	splay_tree_node spn = NULL;
	char *p = NULL;
	if (memdata == NULL) {
		/* shouldnothappen */
		memdata = m_splay_tree_new(m_splay_tree_compare_pointers, m_splay_tree_free_key, NULL /* delete_value_fn */ );
	}

	if (ptr) {
		spn = m_splay_tree_lookup(memdata, (splay_tree_key) ptr);
		if (spn) {
			m_splay_tree_remove(memdata, (splay_tree_key) spn->key);
		} else {
			printf("%s(): %p not found\n", __func__, (void *)ptr);
			if (0) {
				*p = 10;
			}
		}
	}

	return;
}

static void *memcheck_calloc(size_t nmemb, size_t size)
{
	void *ret = NULL;
	size_t total = 0;
	if (memdata == NULL) {
		memdata = m_splay_tree_new(m_splay_tree_compare_pointers, m_splay_tree_free_key, NULL /* delete_value_fn */ );
	}
	total = (nmemb * size);
	ret = calloc(1, total);
	m_splay_tree_insert(memdata, (splay_tree_key) ret, (splay_tree_value) total);
	return (ret);
}

static void *memcheck_realloc(void *ptr, size_t size)
{
	void *ret = NULL;
	size_t oldsize = 0;
	splay_tree_node spn = NULL;

	if (ptr == NULL) {
		return (memcheck_calloc(1, size));
	}
	if (size == 0) {
		memcheck_free(ptr);
		return (0);
	}
	/* find the old size of the pointed to memory block */
	spn = m_splay_tree_lookup(memdata, (splay_tree_key) ptr);
	if (spn) {
		oldsize = (size_t)spn->value;
		/* new memory block */
		ret = memcheck_calloc(1, size);
		if (size > oldsize) {
			memmove(ret, ptr, oldsize);
		} else {
			/* if new size is smaller, copy part of old data */
			memmove(ret, ptr, size);
		}
		/* free old block */
		memcheck_free(ptr);
	}
	return (ret);
}

void dp_memreport(void)
{
	splay_tree_node spn = NULL;
	size_t total = 0;
	int i = 0;
	if (memdata == NULL) {
		return;
	}
	if (m_splay_tree_has_data(memdata)) {
		spn = m_splay_tree_min(memdata);

		i = 1;
		while (spn) {
			printf("%s(): pointer[%d] %p with %d bytes not free'ed\n", __func__, i, (void *)spn->key, (int)spn->value);
			total += (size_t)spn->value;
			i++;
			spn = m_splay_tree_successor(memdata, spn->key);
		}

	}
	if (total) {
		printf("%s(): total %d bytes memory leak at exit\n", __func__, (int)total);
	} else {
		printf("%s(): no memory leak at exit\n", __func__);
	}

	memdata = m_splay_tree_delete(memdata);
	return;
}

void dp_meminit(void)
{
	if (memdata == NULL) {
		memdata = m_splay_tree_new(m_splay_tree_compare_pointers, m_splay_tree_free_key, NULL /* delete_value_fn */ );
	}
	return;
}

#else
/* no memory checking */

/* */
void dp_memreport(void)
{
	if (memdata) {
	}
	memdata = NULL;
	return;
}

static void memcheck_free(void *ptr)
{
	if (ptr) {
		free(ptr);
	}
	return;
}

static void *memcheck_calloc(size_t nmemb, size_t size)
{
	return (calloc(1, (nmemb * size)));
}

static void *memcheck_realloc(void *ptr, size_t size)
{
	return (realloc(ptr, size));
}

void dp_meminit(void)
{
	return;
}

#endif

/* end */
