
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

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <zlib.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpus.h"
#include "dpun.h"
#include "dpmisc.h"
#include "dpcolor.h"
#include "lex.yy.h"
#include "dot.tab.h"
#include "dpn.h"
#include "dpe.h"
#include "dpg.h"
#include "dpmem.h"

char dp_errmsg[256];

int dp_cclass = 0;
int dp_sgnr = 0;		/* uniq graph number */

/* all nodes */
struct dpnlink *dp_anodes = NULL;
static struct dpnlink *dp_anodesend = NULL;

/* all edges */
struct dpelink *dp_aedges = NULL;
static struct dpelink *dp_aedgesend = NULL;

/* all edge points */
static struct dpeplink *dp_epl = NULL;
static struct dpeplink *dp_eplend = NULL;

/* all head edge points */
static struct dpeplink *dp_headepl = NULL;
static struct dpeplink *dp_headeplend = NULL;

/* all subgraphs but not rootgraph */
static struct dpglink *dp_asubg = NULL;
static struct dpglink *dp_asubgend = NULL;

/* tmp edges during edge building */
static struct dptelink *dp_tmpe = NULL;
static struct dptelink *dp_tmpeend = NULL;

/* edge nesting */
static int dp_enest = 0;

/* node id number */
static int dp_nodenum = 0;

/* edge numbers */
static int dp_edgenum = 0;

/* splay tree with nested graphs */
static splay_tree dpgraphs = NULL;

/* the root graph */
struct dpgraph *dp_groot = NULL;

/* the current graph */
struct dpgraph *dp_curgraph = NULL;
struct dpnode *dp_curnode = NULL;
struct dpedge *dp_curedge = NULL;

static void dp_nodelink(struct dpnode *node, int mode);
static void dp_eplink(struct dpepoint *epoint);
static void dp_endel_n2n(struct dpepoint *fn, struct dpepoint *tn);
static void dp_endel_n2g(struct dpepoint *fn, struct dpepoint *tn);
static void dp_endel_g2n(struct dpepoint *fn, struct dpepoint *tn);
static void dp_endel_g2g(struct dpepoint *fn, struct dpepoint *tn);
static void dp_clredges(void);

/* return 0 if no errors, >0 at error */
int dp_chkerr(void)
{
	return ((int)strlen(dp_errmsg));
}

/* */
static void dp_pushgraph(struct dpgraph *g)
{
	int ix = 0;
	splay_tree_node spn;

	spn = splay_tree_max(dpgraphs);

	if (spn == NULL) {
		ix = 0;
	} else {
		ix = (int)spn->key;
		ix++;
	}

	splay_tree_insert(dpgraphs, (splay_tree_key) ix, (splay_tree_value) g);

	dp_curgraph = g;

	return;
}

/* */
static struct dpgraph *dp_pullgraph(void)
{
	struct dpgraph *ret = NULL;
	int ix = 0;
	splay_tree_node spn = NULL;

	spn = splay_tree_max(dpgraphs);

	if (spn == NULL) {
		printf("dot %s(): shouldnothappen near line %d\n", __func__, yylineno);
		return (NULL);
	}

	ix = (int)spn->key;

	if ((ix - 1) < 0) {
		/* remove last element ix=0 */
		splay_tree_remove(dpgraphs, (splay_tree_key) ix);
		printf("dot %s(): removed last element near line %d\n", __func__, yylineno);
		return (NULL);
	}

	spn = splay_tree_lookup(dpgraphs, (splay_tree_key) (ix - 1));

	if (spn == NULL) {
		/* shouldnothappen */
		printf("dot %s(): could not find %d element near line %d\n", __func__, (ix - 1), yylineno);
		ret = NULL;
	} else {
		ret = (struct dpgraph *)spn->value;
		splay_tree_remove(dpgraphs, (splay_tree_key) ix);
	}

	dp_curgraph = ret;

	return (ret);
}

/* at start of graph, etype is -- or -> */
void dp_sg(char *etype, char *gname)
{

	memset(dp_errmsg, 0, 256);

	/* node id number */
	dp_nodenum = 0;

	/* edge numbers */
	dp_edgenum = 0;

	/* graph numbers */
	dp_sgnr = 0;

	/* edge nesting */
	dp_enest = 0;

	dpgraphs = splay_tree_new(splay_tree_compare_ints, NULL, NULL);

	/* fresh root graph */
	dp_groot = dp_calloc(1, sizeof(struct dpgraph));

	if (dp_groot == NULL) {
		/* shouldnothappen */
		return;
	}

	/* root graph has uniq number 0 */
	dp_groot->nr = dp_sgnr;
	dp_sgnr++;
	dp_groot->type = DP_SG_ROOT;

	/* set factory defaults */
	dp_graphfdef(dp_groot);

	if (gname == NULL) {
		/* no graphname, make it "" */
		dp_groot->graphname = "";
	} else {
		dp_groot->graphname = gname;
	}

	/* type of edge, -- or -> */
	dp_groot->yylineno = yylineno;
	dp_groot->etype = etype;
	dp_groot->rootedon = NULL;
	dp_groot->tag = DP_TGRAPH;

	/* splay with node/edge/graph parsed settings */
	dp_groot->gattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	dp_groot->nattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	dp_groot->eattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);

	/* node with default settings */
	dp_groot->defnode = dp_calloc(1, sizeof(struct dpnode));

	if (dp_groot->defnode == NULL) {
		/* shouldnothappen */
		dp_free(dp_groot);
		return;
	}

	/* set factory defaults */
	dp_nodefdef(dp_groot->defnode);
	dp_groot->defnode->name = dp_uniqstr("default");
	dp_groot->defnode->label = dp_uniqstr("default");

	/* edge with default settings */
	dp_groot->defedge = dp_calloc(1, sizeof(struct dpedge));

	if (dp_groot->defedge == NULL) {
		/* shouldnothappen */
		dp_free(dp_groot->defnode);
		dp_free(dp_groot);
		return;
	}

	/* set factory defaults */
	dp_edgefdef(dp_groot->defedge);

	/* add root to array of graphs */
	dp_pushgraph(dp_groot);

	dp_cclass = DP_TGRAPH;

	return;
}

/* subgraph with optional name
 * types of subgraphs:
 * #define DP_SG_ROOT 0	* root graph type
 * #define DP_SG_CO 1	* compound subgraph {}
 * #define DP_SG_NM 2	* named subgrph
 * #define DP_SG_CL 3	* cluster subgraph
 * #define DP_SG_NN 4	* no name subgraph
 */
void dp_nsubg(struct dpgraph *sg, char *gname, int type)
{

	if (sg == NULL) {
		/* shouldnothappen */
		return;
	}

	if (gname == NULL) {
		/* type is now DP_SG_CO (compound) or DP_SG_NN (no-name) */
		sg->type = type;
		/* no graphname, make it "" */
		sg->graphname = NULL;
	} else {
		/* name or "" */
		sg->graphname = gname;
		sg->type = DP_SG_NM;
		/*
		 * when subgraph name starts with cluster
		 * it gets special meaning in dot language
		 */
		if (strncmp(sg->graphname, "cluster", 7) == 0) {
			sg->cluster = 1;
			sg->type = DP_SG_CL;
		}

	}

	/* type of edge, -- or -> */
	sg->etype = dp_groot->etype;
	sg->rootedon = dp_curgraph;
	sg->tag = DP_TGRAPH;

	/* splay with node/edge/graph parsed settings */
	sg->gattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	sg->nattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);
	sg->eattr = splay_tree_new(splay_tree_compare_strings, NULL, NULL);

	/* node with default settings */
	sg->defnode = dp_calloc(1, sizeof(struct dpnode));

	if (sg->defnode == NULL) {
		/* shouldnothappen */
		return;
	}

	sg->defnode->name = dp_uniqstr("default");
	sg->defnode->label = dp_uniqstr("default");

	/* set factory defaults */
	dp_nodefdef(sg->defnode);
	dp_nodegdef(dp_curgraph->defnode, sg->defnode);

	/* edge with default settings */
	sg->defedge = dp_calloc(1, sizeof(struct dpedge));

	if (sg->defedge == NULL) {
		/* shouldnothappen */
		dp_free(sg->defnode);
		return;
	}

	/* set factory defaults */
	dp_edgefdef(sg->defedge);
	dp_edgegdef(dp_curgraph->defedge, sg->defedge);

	/* set factory defaults */
	sg->yylineno = yylineno;

	/* factory defaults */
	dp_graphfdef(sg);

	/* get data from rooted on subgraph */

	/* set graph default */
	dp_graphgdef(sg->rootedon, sg);

	return;
}

/* end graph */
void dp_eg(void)
{

	return;
}

void dp_atype_graph(void)
{
	dp_cclass = DP_TGRAPH;
	return;
}

void dp_atype_sgraph(void)
{
	dp_cclass = DP_SGRAPH;
	return;
}

void dp_atype_node(void)
{
	dp_cclass = DP_TNODE;
	return;
}

void dp_atype_edge(void)
{
	dp_cclass = DP_TEDGE;
	return;
}

void dp_atype_graphdef(void)
{
	dp_cclass = DP_TGRAPHDEF;
	return;
}

void dp_atype_nodedef(void)
{
	dp_cclass = DP_TNODEDEF;
	return;
}

void dp_atype_edgedef(void)
{
	dp_cclass = DP_TEDGEDEF;
	return;
}

/* set attribute with last arg set to 1 if r is a <html-label>, otherwise r="a-string" */
void dp_aset(char *l, char *r, int ishtml)
{
	char *dval = "";
	splay_tree_node spn = NULL;
	int htmllabel = 0;

	if (yydebug || 0) {
		printf("%s(): attribute \"%s\" has arg \"%s\" ishtml=%d\n", __func__, l, r, ishtml);
	}

	htmllabel = 0;
	if (ishtml) {
		if (strcmp(l, "label") == 0) {
			htmllabel = 1;
		} else {
			printf("%s(): html-label only supported for label attribute but not for \"%s=%s\" attribute\n", __func__, l,
			       r);
			return;
		}
	}
	dval = r;

	switch (dp_cclass) {
		/* example : "aa"[color=red] */
	case DP_TNODE:
		{
			dp_do_nattr(l, r, ishtml);
		}
		break;
		/* example: node[color=red] */
	case DP_TNODEDEF:
		{
			spn = splay_tree_lookup(dp_curgraph->nattr, (splay_tree_key) l);
			if (spn == NULL) {
				splay_tree_insert(dp_curgraph->nattr, (splay_tree_key) l, (splay_tree_value) dval);
			} else {
				/*
				   if (0)
				   {
				   printf
				   ("dot %s(): attempt to redefine node attribute `%s=%s' with value `%s' near line %d\n",
				   __func__, l, (char *) spn->value, r, yylineno);
				   fflush (stdout);
				   }
				 */
				spn->value = (splay_tree_value) dval;
			}
			dp_do_nattr(l, r, ishtml);
		}
		break;
	case DP_TEDGE:
		{
			if (htmllabel == 0) {
				dp_do_eattr(l, r);
			} else {
				printf("%s(): html-label not supported for edge attributes\n", __func__);
			}
		}
		break;
	case DP_TEDGEDEF:
		{
			spn = splay_tree_lookup(dp_curgraph->eattr, (splay_tree_key) l);
			if (spn == NULL) {
				splay_tree_insert(dp_curgraph->eattr, (splay_tree_key) l, (splay_tree_value) dval);
			} else {
				/*
				   if (0)
				   {
				   printf
				   ("dot %s(): attempt to redefine edge attribute `%s=%s' with value `%s' near line %d\n",
				   __func__, l, (char *) spn->value, r, yylineno);
				   fflush (stdout);
				   }
				 */
				spn->value = (splay_tree_value) dval;
			}
			if (htmllabel == 0) {
				dp_do_eattr(l, r);
			} else {
				printf("%s(): html-label not supported for edge attributes\n", __func__);
			}
		}
		break;
	case DP_TGRAPHDEF:
	case DP_TGRAPH:
		{
			spn = splay_tree_lookup(dp_curgraph->gattr, (splay_tree_key) l);
			if (spn == NULL) {
				splay_tree_insert(dp_curgraph->gattr, (splay_tree_key) l, (splay_tree_value) dval);
			} else {
				/*
				   if (0)
				   {
				   printf
				   ("dot %s(): attempt to redefine graph attribute `%s=%s' with value `%s' near line %d\n",
				   __func__, l, (char *) spn->value, r, yylineno);
				   fflush (stdout);
				   }
				 */
				spn->value = (splay_tree_value) dval;
			}
			if (htmllabel == 0) {
				dp_do_gattr(l, r);
			} else {
				/* todo */
				printf("%s(): html-label not supported for graph attributes\n", __func__);
			}
		}
		break;
	case DP_SGRAPH:
		/* attribute after subgraph */
		break;
	default:
		{
			printf("dot %s(): shouldnothappen dp_cclass=%d\n", __func__, dp_cclass);
			fflush(stdout);
		}
		break;
	}

	return;
}

/* add node as global node and to subgraph nodelist if mode is 0 */
static void dp_nodelink(struct dpnode *node, int mode)
{
	struct dpnlink *nl = NULL;

	if (0) {
		printf("%s(): add node \"%s\" \"%s\"\n", __func__, node->name, node->label);
	}

	/* if mode is 1, do not add as global node. */
	if (mode == 0) {
		/* add node to global nodelist */
		nl = (struct dpnlink *)dp_calloc(1, sizeof(struct dpnlink));

		if (nl == NULL) {
			/* shouldnothappen */
			return;
		}

		nl->n = node;

		if (dp_anodes == NULL) {
			dp_anodes = nl;
			dp_anodesend = nl;
		} else {
			dp_anodesend->next = nl;
			dp_anodesend = nl;
		}
	}

	/* add node to current subgraph */
	nl = (struct dpnlink *)dp_calloc(1, sizeof(struct dpnlink));

	if (nl == NULL) {
		/* shouldnothappen */
		return;
	}

	nl->n = node;

	if (dp_curgraph->dpnodes == NULL) {
		dp_curgraph->dpnodes = nl;
		dp_curgraph->dpnodesend = nl;
	} else {
		dp_curgraph->dpnodesend->next = nl;
		dp_curgraph->dpnodesend = nl;
	}

	return;
}

/* add edge point */
static void dp_eplink(struct dpepoint *epoint)
{
	struct dpeplink *el = NULL;

	/* add point to global pointlist */
	el = (struct dpeplink *)dp_calloc(1, sizeof(struct dpeplink));

	el->ep = epoint;

	if (dp_epl == NULL) {
		dp_epl = el;
		dp_eplend = el;
	} else {
		dp_eplend->next = el;
		dp_eplend = el;
	}

	/* add point to global pointlist */
	el = (struct dpeplink *)dp_calloc(1, sizeof(struct dpeplink));

	el->ep = epoint;

	if (dp_curgraph->dpeplist == NULL) {
		dp_curgraph->dpeplist = el;
		dp_curgraph->dpeplistend = el;
	} else {
		dp_curgraph->dpeplistend->next = el;
		dp_curgraph->dpeplistend = el;
	}

	return;
}

/* recursive clear all eppoint's */
static void dp_clrep_r(struct dpgraph *gr)
{
	struct dpglink *ng = NULL;
	struct dpeplink *el = NULL;
	struct dpeplink *elnext = NULL;

	if (gr == NULL) {
		return;
	}

	ng = gr->dpsubg;

	while (ng) {
		dp_clrep_r(ng->sg);
		ng = ng->next;
	}

	el = gr->dpeplist;

	while (el) {
		elnext = el->next;
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	gr->dpeplist = NULL;
	gr->dpeplistend = NULL;

	return;
}

/* clear all eppoint's */
void dp_clrep(void)
{
	struct dpeplink *el = NULL;
	struct dpeplink *elnext = NULL;

	/* recursive clear in subgraphs */
	dp_clrep_r(dp_groot);

	/* clear epl itself */
	el = dp_epl;

	while (el) {
		elnext = el->next;
		if (el->ep) {
			dp_free(el->ep);
			el->ep = NULL;
		}
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	dp_epl = NULL;
	dp_eplend = NULL;

	return;
}

/* free nodes in subgraphs and rootgraph */
static void dp_clrnodes_r(struct dpgraph *gr)
{
	struct dpglink *ng = NULL;
	struct dpnlink *nl = NULL;
	struct dpnlink *nlnext = NULL;

	if (gr == NULL) {
		return;
	}

	ng = gr->dpsubg;

	while (ng) {
		dp_clrnodes_r(ng->sg);
		ng = ng->next;
	}

	nl = gr->dpnodes;

	while (nl) {
		nlnext = nl->next;
		if (nl) {
			dp_free(nl);
		}
		nl = NULL;
		nl = nlnext;
	}

	gr->dpnodes = NULL;
	gr->dpnodesend = NULL;

	return;
}

/* clear all nodes */
static void dp_clrnodesli(struct dppart *info)
{
	int i = 0;

	if (info == NULL) {
		return;
	}

	for (i = 0; i < info->ndpparts; i++) {
		if (info->parts[i]) {
			dp_clrnodesli(info->parts[i]);
			info->parts[i] = NULL;
		}
	}

	if (info->parts) {
		dp_free(info->parts);
		info->parts = NULL;
	}

	dp_free(info);

	return;
}

/* free ilist */
static void dp_freememil(struct tdldata *td)
{
	struct ilist *ilptr = NULL;	/* text items in td or 0 */
	struct ilist *ilptrnext = NULL;	/* text items in td or 0 */
	if (td == NULL) {
		return;
	}
	if (td->tdd == NULL) {
		return;
	}
	if (td->tdd->il) {
		ilptr = td->tdd->il;
		while (ilptr) {
			ilptrnext = ilptr->next;
			if (ilptr->items) {
				dp_free(ilptr->items);
				ilptr->items = NULL;
			}
			dp_free(ilptr);
			ilptr = ilptrnext;
		}
		td->tdd->il = NULL;
		td->tdd->ilend = NULL;
	}

	return;
}

/* free <tr> */
static void dp_freememtr(struct trlist *tr)
{
	struct tdldata *tdlptr = NULL;	/* td items in tr */
	struct tdldata *tdlptrnext = NULL;

	if (tr == NULL) {
		return;
	}
	if (tr->tritem == NULL) {
		return;
	}

	/* <td> data */
	tdlptr = tr->tritem->td;
	while (tdlptr) {
		tdlptrnext = tdlptr->next;
		/* tdptr is free'ed later */
		/* free il data in <td> */
		if (tdlptr->tdd) {
			dp_freememil(tdlptr);
			dp_free(tdlptr->tdd);
		}
		dp_free(tdlptr);
		tdlptr = tdlptrnext;
	}
	tr->tritem->td = NULL;
	tr->tritem->tdend = NULL;

	dp_free(tr->tritem);
	tr->tritem = NULL;

	return;
}

static void dp_freememt_r(struct tlist *tl)
{
	struct tlist *tlptr = NULL;	/* list of table items */
	struct tlist *tlptrnext = NULL;	/* list of table items */
	struct trlist *trptr = NULL;	/* tr items */
	struct trlist *trptrnext = NULL;	/* end tr items */

	if (tl == NULL) {
		/* shouldnothappen */
		return;
	}

	if (tl->titem == NULL) {
		/* shouldnothappen */
		return;
	}

	if (tl->titem->tabdata) {
		/* clear sub tables if any */
		if (tl->titem->tabdata->tl) {
			tlptr = tl->titem->tabdata->tl;
			while (tlptr) {
				tlptrnext = tlptr->next;
				dp_freememt_r(tlptr);
				if (tlptr->titem) {
					dp_free(tlptr->titem);
					tlptr->titem = NULL;
				}
				dp_free(tlptr);
				tlptr = tlptrnext;
			}
			tl->titem->tabdata->tl = NULL;
			tl->titem->tabdata->tlend = NULL;
		}
		/* <tr> data */
		if (tl->titem->tabdata->tr) {
			trptr = tl->titem->tabdata->tr;
			while (trptr) {
				trptrnext = trptr->next;
				dp_freememtr(trptr);
				if (trptr->tritem) {
					dp_free(trptr->tritem);
					trptr->tritem = NULL;
				}
				dp_free(trptr);
				trptr = trptrnext;
			}
			tl->titem->tabdata->tr = NULL;
			tl->titem->tabdata->trend = NULL;
		}
		if (tl->titem->tabdata) {
			dp_free(tl->titem->tabdata);
			tl->titem->tabdata = NULL;
		}
	}

	if (tl->titem) {
		dp_free(tl->titem);
		tl->titem = NULL;
	}

	return;
}

/* clear hlinfo of one node */
static void dp_clearhlinfonode(struct dpnode *node)
{
	struct tlist *tlptr = NULL;	/* list of table items */
	struct tlist *tlptrnext = NULL;	/* list of table items */

	struct ilist *pil = NULL;
	struct ilist *pilnext = NULL;
	if (node == NULL) {	/* shoudlothappen */
		return;
	}
	if (node->hlinfo == NULL) {	/* shouldnothappen */
		return;
	}

	/* item data to free */
	if (node->hlinfo->il) {
		pil = node->hlinfo->il;
		while (pil) {
			pilnext = pil->next;
			if (pil->items) {
				dp_free(pil->items);
				pil->items = NULL;
			}
			dp_free(pil);
			pil = pilnext;
		}
		node->hlinfo->il = NULL;
		node->hlinfo->ilend = NULL;
	}

	/* table data to free */
	if (node->hlinfo->tl) {
		/* */
		tlptr = node->hlinfo->tl;
		while (tlptr) {
			tlptrnext = tlptr->next;
			dp_freememt_r(tlptr);
			if (tlptr->titem) {
				dp_free(tlptr->titem);
				tlptr->titem = NULL;
			}
			dp_free(tlptr);
			tlptr = tlptrnext;
		}
		/* ready */
		node->hlinfo->tl = NULL;
		node->hlinfo->tlend = NULL;
	}

	/* final free */
	dp_free(node->hlinfo);
	node->hlinfo = NULL;

	return;
}

static void dp_clrnodes(void)
{
	struct dpnlink *nl = NULL;
	struct dpnlink *nlnext = NULL;

	dp_clrnodes_r(dp_groot);

	nl = dp_anodes;

	while (nl) {
		nlnext = nl->next;
		dp_clrnodesli(nl->n->labelinfo);
		nl->n->labelinfo = NULL;
		dp_clearhlinfonode(nl->n);
		if (nl->n) {
			dp_free(nl->n);
			nl->n = NULL;
		}
		dp_free(nl);
		nl = NULL;
		nl = nlnext;
	}

	dp_anodes = NULL;
	dp_anodesend = NULL;

	return;
}

static void dp_clrgraph_r(struct dpgraph *gr)
{
	struct dpglink *ng = NULL;
	struct dpglink *gl = NULL;
	struct dpglink *glnext = NULL;

	if (gr == NULL) {
		return;
	}

	ng = gr->dpsubg;

	while (ng) {
		dp_clrgraph_r(ng->sg);
		ng = ng->next;
	}

	gl = gr->dpsubg;

	while (gl) {
		glnext = gl->next;
		if (gl->sg->defnode) {
			dp_free(gl->sg->defnode);
			gl->sg->defnode = NULL;
		}
		if (gl->sg->defedge) {
			dp_free(gl->sg->defedge);
			gl->sg->defedge = NULL;
		}
		gl->sg->gattr = splay_tree_delete(gl->sg->gattr);
		gl->sg->nattr = splay_tree_delete(gl->sg->nattr);
		gl->sg->eattr = splay_tree_delete(gl->sg->eattr);
		if (gl) {
			dp_free(gl);
		}
		gl = NULL;
		gl = glnext;
	}

	gr->dpsubg = NULL;
	gr->dpsubgend = NULL;

	return;
}

/* clear all garphs */
static void dp_clrgraphs(void)
{
	struct dpglink *dpl = NULL;
	struct dpglink *dplnext = NULL;

	dp_clrgraph_r(dp_groot);

	if (dp_asubg) {
		dpl = dp_asubg;
		while (dpl) {
			dplnext = dpl->next;
			if (dpl->sg) {
				dp_free(dpl->sg);
			}
			dpl->sg = NULL;
			dp_free(dpl);
			dpl = NULL;
			dpl = dplnext;
		}

	}

	dp_asubg = NULL;
	dp_asubgend = NULL;

	return;
}

/* free edges in subgraphs and rootgraph */
static void dp_clredges_r(struct dpgraph *gr)
{
	struct dpglink *ng = NULL;
	struct dpelink *el = NULL;
	struct dpelink *elnext = NULL;

	if (gr == NULL) {
		return;
	}

	ng = gr->dpsubg;

	while (ng) {
		dp_clredges_r(ng->sg);
		ng = ng->next;
	}

	el = gr->dpedges;

	while (el) {
		elnext = el->next;
		/* edge ->e is free()'ed in dp_clredges() */
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	gr->dpedges = NULL;
	gr->dpedgesend = NULL;

	return;
}

/* clear all edges */
static void dp_clredges(void)
{
	struct dpelink *el = NULL;
	struct dpelink *elnext = NULL;

	dp_clredges_r(dp_groot);

	el = dp_aedges;

	while (el) {
		elnext = el->next;
		if (el->e) {
			dp_free(el->e);
			el->e = NULL;
		}
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	dp_aedges = NULL;
	dp_aedgesend = NULL;

	return;
}

/* clear edge head nodes */
void dp_clrheade(void)
{
	struct dpeplink *el = NULL;
	struct dpeplink *elnext = NULL;

	el = dp_headepl;

	while (el) {
		elnext = el->next;
		if (el->ep) {
			dp_free(el->ep);
			el->ep = NULL;
		}
		dp_free(el);
		el = NULL;
		el = elnext;
	}

	dp_headepl = NULL;
	dp_headeplend = NULL;

	return;
}

/* clear tmp edges during edge building */
static void dp_clrtmpe(void)
{
	struct dptelink *te = NULL;
	struct dptelink *tenext = NULL;

	te = dp_tmpe;

	while (te) {
		tenext = te->next;
		if (te->e) {
			dp_free(te->e);
			te->e = NULL;
		}
		dp_free(te);
		te = NULL;
		te = tenext;
	}

	dp_tmpe = NULL;
	dp_tmpeend = NULL;

	return;
}

/* add graph to lists */
static void dp_graphlink(struct dpgraph *sg)
{
	struct dpglink *ng = NULL;

	/* add node to global nodelist */
	ng = (struct dpglink *)dp_calloc(1, sizeof(struct dpglink));

	if (ng == NULL) {
		/* shouldnothappen */
		return;
	}

	ng->sg = sg;

	/* all subgraphs in one list */
	if (dp_asubg == NULL) {
		dp_asubg = ng;
		dp_asubgend = ng;
	} else {
		dp_asubgend->next = ng;
		dp_asubgend = ng;
	}

	/* add node to current subgraph */
	ng = (struct dpglink *)dp_calloc(1, sizeof(struct dpglink));

	if (ng == NULL) {
		/* shouldnothappen */
		return;
	}

	ng->sg = sg;

	if (dp_curgraph->dpsubg == NULL) {
		dp_curgraph->dpsubg = ng;
		dp_curgraph->dpsubgend = ng;
	} else {
		dp_curgraph->dpsubgend->next = ng;
		dp_curgraph->dpsubgend = ng;
	}

	return;
}

/* create node at nodestatement
 * dot allows to redefine a node.
 * node name can be ""
 * node label can be ""
 */
void dp_mknode0(char *name)
{
	struct dpnode *n = NULL;

	/* check if node is in database */
	n = dpuniqnode(name);

	if (n) {
		/* node exist and being redefined now */
		/* only if earlier defined by a node statement */
		/* todo this does not work */
		if (n->bitflags0.defbynode == 1 || 0) {
			if (0) {
				printf("dot %s(): node `%s' line %d is redefined at line %d\n",
				       __func__, n->name, n->yylineno, yylineno);
				fflush(stdout);
			}
		}

		if (dp_groot != dp_curgraph) {
			dp_nodegdef(dp_curgraph->defnode, n);
		}

		dp_curnode = n;
		/* add node to curgraph but not in nodelist */
		dp_nodelink(n, 1);

	} else {
		/* fresh new node */
		n = (struct dpnode *)dp_calloc(1, sizeof(struct dpnode));

		n->name = name;	/* uniq node name */
		n->label = name;	/* label text \N */

		/* set factory defaults */
		dp_nodefdef(n);
		/* set node defaults for this graph */
		dp_nodegdef(dp_groot->defnode, n);
		if (dp_groot != dp_curgraph || 0) {
			dp_nodegdef(dp_curgraph->defnode, n);
		}
		/* setparams */
		n->root = dp_curgraph;
		dp_nodenum++;
		n->nr = dp_nodenum;	/* uniq node number */
		n->yylineno = yylineno;	/* line where node is defined */
		dp_groot->nnodes++;	/* number of nodes in graph */
		if (dp_groot != dp_curgraph) {
			dp_curgraph->nnodes++;	/* number of nodes in sub graph */
		}
		n->bitflags0.defbynode = 1;
		/* add as uniqnode */
		dpuniqnode_add(n);
		/* add node as global node and to subgraph nodelist */
		dp_nodelink(n, 0);
		/* set current node being parsed */
		dp_curnode = n;
	}

	return;
}

/* edge point with node name and port/compass */
struct dpepoint *dp_mknid(char *name, char *port, char *compass)
{
	struct dpnode *n = NULL;
	struct dpepoint *nid = NULL;
	char *compass2 = NULL;
	char *port2 = NULL;
	int yes = 0;

	port2 = port;
	compass2 = compass;

	if (compass) {

		yes = dp_iscompass(compass);

		if (yes == 0) {
			memset(dp_errmsg, 0, 256);
			snprintf(dp_errmsg, (256 - 1),
				 "dot %s(): syntax error invalid compass point `%s' at node `%s' near line %dexpected one of these compass points: n,ne,e,se,s,sw,w,nw,c,_\n\n",
				 __func__, compass, name, yylineno);
			/* continue and error message will soon appear */
		}
	}

	if (compass == NULL) {
		if (port) {
			yes = dp_iscompass(port);

			if (yes == 1) {
				/* turn port into compass */
				compass2 = port;
				port2 = NULL;
			}
		}
	}

	/* check if node is in database */
	n = dpuniqnode(name);

	if (n == NULL) {
		/* node in edge did not exist and create now */
		/* fresh new node */
		n = (struct dpnode *)dp_calloc(1, sizeof(struct dpnode));
		/* setparams */
		n->name = name;	/* uniq node name */
		n->label = name;	/* label text \N */
		/* set factory defaults */
		dp_nodefdef(n);
		/* set node defaults for this graph */
		dp_nodegdef(dp_groot->defnode, n);
		if (dp_groot != dp_curgraph || 0) {
			dp_nodegdef(dp_curgraph->defnode, n);
		}
		n->root = dp_curgraph;	/* subgraph where node is defined */
		dp_nodenum++;
		n->nr = dp_nodenum;	/* uniq node number */
		n->yylineno = yylineno;	/* line where node is defined */
		dp_groot->nnodes++;	/* number of nodes in graph */
		if (dp_groot != dp_curgraph) {
			dp_curgraph->nnodes++;	/* number of nodes in sub graph */
		}
		/* add as uniqnode */
		dpuniqnode_add(n);
		/* add node as global node and to subgraph nodelist */
		dp_nodelink(n, 0);
	}

	nid = (struct dpepoint *)dp_calloc(1, sizeof(struct dpepoint));

	if (nid == NULL) {
		/* shouldnothappen */
		return (NULL);
	}

	nid->n = n;
	nid->port = port2;	/* port or compass point */
	nid->compass = compass2;
	nid->type = 0;		/* type 0: this is a node */
	nid->root = n->root;

	return (nid);
}

/* start edge at nid */
void dp_starte1(struct dpepoint *ep)
{
	struct dpepoint *epnew = NULL;
	struct dpeplink *el = NULL;

	dp_enest++;
	dp_curgraph->enest++;

	/* add point to global pointlist */
	el = (struct dpeplink *)dp_calloc(1, sizeof(struct dpeplink));

	epnew = (struct dpepoint *)dp_calloc(1, sizeof(struct dpepoint));

	epnew->port = ep->port;
	epnew->compass = ep->compass;
	epnew->type = ep->type;
	epnew->root = ep->root;
	epnew->n = ep->n;

	el->ep = epnew;
	dp_eplink(ep);

	if (dp_headepl == NULL) {
		dp_headepl = el;
		dp_headeplend = el;
	} else {
		dp_headeplend->next = el;
		dp_headeplend = el;
	}

	return;
}

/* start edge at sstatements */
void dp_starte2(struct dpepoint *ep)
{
	struct dpepoint *epnew = NULL;
	struct dpeplink *el = NULL;

	dp_enest++;
	dp_curgraph->enest++;

	/* add point to global pointlist */
	el = (struct dpeplink *)dp_calloc(1, sizeof(struct dpeplink));

	epnew = (struct dpepoint *)dp_calloc(1, sizeof(struct dpepoint));

	epnew->port = ep->port;
	epnew->compass = ep->compass;
	epnew->type = ep->type;
	epnew->root = ep->root;
	epnew->n = ep->n;

	el->ep = epnew;

	dp_eplink(ep);

	if (dp_headepl == NULL) {
		dp_headepl = el;
		dp_headeplend = el;
	} else {
		dp_headeplend->next = el;
		dp_headeplend = el;
	}

	return;
}

/* inside edge statement */
void dp_ine(struct dpepoint *ep)
{
	dp_eplink(ep);
	return;
}

/* setup new edge for edge attribute */

void dp_newe(void)
{

	dp_curedge = (struct dpedge *)dp_calloc(1, sizeof(struct dpedge));

	if (dp_curedge == NULL) {
		/* shouldnothappen */
		return;
	}

	dp_curedge->yylineno = yylineno;

	dp_edgegdef(dp_curgraph->defedge, dp_curedge);

	dp_atype_edge();

	return;
}

static void dp_endeprlink(struct dpeplink *el)
{
	struct dpgraph *g = NULL;
	struct dpeplink *eptr = NULL;
	struct dpnlink *nodes = NULL;
	int ltype = 0;

	eptr = el;

	while (eptr) {

		ltype = eptr->ep->type;

		printf("\tltype=%d", ltype);

		if (eptr->ep->type == 0) {
			/* type 0: this is a node */
			printf("`%s' %p ", eptr->ep->n->name, (void *)eptr->ep->root);
		} else if (eptr->ep->type == 1) {
			printf("`subgraph-%p' : ", (void *)eptr->ep->root);
			/* type 1: this is a subgraph */
			g = eptr->ep->root;
			nodes = g->dpnodes;
			if (nodes) {
				while (nodes) {
					printf("`%s' ", nodes->n->name);
					nodes = nodes->next;
				}
			} else {
				printf("no-nodes");
			}
		} else {
			printf("dp_endeprlink()-unknown-ep->type");
		}

		printf("\n");

		eptr = eptr->next;
	}

	return;
}

/* make edges edges */
static void dp_mkedges(void)
{
	struct dpelink *nel = NULL;
	struct dpedge *newedge = NULL;
	struct dptelink *tl = NULL;

	tl = dp_tmpe;

	while (tl) {
		newedge = (struct dpedge *)dp_calloc(1, sizeof(struct dpedge));

		if (newedge == NULL) {
			/* shouldnothappen */
			return;
		}

		dp_edgenum++;
		newedge->nr = dp_edgenum;
		newedge->rootedon = dp_curgraph;
		newedge->fn = tl->e->fn;
		newedge->fport = tl->e->fport;
		newedge->fcompass = tl->e->fcompass;
		newedge->tn = tl->e->tn;
		newedge->tport = tl->e->tport;
		newedge->tcompass = tl->e->tcompass;
		newedge->yylineno = yylineno;

		/* copy edge attributes */
		dp_edgegdef(dp_curedge, newedge);

		nel = (struct dpelink *)dp_calloc(1, sizeof(struct dpelink));

		if (nel == NULL) {
			/* shouldnothappen */
			return;
		}

		nel->e = newedge;

		if (dp_aedges == NULL) {
			dp_aedges = nel;
			dp_aedgesend = nel;
		} else {
			dp_aedgesend->next = nel;
			dp_aedgesend = nel;
		}

		nel = (struct dpelink *)dp_calloc(1, sizeof(struct dpelink));

		if (nel == NULL) {
			/* shouldnothappen */
			return;
		}

		nel->e = newedge;

		/* */
		if (tl->e->fn->root->dpedges == NULL) {
			tl->e->fn->root->dpedges = nel;	/* edges starting in this graph */
			tl->e->fn->root->dpedgesend = nel;	/* edges starting in this graph */
		} else {
			tl->e->fn->root->dpedgesend->next = nel;	/* edges starting in this graph */
			tl->e->fn->root->dpedgesend = nel;	/* edges starting in this graph */
		}

		tl = tl->next;
	}

	return;
}

/* print all edges */
static void dp_prtae(void)
{
	struct dpelink *nel = NULL;
	printf("dot %s(): all edges:\n", __func__);
	nel = dp_aedges;
	while (nel) {
		printf(" `%s'->`%s'\n", nel->e->fn->name, nel->e->tn->name);
		nel = nel->next;
	}
	printf("dot %s(): end all edges\n", __func__);
	return;
}

/* print tmp edges */
static void dp_prte(void)
{
	struct dptelink *tl = NULL;
	tl = dp_tmpe;
	while (tl) {
		printf("dot %s(): `%s'->`%s' %p->%p\n", __func__, tl->e->fn->name,
		       tl->e->tn->name, (void *)tl->e->fn->root, (void *)tl->e->tn->root);
		tl = tl->next;
	} return;
}

/* create tmp edges */
static void dp_addte(struct dpnode *fn, char *fport, char *fcompass, struct dpnode *tn, char *tport, char *tcompass)
{
	struct dptmpe *te = NULL;
	struct dptelink *tl = NULL;

	te = (struct dptmpe *)dp_calloc(1, sizeof(struct dptmpe));

	if (te == NULL) {
		/* shouldnothappen */
		return;
	}

	te->fn = fn;
	te->fport = fport;
	te->fcompass = fcompass;
	te->tn = tn;
	te->tport = tport;
	te->tcompass = tcompass;

	tl = (struct dptelink *)dp_calloc(1, sizeof(struct dptelink));

	if (tl == NULL) {
		/* shouldnothappen */
		dp_free(te);
		return;
	}

	tl->e = te;

	if (dp_tmpe == NULL) {
		dp_tmpe = tl;
		dp_tmpeend = tl;
	} else {
		dp_tmpeend->next = tl;
		dp_tmpeend = tl;
	}

	return;
}

static void dp_endel_n2n(struct dpepoint *fn, struct dpepoint *tn)
{
	if (yydebug) {
		printf("%s(1): `%s'->`%s'\n", __func__, fn->n->name, tn->n->name);
	}
	dp_addte(fn->n, fn->port, fn->compass, tn->n, tn->port, tn->compass);
	return;
}

static void dp_endel_n2g(struct dpepoint *fn, struct dpepoint *tn)
{
	struct dpgraph *g = NULL;
	struct dpnlink *nodes = NULL;

	g = tn->root;
	nodes = g->dpnodes;
	while (nodes) {
		if (yydebug) {
			printf("%s(1): `%s'->`%s'\n", __func__, fn->n->name, nodes->n->name);
		}
		dp_addte(fn->n, fn->port, fn->compass, nodes->n, NULL, NULL);
		nodes = nodes->next;
	}

	return;
}

/* subgraph to node as in {}->x */
static void dp_endel_g2n(struct dpepoint *fn, struct dpepoint *tn)
{
	struct dpgraph *g = NULL;
	struct dpnlink *nodes = NULL;

	g = fn->root;
	nodes = g->dpnodes;
	while (nodes) {
		if (yydebug || 0) {
			printf("%s(1): `%s'->`%s'\n", __func__, nodes->n->name, tn->n->name);
		}
		dp_addte(nodes->n, NULL, NULL, tn->n, tn->port, tn->compass);
		nodes = nodes->next;
	}

	return;
}

static void dp_endel_g2g(struct dpepoint *fn, struct dpepoint *tn)
{
	struct dpgraph *g = NULL;
	struct dpnlink *nodes = NULL;
	struct dpgraph *g2 = NULL;
	struct dpnlink *nodes2 = NULL;

	g = fn->root;
	nodes = g->dpnodes;
	while (nodes) {
		g2 = tn->root;
		nodes2 = g2->dpnodes;
		while (nodes2) {
			if (yydebug) {
				printf("%s(1): `%s'->`%s'\n", __func__, nodes->n->name, nodes2->n->name);
			}
			dp_addte(nodes->n, NULL, NULL, nodes2->n, NULL, NULL);
			nodes2 = nodes2->next;
		}
		nodes = nodes->next;
	}

	return;
}

/* main */
static void dp_endel(struct dpeplink *el)
{
	struct dpeplink *eptr = NULL;
	struct dpepoint *fn = NULL;
	struct dpepoint *tn = NULL;
	int ltype = 0;
	int rtype = 0;

	eptr = el;

	if (yydebug || 0) {
		printf("%s(start): dp_enest=%d eptr=%p eptr->next=%p\n", __func__, dp_enest, (void *)eptr, (void *)eptr->next);
	}

	if (dp_enest > 1) {
		printf("dot %s(): nested edges not supported at line %d\n", __func__, yylineno);
		fflush(stdout);
	}

	if (eptr && eptr->next == NULL) {
		fn = dp_headepl->ep;
		tn = eptr->ep;

		ltype = fn->type;
		rtype = tn->type;

		if (ltype == 0 && rtype == 0) {
			dp_endel_n2n(fn, tn);
		} else if (ltype == 0 && rtype == 1) {
			dp_endel_n2g(fn, tn);
		} else if (ltype == 1 && rtype == 0) {
			dp_endel_g2n(fn, tn);
		} else if (ltype == 1 && rtype == 1) {
			dp_endel_g2g(fn, tn);
		} else {
			printf("%s(1): ltype=%d rtype=%d shouldnothappen\n", __func__, ltype, rtype);
		}

	} else {

		while (eptr) {
			if (eptr->next == NULL) {
				break;
			}

			fn = eptr->ep;
			tn = eptr->next->ep;

			fflush(stdout);

			ltype = fn->type;
			rtype = tn->type;

			if (dp_enest) {
				if (fn->root == tn->root) {
					if (ltype == 0 && rtype == 0) {
						dp_endel_n2n(fn, tn);
					} else if (ltype == 0 && rtype == 1) {
						dp_endel_n2g(fn, tn);
					} else if (ltype == 1 && rtype == 0) {
						dp_endel_g2n(fn, tn);
					} else if (ltype == 1 && rtype == 1) {
						dp_endel_g2g(fn, tn);
					} else {
						printf("%s(2): ltype=%d rtype=%d shouldnothappen\n", __func__, ltype, rtype);
					}
				}

			} else {
				/* nest is 0 */
				if (ltype == 0 && rtype == 0) {
					dp_endel_n2n(fn, tn);
				} else if (ltype == 0 && rtype == 1) {
					dp_endel_n2g(fn, tn);
				} else if (ltype == 1 && rtype == 0) {
					dp_endel_g2n(fn, tn);
				} else if (ltype == 1 && rtype == 1) {
					dp_endel_g2g(fn, tn);
				} else {
					printf
					    ("%s(3): ltype=%d rtype=%d fn=%s tn=%s shouldnothappen\n",
					     __func__, ltype, rtype, fn->n->name, tn->n->name);
				}

			}

			eptr = eptr->next;
		}

	}

	if (yydebug || 0) {
		printf("%s(end):\n", __func__);
	}

	return;
}

/* end edge statement */
void dp_ende(void)
{
	struct dpgraph *g = NULL;
	struct dpglink *sg = NULL;
	int en = 0;

	en = dp_curgraph->enest;

	if (yydebug || 0) {
		printf
		    ("dot %s(): curgraph=%p now dp_curgraph->enest from %d to %d and enest from %d to %d\n",
		     __func__, (void *)dp_curgraph, en, en - 1, dp_enest, dp_enest - 1);
	}

	dp_enest--;

	if (dp_enest < 0) {
		dp_enest = 0;
	}

	dp_curgraph->enest--;

	if (dp_curgraph->enest < 0) {
		dp_curgraph->enest = 0;
	}

	if (yydebug || 0) {
		printf("dot %s(): dp_epl list:\n", __func__);
		dp_endeprlink(dp_epl);
		g = dp_groot;
		printf("  root graph:\n");
		dp_endeprlink(g->dpeplist);
		sg = g->dpsubg;
		while (sg) {
			printf("  subgraph:\n");
			dp_endeprlink(sg->sg->dpeplist);
			sg = sg->next;
		}

		printf("dot %s(): end dp_epl list\n", __func__);
		printf("dot %s(): dp_headepl list:\n", __func__);
		dp_endeprlink(dp_headepl);
		printf("dot %s(): end dp_headepl list\n", __func__);
		fflush(stdout);
	}

	dp_endel(dp_epl);

	/* and full end of edge statement, handle the rest */
	if (dp_enest == 0) {
		if (yydebug || 0) {
			printf("dot %s(): Wipe headepl\n", __func__);
			/* print tmp edges */
			dp_prte();
		}
		/* make real edges */
		dp_mkedges();
		if (yydebug || 0) {	/* print all edges */
			dp_prtae();
		}
		dp_free(dp_curedge);
		dp_curedge = NULL;
		dp_clrheade();
		dp_clrtmpe();
		dp_enest = 0;
	}

	dp_atype_graph();

	fflush(stdout);

	return;
}

/* subg without name, also in edge like a->{b->c}
 * or with a name as in subgraph "ho" { }
 * or with empty name as in subgraph { }
 * or with nil name as in {  }
 * types of subgraphs:
 * #define DP_SG_ROOT 0	* root graph type
 * #define DP_SG_CO 1	* compound subgraph {}
 * #define DP_SG_NM 2	* named subgrph
 * #define DP_SG_CL 3	* cluster subgraph
 * #define DP_SG_NN 4	* no name subgraph
 */
void dp_namedsubg(char *sgname, int type)
{
	struct dpgraph *nsg = NULL;

	nsg = (struct dpgraph *)dp_calloc(1, sizeof(struct dpgraph));

	if (nsg == NULL) {
		/* shouldnothappen */
		return;
	}

	/* uniq graph number */
	nsg->nr = dp_sgnr;

	dp_sgnr++;

	/* set factory defaults */
	dp_graphfdef(nsg);

	dp_nsubg(nsg, sgname, type);

	dp_graphlink(nsg);

	dp_pushgraph(nsg);

	return;
}

/* end ssatement in edge */
struct dpepoint *dp_endss(void)
{
	struct dpepoint *newe = NULL;
	struct dpgraph *g = NULL;

	newe = dp_calloc(1, sizeof(struct dpepoint));

	newe->type = 1;		/* type 1: this is a subgraph edge point */
	newe->root = dp_curgraph;

	g = dp_pullgraph();

	if (g) {
	}
	return (newe);
}

void dp_cke(char *edgetype)
{
	if (strcmp(edgetype, dp_groot->etype)) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "dot %s(): syntax error edgetype `%s' but expected `%s' near line %d\n",
			 __func__, edgetype, dp_groot->etype, yylineno);
	}
	return;
}

/* 'add' strings in a new string */
char *dp_ccat(char *a, char *b)
{
	size_t lena = 0;
	size_t lenb = 0;
	char *tmpp = NULL;
	char *res = NULL;

	lena = strlen(a);
	lenb = strlen(b);

	tmpp = dp_calloc(1, (lena + lenb + 1));

	if (tmpp == NULL) {
		/* shouldnothappen */
		return (NULL);
	}

	strcpy(tmpp, a);
	strcat(tmpp, b);

	res = dp_uniqstr(tmpp);

	dp_free(tmpp);

	return (res);
}

/* clear all memory in use zzz */
void dp_clearall(void)
{

	dp_clrep();

	dp_clrheade();

	dp_clrtmpe();

	/* clear all edges in graph */
	dp_clredges();
	dp_clrnodes();
	dp_clrgraphs();

	if (dp_groot) {
		dp_groot->gattr = splay_tree_delete(dp_groot->gattr);
		dp_groot->nattr = splay_tree_delete(dp_groot->nattr);
		dp_groot->eattr = splay_tree_delete(dp_groot->eattr);
		dp_free(dp_groot->defnode);
		dp_free(dp_groot->defedge);
		dp_free(dp_groot);
	}

	dpgraphs = splay_tree_delete(dpgraphs);
	dp_curgraph = NULL;
	dp_groot = NULL;

	clear_dpuniqnode();
	dp_colorcode_clear();
	dp_clear_uniqstr();

	return;
}

/* end */
