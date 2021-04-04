
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

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpmem.h"

/* */
void dp_free(void *ptr)
{
	char *p = NULL;
	if (ptr) {
		free(ptr);
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
	ret = calloc(nmemb, size);
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
	ret = realloc(ptr, n);
	/* with size 0, return NULL is oke. */
	if (n) {
		if (ret == NULL) {
			printf("%s(): nil realloc\n", __func__);
			exit(1);
		}
	}
	return (ret);
}

/* end */
