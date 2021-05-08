
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
struct gml_hl;

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
	int fbbx;		/* bounding box xsize full sized */
	int fbby;		/* bounding box ysize full sized */
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
	char drawrh;		/* if set draw r/h labels */
	char dummy;		/* set to 1 if dummy node */
	char hashedge;		/* set to 1 if node has hor. edges */
	char elabel;		/* set if node is a edge label */
	char ishtml;		/* set if label is html label <> */
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
	struct gml_hl *hlabel;	/* optional html label data */
	int hlabeldone;		/* set if textsizes hlabel are set */
	int ncolor;		/* r/g/b fill color of node */
	int nbcolor;		/* r/g/b border color of node */
	int fontcolor;		/* r/g/b color of label text */
	int secolor;		/* r/g/b fill color of self-edge at node if any */
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
	int ishtml;		/* set if elabel is <> html label */
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

/* one item of text:
 * bgcolor is default white 0x00ffffff
 * then set by optional node fillcolor
 * then set by optional <table> bgcolor
 * then set by optional <td> bgcolor
 */
struct gml_hitem {
	char *text;		/* text to display modified */
	char *otext;		/* text to display original */
	char *fontstr;		/* pango font format string */
	char *fontdesc;		/* pango font description */
	char *fontname;		/* optional font name */
	char *fontslant;	/* font slant */
	char *fontweight;	/* fontweight */
	int fontsize;		/* optional pointsize */
	int fontcolor;		/* optional color of text */
	int ncolor;		/* optional background color from <td> or <table> */
	int txsizemin;		/* min. text x size of all lines */
	int tysizemin;		/* min. text y size of all lines */
	int txsize;		/* text x size of all lines */
	int tysize;		/* text y size of all lines */
	int txoff;		/* text x offset in 1 line */
	int tyoff;		/* text y offset in 1 line */
	int lysize;		/* y size of this text line */
	int yoff;		/* y offset of line */
	struct {
		unsigned int at:1;	/* set if str has a '&' */
		unsigned int br:1;	/* set if str is a <br/> token */
		unsigned int img:1;	/* set if str is a <img> */
		unsigned int i:1;	/* set if str is <i> italic */
		unsigned int u:1;	/* set if str is <u> underline */
		unsigned int o:1;	/* set if str is <o> overline */
		unsigned int s:1;	/* set if str is <s> strike-through */
		unsigned int sub:1;	/* set if str is <sub> subscript */
		unsigned int sup:1;	/* set if str is <sup> superscript */
		unsigned int hr:1;	/* set if str is a <hr> token */

		unsigned int vr:1;	/* set if str is a <vr> token */
		unsigned int b:1;	/* set if str is <b> bold */
		unsigned int table:1;	/* set if a <table> not string */
		unsigned int bit13:1;
		unsigned int bit14:1;
		unsigned int bit15:1;
		unsigned int bit16:1;
		unsigned int bit17:1;
		unsigned int bit18:1;
		unsigned int bit19:1;

		unsigned int bit20:1;
		unsigned int bit21:1;
		unsigned int bit22:1;
		unsigned int bit23:1;
		unsigned int bit24:1;
		unsigned int bit25:1;
		unsigned int bit26:1;
		unsigned int bit27:1;
		unsigned int bit28:1;
		unsigned int bit29:1;

		unsigned int bit30:1;
		unsigned int bit31:1;
	} bitflags;
	struct gml_titem *rootedon;	/* item is part of <table> */
	struct gml_titem *table;	/* item is a <table> */
};

/* list with text items in html string */
struct gml_hilist {
	struct gml_hitem *items;
	struct gml_hilist *next;
};

/* one <td> */
struct gml_tditem {
	struct gml_hilist *il;	/* list of text items */
	struct gml_hilist *ilend;
	struct gml_titem *rootedon;	/* <td> is part of <table> */
	/* data from input */
	int bgcolor;		/* ="colorname" */
	int border;		/* ="int-value" */
	int cellpadding;	/* ="int-value" */
	int cellspacing;	/* ="int-value" */
	int color;		/* ="colorname" */
	int colspan;		/* ="int-value" */
	int height;		/* ="int-value" */
	int rowspan;		/* ="int-value" */
	int width;		/* ="int-value" */
	/* */
	int xsize;		/* x size of <td> at col <tr> */
	int ysize;		/* y size of <td> at col <tr> */
	int xsizemin;		/* min. x size of <td> at col <tr> */
	int ysizemin;		/* min. y size of <td> at col <tr> */
	int xstep;		/* x step size for this <td> */
	int ystep;		/* y step size for this <td> */
	/* */
	int istab;		/* set if <td> is a <table> */
	int dummy;		/* set if <td> is dummy to fill the table */
	struct gml_tditem *next;
};

/* one <tr> item */
struct gml_tritem {
	struct gml_tditem *tdi;
	struct gml_tditem *tdiend;
	struct gml_titem *rootedon;	/* <tr> is part of <table> */
	/* data of <tr> */
	int numtd;		/* number of <td> statements in this <tr> */
	/* placement data */
	int ysize;		/* y size of this <tr> for the <td> elements */
	int hastab;		/* set if <tr> has a <td> with <table> data */
};

/* list with <tr> items */
struct gml_tritemlist {
	struct gml_tritem *tritem;
	struct gml_tritemlist *next;
};

/* table data */
struct gml_titem {
	struct gml_htlist *tl;	/* list of sub table items */
	struct gml_htlist *tlend;
	struct gml_tritemlist *tr;	/* list of <tr> items in this table */
	struct gml_tritemlist *trend;
	/* data of table */
	int xoff;		/* x offset */
	int yoff;		/* y offset */
	int txsize;		/* x size of table */
	int tysize;		/* y size of table */
	int txsizemin;		/* min. x size of table */
	int tysizemin;		/* min. y size of table */
	int numtr;		/* number of <tr> statements */
	int numtd;		/* number of <td> needed in table */
	int ncols;		/* number of columns x */
	int nrows;		/* number of rows y */
	int sizeset;		/* set if min. size is known */
	/* input table data */
	int bgcolor;		/* background color */
	int color;		/* fontcolor */
	int cellborder;		/* ="int-value" */
	int cellpadding;	/* ="int-value" */
	int cellspacing;	/* ="int-value" */
	int height;		/* ="int-value" */
	int width;		/* ="int-value" */
};

/* list with table elements in html string */
struct gml_htlist {
	struct gml_titem *titem;
	struct gml_htlist *next;
};

/* html label with items or tables */
struct gml_hl {
	int mode;		/* 0=items, 1=tables */
	struct gml_hilist *il;	/* list of text items */
	struct gml_hilist *ilend;
	struct gml_htlist *tl;	/* list of <table> items */
	struct gml_htlist *tlend;
};

/* in gui code, update status text crossings */
extern void update_status_text_cross(char *text);

#endif

/* end */
