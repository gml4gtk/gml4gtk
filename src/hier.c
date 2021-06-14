
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
 *
 * SPDX-License-Identifier: GPL-3.0+
 * License-Filename: LICENSE
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "uniqnode.h"
#include "uniqstr.h"
#include "uniqgraph.h"
#include "hier.h"
#include "dot.tab.h"
#include "rhp.h"
#include "sugi.h"
#include "dpmem.h"

/* the graph data root graph */
struct gml_graph *maingraph = NULL;

/* type of graph data 0=gml 1=dot 2=vcg */
int graphtype = 0;

/* if set mirror in y direction */
int option_mirrory = 0;

/* if set do node names instead of node label */
int option_nnames = 0;

/* if set do node label popup */
int option_popup = 0;

/* if 1 allow incremental layout for clusters if any */
int incrlayout = 0;		/* 1 */

/* level placement, 1=dfs, 2=bfs, 3=topological */
int ranktype = 1;

/* type of barycenter, 1 is sugi2, 2 is sugi3, 3 is is rhp */
int barytype = 1;

/* edgelabels on/off */
int option_edgelabels = 1;	/* default show edgelabels (1) */

/* labels on/off */
int option_labels = 1;		/* default show labels (1) */

/* positioning mode of drawing used in pos.c, value 1 or 2 or 3 */
int postype = 2;

/* parser messages */
char parsermessage[256];

/* max x of end drawing */
int maxx = 0;

/* max y of end drawing */
int maxy = 0;

/* initial x,y spacing which can be changed using the gui */
int xspacing = 3;		// 5;
int yspacing = 7;		// 15;

/* background r/g/b of drawing */
int bgcr = 0xff;
int bgcg = 0xff;
int bgcb = 0xff;

/* add node as node with a self-edge */
static void add_selfedgenode(struct gml_graph *g, struct gml_node *node);

/* undo reversed edges and refresh node edgelists */
static void unrev(struct gml_graph *g);

/* */
static int getnodedata_from_rhp_1(int num, int level, int pos, void *data)
{
	struct gml_node *un = NULL;

	un = (struct gml_node *)data;

	if (un == NULL) {
		/* shouldnothappen and set stop signal */
		return (1);
	}

	if (num) {		/* node number */
	}

	if (level != un->rely) {	/* node is at level */
		/* shouldnothappen */
		printf("%s(): node changed level\n", __func__);
	}

	/* this is the new relative x position */
	un->relx = pos;
	return (0);
}

/* run kozo sugiyama barycenter */
void barycenter(struct gml_graph *g, int it1val, int it2val)
{
	int current_crossings = 0;
	int current_icrossings = 0;
	int status = 0;
	struct gml_nlist *lnl = NULL;
	struct gml_elist *enl = NULL;
	int layer = 0;
	/* type of barycenter, 1 is sugi2.c, 2 is sugi3, else is rhp.c */
	if (barytype == 1) {
		reduce_crossings2(g, it1val, it2val);
	} else if (barytype == 2) {
		reduce_crossings3(g, it1val, it2val);
	} else if (barytype == 3) {
		reduce_crossings4(g, it1val, it2val);
	} else if (barytype == 4) {
		reduce_crossings5(g, it1val, it2val);
	} else {
		/* using rhp.c */
		/* number of crossing edges at level */
		if (g->numce == NULL) {
			g->numce = (int *)dp_calloc(1, (g->maxlevel + 1) * sizeof(int));
		}

		if (g->maxlevel == 0) {
			/* if graph has only 1 or more nodes */
			return;
		}

		/* with too complex graph data at least this message is on console before cpu get roasted. */
		printf("%s(): starting rhp barycenter algorithm for graph with %d nodes, %d edges in %d levels ... wait\n",
		       __func__, g->nnodes, g->nedges, g->maxlevel);
		fflush(stdout);

		if (g->nnodes < 2) {
			/* not much todo if only 0 or 1 nodes */
			return;
		}

		if (g->nedges < 2) {
			/* not much todo if only 1 edge */
			return;
		}

		/* set this to 1 to get image when no barycenter is done */
		if (0) {
			return;
		}

		/* init, no log file */
		rhp_init((char *)0, 0);

		/* copy data */
		lnl = g->nodelist;
		while (lnl) {
			/* add node with uniq number at given level */
			status = rhp_addnode((int)lnl->node->nr, (int)lnl->node->rely, (void *)lnl->node);
			if (status) {
				/* shouldnothappen */
				printf("%s(): rhp_addnode(2) failed\n", __func__);
				break;
			}
			lnl = lnl->next;
		}

		/* copy data */
		enl = g->edgelist;
		while (enl) {
			/* add edge with uniq number, between two nodes, skip hor. edges */
			if (enl->edge->hedge == 0) {
				status =
				    rhp_addedge((int)enl->edge->nr, (int)enl->edge->from_node->nr, (int)enl->edge->to_node->nr,
						(void *)enl->edge);
				if (status) {
					/* shouldnothappen */
					printf("%s(): rhp_addedge() failed\n", __func__);
					break;
				}
			}
			enl = enl->next;
		}

		current_icrossings = (int)rhp_initial_crossings();

		/* run layouter */
		rhp_layout( /* options */ 0, /* 0 left node weight adjust or 1 avg. adjust */ 0);

		/* */
		current_crossings = rhp_current_crossings();
		printf("%s(): %d crossings in rhp graph after layout, initial %d\n", __func__, current_crossings,
		       current_icrossings);

		maingraph->sugi_fcrossings = (int)current_crossings;

		/* get how many crossings at given level */
		for (layer = 1; layer < g->maxlevel; layer++) {
			g->numce[layer] = (int)rhp_current_crossings_at_level(layer);
			/* check extra and correct if needed */
			if (g->numce[layer] < 0) {
				printf("%s(): value %d from rhp_current_crossings_at_level()\n", __func__, g->numce[layer]);
				g->numce[layer] = 0;
			}
		}

		status = rhp_node_foreach(getnodedata_from_rhp_1);

		if (status) {
			/* shouldnothappen */
			printf("%s(): error status %d from rhp\n", __func__, status);
		}

		/* free all memory when ready with rhp.c */
		rhp_deinit();
	}

	return;
}

/* prepare for all-at-once graph layout */
void prep(struct gml_graph *g)
{
	struct gml_graph *ga = NULL;
	struct gml_nlist *lnl = NULL;
	struct gml_nlist *lnl2 = NULL;
	struct gml_node *node2 = NULL;
	struct gml_node *node = NULL;
	struct gml_elist *enl = NULL;
	struct gml_elist *enl2 = NULL;
	struct gml_edge *edge2 = NULL;
	struct gml_edge *edge = NULL;

	if (g == NULL) {
		return;
	}

	ga = maingraph;
	ga->nnodes = 0;
	ga->nedges = 0;
	ga->nedgelabels = 0;
	ga->nodenum = 0;
	ga->tnedgelabels = 0;

	/* */
	lnl = maingraph->rawnodelist;
	while (lnl) {
		node = lnl->node;

		node2 = dp_calloc(1, sizeof(struct gml_node));

		node2->rootedon = node->rootedon;
		node2->rlabel = node->rlabel;	/* record label */
		node2->hlabel = node->hlabel;	/* html label */
		node2->id = node->id;
		node2->ncolor = node->ncolor;	/* fill color r/g/b */
		node2->nbcolor = node->nbcolor;	/* border color r/g/b */
		node2->fontcolor = node->fontcolor;
		node2->secolor = node->secolor;	/* self edge color */
		node2->nlabel = node->nlabel;
		node2->name = node->name;
		node2->nselfedges = node->nselfedges;
		/* uniq node numbers start at 1 */
		node2->nr = node->nr;
		/* update the node number */
		if (node2->nr > ga->nodenum) {
			ga->nodenum = node2->nr;
		}
		node2->ishtml = node->ishtml;
		/* option to use node names instead of node labels in gui */
		/* update now done differently */
		if (0) {
			if (option_nnames) {
				node2->nlabel = node2->name;
				/* turn off r/h labels */
				node2->rlabel = NULL;
				node2->hlabel = NULL;
				node2->ishtml = 0;
			} else {
				/* keep the configuration with using r/h node labels */
			}
		}

		/* add node in work list */
		lnl2 = dp_calloc(1, sizeof(struct gml_nlist));

		lnl2->node = node2;

		if (ga->nodelist == NULL) {
			ga->nodelist = lnl2;
			ga->nodelisttail = lnl2;
		} else {
			ga->nodelisttail->next = lnl2;
			ga->nodelisttail = lnl2;
		}

		if (yydebug || 0) {
			printf("%s(): adding node \"%s\"\n", __func__, node2->name);
		}

		uniqnode_add2(g, node2);
		ga->nnodes++;
		lnl = lnl->next;
	}

	/* create copy of rawedgelist in edge list */
	enl = maingraph->rawedgelist;
	while (enl) {
		edge = enl->edge;

		edge2 = dp_calloc(1, sizeof(struct gml_edge));

		edge2->nr = edge->nr;
		if (edge->nr > g->edgenum) {
			g->edgenum = edge->nr;
		}

		edge2->rootedon = edge->rootedon;
		edge2->from_node = uniqnode2(g, edge->from_node->nr);
		if (edge2->from_node == NULL) {
			printf("%s(): nil from\n", __func__);
		}

		edge2->to_node = uniqnode2(g, edge->to_node->nr);
		if (edge2->to_node == NULL) {
			printf("%s(): nil to\n", __func__);
		}

		if (edge2->from_node == edge2->to_node) {
			/* shouldnothappen */
			printf("%s(): selfedge huh?\n", __func__);
		}

		/* edge label or NULL for no edgelabel.
		 * with gui checkbox the edgelabels can be turned on/off
		 */
		if (edge->elabel) {
			ga->tnedgelabels++;
		}

		/* set to zero if no edgelabels wanted */
		if (option_edgelabels == 0) {
			edge2->elabel = NULL;
			ga->nedgelabels = 0;
		} else {
			/* add edgelabels in the graph layout */
			edge2->elabel = edge->elabel;
			if (edge2->elabel) {
				ga->nedgelabels++;
			}
		}

		/* edge color */
		edge2->ecolor = edge->ecolor;
		edge2->style = edge->style;
		/* from/to compass point in gcc data */
		edge2->fcompass = edge->fcompass;
		edge2->tcompass = edge->tcompass;
		/* dot constraint flag */
		edge2->constraint = edge->constraint;
		/* check if nodes are in same subgraph, and in a cluster */
		if (edge2->from_node && edge2->to_node) {
			if (edge2->from_node->rootedon == edge2->to_node->rootedon) {
				if (edge2->from_node->rootedon->type == SG_CLUSTER) {
					if (yydebug || 0) {
						printf("%s(): edge %d is inside cluster\n", __func__, edge2->nr);
					}
					edge2->incluster = 1;
				}
			}

			/* update in/out degree of nodes for reorg() */
			edge2->from_node->outdegree++;
			edge2->to_node->indegree++;
		}

		enl2 = dp_calloc(1, sizeof(struct gml_elist));

		enl2->edge = edge2;

		/* link in */
		if (ga->edgelist == NULL) {
			ga->edgelist = enl2;
			ga->edgelisttail = enl2;
		} else {
			ga->edgelisttail->next = enl2;
			ga->edgelisttail = enl2;
		}

		ga->nedges++;
		enl = enl->next;
	}

	/* update the nodes in self-edges */
	lnl = maingraph->nodelist;
	while (lnl) {
		if (lnl->node->nselfedges) {
			/* add node in list with self-edge nodes */
			add_selfedgenode(maingraph, lnl->node);
		}
		lnl = lnl->next;
	}

	return;
}

/* add node to cluster, only if there is edge connected inside cluster
 * there can also be single nodes in a cluster or nodes connecting
 * to other clusters and those are not in the nodelist here
 */
static void prepincr_addnode(struct gml_graph *g, struct gml_node *node)
{
	struct gml_nlist *lnl2 = NULL;
	struct gml_node *node2 = NULL;
	struct gml_graph *ga = NULL;
	struct gml_nlist *lnl = NULL;
	int found = 0;
	if (g) {
	}

	ga = node->rootedon;
	found = 0;
	lnl = ga->nodelist;
	while (lnl) {
		if (lnl->node->nr == node->nr) {
			found = 1;
			break;
		}
		lnl = lnl->next;
	}

	if (found) {
		/* node is already in nodelist */
		node->incluster = 1;	/* node is part of cluster layout */
		return;
	}

	/* add node to nodelist of cluster graph */
	node2 = dp_calloc(1, sizeof(struct gml_node));

	node2->rootedon = node->rootedon;
	node2->rlabel = node->rlabel;	/* record label */
	node2->id = node->id;
	node2->ncolor = node->ncolor;	/* fill color r/g/b */
	node2->nbcolor = node->nbcolor;	/* border color r/g/b */
	node2->fontcolor = node->fontcolor;
	node2->secolor = node->secolor;	/* self-edge color */
	node2->nlabel = node->nlabel;
	node2->name = node->name;
	node2->nselfedges = node->nselfedges;
	node2->incluster = 1;	/* node is part of cluster layout */

	/* uniq node numbers start at 1 */
	node2->nr = node->nr;

	lnl2 = dp_calloc(1, sizeof(struct gml_nlist));

	lnl2->node = node2;
	if (ga->nodelist == NULL) {
		ga->nodelist = lnl2;
		ga->nodelisttail = lnl2;
	} else {
		ga->nodelisttail->next = lnl2;
		ga->nodelisttail = lnl2;
	}

	return;
}

/* prepare for incremental layout */
void prepincr(struct gml_graph *g)
{
	struct gml_graph *ga = NULL;
	struct gml_elist *enl = NULL;
	struct gml_elist *enl2 = NULL;
	struct gml_edge *edge2 = NULL;
	struct gml_edge *edge = NULL;

	if (g == NULL) {
		return;
	}

	if (0) {
		prep(g);
		return;
	}

	/* create copy of rawedgelist in edge list */
	enl = maingraph->rawedgelist;
	while (enl) {
		edge = enl->edge;
		/* check if nodes are in same subgraph, and in a cluster */
		if (edge->rootedon->type == SG_CLUSTER) {

			/* XXX fixme todo reloc of nodes
			   when edge is in cluster both nodes must be in that cluster
			   but when nodes are in other cluster then not
			   if(edge->from_node->rootedon->type!=SG_CLUSTER)
			   {
			   edge->from_node->rootedon = edge->rootedon;
			   }

			   if(edge->to_node->rootedon->type!=SG_CLUSTER)
			   {
			   edge->to_node->rootedon = edge->rootedon;
			   }

			   also:
			   it may happen root of edge is changed if both
			   nodes now are in other cluster
			 */

			/* add these nodes in nodelist */
			prepincr_addnode(g, edge->from_node);
			prepincr_addnode(g, edge->to_node);
			/* create copy of the edge */
			edge2 = dp_calloc(1, sizeof(struct gml_edge));
			if (edge2 == NULL) {
				return;
			}

			edge2->nr = edge->nr;
			if (edge->nr > g->edgenum) {
				g->edgenum = edge->nr;
			}

			edge2->rootedon = edge->rootedon;
			edge2->from_node = uniqnode2(g, edge->from_node->nr);
			edge2->to_node = uniqnode2(g, edge->to_node->nr);
			if (edge2->from_node == edge2->to_node) {
				/* shouldnothappen */
				printf("%s(): selfedge huh?\n", __func__);
			}

			edge2->elabel = edge->elabel;
			edge2->ecolor = edge->ecolor;
			edge2->style = edge->style;
			edge2->fcompass = edge->fcompass;
			edge2->tcompass = edge->tcompass;
			edge2->constraint = edge->constraint;
			if (yydebug || 0) {
				printf("%s(): edge %d is inside cluster\n", __func__, edge2->nr);
			}

			edge2->incluster = 1;

			/* update in/out degree of nodes */
			edge2->from_node->outdegree++;
			edge2->to_node->indegree++;

			enl2 = dp_calloc(1, sizeof(struct gml_elist));
			if (enl2 == NULL) {
				dp_free(edge2);
				return;
			}

			enl2->edge = edge2;
			/* add to edgelist in this cluster subgraph */
			/*         ga = edge2->from_node->rootedon; */
			ga = edge->rootedon;
			/* XXX fixme, maybe other rootedon is needed */
			if (ga->edgelist == NULL) {
				ga->edgelist = enl2;
				ga->edgelisttail = enl2;
			} else {
				ga->edgelisttail->next = enl2;
				ga->edgelisttail = enl2;
			}

		}

		enl = enl->next;
	}

	/* XXX todo update the nodes in self-edges list, see prep() */

	/*
	   XXX todo fixme the single nodes in a cluster to add
	 */

	return;
}

/* create root graph */
void create_maingraph(void)
{
	if (maingraph) {
		/* shouldnothappen */
		printf("%s(): maingraph is %p shouldnothappen\n", __func__, (void *)maingraph);
	}
	maingraph = dp_calloc(1, sizeof(struct gml_graph));
	if (maingraph == NULL) {
		return;
	}
	/* set root graph as graph with number 0 in db */
	uniqgraph_add(maingraph, 0);
	maingraph->graphname = uniqstr("rootgraph");
	maingraph->label = uniqstr("rootgraph");
	return;
}

/* create subgraphs and add summarynode for cluster subgraphs
 * types of subgraphs in type are:
 * #define SG_ROOT 0		root
 * #define SG_COMPOUND 1	compound {}
 * #define SG_SUBG 2		subgraph wito or without name {}
 * #define SG_CLUSTER 3		subgraph cluster {}
 */
void create_sg(int nr, char *name, char *label, int type)
{
	struct gml_graph *gr = NULL;
	gr = dp_calloc(1, sizeof(struct gml_graph));
	if (gr == NULL) {
		return;
	}
	gr->id = nr;
	/* name can be NULL or start with "cluster" */
	gr->graphname = name;
	gr->label = label;
	/* type is one of above */
	gr->type = type;
	/* update total number of clusters in the whole graph */
	if (gr->type == SG_CLUSTER) {
		maingraph->tnclusters++;
		/* add summary node to the subgraph */
	}
	uniqgraph_add(gr, nr);
	return;
}

/*
 * There are 5 pre-defined entity references in XML:
 * &lt; 	< 	less than
 * &gt; 	> 	greater than
 * &amp; 	& 	ampersand 
 * &apos; 	' 	apostrophe
 * &quot; 	" 	quotation mark
 * This is what dia uses for <>"'&#
 * <dia:string>#&lt;&gt;"'&amp;##</dia:string>
 */
static void dia_string(FILE * f, char *string)
{
	char *p = NULL;
	if (string == NULL) {
		return;
	}

	p = string;
	while (*p) {
		if (*p == '#') {
			/* dia uses # for # */
			fputc('#', f);
		} else if (*p == '\'') {
			/* dia uses ' for ' */
			fputc('\'', f);
		} else if (*p == '"') {
			/* dia uses " for " */
			fputc('"', f);
		} else if (*p == '<') {
			/* dia uses xml < for < */
			fputs("&lt;", f);
		} else if (*p == '>') {
			/* dia uses xml > for > */
			fputs("&gt;", f);
		} else if (*p == '&') {
			/* dia uses xml & for & */
			fputs("amp;", f);
		} else {
			fputc(*p, f);
		}
		p++;
	}

	return;
}

static void dialine(FILE * f, int objectcount, double fx, double fy, double tx, double ty, int color)
{
	int red;
	int green;
	int blue;
	/* cairo_line_to (crp, tnx1, tny0); cairo_line_to (crp, tnx1, tny1); */
	fprintf(f, "<dia:object type=\"Standard - Line\" version=\"0\" id=\"O%d\">\n", objectcount);
	fprintf(f, "<dia:attribute name=\"obj_pos\">\n");
	/* start */
	fprintf(f, "<dia:point val=\"%f,%f\"/>\n", fx, fy);
	fprintf(f, "</dia:attribute>\n");
	fprintf(f, "<dia:attribute name=\"obj_bb\">\n");
	/* start end */
	fprintf(f, "<dia:rectangle val=\"%f,%f;%f,%f\"/>\n", fx, fy, fx, ty);
	fprintf(f, "</dia:attribute>\n");
	fprintf(f, "<dia:attribute name=\"conn_endpoints\">\n");
	/* start */
	fprintf(f, "<dia:point val=\"%f,%f\"/>\n", fx, fy);
	/* end */
	fprintf(f, "<dia:point val=\"%f,%f\"/>\n", tx, ty);
	fprintf(f, "</dia:attribute>\n");
	fprintf(f, "<dia:attribute name=\"numcp\">\n");
	fprintf(f, "<dia:int val=\"1\"/>\n");
	fprintf(f, "</dia:attribute>\n");
	if (color != 0) {
		red = (color & 0x00ff0000) >> 16;
		green = (color & 0x0000ff00) >> 8;
		blue = (color & 0x000000ff);
		fprintf(f, "<dia:attribute name=\"line_color\">\n");
		fprintf(f, "<dia:color val=\"#%02x%02x%02x\"/>\n", red, green, blue);
		fprintf(f, "</dia:attribute>\n");
	}

	fprintf(f, "</dia:object>\n");
	return;
}

/* save as dia software xml format.
 * there is no documentation on this xml format.
 * read dia source, guess and look at xml data.
 * java api for dia xml https://v2.pikacode.com/tachikoma/diaxml_api
 */
/* write graph data as dia diagram */
void graph2dia(struct gml_graph *g, FILE * f)
{
	struct gml_elist *el = NULL;
	struct gml_nlist *lnl = NULL;
	struct gml_node *un = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	double diafactor = 10.0;
	int objectcount = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	double fnx1 = 0;
	double fny1 = 0;
	double dx15 = 0;
	double tnx1 = 0;
	/* scaling factor */
	diafactor = 10.0;
	/* uniq object counter */
	objectcount = 0;
	/* head */
	fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(f, "<dia:diagram xmlns:dia=\"http://www.lysator.liu.se/~alla/dia/\">\n");
	fprintf(f, "<dia:layer name=\"Background\" visible=\"true\" active=\"true\">\n");
	fprintf(f, "<!-- generated by %s %s -->\n", PACKAGE_STRING, PACKAGE_URL);
	/* print the node list with real nodes */
	lnl = g->nodelist;
	while (lnl) {
		un = lnl->node;
		/* only real node or edge label, skip dummy nodes */
		if (lnl->node->dummy == 0) {
			/* regular node or edge label */
			fprintf(f,
				"<!-- node %d in drawing at (%d,%d) size (%d,%d) relative level=%d -->\n",
				un->id, un->finx, un->finy, un->bbx, un->bby, un->rely);
			fprintf(f, "<dia:object type=\"Standard - Box\" version=\"0\" id=\"O%d\">\n", objectcount);
			/* dia object number to reference in edge */
			un->objectnr = objectcount;
			objectcount = objectcount + 1;
			fprintf(f, "<dia:attribute name=\"obj_pos\">\n");
			fprintf(f, "<dia:point val=\"%f,%f\"/>\n", un->finx / diafactor, un->finy / diafactor);
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name=\"obj_bb\">\n");
			fprintf(f, "<dia:rectangle val=\"%f,%f;%f,%f\"/>\n",
				un->finx / diafactor, un->finy / diafactor,
				(un->finx + un->bbx) / diafactor, (un->finy + un->bby) / diafactor);
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name=\"elem_corner\">\n");
			fprintf(f, "<dia:point val=\"%f,%f\"/>\n", un->finx / diafactor, un->finy / diafactor);
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name=\"elem_width\">\n");
			fprintf(f, "<dia:real val=\"%f\"/>\n", un->bbx / diafactor);
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name =\"elem_height\">\n");
			fprintf(f, "<dia:real val=\"%f\"/>\n", un->bby / diafactor);
			fprintf(f, "</dia:attribute>\n");
			red = (un->ncolor & 0x00ff0000) >> 16;
			green = (un->ncolor & 0x0000ff00) >> 8;
			blue = (un->ncolor & 0x000000ff);
			fprintf(f, "<dia:attribute name=\"inner_color\">\n");
			fprintf(f, "<dia:color val=\"#%02x%02x%02x\"/>\n", red, green, blue);
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name=\"show_background\">\n");
			fprintf(f, "<dia:boolean val=\"true\"/>\n");
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "</dia:object>\n");
			fprintf(f, "<dia:object type=\"Standard - Text\" version=\"1\" id=\"O%d\">\n", objectcount);
			objectcount = objectcount + 1;
			fprintf(f, "<dia:attribute name=\"obj_pos\">\n");
			fprintf(f, "<dia:point val=\"%f,%f\"/>\n", un->finx / diafactor, un->finy / diafactor);
			fprintf(f, "</dia:attribute>\n");
			/*
			 * fprintf (f, "<dia:attribute name=\"obj_bb\">\n");
			 * fprintf (f,"<dia:rectangle val=\"13.7,0.186375;14.5336,0.98725\"/>\n");
			 * fprintf (f, "</dia:attribute>\n");
			 */
			fprintf(f, "<dia:attribute name=\"text\">\n");
			fprintf(f, "<dia:composite type=\"text\">\n");
			fprintf(f, "<dia:attribute name=\"string\">\n");
			fprintf(f, "<dia:string>#");

			/* not supported dot record/html label */
			if (un->rlabel || un->hlabel) {
				dia_string(f, un->name);
			} else {
				dia_string(f, un->nlabel);
			}

			fprintf(f, "#</dia:string>\n");
			fprintf(f, "</dia:attribute>\n");
			fprintf(f, "<dia:attribute name=\"font\">\n");
			fprintf(f, "   <dia:font family=\"sans\" style=\"0\" name=\"Helvetica\"/>\n");
			fprintf(f, "</dia:attribute>\n");
			/* font size */
			fprintf(f, "<dia:attribute name=\"height\">\n");
			fprintf(f, "  <dia:real val=\"1.7\"/>\n");
			fprintf(f, "</dia:attribute>\n");
			/* <dia:attribute name="pos"> */
			/* <dia:point val="13.7,0.8"/> */
			/* </dia:attribute> */
			/* <dia:attribute name="color"> */
			/* <dia:color val="#000000"/> */
			/* </dia:attribute> */
			/* <dia:attribute name="alignment"> */
			/* <dia:enum val="0"/> */
			/* </dia:attribute> */
			fprintf(f, "</dia:composite>\n");
			fprintf(f, "</dia:attribute>\n");
			/* <dia:attribute name="valign"> */
			/* <dia:enum val="3"/> */
			/* </dia:attribute> */
			/*
			 * fprintf (f, "<dia:connections>\n");
			 * fprintf (f, "<dia:connection handle=\"0\" to=\"O%d\" connection=\"8\"/>\n", objectcount - 1);
			 * fprintf (f, "</dia:connections>\n");
			 */
			fprintf(f, "</dia:object>\n");
		}

		/* next node */
		lnl = lnl->next;
	}

	/* print the edges */
	el = g->edgelist;
	while (el) {
		/* from/to node */
		sn = el->edge->from_node;
		tn = el->edge->to_node;
		/* special drawing for hor. edge */
		if (el->edge->hedge) {
			fprintf(f, "<!-- horizontal edge from (real) node %d to (real) node %d -->\n", sn->id, tn->id);
			/* horizontal edge has original endpoints */
			/* center of from/to nodes */
			fnx1 = (sn->finx + sn->bbx / 2);
			tnx1 = (tn->finx + tn->bbx / 2);
			if (tnx1 > fnx1) {
				/* edge from left to right */

				/* distance length of hor. line / 5 */
				dx15 = (tnx1 - fnx1) / 5;
				/* start line at center */
				fnx1 = (sn->finx + sn->bbx / 2);
				fny1 = (sn->finy + sn->bby);
				if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
					/* from node y is lower then target, put hor. line 10px lower */
					dialine(f, objectcount, fnx1 / diafactor, fny1 / diafactor,
						(fnx1 + dx15) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount, (fnx1 + dx15) / diafactor,
						(sn->finy + (sn->bby / 2) + 10) / diafactor,
						((fnx1 + dx15) + (3 * dx15)) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount,
						((fnx1 + dx15) + (3 * dx15)) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor,
						(tn->finx + tn->bbx / 2) / diafactor,
						(tn->finy + tn->bby) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
				} else {
					/* from-node y is higher */

					dialine(f, objectcount, fnx1 / diafactor, fny1 / diafactor,
						(fnx1 + dx15) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount, (fnx1 + dx15) / diafactor,
						(sn->finy + (sn->bby / 2) + 10) / diafactor,
						((fnx1 + dx15) + (3 * dx15)) / diafactor,
						((tn->finy + tn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount,
						((fnx1 + dx15) + (3 * dx15)) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor,
						(tn->finx + (tn->bbx / 2)) / diafactor,
						(tn->finy + tn->bby) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
				}

			} else {
				/* edge from right to left fnx1>tnx1 */

				/* distance length of hor. line / 5 */
				dx15 = (fnx1 - tnx1) / 5;
				/* start line at center */
				fnx1 = (sn->finx + sn->bbx / 2);
				fny1 = (sn->finy + sn->bby);
				if ((sn->finy + sn->bby) >= (tn->finy + tn->bby)) {
					/* from node y is lower then target, put hor. line 10px lower */

					dialine(f, objectcount, fnx1 / diafactor, fny1 / diafactor,
						(fnx1 - dx15) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount, (fnx1 - dx15) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor,
						((fnx1 - dx15) - (3 * dx15)) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount,
						((fnx1 - dx15) - (3 * dx15)) / diafactor,
						((sn->finy + sn->bby) + 10) / diafactor,
						(tn->finx + (tn->bbx / 2)) / diafactor,
						(tn->finy + tn->bby) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
				} else {
					/* from-node y is higher */

					dialine(f, objectcount, fnx1 / diafactor, fny1 / diafactor,
						(fnx1 - dx15) / diafactor,
						((tn->finy + tn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount, (fnx1 - dx15) / diafactor,
						((tn->finy + tn->bby) + 10) / diafactor,
						((fnx1 - dx15) - (3 * dx15)) / diafactor,
						((tn->finy + tn->bby) + 10) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
					dialine(f, objectcount,
						((fnx1 - dx15) - (3 * dx15)) / diafactor,
						((tn->finy + tn->bby) + 10) / diafactor,
						(tn->finx + (tn->bbx / 2)) / diafactor,
						(tn->finy + tn->bby) / diafactor, el->edge->ecolor);
					objectcount = objectcount + 1;
				}

			}

		} else {

			/*
			 * here regular edge from level, to level+1, 4 types.
			 */
			if (sn->dummy == 0 && tn->dummy == 0) {
				/* from real node to real node.
				 * real nodes are interleaved with dummy nodes.
				 * but real nodes to edgelabels are also here.
				 */
				fprintf(f, "<!-- edge from real node %d to real node %d -->\n", sn->id, tn->id);
				dialine(f, objectcount, (sn->finx + (sn->bbx / 2)) / diafactor,
					(sn->finy + sn->bby) / diafactor,
					(tn->finx + (tn->bbx / 2)) / diafactor, tn->finy / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
			} else if (sn->dummy == 1 && tn->dummy == 0) {
				/* from dummy node to real node */

				dialine(f, objectcount, sn->finx / diafactor,
					sn->finy / diafactor, sn->finx / diafactor,
					(sn->finy + (sn->bby / 2)) / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
				dialine(f, objectcount, sn->finx / diafactor,
					(sn->finy + (sn->bby / 2)) / diafactor,
					(tn->finx + (tn->bbx / 2)) / diafactor, tn->finy / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
			} else if (sn->dummy == 0 && tn->dummy == 1) {
				/* from real node to dummy node */

				fprintf(f, "<!-- edge from real node %d to dummy node nr=%d -->\n", sn->id, tn->nr);
				dialine(f, objectcount, (sn->finx + (sn->bbx / 2)) / diafactor,
					(sn->finy + sn->bby) / diafactor, tn->finx / diafactor,
					(tn->finy - (tn->bby / 2)) / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
				dialine(f, objectcount, tn->finx / diafactor,
					(tn->finy - (tn->bby / 2)) / diafactor,
					tn->finx / diafactor, tn->finy / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
			} else {
				/* from dummy node to dummy node */

				fprintf(f, "<!-- edge from dummy node nr=%d to dummy node nr=%d -->\n", sn->nr, tn->nr);
				dialine(f, objectcount, sn->finx / diafactor,
					sn->finy / diafactor, sn->finx / diafactor,
					(sn->finy + (sn->bby / 2)) / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
				dialine(f, objectcount, sn->finx / diafactor,
					(sn->finy + (sn->bby / 2)) / diafactor,
					tn->finx / diafactor, (tn->finy - (tn->bby / 2)) / diafactor, el->edge->ecolor);
				objectcount = objectcount + 1;
				dialine(f, objectcount, tn->finx / diafactor,
					(tn->finy - (tn->bby / 2)) / diafactor, tn->finx / diafactor, tn->finy / diafactor,
					el->edge->ecolor);
				/* no arrow draw because there are no real nodes */
			}

		}

		el = el->next;
	}

	/* tail */
	fprintf(f, "</dia:layer>\n");
	fprintf(f, "</dia:diagram>\n");
	return;
}

/* write graph data as jgf json

This is a minimal graph with no data:

{
    "graph": {
        "id": "",
        "type": "schema test",
        "label": "empty test",
        "nodes": {},
        "edges": [],
        "metadata": {}
    }
}

this is a small example single graph:
 "graph": {
            "id": "car-manufacturer-countries",
            "type": "car",
            "label": "Car Manufacturer Countries",
            "nodes": {
                "japan": {
                    "label": "Japan"
                },
                "nissan": {
                    "label": "Nissan"
                },
                "toyota": {
                    "label": "Toyota"
                }
            },
            "edges": [
                {
                    "source": "nissan",
                    "target": "japan",
                    "relation": "country_of_origin"
                },
                {
                    "source": "nissan",
                    "target": "japan",
                    "relation": "country_of_origin"
                }
            ]
        }
- dot html or record labels are set as node name
- edge label "" is set as no label
- node label "" is set as "" label
- in the metadata can put more
- see also the dot xdot json format
*/
/* save as jgf json diagram json jgf version 2.1
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "$id": "http://jsongraphformat.info/v2.1/json-graph-schema.json",
  "title": "JSON Graph Schema",
  "oneOf": [
    {
      "type": "object",
      "properties": {
        "graph": { "$ref": "#/definitions/graph" }
      },
      "additionalProperties": false,
      "required": [
        "graph"
      ]
    },
    {
      "type": "object",
      "properties": {
        "graphs": {
          "type": "array",
          "items": { "$ref": "#/definitions/graph" }
        }
      },
      "additionalProperties": false
    }
  ],
  "definitions": {
    "graph": {
      "oneOf": [
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "default": true },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "edges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/edge" }
            }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "default": true },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "hyperedges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/directedhyperedge" }
            }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "properties": {
            "id": { "type": "string" },
            "label": { "type": "string" },
            "directed": { "type": [ "boolean" ], "enum": [false] },
            "type": { "type": "string" },
            "metadata": { "type": [ "object" ] },
            "nodes": {
              "type": "object",
              "additionalProperties": { "$ref": "#/definitions/node" }
            },
            "hyperedges": {
              "type": [ "array" ],
              "items": { "$ref": "#/definitions/undirectedhyperedge" }
            }
          },
          "required": [ "directed" ]
        }
      ]
    },
    "node": {
      "type": "object",
      "properties": {
        "label": { "type": "string" },
        "metadata": { "type": "object" },
        "additionalProperties": false
      }
    },
    "edge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "source": { "type": "string" },
        "target": { "type": "string" },
        "relation": { "type": "string" },
        "directed": { "type": [ "boolean" ], "default": true },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "source", "target" ]
    },
    "directedhyperedge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "source": { "type": "array", "items": { "type": "string" } },
        "target": { "type": "array", "items": { "type": "string" } },
        "relation": { "type": "string" },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "source", "target" ]
    },
    "undirectedhyperedge": {
      "type": "object",
      "additionalProperties": false,
      "properties": {
        "id": { "type": "string" },
        "nodes": { "type": "array", "items": { "type": "string" } },
        "relation": { "type": "string" },
        "label": { "type": "string" },
        "metadata": { "type": [ "object" ] }
      },
      "required": [ "nodes" ]
    }
  }
}
*/

static void graph2jgflabel(char *text, FILE * f)
{
	char *ptr = NULL;
	if (text == NULL) {
		return;
	}
	if (strlen(text) == 0) {
		return;
	}
	ptr = text;
	while (*ptr) {
		/* bnfrt\ and \u[a-fA-f] todo */
		if ((*ptr) == '\n') {
			fputs("\\n", f);
		} else if ((*ptr) == '"') {
			/* this is '\"' in a "..." string */
			fputs("\\\"", f);
		} else if ((*ptr) == '\\') {
			/* this becomes \\ */
			fputs("\\\\", f);
		} else if ((*ptr) == '\t') {
			fputs("    ", f);
		} else if ((*ptr) == '\b') {
			/* parsed by json, but generates error in dagre.js, so skip \b */
			if (0) {
				fputs("\\b", f);
			} else {

			}
		} else if ((*ptr) == '\r') {
			fputs("\\r", f);
		} else if ((*ptr) == '\f') {
			fputs("\\f", f);
		} else if ((*ptr) == '/') {
			fputs("\\/", f);
		} else {
			fputc((*ptr), f);
		}
		ptr++;
	}

	return;
}

void graph2jgf(struct gml_graph *g, FILE * f)
{
	struct gml_elist *el = NULL;
	struct gml_nlist *lnl = NULL;
	struct gml_node *un = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	int color = 0;
	int rc = 0;
	int gc = 0;
	int bc = 0;

	/* head */
	fprintf(f, "{\n");
	fprintf(f, "  \"graph\": {\n");

	/* optional graph data */
	fprintf(f, "    \"id\": \"gml4gtk\",\n");
	if (1)
		fprintf(f, "    \"type\": \"schema test\",\n");
	fprintf(f, "    \"label\": \"gml4gtk\",\n");

	/* print the node list with real nodes */
	lnl = g->rawnodelist;

	fprintf(f, "    \"nodes\": {\n");

	while (lnl) {
		un = lnl->node;

		fprintf(f, "      \"");
		graph2jgflabel(un->name, f);
		fputs("\": {\n", f);

		/* id is optional */
		if (0) {
			fprintf(f, "        \"id\": \"");
			graph2jgflabel(un->name, f);
			fputs("\",\n", f);
		}

		/* at html, record label set node name */
		if (un->rlabel || un->hlabel) {
			fprintf(f, "        \"label\": \"");
			graph2jgflabel(un->name, f);
			fputs("\",\n", f);
		} else {
			if (un->nlabel) {
				/* this can be "" labels */
				fprintf(f, "        \"label\": \"");
				graph2jgflabel(un->nlabel, f);
				fputs("\",\n", f);
			} else {
				fprintf(f, "        \"label\": \"");
				graph2jgflabel(un->name, f);
				fputs("\",\n", f);
			}
		}

		fprintf(f, "        \"metadata\": {\n");

		if (1) {
			color = un->ncolor;

			/* fill color of node white default or color */
			rc = (color & 0x00ff0000) >> 16;
			gc = (color & 0x0000ff00) >> 8;
			bc = (color & 0x000000ff);

			fprintf(f, "          \"fillcolor\": \"#%02x%02x%02x\",\n", rc, gc, bc);

			color = un->nbcolor;

			/* border color of node black default or color */
			rc = (color & 0x00ff0000) >> 16;
			gc = (color & 0x0000ff00) >> 8;
			bc = (color & 0x000000ff);

			fprintf(f, "          \"bordercolor\": \"#%02x%02x%02x\",\n", rc, gc, bc);

			color = un->fontcolor;

			/* font color of node black default or color */
			rc = (color & 0x00ff0000) >> 16;
			gc = (color & 0x0000ff00) >> 8;
			bc = (color & 0x000000ff);

			fprintf(f, "          \"fontcolor\": \"#%02x%02x%02x\"\n", rc, gc, bc);
		}
		/* end of metadata */
		fprintf(f, "        }\n");

		/* end of node */
		fprintf(f, "      }");

		if (lnl->next) {
			fprintf(f, ",");
		}
		fprintf(f, "\n");

		/* next node */
		lnl = lnl->next;
	}

	/* end of nodes */
	fprintf(f, "    },\n");

	fprintf(f, "    \"edges\": [\n");

	el = g->rawedgelist;
	while (el) {
		/* from/to node */
		sn = el->edge->from_node;
		tn = el->edge->to_node;
		fprintf(f, "      {\n");
		if (el->edge->elabel) {
			if (el->edge->ishtml == 0) {
				/* skip "" labels */
				if (strlen(el->edge->elabel)) {
					fprintf(f, "        \"label\": \"");
					graph2jgflabel(el->edge->elabel, f);
					fputs("\",\n", f);
				}
			}
		}
		fprintf(f, "        \"source\": \"");
		graph2jgflabel(sn->name, f);
		fputs("\",\n", f);
		fprintf(f, "        \"target\": \"");
		graph2jgflabel(tn->name, f);
		fputs("\"\n", f);

		if (0) {
			fprintf(f, "        \"relation\": \"edge\"\n");
		}

		fprintf(f, "      }");
		if (el->next) {
			fprintf(f, ",\n");
		} else {
			fprintf(f, "\n");
		}
		el = el->next;
	}

	/* end of edges */
	fprintf(f, "    ],\n");

	/* end of nodes+edges */

	fprintf(f, "    \"metadata\": {}\n");

	/* end of "graph": { */
	fprintf(f, "  }\n");

	/* tail */
	fprintf(f, "}\n");

	return;
}

/* compare outgoing edges, looking at the to-node prosition */
static int edgescompareout(const void *p, const void *q)
{
	struct gml_edge *l;
	struct gml_edge *r;
	struct gml_node *ll;
	struct gml_node *rr;
	int lll = 0;
	int rrr = 0;
	l = *(struct gml_edge **)p;
	r = *(struct gml_edge **)q;
	ll = l->to_node;
	rr = r->to_node;
	lll = ll->finx;
	rrr = rr->finx;
	return (lll - rrr);
}

/* compare incoming edges, looking at the from-node prosition */
static int edgescomparein(const void *p, const void *q)
{
	struct gml_edge *l;
	struct gml_edge *r;
	struct gml_node *ll;
	struct gml_node *rr;
	int lll = 0;
	int rrr = 0;
	l = *(struct gml_edge **)p;
	r = *(struct gml_edge **)q;
	ll = l->from_node;
	rr = r->from_node;
	lll = ll->finx;
	rrr = rr->finx;
	return (lll - rrr);
}

/* calculate edge connections */
void edgeconnections(struct gml_graph *g)
{
	struct gml_elist *ell;
	struct gml_nlist *lnl;
	int i = 0;
	if (g->edgelist == NULL) {
		/* no edges, nothing to do here */
		return;
	}

	/* mark vertical edges */
	ell = g->edgelist;
	while (ell) {
		ell->edge->vedge = 0;
		if ((ell->edge->from_node->finx + (ell->edge->from_node->bbx / 2)) ==
		    (ell->edge->to_node->finx + (ell->edge->to_node->bbx / 2))) {
			/* mark edge as perfect vertical */
			ell->edge->vedge = 1;
		}
		ell = ell->next;
	}

	/* make arrays with edges in every node */
	lnl = g->nodelist;
	while (lnl) {
		if (lnl->node->indegree > 1) {
			/* check if enough size at node for edge placement */
			if ((lnl->node->indegree * 3 + 15 + 15) < lnl->node->bbx) {
				lnl->node->iedges = (struct gml_edge **)dp_calloc(1, (sizeof(struct gml_edge *))
										  * lnl->node->indegree);
				i = 0;
				ell = lnl->node->incoming_e;
				while (ell) {
					lnl->node->iedges[i] = ell->edge;
					i++;
					ell = ell->next;
				}
				qsort((void *)lnl->node->iedges, (size_t)lnl->node->indegree,
				      (size_t)sizeof(struct gml_edge *), edgescomparein);
				lnl->node->dx_iedges = ((lnl->node->bbx - 15 - 15) / (lnl->node->indegree - 1));
			} else {
				lnl->node->iedges = NULL;
				lnl->node->dx_iedges = 0;
			}
		}

		if (lnl->node->outdegree > 1) {
			if ((lnl->node->outdegree * 3 + 15 + 15) < lnl->node->bbx) {
				lnl->node->oedges = (struct gml_edge **)dp_calloc(1, (sizeof(struct gml_edge *))
										  * lnl->node->outdegree);
				i = 0;
				ell = lnl->node->outgoing_e;
				while (ell) {
					lnl->node->oedges[i] = ell->edge;
					i++;
					ell = ell->next;
				}
				qsort((void *)lnl->node->oedges,
				      (size_t)lnl->node->outdegree, (size_t)sizeof(struct gml_edge *), edgescompareout);
				lnl->node->dx_oedges = ((lnl->node->bbx - 15 - 15) / (lnl->node->outdegree - 1));
			} else {
				lnl->node->oedges = NULL;
				lnl->node->dx_oedges = 0;
			}
		}

		lnl = lnl->next;
	}

	return;
}

/* clear number of edges between level n and N+1 */
void clear_nume_r(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_nume_r(gl->sg);
		gl = gl->next;
	}

	if (g->nume) {
		dp_free(g->nume);
	}

	g->nume = NULL;
	return;
}

/* free one record label info */
static void clear_rlabel2(struct gml_rl *info)
{
	int i = 0;

	if (info == NULL) {
		return;
	}

	/* first recursive free the sub-parts of this info, then info itself */
	if (info->parts) {
		for (i = 0; i < info->nparts; i++) {
			clear_rlabel2(info->parts[i]);
		}
		dp_free(info->parts);
	}

	info->parts = NULL;
	info->label = NULL;
	info->ulabel = NULL;
	info->nparts = 0;
	dp_free(info);
	return;
}

/* clear optional record labels */
void clear_rlabel_r(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_rlabel_r(gl->sg);
		gl = gl->next;
	}

	lnll = g->nodelist;
	while (lnll) {
		if (lnll->node->rlabel) {
			clear_rlabel2(lnll->node->rlabel);
			lnll->node->rlabel = NULL;
		}
		lnll = lnll->next;
	}

	return;
}

/* clear html items list */
static void clear_hlabel2il(struct gml_hilist *il)
{
	struct gml_hilist *ptr = NULL;
	struct gml_hilist *ptrnext = NULL;

	ptr = il;

	while (ptr) {
		ptrnext = ptr->next;
		/* free the html item data */
		if (ptr->items) {
			dp_free(ptr->items);
			ptr->items = NULL;
		}
		dp_free(ptr);
		ptr = NULL;
		ptr = ptrnext;
	}

	return;
}

/* clear <td> data */
static void clear_hlabel2td(struct gml_tritem *tritem)
{
	struct gml_tditem *tdiptr = NULL;
	struct gml_tditem *tdiptrnext = NULL;

	if (tritem == NULL) {
		return;
	}
	if (tritem->tdi == NULL) {
		return;
	}
	tdiptr = tritem->tdi;
	while (tdiptr) {
		tdiptrnext = tdiptr->next;
		if (tdiptr->il) {
			/* clear il data in this <td> */
			clear_hlabel2il(tdiptr->il);
		}
		tdiptr->il = NULL;
		tdiptr->ilend = NULL;
		dp_free(tdiptr);
		tdiptr = tdiptrnext;
	}
	tritem->tdi = NULL;
	tritem->tdiend = NULL;
	return;
}

/* recurse free sub-table data */
static void clear_hlabel2tl_r(struct gml_titem *titem)
{
	struct gml_htlist *ptr = NULL;
	struct gml_htlist *ptrnext = NULL;
	struct gml_tritemlist *trptr = NULL;	/* list of <tr> items in this table */
	struct gml_tritemlist *trptrnext = NULL;	/* list of <tr> items in this table */

	if (titem == NULL) {
		return;
	}

	ptr = titem->tl;

	/* first recurse in sub tables if any */
	while (ptr) {
		ptrnext = ptr->next;
		/* free the table data */
		if (ptr->titem) {
			clear_hlabel2tl_r(ptr->titem);
			if (ptr->titem->tl) {
				ptr->titem->tl = NULL;
				ptr->titem->tlend = NULL;
			}
			/* free the <tr> data in this table */
			if (ptr->titem->tr) {
				trptr = ptr->titem->tr;
				while (trptr) {
					trptrnext = trptr->next;
					if (trptr->tritem) {
						/* clear <td> data */
						clear_hlabel2td(trptr->tritem);
						dp_free(trptr->tritem);
						trptr->tritem = NULL;
					}
					dp_free(trptr);
					trptr = trptrnext;
				}
				ptr->titem->tr = NULL;
				ptr->titem->trend = NULL;
			}

			dp_free(ptr->titem);
			ptr->titem = NULL;
		}
		dp_free(ptr);
		ptr = NULL;
		ptr = ptrnext;
	}

	titem->tl = NULL;
	titem->tlend = NULL;

	/* clear the titem data */

	return;
}

/* clear html tables list */
static void clear_hlabel2tl(struct gml_htlist *titem)
{
	struct gml_htlist *ptr = NULL;
	struct gml_htlist *ptrnext = NULL;
	struct gml_tritemlist *trptr;	/* list of <tr> items in this table */
	struct gml_tritemlist *trptrnext;	/* list of <tr> items in this table */

	ptr = titem;

	while (ptr) {
		ptrnext = ptr->next;
		/* free the table data */
		if (ptr->titem) {
			clear_hlabel2tl_r(ptr->titem);
			/* free the sub table data */
			if (ptr->titem->tl) {
				ptr->titem->tl = NULL;
				ptr->titem->tlend = NULL;
			}
			/* free the <tr> data in this table */
			if (ptr->titem->tr) {
				trptr = ptr->titem->tr;
				while (trptr) {
					trptrnext = trptr->next;
					if (trptr->tritem) {
						/* clear <td> data */
						clear_hlabel2td(trptr->tritem);
						dp_free(trptr->tritem);
						trptr->tritem = NULL;
					}
					dp_free(trptr);
					trptr = trptrnext;
				}
				ptr->titem->tr = NULL;
				ptr->titem->trend = NULL;
			}

			dp_free(ptr->titem);
			ptr->titem = NULL;

		}

		dp_free(ptr);
		ptr = NULL;
		ptr = ptrnext;
	}

	return;
}

/* free one html label info */
static void clear_hlabel2(struct gml_hl *info)
{

	if (info == NULL) {
		return;
	}

	/* only il or tl should be set */
	if (info->il) {
		clear_hlabel2il(info->il);
		info->il = NULL;
		info->ilend = NULL;
	}

	if (info->tl) {
		clear_hlabel2tl(info->tl);
		info->tl = NULL;
		info->tlend = NULL;
	}

	info->mode = 0;

	dp_free(info);

	return;
}

/* clear optional html labels */
void clear_hlabel_r(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_hlabel_r(gl->sg);
		gl = gl->next;
	}

	lnll = g->nodelist;
	while (lnll) {
		if (lnll->node->hlabel) {
			clear_hlabel2(lnll->node->hlabel);
			lnll->node->hlabel = NULL;
		}
		lnll = lnll->next;
	}

	return;
}

/* clear arrays in/out edges in nodes
 * and number of edge crossings at level
 */
void clear_ioedges_r(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_ioedges_r(gl->sg);
		gl = gl->next;
	}

	lnll = g->nodelist;
	while (lnll) {
		/* array with out edges */
		if (lnll->node->oedges) {
			dp_free(lnll->node->oedges);
			lnll->node->oedges = NULL;
		}
		lnll->node->dx_oedges = 0;
		/* array with in edges */
		if (lnll->node->iedges) {
			dp_free(lnll->node->iedges);
			lnll->node->iedges = NULL;
		}
		lnll->node->dx_iedges = 0;
		lnll = lnll->next;
	}

	return;
}

/* clear number of edge crossings at level */
void clear_numce_r(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_numce_r(gl->sg);
		gl = gl->next;
	}

	if (g->numce) {
		dp_free(g->numce);
	}

	g->numce = NULL;
	return;
}

/* clear the s/t list of a node */
void clear_stlist(struct gml_node *node)
{
	struct gml_elist *ell = NULL;
	struct gml_elist *ellnext = NULL;
	/* free outgoing edges */
	ell = node->outgoing_e;
	while (ell) {
		ellnext = ell->next;
		dp_free(ell);
		ell = NULL;
		ell = ellnext;
	}

	node->outgoing_e = NULL;
	node->outgoing_etail = NULL;
	node->outdegree = 0;
	/* free incoming edges */
	ell = node->incoming_e;
	while (ell) {
		ellnext = ell->next;
		dp_free(ell);
		ell = NULL;
		ell = ellnext;
	}

	node->incoming_e = NULL;
	node->incoming_etail = NULL;
	node->indegree = 0;
	return;
}

/* clear the s/t list of all nodes */
void clear_stlist_all(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	lnll = g->nodelist;
	while (lnll) {
		clear_stlist(lnll->node);
		lnll = lnll->next;
	}

	return;
}

/* clear nodelist, nodes and inside nodes */
void clear_rawnodelist(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	lnll = g->rawnodelist;
	while (lnll) {
		nlnext = lnll->next;
		dp_free(lnll->node);
		lnll->node = NULL;
		dp_free(lnll);
		lnll = NULL;
		lnll = nlnext;
	}
	g->rawnodelist = NULL;
	g->rawnodelisttail = NULL;
	g->nodenum = 0;
	g->nnodes = 0;
	return;
}

/* clear edgelist */
void clear_rawedgelist(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_elist *elnext = NULL;
	el = g->rawedgelist;
	while (el) {
		elnext = el->next;
		dp_free(el->edge);
		el->edge = NULL;
		dp_free(el);
		el = NULL;
		el = elnext;
	}
	g->rawedgelist = NULL;
	g->rawedgelisttail = NULL;
	g->nedges = 0;
	g->edgenum = 0;
	return;
}

/* clear nodelist, nodes and inside nodes
 * if mode==0 also clear record node label data
 * if mode<>0 keep the rlabel record label data
 */
void clear_nodelist_r(struct gml_graph *g, int mode)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_nodelist_r(gl->sg, mode);
		gl = gl->next;
	}

	clear_stlist_all(g);
	lnll = g->nodelist;
	while (lnll) {
		nlnext = lnll->next;
		/* if 0, clear also record label data */
		if (mode == 0) {
			if (lnll->node->rlabel) {
				clear_rlabel2(lnll->node->rlabel);
				lnll->node->rlabel = NULL;
			}
		}
		dp_free(lnll->node);
		lnll->node = NULL;
		dp_free(lnll);
		lnll = NULL;
		lnll = nlnext;
	}

	g->nodelist = NULL;
	g->nodelisttail = NULL;
	g->nnodes = 0;
	/* for re-layout do not clear the g->nodenum here */
	return;
}

/* clear single node list */
void clear_singlenodelist_r(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_singlenodelist_r(gl->sg);
		gl = gl->next;
	}

	lnll = g->singlenodelist;
	while (lnll) {
		nlnext = lnll->next;
		dp_free(lnll);
		lnll = NULL;
		lnll = nlnext;
	}

	g->singlenodelist = NULL;
	g->nsinglenodes = 0;
	return;
}

/* clear self-edges node list */
void clear_selfedgesnodelist_r(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_selfedgesnodelist_r(gl->sg);
		gl = gl->next;
	}

	lnll = g->selfedgesnodelist;
	while (lnll) {
		nlnext = lnll->next;
		dp_free(lnll);
		lnll = NULL;
		lnll = nlnext;
	}

	g->selfedgesnodelist = NULL;
	g->nselfedges = 0;
	return;
}

/* clear edgelist */
void clear_edgelist_r(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_elist *elnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_edgelist_r(gl->sg);
		gl = gl->next;
	}

	el = g->edgelist;
	while (el) {
		elnext = el->next;
		dp_free(el->edge);
		el->edge = NULL;
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	/* no edge labels */
	g->edgelist = NULL;
	g->nedgelabels = 0;
	g->nedges = 0;
	/* for re-layout do not clear the g->edgenum here */
	return;
}

/* rebuild nodes st lists */
void make_stlist(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	struct gml_elist *ne = NULL;
	struct gml_nlist *lnll = NULL;
	/* refresh degree count of nodes */
	lnll = g->nodelist;
	while (lnll) {
		/* make ure these are cleared */
		lnll->node->outgoing_e = NULL;	/* source list, outgoing edges */
		lnll->node->outgoing_etail = NULL;	/* source list, outgoing edges */
		lnll->node->oedges = NULL;	/* array outgoing edges */
		lnll->node->incoming_e = NULL;	/* target list, incoming edges */
		lnll->node->incoming_etail = NULL;	/* target list, incoming edges */
		lnll->node->iedges = NULL;	/* array incoming edges */
		lnll->node->indegree = 0;
		lnll->node->outdegree = 0;
		lnll = lnll->next;
	}

	el = g->edgelist;
	while (el) {
		edge = el->edge;
		/* from/to nodes */
		sn = edge->from_node;
		tn = edge->to_node;
		ne = dp_calloc(1, sizeof(struct gml_elist));
		if (ne == NULL) {
			return;
		}

		ne->edge = edge;
		/* list of outgoing edges */
		if (sn->outgoing_e == NULL) {
			sn->outgoing_e = ne;
			sn->outgoing_etail = ne;
		} else {
			sn->outgoing_etail->next = ne;
			sn->outgoing_etail = ne;
		}

		sn->outdegree++;
		ne = dp_calloc(1, sizeof(struct gml_elist));
		if (ne == NULL) {
			return;
		}

		ne->edge = edge;
		/* list of incoming edges */
		if (tn->incoming_e == NULL) {
			tn->incoming_e = ne;
			tn->incoming_etail = ne;
		} else {
			tn->incoming_etail->next = ne;
			tn->incoming_etail = ne;
		}

		tn->indegree++;
		el = el->next;
	}

	return;
}

/* delete edge when replaced with a chain of edges */
void del_edge(struct gml_graph *g, struct gml_elist *edgeel)
{
	struct gml_elist *elprev = NULL;
	struct gml_elist *el = NULL;
	struct gml_elist *elto = NULL;
	if (g->edgelist == NULL) {
		return;
	}

	if (edgeel == g->edgelist) {
		g->edgelist = g->edgelist->next;
		if (g->edgelisttail == edgeel) {
			g->edgelisttail = NULL;
		} else {
			el = g->edgelist;
			elprev = el;
			while (el) {
				elprev = el;
				if (el->next == edgeel) {
					break;
				}
				el = el->next;
			}
			g->edgelisttail = elprev;
		}

		dp_free(edgeel->edge);
		edgeel->edge = NULL;
		dp_free(edgeel);
	} else {

		elto = edgeel->next;
		el = g->edgelist;
		elprev = el;
		while (el) {
			elprev = el;
			if (el->next == edgeel) {
				break;
			}
			el = el->next;
		}

		elprev->next = elto;
		if (g->edgelisttail == edgeel) {
			g->edgelisttail = elprev;
		}

		dp_free(edgeel->edge);
		edgeel->edge = NULL;
		dp_free(edgeel);
	}

	return;
}

/* splits edgelabel edges into node->label->node */
void edgelabels(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_elist *elnext = NULL;
	struct gml_node *ln = NULL;
	char rev = 0;
	int ecolor = 0;
	int style = 0;
	char *fc = NULL;
	char *tc = NULL;
	char constraint = 0;
	int ydiff = 0;
	int ishtml = 0;
	if (g->nedgelabels == 0) {
		/* no edge labels, nothing todo here */
		return;
	}

	/* scan edges all downwards */
	el = g->edgelist;
	while (el) {
		/* make sure, from-node is lower y then to-node */
		if (el->edge->from_node->y > el->edge->to_node->y) {
			ln = el->edge->from_node;
			el->edge->from_node = el->edge->to_node;
			el->edge->to_node = ln;
			/* toggle rev flag */
			if (el->edge->reversed) {
				el->edge->reversed = 0;
			} else {
				el->edge->reversed = 1;
			}
		}
		el = el->next;
	}

	/* scan edges for edge labels */
	el = g->edgelist;
	while (el) {
		elnext = el->next;
		/* do if there is a edge label */
		if (el->edge->elabel) {

			/* edge attr. is-reversed */
			rev = el->edge->reversed;
			ecolor = el->edge->ecolor;
			style = el->edge->style;
			fc = el->edge->fcompass;
			tc = el->edge->tcompass;
			constraint = el->edge->constraint;
			/* set if html label */
			ishtml = el->edge->ishtml;
			maingraph->nodenum++;
			/* create label node */
			add_new_dummynode(g, maingraph->nodenum);
			/* mark this is a label node and set label text */
			ln = uniqnode2(NULL, maingraph->nodenum);
			/* edge-label-node, original from/to node */
			ln->el_fnode = el->edge->from_node;
			ln->el_tnode = el->edge->to_node;
			/* y level difference between original from/to-nodes */
			ydiff = (ln->el_tnode->y - ln->el_fnode->y);
			if (0) {
				printf("%s(): ydiff=%d\n", __func__, ydiff);
			}
			/* put edge label halfway */
			ln->y = ln->el_fnode->y + (ydiff / 2);
			ln->elabel = 1;	/* mark this is a edgelabel */
			ln->dummy = 0;
			ln->name = el->edge->elabel;
			ln->nlabel = el->edge->elabel;
			/* node belongs to graph with this startnode */
			ln->startnode = el->edge->from_node->startnode;
			/* set if html label */
			ln->ishtml = ishtml;
			/* create new edges with label node in between */
			add_new_dummyedge(g, el->edge->rootedon, el->edge->from_node->nr,
					  maingraph->nodenum, rev, ecolor, style, fc, tc, constraint);
			add_new_dummyedge(g, el->edge->rootedon, maingraph->nodenum,
					  el->edge->to_node->nr, rev, ecolor, style, fc, tc, constraint);
			/* free old edge */
			del_edge(g, el);
		}

		el = elnext;
	}

	return;
}

/* v3 is oke using grey */
static int decycle3(struct gml_graph *g, struct gml_node *n, int level, struct gml_edge *e)
{
	struct gml_node *tmpnode = NULL;
	struct gml_node *source = NULL;
	struct gml_node *target = NULL;
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	int changed = 0;
	if (e) {
	}

	if (n->done) {
		if (level > n->y) {
			n->y = level;
		}
		return (0);
	}

	n->y = level;
	n->done = 1;
	/* mark this node is being processed */
	n->grey = 1;
	source = n;
	/* follow outgoing edges */
	el = source->outgoing_e;
	while (el) {
		edge = el->edge;
		/* get the to-node */
		target = edge->to_node;
		if (target->grey) {
			changed++;
			tmpnode = edge->to_node;
			edge->to_node = edge->from_node;
			edge->from_node = tmpnode;
			/* toggle the edge is reversed bit */
			if (edge->reversed) {
				edge->reversed = 0;
			} else {
				edge->reversed = 1;
			}
		} else {
			if (target->done == 0) {
				changed += decycle3(g, target, (level + 1), e);
			}
		}
		el = el->next;
	}

	/* this node is ready being processed */
	n->grey = 0;
	return (changed);
}

/* reorg nodelist */
void reorg(struct gml_graph *g)
{
	struct gml_nlist *nl = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_nlist *nn = NULL;
	struct gml_nlist *nnl = NULL;
	struct gml_nlist *nnlend = NULL;
	nl = g->nodelist;
	if (nl == NULL) {
		return;
	}

	while (nl) {
		/* first the single nodes */
		if (nl->node->indegree == 0 && nl->node->outdegree == 0) {
			nn = dp_calloc(1, sizeof(struct gml_nlist));
			if (nn) {
				nn->node = nl->node;
				if (nnl == NULL) {
					nnl = nn;
					nnlend = nn;
				} else {
					nnlend->next = nn;
					nnlend = nn;
				}
			}
		}
		nl = nl->next;
	}

	nl = g->nodelist;
	while (nl) {
		/* second the starter nodes */
		if (nl->node->indegree == 0 && nl->node->outdegree != 0) {
			nn = dp_calloc(1, sizeof(struct gml_nlist));
			if (nn) {
				nn->node = nl->node;
				if (nnl == NULL) {
					nnl = nn;
					nnlend = nn;
				} else {
					nnlend->next = nn;
					nnlend = nn;
				}
			}
		}
		nl = nl->next;
	}

	nl = g->nodelist;
	while (nl) {
		/* third the middle nodes */
		if (nl->node->indegree != 0 && nl->node->outdegree != 0) {
			nn = dp_calloc(1, sizeof(struct gml_nlist));
			if (nn) {
				nn->node = nl->node;
				if (nnl == NULL) {
					nnl = nn;
					nnlend = nn;
				} else {
					nnlend->next = nn;
					nnlend = nn;
				}
			}
		}
		nl = nl->next;
	}

	nl = g->nodelist;
	while (nl) {
		/* fourth the tail nodes */
		if (nl->node->indegree != 0 && nl->node->outdegree == 0) {
			nn = dp_calloc(1, sizeof(struct gml_nlist));
			if (nn) {
				nn->node = nl->node;
				if (nnl == NULL) {
					nnl = nn;
					nnlend = nn;
				} else {
					nnlend->next = nn;
					nnlend = nn;
				}
			}
		}
		nl = nl->next;
	}

	/* clear nodelist */
	nl = g->nodelist;
	while (nl) {
		nlnext = nl->next;
		dp_free(nl);
		nl = NULL;
		nl = nlnext;
	}

	/* set the refreshed nodelist but keep the nodes */
	g->nodelist = nnl;
	g->nodelisttail = nnlend;
	return;
}

/* break cycles in the graph */
void uncycle(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	int changed = 0;
	int sn = 0;
	int sin = 0;
	/* build the s/tlist of a node */
	clear_stlist_all(g);
	make_stlist(g);
	/* revert cycles at the last edge in the chain */
	g->maxlevel = 0;
	lnll = g->nodelist;
	while (lnll) {
		lnll->node->y = -1;
		lnll->node->done = 0;
		lnll->node->grey = 0;
		lnll = lnll->next;
	}

	/* first the startnodes */
	lnll = g->nodelist;
	changed = 0;
	sn = 0;
	while (lnll) {
		/* select start nodes */
		if (lnll->node->indegree == 0 && lnll->node->outdegree != 0) {
			sn++;
			if (lnll->node->done == 0) {
				/* use v3 */
				changed += decycle3(g, lnll->node, 0, NULL);
			}
		}
		lnll = lnll->next;
	}

	/* check nodes */
	lnll = g->nodelist;
	while (lnll) {
		/* select other nodes */
		if (lnll->node->y == -1) {
			/* use v3 */
			changed += decycle3(g, lnll->node, 0, NULL);
		}
		lnll = lnll->next;
	}

	if (changed) {
		/* build the s/tlist of a node */
		clear_stlist_all(g);
		make_stlist(g);
		/* check nodes, count startnodes */
		lnll = g->nodelist;
		sn = 0;
		sin = 0;
		while (lnll) {
			/* count start nodes */
			if (lnll->node->indegree == 0 && lnll->node->outdegree != 0) {
				sn++;
			}
			/* count single nodes */
			if (lnll->node->indegree == 0 && lnll->node->outdegree == 0) {
				sin++;
			}
			if (lnll->node->y == -1) {
				/* should not be printed */
				printf("*");
			}
			lnll = lnll->next;
		}

		printf("%s(): changed %d edges with %d startnodes\n", __func__, changed, sn);
		/* print nodes list */
		if (0) {
			lnll = g->nodelist;
			while (lnll) {
				printf("%s indegree=%d outdegree=%d\n", lnll->node->nlabel, lnll->node->indegree,
				       lnll->node->outdegree);
				lnll = lnll->next;
			}
		}
	}

	/* check nodes, count startnodes */
	lnll = g->nodelist;
	sn = 0;
	sin = 0;
	while (lnll) {
		if (lnll->node->indegree == 0 && lnll->node->outdegree != 0) {
			sn++;
		}
		if (lnll->node->indegree == 0 && lnll->node->outdegree == 0) {
			sin++;
		}
		if (lnll->node->y == -1) {
			/* should not be printed */
			printf("*");
		}
		lnll = lnll->next;
	}

	printf("%s(): there are %d start nodes\n", __func__, sn);
	if (sin) {
		printf("%s(): there are %d single nodes\n", __func__, sin);
	}

	/* if no startnodes, there can be only single nodes */

	fflush(stdout);
	/* make sure the rebuild of the s/tlist of a node */
	clear_stlist_all(g);
	make_stlist(g);
	return;
}

/* all edges downwards */
void edgesdownwards(struct gml_graph *g, int modes)
{
	struct gml_elist *el = NULL;
	struct gml_node *tmpnode = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	struct gml_edge *edge = NULL;
	int changed0 = 0;
	int changed1 = 0;

	if (yydebug || 1) {
		printf("%s(): mode=%d\n", __func__, modes);
	}

	if (modes == 0) {

		el = g->edgelist;
		while (el) {
			edge = el->edge;
			sn = edge->from_node;
			tn = edge->to_node;
			if ((tn->y - sn->y) < 0) {
				if (yydebug || 0) {
					printf
					    ("%s(%d): edge length < 0 (%d) at nodes %d->%d at level %d->%d swapping\n",
					     __func__, modes, (tn->y - sn->y), sn->id, tn->id, sn->y, tn->y);
				}

				/* swap */
				tmpnode = tn;
				el->edge->to_node = el->edge->from_node;
				el->edge->from_node = tmpnode;
				/* toggle the edge is reversed bit */
				if (el->edge->reversed) {
					el->edge->reversed = 0;
				} else {
					el->edge->reversed = 1;
				}
				changed0++;
			}

			el = el->next;
		}

	} else {

		el = g->edgelist;
		while (el) {
			edge = el->edge;
			sn = edge->from_node;
			tn = edge->to_node;
			if (yydebug || 0) {
				printf("%s(): edge \"%s\"->\"%s\" rev=%d\n", __func__, sn->nlabel, tn->nlabel, edge->reversed);
			}
			if ((tn->y - sn->y) < 0) {
				if (yydebug || 0) {
					printf
					    ("%s(%d): edge length < 0 (%d) at nodes %d->%d \"%s\"->\"%s\" at level %d->%d swapping\n",
					     __func__, modes, (tn->y - sn->y), sn->id, tn->id, sn->nlabel, tn->nlabel, sn->y,
					     tn->y);
				}

				/* swap */
				tmpnode = tn;
				edge->to_node = edge->from_node;
				edge->from_node = tmpnode;
				/* toggle the edge is reversed bit */
				if (edge->reversed) {
					edge->reversed = 0;
				} else {
					edge->reversed = 1;
				}
				changed1++;
				if (yydebug || 0) {
					printf("%s(): changed into edge \"%s\"->\"%s\" rev=%d\n", __func__, sn->nlabel, tn->nlabel,
					       edge->reversed);
				}

			}

			el = el->next;
		}

	}

	if (changed0) {
		printf("%s(0): changed %d edges\n", __func__, changed0);
	}

	if (changed1) {
		printf("%s(1): changed %d edges\n", __func__, changed1);
	}

	if (changed0 || changed1) {
		/* rebuild the in/out edges lists at the nodes in the modified graph */
		g->maxlevel = 0;
		/* refresh st lists */
		clear_stlist_all(g);
		make_stlist(g);
	}

	return;
}

struct bfsqueue {
	int item;
	struct bfsqueue *child;
};

static struct bfsqueue *bfsfrontpointer = NULL;
static struct bfsqueue *bfsrearpointer = NULL;

static void bfsinsertq(int v)
{
	struct bfsqueue *p = NULL;
	p = (struct bfsqueue *)dp_calloc(1, sizeof(struct bfsqueue));
	if (p == NULL) {
		/* shouldnothappen */
		return;
	}
	p->item = v;
	p->child = NULL;
	bfsrearpointer->child = p;
	bfsrearpointer = bfsrearpointer->child;
	return;
}

static int bfsremoveq(void)
{
	struct bfsqueue *p = NULL;
	p = bfsfrontpointer;
	bfsfrontpointer = p->child;
	dp_free(p);
	p = NULL;
	return (bfsfrontpointer->item);
}

/* return 1 if no items anymore */
static int bfsemptyq(void)
{
	if (bfsfrontpointer == bfsrearpointer) {
		return (1);
	} else {
		return (0);
	}
}

/* use bfs to set level, start at node n, at level i with startnode number startnode */
static void set_bfslevel(struct gml_graph *g, struct gml_node *n, int i, int startnode)
{
	int flag = 0;
	int v = 0;
	int counter = 0;
	int o = 0;
	int t = 0;
	int po = 0;
	struct gml_elist *el = NULL;
	struct gml_node *target = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *vt = NULL;

	/* set graph max. level to start level */
	g->maxlevel = i;

	/* startlevel */
	counter = i;

	/* unused high node nr as marker */
	flag = (g->nodenum * 2);

	/* outdegree of start node */
	po = n->outdegree;

	bfsfrontpointer = (struct bfsqueue *)dp_calloc(1, sizeof(struct bfsqueue));
	bfsrearpointer = bfsfrontpointer;

	/* set first node at start level */
	if (n->y == (-1)) {
		n->y = i;
		n->startnode = startnode;
	}

	bfsinsertq(flag);
	bfsinsertq(n->nr);
	bfsinsertq(flag);

	/* while q has data */
	while (!bfsemptyq()) {
		v = bfsremoveq();
		if (v == flag) {
			/* increment level */
			counter++;
		} else {
			/* follow outgoing edges */
			vt = uniqnode2(g, v);
			if (vt) {
				el = vt->outgoing_e;
				while (el) {
					edge = el->edge;
					target = edge->to_node;
					o++;
					t += target->outdegree;
					if (target->y < counter) {
						target->y = counter;
						if (counter > g->maxlevel) {
							g->maxlevel = counter;
						}
						target->startnode = startnode;
						if (yydebug || 0) {
							printf("%s(): node \"%s\" set at level %d\n", __func__, target->name,
							       counter);
						}
					}
					bfsinsertq(target->nr);
					if (o == po) {
						bfsinsertq(flag);
						o = 0;
						po = t;
						t = 0;
					}
					el = el->next;
				}
			} else {
				/* shouldnothappen */
				printf("%s(): cannot find node with number %d\n", __func__, v);
			}
		}
	}

	/* empty q */
	if (bfsfrontpointer->child) {
		dp_free(bfsfrontpointer->child);
		bfsfrontpointer->child = NULL;
	}
	dp_free(bfsfrontpointer);

	bfsrearpointer = NULL;
	bfsfrontpointer = NULL;

	return;
}

/*
 * See also https://en.wikipedia.org/wiki/Topological_sorting
 * L ← Empty list that will contain the sorted nodes
 * while exists nodes without a permanent mark do
 *     select an unmarked node n
 *     visit(n)
 *
 * function visit(node n)
 *     if n has a permanent mark then
 *         return
 *     if n has a temporary mark then
 *         stop   (not a DAG)
 *
 *     mark n with a temporary mark
 *
 *     for each node m with an edge from n to m do
 *         visit(m)
 *
 *     remove temporary mark from n
 *     mark n with a permanent mark
 *     add n to head of L
 */

static int span = 0;

/* topological set rel. y level of nodes */
static void set_tlevel0(struct gml_graph *g, struct gml_node *n, int i, int startnode)
{
	struct gml_node *target = NULL;
	struct gml_edge *edge = NULL;
	struct gml_elist *el = NULL;
	if (i) {
	}

	if (n->done) {
		return;
	}

	/* follow outgoing edges */
	el = n->outgoing_e;
	while (el) {
		edge = el->edge;
		target = edge->to_node;
		set_tlevel0(g, target, span, startnode);
		el = el->next;
	}

	if (n->y < 0) {
		n->startnode = startnode;
	}
	n->y = span;
	span++;
	if (yydebug || 0) {
		printf("%s(): setting `%s' to level %d\n", __func__, n->name, n->y);
	}

	if (span > g->maxlevel) {
		g->maxlevel = span;
	}

	n->done = 1;

	return;
}

/* set rel. y level of nodes */
static void set_level2(struct gml_graph *g, struct gml_node *n, int i, int startnode)
{
	struct gml_node *target = NULL;
	struct gml_edge *edge = NULL;
	struct gml_elist *el = NULL;
	if (n->done) {
		if (i > n->y && n->grey == 0) {
			n->y = i;
			if (n->y < 0) {
				n->startnode = startnode;
			}
		}
		if (n->grey) {
			return;
		}
		if (n->done > 1) {
			return;
		}
	}

	n->grey++;
	n->done++;
	if (n->y < 0) {
		n->startnode = startnode;
	}
	n->y = span;
	if (yydebug || 0) {
		printf("%s(): setting \"%s\" to level %d startnode %d\n", __func__, n->nlabel, n->y, n->startnode);
	}

	if (span > g->maxlevel) {
		g->maxlevel = span;
	}

	/* follow outgoing edges */
	el = n->outgoing_e;
	while (el) {
		edge = el->edge;
		target = edge->to_node;
		/* dot constraint */
		if (edge->constraint) {

			span++;
			set_level2(g, target, span, startnode);
			span = n->y;
		} else {
			/* if dot constraint is false, edge is not included in rank level setting */
			target->y = i;
			target->done = 1;
		}

		el = el->next;
	}
	n->grey = 0;
	return;
}

/* set rel. y level of nodes */
static void set_level(struct gml_graph *g, struct gml_node *n, int i, int startnode)
{
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *source = NULL;
	struct gml_node *target = NULL;
	if (n == (struct gml_node *)0) {
		/* shouldnothappen */
		return;
	}

	/* n->y is inited to -1 */
	if (n->y >= 0) {
		/* node already done */
		/* update maxlevel if needed */
		if (i > g->maxlevel) {
			g->maxlevel = i;
		}
		n->y = i;
	}

	if (n->done) {
		return;
	}

	/* update maxlevel if needed */
	if (i > g->maxlevel) {
		g->maxlevel = i;
	}

	if (n->y <= i) {

		n->grey = 1;
		n->y = i;	/* set y level of node */
		if (yydebug || 0) {
			printf("%s(): node %d \"%s\" set at level %d maxlevel is %d\n", __func__, n->nr, n->name, n->y,
			       g->maxlevel);
		}

		/* node belongs to part of graph with this startnumber */
		n->startnode = startnode;
		source = n;
		/* follow outgoing edges */
		el = source->outgoing_e;
		while (el) {
			edge = el->edge;
			target = edge->to_node;
			/* dot constraint */
			if (edge->constraint) {
				set_level(g, target, (i + 1), startnode);
			} else {
				/* if dot constraint is false, edge is not included in rank level setting */
				target->y = i;
			}
			el = el->next;
		}
		n->grey = 0;
		n->done = 1;
	}

	return;
}

/* add node as single node */
static void add_singlenode(struct gml_graph *g, struct gml_node *node)
{
	struct gml_nlist *lnll = NULL;
	lnll = (struct gml_nlist *)dp_calloc(1, sizeof(struct gml_nlist));
	lnll->node = node;
	if (g->singlenodelist == NULL) {
		g->singlenodelist = lnll;
		g->singlenodelisttail = lnll;
	} else {
		g->singlenodelisttail->next = lnll;
		g->singlenodelisttail = lnll;
	}

	return;
}

/* add node as node with a self-edge */
static void add_selfedgenode(struct gml_graph *g, struct gml_node *node)
{
	struct gml_nlist *lnll = NULL;
	lnll = (struct gml_nlist *)dp_calloc(1, sizeof(struct gml_nlist));
	lnll->node = node;
	if (g->selfedgesnodelist == NULL) {
		g->selfedgesnodelist = lnll;
		g->selfedgesnodelisttail = lnll;
	} else {
		g->selfedgesnodelisttail->next = lnll;
		g->selfedgesnodelisttail = lnll;
	}

	return;
}

/* gcc data uses "n" and "s" compass points
 * in edge to force nodes below of each other.
 * this is not automatic layout but semi-automatic.
 * implement this limitation here.
 */
static void nscompass(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	char *dir = NULL;
	int changed = 0;
	/* the gcc data n/s compass points are for a dfs only layout */
	if (ranktype != 1) {
		if (0) {	/* temp test */
			return;
		}
	}

	el = g->edgelist;
	while (el) {
		edge = el->edge;
		sn = edge->from_node;
		tn = edge->to_node;
		if (yydebug) {
			if (tn->y >= sn->y) {
				dir = "downward";
			} else {
				dir = "upward";
			}
			printf("%s(): rev=%d `%s'->`%s' level %d->%d %s\n", __func__,
			       edge->reversed, sn->nlabel, tn->nlabel, sn->y, tn->y, dir);
		}

		/* only if any compass points */
		if (edge->fcompass && edge->tcompass) {
			if ((strcmp(edge->fcompass, "s") == 0)
			    && (strcmp(edge->tcompass, "n") == 0)) {
				if (yydebug || 0) {
					printf("%s(); compass points s and n in edge level %d->%d %s->%s\n", __func__, sn->y, tn->y,
					       sn->name, tn->name);
				}
				/* */
				if (edge->reversed == 0) {
					if (tn->y < (sn->y + 1)) {
						tn->y = (sn->y + 1);
						changed++;
					}
					if (tn->y > g->maxlevel) {
						g->maxlevel = tn->y;
					}
				} else {
					/* reversed edge */
					/* XXX tofix todo needed? */
					if (sn->y < (tn->y + 1)) {
						sn->y = (tn->y + 1);
						changed++;
					}
					if (sn->y > g->maxlevel) {
						g->maxlevel = sn->y;
					}
				}
				/* */
			}
		}
		el = el->next;
	}
	if (changed) {
		printf("%s(): changed nodes in %d edges\n", __func__, changed);
	}
	return;
}

/* set rel. y level of all nodes */
void ylevels(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	int start2 = 0;
	int i = 0;
	int special = 0;
	int nnodes = 0;
	if (g->nodelist == NULL) {
		/* nothing to do */
		return;
	}

	/* no single nodes in the graph */
	g->nsinglenodes = 0;
	/* set all y levels to undefined */
	lnll = g->nodelist;
	nnodes = 0;
	while (lnll) {
		nnodes++;
		/* y = -1, means undefined */
		lnll->node->y = -1;
		lnll->node->done = 0;
		lnll->node->grey = 0;
		lnll->node->startnode = -1;
		if (incrlayout) {
			/* in cluster the single nodes must be kept in cluster */
			if (g->type != SG_CLUSTER) {
				/* check for single nodes and mark them */
				if (lnll->node->outgoing_e == NULL && lnll->node->incoming_e == NULL) {
					/* set single nodes at fixed level 0 */
					lnll->node->y = 0;
					lnll->node->done = 1;
					/* node belongs to part of graph with this startnode */
					lnll->node->startnode = 0;
					g->nsinglenodes = (g->nsinglenodes + 1);
					add_singlenode(g, lnll->node);
					/* XXX tofix todo should be in maingraph->list? */
				}
			} else {
				/* this is a cluster graph */
			}
		} else {
			/* no incr. layout done */
			/* check for single nodes and mark them */
			if (lnll->node->outgoing_e == NULL && lnll->node->incoming_e == NULL) {
				/* set single nodes at fixed level 0 */
				lnll->node->y = 0;
				lnll->node->done = 1;
				/* node belongs to part of graph with this startnode */
				lnll->node->startnode = 0;
				g->nsinglenodes = (g->nsinglenodes + 1);
				add_singlenode(g, lnll->node);
			}
		}
		lnll = lnll->next;
	}

	if (g->nsinglenodes) {
		printf("%s(): there are %d single nodes in the graph\n", __func__, g->nsinglenodes);
		/* start the drawing of other nodes at level 1 */
		if (incrlayout) {
			/* in cluster the single nodes must be kept in cluster */
			if (g->type != SG_CLUSTER) {
				start2 = 1;
			} else {
				/* cluster: start at level 0 always */
				start2 = 0;
			}
		} else {
			/* no incr. layout */
			start2 = 1;
		}
	} else {
		start2 = 0;
	}

	if (ranktype == 3) {
		printf("%s(): doing topological placement\n", __func__);
	}

	if (ranktype == 2) {
		printf("%s(): doing bfs placement\n", __func__);
	}

	/* number of start nodes in the graph */
	g->nstartnodes = 0;
	/* where the actual drawing starts at y-level */
	g->startnodeslevel = start2;
	span = start2;
	special = 0;
	/* dfs */
	lnll = g->nodelist;
	while (lnll) {
		if (lnll->node->y == -1) {
			/* select start nodes */
			if (lnll->node->indegree == 0 && lnll->node->outdegree != 0) {
				g->nstartnodes++;
				if (ranktype == 3) {
					/* topological sort to set y level */
					span = start2;
					set_tlevel0(g, lnll->node, start2, lnll->node->nr);
				} else if (ranktype == 2) {
					/* bfs */
					span = start2;
					set_bfslevel(g, lnll->node, start2, lnll->node->nr);
				} else {
					/* dfs type must be level2() */
					if (0) {
						set_level(g, lnll->node, start2, lnll->node->nr);
					} else {
						if (yydebug || 0) {
							printf("%s(): startnode %d\n", __func__, lnll->node->nr);
						}
						set_level2(g, lnll->node, start2, lnll->node->nr);
					}
				}
			}
		}
		lnll = lnll->next;
	}

	/* */
	if ((g->nstartnodes > 1) || 1) {
		printf("%s(): there are %d start nodes\n", __func__, g->nstartnodes);
	}

	/* if multiple startnodes, switch to drawing positioning mode
	 * changed: always start with pos2, and pos1 can be done using pos button.
	 * if (g->nstartnodes > 1)
	 * {
	 * postype = 2;
	 * }
	 * else
	 * {
	 * postype = 1;
	 * }
	 * new: always use pos mode 2
	 */
	if (0) {		/* temp test */
		postype = 2;
	}
	/* check that all nodes have y position now and update maxlevel */
	g->maxlevel = 0;
	lnll = g->nodelist;
	while (lnll) {
		if (yydebug || 0) {
			printf("%s(): node \"%s\" is at level %d\n", __func__, lnll->node->nlabel, lnll->node->y);
		}
		if (lnll->node->y == -1) {
			if (0) {	/* temp test */
				postype = 1;
			}
			/* doeshappen */
			if (yydebug || 1) {
				printf
				    ("%s(): node \"%s\" updating level (-1) indegree=%d outdegree=%d\n",
				     __func__, lnll->node->name, lnll->node->indegree, lnll->node->outdegree);
			}
			if (1) {
				set_level(g, lnll->node, start2, lnll->node->nr);
			} else {
				set_level2(g, lnll->node, start2, lnll->node->nr);
			}
		}
		/* make sure maxlevel is updated to correct value */
		if (lnll->node->y > g->maxlevel) {
			g->maxlevel = lnll->node->y;
		}
		lnll = lnll->next;
	}

	/* gcc data uses "n" and "s" compass points
	 * in edge to force nodes below of each other.
	 * this is not automatic layout but semi-automatic.
	 * implement this limitation here.
	 */
	nscompass(g);
	/* graph can have zero startnodes.
	 * set first node as startnode.
	 * but a cycle is broken and there there is always a start node
	 */
	if (g->nstartnodes == 0) {
		/* shouldnothappen */
		printf("%s(): no startnodes in `%s' of %d nodes\n", __func__, g->graphname, nnodes);
		g->nstartnodes++;
		if (g->nodelist) {
			set_level(g, g->nodelist->node, start2, g->nodelist->node->nr);
		}
		special = 1;
	}

	/* fill the table with startnodes */
	g->startnodes = dp_calloc(1, g->nstartnodes * sizeof(int));
	if (g->startnodes == NULL) {
		return;
	}

	/* special case if there were no startnodes */
	if (special) {
		/* set first node as startnode */
		if (g->nodelist) {
			g->startnodes[0] = g->nodelist->node->nr;
		}
	} else {

		/* copy the startnodes numbers in the table */
		i = 0;
		lnll = g->nodelist;
		while (lnll) {
			/* no incoming edges and at least one outgoing edge */
			if ((lnll->node->incoming_e == NULL && lnll->node->outgoing_e != NULL)) {
				/* set node number. this is not the id number in the input. */
				g->startnodes[i] = lnll->node->nr;
				i++;
			}
			lnll = lnll->next;
		}

		if (i != g->nstartnodes) {
			printf("%s(): found %d startnodes, should be %d shouldnothappen\n", __func__, i, g->nstartnodes);
		}
	}

	/* option in the gui to mirror in y the relative node positions. this causes trouble in pos2, so postype=1 is forced. */
	if (option_mirrory) {
		/* maxlevel is updated above */
		lnll = g->nodelist;
		while (lnll) {
			lnll->node->y = (g->maxlevel - lnll->node->y);
			lnll = lnll->next;
		}
	}

	fflush(stdout);

	return;
}

/* dfs check again and reverse if needed */
void edgelen(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	struct gml_node *tmpnode = NULL;
	int changed = 0;
	el = g->edgelist;
	while (el) {
		edge = el->edge;
		sn = edge->from_node;
		tn = edge->to_node;
		if ((tn->y - sn->y) < 0) {
			if (yydebug || 0) {
				printf("%s(): before splitting, edgelen < 0 from %d->%d level %d->%d\n", __func__, sn->id, tn->id,
				       sn->y, tn->y);
			}
			changed++;
			tmpnode = tn;
			el->edge->to_node = el->edge->from_node;
			el->edge->from_node = tmpnode;
		}

		el = el->next;
	}

	if (changed) {
		printf("%s(): changed %d edges\n", __func__, changed);
		/* refresh st lists */
		clear_stlist_all(g);
		make_stlist(g);
	}

	return;
}

/* undo reversed edges and refresh node edgelists */
static void unrev(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_node *tmpnode = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	struct gml_edge *edge = NULL;
	int changed = 0;
	el = g->edgelist;
	while (el) {
		edge = el->edge;
		if (el->edge->reversed) {
			changed++;
			sn = edge->from_node;
			tn = edge->to_node;
			/* swap */
			tmpnode = tn;
			el->edge->to_node = sn;
			el->edge->from_node = tmpnode;
			el->edge->reversed = 0;
		}

		el = el->next;
	}

	/* rebuild the in/out edges lists at the nodes in the modified graph */
	g->maxlevel = 0;
	if (changed) {
		/* refresh st lists */
		clear_stlist_all(g);
		make_stlist(g);
	}
	return;
}

/* follow edge */
static int shorteredges_r(struct gml_node *n)
{
	int ny = 0;
	if ((n->indegree == 1) && (n->outdegree == 1)) {
		ny = shorteredges_r(n->outgoing_e->edge->to_node);
		n->y = ny - 1;
	}

	return (n->y);
}

/* try to find shorter edges */
void shorteredges(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_elist *ine = NULL;
	struct gml_elist *oute = NULL;
	struct gml_edge *eg = NULL;
	struct gml_node *inn = NULL;
	struct gml_edge *etop = NULL;
	struct gml_edge *ebot = NULL;
	struct gml_node *ntop = NULL;
	struct gml_node *nbot = NULL;
	int canmove = 0;
	int ny = 0;
	/* undo reversed edges and refresh node edgelists */
	unrev(g);
	/* move in between nodes at halfway */
	lnll = g->nodelist;
	while (lnll) {
		if ((lnll->node->indegree == 1) && (lnll->node->outdegree == 1)) {
			oute = lnll->node->outgoing_e;
			ine = lnll->node->incoming_e;
			etop = ine->edge;
			ebot = oute->edge;
			ntop = etop->from_node;
			nbot = ebot->to_node;
			if (yydebug) {
				printf("%s(): at node %s between %s and %s\n", __func__, lnll->node->nlabel, ntop->nlabel,
				       nbot->nlabel);
			}
			if ((abs(ntop->y - lnll->node->y) > 1)
			    || (abs(nbot->y - lnll->node->y) > 1)) {
				/* put node at the middle, does not depend on edge direction up/down */
				lnll->node->y = ((ntop->y + nbot->y) / 2);
			}
		}
		lnll = lnll->next;
	}

	return;
	/* todo fixme XXX next may cause fail */
	/* move top level nodes */
	lnll = g->nodelist;
	if (1) {

		while (lnll) {
			/* sometimes starter nodes can be moved close to to-node */
			if ((lnll->node->indegree == 0) && (lnll->node->outdegree != 0)) {
				ny = shorteredges_r(lnll->node->outgoing_e->edge->to_node);
				lnll->node->y = ny - 1;
			}
			lnll = lnll->next;
		}

	} else {

		while (lnll) {
			/* sometimes starter nodes can be moved close to to-node */
			if ((lnll->node->indegree == 0) && (lnll->node->outdegree != 0)) {
				/* check if node can be moved */
				canmove = 1;
				oute = lnll->node->outgoing_e;
				while (oute) {
					ebot = oute->edge;
					nbot = ebot->to_node;
					if (abs(nbot->y - lnll->node->y) == 1) {
						canmove = 0;
						break;
					}
					oute = oute->next;
				}
				if (0) {
					printf("%s(): can move is %d\n", __func__, canmove);
				}
				if (canmove) {
					oute = lnll->node->outgoing_e;
					ebot = oute->edge;
					nbot = ebot->to_node;
					/* moved closer to the target */
					lnll->node->y = nbot->y - 1;
					while (oute) {
						ebot = oute->edge;
						nbot = ebot->to_node;
						if (nbot->y - 1 < lnll->node->y) {
							/* moved closer to the target */
							lnll->node->y = nbot->y - 1;
						}
						oute = oute->next;
					}
				}
			}
			lnll = lnll->next;
		}

	}

	/* scan tail nodes, */
	lnll = g->nodelist;
	while (lnll) {
		if ((lnll->node->indegree != 0) && (lnll->node->outdegree == 0)) {

			if (yydebug) {
				printf("%s(): hit at node %s indegree=%d outdegree=0\n", __func__, lnll->node->nlabel,
				       lnll->node->indegree);
			}

			/* target list, incoming edges */
			ine = lnll->node->incoming_e;
			while (ine) {
				eg = ine->edge;
				inn = eg->from_node;
				if (yydebug) {
					printf("%s(): at edge %s->%s rev=%d delta=%d\n", __func__,
					       eg->from_node->nlabel, eg->to_node->nlabel, eg->reversed, (inn->y - lnll->node->y));
				}

				/* check if move is needed */

				if ((inn->y - lnll->node->y) > 0) {
					if (yydebug) {
						printf("%s(): moving node %s from %d to %d\n", __func__, lnll->node->nlabel,
						       lnll->node->y, inn->y + 1);
					}
					lnll->node->y = inn->y + 1;
					if ((inn->y + 1) > g->maxlevel) {
						g->maxlevel = inn->y + 1;
					}
				}

				ine = ine->next;
			}
		}
		lnll = lnll->next;
	}

	return;
}

/* doublespace the vertical levels */
void doublespacey(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	int miniy = 0;
	/* same edges now will have different dummy nodes resulting in 2 lines */
	g->maxlevel = 0;
	/* correct for start level */
	if (g->startnodeslevel > 0) {
		miniy = 1;
	}
	/* at the odd levels the edge labels will be placed. */
	lnll = g->nodelist;
	while (lnll) {
		lnll->node->y = (2 * lnll->node->y);
		/* where the actual drawing starts at y-level */
		if (lnll->node->y > g->startnodeslevel) {
			lnll->node->y = lnll->node->y - miniy;
		}
		if (lnll->node->y > g->maxlevel) {
			g->maxlevel = lnll->node->y;
		}

		lnll = lnll->next;
	}

	return;
}

/* split longer edges */
void splitedges(struct gml_graph *g)
{
	struct gml_elist *el = NULL;
	struct gml_elist *elnext = NULL;
	struct gml_edge *edge = NULL;
	struct gml_node *sn = NULL;
	struct gml_node *tn = NULL;
	struct gml_node *nlnode = NULL;
	int edgelen = 0;
	int prevnodeid = 0;
	int newid = 0;
	int i = 0;
	int sny = 0;
	char rev = 0;
	int ecolor = 0;
	int style = 0;
	char *fc = NULL;
	char *tc = NULL;
	char constraint = 0;
	el = g->edgelist;
	while (el) {
		elnext = el->next;
		edge = el->edge;
		sn = edge->from_node;	/* from-node */
		tn = edge->to_node;	/* to-node */
		rev = edge->reversed;	/* edge attr. to copy when splitting edge */
		ecolor = edge->ecolor;	/* color of edge line */
		style = edge->style;
		fc = edge->fcompass;
		tc = edge->tcompass;
		constraint = edge->constraint;
		edgelen = (tn->y - sn->y);
		/* horizontal edge */
		if (edgelen == 0) {
			/* horizontal edge has original endpoints, used in drawing edges */
			edge->hedge = 1;
			g->nhedges++;	/* number of horizontal edges */
			/* mark that nodes have a hor. edge */
			sn->hashedge = 1;
			tn->hashedge = 1;
			if (0) {
				printf
				    ("%s(): horizontal edge %d->%d \"%s\"->\"%s\" rev=%d length %d pos=%d -> pos=%d\n",
				     __func__, sn->nr, tn->nr, sn->nlabel, tn->nlabel, rev, edgelen, sn->x, tn->x);
				fflush(stdout);
			}

		} else if (edgelen > 1) {
			if (yydebug) {
				printf("%s(): splitting edge %d->%d length %d\n", __func__, sn->nr, tn->nr, edgelen);
				fflush(stdout);
			}

			prevnodeid = sn->nr;
			sny = sn->y;
			for (i = 1; i < edgelen; i++) {
				/* dummy node numbers start at first free node nr number */
				maingraph->nodenum++;
				newid = maingraph->nodenum;
				add_new_dummynode(g, newid);
				nlnode = uniqnode2(NULL, newid);
				nlnode->dummy = 1;	/* this is a dummy node */
				nlnode->elabel = 0;	/* not a edgelabel */
				nlnode->y = (sny + i);
				nlnode->startnode = sn->startnode;
				add_new_dummyedge(g, el->edge->rootedon, prevnodeid, newid, rev, ecolor, style, fc, tc, constraint);
				prevnodeid = newid;
			}

			add_new_dummyedge(g, el->edge->rootedon, prevnodeid, tn->nr, rev, ecolor, style, fc, tc, constraint);
			del_edge(g, el);
		} else if (edgelen == 1) {
			/* edge len is 1 oke. */
		} else {
			/* shouldnothappen */
			printf("%s(): edgelen<0 is %d shouldnothappen\n", __func__, edgelen);
			fflush(stdout);
		}

		el = elnext;
	}

	return;
}

/* create level node count data */
void nodecounts(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	/* refresh st lists */
	clear_stlist_all(g);
	make_stlist(g);
	/* table with number of nodes per level */
	g->nnodes_of_level = dp_calloc((g->maxlevel + 1), sizeof(int));
	if (g->nnodes_of_level == NULL) {
		return;
	}

	/* determine widest level and how many nodes it has */
	g->widestlevel = 0;
	g->widestnnodes = 0;
	lnll = g->nodelist;
	while (lnll) {
		/* rely used for sugi */
		lnll->node->rely = lnll->node->y;
		g->nnodes_of_level[lnll->node->y] = g->nnodes_of_level[lnll->node->y] + 1;
		/* x used for sugi, offset 1...n */
		lnll->node->relx = g->nnodes_of_level[lnll->node->y];
		if (g->nnodes_of_level[lnll->node->y] >= g->widestnnodes) {
			g->widestnnodes = g->nnodes_of_level[lnll->node->y];
			g->widestlevel = lnll->node->y;
		}

		lnll = lnll->next;
	}

	return;
}

/* this is called from the parsercode.
 * the parser has already done some checks.
 */
void
add_new_edge(struct gml_graph *g, struct gml_graph *ro, int foundsource,
	     int foundtarget, char *elabel, int ecolor, int style, char *fcompass, char *tcompass, int constraint, int ishtml)
{
	struct gml_node *snode = NULL;
	struct gml_node *tnode = NULL;
	struct gml_edge *edge = NULL;
	struct gml_elist *el = NULL;
	char *elabel2 = NULL;
	char *se = NULL;

	/* get node struct of sourcenode */
	snode = uniqnode(NULL, foundsource);
	tnode = uniqnode(NULL, foundtarget);

	if (snode == NULL) {
		printf
		    ("%s(): source node in edge from %d to %d not found and edge is skipped\n", __func__, foundsource, foundtarget);
	}

	if (tnode == NULL) {
		printf
		    ("%s(): target node in edge from %d to %d not found and edge is skipped\n", __func__, foundsource, foundtarget);
	}

	if ((snode == NULL) || (tnode == NULL)) {
		return;
	}

	if (snode == tnode) {
		se = " and this is a selfedge";
	} else {
		se = "";
	}

	if (yydebug || 0) {
		printf("%s(): edge from \"%s\" to \"%s\" has edgelabel \"%s\"%s\n", __func__, snode->name, tnode->name, elabel, se);
	}

	/* update number of edgelabels in the graph
	 * todo edgelabels in self-edges are also counted this way
	 * todo edgelabels in self edges
	 */
	if (elabel) {

		if (strlen(elabel)) {
			g->nedgelabels++;
			elabel2 = elabel;
		} else {
			/* "" is set as no-edgelabel */
			elabel2 = NULL;
		}
	} else {
		elabel2 = NULL;
	}

	/* at self edge incr. it at the node */
	if (snode == tnode) {
		if (yydebug || 0) {
			printf("%s(): selfedge in add edge secolor=%x\n", __func__, ecolor);
		}
		/* a self-edge, increment count */
		snode->nselfedges++;
		/* set color of self-edge */
		snode->secolor = ecolor;
		tnode->secolor = ecolor;
		g->nselfedges++;
		/* in prep(): add node in list with self-edge nodes
		 * add_selfedgenode(g, snode);
		 */
		g->nedges++;
		maingraph->tnedges++;
		/* self edges are not so good supported yet, todo */
		if (elabel2) {
			printf("%s(): at edge with node \"%s\" self edges with labels not supported\n", __func__, snode->name);
		}
		return;
	}

	/* a new edge */
	edge = dp_calloc(1, sizeof(struct gml_edge));

	/* edge number start at 1 */
	g->edgenum++;
	edge->nr = g->edgenum;
	edge->rootedon = ro;
	edge->from_node = snode;
	edge->to_node = tnode;
	edge->elabel = uniqstr(elabel2);	/* "" is set as (char *)0 */
	edge->ishtml = ishtml;	/* set if elabel is html string */
	edge->ecolor = ecolor;
	edge->style = style;
	edge->fcompass = fcompass;
	edge->tcompass = tcompass;
	edge->constraint = constraint;

	/* */
	el = dp_calloc(1, sizeof(struct gml_elist));

	el->edge = edge;

	if (g->rawedgelist == NULL) {
		g->rawedgelist = el;
		g->rawedgelisttail = el;
	} else {
		g->rawedgelisttail->next = el;
		g->rawedgelisttail = el;
	}

	/* number of edges in this subgraph */
	g->nedges++;

	/* total number of edges */
	maingraph->tnedges++;

	return;
}

/* edge to dummy node is in edgelist but not in rawedgelist */
void
add_new_dummyedge(struct gml_graph *g, struct gml_graph *ro, int foundsource,
		  int foundtarget, int reversed, int ecolor, int style, char *fcompass, char *tcompass, int constraint)
{
	struct gml_node *snode = NULL;
	struct gml_node *tnode = NULL;
	struct gml_edge *edge = NULL;
	struct gml_elist *el = NULL;
	snode = uniqnode2(NULL, foundsource);
	if (snode == NULL) {
		printf("%s(): sourcenode in %d->%d not found and edge is skipped\n", __func__, foundsource, foundtarget);
		return;
	}

	tnode = uniqnode2(NULL, foundtarget);
	if (tnode == NULL) {
		printf("%s(): targetnode in %d->%d not found and edge is skipped\n", __func__, foundsource, foundtarget);
		return;
	}

	edge = dp_calloc(1, sizeof(struct gml_edge));
	if (edge == NULL) {
		return;
	}
	g->edgenum++;
	edge->nr = g->edgenum;
	edge->rootedon = ro;
	edge->from_node = snode;	/* from-node */
	edge->to_node = tnode;	/* to-node */
	edge->reversed = reversed;	/* edge attr. edge-is-reversed */
	edge->ecolor = ecolor;	/* r/g/b of edge line */
	edge->style = style;
	edge->fcompass = fcompass;
	edge->tcompass = tcompass;
	edge->constraint = constraint;
	/* edge is a inner edge if both nodes are dummy nodes */
	if (edge->from_node->dummy && edge->to_node->dummy) {
		edge->inner = 1;
	} else {
		edge->inner = 0;
	}
	el = dp_calloc(1, sizeof(struct gml_elist));
	if (el == NULL) {
		return;
	}

	el->edge = edge;
	if (g->edgelist == NULL) {
		g->edgelist = el;
		g->edgelisttail = el;
	} else {
		g->edgelisttail->next = el;
		g->edgelisttail = el;
	}

	return;
}

/* this is called from the parser code to add a node
 * the parsercode has already done some checks.
 */
void
add_new_node(struct gml_graph *g, struct gml_graph *ro, int nr, int foundid, char *nodename,
	     char *nodelabel, int ncolor, int nbcolor, struct gml_rl *rlabel, struct gml_hl *hlabel, int fontcolor, int ishtml)
{
	struct gml_node *node = NULL;
	struct gml_nlist *lnll = NULL;
	char nlbuf[16];
	char *lb = NULL;
	/* check if node exists as gml node with a id but not for dot/vg parsers then foundid is -1 */
	if (foundid >= 0) {
		node = uniqnodeid(NULL, foundid);
		if (node) {
			if (nodelabel) {
				lb = nodelabel;
			} else {
				lb = "";
			}
			printf("%s(): node id %d with label \"%s\"is already defined and this one skipped\n", __func__, foundid,
			       lb);
			if (node->nlabel) {
				lb = node->nlabel;
			} else {
				lb = "";
			}
			printf("%s(): earlier defined as node %d with label \"%s\"\n", __func__, node->id, lb);
			return;
		}
	}

	node = uniqnode(NULL, nr);
	/* shouldnothappen */
	if (node) {
		if (nodelabel) {
			lb = nodelabel;
		} else {
			lb = "";
		}
		printf("%s(): node nr %d with label \"%s\"is already defined and this one skipped\n", __func__, nr, lb);
		if (node->nlabel) {
			lb = node->nlabel;
		} else {
			lb = "";
		}
		printf("%s(): earlier defined as node %d with label \"%s\"\n", __func__, node->nr, lb);
		return;
	}

	/* label is node number or specified label */
	if (nodelabel == NULL) {
		memset(nlbuf, 0, 16);
		/* no specified node label, so use the id of the node. */
		snprintf(nlbuf, (16 - 1), "%d", foundid);
	}

	node = dp_calloc(1, sizeof(struct gml_node));

	node->rootedon = ro;	/* graph where node is located */
	node->nr = nr;		/* uniq node number */
	node->id = foundid;	/* id of node */
	node->ncolor = ncolor;	/* fill color r/g/b */
	node->nbcolor = nbcolor;	/* border color r/g/b */
	node->fontcolor = fontcolor;
	node->secolor = 0;	/* self edge color */
	node->name = uniqstr(nodename);

	if (nodelabel) {
		/* label is the specified label */
		node->nlabel = uniqstr(nodelabel);
	} else {
		/* label is the numeric string of the node id. */
		node->nlabel = uniqstr(nlbuf);
	}
	/* set if a html <> label */
	node->ishtml = ishtml;

	if ((ishtml != 0) && (hlabel == NULL)) {
		/* message shouldnothappen */
		printf("%s(): missing html-label data in node \"%s\"\n", __func__, node->name);
		/* turn html label mode off. */
		node->ishtml = 0;
	}

	if (hlabel) {
		node->hlabel = hlabel;	/* html label data */
	}
	if (rlabel) {
		node->rlabel = rlabel;	/* record label data */
	}
	if (hlabel && rlabel) {
		/* shouldnothappen */
		printf("%s(): node `%s' has html and record label\n", __func__, nodename);
		node->hlabel = NULL;
		node->rlabel = NULL;
		node->ishtml = 0;
	}

	uniqnode_add(NULL, node);

	lnll = dp_calloc(1, sizeof(struct gml_nlist));

	if (lnll == NULL) {
		dp_free(node);
		return;
	}

	lnll->node = node;

	if (g->rawnodelist == NULL) {
		g->rawnodelist = lnll;
		g->rawnodelisttail = lnll;
	} else {
		g->rawnodelisttail->next = lnll;
		g->rawnodelisttail = lnll;
	}

	/* number of nodes in this graph */
	g->nnodes++;

	/* number of total nodes in input graph */
	maingraph->tnnodes++;

	return;
}

/* dummy nodes are only in nodelist, not raw nodelist */
void add_new_dummynode(struct gml_graph *g, int foundid)
{
	struct gml_node *node = NULL;
	struct gml_nlist *lnll = NULL;
	if (uniqnode2(NULL, foundid)) {
		printf("%s(): node %d already defined\n", __func__, foundid);
		fflush(stdout);
		return;
	}

	node = dp_calloc(1, sizeof(struct gml_node));
	if (node == NULL) {
		return;
	}

	node->id = foundid;
	node->nr = foundid;
	/*  white background color for edgelabel */
	node->ncolor = 0xffffffff;
	/* dummy nodes are in work list, not raw nodes list */
	uniqnode_add2(NULL, node);
	lnll = dp_calloc(1, sizeof(struct gml_nlist));
	if (lnll == NULL) {
		return;
	}

	lnll->node = node;
	if (g->nodelist == NULL) {
		g->nodelist = lnll;
	} else {
		g->nodelisttail->next = lnll;
	}

	g->nodelisttail = lnll;
	return;
}

/* lists per position */
void make_posnodes(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;
	int maxw = 0;
	int maxrx = 0;
	/* extra check max rel. x pos. */
	lnll = g->nodelist;
	while (lnll) {
		if (lnll->node->absx > maxrx) {
			maxrx = lnll->node->absx;
		}
		lnll = lnll->next;
	}

	/* pos.c has moved node in x dir. */
	if (maxrx > g->widestnnodes) {
		g->widestnnodes = maxrx;
	}

	/* x width at position */
	g->wpos = dp_calloc(1, (g->widestnnodes + 1) * sizeof(int));
	if (g->wpos == NULL) {
		return;
	}

	/* lists with nodes up to down at position */
	g->posnodes = dp_calloc(1, (g->widestnnodes + 1) * sizeof(struct gml_nlist *));
	if (g->posnodes == NULL) {
		return;
	}

	/* create for every postion the list of nodes at that position */
	lnll = g->nodelist;
	while (lnll) {
		i = lnll->node->absx;
		newl = dp_calloc(1, sizeof(struct gml_nlist));
		if (newl == NULL) {
			return;
		}

		newl->node = lnll->node;
		if (g->posnodes[i] == NULL) {
			g->posnodes[i] = newl;
			newl->next = NULL;
		} else {
			newl->next = g->posnodes[i];
			g->posnodes[i] = newl;
		}

		lnll = lnll->next;
	}

	/* determine the max width of a element at vertical pos. */
	for (i = 0; i < (g->widestnnodes + 1); i++) {
		maxw = 0;
		/* lists per pos. */
		lnll = g->posnodes[i];
		while (lnll) {
			if (lnll->node->bbx > maxw) {
				maxw = lnll->node->bbx;
			}
			lnll = lnll->next;
		}

		g->wpos[i] = maxw;
		if (0) {
			printf("x-position %d has max xsize %d\n", i, maxw);
		}

	}

	return;
}

/* clear pos. nodes lists */
void clear_posnodes_r(struct gml_graph *g)
{
	int i = 0;
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_posnodes_r(gl->sg);
		gl = gl->next;
	}

	/* width of positions */
	if (g->wpos) {
		dp_free(g->wpos);
		g->wpos = NULL;
	}

	if (g->posnodes) {

		for (i = 0; i < (g->widestnnodes + 1); i++) {
			/* lists per pos. */
			lnll = g->posnodes[i];
			while (lnll) {
				nlnext = lnll->next;
				dp_free(lnll);
				lnll = NULL;
				lnll = nlnext;
			}

			g->posnodes[i] = NULL;
		}

		dp_free(g->posnodes);
	}

	g->posnodes = NULL;
	return;
}

/* lists per level */
void make_levelnodes(struct gml_graph *g)
{
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *newl = NULL;
	int i = 0;
	int maxh = 0;
	g->hpos = dp_calloc(1, (g->maxlevel + 1) * sizeof(int));
	if (g->hpos == NULL) {
		return;
	}

	g->levelnodes = dp_calloc(1, (g->maxlevel + 1) * sizeof(struct gml_nlist *));
	if (g->levelnodes == NULL) {
		return;
	}

	lnll = g->nodelist;
	while (lnll) {
		i = lnll->node->absy;
		newl = dp_calloc(1, sizeof(struct gml_nlist));
		if (newl == NULL) {
			return;
		}

		newl->node = lnll->node;
		if (g->levelnodes[i] == NULL) {
			g->levelnodes[i] = newl;
			newl->next = NULL;
		} else {
			newl->next = g->levelnodes[i];
			g->levelnodes[i] = newl;
		}

		lnll = lnll->next;
	}

	/* determine the max width of a element at vertical pos. */
	for (i = 0; i < (g->maxlevel + 1); i++) {

		maxh = 0;
		/* lists per pos. */
		lnll = g->levelnodes[i];
		while (lnll) {
			if (lnll->node->bby > maxh) {
				maxh = lnll->node->bby;
			}
			lnll = lnll->next;
		}

		g->hpos[i] = maxh;
	}

	return;
}

/* clear level nodes lists */
void clear_levelnodes_r(struct gml_graph *g)
{
	int i = 0;
	struct gml_nlist *lnll = NULL;
	struct gml_nlist *nlnext = NULL;
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_levelnodes_r(gl->sg);
		gl = gl->next;
	}

	/* width of positions */
	if (g->hpos) {
		dp_free(g->hpos);
		g->hpos = NULL;
	}

	if (g->levelnodes) {

		for (i = 0; i < (g->maxlevel + 1); i++) {
			/* lists per pos. */
			lnll = g->levelnodes[i];
			while (lnll) {
				nlnext = lnll->next;
				dp_free(lnll);
				lnll = NULL;
				lnll = nlnext;
			}

			g->levelnodes[i] = NULL;
		}

		dp_free(g->levelnodes);
	}

	g->levelnodes = NULL;
	return;
}

/* clear table of startnodes */
void clear_startnodes_r(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_startnodes_r(gl->sg);
		gl = gl->next;
	}

	if (g->startnodes) {
		dp_free(g->startnodes);
		g->startnodes = NULL;
	}

	g->nstartnodes = 0;
	return;
}

/* clear number of nodes at level */
void clear_nnl_r(struct gml_graph *g)
{
	struct gml_glist *gl = NULL;
	if (g == NULL) {
		return;
	}

	gl = g->subglist;
	while (gl) {
		clear_nnl_r(gl->sg);
		gl = gl->next;
	}

	if (g->nnodes_of_level) {
		dp_free(g->nnodes_of_level);
	}

	g->nnodes_of_level = NULL;
	return;
}

/* clear subgraphs and optional summary node */
void clear_sg(struct gml_graph *sg)
{
	struct gml_glist *eg = NULL;
	struct gml_glist *egnext = NULL;
	if (sg == NULL) {
		return;
	}
	eg = sg->subglist;
	while (eg) {
		egnext = eg->next;
		/* recurse into current subgraph */
		clear_sg(eg->sg);
		if (eg->sg) {
			/* free optional summary node */
			/* free subgraph */
			dp_free(eg->sg);
			eg->sg = NULL;
		}
		dp_free(eg);
		eg = NULL;
		eg = egnext;
	}

	return;
}

/* convert large number to easier human string */
static const char *humansized(int bytes)
{
	static char output[200];
	char *suffix[] = { "", "K", "M", "G", "T" };
	char length = sizeof(suffix) / sizeof(suffix[0]);
	int i = 0;
	double dblbytes = bytes;
	if (dblbytes > 1000) {
		for (i = 0; (bytes / 1000) > 0 && i < length - 1; i++, bytes /= 1000)
			dblbytes = bytes / 1000.0;
	}

	memset(output, 0, 200);
	snprintf(output, (200 - 1), "%.01lf %s", dblbytes, suffix[i]);
	return output;
}

/* dfs the outgoing edges at level i */
static void longestpath_r(struct gml_graph *g, struct gml_node *n, int i)
{
	struct gml_elist *el = NULL;
	if (i > g->maxlevel) {
		g->maxlevel = i;
	}

	if (n->done) {
		return;
	}

	n->done = 1;
	el = n->outgoing_e;
	while (el) {
		if (el->edge->to_node->done == 0) {
			longestpath_r(g, el->edge->to_node, (i + 1));
		}
		el = el->next;
	}

	return;
}

/* longest path algorithm :
 * this is a dfs counting how many levels are used starting at a start node.
 * the sum of all can be used as one of the graph complexity metrics.
 * the barycenter has also graph metrics.
 */
void longestpath(struct gml_graph *g)
{
	struct gml_node *mn = NULL;
	struct gml_nlist *nl = NULL;
	int n = 0;
	int maxn = 0;
	int fac = 0;
	char *mns = NULL;
	if (g->nodelist == NULL) {
		return;
	}

	nl = g->nodelist;
	while (nl) {
		nl->node->done = 0;
		nl = nl->next;
	}

	mn = NULL;
	maxn = 0;
	fac = 1;
	nl = g->nodelist;
	while (nl) {
		/* start at startnodes */
		if (nl->node->indegree == 0 && nl->node->outdegree != 0) {
			g->maxlevel = 0;
			longestpath_r(g, nl->node, 0);
			n = g->maxlevel;
			if (yydebug || 0) {
				printf("%s(): longest path is %d starting at %s\n", __func__, n, nl->node->name);
			}
			if (n > maxn) {
				maxn = n;
				mn = nl->node;
			}
			fac = (fac + n);
		}
		nl = nl->next;
	}

	nl = g->nodelist;
	while (nl) {
		/* start at other nodes */
		if (nl->node->done == 0) {
			g->maxlevel = 0;
			longestpath_r(g, nl->node, 0);
			n = g->maxlevel;
			if (yydebug || 0) {
				printf("%s(): path is %d starting at %s\n", __func__, n, nl->node->name);
			}
			if (n > maxn) {
				maxn = n;
				mn = nl->node;
			}
			fac = fac + n;
		}
		nl = nl->next;
	}

	if (mn) {
		mns = mn->name;
	} else {
		mns = "unknown";
	}

	if (yydebug || 0) {
		printf("%s(): path is %d edges starting at \"%s\" with metric %d (%s)\n", __func__, maxn, mns, fac,
		       humansized(fac));
	}

	return;
}

/* end */
