
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

#ifndef MAIN_H
#define MAIN_H 1

/* types of subgraphs */
#define SG_ROOT 0		/* root */
#define SG_COMPOUND 1		/* compound {} */
#define SG_SUBG 2		/* subgraph {} */
#define SG_CLUSTER 3		/* subgraph cluster {} */

/* type of nodes */
#define NODE_SUM 1		/* summary node */

struct gml_graph;
struct gml_node;
struct gml_edge;
struct gml_elist;
struct gml_nlist;
struct gml_glist;
struct gml_rl;
struct gml_p;

struct gml_graph {
	int id;			/* uniq number and 0 is rootgraph */
	char *graphname;	/* name of subgraph */
	char *label;		/* label of subgraph */
	int type;		/* type of subgraph */

	int tnclusters;		/* total number of clusters in whole graph at rootgraph */
	int tnnodes;		/* total number of input nodes in whole graph */
	int tnedges;		/* total number of input edges in whole graph */
	int tnedgelabels;	/* total number of edge labels in whole graph */

	int maxlevel;		/* max. level in graph */
	int *nnodes_of_level;	/* number of nodes at level */

	int nnodes;		/* number of input nodes */
	int nedges;		/* number of input edges */

	int nodenum;		/* node uniq number starting at 1 */
	int edgenum;		/* edge uniq number starting at 1 */

	int nedgelabels;	/* number of edge labels */
	int nhedges;		/* number of horizontal edges */
	int nselfedges;		/* number of self edges in the graph */
	int nstartnodes;	/* number of starting subgraphs */
	int nsinglenodes;	/* number of single nodes in the graph */
	int startnodeslevel;	/* where the actual drawing starts at y-level */
	int *startnodes;	/* table with startnode numbers */

	int *nume;		/* number of edges between level n and n+1 */
	int widestlevel;	/* level with most nodes */
	int widestnnodes;	/* number of nodes at widest level */
	int *wpos;		/* width of positions */
	int *hpos;		/* height of levels */
	struct gml_nlist **posnodes;	/* lists per pos. */
	struct gml_nlist **levelnodes;	/* lists per level */

	/* the raw parsed node/edge list */
	struct gml_nlist *rawnodelist;
	struct gml_nlist *rawnodelisttail;
	struct gml_elist *rawedgelist;
	struct gml_elist *rawedgelisttail;
	/* */

	/* the used and changed node/edge/single-node list */
	struct gml_nlist *nodelist;
	struct gml_nlist *nodelisttail;
	struct gml_elist *edgelist;
	struct gml_elist *edgelisttail;
	struct gml_nlist *singlenodelist;
	struct gml_nlist *singlenodelisttail;
	struct gml_nlist *selfedgesnodelist;
	struct gml_nlist *selfedgesnodelisttail;

	struct gml_glist *subglist;	/* subgraphs */
	struct gml_glist *subglistend;

	int sugi_icrossings;	/* sugiyama initial crossings */
	int sugi_fcrossings;	/* sugiyama final crossings */
	int sugi_changes;	/* sugiyama changes made */
	int *numce;		/* number of edge crossings per level */
};

/* list of subgraphs */
struct gml_glist {
	struct gml_graph *sg;
	struct gml_glist *next;
};

struct gml_node {
	struct gml_graph *rootedon;	/* graph where node is located */
	int nr;			/* uniq node number starting at 1 */
	int type;		/* type of node */
	int id;			/* id number as in gml graph */
	char *name;		/* name of node or label */
	int startnode;		/* node belongs to part of graph with this startnode */
	int objectnr;		/* dia xml object number */
	int x;			/* */
	int y;			/* */
	int relx;		/* relative x pos. */
	int rely;		/* relative y pos. */
	int absx;		/* absolute x pos. */
	int absy;		/* absolute y pos. */
	int bbx;		/* bounding box xsize */
	int bby;		/* bounding box ysize */
	int finx;		/* final x pos */
	int finy;		/* final y pos */
	int tx;			/* text xsize */
	int ty;			/* text ysize */
	int lx0;		/* start of level x pos where node is */
	int lx1;		/* end of level x pos where node is */
	int ly0;		/* start of level y pos where node is */
	int ly1;		/* end of level y pos where node is */
	char txsize;		/* set if node text size is calculated */
	char incluster;		/* set if node is in a cluster layout */
	char dummy;		/* set to 1 if dummy node */
	char hashedge;		/* set to 1 if node has hor. edges */
	char elabel;		/* set if node is a edge label */
	int nselfedges;		/* number of self edges at this node */
	struct gml_elist *outgoing_e;	/* source list, outgoing edges */
	struct gml_elist *outgoing_etail;	/* source list, outgoing edges */
	struct gml_edge **oedges;	/* array outgoing edges */
	int dx_oedges;		/* x distance between outgoing edges */
	struct gml_elist *incoming_e;	/* target list, incoming edges */
	struct gml_elist *incoming_etail;	/* target list, incoming edges */
	struct gml_edge **iedges;	/* array incoming edges */
	int dx_iedges;		/* x distance between incoming edges */
	char *nlabel;		/* optional label or the id */
	struct gml_rl *rlabel;	/* optional record label data */
	int rlabeldone;		/* set if textsizes rlabel are set */
	int ncolor;		/* r/g/b fill color of node */
	int nbcolor;		/* r/g/b border color of node */
	int fontcolor;		/* r/g/b color of label text */
	int indegree;		/* incoming edges to node */
	int outdegree;		/* outgoing edges from node */
	struct gml_node *el_fnode;	/* in edge-label the from-node */
	struct gml_node *el_tnode;	/* in edge-label the to-node */
	int done;		/* dfs black/white */
	int grey;		/* dfs grey */
};

struct gml_nlist {
	struct gml_node *node;
	struct gml_nlist *next;
};

struct gml_edge {
	int nr;			/* uniq number staring at 1 */
	int done;		/* edge is done */
	struct gml_graph *rootedon;	/* graph where edge is located */
	struct gml_node *from_node;	/* from node */
	struct gml_node *to_node;	/* to node */
	char incluster;		/* set if edge is in cluster layout */
	char reversed;		/* set if edge is reversed */
	char hedge;		/* set if edge is horizontal line */
	char vedge;		/* set if edge is vertical */
	char *elabel;		/* optional edge label */
	int ecolor;		/* r/g/b edge line color */
	int style;		/* edge line style, solid dotted dashed */
	char *fcompass;		/* optional from-compass point */
	char *tcompass;		/* optional to-compass point */
	char constraint;	/* dot edge constraint */
};

struct gml_elist {
	struct gml_edge *edge;
	struct gml_elist *next;
};

/* record label */
struct gml_rl {
	int hd;			/* has-data */
	int dir;		/* x or y direction */
	int nparts;		/* how many parts */
	struct gml_rl **parts;	/* subparts */
	char *port;		/* port name */
	char *label;		/* original label */
	char *ulabel;		/* updated label */
	int txsize;		/* text x size */
	int tysize;		/* text y size */
	int bbx;		/* total x size */
	int bby;		/* total y size */
	int xoff;		/* x offset */
	int yoff;		/* y offset */
	int xstep;		/* x stepsize */
	int ystep;		/* y stepsize */
};

/* (x,y) point */
struct gml_p {
	int x;
	int y;
};

extern void update_status_text_cross(char *text);

#endif

/* end */
