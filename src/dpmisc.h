
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

#ifndef DPMISC_H
#define DPMISC_H 1

/* return 0 if str is a number string */
extern int dp_chknum (char *str);

/* return 1 if is a compass point */
extern int dp_iscompass (char *compass);

/* is a known shape name, -1 at error */
extern int dp_isdotshape (char *s);

/* check data, 0 if oke */
extern int dp_datachk(void);

extern int dp_islabelloc (char *loc);

/* parse number */
extern struct dpnum *dp_getnum (char *s);

/* parse boolean */
extern struct dpbool *dp_getbool (char *s);

/* */
extern struct dpcolor *dp_getcolor (int cs,int scheme,char *s);

/* parse style= */
extern struct dpstyle *dp_getstyle (char *s);

/* parse edge arrow style */
extern struct dparrow *dp_getarrow (char *s);

/* edge arrow direction */
extern struct dpdir *dp_getdir (char *s);

/* point (x,y) with optional '!' flag */
extern struct dppoint *dp_getpoint (char *s);

/* get rect %f,%f,%f,%f */
extern struct dprect *dp_getrect (char *s);

/* clusterrank value */
extern int dp_getclrank (char *s);

/* margin */
extern struct dpmargin *dp_getmargin (char *s);

/* outputorder */
extern struct dpoo *dp_getoo (char *s);

/* rank */
extern struct dprank *dp_getrank (char *s);

/* rankdir */
extern struct dprankdir *dp_getrankdir (char *s);

/* ranksep */
extern struct dpranksep *dp_getranksep (char *s);

/* ratio */
extern struct dpratio *dp_getratio (char *s);

/* splines */
extern struct dpsplines *dp_getsplines (char *s);

/* check nodes with record labels */
extern int dp_chkrec(void);

#endif

/* end */
