
/*
 *  Copyright t lefering
 *  (C) Universitaet Passau 1986-1991
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

#ifndef GML_PARSER_H
#define GML_PARSER_H 1

union GML_pair_val {
	long integer;
	double floating;
	char *string;
	struct GML_pair *list;
};

struct GML_pair {
	char *key;
	GML_value kind;
	union GML_pair_val value;
	struct GML_pair *next;
};

struct GML_list_elem {
	char *key;
	struct GML_list_elem *next;
};

struct GML_stat {
	struct GML_error err;
	struct GML_list_elem *key_list;
};

/*
 * returns list of KEY - VALUE pairs. Errors and a pointer to a list
 * of key-names are returned in GML_stat. Previous information contained
 * in GML_stat, i.e. the key_list, will be *lost*.
 */

struct GML_pair *GML_parser(FILE *, struct GML_stat *, int);

/*
 * free memory used in a list of GML_pair
 */

void GML_free_list(struct GML_pair *, struct GML_list_elem *);

/*
 * debugging
 */

void GML_print_list(struct GML_pair *, int);

/* memory wrapping */
extern void gmlparser_free(void *ptr);

/* */
extern void *gmlparser_calloc(int nn, size_t sz);

/* */
extern int gmlparse(struct gml_graph *g, FILE * f, char *fname);

#endif

/* end */
