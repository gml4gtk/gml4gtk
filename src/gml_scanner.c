
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

/*
 * Scanner for the GML - file format
 * this file has 1 memory leak
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <zlib.h>

#include "main.h"
#include "gml_scanner.h"
#include "gml_parser.h"

/*
 * ISO8859-1 coding of chars >= 160
 */

char *GML_table[] = {
	"&nbsp;",		/* 160 */
	"&iexcl;",
	"&cent;",
	"&pound;",
	"&curren;",
	"&yen;",
	"&brvbar;",
	"&sect;",
	"&uml;",
	"&copy;",
	"&ordf;",		/* 170 */
	"&laquo;",
	"&not;",
	"&shy;",
	"&reg;",
	"&macr;",
	"&deg;",
	"&plusmn;",
	"&sup2;",
	"&sup3;",		/* 180 */
	"&acute;",
	"&micro;",
	"&para;",
	"&middot;",
	"&cedil;",
	"&sup1;",
	"&ordm;",
	"&raquo;",
	"&frac14;",
	"&frac12;",
	"&frac34;",		/* 190 */
	"&iquest;",
	"&Agrave;",
	"&Aacute;",
	"&Acirc;",
	"&Atilde;",
	"&Auml;",
	"&Aring;",
	"&AElig;",
	"&Ccedil;",
	"&Egrave;",		/* 200 */
	"&Eacute;",
	"&Ecirc;",
	"&Euml;",
	"&Igrave;",
	"&Iacute;",
	"&Icirc;",
	"&Iuml;",
	"&ETH;",
	"&Ntilde;",
	"&Ograve;",		/* 210 */
	"&Oacute;",
	"&Ocirc;",
	"&Otilde;",
	"&Ouml;",
	"&times;",
	"&Oslash;",
	"&Ugrave;",
	"&Uacute;",
	"&Ucirc;",
	"&Uuml;",		/* 220 */
	"&Yacute;",
	"&THORN;",
	"&szlig;",
	"&agrave;",
	"&aacute;",
	"&acirc;",
	"&atilde;",
	"&auml;",
	"&aring;",
	"&aelig;",		/* 230 */
	"&ccedil;",
	"&egrave;",
	"&eacute;",
	"&ecirc;",
	"&euml;",
	"&igrave;",
	"&iacute;",
	"&icirc;",
	"&iuml;",
	"&eth;",		/* 240 */
	"&ntilde;",
	"&ograve;",
	"&oacute;",
	"&ocirc;",
	"&otilde;",
	"&ouml;",
	"&divide;",
	"&oslash;",
	"&ugrave;",
	"&uacute;",		/* 250 */
	"&ucirc;",
	"&uuml;",
	"&yacute;",
	"&thorn;",
	"&yuml;"
};

unsigned int GML_line = 0;
unsigned int GML_column = 0;

int GML_search_ISO(char *str, int len)
{

	int i = 0;
	int ret = '&';

	if (strncmp(str, "&quot;", (size_t)len) == 0) {
		return 34;
	} else if (strncmp(str, "&amp;", (size_t)len) == 0) {
		return 38;
	} else if (strncmp(str, "&lt;", (size_t)len) == 0) {
		return 60;
	} else if (strncmp(str, "&gt;", (size_t)len) == 0) {
		return 62;
	}

	for (i = 0; i < 96; i++) {
		if (strncmp(str, GML_table[i], (size_t)len) == 0) {
			ret = i + 160;
			break;
		}
	}

	return ret;
}

void GML_init(void)
{

	GML_line = 1;
	GML_column = 1;

	return;
}

struct GML_token GML_scanner(gzFile source)
{
	unsigned int cur_max_size = INITIAL_SIZE;
	static char buffer[INITIAL_SIZE];
	char *tmp = buffer;
	char *ret = tmp;
	struct GML_token token;
	int is_float = 0;
	unsigned int count = 0;
	int next;
	char ISO_buffer[8];
	int ISO_count;

	assert(source != NULL);

	/*
	 * eliminate preceeding white spaces
	 */

	do {
		next = gzgetc(source);
		GML_column++;

		if (next == '\n') {
			GML_line++;
			GML_column = 1;
		}

	}
	while (isspace(next) && next != EOF);

	if (next == EOF) {

		/*
		 * reached EOF
		 */

		token.kind = GML_END;
		return token;

	} else if (isdigit(next) || next == '.' || next == '+' || next == '-') {

		/* 
		 * floating point or integer 
		 */

		do {
			if (count == INITIAL_SIZE - 1) {
				token.value.err.err_num = GML_TOO_MANY_DIGITS;
				token.value.err.line = GML_line;
				token.value.err.column = GML_column + count;
				token.kind = GML_ERROR;
				return token;
			}

			if (next == '.' || next == 'E') {
				is_float = 1;
			}

			buffer[count] = next;
			count++;
			next = gzgetc(source);

		}
		while (!isspace(next) && next != ']' && next != EOF);

		buffer[count] = 0;

		if (next == ']') {
			gzungetc(next, source);
		}

		if (next == '\n') {
			GML_line++;
			GML_column = 1;
		} else {
			GML_column += count;
		}

		if (is_float) {
			token.value.floating = atof(tmp);
			token.kind = GML_DOUBLE;
		} else {
			token.value.integer = atol(tmp);
			token.kind = GML_INT;
		}

		return token;

	} else if (isalpha(next) || next == '_') {

		/*
		 * key
		 */

		do {
			if (count == cur_max_size - 1) {
				*tmp = 0;
				tmp = (char *)gmlparser_calloc((size_t)1, (2 * cur_max_size * sizeof(char)));
				strcpy(tmp, ret);

				if (cur_max_size > INITIAL_SIZE) {
					gmlparser_free(ret);
				}

				ret = tmp;
				tmp += count;
				cur_max_size *= 2;
			}

			*tmp++ = next;
			count++;
			next = gzgetc(source);
		}
		while (isalnum(next) || next == '_');

		if (next == '\n') {
			GML_line++;
			GML_column = 1;
		} else {
			GML_column += count;
		}

		if (next == '[') {
			gzungetc(next, source);
		} else if (!isspace(next)) {
			token.value.err.err_num = GML_UNEXPECTED;
			token.value.err.line = GML_line;
			token.value.err.column = GML_column + count;
			token.kind = GML_ERROR;

			if (cur_max_size > INITIAL_SIZE) {
				gmlparser_free(ret);
			}

			return token;
		}

		*tmp = 0;
		token.kind = GML_KEY;
/* #warning "memleak here" */
		token.value.string = (char *)gmlparser_calloc((size_t)1, ((count + 1) * sizeof(char)));
		strcpy(token.value.string, ret);

		if (cur_max_size > INITIAL_SIZE) {
			gmlparser_free(ret);
		}

		return token;

	} else {
		/*
		 * comments, brackets and strings
		 */

		switch (next) {
		case '#':
			do {
				next = gzgetc(source);
			}
			while (next != '\n' && next != EOF);

			GML_line++;
			GML_column = 1;
			return GML_scanner(source);

		case '[':
			token.kind = GML_L_BRACKET;
			return token;

		case ']':
			token.kind = GML_R_BRACKET;
			return token;

		case '"':
			next = gzgetc(source);
			GML_column++;

			while (next != '"') {

				if (count >= cur_max_size - 8) {
					*tmp = 0;
					tmp = (char *)gmlparser_calloc((size_t)1, (2 * cur_max_size * sizeof(char)));
					strcpy(tmp, ret);

					if (cur_max_size > INITIAL_SIZE) {
						gmlparser_free(ret);
					}

					ret = tmp;
					tmp += count;
					cur_max_size *= 2;
				}

				if (next == '&') {
					ISO_count = 0;

					while (next != ';') {
						if (next == '"' || next == EOF) {
							gzungetc(next, source);
							ISO_count = 0;
							break;
						}

						if (ISO_count < 8) {
							ISO_buffer[ISO_count] = next;
							ISO_count++;
						}

						next = gzgetc(source);
					}

					if (ISO_count == 8) {
						ISO_count = 0;
					}

					if (ISO_count) {
						ISO_buffer[ISO_count] = ';';
						ISO_count++;
						next = GML_search_ISO(ISO_buffer, ISO_count);
						ISO_count = 0;
						if (ISO_count) {
						}
					} else {
						next = '&';
					}
				}

				*tmp++ = next;
				count++;
				GML_column++;

				next = gzgetc(source);

				if (next == EOF) {
					token.value.err.err_num = GML_PREMATURE_EOF;
					token.value.err.line = GML_line;
					token.value.err.column = GML_column + count;
					token.kind = GML_ERROR;

					if (cur_max_size > INITIAL_SIZE) {
						gmlparser_free(ret);
					}

					return token;
				}

				if (next == '\n') {
					GML_line++;
					GML_column = 1;
				}
			}

			*tmp = 0;
			token.kind = GML_STRING;
			token.value.string = (char *)gmlparser_calloc((size_t)1, ((count + 1) * sizeof(char)));
			strcpy(token.value.string, ret);

			if (cur_max_size > INITIAL_SIZE) {
				gmlparser_free(ret);
			}

			return token;

		default:
			token.value.err.err_num = GML_UNEXPECTED;
			token.value.err.line = GML_line;
			token.value.err.column = GML_column;
			token.kind = GML_ERROR;
			return token;
		}
	}

	/* shouldnothappen */
	token.value.err.err_num = GML_UNEXPECTED;
	token.value.err.line = GML_line;
	token.value.err.column = GML_column;
	token.kind = GML_ERROR;
	return token;
}

/* end */
