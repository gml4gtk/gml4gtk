
/*
 *  Copyright 2021
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

#ifndef HIER_H
#define HIER_H 1

/* the graph data rootgraph */
extern struct gml_graph *maingraph;

/* type of graph data 0=gml 1=dot 2=vcg */
extern int graphtype;

/* if set use priority algorithm for placement otherwise brandes and kopf */
extern int option_priority;

/* if set do node names instead of node label */
extern int option_nnames;

/* if set mirror in y direction */
extern int option_mirrory;

/* if set do node label popup */
extern int option_popup;

/* if 1 allow incremental layout for clusters if any */
extern int incrlayout;

/* type of barycenter, 0 is sugi2, 1 is rhp */
extern int barytype;

/* edgelabels on/off */
extern int option_edgelabels;

/* labels on/off */
extern int option_labels;

/* positioning mode */
extern int postype;

/* parser messages */
extern char parsermessage[256];

/* max x of end drawing */
extern int maxx;

/* max y of end drawing */
extern int maxy;

/* (x,y) spacing in the drawing raster */
extern int xspacing;
extern int yspacing;

/* background r/g/b of drawing */
extern int bgcr;
extern int bgcg;
extern int bgcb;

/* type of level placement */
extern int ranktype;

/* run barycenter */
extern void barycenter(struct gml_graph *g, int it1val, int it2val);

/* longest path algorithm */
extern void longestpath(struct gml_graph *g);

/* reorg nodelist */
extern void reorg(struct gml_graph *g);

/* prepare */
extern void prep(struct gml_graph *g);

/* set edges with labels */
extern void prepel(struct gml_graph *g);

/* determine startnodes */
extern void startnodes(struct gml_graph *g);

/* determine startnodes */
extern void startnodesafter(struct gml_graph *g);

/* final after barycenter */
extern void finalafter(struct gml_graph *g);

/* prepare */
extern void prepincr(struct gml_graph *g);

/* write graph data as dia diagram */
extern void graph2dia(struct gml_graph *g, FILE * fout);

/* write graph data as jgf json */
extern void graph2jgf(struct gml_graph *g, FILE * fout);

/* calculate edge connections */
extern void edgeconnections(struct gml_graph *g);

/* clear self-edges node list */
extern void clear_selfedgesnodelist_r(struct gml_graph *g);

/* clear nr. of edges between level n and n+1 */
extern void clear_nume_r(struct gml_graph *g);

/* clear arrays in/out edges */
extern void clear_ioedges_r(struct gml_graph *g);

/* clear the s/t list of a node */
extern void clear_stlist(struct gml_node *node);

/* clear the s/t list of all nodes */
extern void clear_stlist_all(struct gml_graph *g);

/* free nodelist and nodes */
extern void clear_rawnodelist(struct gml_graph *g);

/* free edgelist */
extern void clear_rawedgelist(struct gml_graph *g);

/* clear optional edge label data */
extern void clear_edgelabeldata(struct gml_graph *g);

/* free nodelist and nodes */
extern void clear_nodelist_r(struct gml_graph *g, int mode);

/* free single nodelist */
extern void clear_singlenodelist_r(struct gml_graph *g);

/* free edgelist */
extern void clear_edgelist_r(struct gml_graph *g);

/* rebuild nodes st lists */
extern void make_stlist(struct gml_graph *g);

/* delete edge */
extern void del_edge(struct gml_graph *g, struct gml_elist *edgeel);

/* splits edgelabel edges into node->label->node */
extern void edgelabels(struct gml_graph *g, int mode);

/* break cycles in the graph */
extern void uncycle(struct gml_graph *g);

/* all edges downwards */
extern void edgesdownwards(struct gml_graph *g, int mode);

/* set rel. y level of all nodes */
extern void ylevels(struct gml_graph *g);

/* dfs check again and revers if needed */
extern void edgelen(struct gml_graph *g);

/* try to find shorter edges */
extern void shorteredges(struct gml_graph *g);

/* doublespace the vertical levels */
extern void doublespacey(struct gml_graph *g);

/* doublespace the vertical levels */
extern void doublespaceyafter(struct gml_graph *g);

/* check for same edges */
extern void checksame(struct gml_graph *g);

/* split same edges */
extern void splitsame(struct gml_graph *g);

/* split longer edges */
extern void splitedges(struct gml_graph *g, int after);

/* split longer edges */
extern void splitedgesafter(struct gml_graph *g);

/* create level node count data */
extern void nodecounts(struct gml_graph *g);

/* create level node count data */
extern void nodecountsafter(struct gml_graph *g);

/* */
extern void add_new_node(struct gml_graph *g, struct gml_graph *ro, int nr,
			 int foundid, char *nodename, char *nodelabel, int ncolor, int nbcolor, struct gml_rl *rlabel,
			 struct gml_hl *hlabel, int fontcolor, int ishtml);

/* */
extern void add_new_dummynode(struct gml_graph *g, int foundid);

/* */
extern void
add_new_edge(struct gml_graph *g, struct gml_graph *ro, int foundsource,
	     int foundtarget, char *elabel, int ecolor, int style, char *fcompass, char *tcompass, int constraint, int ishtml);

/* */
extern void add_new_dummyedge(struct gml_graph *g, struct gml_edge *rawedge, struct gml_graph *ro,
			      int foundsource, int foundtarget, int reversed,
			      int ecolor, int style, char *fcompass, char *tcompass, int constraint, struct gml_el *eldata);

/* lists per position */
extern void make_posnodes(struct gml_graph *g);

/* clear pos. nodes lists */
extern void clear_posnodes_r(struct gml_graph *g);

/* lists per level */
extern void make_levelnodes(struct gml_graph *g);

/* clear level nodes lists */
extern void clear_levelnodes_r(struct gml_graph *g);

/* clear list of startnodes */
extern void clear_startnodes_r(struct gml_graph *g);

/* clear record labels */
extern void clear_rlabel_r(struct gml_graph *g);

/* clear html labels */
extern void clear_hlabel_r(struct gml_graph *g);

/* */
extern void clear_numce_r(struct gml_graph *g);

/* clear number of nodes at level */
extern void clear_nnl_r(struct gml_graph *g);

/* clear subgraphs and optional summary node */
extern void clear_sg(struct gml_graph *sg);

/* create root graph */
extern void create_maingraph(void);

/* create subgraphs */
extern void create_sg(int nr, char *name, char *label, int type);

#endif

/* end */
