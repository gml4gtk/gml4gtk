
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
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

/*
 * the dp*.c dp*.h files are about DotParsing */

#ifndef DP_H
#define DP_H 1

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS		/* empty */
#define __END_DECLS		/* empty */
#endif

__BEGIN_DECLS
/* types of subgraphs */
#define DP_SG_ROOT 0		/* root graph type */
#define DP_SG_CO 1		/* compound subgraph {} */
#define DP_SG_NM 2		/* named subgrph */
#define DP_SG_CL 3		/* cluster subgraph */
#define DP_SG_NN 4		/* no name subgraph */
/* spline modes */
#define DP_SPLINE_NONE 1
#define DP_SPLINE_LINE 2
#define DP_SPLINE_POLY 3
#define DP_SPLINE_CURVED 4
#define DP_SPLINE_ORTHO 5
#define DP_SPLINE_SPLINE 6
#define DP_SPLINE_COMP 7
/* ratio modes */
#define DP_RATIO_FILL 1
#define DP_RATIO_COM 2
#define DP_RATIO_EXP 3
#define DP_RATIO_AUTO 4
/* graph rankdir */
#define DP_RANKDIR_TB 1
#define DP_RANKDIR_LR 2
#define DP_RANKDIR_BT 3
#define DP_RANKDIR_RL 4
/* graph rank added rank=none */
#define DP_RANK_SAME 1
#define DP_RANK_MIN 2
#define DP_RANK_SRC 3
#define DP_RANK_MAX 4
#define DP_RANK_SINK 5
#define DP_RANK_NONE 6
/* graph output order modes, 0 means undefined */
#define DP_OO_BF 1		/* breadthfirst */
#define DP_OO_NF 2		/* nodesfirst */
#define DP_OO_EF 3		/* edgesfirst */
/* edge arrow directions */
#define DP_DIR_NONE 1
#define DP_DIR_BOTH 2
#define DP_DIR_BACK 3
#define DP_DIR_FORWARD 4
/* edge arrow basic types */
#define DP_EA_BOX 1		/* "box" */
#define DP_EA_CROW 2		/* "crow" */
#define DP_EA_CURVE 3		/* "curve" */
#define DP_EA_ICURVE 4		/* "icurve" */
#define DP_EA_DIAMOND 5		/* "diamond" */
#define DP_EA_DOT 6		/* "dot" */
#define DP_EA_INV 7		/* "inv" */
#define DP_EA_NONE 8		/* "none" */
#define DP_EA_NORMAL 9		/* "normal" */
#define DP_EA_TEE 10		/* "tee" */
#define DP_EA_VEE 11		/* "vee" */
#define DP_EA_UNKNOWN 0;
/* labelloc, t,b,c, default c for node, b for graph */
#define DP_LLT 1		/* top */
#define DP_LLB 2		/* bottom */
#define DP_LLC 3		/* center */
/* states during parse */
#define DP_TGRAPH 1
#define DP_TNODE 2
#define DP_TEDGE 3
#define DP_TGRAPHDEF 4
#define DP_TNODEDEF 5
#define DP_TEDGEDEF 6
#define DP_SGRAPH 7
/* node shapes */
#define DPSHAPE_ASSEMBLY 1	/* "assembly" */
#define DPSHAPE_BOX 2		/* "box" */
#define DPSHAPE_BOX3D 3		/* "box3d" */
#define DPSHAPE_CDS 4		/* "cds" */
#define DPSHAPE_CIRCLE 5	/* "circle" */
#define DPSHAPE_COMPONENT 6	/* "component" */
#define DPSHAPE_CYLINDER 7	/* "cylinder" */
#define DPSHAPE_DIAMOND 8	/* "diamond" */
#define DPSHAPE_DOUBLECIRCLE 9	/* "doublecircle" */
#define DPSHAPE_DOUBLEOCTAGON 10	/* "doubleoctagon" */
#define DPSHAPE_EGG 11		/* "egg" */
#define DPSHAPE_ELLIPSE 12	/* "ellipse" */
#define DPSHAPE_FIVEPOVERHANG 13	/* "fivepoverhang" */
#define DPSHAPE_FOLDER 14	/* "folder" */
#define DPSHAPE_HEXAGON 15	/* "hexagon" */
#define DPSHAPE_HOUSE 16	/* "house" */
#define DPSHAPE_INSULATOR 17	/* "insulator" */
#define DPSHAPE_INVHOUSE 18	/* "invhouse" */
#define DPSHAPE_INVTRAPEZIUM 19	/* "invtrapezium" */
#define DPSHAPE_INVTRIANGLE 20	/* "invtriangle" */
#define DPSHAPE_LARROW 21	/* "larrow" */
#define DPSHAPE_LPROMOTOR 22	/* "lpromoter" */
#define DPSHAPE_MCIRCLE 23	/* "Mcircle" */
#define DPSHAPE_MDIAMOND 24	/* "Mdiamond" */
#define DPSHAPE_MSQUARE 25	/* "Msquare" */
#define DPSHAPE_NONE 26		/* "none" */
#define DPSHAPE_NOTE 27		/* "note" */
#define DPSHAPE_NOVERHANG 28	/* "noverhang" */
#define DPSHAPE_OCTAGON 29	/* "octagon" */
#define DPSHAPE_OVAL 30		/* "oval" */
#define DPSHAPE_PARALLELOGRAM 31	/* "parallelogram" */
#define DPSHAPE_PENTAGON 32	/* "pentagon" */
#define DPSHAPE_PLAIN 33	/* "plain" */
#define DPSHAPE_PLAINTEXT 34	/* "plaintext" */
#define DPSHAPE_POINT 35	/* "point" */
#define DPSHAPE_POLYGON 36	/* "polygon" */
#define DPSHAPE_PRIMERSITE 37	/* "primersite" */
#define DPSHAPE_PROMOTER 38	/* "promoter" */
#define DPSHAPE_PROTEASESITE 39	/* "proteasesite" */
#define DPSHAPE_PROTEINSTAB 40	/* "proteinstab" */
#define DPSHAPE_RARROW 41	/* "rarrow" */
#define DPSHAPE_RECT 42		/* "rect" */
#define DPSHAPE_RECTANGLE 43	/* "rectangle" */
#define DPSHAPE_RESTRICTIONSITE 44	/* "restrictionsite" */
#define DPSHAPE_RIBOSITE 45	/* "ribosite" */
#define DPSHAPE_RNASTAB 46	/* "rnastab" */
#define DPSHAPE_RPROMOTER 47	/* "rpromoter" */
#define DPSHAPE_SEPTAGON 48	/* "septagon" */
#define DPSHAPE_SIGNATURE 49	/* "signature" */
#define DPSHAPE_SQUARE 50	/* "square" */
#define DPSHAPE_STAR 51		/* "star" */
#define DPSHAPE_TAB 52		/* "tab" */
#define DPSHAPE_TERMINATOR 53	/* "terminator" */
#define DPSHAPE_THREEPOVERHANG 54	/* "threepoverhang" */
#define DPSHAPE_TRAPEZIUM 55	/* "trapezium" */
#define DPSHAPE_TRIANGLE 56	/* "triangle" */
#define DPSHAPE_TRIPLEOCTAGON 57	/* "tripleoctagon" */
#define DPSHAPE_UNDERLINE 58	/* "underline" */
#define DPSHAPE_UTR 59		/* "utr" */
#define DPSHAPE_RECORD 60	/* "record" special shape */
#define DPSHAPE_MRECORD 61	/* "record" special shape */
/* values for align html setting */
#define DP_ALIGNC 1		/* center */
#define DP_ALIGNL 2		/* left */
#define DP_ALIGNR 3		/* right */
#define DP_ALIGNT 4		/* text */
/* values for valign html setting */
#define DP_VALIGNM 1		/* middle */
#define DP_VALIGNB 2		/* bottom */
#define DP_VALIGNT 3		/* top */
/* values for html img scale */
#define DP_IMGF 1		/* "false" */
#define DP_IMGT 2		/* "true" */
#define DP_IMGW 3		/* "width" */
#define DP_IMGH 4		/* "height" */
#define DP_IMGB 5		/* "both" */
/* numbers for <tags> in html strings */
#define T_TD 1			/* <td> */
#define T_TABLE 2		/* <table> */
#define T_FONT 3		/* <font> */
#define T_IMG 4			/* <img> */
#define T_BR 5			/* <br> */
/* true/false for fixedsize in html strings */
#define DP_TRUE 1		/* true */
#define DP_FALSE 0		/* false */
    struct dpgraph;
struct dpnode;
struct dpepoint;
struct dpnlink;
struct dpeplink;
struct dpglink;
struct dptmpe;
struct dptelink;
struct dpedge;
struct dpelink;
struct dppart;
struct dpnum;
struct dpbool;
struct dpcolor;
struct dpstyle;
struct dpdir;
struct dppoint;
struct dprect;
struct dpmargin;
struct dpoo;
struct dprank;
struct dprankdir;
struct dpranksep;
struct dpratio;
struct dpsplines;
struct hlpart;

/* */
struct dpgraph {
	int nr;			/* uniq graph number */
	int type;		/* type of subgraph */
	struct dpgraph *rootedon;	/* graph is rooted on */
	char tag;		/* tag */
	char *etype;		/* -- or -> */
	char *graphname;	/* "" or name */
	int cluster;		/* set if graphname start with cluster */
	int nnodes;		/* number of nodes */
	int nnedges;		/* number of edges */
	int nngraph;		/* number of graphs */
	splay_tree gattr;	/* graph[] attributes */
	splay_tree nattr;	/* node[] attributes */
	splay_tree eattr;	/* edge[] attributes */
	struct dpnode *defnode;	/* node with defaults */
	struct dpedge *defedge;	/* edge with defaults */

	struct dpeplink *dpeplist;	/* edge points list */
	struct dpeplink *dpeplistend;	/* edge points list */
	struct dpnlink *dpnodes;	/* node in this graph */
	struct dpnlink *dpnodesend;	/* node in this graph */
	struct dpelink *dpedges;	/* edges starting in this graph */
	struct dpelink *dpedgesend;	/* edges starting in this graph */
	struct dpglink *dpsubg;	/* subgraphs */
	struct dpglink *dpsubgend;	/* subgraphs */

	int enest;		/* nesting counter */

	int yylineno;		/* line number where graph starts */

	int color;
	int bgcolor;		/* rgb background color */
	int fontcolor;
	int fcolor;
	int pencolor;
	int csnum;		/* color scheme number or 0 */
	double penwidth;	/* */
	char *bb;		/* bb string */
	double bbx0;		/* bb number */
	double bby0;		/* bb number */
	double bbx1;		/* bb number */
	double bby1;		/* bb number */
	char *url;		/* url */
	char *charset;		/* charset */
	int clrank;		/* clusterrank  none,local,global */
	char *comment;		/* device data */
	double dpi;		/* svg dpi */
	char *fontname;		/* fontname */
	char *fontpath;		/* fontpath */
	double fontsize;	/* fontsize 14, min 1. */
	char *id;		/* imagemap id */
	char *label;		/* label */
	char *labelj;		/* label justify for cluster is l,r or other c center */
	int labelloc;		/* label location t,b,c */
	char *layers;		/* layers */
	char *layerls;		/* layerlistsep chars */
	char *layersep;		/* layersep chars */
	char *layersel;		/* layerselect */
	char *layout;		/* layout */
	double lheight;		/* lheight */
	double lwidth;		/* lwidth */
	char *lp;		/* lp */
	double lpx;		/* lp */
	double lpy;		/* lp */
	int lpflag;		/* lp */
	char *margin;		/* margin */
	double marginx;		/* margin */
	double marginy;		/* margin */
	double mclimit;		/* mclimit layout stop factor */
	double nodesep;		/* nodesep */
	double nslimit;		/* nslimit */
	double nslimit1;	/* nslimit1 */
	char *ordering;		/* ordering */
	char *orientation;	/* landscape orientation */
	int oorder;		/* outputorder mode */
	double pack;		/* pack number or bool */
	char *packmode;		/* scc packing */
	char *pad;		/* padding around drawing */
	double peripheries;	/* cluster peripheries */
	double quantum;		/* round factor */
	int rank;		/* rank type or 0 */
	int rankdir;		/* rankdir type or 0 */
	double ranksep;		/* ranksep number */
	double ratio;		/* ratio */
	int ratiomode;		/* ratio */
	double rotate;		/* rotate in degrees int */
	double ssize;		/* searchsize */
	double sboxes;		/* showboxes */
	double sizex;		/* size */
	double sizey;		/* size */
	int sizeflag;		/* size */
	double sortv;		/* sortv */
	int splines;		/* splines type */
	char *viewport;		/* viewport numbes as string */

	struct {
		unsigned int bgcolorset:1;	/* set if background color bgcolor specified */
		unsigned int penwidthset:1;
		unsigned int csnumset:1;
		unsigned int colorset:1;
		unsigned int fontcolorset:1;
		unsigned int fcolorset:1;	/* fill color */
		unsigned int pencolorset:1;
		unsigned int bbset:1;	/* set if bb specified */
		unsigned int center:1;	/* center drawing */
		unsigned int centerset:1;	/* set if center specified */

		unsigned int urlset:1;	/* set if url specified */
		unsigned int charsset:1;	/* set if charset specified */
		unsigned int clrankset:1;	/* set if clusterrank specified none,local,global */
		unsigned int commset:1;	/* set if comment specified */
		unsigned int compound:1;	/* compound bool */
		unsigned int compset:1;	/* set if compound specified */
		unsigned int concentrate:1;	/* concentrate */
		unsigned int concenset:1;	/* set if concentrate specified */
		unsigned int dpiset:1;	/* set if dpi specified */
		unsigned int fontnameset:1;	/* set if fontname specified */

		unsigned int fontpathset:1;	/* set if fontpath specified */
		unsigned int fontsizeset:1;	/* set if fontsize specified */
		unsigned int idset:1;	/* set if id specified */
		unsigned int labelset:1;	/* set if label specified */
		unsigned int labeljset:1;	/* set if labeljustify specified */
		unsigned int labellset:1;	/* set if labelloc specified */
		unsigned int landscape:1;	/* landscape drawing mode bool */
		unsigned int landscset:1;	/* set if landscape specified */
		unsigned int layersset:1;	/* set if layers specified */
		unsigned int layerlsset:1;	/* set if layerlistsep specified */

		unsigned int layersepset:1;	/* set if layersep specified */
		unsigned int layerselset:1;	/* set if layerselect specified */
	} bitflags0;

	struct {
		unsigned int layoutset:1;	/* set if layout specified */
		unsigned int lhset:1;	/* set if lheight specified */
		unsigned int lwset:1;	/* set if lwidth specified */
		unsigned int lpset:1;	/* set if lp specified */
		unsigned int marginset:1;	/* set if margin specified */
		unsigned int mcset:1;	/* set if mclimit specified */
		unsigned int newrank:1;	/* newrank algo */
		unsigned int nrankset:1;	/* set if newrank specified */
		unsigned int nsepset:1;	/* set if nodesep specified */
		unsigned int nojustify:1;	/* nojustify bool */

		unsigned int nojustset:1;	/* set if nojustify specified */
		unsigned int nsset:1;	/* set if nslimit specified */
		unsigned int ns1set:1;	/* set if nslimit1 specified */
		unsigned int orderset:1;	/* set if ordering specified */
		unsigned int oriset:1;	/* set if orientation specified */
		unsigned int ooset:1;	/* set if outputorder specified */
		unsigned int packset:1;	/* set if pack specified */
		unsigned int packmset:1;	/* set if packmode specified */
		unsigned int padset:1;	/* set if pad specified */
		unsigned int periset:1;	/* set if peripheries specified */

		unsigned int quanset:1;	/* set if quantum specified */
		unsigned int rankset:1;	/* set if rank specified */
		unsigned int rankdset:1;	/* set if rankdir specified */
		unsigned int ranksset:1;	/* set if ranksep specified */
		unsigned int rankseq:1;	/* equally in ranksep value */
		unsigned int ratioset:1;	/* set if ratio specified */
		unsigned int remincross:1;	/* run mincross again 1/0 */
		unsigned int remset:1;	/* set if remincross specified */
		unsigned int rotset:1;	/* set if rotate specified */
		unsigned int ssizeset:1;	/* set if searchsize specified */

		unsigned int sboxesset:1;	/* set if showboxes specified */
		unsigned int sizeset:1;	/* set if size specified */
	} bitflags1;

	struct {
		unsigned int sortvset:1;	/* set if sortv specified */
		unsigned int splinesset:1;	/* set if splines specified */
		unsigned int dashed:1;	/* style */
		unsigned int dashedset:1;	/* style */
		unsigned int dotted:1;	/* style */
		unsigned int dottedset:1;	/* style */
		unsigned int solid:1;	/* style */
		unsigned int solidset:1;	/* style */
		unsigned int bold:1;	/* style */
		unsigned int boldset:1;	/* style */

		unsigned int filled:1;	/* style */
		unsigned int filledset:1;	/* style */
		unsigned int striped:1;	/* style */
		unsigned int stripedset:1;	/* style */
		unsigned int rounded:1;	/* style */
		unsigned int roundedset:1;	/* style */
		unsigned int styleset:1;	/* set if style specified */
		unsigned int vpset:1;	/* viewport */
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
	} bitflags2;

	struct {
		unsigned int bit0:1;
		unsigned int bit1:1;
		unsigned int bit2:1;
		unsigned int bit3:1;
		unsigned int bit4:1;
		unsigned int bit5:1;
		unsigned int bit6:1;
		unsigned int bit7:1;
		unsigned int bit8:1;
		unsigned int bit9:1;

		unsigned int bit10:1;
		unsigned int bit11:1;
		unsigned int bit12:1;
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
	} bitflags3;

};

struct dpnode {
	int nr;			/* uniq node number */
	char *name;		/* uniq node name */
	char *label;		/* label text of node */
	char htmllabel;		/* set if html label */
	struct hlpart *hlinfo;	/* parts of html label */
	struct dppart *labelinfo;	/* parts of record-label */
	int yylineno;		/* line where defined in input */
	struct dpgraph *root;	/* graph where node is defined */
	int csnum;		/* colorscheme number or 0 */
	int color;		/* parsed color, rgb */
	int fcolor;		/* parsed fillcolor, background fill color rgb */
	int fontcolor;		/* parsed fontcolor */
	int shape;		/* node shape number DPSHAPE_ */
	double penwidth;	/* border line thickness */
	double sides;		/* nr. of sides for shape polygon */
	double width;		/* specified node width */
	double height;		/* specified node height */
	char *group;		/* specified group */
	char *comment;		/* device dep. comment */
	double distortion;	/* shape polygon distortion, default 0, min -100 */
	char *fontname;		/* name of font */
	double fontsize;	/* size of font, 14, min 1 */
	char *id;		/* imagemap id */
	char *image;		/* image for node */
	int labelloc;		/* label location */
	char *layer;		/* layer string */
	char *margin;		/* margin string */
	double marginx;		/* margin */
	double marginy;		/* margin */
	double orientation;	/* rotate polygon nodes, 0.0..360.0 */
	double peripheries;	/* int for polygonal shapes */
	char *pos;		/* pos of node %f,%f as string */
	char *rects;		/* rect %f,%f,%f,%f as string */
	double samplepoints;	/* sample points for shape */
	char *shapefile;	/* external node shape */
	double showboxes;	/* postscript showboxes, (int) 0,1,2 */
	double skew;		/* polygon skew factor */
	double sortv;		/* (int) packing */
	char *vertices;		/* coords polygon */
	char *url;		/* url of node */
	int indegree;		/* number of incoming edges */
	int outdegree;		/* number of outgoing edges */

	struct {
		unsigned int defbynode:1;	/* set if defined by node statement */
		unsigned int csnumset:1;	/* set if colorscheme is defined */
		unsigned int fcolorset:1;	/* set if fillcolor specified */
		unsigned int shapeset:1;	/* set if node shape specified */
		unsigned int labelset:1;	/* set if label specified */
		unsigned int radialset:1;	/* set at style=radial */
		unsigned int colorset:1;	/* set if color specified bordercolor */
		unsigned int fontcolorset:1;	/* set if font color set */
		unsigned int penwidthset:1;	/* set if border thickness set with penwidth */
		unsigned int sidesset:1;	/* set if sides specified */

		unsigned int widthset:1;	/* set if width specified */
		unsigned int fixsize:1;	/* set if fixedsize=true */
		unsigned int fixsizeset:1;	/* set if fixedsize is set */
		unsigned int heightset:1;	/* set if height specified */
		unsigned int groupset:1;	/* set if group specified */
		unsigned int comset:1;	/* set if comment is specified */
		unsigned int distortionset:1;	/* set if distortion shape polygon is set */
		unsigned int fontnameset:1;	/* set if font name specified */
		unsigned int fontsizeset:1;	/* set if size of font specified */
		unsigned int idset:1;	/* set if imagemap id set */

		unsigned int imgset:1;	/* set if image specified */
		unsigned int iscale:1;	/* bool imagescale */
		unsigned int iscaleset:1;	/* set if imagescale specified */
		unsigned int labellset:1;	/* set if label loc specified */
		unsigned int layerset:1;	/* set if layer specified */
		unsigned int marginset:1;	/* set if margin specified */
		unsigned int nojust:1;	/* nojustify bool */
		unsigned int nojustset:1;	/* set if nojustify specified */
		unsigned int oriset:1;	/* set if orientation specified */
		unsigned int periset:1;	/* set if peripheries specified */

		unsigned int pin:1;	/* true if fixed node pos */
		unsigned int pinset:1;	/* set if pin specified */
	} bitflags0;

	struct {
		unsigned int posset:1;	/* pos of node %f,%f as string */
		unsigned int rectsset:1;	/* rect %f,%f,%f,%f as string set */
		unsigned int regular:1;	/* regular polygon bool */
		unsigned int reguset:1;	/* set if regular specified */
		unsigned int spset:1;	/* set if samplepoints specified */
		unsigned int shapefset:1;	/* set if shapefile specified */
		unsigned int showbset:1;	/* set if showboxes specified */
		unsigned int skewset:1;	/* set if skew specified */
		unsigned int sortvset:1;	/* set if sortv specified */
		unsigned int vertset:1;	/* set if vertices specified */

		unsigned int urlset:1;	/* set if url specified */
		unsigned int dashed:1;	/* style dashed */
		unsigned int dashedset:1;	/* set if style dashed specified */
		unsigned int dotted:1;	/* style dotted */
		unsigned int dottedset:1;	/* set if style style dotted specified */
		unsigned int solid:1;	/* style solid */
		unsigned int solidset:1;	/* set if style solid specified */
		unsigned int invis:1;	/* style invis */
		unsigned int invisset:1;	/* set if style invis specified */
		unsigned int bold:1;	/* style bold */

		unsigned int boldset:1;	/* set if style bold specified */
		unsigned int filled:1;	/* style filled */
		unsigned int filledset:1;	/* set if style filled specified */
		unsigned int striped:1;	/* style striped */
		unsigned int stripedset:1;	/* set if style striped specified */
		unsigned int wedged:1;	/* style wedged */
		unsigned int wedgedset:1;	/* set if style wedged specified */
		unsigned int dia:1;	/* style diagonals */
		unsigned int diaset:1;	/* set if style diagonals specified */
		unsigned int rounded:1;	/* style rounded */

		unsigned int roundedset:1;	/* set if style rounded specified */
		unsigned int radial:1;	/* style radial */
	} bitflags1;

};

/*edge */
struct dpedge {
	int nr;			/* uniq number */
	struct dpgraph *rootedon;	/* edge is rooted on */
	struct dpnode *fn;	/* from node */
	char *fport;
	char *fcompass;
	struct dpnode *tn;	/* to node */
	char *tport;
	char *tcompass;
	int yylineno;		/* input line nr of edge */
	char *label;		/* optional edge label */
	char style;		/* optional edge style, solid, dotted */
	int ecolor;		/* edge line color */
	double penwidth;	/* edge line thickness */
	int csnum;		/* color scheme number */
	char *url;		/* url */
	char *ahstring;		/* raw arrowhead string */
	char *atstring;		/* raw arrowtail string */
	int ahnum;		/* arrowhead encoding */
	int atnum;		/* arrowtail encoding */
	double asize;		/* arrowsize mult factor, 1.0 */
	char *comment;		/* output data */
	int dir;		/* arrow dir */
	char *etarg;		/* svg only edge target */
	char *ett;		/* tooltip for url */
	int fontcolor;		/* font color edge label */
	char *fontname;		/* font name */
	double fontsize;	/* fontsize is 14, min 1 */
	char *hurl;		/* headurl */
	char *hlp;		/* %f,%f point of head label as string */
	double hlpx;		/* point x for head_lp */
	double hlpy;		/* point y for head_lp */
	int hlpflag;		/* '!' flag for head_lp */
	char *hlabel;		/* head label */
	char *hport;		/* head port compass point as string */
	char *htarg;		/* headtarget, svg map */
	char *htt;		/* headtooltip svg cmap */
	char *id;		/* svg id */
	char *lurl;		/* label url */
	double la;		/* labelangle */
	double ldist;		/* labeldistance */
	int lfontcolor;		/* labelfontcolor */
	char *lfontname;	/* labelfontname */
	double lfontsize;	/* labelfontsize is 14, min 1 */
	char *ltarg;		/* labeltarget */
	char *ltt;		/* labeltooltip svg cmap */
	char *layer;		/* layer control string */
	double len;		/* len neato */
	char *lhead;		/* lhead */
	char *ltail;		/* ltail */
	char *lp;		/* %f,%f point of label as string */
	double lpx;		/* point x for lp */
	double lpy;		/* point y for lp */
	int lpflag;		/* '!' flag for lp */
	double minlen;		/* minlen */
	char *pos;		/* pos string */
	char *sameh;		/* samehead */
	char *samet;		/* sametail */
	char *turl;		/* label url */
	char *tlp;		/* %f,%f point of tail label as string */
	double tlpx;		/* point x for tail_lp */
	double tlpy;		/* point y for tail_lp */
	int tlpflag;		/* '!' flag for tail_lp */
	char *tlabel;		/* tail label */
	char *tlport;		/* tail port */
	char *ttarg;		/* tail target */
	char *ttt;		/* tail tooltip */
	char *target;		/* target */
	char *tt;		/* tooltip */
	double weight;		/* edge weight */
	char *xlabel;		/* x-label */
	char *xlp;		/* %f,%f point of x label as string */
	double xlpx;		/* point x for xlp */
	double xlpy;		/* point y for xlp */
	int xlpflag;		/* '!' flag for xlp */

	struct {
		unsigned int labelset:1;	/* set if label specified */
		unsigned int styleset:1;	/* set if style specified */
		unsigned int ecolorset:1;	/* set if color specified */
		unsigned int penwidthset:1;	/* set if penwidth specified */
		unsigned int csnumset:1;	/* set if colorscheme specified */
		unsigned int urlset:1;	/* set if url specified */
		unsigned int ahset:1;	/* set if arrowhead specified */
		unsigned int asizeset:1;	/* set if arrowsize mult factor set */
		unsigned int atset:1;	/* set if arrowtail specified */
		unsigned int comset:1;	/* set if comment specified */

		unsigned int constraint:1;	/* bool constraint */
		unsigned int constrset:1;	/* set if constraint specified */
		unsigned int decorset:1;	/* set if decorate set */
		unsigned int decorate:1;	/* decorate bool */
		unsigned int dirset:1;	/* set if dir specified */
		unsigned int etargset:1;	/* set if edgetarget specified */
		unsigned int ettset:1;	/* set if edgetooltip specified */
		unsigned int focolorset:1;	/* set if fontcolor specified */
		unsigned int fontnameset:1;	/* set if fontname specified */
		unsigned int fontsizeset:1;	/* set if fontsize specified */

		unsigned int hurlset:1;	/* set if headurl specified */
		unsigned int hlpset:1;	/* set if head_lp specified */
		unsigned int headclip:1;	/* head clip booleam */
		unsigned int hcset:1;	/* set if headclip bool specified */
		unsigned int hlset:1;	/* set if headlabel spacified */
		unsigned int hportset:1;	/* set if headport specified */
		unsigned int htargset:1;	/* set if headtarget specified svg map */
		unsigned int httset:1;	/* set if headtooltip specified svg cmap */
		unsigned int idset:1;	/* set if id specified */
		unsigned int lurlset:1;	/* set if labelurl specified */

		unsigned int laset:1;	/* set if labelangle specified */
		unsigned int ldistset:1;	/* set if labeldistance specified */
	} bitflags0;

	struct {
		unsigned int lfloat:1;	/* labelfloat */
		unsigned int lfloatset:1;	/* set if labelfloat specified */
		unsigned int lfocolorset:1;	/* set if labelfontcolor specified */
		unsigned int lfontnameset:1;	/* set if labelfontname specified */
		unsigned int lfontsizeset:1;	/* set if labelfontsize specified */
		unsigned int ltargset:1;	/* set if labeltarget specified */
		unsigned int lttset:1;	/* set if labeltooltip specified */
		unsigned int layerset:1;	/* set if layer string specified */
		unsigned int lenset:1;	/* set if len specified neato */
		unsigned int lheadset:1;	/* set if lhead specified */

		unsigned int ltailset:1;	/* set if ltail specified */
		unsigned int lpset:1;	/* set if lp specified */
		unsigned int minlenset:1;	/* set if minlen specified */
		unsigned int nojust:1;	/* nojustify bool */
		unsigned int nojustset:1;	/* set if nojustify specified */
		unsigned int posset:1;	/* set if pos specified */
		unsigned int samehset:1;	/* set if samehead specified */
		unsigned int sametset:1;	/* set if sametail specified */
		unsigned int dashed:1;	/* style */
		unsigned int dashedset:1;	/* style */

		unsigned int dotted:1;	/* style */
		unsigned int dottedset:1;	/* style */
		unsigned int solid:1;	/* style */
		unsigned int solidset:1;	/* style */
		unsigned int invis:1;	/* style */
		unsigned int invisset:1;	/* style */
		unsigned int bold:1;	/* style */
		unsigned int boldset:1;	/* style */
		unsigned int tapered:1;	/* style */
		unsigned int taperedset:1;	/* style */

		unsigned int turlset:1;	/* set if tailurl specified */
		unsigned int tlpset:1;	/* set if tail_lp specified */
	} bitflags1;

	struct {
		unsigned int tailc:1;	/* tailclip bool */
		unsigned int tailcset:1;	/* set if tailclip specified */
		unsigned int tlabelset:1;	/* set if taillabel specified */
		unsigned int tportset:1;	/* set if tailport specified */
		unsigned int ttargset:1;	/* set if tailtarget specified */
		unsigned int tttset:1;	/* set if tailtooltip specified */
		unsigned int targetset:1;	/* set if target specified */
		unsigned int ttset:1;	/* set if tooltip specified */
		unsigned int weightset:1;	/* set if weight specified */
		unsigned int xlabelset:1;	/* set if xlabel specified */

		unsigned int xlpset:1;	/* set if xlp specified */
		unsigned int bit11:1;
		unsigned int bit12:1;
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
	} bitflags2;

	struct {
		unsigned int bit0:1;
		unsigned int bit1:1;
		unsigned int bit2:1;
		unsigned int bit3:1;
		unsigned int bit4:1;
		unsigned int bit5:1;
		unsigned int bit6:1;
		unsigned int bit7:1;
		unsigned int bit8:1;
		unsigned int bit9:1;

		unsigned int bit10:1;
		unsigned int bit11:1;
		unsigned int bit12:1;
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
	} bitflags3;

};

/* edge point */
struct dpepoint {
	char *port;		/* port or compass */
	char *compass;
	int type;		/* node or graph */
	struct dpgraph *root;	/* where node is rooted */
	struct dpnode *n;
};

/* node linked list */
struct dpnlink {
	struct dpnode *n;
	struct dpnlink *next;
};

/* edge point list */
struct dpeplink {
	struct dpepoint *ep;
	struct dpeplink *next;
};

/* subgraph list */
struct dpglink {
	struct dpgraph *sg;
	struct dpglink *next;
};

/* tmp edge */
struct dptmpe {
	struct dpnode *fn;
	char *fport;
	char *fcompass;
	struct dpnode *tn;
	char *tport;
	char *tcompass;
};

struct dptelink {
	struct dptmpe *e;
	struct dptelink *next;
};

struct dpelink {
	struct dpedge *e;
	struct dpelink *next;
};

/* part of record label */
struct dppart {
	int dir;		/* direction, 0=hor, 1=vertical */
	int ndpparts;		/* how many subparts */
	struct dppart **parts;	/* sub parts */
	char *id;		/* port id */
	char *lp;		/* label text */
	int hd;			/* has-data */
};

/* parsed number */
struct dpnum {
	double number;
	int pe;			/* set at parse error */
	int es;			/* set at "" string */
};

/* parsed int number */
struct dpinum {
	int number;
	int pe;			/* set at parse error */
	int es;			/* set at "" string */
};

/* parsed boolean */
struct dpbool {
	int number;		/* 0/1 number */
	int pe;			/* set at parse error */
	int es;			/* set at "" string */
};

/* parsed color */
struct dpcolor {
	int color;		/* argb color */
	int pe;			/* set at parse error */
	int es;			/* set at "" string */
	int islist;		/* set if color is a list of colors */
};

/* parsed style */
struct dpstyle {
	int pe;			/* parse error */
	int pe_slw;		/* parse error setlinewidth number */
	int pe_unk;		/* parse error unknown token */
	int pe_exp;		/* parse error expected number at setlinewidth */
	int es;			/* empty string */
	int slwset;		/* set if setlinewidth N */
	double slw;		/* setlinewidth number */
	int dashed;		/* "dashed" parsed N+E */
	int dotted;		/* "dotted" parsed N+E */
	int solid;		/* "solid" parsed N+E */
	int invis;		/* "invis" parsed N+E */
	int bold;		/* "bold" parsed N+E */
	int tapered;		/* "tapered" parsed E */
	int filled;		/* "filled" parsed N+c */
	int striped;		/* "striped" parsed N+c */
	int wedged;		/* "wedged" parsed N */
	int diagonals;		/* "diagonals" parsed N */
	int rounded;		/* "rounded" parsed N+C */
	int radial;		/* "radial" parsed N+C+G */
	char *unknown;		/* unknown token */
};

/* edge arrow */
struct dparrow {
	int pe;
	int es;
	char *name;
	int type;		/* type is basic type or 0 */
};

/* edge dir */
struct dpdir {
	int pe;
	int es;
	int type;
};

/* 1 point with optional '!' flag */
struct dppoint {
	int pe;
	double x;
	double y;
	int flag;
};

/* rect */
struct dprect {
	int pe;
	int es;
	double x0;
	double y0;
	double x1;
	double y1;
};

/* margin */
struct dpmargin {
	int pe;
	int es;
	double x;
	double y;
};

/* output order */
struct dpoo {
	int pe;
	int es;
	int mode;
};

/* rank */
struct dprank {
	int pe;
	int es;
	int mode;
};

/* rankdir */
struct dprankdir {
	int pe;
	int es;
	int mode;
};

/* ranksep */
struct dpranksep {
	int pe;
	int es;
	double number;
	int eq;
};

/* ratio */
struct dpratio {
	int pe;
	int es;
	double number;
	int mode;
};

/* splines args */
struct dpsplines {
	int pe;
	int mode;
};

/* for <table>
 * int      align="center|left|right"
 * int      bgcolor="colorname"
 * int      border="int-value"
 * int      cellborder="int-value"
 * int      cellpadding="int-value"
 * int      cellspacing="int-value"
 * int      color="colorname"
 * (char *) columns="string" only "*" allowed
 * int      fixedsize="true|false"
 * int      gradientangle="int-value"
 * int      height="int-value"
 * (char *) href="string"
 * (char *) id="string"
 * (char *) port="string"
 * (char *) rows="string" only "*" allowed
 * (char *) sides="string"
 * (char *) style="string"
 * (char *) target="string"
 * (char *) title="string"
 * int      valign="middle|bottom|top"
 * int      width="int-value"
 */
struct tabledata {
	struct tlist *tl;	/* list of sub table items */
	struct tlist *tlend;	/* end list of sub table items */
	struct tabledata *table;	/* rooted on this table or 0 */
	struct trlist *tr;	/* tr items */
	struct trlist *trend;	/* end tr items */
	int align;		/* ="center|left|right" */
	int bgcolor;		/* ="colorname" background color */
	int border;		/* ="int-value" */
	int cellborder;		/* ="int-value" */
	int cellpadding;	/* ="int-value" */
	int cellspacing;	/* ="int-value" */
	int color;		/* ="colorname" fontcolor */
	char *columns;		/* ="string" only "*" allowed */
	int fixedsize;		/* ="true|false" */
	int gradientangle;	/* ="int-value" */
	int height;		/* ="int-value" */
	char *href;		/* ="string" */
	char *id;		/* ="string" */
	char *port;		/* ="string" */
	char *rows;		/* ="string" only "*" allowed */
	char *sides;		/* ="string" */
	char *style;		/* ="string" */
	int stylerounded;	/* style options */
	int styleradial;	/* style options */
	int styleinvis;		/* style options */
	int styledotted;	/* style options */
	int styledashed;	/* style options */
	char *target;		/* ="string" */
	char *title;		/* ="string" */
	int valign;		/* ="middle|bottom|top" */
	int width;		/* ="int-value" */
	struct gml_titem *alt;	/* ptr to copy */
};

/* for <td>
 * int      align="center|left|right|text"
 * int      balign="center|left|right"
 * int      bgcolor="colorname"
 * int      border="int-value"
 * int      cellpadding="int-value"
 * int      cellspacing="int-value"
 * int      color="colorname"
 * int      colspan="int-value"
 * int      fixedsize="true|false"
 * int      gradientangle="int-value"
 * int      height="int-value"
 * (char *) href="string"
 * (char *) id="string"
 * (char *) port="string"
 * int      rowspan="int-value"
 * (char *) sides="string"
 * (char *) style="string"
 * (char *) target="string"
 * (char *) title="string"
 * int      valign="middle|bottom|top"
 * int      width="int-value"
 */
struct tddata {
	struct tabledata *table;	/* rooted on this table or 0 */
	struct ilist *il;	/* text items in td or 0 */
	struct ilist *ilend;	/* end text items */
	int align;		/* ="center|left|right|text" */
	int balign;		/* ="center|left|right" */
	int bgcolor;		/* ="colorname" */
	int border;		/* ="int-value" */
	int cellpadding;	/* ="int-value" */
	int cellspacing;	/* ="int-value" */
	int color;		/* ="colorname" */
	int colspan;		/* ="int-value" */
	int fixedsize;		/* ="true|false" */
	int gradientangle;	/* ="int-value" */
	int height;		/* ="int-value" */
	char *href;		/* ="string" */
	char *id;		/* ="string" */
	char *port;		/* ="string" */
	int rowspan;		/* ="int-value" */
	char *sides;		/* ="string" */
	char *style;		/* ="string" */
	int stylerounded;	/* style options */
	int styleradial;	/* style options */
	int styleinvis;		/* style options */
	int styledotted;	/* style options */
	int styledashed;	/* style options */
	char *target;		/* ="string" */
	char *title;		/* ="string" */
	int valign;		/* ="middle|bottom|top" */
	int width;		/* ="int-value" */
	int istab;		/* set if <td> is a <table> */
};

/* for <img>
 * int      scale="false|true|width|height|both"
 * (char *) src="imagename"
 */
struct imgdata {
	int scale;		/* ="false|true|width|height|both" */
	char *src;		/* ="imagename" */
};

/* for <br>
 * int  align="center|left|right"
 */
struct brdata {
	int align;		/* ="center|left|right" */
};

/* for <font>
 * int      color="colorname"
 * (char *) face="fontname"
 * int      point-size="int-number"
 */
struct fontdata {
	int color;		/* ="colorname" */
	char *face;		/* ="fontname" */
	int pointsize;		/* ="int-number" */
};

struct fontldata {
	struct fontdata *fd;
	struct fontldata *next;
};

/* one item of text:
 * bgcolor is default white 0x00ffffff
 * then set by optional node fillcolor
 * then set by optional <table> bgcolor
 * then set by optional <td> bgcolor
 */
struct item {
	char *text;		/* text to display */
	char *atext;		/* modified text to display */
	char *fontname;		/* optional font name */
	int fontsize;		/* optional pointsize */
	int fontcolor;		/* optional color of text */
	int ncolor;		/* optional background color from <td> or <table> */
	struct tabledata *table;	/* optional <table> if <td> is a table */
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
		unsigned int table:1;	/* set if a <table> not a string */
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
};

struct tableldata {
	struct tabledata *tabdata;
	struct tableldata *next;
};

/* <td> */
struct tdldata {
	struct tddata *tdd;
	struct tdldata *next;
};

/* tr data */
struct trdata {
	struct tabledata *table;	/* rooted on this table or 0 */
	struct tdldata *td;	/* td items in tr */
	struct tdldata *tdend;
	int hastab;		/* set if <tr> has <td> elements with a <table> */
	struct trdata *next;
};

/* list with tr items in html string */
struct trlist {
	struct trdata *tritem;
	struct trlist *next;
};

/* list with text items in html string */
struct ilist {
	struct item *items;
	struct ilist *next;
};

/* list with table elements in html string */
struct tlist {
	struct tableldata *titem;
	struct tlist *next;
};

/* html label info is
 * item list with parts of html label
 * or table list with parts of html label
 * but not both at once.
 */
struct hlpart {
	int mode;		/* 0=items, 1=tables */
	struct ilist *il;	/* list of text items */
	struct ilist *ilend;
	struct tlist *tl;	/* list of table items */
	struct tlist *tlend;
};

/* static buffer for parser error messages */
extern char dp_errmsg[256];

/* all nodes */
extern struct dpnlink *dp_anodes;

/* all edges */
extern struct dpelink *dp_aedges;

/* root graphs */
extern struct dpgraph *dp_groot;

/* the current graph */
extern struct dpgraph *dp_curgraph;
extern struct dpnode *dp_curnode;
extern struct dpedge *dp_curedge;

/* data type during parse */
extern int dp_cclass;

/* routines */
extern int dp_chkerr(void);
extern void dp_sg(char *etype, char *gname);
extern void dp_eg(void);
extern char *dp_ccat(char *a, char *b);
extern void dp_atype_graph(void);
extern void dp_atype_sgraph(void);
extern void dp_atype_node(void);
extern void dp_atype_edge(void);
extern void dp_atype_graphdef(void);
extern void dp_atype_nodedef(void);
extern void dp_atype_edgedef(void);
extern void dp_aset(char *l, char *r, int ishtml);
extern void dp_mknode0(char *name);
extern void dp_cke(char *edgedir);
extern struct dpepoint *dp_mknid(char *name, char *port, char *compass);
extern void dp_ende(void);
extern void dp_newe(void);
extern void dp_starte1(struct dpepoint *ep);
extern void dp_starte2(struct dpepoint *ep);
extern void dp_ine(struct dpepoint *ep);
extern void dp_namedsubg(char *sgname, int type);
extern struct dpepoint *dp_endss(void);
extern void dp_clrep(void);
extern void dp_clearall(void);
extern void dp_clrheade(void);
extern void dp_nsubg(struct dpgraph *sg, char *gname, int type);

__END_DECLS
#endif
/* end */
