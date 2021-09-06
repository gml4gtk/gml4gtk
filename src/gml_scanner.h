
/*
 *  Copyright 2021
 *  (C) Universitaet Passau 1986-1991
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

#ifndef GML_SCANNER_H
#define GML_SCANNER_H 1

/*
 * start-size of buffers for reading strings. If too small it will be enlarged
 * dynamically
 */

#define INITIAL_SIZE 1024

typedef enum {
	GML_KEY, GML_INT, GML_DOUBLE, GML_STRING, GML_L_BRACKET,
	GML_R_BRACKET, GML_END, GML_LIST, GML_ERROR
} GML_value;

typedef enum {
	GML_UNEXPECTED, GML_SYNTAX, GML_PREMATURE_EOF, GML_TOO_MANY_DIGITS,
	GML_OPEN_BRACKET, GML_TOO_MANY_BRACKETS, GML_OK
} GML_error_value;

struct GML_error {
	GML_error_value err_num;
	unsigned int line;
	unsigned int column;
};

union GML_tok_val {
	long integer;
	double floating;
	char *string;
	struct GML_error err;
};

struct GML_token {
	GML_value kind;
	union GML_tok_val value;
};

/*
 * global variables
 */

extern unsigned int GML_line;
extern unsigned int GML_column;

/*
 * if you are interested in the position where an error occured it is a good
 * idea to set GML_line and GML_column back.
 * This is what GML_init does.
 */

extern void GML_init(void);

/*
 * returns the next token in file. If an error occured it will be stored in
 * GML_token.
 */

extern struct GML_token GML_scanner(gzFile stream);

extern int GML_search_ISO(char *str, int len);

#endif

/* end */
