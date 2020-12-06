
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

#ifndef VCG_YY_H
#define VCG_YY_H 1

/* */
extern int vcgdebug;

/* */
extern char *vcgtext;

/* */
extern char *vcglaststring;

/* */
extern int vcglineno;

/* */
extern void vcg_lex_init(FILE * f, int debug);

/* */
extern void vcg_lex_clear(void);

 /* */
extern void vcg_yydebug(int debugflag);

#endif

/* end */
