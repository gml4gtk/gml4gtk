
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
#include "dpmem.h"
#include "dphl.h"

/* change \n \r \l chars */
static char *dolabel(char *str)
{
	char *ret = NULL;
	char *res = NULL;
	char *p = NULL;
	char *q = NULL;
	int len = 0;

	if (str == NULL) {
		return (NULL);
	}

	len = strlen(str);

	if (len == 0) {
		/* fixme todo */
		return ("  ");
	}

	if (len < 2) {
		return (str);
	}

	res = (char *)dp_calloc(1, (len + 1));

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
	dp_free(res);
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
	nrec = (struct gml_rl *)dp_calloc(1, sizeof(struct gml_rl));
	/* number of sub parts can be 0 */
	nrec->hd = info->hd;
	nrec->nparts = info->ndpparts;
	nrec->dir = info->dir;
	nrec->port = uniqstr(info->id);
	nrec->label = uniqstr(info->lp);
	/* copy sub parts if any */
	if (info->ndpparts) {
		nrec->parts = (struct gml_rl **)dp_calloc(1, info->ndpparts * sizeof(struct gml_rl *));
		for (i = 0; i < info->ndpparts; i++) {
			nrec->parts[i] = rlcopy(info->parts[i]);
		}
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
				gl = dp_calloc(1, sizeof(struct gml_glist));
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

/* copy 1 html item */
static struct gml_hitem *hlimakecopy(struct item *item, struct dpnode *node)
{
	struct gml_hitem *ret = NULL;
	ret = dp_calloc(1, sizeof(struct gml_hitem));
	if (ret == NULL) {
		/* shouldnothappen */
		return (ret);
	}
	ret->text = NULL;	/* text to display */
	ret->fontname = NULL;	/* optional font */
	ret->fontsize = (-1);	/* optional pointsize */
	ret->fontcolor = (-1);	/* optional color of text */
	ret->ncolor = (-1);	/* optional background color from <td> or <table> */
	/* set modified text if any */
	if (item->atext) {
		ret->text = uniqstr(item->atext);
	} else {
		ret->text = uniqstr(item->text);
	}
	if (yydebug || 0) {
		printf("%s(): copy \"%s\"\n", __func__, ret->text);
	}
	/* set original text */
	ret->otext = uniqstr(item->text);
	/* set fontname if specified */
	if (item->fontname == NULL) {
		/* not specified */
		if (node->bitflags0.fontnameset) {
			ret->fontname = uniqstr(node->fontname);
		} else {
			/* not specified */
			ret->fontname = NULL;
		}
	} else {
		ret->fontname = uniqstr(item->fontname);
	}
	/* set fontsize if specified */
	if (item->fontsize < 0) {
		/* not specified */
		if (node->bitflags0.fontsizeset) {
			ret->fontsize = (int)node->fontsize;
		} else {
			/* not specified */
			ret->fontsize = 0;
		}
	} else {
		ret->fontsize = item->fontsize;
	}
	/* set fontcolor if specified */
	if (item->fontcolor < 0) {
		/* not specified */
		if (node->bitflags0.fontcolorset) {
			ret->fontcolor = node->fontcolor;
		} else {
			/* not specified default to black font color */
			ret->fontcolor = 0;
		}
	} else {
		ret->fontcolor = item->fontcolor;
	}
	/* set background color */
	if (item->ncolor < 0) {
		/* not specified */
		if (node->bitflags0.fcolorset) {
			/* fillcolor of node */
			ret->ncolor = node->fcolor;
		} else {
			/* not specified default white background color */
			ret->ncolor = 0x00ffffff;
		}
	} else {
		ret->ncolor = item->ncolor;
	}
	/* copy bitflags */
	if (item->bitflags.at) {
		/* set if str has a '&' */
		ret->bitflags.at = 1;
	}
	if (item->bitflags.br) {
		/* set if str is a <br/> token */
		ret->bitflags.br = 1;
	}
	if (item->bitflags.img) {
		/* set if str is a <img> */
		ret->bitflags.img = 1;
	}
	if (item->bitflags.b) {
		/* set if str is <b> bold */
		ret->bitflags.b = 1;
	}
	if (item->bitflags.i) {
		/* set if str is <i> italic */
		ret->bitflags.i = 1;
	}
	if (item->bitflags.u) {
		/* set if str is <u> underline */
		ret->bitflags.u = 1;
	}
	if (item->bitflags.o) {
		/* set if str is <o> overline */
		ret->bitflags.o = 1;
	}
	if (item->bitflags.s) {
		/* set if str is <s> strike-through */
		ret->bitflags.s = 1;
	}
	if (item->bitflags.sub) {
		/* set if str is <sub> subscript */
		ret->bitflags.sub = 1;
	}
	if (item->bitflags.sup) {
		/* set if str is <sup> superscript */
		ret->bitflags.sup = 1;
	}
	if (item->bitflags.hr) {
		/* set if str is a <hr> token */
		ret->bitflags.hr = 1;
	}
	if (item->bitflags.vr) {
		/* set if str is a <vr> token */
		ret->bitflags.vr = 1;
	}
	return (ret);
}

/* */
static void hlicopy_pr(struct gml_hl *h, struct dpnode *node)
{
	struct gml_hilist *hil = NULL;
	struct gml_hitem *ph = NULL;
	int i = 1;
	if (h == NULL) {	/* shouldnothappen */
		return;
	}
	if (node == NULL) {	/* shoulnothappen */
		return;
	}
	printf("%s(): items in node \"%s\" \"%s\":\n", __func__, node->name, node->label);
	hil = h->il;
	while (hil) {
		ph = hil->items;
		if (ph) {
			printf("  item %d \"%s\"\n", i, ph->text);
		} else {
			printf("  item %d nil string\n", i);
		}
		i++;
		hil = hil->next;
	}
	return;
}

/* copy html items list */
static struct gml_hl *hlicopy(struct dpnode *node)
{
	struct gml_hl *ret = NULL;
	struct ilist *il = NULL;
	struct gml_hilist *hil = NULL;
	struct hlpart *pp = NULL;
	ret = dp_calloc(1, sizeof(struct gml_hl));
	if (ret == NULL) {
		/* shouldnothappen */
		return (ret);
	}
	ret->mode = 0;
	pp = node->hlinfo;
	if (pp == NULL) {
		/* shouldnothappen */
		printf("%s(): nil hlinfo for node \"%s\"\n", __func__, node->name);
		return (ret);
	}
	il = pp->il;
	while (il) {
		if (il->items == NULL) {
			/* shouldnothappen */
			printf("%s(): nil item in node \"%s\" \"%s\"\n", __func__, node->name, node->label);
		} else {
			hil = dp_calloc(1, sizeof(struct gml_hilist));
			if (hil == NULL) {
				/* shouldnothappen */
				break;
			}
			/* create copy of html item */
			hil->items = hlimakecopy(il->items, node);
			/* link in */
			if (ret->il == NULL) {
				ret->il = hil;
				ret->ilend = hil;
			} else {
				ret->ilend->next = hil;
				ret->ilend = hil;
			}
		}
		il = il->next;
	}
	/* print the item data */
	if (yydebug || 0) {
		hlicopy_pr(ret, node);
	}
	return (ret);
}

/* zzz */

/* copy 1 <td> */
static struct gml_tditem *hltdcopy(struct tddata *ttdd)
{
	struct gml_tditem *newtd = NULL;
	struct ilist *pil;	/* text items in td or 0 */
	struct item *items;

	printf("%s(): copy 1 <td> ttdd=%p ttri->td=%p\n", __func__, (void *)ttdd, (void *)ttdd->il);

	newtd = dp_calloc(1, sizeof(struct gml_tditem));

	pil = ttdd->il;

	while (pil) {
		items = pil->items;
		printf("%s(): <td> il = \"%s\"\n", __func__, items->text);
		pil = pil->next;
	}

	return (newtd);
}

/* copy 1 <tr> */
static struct gml_tritem *hltrcopy(struct trdata *ttri)
{
	struct gml_tritem *newtr = NULL;
	struct tdldata *ptd = NULL;	/* td items in tr */
	struct tddata *ttdd = NULL;
	struct gml_tditem *newtd = NULL;

	printf("%s(): copy 1 <tr> ttri->td=%p\n", __func__, (void *)ttri->td);

	newtr = dp_calloc(1, sizeof(struct gml_tritem));

	ptd = ttri->td;

	while (ptd) {
		/* tddata has list to <td> items */
		ttdd = ptd->tdd;
		hltdcopy(ttdd);
		if (newtr->tdi == NULL) {
			newtr->tdi = newtd;
			newtr->tdiend = newtd;
		} else {
			newtr->tdiend->next = newtd;
			newtr->tdiend = newtd;
		}
		ptd = ptd->next;
	}

	return (newtr);
}

/* copy html tables list */
//struct gml_htlist *
static struct gml_titem *hltcopy_r(struct tlist *tl, struct gml_titem *ti)
{
	struct gml_titem *tinew = NULL;
	struct gml_htlist *tlnew = NULL;	/* list of sub table items */
	struct tlist *tlp = NULL;	/* list of table items */
	struct tableldata *tbd = NULL;
	struct tabledata *tabd = NULL;
	struct trlist *trd = NULL;	/* tr items */
	struct trdata *ttritem = NULL;
	struct gml_tritemlist *trl = NULL;

	if (ti == NULL) {
		printf("%s(): starting root table\n", __func__);
	} else {
		printf("%s(): starting sub table rooted on ti=%p ti->tl=%p ti->tlend=%p\n", __func__, (void *)ti, (void *)ti->tl,
		       (void *)ti->tlend);
	}

	tinew = calloc(1, sizeof(struct gml_titem));

	if (ti) {
		if (ti->tl == NULL) {
			ti->tl = tlnew;
			ti->tlend = tlnew;
		} else {
			ti->tlend->next = tlnew;
			ti->tlend = tlnew;
		}
	}

	if (tl == NULL) {
		return (tinew);
	}

	/* first copy subs */
	tlp = tl;
	while (tlp) {
		tbd = tl->titem;
		if (tbd) {
			tabd = tbd->tabdata;
			if (tabd) {
				tlnew = calloc(1, sizeof(struct gml_htlist));
				tlnew->titem = hltcopy_r(tabd->tl, tinew);
				if (ti) {
					if (ti->tl == NULL) {
						ti->tl = tlnew;
						ti->tlend = tlnew;
					} else {
						ti->tlend->next = tlnew;
						ti->tlend = tlnew;
					}
				}
			}
		}
		tlp = tlp->next;
	}

	printf("%s(): at ti=%p tl->titem=%p\n", __func__, (void *)ti, (void *)tl->titem);
	if (1) {
		/* list of tr items in this table to copy */
		tbd = tl->titem;
		if (tbd) {
			tabd = tbd->tabdata;
			trd = tabd->tr;
			while (trd) {
				ttritem = trd->tritem;
				trl = dp_calloc(1, sizeof(struct gml_tritemlist));
				printf("tr in table %p\n", (void *)ti);
				trl->tritem = hltrcopy(ttritem);
				if (tinew->tr == NULL) {
					tinew->tr = trl;
					tinew->trend = trl;
				} else {
					tinew->trend->next = trl;
					tinew->trend = trl;
				}
				trd = trd->next;
			}
		}
	}

	return (tinew);
}

static void htlcopy_prsp(int ind)
{
	int i = 0;
	for (i = 0; i < ind; i++) {
		printf(" ");
	}
	return;
}

static void htlcopy_prhtl_r(struct gml_htlist *htl, int ind)
{
	struct gml_htlist *htlp = NULL;

	htlcopy_prsp(ind);

	htlp = htl;

	if (htl == NULL) {
		printf("%p htlsub\n", (void *)htlp);
		return;
	}

	while (htlp) {
		printf("%p htlsub\n", (void *)htlp);
		htlp = htlp->next;
	}
	return;
}

/* print the build data */
static void htlcopy_pr(struct gml_hl *hl, struct dpnode *node)
{
	struct gml_htlist *htl = NULL;
	struct gml_htlist *htlsub = NULL;

	printf("html data of this node number %d:\n", node->nr);

	if (hl) {
		htl = hl->tl;
		if (htl) {
			while (htl) {
				printf("%p root htlist\n", (void *)htl);
				htlsub = htl->titem->tl;
				if (htlsub) {
					htlcopy_prhtl_r(htlsub, 3);
				} else {
					printf("no-hltsub-data\n");
				}
				htl = htl->next;
			}
		} else {
			printf("no-hlt-data\n");
		}
	} else {
		printf("nil-no-data\n");
	}
	printf("html data end\n");
	return;
}

/* copy html tables list */
static struct gml_hl *hltcopy(struct dpnode *node)
{
	struct gml_hl *ret = NULL;
	struct tlist *tl = NULL;	/* list of table items */
	struct gml_htlist *tlnew = NULL;	/* list of sub table items */

	if (node->hlinfo == NULL) {
		/* shouldnothappen */
		return (NULL);
	}

	ret = dp_calloc(1, sizeof(struct gml_hl));

	/* this is table data */
	ret->mode = 1;

	/* scan the tables */
	tl = node->hlinfo->tl;

	if (yydebug || 1) {
		printf("%s(): node %d node->hlinfo=%p node->hlinfo->tl=%p\n", __func__, node->nr, (void *)node->hlinfo, (void *)tl);
	}

	while (tl) {
		tlnew = calloc(1, sizeof(struct gml_htlist));
		tlnew->titem = hltcopy_r(tl, NULL);
		if (ret->tl == NULL) {
			ret->tl = tlnew;
			ret->tlend = tlnew;
		} else {
			ret->tlend->next = tlnew;
			ret->tlend = tlnew;
		}
		tl = tl->next;
	}

	if (yydebug || 1) {
		htlcopy_pr(ret, node);
	}

	return (ret);
}

/* parse dot file, 0 return if oke. */
int dotparse(struct gml_graph *g, FILE * f, char *fname, char *argv0)
{
	struct dpnlink *nss = NULL;
	struct dpnode *node = NULL;
	struct dpelink *es = NULL;
	struct dpedge *edge = NULL;
	struct gml_rl *rl = NULL;
	struct gml_hl *hl = NULL;
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
	int bgcolor = 0x00ffffff;	/* default white node background */
	int fontcolor = 0;	/* default black text color */
	char *fc = NULL;
	char *tc = NULL;
	int nr = 0;
	int ishtml = 0;
	int nhtmltable = 0;

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

	dp_lex_deinit();

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

	if (0) {
		/* list with all nodes */
		nss = dp_anodes;

		while (nss) {
			/* get node data */
			node = nss->n;

			printf("%s(): pre-checking node \"%s\" \"%s\" html-label=%d ", __func__, node->name, node->label,
			       node->htmllabel);
			if (node->htmllabel) {
				printf("mode=%d hlinfo=%p il=%p tl=%p\n", nss->n->hlinfo->mode, (void *)nss->n->hlinfo,
				       (void *)node->hlinfo->il, (void *)node->hlinfo->tl);
			} else {
				printf("\n");
			}

			nss = nss->next;
		}
		nss = NULL;
	}

	/* create copy of subgraphs */
	sp_crsg_r(dp_groot);

	/* add subgraphs to root graph */
	sp_addsg_r(dp_groot);

	if (0) {
		/* list with all nodes */
		nss = dp_anodes;

		while (nss) {
			/* get node data */
			node = nss->n;

			printf("%s(): pre-checking-2 node \"%s\" \"%s\" html-label=%d ", __func__, node->name, node->label,
			       node->htmllabel);
			if (node->htmllabel) {
				printf("mode=%d hlinfo=%p il=%p tl=%p\n", nss->n->hlinfo->mode, (void *)nss->n->hlinfo,
				       (void *)nss->n->hlinfo->il, (void *)nss->n->hlinfo->tl);
			} else {
				printf("\n");
			}

			nss = nss->next;
		}
		nss = NULL;
	}

	/* list with all nodes */
	nss = dp_anodes;

	while (nss) {
		/* get node data */
		node = nss->n;

		if (0) {
			printf("%s(): checking-1 node \"%s\" \"%s\" html-label=%d ", __func__, nss->n->name, nss->n->label,
			       nss->n->htmllabel);
			if (node->htmllabel) {
				printf("mode=%d hlinfo=%p il=%p tl=%p\n", nss->n->hlinfo->mode, (void *)nss->n->hlinfo,
				       (void *)nss->n->hlinfo->il, (void *)nss->n->hlinfo->tl);
			} else {
				printf("\n");
			}
		}

		/* graph where node is located */
		ro = uniqgraph(nss->n->root->nr);

		/* node number as in gml graph */
		foundid = node->nr;

		nodename = node->name;
		nodelabel = dolabel(nss->n->label);

		if (0) {
			printf("%s(): checking-2 node \"%s\" \"%s\" html-label=%d ", __func__, node->name, node->label,
			       node->htmllabel);
			if (node->htmllabel) {
				printf("mode=%d hlinfo=%p il=%p tl=%p\n", nss->n->hlinfo->mode, (void *)nss->n->hlinfo,
				       (void *)nss->n->hlinfo->il, (void *)nss->n->hlinfo->tl);
			} else {
				printf("\n");
			}
		}

		/* check if html label */
		if (nss->n->htmllabel) {
			ishtml = 1;
		} else {
			ishtml = 0;
		}

		/* node fill color white and bordercolor black */
		ncolor = 0x00ffffff;
		nbcolor = 0;
		fontcolor = 0;

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

		/* record or html data */
		rl = NULL;
		hl = NULL;

		/* this is a html label */
		if (ishtml == 1 && nss->n->hlinfo == NULL) {
			/* shouldnothappen */
			printf("%s(): ishtml is 1 but ns->n->hlinfo=%p for node \"%s\"\n", __func__, (void *)nss->n->hlinfo,
			       nss->n->name);
		}

		if (nss->n->hlinfo) {
			if (yydebug || 0) {
				printf("%s(): before-copy node \"%s\" mode=%d hlinfo=%p il=%p tl=%p\n", __func__, node->name,
				       nss->n->hlinfo->mode, (void *)nss->n->hlinfo, (void *)nss->n->hlinfo->il,
				       (void *)nss->n->hlinfo->tl);
			}
			/* this is a html label */
			if (ishtml == 0) {
				/* shouldnothappen */
				printf("%s(): ishtml is 0 but ns->n->hlinfo=%p\n", __func__, (void *)nss->n->hlinfo);
			}
			/* create copy of html items or tables */
			if (nss->n->hlinfo->mode == 0) {
				/* html items list */
				hl = hlicopy(nss->n);
				ishtml = 1;
			} else if (nss->n->hlinfo->mode == 1) {
				/* html tables list rooted on basis */
				if (0) {
					/* html tables not-yet supported */
					hl = hltcopy(nss->n);
				} else {
					/* turn-off html label */
					ishtml = 0;
					/* substitute label text */
					nodelabel = "html-table";
				}
				if (nss->n->name == NULL) {
					/* shouldnothappen */
					nss->n->name = uniqstr("nil-node-name");
				}
				if (nhtmltable == 0) {
					printf("%s(): html tables as in node with name \"%s\" not yet supported\n", __func__,
					       nss->n->name);
				}
				nhtmltable++;
			} else {
				printf("%s(): wrong html mode %d for node \"%s\"\n", __func__, nss->n->hlinfo->mode, nss->n->name);
			}
		} else if (nss->n->labelinfo) {
			/* this is a record label */
			if (nss->n->shape == DPSHAPE_RECORD || nss->n->shape == DPSHAPE_MRECORD) {
				/* can also be html label */
				if (ishtml) {
					/* todo copy html info */
					if (nss->n->labelinfo) {
						printf("%s(): ns->n->labelinfo=%p should be 0\n", __func__,
						       (void *)nss->n->labelinfo);
					}
				} else {
					if (nss->n->labelinfo) {
						rl = rlcopy(nss->n->labelinfo);
						rlcheck(rl);
					}
				}
			} else {
				/* this is not a record shape */
				if (nss->n->labelinfo) {
					printf("%s(): ns->n->labelinfo=%p should be 0\n", __func__, (void *)nss->n->labelinfo);
				}
				rl = NULL;
			}
		} else {
			/* not html label, not record label, but other label */
		}

		/* print record label data */
		if (yydebug) {
			if (rl) {
				prrlind = 0;
				prrl(rl);
			}
			/* if html, print html label */
		}

		/* uniq node number starting at 1 */
		maingraph->nodenum++;
		nr = maingraph->nodenum;

		add_new_node(g, ro, nr, foundid, nodename, nodelabel, ncolor, nbcolor, rl, hl, fontcolor, ishtml);

		/* free dphl data */
		dphl_freemem();

		nss = nss->next;
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

		/* check if html <> string */
		ishtml = 0;
		if (elabel) {
			if (strlen(elabel)) {
				if (elabel[0] == '<' && elabel[strlen(elabel) - 1] == '>') {
					ishtml = 1;
				}
			}
		}

		ecolor = edge->ecolor;
		style = edge->style;
		fc = uniqstr(edge->fcompass);
		tc = uniqstr(edge->tcompass);
		add_new_edge(g, ro, foundsource, foundtarget, elabel, ecolor, style, fc, tc, econstraint, ishtml);
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
