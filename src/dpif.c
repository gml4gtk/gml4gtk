
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

/*
 * the dp*.c files are about DotParsing
 * and dpif.c is the interface to the rest of the program
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "dp.h"
#include "dpif.h"
#include "dpmisc.h"
#include "lex.yy.h"
#include "uniqstr.h"
#include "uniqgraph.h"
#include "dot.tab.h"

extern void dp_lex_init(FILE * f, int debugflag);
extern void dp_lex_clear(void);

/* change \n \r \l chars */
static char *dolabel(char *str)
{
	char *ret = NULL;
	char *res = NULL;
	char *p = NULL;
	char *q = NULL;

	if (str == NULL) {
		return (NULL);
	}

	if (strlen(str) == 0) {
		/* fixme XXX todo */
		return (uniqstr("  "));
	}

	res = (char *)calloc(1, (strlen(str) + 1));
	p = str;
	q = res;
	while (*p) {
		if (*p == '\\') {
			if (*(p + 1) == 'n') {
				*q = '\n';
				q++;
				p++;
				p++;
			} else if (*(p + 1) == 'l') {
				*q = '\n';
				q++;
				p++;
				p++;
			} else if (*(p + 1) == 'r') {
				*q = '\n';
				q++;
				p++;
				p++;
			} else {
				*q = *p;
				p++;
				q++;
			}
		} else {
			(*q) = (*p);
			p++;
			q++;
		}
	}

	ret = uniqstr(res);
	free(res);
	return (ret);
}

static int prrlind = 0;
static void prrl(struct gml_rl *info)
{
	int i = 0;
	if (info == NULL) {
		return;
	}
	for (i = 0; i < prrlind; i++) {
		printf("\t");
	}
	printf("hd=%d dir=%d `%s' `%s' nparts=%d\n", info->hd, info->dir, info->port, info->label, info->nparts);
	for (i = 0; i < info->nparts; i++) {
		prrlind++;
		prrl(info->parts[i]);
		prrlind--;
	}

	return;
}

static struct gml_rl *rlcopy(struct dppart *info)
{
	struct gml_rl *nrec = NULL;
	int i = 0;
	if (info == NULL) {
		return (NULL);
	}
	nrec = (struct gml_rl *)calloc(1, sizeof(struct gml_rl));
	nrec->parts = (struct gml_rl **)calloc(1, info->ndpparts * sizeof(struct gml_rl *));
	nrec->hd = info->hd;
	nrec->nparts = info->ndpparts;
	nrec->dir = info->dir;
	nrec->port = uniqstr(info->id);
	nrec->label = uniqstr(info->lp);
	for (i = 0; i < info->ndpparts; i++) {
		nrec->parts[i] = rlcopy(info->parts[i]);
	}
	return (nrec);
}

/* check number of elements actually */
static void rlcheck(struct gml_rl *info)
{
	int i = 0;
	int count = 0;
	count = 0;
	/* null value can happen */
	if (info == NULL) {
		return;
	}
	for (i = 0; i < info->nparts; i++) {
		if (info->parts[i]) {
			count++;
			rlcheck(info->parts[i]);
		}
	}
	info->nparts = count;
	return;
}

/* add subgraphs */
static void sp_addsg_r(struct dpgraph *sg)
{
	struct dpglink *eg = NULL;
	struct dpgraph *cursg = NULL;
	struct gml_graph *rg = NULL;
	struct gml_graph *cg = NULL;
	struct gml_glist *gl = NULL;

	if (sg == NULL) {
		return;
	}

	eg = sg->dpsubg;

	while (eg) {
		cursg = eg->sg;
		/* recurse into current subgraph */
		sp_addsg_r(cursg);
		if (cursg) {
			/* get graph of rooted-on and current subgraph */
			rg = uniqgraph(cursg->rootedon->nr);
			cg = uniqgraph(cursg->nr);
			if (rg && cg) {
				if (yydebug || 0) {
					printf
					    ("%s(): subgraph %d `%s' is rooted on subgraph %d `%s'\n",
					     __func__, cursg->nr, cursg->graphname,
					     cursg->rootedon->nr, cursg->rootedon->graphname);
				}
				gl = calloc(1, sizeof(struct gml_glist));
				if (gl == NULL) {
					return;
				}
				/* set current graph as subgraph */
				gl->sg = cg;
				/* link the list of subgraphs */
				if (rg->subglist == NULL) {
					rg->subglist = gl;
					rg->subglistend = gl;
				} else {
					rg->subglistend->next = gl;
					rg->subglistend = gl;
				}
			} else {
				/* both rg and cg must be found */
				printf("%s(): rg=%p cg=%p shouldnothappen\n", __func__, (void *)rg, (void *)cg);
			}
		}
		eg = eg->next;
	}

	return;
}

/* create subgraphs */
static void sp_crsg_r(struct dpgraph *sg)
{
	struct dpglink *eg = NULL;
	struct dpgraph *cursg = NULL;
	int ttype = 0;
	char *stype = NULL;
	if (sg == NULL) {
		return;
	}
	eg = sg->dpsubg;
	while (eg) {
		cursg = eg->sg;
		/* recurse into current subgraph */
		sp_crsg_r(cursg);
		if (cursg) {
			switch (cursg->type) {
			case DP_SG_ROOT:	/* 0 root graph type */
				stype = "root-subgraph";
				ttype = SG_ROOT;
				break;
			case DP_SG_CO:	/* 1 compound subgraph {} */
				stype = "compound-subgraph";
				ttype = SG_COMPOUND;
				break;
			case DP_SG_NM:	/* 2 named subgrph */
				stype = "named-subgraph";
				ttype = SG_SUBG;
				break;
			case DP_SG_CL:	/* 3 cluster subgraph */
				stype = "cluster-subgraph";
				ttype = SG_CLUSTER;
				break;
			case DP_SG_NN:	/* 4 no name subgraph */
				stype = "unnamed-subgraph";
				ttype = SG_SUBG;
				break;
			default:
				/* shouldnothappen */
				stype = "unknown";
				ttype = 0;
				break;
			}
			if (yydebug || 0) {
				printf("%s(): creating subgraph %d `%s' `%s' type %d %s\n",
				       __func__, cursg->nr, cursg->graphname, cursg->label, ttype, stype);
			}
			create_sg(cursg->nr, uniqstr(cursg->graphname), uniqstr(cursg->label), ttype);
		}
		eg = eg->next;
	}

	return;
}

/* parse dot file, 0 return if oke. */
int dotparse(struct gml_graph *g, FILE * f, char *fname, char *argv0)
{
	struct dpnlink *ns = NULL;
	struct dpnode *node = NULL;
	struct dpelink *es = NULL;
	struct dpedge *edge = NULL;
	struct gml_rl *rl = NULL;
	struct gml_graph *ro = NULL;
	int foundsource = 0;
	int foundtarget = 0;
	int foundid = 0;
	char *nodelabel = NULL;
	char *nodename = NULL;
	int ncolor = 0;
	int nbcolor = 0;
	char *elabel = NULL;
	int econstraint = 0;
	int status = 0;
	int ecolor = 0;
	int style = 0;
	int bgcolor = 0x00ffffff;
	int fontcolor = 0;
	char *fc = NULL;
	char *tc = NULL;
	int nr = 0;

	if (g) {
	}

	if (fname) {
	}

	memset(parsermessage, 0, 256);
	memset(dp_errmsg, 0, 256);
	status = 0;

	if (strcmp(argv0, "gml4gtkd") == 0) {
		/* activate debug output */
		dp_lex_init(f, 1);
	} else {
		dp_lex_init(f, 0);
	}

	/* run bison */
	status = yyparse();
	if (yydebug || 0) {
		printf("%s(): status %d `%s' for dot file `%s'\n", __func__, status, dp_errmsg, fname);
		fflush(stdout);
	}

	if (strlen(dp_errmsg)) {
		strncpy(parsermessage, dp_errmsg, (256 - 1));
		/* set error status */
		status = 1;
		dp_clearall();

		fflush(stdout);
		fflush(stderr);
		return (status);
	}

	/* check data parsed and handle record labels */
	status = dp_datachk();

	if (status) {
		strncpy(parsermessage, dp_errmsg, (256 - 1));
		/* set error status */
		status = 1;
		dp_clearall();

		fflush(stdout);
		fflush(stderr);
		return (status);
	}

	/* create copy of subgraphs */
	sp_crsg_r(dp_groot);

	/* add subgraphs to root graph */
	sp_addsg_r(dp_groot);

	/* list with all nodes */
	ns = dp_anodes;

	while (ns) {
		/* get node data */
		node = ns->n;

		/* graph where node is located */
		ro = uniqgraph(ns->n->root->nr);

		/* node number as in gml graph */
		foundid = node->nr;

		nodename = node->name;
		nodelabel = dolabel(node->label);

		/* node fill color white and bordercolor black */
		ncolor = 0x00ffffff;
		nbcolor = 0;

		/* color for text label */
		if (node->bitflags0.fontcolorset) {
			fontcolor = node->fontcolor;
		}

		if (node->bitflags0.fcolorset || node->bitflags0.colorset) {
			if (node->bitflags1.filled) {
				/* style is filled */
				if (node->bitflags0.fcolorset && node->bitflags0.colorset) {
					ncolor = node->fcolor;
					nbcolor = node->color;
				} else if (node->bitflags0.fcolorset && node->bitflags0.colorset == 0) {
					ncolor = node->fcolor;
					nbcolor = 0;
				} else if (node->bitflags0.fcolorset == 0 && node->bitflags0.colorset) {
					ncolor = node->color;
					nbcolor = node->color;
				} else {
					ncolor = 0x00a9a9a9;
					nbcolor = 0;
				}
			} else {
				/* not style is filled */
				if (node->bitflags0.fcolorset && node->bitflags0.colorset) {
					ncolor = 0x00ffffff;
					nbcolor = node->color;
				} else if (node->bitflags0.fcolorset && node->bitflags0.colorset == 0) {
					ncolor = 0x00ffffff;
					nbcolor = 0;
				} else if (node->bitflags0.fcolorset == 0 && node->bitflags0.colorset) {
					ncolor = 0x00ffffff;
					nbcolor = node->color;
				} else {
					ncolor = 0x00ffffff;
					nbcolor = 0;
				}
			}
		} else {
			/* no colors specified, but style=filled, then grey node */
			if (node->bitflags1.filled) {
				ncolor = 0x00a9a9a9;
				nbcolor = 0;
			}
		}

		if (ns->n->shape == DPSHAPE_RECORD || ns->n->shape == DPSHAPE_MRECORD) {
			if (ns->n->labelinfo) {
				rl = rlcopy(ns->n->labelinfo);
				rlcheck(rl);
			}
		} else {
			rl = NULL;
		}

		/* print record label data */
		if (yydebug) {
			prrlind = 0;
			prrl(rl);
		}

		/* uniq node number starting at 1 */
		maingraph->nodenum++;
		nr = maingraph->nodenum;

		add_new_node(g, ro, nr, foundid, nodename, nodelabel, ncolor, nbcolor, rl, fontcolor);

		ns = ns->next;
	}

	/* all edges */
	es = dp_aedges;

	while (es) {
		edge = es->e;

		/* graph where edge is located */
		ro = uniqgraph(es->e->rootedon->nr);

		if (edge->dir == DP_DIR_BACK) {
			/* backward edge */
			foundsource = edge->tn->nr;
			foundtarget = edge->fn->nr;
		} else {
			/* regular edge */
			foundsource = edge->fn->nr;
			foundtarget = edge->tn->nr;
		}

		if (edge->bitflags0.constraint) {
			econstraint = 1;
		} else {
			econstraint = 0;
		}

		elabel = dolabel(edge->label);
		ecolor = edge->ecolor;
		style = edge->style;
		fc = uniqstr(edge->fcompass);
		tc = uniqstr(edge->tcompass);
		add_new_edge(g, ro, foundsource, foundtarget, elabel, ecolor, style, fc, tc, econstraint);
		es = es->next;
	}

	/* background r/g/b of drawing */
	bgcolor = dp_groot->bgcolor;
	bgcr = (bgcolor & 0x00ff0000) >> 16;
	bgcg = (bgcolor & 0x0000ff00) >> 8;
	bgcb = (bgcolor & 0x000000ff);

	dp_clearall();

	fflush(stdout);
	fflush(stderr);

	return (status);
}

/* end */
