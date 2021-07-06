
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

/* skip list algoithm with same usage as GNU GCC compiler splay-tree.c, see also wikipedia for skiplist */

/**
 * @file: skip-list.c
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "skip-list.h"
#include "dpmem.h"

/* here wrapping to custom malloc/free can be set */
static inline void *skip_list_malloc(size_t n)
{
	return (dp_calloc(1, n));
}

static inline void *skip_list_free(void *ptr)
{
	if (ptr) {
		dp_free(ptr);
	}
	return (NULL);
}

/* forward decl. */
static skip_list_node skip_list_create_node(int level, skip_list_key key, skip_list_value val);
static int skip_list_randomlevel(void);

/* delete whole sp tree */
skip_list skip_list_delete(skip_list sp)
{
	skip_list_node q = (skip_list_node) 0;
	skip_list_node next = (skip_list_node) 0;

	if (sp == (skip_list) 0) {
		return ((skip_list) 0);
	}

	if (sp->head) {
		q = sp->head;

		while (q) {
			next = q->next[0];

			if (q->value) {
				if (sp->delete_value) {
					(*sp->delete_value) (q->value);
				}
			}

			if (q->key) {
				if (sp->delete_key) {
					(*sp->delete_key) (q->key);
				}
			}

			q = (skip_list_node) skip_list_free(q);
			/* q is never read */
			if (q) {	/* fix */
			}
			q = next;
		}

	}

	return ((skip_list) skip_list_free(sp));
}

/* Allocate a new skip list tree, using COMPARE_FN to compare nodes,
   DELETE_KEY_FN to deallocate keys, and DELETE_VALUE_FN to deallocate
   values.  */

skip_list
skip_list_new(skip_list_compare_fn compare_fn, skip_list_delete_key_fn delete_key_fn, skip_list_delete_value_fn delete_value_fn)
{
	skip_list sp = (skip_list) 0;
	skip_list_node h = (skip_list_node) 0;
	int i = 0;

	/* there must be a compare function, the free() functions are optional */
	if (compare_fn == (skip_list_compare_fn) 0) {
		return ((skip_list) 0);
	}

	sp = (skip_list) skip_list_malloc(sizeof(struct skip_list_t));

	sp->level = 0;

	h = skip_list_create_node((SKIP_LIST_MAX_LEVEL - 1), 0, 0);

	sp->head = h;

	for (i = 0; i < SKIP_LIST_MAX_LEVEL; ++i) {
		h->next[i] = (skip_list_node) 0;
	}

	/* The comparision function.  */
	sp->comp = compare_fn;

	/* The deallocate-key function.  NULL if no cleanup is necessary.  */
	sp->delete_key = delete_key_fn;

	/* The deallocate-value function.  NULL if no cleanup is necessary.  */
	sp->delete_value = delete_value_fn;

	return ((skip_list) sp);
}

/* Insert a new node (associating KEY with DATA) into SP.  If a
   previous node with the indicated KEY exists, its data is not replaced
   with the new value.  */

void skip_list_insert(skip_list sp, skip_list_key key, skip_list_value value)
{
	skip_list_node update[SKIP_LIST_MAX_LEVEL];
	skip_list_node q = (skip_list_node) 0;
	skip_list_node p = (skip_list_node) 0;
	int comparison = 0;
	int level = 0;
	int i = 0;

	if (sp == (skip_list) 0) {
		/* no tree */
		return;
	}

	if (sp->head == (skip_list_node) 0) {
		return;
	}

	p = sp->head;

	for (i = (sp->level) - 1; i >= 0; --i) {
		while ((q = p->next[i])) {
			comparison = (*sp->comp) (q->key, key);
			/* check if q->key >= key */
			if (comparison >= 0) {
				break;
			}
			/* here if q->key < key */
			p = q;
		}
		update[i] = p;
	}

	/* check if key already exist */
	if (q) {
		if (q->key == key) {
			if (0) {
				/* if found, update with new value */
				if (q->value) {
					if (sp->delete_value) {
						(*sp->delete_value) (q->value);
					}
				}
				q->value = value;
			}
			return;
		}
	}

	level = skip_list_randomlevel();

	if (level > sp->level) {
		for (i = sp->level; i < level; ++i) {
			update[i] = sp->head;
		}
		sp->level = level;
	}

	q = skip_list_create_node(level, key, value);

	for (i = (level - 1); i >= 0; --i) {
		q->next[i] = update[i]->next[i];
		update[i]->next[i] = q;
	}

	return;
}

/* Remove KEY from SP.  It is not an error if it did not exist.  */
void skip_list_remove(skip_list sp, skip_list_key key)
{
	skip_list_node update[SKIP_LIST_MAX_LEVEL];
	skip_list_node q = (skip_list_node) 0;
	skip_list_node p = (skip_list_node) 0;
	int comparison = 0;
	int i = 0;

	if (sp == (skip_list) 0) {
		/* no tree */
		return;
	}

	if (sp->head == (skip_list_node) 0) {
		return;
	}

	p = sp->head;

	for (i = (sp->level) - 1; i >= 0; --i) {
		while ((q = p->next[i])) {
			comparison = (*sp->comp) (q->key, key);
			/* check if q->key >= key */
			if (comparison >= 0) {
				break;
			}
			/* here if q->key < key */
			p = q;
		}
		update[i] = p;
	}

	if (q == (skip_list_node) 0) {
		return;
	}

	if (q->key != key) {
		return;
	}

	for (i = (sp->level - 1); i >= 0; --i) {
		if (update[i]->next[i] == q) {
			update[i]->next[i] = q->next[i];
			if (sp->head->next[i] == (skip_list_node) 0) {
				sp->level--;
			}
		}
	}

	if (q->value) {
		if (sp->delete_value) {
			(*sp->delete_value) (q->value);
		}
	}

	if (q->key) {
		if (sp->delete_key) {
			(*sp->delete_key) (q->key);
		}
	}

	q = (skip_list_node) skip_list_free(q);

	/* q is never read */
	if (q) {		/* fix */
	}

	return;
}

/* Lookup KEY in SP, returning VALUE if present, and NULL
   otherwise.  */
skip_list_node skip_list_lookup(skip_list sp, skip_list_key key)
{
	skip_list_node q = (skip_list_node) 0;
	skip_list_node p = (skip_list_node) 0;
	int comparison = 0;
	int i = 0;

	if (sp == (skip_list) 0) {
		/* no tree */
		return ((skip_list_node) 0);
	}

	if (sp->head == (skip_list_node) 0) {
		return ((skip_list_node) 0);
	}

	p = sp->head;

	for (i = (sp->level - 1); i >= 0; --i) {
		while ((q = p->next[i])) {
			comparison = (*sp->comp) (q->key, key);
			/* check if q->key >= key */
			if (comparison >= 0) {
				break;
			}
			/* here if q->key < key */
			p = q;
		}
	}

	if (q) {
		if (q->key == key) {
			return ((skip_list_node) q);
		}
	}

	/* not found */
	return ((skip_list_node) 0);
}

/* free() wrappers to free key/value */
void skip_list_free_value(skip_list_value value)
{
	if (value) {
		(void)skip_list_free((void *)value);
	}
	return;
}

void skip_list_free_key(skip_list_key key)
{
	if (key) {
		(void)skip_list_free((void *)key);
	}
	return;
}

/* comparison function, treating the keys as ints.  */

int skip_list_compare_ints(skip_list_key k1, skip_list_key k2)
{
	if ((int)k1 < (int)k2) {
		return ((int)-1);
	} else if ((int)k1 > (int)k2) {
		return (1);
	} else {
		return (0);
	}
}

/* comparison function, treating the keys as pointers.
   Note this is possibly not portable on all systems according to standards
   and may have undefined results. there seems no good solution for this.
   (a char datatype does not have to be a single byte in c for example)
*/

int skip_list_compare_pointers(skip_list_key k1, skip_list_key k2)
{
	/* 0==0 */
	if ((k1 == (skip_list_key) 0) && (k2 == (skip_list_key) 0)) {
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

/* Comparison function for a skip list in which the keys are strings.
   K1 and K2 have the dynamic type "const char *".  Returns <0, 0, or
   >0 to indicate whether K1 is less than, equal to, or greater than
   K2, respectively.
   similar issues here when as compare pointers and c portable src.
*/

int skip_list_compare_strings(skip_list_key k1, skip_list_key k2)
{
	const char *s1 = (const char *)k1;
	const char *s2 = (const char *)k2;
	int ret = 0;

	if ((k1 == (skip_list_key) 0) && (k2 == (skip_list_key) 0)) {
		return (0);
	}

	if (s1 == (const char *)0) {
		/* to avoid crashes only */
		return (0);
	}

	if (s2 == (const char *)0) {
		/* to avoid crashes only */
		return (0);
	}

	/* check if same pointer. possible not portable c. */
	if (s1 == s2) {
		return (0);
	}

	ret = strcmp(s1, s2);

	return ((int)ret);
}

/* */
static skip_list_node skip_list_create_node(int level, skip_list_key key, skip_list_value val)
{
	skip_list_node p = (skip_list_node) 0;

	p = (skip_list_node) skip_list_malloc((sizeof(struct skip_list_node_n) + level * sizeof(skip_list_node)));

	p->key = key;
	p->value = val;

	return ((skip_list_node) p);
}

/* */
static int skip_list_randomlevel(void)
{
	int level = 1;
	double d = 0.0;
	int c = 0;

	for (;;) {
		c = rand();
		d = (double)c;
		if ((d / SKIP_LIST_MAX_LEVEL) < 0.50) {
			level++;
			if (level > SKIP_LIST_MAX_LEVEL) {
				break;
			}
		}
	}

	if (level > SKIP_LIST_MAX_LEVEL) {
		level = SKIP_LIST_MAX_LEVEL;
	}

	return level;
}

/* end. */
