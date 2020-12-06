
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

#ifndef UNIQNODE_H
#define UNIQNODE_H 1

/* */
extern void clear_uniqnode(struct gml_graph *g);

/* */
extern void clear_uniqnode2(struct gml_graph *g);

/* */
extern void uniqnode_add(struct gml_graph *g, struct gml_node *node);

/* */
extern void uniqnode_add2(struct gml_graph *g, struct gml_node *node);

/* */
extern struct gml_node *uniqnode(struct gml_graph *g, int nr);

/* */
extern struct gml_node *uniqnode2(struct gml_graph *g, int nr);

/* */
extern struct gml_node *uniqnodeid(struct gml_graph *g, int nr);

#endif

/* end */
