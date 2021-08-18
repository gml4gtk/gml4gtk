
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

/*
 * the dp*.c files are about DotParsing
 * and dpif.c is the interface to the rest of the program
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <zlib.h>

#include "splay-tree.h"
#include "main.h"
#include "hier.h"
#include "dp.h"
#include "dpun.h"
#include "dpus.h"
#include "dpif.h"
#include "dpmisc.h"
#include "lex.yy.h"
#include "uniqstr.h"
#include "uniqgraph.h"
#include "dot.tab.h"
#include "dpmem.h"
#include "dphl.h"

/* change \n \r \l \N chars */
static char *dolabel(struct dpnode *node, char *str)
{
	char *ret = NULL;
	char *res = NULL;
	char *res2 = NULL;
	char *p = NULL;
	char *p2 = NULL;
	char *q = NULL;
	int len = 0;
	int nn = 0;
	char *nname = NULL;

	if (str == NULL) {
		return (NULL);
	}

	len = strlen(str);

	if (len == 0) {
		/* fixme todo at "" return "  " */
		return ("  ");
	}

	if (len < 2) {
		return (uniqstr(str));
	}

	res = (char *)dp_calloc(1, (len + 1));

	p = str;
	q = res;
	while (*p) {
		if (*p == '\\') {
			if (*(p + 1) == 'n') {
				(*q) = '\n';
				q++;
				p++;
				p++;
			} else if (*(p + 1) == 'l') {
				(*q) = '\n';
				q++;
				p++;
				p++;
			} else if (*(p + 1) == 'r') {
				(*q) = '\n';
				q++;
				p++;
				p++;
			} else if (*(p + 1) == 'N') {
				/* first only count number of \N */
				nn++;
				(*q) = (*p);
				p++;
				q++;
			} else {
				(*q) = (*p);
				p++;
				q++;
			}
		} else {
			/* regular char */
			(*q) = (*p);
			p++;
			q++;
		}
	}

	/* translate \N nn times */
	if (nn) {
		if (node) {
			if (node->name == NULL) {
				/* shouldnothappen */
				printf("%s(): node %d name is (char *)0 and label is \"%s\"\n", __func__, node->nr, str);
				nname = "<nil-node-name>";
			} else {
				nname = node->name;
			}
			res2 = (char *)dp_calloc(1, ((len + 1) + (nn * strlen(nname))));
			/* substitute \N with node name */
			p = res;
			q = res2;
			while (*p) {
				if (*p == '\\') {
					if (*(p + 1) == 'N') {
						p2 = node->name;
						if (yydebug || 0) {
							printf("%s(): node name to substitute is \"%s\"\n", __func__, node->name);
						}
						while ((*p2)) {
							(*q) = (*p2);
							p2++;
							q++;
						}
						p++;
						p++;
					} else {
						(*q) = (*p);
						p++;
						q++;
					}
				} else {
					(*q) = (*p);
					p++;
					q++;
				}
			}
			ret = uniqstr(res2);
			res2 = dp_free(res2);
			if (res2) {
			}
			res = dp_free(res);
			if (res) {
			}
		} else {
			/* no node. then no node name. */
			ret = uniqstr(res);
			res = dp_free(res);
			if (res) {
			}
		}
	} else {
		/* no \N chars replaced */
		ret = uniqstr(res);
		res = dp_free(res);
		if (res) {
		}
	}

	return (ret);
}

/* */
static void prrl(struct gml_rl *info, int prrlind)
{
	int i = 0;
	if (info == NULL) {
		return;
	}
	for (i = 0; i < prrlind; i++) {
		printf("  ");
	}
	printf("hd=%d dir=%d `%s' `%s' nparts=%d\n", info->hd, info->dir, info->port, info->label, info->nparts);
	for (i = 0; i < info->nparts; i++) {
		prrlind++;
		prrl(info->parts[i], (prrlind + 1));
		prrlind--;
	}

	return;
}

/* copy record label data */
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
					     __func__, cursg->nr, cursg->graphname, cursg->rootedon->nr,
					     cursg->rootedon->graphname);
				}
				gl = dp_calloc(1, sizeof(struct gml_glist));

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
		printf("%s(): copy \"%s\" bgcolor 0x%x\n", __func__, ret->text, item->ncolor);
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
	if (item->bitflags.table) {
		/* set if str is a <table> token */
		ret->bitflags.table = 1;
		if (item->table) {
			/* get the copied <table> */
			ret->table = item->table->alt;
			if (yydebug || 0) {
				printf("%s(): got table %p\n", __func__, (void *)ret->table);
			}
		} else {
			/* shouldnothappen */
			printf("%s(): nil table\n", __func__);
		}
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
	printf("%s(): end of items in node \"%s\"\n", __func__, node->name);
	return;
}

/* copy html items list */
static struct gml_hl *hlicopy(struct dpnode *node)
{
	struct gml_hl *ret = NULL;
	struct ilist *il = NULL;
	struct gml_hilist *hil = NULL;
	struct hlpart *pp = NULL;
	if (node == NULL) {
		return (NULL);
	}
	ret = dp_calloc(1, sizeof(struct gml_hl));
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

/* copy html tables list */
static struct gml_htlist *hltcopy_r(struct tlist *tl, struct gml_htlist *htl, struct dpnode *node)
{
	struct trlist *trptr = NULL;
	struct tlist *tlptr = NULL;	/* list of table items */
	struct tdldata *tdptr = NULL;	/* td items in tr */
	struct ilist *ilptr = NULL;
	struct gml_titem *tinew = NULL;
	struct gml_htlist *tlnew = NULL;	/* list of sub table items */
	struct gml_tritemlist *tritemlistnew = NULL;
	struct gml_tritem *tritemnew = NULL;
	struct gml_tditem *tditemnew = NULL;
	struct gml_hilist *hilistnew = NULL;
	int numtr = 0;
	int numtd = 0;

	if (htl == NULL) {
		return (NULL);
	}

	if (tl->titem == NULL) {
		return (NULL);
	}

	if (tl->titem->tabdata == NULL) {
		return (NULL);
	}

	/* new gml table data */
	tinew = dp_calloc(1, sizeof(struct gml_titem));

	/* set the alt tbel in dp table data */
	tl->titem->tabdata->alt = tinew;

	htl->titem = tinew;

	/* first copy sub tables if any */
	if (tl->titem->tabdata->tl) {

		tlptr = tl->titem->tabdata->tl;
		while (tlptr) {

			/* */
			tlnew = dp_calloc(1, sizeof(struct gml_htlist));
			tlnew = hltcopy_r(tlptr, tlnew, node);
			if (tlnew->titem) {

				/* */
				if (htl->titem->tl == NULL) {
					htl->titem->tl = tlnew;
					htl->titem->tlend = tlnew;
				} else {
					htl->titem->tlend->next = tlnew;
					htl->titem->tlend = tlnew;
				}

			}

			tlptr = tlptr->next;
		}
	}

	/* copy the <tr> data if any */
	if (tl->titem->tabdata->tr) {
		numtr = 0;
		trptr = tl->titem->tabdata->tr;
		while (trptr) {
			tritemlistnew = dp_calloc(1, sizeof(struct gml_tritemlist));
			/* if there are <tr> items */
			if (trptr->tritem) {
				/* are there <td> in <tr> */
				if (trptr->tritem->td) {
					tritemnew = dp_calloc(1, sizeof(struct gml_tritem));
					tritemlistnew->tritem = tritemnew;
					/* set if <tr> has a <td> with a <table> */
					tritemnew->hastab = trptr->tritem->hastab;
					numtd = 0;
					tdptr = trptr->tritem->td;
					while (tdptr) {
						/* if actual <td> data */
						if (tdptr->tdd) {
							/* a <td> can have no items as in <td></td> then do not copy data */
							/* il list in <td> */
							if (tdptr->tdd->il) {

								tditemnew = dp_calloc(1, sizeof(struct gml_tditem));
								/* set if <td> is a <table> */
								tditemnew->istab = tdptr->tdd->istab;

								/* copy the il data */
								ilptr = tdptr->tdd->il;
								while (ilptr) {
									hilistnew = dp_calloc(1, sizeof(struct gml_hilist));
									hilistnew->items = hlimakecopy(ilptr->items, node);
									if (yydebug || 0) {
										printf("%s(): copy item \"%s\" bgcolor 0x%x\n",
										       __func__, ilptr->items->text,
										       ilptr->items->ncolor);
									}
									/* set which <table> this item is part of */
									hilistnew->items->rootedon = tinew;
									if (tditemnew->il == NULL) {
										tditemnew->il = hilistnew;
										tditemnew->ilend = hilistnew;
									} else {
										tditemnew->ilend->next = hilistnew;
										tditemnew->ilend = hilistnew;
									}
									ilptr = ilptr->next;
								}
								/* */

								/* set <table> of this <td> */
								tditemnew->rootedon = tinew;
								/* set data from input */
								tditemnew->bgcolor = tdptr->tdd->bgcolor;	/* ="colorname" */
								tditemnew->border = tdptr->tdd->border;	/* ="int-value" */
								tditemnew->cellpadding = tdptr->tdd->cellpadding;	/* ="int-value" */
								tditemnew->cellspacing = tdptr->tdd->cellspacing;	/* ="int-value" */
								tditemnew->color = tdptr->tdd->color;	/* ="colorname" */
								tditemnew->colspan = tdptr->tdd->colspan;	/* ="int-value" */
								tditemnew->height = tdptr->tdd->height;	/* ="int-value" */
								tditemnew->rowspan = tdptr->tdd->rowspan;	/* ="int-value" */
								tditemnew->width = tdptr->tdd->width;	/* ="int-value" */
								/* */
								if (tritemnew->tdi == NULL) {
									tritemnew->tdi = tditemnew;
									tritemnew->tdiend = tditemnew;
								} else {
									tritemnew->tdiend->next = tditemnew;
									tritemnew->tdiend = tditemnew;
								}
								/* */
								numtd++;
							}
						}
						/* */
						tdptr = tdptr->next;
					}
					/* */
					if (yydebug || 0) {
						printf("%s(): %d <td> in <tr>\n", __func__, numtd);
					}
					/* set number of <td> in this <tr> */
					tritemnew->numtd = numtd;
					/* set <table> of this <tr> */
					tritemnew->rootedon = tinew;
					/* */
				}
			}
			/* */
			if (htl->titem->tr == NULL) {
				htl->titem->tr = tritemlistnew;
				htl->titem->trend = tritemlistnew;
			} else {
				htl->titem->trend->next = tritemlistnew;
				htl->titem->trend = tritemlistnew;
			}
			/* */
			numtr++;	/* update count of <tr> in this <table> */
			trptr = trptr->next;
		}
		htl->titem->numtr = numtr;
	}

	/* copy input parms from <table> */
	htl->titem->bgcolor = tl->titem->tabdata->bgcolor;	/* background color */
	htl->titem->color = tl->titem->tabdata->color;	/* fontcolor */
	htl->titem->cellborder = tl->titem->tabdata->cellborder;	/* ="int-value" */
	htl->titem->cellpadding = tl->titem->tabdata->cellpadding;	/* ="int-value" */
	htl->titem->cellspacing = tl->titem->tabdata->cellspacing;	/* ="int-value" */
	htl->titem->height = tl->titem->tabdata->height;	/* ="int-value" */
	htl->titem->width = tl->titem->tabdata->width;	/* ="int-value" */

	return (htl);
}

/* copy html tables list */
static struct gml_hl *hltcopy(struct dpnode *node)
{
	struct gml_hl *ret = NULL;
	struct tlist *tl = NULL;	/* list of table items */
	struct gml_htlist *tlnew = NULL;	/* list of sub table items */
	struct gml_htlist *tlnew2 = NULL;	/* list of sub table items */

	if (node->hlinfo == NULL) {
		/* shouldnothappen */
		return (NULL);
	}

	if (node->hlinfo->tl == NULL) {
		/* shouldnothappen */
		return (NULL);
	}

	ret = dp_calloc(1, sizeof(struct gml_hl));

	/* this is table data */
	ret->mode = 1;

	/* scan the tables */
	tl = node->hlinfo->tl;

	if (yydebug || 0) {
		printf("%s(): node \"%s\" node->hlinfo=%p node->hlinfo->tl=%p\n", __func__, node->name,
		       (void *)node->hlinfo, (void *)tl);
	}

	while (tl) {
		tlnew = dp_calloc(1, sizeof(struct gml_htlist));
		tlnew2 = hltcopy_r(tl, tlnew, node);
		if (tlnew2) {
			if (ret->tl == NULL) {
				ret->tl = tlnew2;
				ret->tlend = tlnew2;
			} else {
				ret->tlend->next = tlnew2;
				ret->tlend = tlnew2;
			}
		} else {
			/* shouldnothappen */
			tlnew = dp_free(tlnew);
			if (tlnew) {
			}
		}
		tl = tl->next;
	}

	return (ret);
}

/* */
static void dpif_pr_out_sp(int ind)
{
	int i = 0;
	for (i = 0; i < ind; i++) {
		printf(" ");
	}
	return;
}

/* */
static void dpif_pr_out_t_r(struct gml_htlist *tl, int ind, int tabnum)
{
	struct gml_htlist *tlptr = NULL;	/* list of table items */
	struct gml_htlist *tlptrnext = NULL;	/* list of table items */
	int nts = 0;

	if (tl == NULL) {
		/* shouldnothappen */
		return;
	}

	nts = tabnum;
	dpif_pr_out_sp(ind);
	printf("<table>[%d]\n", tabnum);
	if (tl->titem == NULL) {
		printf("%s(): tl->titem is nil\n", __func__);
		/* shouldnothappen */
		return;
	}

	if (0) {
		printf("%s(): tl->titem->tl=%p\n", __func__, (void *)tl->titem->tl);
	}

	/* sub tables if any */
	if (tl->titem->tl) {
		tlptr = tl->titem->tl;
		while (tlptr) {
			tlptrnext = tlptr->next;
			dpif_pr_out_t_r(tlptr, (ind + 2), nts);
			nts++;
			tlptr = tlptrnext;
		}
	}

	/* <tr> data if any */
	if (tl->titem->tr) {
		dpif_pr_out_sp(ind);
		printf("has %d <tr>\n", tl->titem->numtr);
	}

	return;
}

/* print list data if any */
static void dpif_pr_out_tl(struct gml_hl *hl, struct dpnode *node)
{
	struct gml_htlist *tlptr;	/* list of table items */
	struct gml_htlist *tlptrnext;	/* list of table items */
	printf("%s(): copied table data of node\"%s\" with hl=%p\n", __func__, node->name, (void *)hl);
	if (hl == NULL) {
		return;
	}
	if (hl->tl == NULL) {
		printf("%s(): html table data is nil at node \"%s\"\n", __func__, node->name);
		return;
	}
	tlptr = hl->tl;
	while (tlptr) {
		tlptrnext = tlptr->next;
		dpif_pr_out_t_r(tlptr, 0, 1);
		tlptr = tlptrnext;
	}
	printf("%s(): end copied table data of node\"%s\"\n", __func__, node->name);
	return;
}

/* */
static void dpif_pr_in_sp(int ind)
{
	int i = 0;
	for (i = 0; i < ind; i++) {
		printf(" ");
	}
	return;
}

/* */
static void dpif_pr_in_1il(struct ilist *ildata, int ind, int tinum)
{
	char *iltext = NULL;
	if (ildata == NULL) {
		return;
	}

	dpif_pr_in_sp(ind);
	printf("<item>[%d]\n", tinum);
	if (ildata->items == NULL) {
		printf("%s(): ildata->items is nil\n", __func__);
		return;
	}
	if (ildata->items->text == NULL) {
		if (ildata->items->bitflags.br) {
			/* set if str is a <br/> token */
			iltext = "<br/>";
		} else if (ildata->items->bitflags.img) {
			/* set if str is a <img> */
			iltext = "<img>";
		} else if (ildata->items->bitflags.i) {
			/* set if str is <i> italic */
			iltext = "<i>";
		} else if (ildata->items->bitflags.u) {
			/* set if str is <u> underline */
			iltext = "<u>";
		} else if (ildata->items->bitflags.o) {
			/* set if str is <o> overline */
			iltext = "<o>";
		} else if (ildata->items->bitflags.s) {
			/* set if str is <s> strike-through */
			iltext = "<s>";
		} else if (ildata->items->bitflags.sub) {
			/* set if str is <sub> subscript */
			iltext = "<sub>";
		} else if (ildata->items->bitflags.sup) {
			/* set if str is <sup> superscript */
			iltext = "<sump>";
		} else if (ildata->items->bitflags.hr) {
			/* set if str is a <hr> token */
			iltext = "<hr>";
		} else if (ildata->items->bitflags.vr) {
			/* set if str is a <vr> token */
			iltext = "<vr>";
		} else if (ildata->items->bitflags.b) {
			/* set if str is <b> bold */
			iltext = "<b>";
		} else if (ildata->items->bitflags.table) {
			/* set if str is <table> */
			iltext = "<table>";
		} else {
			iltext = "unknown ildata->items->bitflags";
		}
	} else {
		iltext = ildata->items->text;
	}
	dpif_pr_in_sp(ind + 2);
	printf("\"%s\"\n", iltext);
	return;
}

/* free ilist */
static void dpif_pr_in_il(struct tdldata *td, int ind, int tdnum)
{
	struct ilist *ilptr = NULL;	/* text items in td or 0 */
	struct ilist *ilptrnext = NULL;	/* text items in td or 0 */
	int nti = 0;
	if (td == NULL) {
		return;
	}

	dpif_pr_in_sp(ind);
	printf("<td>[%d]\n", tdnum);
	if (td->tdd == NULL) {
		printf("%s(): td->tdd is nil\n", __func__);
		return;
	}
	if (td->tdd->il == NULL) {
		printf("%s(): td->tdd->il is nil\n", __func__);
	}

	nti++;
	ilptr = td->tdd->il;
	while (ilptr) {
		ilptrnext = ilptr->next;
		/* print 1 il */
		dpif_pr_in_1il(ilptr, (ind + 2), nti);
		ilptr = ilptrnext;
	}

	return;
}

/* free <tr> */
static void dpif_pr_in_tr(struct trlist *tr, int ind, int trnum)
{
	struct tdldata *tdlptr = NULL;	/* td items in tr */
	struct tdldata *tdlptrnext = NULL;
	int ntd = 0;
	if (tr == NULL) {
		return;
	}

	dpif_pr_in_sp(ind);
	printf("<tr>[%d]\n", trnum);
	if (tr->tritem == NULL) {
		printf("%s(): tr->tritem is nil\n", __func__);
		return;
	}

	if (tr->tritem->td == NULL) {
		printf("%s(): tr->tritem->td is nil\n", __func__);
		return;
	}

	ntd++;
	/* <td> data */
	tdlptr = tr->tritem->td;
	while (tdlptr) {
		tdlptrnext = tdlptr->next;
		dpif_pr_in_il(tdlptr, (ind + 2), ntd);
		ntd++;
		tdlptr = tdlptrnext;
	}

	return;
}

/* */
static void dpif_pr_in_t_r(struct tlist *tl, int ind, int tabnum)
{
	struct tlist *tlptr = NULL;	/* list of table items */
	struct tlist *tlptrnext = NULL;	/* list of table items */
	struct trlist *trptr = NULL;	/* tr items */
	struct trlist *trptrnext = NULL;	/* end tr items */
	int ntr = 0;
	int nts = 0;
	if (tl == NULL) {
		/* shouldnothappen */
		return;
	}

	nts = tabnum;
	dpif_pr_in_sp(ind);
	printf("<table>[%d]\n", tabnum);
	if (tl->titem == NULL) {
		printf("%s(): tl->titem is nil\n", __func__);
		/* shouldnothappen */
		return;
	}

	if (tl->titem->tabdata == NULL) {
		printf("%s(): tl->titem->tabdata is nil\n", __func__);
		return;
	}

	/* sub tables if any */
	if (tl->titem->tabdata->tl) {
		tlptr = tl->titem->tabdata->tl;
		while (tlptr) {
			tlptrnext = tlptr->next;
			dpif_pr_in_t_r(tlptr, (ind + 2), nts);
			nts++;
			tlptr = tlptrnext;
		}
	}

	/* <tr> data */
	if (tl->titem->tabdata->tr == NULL) {
		printf("%s(): tl->titem->tabdata->tr is nil\n", __func__);
		return;
	}

	ntr++;
	trptr = tl->titem->tabdata->tr;
	while (trptr) {
		trptrnext = trptr->next;
		dpif_pr_in_tr(trptr, (ind + 2), ntr);
		ntr++;
		trptr = trptrnext;
	}

	return;
}

/* print list data if any */
static void dpif_pr_in_tl(struct dpnode *node)
{
	struct tlist *tlptr;	/* list of table items */
	struct tlist *tlptrnext;	/* list of table items */
	if (node->hlinfo == NULL) {
		return;
	}
	if (node->hlinfo->tl == NULL) {
		printf("%s(): input html table data is nil at node \"%s\"\n", __func__, node->name);
		return;
	}
	printf("%s(): input html table data from node \"%s\" is:\n", __func__, node->name);
	tlptr = node->hlinfo->tl;
	while (tlptr) {
		tlptrnext = tlptr->next;
		dpif_pr_in_t_r(tlptr, 0, 1);
		tlptr = tlptrnext;
	}
	printf("%s(): input html table data end from node \"%s\"\n", __func__, node->name);
	return;
}

/* return node name with rand() chars */
static char *dp_randnname(void)
{
	char *ret = NULL;
	char buf[9];
	int i = 0;
	int count = 0;
	int rn = 0;
	struct dpnode *n = NULL;
	for (count = 0; count < 10; count++) {

		memset(buf, 0, 9);

		for (i = 0; i < 8; i++) {
			rn = (rand() & 0x07);
			if (rand() & 0x01) {
				buf[i] = ('a' + rn);
			} else {
				buf[i] = ('0' + rn);
			}
		}

		n = dpuniqnode(buf);
		if (n == NULL) {
			break;
		}
	}

	if (n) {
		return (NULL);
	}

	ret = dp_uniqstr(buf);

	return (ret);
}

/* parse dot file, 0 return if oke. */
int dotparse(struct gml_graph *g, gzFile f, char *fname, char *argv0)
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
	int nodehasrootname = 0;

	if (g) {
	}

	if (fname) {
	}

	/* static buffer for parser error message */
	memset(parsermessage, 0, 256);
	memset(dp_errmsg, 0, 256);

	dp_lex_init(f, yydebug);

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

	/* create copy of subgraphs */
	sp_crsg_r(dp_groot);
	/* add subgraphs to root graph */
	sp_addsg_r(dp_groot);
	/* list with all nodes */
	nss = dp_anodes;
	while (nss) {

		/* get node data */
		node = nss->n;
		/* graph where node is located */
		ro = uniqgraph(nss->n->root->nr);

		/* count how many nodes have a subgraph with actual name */
		if (ro->label) {
			if (strlen(ro->label)) {
				nodehasrootname++;
			}
		}

		/* node number as in gml graph
		 *  node->nr;
		 * using -1 does not apply the gml id check
		 */
		foundid = (-1);
		nodename = node->name;

		/* check if html label */
		if (nss->n->htmllabel) {
			ishtml = 1;
		} else {
			ishtml = 0;
			/* translate \n \r \l \N chars */
			nodelabel = dolabel(nss->n, nss->n->label);
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
			printf("%s(): ishtml is 1 but ns->n->hlinfo=%p for node \"%s\"\n", __func__,
			       (void *)nss->n->hlinfo, nss->n->name);
		}

		if (nss->n->hlinfo) {
			if (yydebug || 0) {
				printf("%s(): before-copy node \"%s\" mode=%d hlinfo=%p il=%p tl=%p\n", __func__,
				       node->name, nss->n->hlinfo->mode, (void *)nss->n->hlinfo,
				       (void *)nss->n->hlinfo->il, (void *)nss->n->hlinfo->tl);
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
				/* print input html table data */
				if (yydebug || 0) {
					dpif_pr_in_tl(nss->n);
				}
				/* html tables not-yet supported */
				hl = hltcopy(nss->n);
				if (yydebug || 0) {
					dpif_pr_out_tl(hl, nss->n);
				}
				if (nss->n->name == NULL) {
					/* shouldnothappen */
					nss->n->name = uniqstr("nil-node-name");
				}
			} else {
				printf("%s(): wrong html mode %d for node \"%s\"\n", __func__, nss->n->hlinfo->mode, nss->n->name);
			}
		} else if (nss->n->labelinfo) {
			/* this is a record label */
			if (nss->n->shape == DPSHAPE_RECORD || nss->n->shape == DPSHAPE_MRECORD) {
				/* can also be html label */
				if (ishtml) {
					/* todo copy html info in record hape */
					if (nss->n->labelinfo) {
					}
					printf("%s(): html in record node not yet supported ns->n->labelinfo=%p\n", __func__,
					       (void *)nss->n->labelinfo);
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
				printf("%s(): record label data for node \"%s\" is:\n", __func__, nss->n->name);
				prrl(rl, 0);
				printf("%s(): end of record label data for node \"%s\"\n", __func__, nss->n->name);
			}
			/* if html, print html label */
		}

		/* uniq node number starting at 1 */
		maingraph->nodenum++;
		nr = maingraph->nodenum;
		add_new_node(g, ro, nr, foundid, nodename, nodelabel, ncolor, nbcolor, rl, hl, fontcolor, ishtml);

		/* free dphl data at html label if any */
		if (hl) {
			dphl_freemem();
		}

		/* to next node. */
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

		/* update in/outdegree of nodes */
		if (edge->dir == DP_DIR_BACK) {
			/* backward edge */
			edge->fn->indegree++;
			edge->tn->outdegree++;
		} else {
			/* regular edge */
			edge->fn->outdegree++;
			edge->tn->indegree++;
		}

		if (edge->bitflags0.constraint) {
			econstraint = 1;
		} else {
			econstraint = 0;
		}

		/* econstraint is normally 1 */

		/* transform \n \l \r chars */
		elabel = dolabel(NULL, edge->label);

		/* check if html <> string */
		if (elabel) {
			if (strlen(elabel)) {
				/* todo edge html labels */
				elabel = uniqstr(elabel);
			} else {
				/* edgelabel "" is same as no-edge-label */
				elabel = NULL;
			}
		}

		/* at self-edge the edge color is put in the node ecolor
		 * if(edge->fn==edge->tn) this is a self-edge
		 */
		ecolor = edge->ecolor;

		/* edge line style */
		style = edge->style;
		fc = uniqstr(edge->fcompass);
		tc = uniqstr(edge->tcompass);
		add_new_edge(g, ro, foundsource, foundtarget, elabel, ecolor, style, fc, tc, econstraint, ishtml);
		es = es->next;
	}

	/* add artificial node for starter nodes when the rooted
	 * subgraph cluster has a label and add edge to startnode.
	 * this is needed for gcc rtl/tree/ipa data
	 */
	if (nodehasrootname) {

		/* init rand() */
		srand((unsigned int)time(NULL));
		/* list with all nodes */
		nss = dp_anodes;
		while (nss) {

			/* get node data */
			node = nss->n;
			/* check the starter nodes */
			if ((node->indegree == 0) && (node->outdegree != 0)) {
				if (node->root) {
					if (node->root->label) {
						if (strlen(node->root->label)) {

							/* todo html label for subgraph labels */

							if (yydebug || 0) {
								printf
								    ("%s(): node \"%s\" is rooted in cluster with label \"%s\" and adding artificial node\n",
								     __func__, node->name, node->root->label);
							}
							/* this node is a starter node with cluster label
							 * now add artifical node with cluster label
							 * add edge from artificial node to this node
							 */

							/* graph where node is located */
							ro = uniqgraph(node->root->nr);
							/* node name with rand() chars */
							nodename = dp_randnname();
							if (yydebug || 0) {
								printf
								    ("%s(): generating artificial startnode \"%s\" to point to node \"%s\"\n",
								     __func__, nodename, node->name);
							}

							/* set cluster label as node label */
							nodelabel = dolabel(NULL, node->root->label);
							/* node fill color white and bordercolor black */
							ncolor = 0x00ffffff;
							nbcolor = 0;
							fontcolor = 0;
							/* record or html data is currently not supported in cluster labels */
							rl = NULL;
							hl = NULL;
							ishtml = 0;
							/* uniq node number starting at 1 */
							maingraph->nodenum++;
							nr = maingraph->nodenum;
							/* node number as in gml graph 
							 * using -1 does not apply the gml id check.
							 */
							foundid = (-1);
							add_new_node(g, ro, nr, foundid, nodename, nodelabel, ncolor,
								     nbcolor, rl, hl, fontcolor, ishtml);
							/* add edge from artifical node to startnode */
							/* regular edge */
							foundsource = maingraph->nodenum;
							foundtarget = node->nr;
							econstraint = 1;
							elabel = NULL;
							ishtml = 0;
							ecolor = 0;
							style = 0;
							fc = NULL;
							tc = NULL;
							/* graph where edge is located */
							ro = uniqgraph(node->root->nr);
							add_new_edge(g, ro, foundsource, foundtarget, elabel, ecolor, style,
								     fc, tc, econstraint, ishtml);
						}
					}
				}
			}

			nss = nss->next;
		}

	}

	/* background r/g/b of drawing */
	if (dp_groot) {
		bgcolor = dp_groot->bgcolor;
		bgcr = (bgcolor & 0x00ff0000) >> 16;
		bgcg = (bgcolor & 0x0000ff00) >> 8;
		bgcb = (bgcolor & 0x000000ff);
	} else {
		/* white */
		bgcr = 0xff;
		bgcg = 0xff;
		bgcb = 0xff;
	}
	/* */
	dp_clearall();
	fflush(stdout);
	fflush(stderr);
	return (status);
}

/* end */
