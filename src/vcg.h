
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
 */

#ifndef VCG_H
#define VCG_H 1

struct vcgn;
struct vcge;

/* node */
struct vcgn {
	int nr;
	int finalnr;
	char *name;
	char *label;
	int shape;
	struct vcgn *next;
};

/* edge */
struct vcge {
	int nr;
	int fnn;
	char *fns;
	struct vcgn *fromnode;
	int tnn;
	char *tns;
	struct vcgn *tonode;
	char *label;
	struct vcge *next;
};

/* parse gcc vcg file */
extern int vcgparse(struct gml_graph *g, FILE * f, char *fname, char *argv0);

/* in vcg.l */
extern int vcglex(void);

/* in vcg.l */
extern void vcg_lex_init(FILE * f, int debugflag);

/* in vcg.l */
extern void vcg_lex_clear(void);

#endif

/* end */
