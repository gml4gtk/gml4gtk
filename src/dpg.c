
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

/* graph attributes:
 *
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <math.h>
#include <zlib.h>

#include "splay-tree.h"
#include "dp.h"
#include "dpg.h"
#include "dpcolor.h"
#include "dpmisc.h"
#include "dot.tab.h"
#include "lex.yy.h"
#include "dpmem.h"

/* graph[] attribute to check
 * Damping K URL aspect bb bgcolor center charset
 * clusterrank color colorscheme comment compound
 * concentrate defaultdist dim dimen diredgeconstraints
 * dpi epsilon esep fillcolor fontcolor fontname
 * fontnames fontpath fontsize id label labeljust
 * labelloc landscape layers layersep layout levels
 * levelsgap lheight lp lwidth margin maxiter mclimit
 * mindist mode model mosek nodesep nojustify normalize
 * nslimit nslimit1 ordering orientation outputorder
 * overlap overlap_scaling pack packmode pad page pagedir
 * pencolor penwidth peripheries quadtree quantum rank
 * rankdir ranksep ratio remincross repulsiveforce
 * resolution root rotate searchsize sep showboxes
 * size smoothing sortv splines start style stylesheet
 * target tooltip truecolor viewport voro_margin
 * (and there are more then this)
 */

void dp_do_gattr(char *l, char *r)
{
	struct dpgraph *res = NULL;
	int cc = 0;
	int tmpi = 0;
	struct dpnum *num = NULL;
	struct dpcolor *colornum = NULL;
	struct dprect *rectnum = NULL;
	struct dpbool *boolnum = NULL;
	struct dppoint *pointnum = NULL;
	struct dpmargin *mnum = NULL;
	struct dpoo *oonum = NULL;
	struct dprank *ranknum = NULL;
	struct dprankdir *rankdirnum = NULL;
	struct dpranksep *ranksepnum = NULL;
	struct dpratio *rationum = NULL;
	struct dpsplines *splinesnum = 0;
	struct dpstyle *stylenum = NULL;

	res = dp_curgraph;

	/* switch on first char */
	cc = (*l);

	switch (cc) {
	case '_':
		if (strcmp(l, "_background") == 0) {
			/* xdot string */
		} else {
		}
		break;
		/* Damping */
	case 'D':
		if (strcmp(l, "Damping") == 0) {
			/* neato, not dot */
		} else {
		}
		break;
		/* Epsilon */
	case 'E':
		if (strcmp(l, "Epsilon") == 0) {
			/* neato, not dot */
		} else {
		}
		break;
		/* K */
	case 'K':
		if (strcmp(l, "K") == 0) {
			/* fdp, not dot */
		} else {
		}
		break;
		/* URL */
	case 'U':
		if (strcmp(l, "URL") == 0) {
			/* map svg */
			if (r) {
				if (strlen(r)) {
					res->url = r;
				} else {
					/* using "" turns off */
					res->url = NULL;
				}
				res->bitflags0.urlset = 1;
			}
		} else {
		}
		break;
		/* aspect */
	case 'a':
		if (strcmp(l, "aspect") == 0) {
			/* huh? */
		} else {
		}
		break;
		/* bb bgcolor */
	case 'b':
		if (strcmp(l, "bb") == 0) {
			/* rect area example: graph [bb="0,0,1216.6,1032"]; */
			rectnum = dp_getrect(r);
			res->bb = r;
			if (rectnum->pe) {
				if (rectnum->es) {
					/* at "" set default */
					res->bbx0 = 0;
					res->bby0 = 0;
					/* todo some hi number */
					res->bbx1 = 54;
					res->bby1 = 108;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for bb at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				res->bbx0 = rectnum->x0;
				res->bby0 = rectnum->y0;
				res->bbx1 = rectnum->x1;
				res->bby1 = rectnum->y1;
				if (res->bbx0 < 0 || res->bby0 < 0 || res->bbx1 < 0 || res->bby1 < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for bb at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					if (res->bbx1 < res->bbx0 || res->bby1 < res->bby0) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): second number `%s' is lower the first number for bb at line %d\n",
							 __func__, r, res->yylineno);
					}
				}
			}
			res->bitflags0.bbset = 1;
			rectnum = (struct dprect *)dp_free((void *)rectnum);
			if (rectnum) {
			}
		} else if (strcmp(l, "bgcolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default white color */
					res->bgcolor = 0x00ffffff;
					res->bitflags0.bgcolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' for bgcolor at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default white color */
					res->bgcolor = 0x00ffffff;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->bgcolor = colornum->color;
				}
				res->bitflags0.bgcolorset = 1;
			}
			colornum = (struct dpcolor *)dp_free((void *)colornum);
			if (colornum) {
			}
		} else {
		}
		break;
		/* center charset clusterrank color colorscheme comment compound concentrate */
	case 'c':
		if (strcmp(l, "center") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.center = 0;
					res->bitflags0.centerset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for center at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.center = 1;
				} else {
					res->bitflags0.center = 0;
				}
				res->bitflags0.centerset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "charset") == 0) {
			if (r) {
				if (strlen(r)) {
					res->charset = r;
				} else {
					/* using "" turns off default utf8 */
					res->charset = NULL;
				}
				res->bitflags0.charsset = 1;
			}
		} else if (strcmp(l, "clusterrank") == 0) {
			/* cluster mode, none, local, global */
			tmpi = dp_getclrank(r);
			if (tmpi == (-1)) {
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "dot %s(): unknown name `%s' for clusterrank at line %d\n", __func__, r, res->yylineno);
			} else {
				res->clrank = tmpi;
				res->bitflags0.clrankset = 1;
			}
		} else if (strcmp(l, "color") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default white color */
					res->color = 0x00ffffff;
					res->bitflags0.colorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' for color at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default white color */
					res->color = 0x00ffffff;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->color = colornum->color;
				}
				res->bitflags0.colorset = 1;
			}
			colornum = (struct dpcolor *)dp_free((void *)colornum);
			if (colornum) {
			}
		} else if (strcmp(l, "colorscheme") == 0) {
			tmpi = dp_colorschemecode(r);
			if (tmpi == (-1)) {
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "dot %s(): syntax error invalid name of colorscheme `%s' near line %d\n",
					 __func__, r, yylineno);
				/* continue and error message will soon appear */
			} else {
				/* number oke for colorscheme */
				res->csnum = tmpi;
				res->bitflags0.csnumset = 1;
			}
		} else if (strcmp(l, "comment") == 0) {
			if (r) {
				if (strlen(r)) {
					res->comment = r;
				} else {
					/* using "" turns off default */
					res->comment = NULL;
				}
				res->bitflags0.commset = 1;
			}
		} else if (strcmp(l, "compound") == 0) {
			/* allow edges between clusters */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default false */
					res->bitflags0.compound = 0;
					res->bitflags0.compset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for compound at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.compound = 1;
				} else {
					res->bitflags0.compound = 0;
				}
				res->bitflags0.compset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "concentrate") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default false */
					res->bitflags0.concentrate = 0;
					res->bitflags0.concenset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for concentrate at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.concentrate = 1;
				} else {
					res->bitflags0.concentrate = 0;
				}
				res->bitflags0.concenset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else {
		}
		break;
		/* defaultdist dim dimen diredgeconstraints dpi */
	case 'd':
		if (strcmp(l, "defaultdist") == 0) {
			/* neato */
		} else if (strcmp(l, "dim") == 0) {
			/* neato */
		} else if (strcmp(l, "dimen") == 0) {
			/* neato */
		} else if (strcmp(l, "diredgeconstraints") == 0) {
			/* neato */
		} else if (strcmp(l, "dpi") == 0) {
			/* svg 96 */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->dpi = 96;
					res->bitflags0.dpiset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for dpi at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for dpi at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->dpi = num->number;
					res->bitflags0.dpiset = 1;
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* epsilon esep */
	case 'e':
		if (strcmp(l, "epsilon") == 0) {
			/* neato, not dot */
		} else if (strcmp(l, "esep") == 0) {
			/* not dot */
		} else {
		}
		break;
		/* fillcolor fontcolor fontname fontnames fontpath fontsize */
	case 'f':
		if (strcmp(l, "fillcolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default white color */
					res->fcolor = 0x00ffffff;
					res->bitflags0.fcolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' for fillcolor at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default white color */
					res->fcolor = 0x00ffffff;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->fcolor = colornum->color;
				}
				res->bitflags0.fcolorset = 1;
			}
			colornum = (struct dpcolor *)dp_free((void *)colornum);
			if (colornum) {
			}
		} else if (strcmp(l, "fontcolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->fontcolor = 0x00000000;
					res->bitflags0.fontcolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' for fontcolor at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->fontcolor = 0x00000000;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->fontcolor = colornum->color;
				}
				res->bitflags0.fontcolorset = 1;
			}
			colornum = (struct dpcolor *)dp_free((void *)colornum);
			if (colornum) {
			}
		} else if (strcmp(l, "fontname") == 0) {
			if (r) {
				if (strlen(r)) {
					res->fontname = r;
				} else {
					/* using "" turns off default */
					res->fontname = NULL;
				}
				res->bitflags0.fontnameset = 1;
			}
		} else if (strcmp(l, "fontnames") == 0) {
			/* svg only */
		} else if (strcmp(l, "fontpath") == 0) {
			if (r) {
				if (strlen(r)) {
					res->fontpath = r;
				} else {
					/* using "" turns off default */
					res->fontpath = NULL;
				}
				res->bitflags0.fontpathset = 1;
			}
		} else if (strcmp(l, "fontsize") == 0) {
			/* size of font */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->fontsize = 14;
					res->bitflags0.fontsizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse fontsize number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number >= 1.0) {
					/* round to int in double format */
					res->fontsize = rint(num->number);
					res->bitflags0.fontsizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): fontsize number `%s' at line %d is too low, minimum is 1.0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* id */
	case 'i':
		if (strcmp(l, "id") == 0) {
			/* imagemap id's */
			if (r) {
				if (strlen(r)) {
					res->id = r;
				} else {
					res->id = NULL;
				}
				res->bitflags0.idset = 1;
			}
		} else {
		}
		break;
		/* label labeljust labelloc landscape layers layersep layout levels levelsgap lheight lp lwidth */
	case 'l':
		if (strcmp(l, "label") == 0) {
			if (r) {
				if (strlen(r)) {
					res->label = r;
				} else {
					/* label="" does empty the label text */
					/* dot sets few spaces at "" to get ellipse default shape */
					res->label = NULL;
				}
				res->bitflags0.labelset = 1;
			}
		} else if (strcmp(l, "labeljust") == 0) {
			/* label justify for cluster is l,r or other center */
			if (r) {
				if (strlen(r)) {
					res->labelj = r;
				} else {
					res->labelj = (char *)"c";
				}
				res->bitflags0.labeljset = 1;
			}
		} else if (strcmp(l, "labelloc") == 0) {
			/* location of label */
			tmpi = dp_islabelloc(r);
			if (r == 0) {
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "dot %s(): not a location `%s' for labelloc at line %d\n", __func__, r, res->yylineno);
			} else {
				res->labelloc = tmpi;
				res->bitflags0.labellset = 1;
			}
		} else if (strcmp(l, "landscape") == 0) {
			/* oreintation=landscape or rotate90 */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default false */
					res->bitflags0.landscape = 0;
					res->bitflags0.landscset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for landscape at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.landscape = 1;
				} else {
					res->bitflags0.landscape = 0;
				}
				res->bitflags0.landscset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "layers") == 0) {
			if (r) {
				if (strlen(r)) {
					res->layers = r;
				} else {
					res->layers = NULL;
				}
				res->bitflags0.layersset = 1;
			}
		} else if (strcmp(l, "layerlistsep") == 0) {
			/* seperator chars for layers list */
			if (r) {
				if (strlen(r)) {
					res->layerls = r;
				} else {
					res->layerls = (char *)",";
				}
				res->bitflags0.layerlsset = 1;
			}
		} else if (strcmp(l, "layersep") == 0) {
			/* seperator chars for layers */
			if (r) {
				if (strlen(r)) {
					res->layersep = r;
				} else {
					res->layersep = (char *)":\t";
				}
				res->bitflags0.layersepset = 1;
			}
		} else if (strcmp(l, "layerselect") == 0) {
			if (r) {
				if (strlen(r)) {
					res->layersel = r;
				} else {
					res->layersel = NULL;
				}
				res->bitflags0.layerselset = 1;
			}
		} else if (strcmp(l, "layout") == 0) {
			/* layout type, "dot" or "neato" */
			if (r) {
				if (strlen(r)) {
					res->layout = r;
				} else {
					/* defaults to dot */
					res->layout = NULL;
				}
				res->bitflags1.layoutset = 1;
			}
		} else if (strcmp(l, "levels") == 0) {
			/* sfdp */
		} else if (strcmp(l, "levelsgap") == 0) {
			/* neato */
		} else if (strcmp(l, "lheight") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->lheight = 0;	/* todo what is the default? */
					res->bitflags1.lhset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse lheight number `%s' at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number >= 0) {
					/*  */
					res->lheight = num->number;
					res->bitflags1.lhset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): lheight number `%s' at line %d is too low, minimum is 0.0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "lp") == 0) {
			if (r) {
				if (strlen(r)) {
					res->lp = r;
					pointnum = dp_getpoint(r);
					if (pointnum->pe) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): cannot parse lp (x,y) number `%s' at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->lpx = pointnum->x;
						res->lpy = pointnum->y;
						res->lpflag = pointnum->flag;
					}
					pointnum = (struct dppoint *)dp_free((void *)pointnum);
					if (pointnum) {
					}
				} else {
					res->lp = NULL;
					res->lpx = 0;
					res->lpy = 0;
					res->lpflag = 0;
				}
				res->bitflags1.lpset = 1;
			}
		} else if (strcmp(l, "lwidth") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->lwidth = 0;	/* todo ? */
					res->bitflags1.lwset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse lwidth number `%s' at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number >= 0.0) {
					/* */
					res->lwidth = num->number;
					res->bitflags1.lwset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): lwidth number `%s' at line %d is too low, minimum is 0.0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* margin maxiter mclimit mindist mode model mosek */
	case 'm':
		if (strcmp(l, "margin") == 0) {
			if (r) {
				if (dp_chknum(r)) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a number `%s' for margin at line %d\n", __func__, r, res->yylineno);
				} else {
					res->margin = r;
					mnum = dp_getmargin(r);
					if (mnum->pe) {
						if (mnum->es) {
							res->margin = NULL;
							res->marginx = 0;	/* todo default values */
							res->marginy = 0;
						} else {
							memset(dp_errmsg, 0, 256);
							snprintf(dp_errmsg, (256 - 1),
								 "dot %s(): cannot parse margin number `%s' at line %d\n",
								 __func__, r, res->yylineno);
						}
					} else {
						if (mnum->x < 0 || mnum->y < 0) {
							memset(dp_errmsg, 0, 256);
							snprintf(dp_errmsg, (256 - 1),
								 "dot %s(): not allowed negative number `%s' for margin at line %d\n",
								 __func__, r, res->yylineno);
						} else {
							res->marginx = mnum->x;
							res->marginy = mnum->y;
						}
					}
					res->bitflags1.marginset = 1;
					mnum = (struct dpmargin *)dp_free((void *)mnum);
					if (mnum) {
					}
				}
			}
		} else if (strcmp(l, "maxiter") == 0) {
			/* neato */
		} else if (strcmp(l, "mclimit") == 0) {
			/* factor to stop layout */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->mclimit = 1;
					res->bitflags1.mcset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse mclimit number `%s' at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number >= 0.0) {
					/* */
					res->mclimit = num->number;
					res->bitflags1.mcset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): mclimit number `%s' at line %d is too low, minimum is 0.0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "mindist") == 0) {
			/* circo */
		} else if (strcmp(l, "mode") == 0) {
			/* neato */
		} else if (strcmp(l, "model") == 0) {
			/* neato */
		} else if (strcmp(l, "mosek") == 0) {
			/* neato */
		} else {
		}
		break;
		/* nodesep nojustify normalize nslimit nslimit1 */
	case 'n':
		if (strcmp(l, "newrank") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default false */
					res->bitflags1.newrank = 0;
					res->bitflags1.nrankset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for newrank at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.newrank = 1;
				} else {
					res->bitflags1.newrank = 0;
				}
				res->bitflags1.nrankset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "nodesep") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->nodesep = 0.25;
					res->bitflags1.nsepset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse nodesep number `%s' at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number >= 0.02) {
					/* */
					res->nodesep = num->number;
					res->bitflags1.nsepset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): nodesep number `%s' at line %d is too low, minimum is 0.02\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "nojustify") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default false */
					res->bitflags1.nojustify = 0;
					res->bitflags1.nojustset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for nojustify at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.nojustify = 1;
				} else {
					res->bitflags1.nojustify = 0;
				}
				res->bitflags1.nojustset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "normalize") == 0) {
			/* not dot */
		} else if (strcmp(l, "notranslate") == 0) {
			/* neato */
		} else if (strcmp(l, "nslimit") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->nslimit = 0;
					res->bitflags1.nsset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse nslimit number `%s' at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number >= 0) {
					/* */
					res->nslimit = rint(num->number);
					res->bitflags1.nsset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): nslimit number `%s' at line %d is too low, minimum is 0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "nslimit1") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->nslimit1 = 0;
					res->bitflags1.ns1set = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse nslimit1 number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number >= 0) {
					/* */
					res->nslimit1 = rint(num->number);
					res->bitflags1.ns1set = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): nslimit1 number `%s' at line %d is too low, minimum is 0\n",
						 __func__, r, res->yylineno);
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* ordering orientation outputorder overlap overlap_ */
	case 'o':
		if (strcmp(l, "ordering") == 0) {
			if (r) {
				/* valid in,out or "" */
				if ((strcasecmp(r, "in") == 0) || (strcasecmp(r, "out") == 0)
				    || (strlen(r) == 0)) {
					if (strlen(r)) {
						res->ordering = r;
					} else {
						res->ordering = NULL;;
					}
					res->bitflags1.orderset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse ordering string `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			}
		} else if (strcmp(l, "orientation") == 0) {
			/* landscape mode */
			if (r) {
				if (strlen(r)) {
					res->orientation = r;
				} else {
					/* defaults */
					res->orientation = NULL;
				}
				res->bitflags1.oriset = 1;
			}
		} else if (strcmp(l, "outputorder") == 0) {
			oonum = dp_getoo(r);
			if (oonum->pe) {
				if (oonum->es) {
					res->oorder = 0;	/* means undefined */
					res->bitflags1.ooset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse outputorder string `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				res->oorder = oonum->mode;
				res->bitflags1.ooset = 1;
			}
			oonum = (struct dpoo *)dp_free((void *)oonum);
			if (oonum) {
			}
		} else if (strcmp(l, "overlap") == 0) {
			/* not dot */
		} else if (strcmp(l, "overlap_") == 0) {
			/* not dot */
		} else {
		}
		break;
		/* pack packmode pad page pagedir pencolor penwidth peripheries */
	case 'p':
		if (strcmp(l, "pack") == 0) {
			/* pack arg can be boolean or a positive number as a margin */
			if (r) {
				if (strlen(r)) {
					boolnum = dp_getbool(r);
					if (boolnum->pe) {
						/* not bool, try number */
						num = dp_getnum(r);
						if (num->pe) {
							memset(dp_errmsg, 0, 256);
							snprintf(dp_errmsg, (256 - 1),
								 "dot %s(): cannot parse pack number or boolean `%s' at line %d\n",
								 __func__, r, res->yylineno);
						} else {
							if (num->number >= 0) {
								/* */
								res->pack = rint(num->number);
								res->bitflags1.packset = 1;
							} else {
								memset(dp_errmsg, 0, 256);
								snprintf(dp_errmsg, (256 - 1),
									 "dot %s(): pack number `%s' at line %d is too low, minimum is 0\n",
									 __func__, r, res->yylineno);
							}
						}
						num = (struct dpnum *)dp_free((void *)num);
						if (num) {
						}
					} else {
						/* arg is a boolean true/false */
						if (boolnum->number) {
							/* todo, correct pack value here? */
							res->pack = 1;
						} else {
							res->pack = 0;
						}
						res->bitflags1.packset = 1;
					}
					boolnum = (struct dpbool *)dp_free((void *)boolnum);
					if (boolnum) {
					}
				} else {
					/* at "" */
					res->pack = 0;
					res->bitflags1.packset = 1;
				}
			}
		} else if (strcmp(l, "packmode") == 0) {
			/* scc packing mode, todo parse the string */
			if (r) {
				if (strlen(r)) {
					res->packmode = r;
				} else {
					/* defaults */
					res->packmode = NULL;
				}
				res->bitflags1.packmset = 1;
			}
		} else if (strcmp(l, "pad") == 0) {
			/* one or two numbers for room around drawing */
			/* todo parse the string */
			if (r) {
				if (strlen(r)) {
					res->pad = r;
				} else {
					/* defaults */
					res->pad = NULL;
				}
				res->bitflags1.padset = 1;
			}
		} else if (strcmp(l, "page") == 0) {
			/* postscript only */
		} else if (strcmp(l, "pagedir") == 0) {
			/* postscript only */
		} else if (strcmp(l, "pencolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->pencolor = 0x00000000;
					res->bitflags0.pencolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' for pencolor at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->pencolor = 0x00000000;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->pencolor = colornum->color;
				}
				res->bitflags0.pencolorset = 1;
			}
			colornum = (struct dpcolor *)dp_free((void *)colornum);
			if (colornum) {
			}
		} else if (strcmp(l, "penwidth") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->penwidth = 1;
					res->bitflags0.penwidthset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for penwidth at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* penwidth 0 is oke */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for penwidth at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->penwidth = num->number;
					res->bitflags0.penwidthset = 1;
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "peripheries") == 0) {
			/* for clusters, max 1, default 1 */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->peripheries = 1;
					res->bitflags1.periset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for peripheries at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				/* 0 is oke */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for peripheries at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->peripheries = num->number;
					res->bitflags1.periset = 1;
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* quadtree quantum */
	case 'q':
		if (strcmp(l, "quadtree") == 0) {
			/* sfdp */
		} else if (strcmp(l, "quantum") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->quantum = 1;
					res->bitflags1.quanset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for quantum at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* 0 is oke */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for quantum at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->quantum = num->number;
					res->bitflags1.quanset = 1;
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else {
		}
		break;
		/* rank rankdir ranksep ratio remincross repulsiveforce resolution root rotate */
	case 'r':
		if (strcmp(l, "rank") == 0) {
			ranknum = dp_getrank(r);
			if (ranknum->pe) {
				if (ranknum->es) {
					res->rank = 0;
					res->bitflags1.rankset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown type `%s' for rank at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				res->rank = ranknum->mode;
				res->bitflags1.rankset = 1;
			}
			ranknum = (struct dprank *)dp_free((void *)ranknum);
			if (ranknum) {
			}
		} else if (strcmp(l, "rankdir") == 0) {
			rankdirnum = dp_getrankdir(r);
			if (rankdirnum->pe) {
				if (rankdirnum->es) {
					res->rankdir = 0;
					res->bitflags1.rankdset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown type `%s' for rankdir at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				res->rank = rankdirnum->mode;
				res->bitflags1.rankdset = 1;
			}
			rankdirnum = (struct dprankdir *)dp_free((void *)rankdirnum);
			if (rankdirnum) {
			}
		} else if (strcmp(l, "ranksep") == 0) {
			ranksepnum = dp_getranksep(r);
			if (ranksepnum->pe) {
				if (ranksepnum->es) {
					res->ranksep = 0.5;
					res->bitflags1.ranksset = 1;
					res->bitflags1.rankseq = ranksepnum->eq;	/* 0 or 1 */
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for ranksep at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (ranksepnum->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for ranksep at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->ranksep = ranksepnum->number;
					res->bitflags1.ranksset = 1;
					res->bitflags1.rankseq = ranksepnum->eq;	/* 0 or 1 */
				}
			}
			ranksepnum = (struct dpranksep *)dp_free((void *)ranksepnum);
			if (ranksepnum) {
			}
		} else if (strcmp(l, "ratio") == 0) {
			rationum = dp_getratio(r);
			if (rationum->pe) {
				if (rationum->es) {
					res->ratio = 0;
					res->ratiomode = 0;
					res->bitflags1.ratioset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number or mode `%s' for ratio at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (rationum->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for ratio at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->ratio = rationum->number;
					res->ratiomode = rationum->mode;
					res->bitflags1.ratioset = 1;
				}
			}
			rationum = (struct dpratio *)dp_free((void *)rationum);
			if (rationum) {
			}
		} else if (strcmp(l, "remincross") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default true */
					res->bitflags1.remincross = 1;
					res->bitflags1.remset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for remincross at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.remincross = 1;
				} else {
					res->bitflags1.remincross = 0;
				}
				res->bitflags1.remset = 1;
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else if (strcmp(l, "repulsiveforce") == 0) {
			/* sfdp */
		} else if (strcmp(l, "resolution") == 0) {
			/* same as dpi, svg 96 */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->dpi = 96;
					res->bitflags0.dpiset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for resolution at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for resolution at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->dpi = num->number;
					res->bitflags0.dpiset = 1;
				}
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "root") == 0) {
			/* circo */
		} else if (strcmp(l, "rotate") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->rotate = 0;
					res->bitflags1.rotset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for rotate at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				res->rotate = rint(num->number);
				res->bitflags1.rotset = 1;
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "rotation") == 0) {
			/* sfdp */
		} else {
		}
		break;
		/* scaling searchsize sep showboxes size smoothing sortv splines start style stylesheet */
	case 's':
		if (strcmp(l, "scale") == 0) {
			/* not dot */
		} else if (strcmp(l, "scaling") == 0) {
			/* ? not dot */
		} else if (strcmp(l, "searchsize") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->ssize = 30;
					res->bitflags1.ssizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for searchsize at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				res->ssize = rint(num->number);
				res->bitflags1.ssizeset = 1;
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "sep") == 0) {
			/* not dot */
		} else if (strcmp(l, "showboxes") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->sboxes = 0;
					res->bitflags1.sboxesset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for showboxes at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				res->sboxes = rint(num->number);
				res->bitflags1.sboxesset = 1;
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "size") == 0) {
			if (r) {
				if (strlen(r)) {
					pointnum = dp_getpoint(r);
					if (pointnum->pe) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): cannot parse size (x,y) number `%s' at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->sizex = pointnum->x;
						res->sizey = pointnum->y;
						res->sizeflag = pointnum->flag;
					}
					pointnum = (struct dppoint *)dp_free((void *)pointnum);
					if (pointnum) {
					}
				} else {
					res->sizex = 0;
					res->sizey = 0;
					res->sizeflag = 0;
				}
				res->bitflags1.sizeset = 1;
			}
		} else if (strcmp(l, "smoothing") == 0) {
			/* sfdp */
		} else if (strcmp(l, "sortv") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->sortv = 0;
					res->bitflags2.sortvset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for sortv at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				res->sortv = rint(num->number);
				res->bitflags2.sortvset = 1;
			}
			num = (struct dpnum *)dp_free((void *)num);
			if (num) {
			}
		} else if (strcmp(l, "splines") == 0) {
			splinesnum = dp_getsplines(r);
			if (splinesnum->pe) {
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "dot %s(): unknown type `%s' for splines at line %d\n", __func__, r, res->yylineno);
			} else {
				res->splines = splinesnum->mode;
				res->bitflags2.splinesset = 1;
			}
			splinesnum = (struct dpsplines *)dp_free((void *)splinesnum);
			if (splinesnum) {
			}
		} else if (strcmp(l, "start") == 0) {
			/* neato */
		} else if (strcmp(l, "style") == 0) {
			stylenum = dp_getstyle(r);
			if (stylenum->pe) {
				if (stylenum->es) {
					/* at "" clear all */
					res->bitflags2.styleset = 1;
					res->bitflags2.dashed = 0;
					res->bitflags2.dashedset = 1;
					res->bitflags2.dotted = 0;
					res->bitflags2.dottedset = 1;
					res->bitflags2.solid = 0;
					res->bitflags2.solidset = 1;
					res->bitflags2.bold = 0;
					res->bitflags2.boldset = 1;
					res->bitflags2.filled = 0;
					res->bitflags2.filledset = 1;
					res->bitflags2.striped = 0;
					res->bitflags2.stripedset = 1;
					res->bitflags2.rounded = 0;
					res->bitflags2.roundedset = 1;
					res->penwidth = 1;
					res->bitflags0.penwidthset = 1;
				} else {
					if (stylenum->pe_unk) {
						/* parse error at unknown token */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): unknown token `%s' in `%s' for style at line %d\n",
							 __func__, stylenum->unknown, r, res->yylineno);
					} else if (stylenum->pe_slw) {
						/* parse error at setlinewidth number */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): unknown number or negative number `%s' for setlinewidth in style at line %d\nuse penwidth instead of setlinewidth.\n",
							 __func__, r, res->yylineno);
					} else if (stylenum->pe_exp) {
						/* missing number at setlinewidth */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): missing number `%s' for setlinewidth in style at line %d\nuse penwidth instead of setlinewidth.\n",
							 __func__, r, res->yylineno);
					} else {
						/* other parse error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): unknown error in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					}
				}
			} else {
				/*  int slwset;         set if setlinewidth N */
				/*  double slw;         setlinewidth number */
				/*  int dashed;         "dashed" parsed N+E+G */
				/*  int dotted;         "dotted" parsed N+E+G */
				/*  int solid;          "solid" parsed N+E+G */
				/*  int invis;          "invis" parsed N+E */
				/*  int bold;           "bold" parsed N+E+G */
				/*  int tapered;        "tapered" parsed E */
				/*  int filled;         "filled" parsed N+G */
				/*  int striped;        "striped" parsed N+G */
				/*  int wedged;         "wedged" parsed N */
				/*  int diagonals;      "diagonals" parsed N */
				/*  int rounded;        "rounded" parsed N+C+G */
				/*  int radial;         "radial" parsed N */

				if (stylenum->invis) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): invis does not apply to graph in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						/* as warning */
						printf("dot %s(): invis does not apply to graph in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->tapered) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): tapered does not apply to graph in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						/* as warning */
						printf("dot %s(): tapered does not apply to graph in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->wedged) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): wedged does not apply to graph in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						/* as warning */
						printf("dot %s(): wedged does not apply to graph in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->diagonals) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): diagonals does not apply to graph in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						/* as warning */
						printf("dot %s(): diagonals does not apply to graph in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->radial) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): radial does not apply to graph in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						/* as warning */
					}
				} else {
					if (stylenum->slwset) {
						if (stylenum->slw < 0) {
							memset(dp_errmsg, 0, 256);
							snprintf(dp_errmsg, (256 - 1),
								 "dot %s(): negative number `%s' for setlinewidth in style at line %d\nuse penwidth instead of setlinewidth.\n",
								 __func__, r, res->yylineno);
						} else {
							res->penwidth = stylenum->slw;
							res->bitflags0.penwidthset = 1;
						}
					}
					res->bitflags2.styleset = 1;
					if (stylenum->dashed) {
						res->bitflags2.dashed = 1;
						res->bitflags2.dashedset = 1;
					}
					if (stylenum->dotted) {
						res->bitflags2.dotted = 1;
						res->bitflags2.dottedset = 1;
					}
					if (stylenum->solid) {
						res->bitflags2.solid = 1;
						res->bitflags2.solidset = 1;
					}
					if (stylenum->bold) {
						res->bitflags2.bold = 1;
						res->bitflags2.boldset = 1;
					}
					if (stylenum->filled) {
						res->bitflags2.filled = 1;
						res->bitflags2.filledset = 1;
					}
					if (stylenum->striped) {
						res->bitflags2.striped = 1;
						res->bitflags2.stripedset = 1;
					}
					if (stylenum->rounded) {
						res->bitflags2.rounded = 1;
						res->bitflags2.roundedset = 1;
					}
				}
			}
			stylenum = (struct dpstyle *)dp_free((void *)stylenum);
			if (stylenum) {
			}
		} else if (strcmp(l, "stylesheet") == 0) {
			/* svg */
		} else {
		}
		break;
		/* target tooltip truecolor */
	case 't':
		if (strcmp(l, "target") == 0) {
			/* svg */
		} else if (strcmp(l, "tooltip") == 0) {
			/* svg */
		} else if (strcmp(l, "truecolor") == 0) {
			/* bitmap output */
		} else {
		}
		break;
		/* viewport voro_margin */
	case 'v':
		if (strcmp(l, "viewport") == 0) {
			/* viewport numbers, todo to parse string */
			if (r) {
				res->viewport = r;
				res->bitflags2.vpset = 1;
			}
		} else if (strcmp(l, "voro_margin") == 0) {
			/* not dot */
		} else {
		}
		break;
	case 'x':
		if (strcmp(l, "xdotversion") == 0) {
			/* xdot only */
		} else {
			/* something else */
		}
		break;
		/* yydebug */
	case 'y':
		if (strcmp(l, "yydebug") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* debug off */
					dp_yydebug(0);
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for yydebug at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					/* debug on */
					dp_yydebug(1);
				} else {
					/* debug off */
					dp_yydebug(0);
				}
			}
			boolnum = (struct dpbool *)dp_free((void *)boolnum);
			if (boolnum) {
			}
		} else {
		}
		break;

	default:
		/* something else */
		break;
	}

	return;
}

/* set factory default */
void dp_graphfdef(struct dpgraph *g)
{
	/* white rgb */
	g->bgcolor = 0x00ffffff;
	g->bitflags0.bgcolorset = 1;

	g->penwidth = 1;
	g->bitflags0.penwidthset = 1;

	/* bb number */
	/* at "" set default */
	g->bbx0 = 0;
	g->bby0 = 0;
	/* todo some hi number */
	g->bbx1 = 54;
	g->bby1 = 108;
	g->bitflags0.bbset = 1;

	/* url is (char *)0 */

	/* center is 0 false */

	/* charset is (char *)0 utf8 */

	/* clusterrank is default int 0 is local */

	/* comment is (char *)0 */

	/* compound is 0 false bool */

	/* concentrate is 0 false bool */

	/* dpi */
	g->dpi = 96;
	g->bitflags0.dpiset = 1;

	/* fontname is (char *)0 "times-Roman" */

	/* fontpath is (char *)0 */

	/* fontsize is min. 1 */
	g->fontsize = 14;
	g->bitflags0.fontsizeset = 1;

	/* id is (char *)0 */

	/* label is (char *)0 */

	/* labeljust is center */
	g->labelj = (char *)"c";
	g->bitflags0.labeljset = 1;

	/* labelloc graph location is bottom */
	g->labelloc = DP_LLB;
	g->bitflags0.labellset = 1;

	/* landscape is 0 false bool */

	/* layers is (char *)0 */

	/* layerlistsep */
	g->layerls = (char *)",";
	g->bitflags0.layerlsset = 1;

	/* layersep */
	g->layersep = (char *)":\t";
	g->bitflags0.layersepset = 1;

	/* layerselect is (char *)0 */

	/* layout is (char *)0 dot */

	/* lheight is 0 */

	/* lwidth is 0 */

	/* lp is (char *)0 */

	/* margin is (char *)0 */

	/* mclimit stop layout factor */
	g->mclimit = 1;
	g->bitflags1.mcset = 1;

	/* newrank is 0 false */

	/* nodesep */
	g->nodesep = 0.25;
	g->bitflags1.nsepset = 1;

	/* nojustify is 0 false bool */

	/* nslimit is 0 not-set */

	/* nslimit1 is 0 not-set */

	/* ordering is (char *)0 */

	/* orientation is (char *)0 */

	/* outputorder mode is in 0 (undefined) */

	/* pack is 0 bool false */

	/* packmode is (char *)0 */

	/* pad is (char *)0 */

	/* cluster peripheries */
	g->peripheries = 1;
	g->bitflags1.periset = 1;

	/* quantum is 0 */

	/* rank is 0 */

	/* rankdir is 0 */

	/* ranksep */
	g->ranksep = 0.5;
	g->bitflags1.ranksset = 1;
	g->bitflags1.rankseq = 0;

	/* ratio is 0 */

	/* re-mincross is true */
	g->bitflags1.remincross = 1;
	g->bitflags1.remset = 1;

	/* rotate is 0 */

	/* searchsize */
	g->ssize = 30;
	g->bitflags1.ssizeset = 1;

	/* showboxes is 0 */

	/* size is 0 */

	/* sortv is 0 */

	/* splines */
	g->splines = DP_SPLINE_SPLINE;
	g->bitflags2.splinesset = 1;

	/* style bits are 0 */

	/* viewport is (char *)0 */

	return;
}

/* set graph default */
void dp_graphgdef(struct dpgraph *from, struct dpgraph *g)
{

	/* colorscheme */
	if (from->bitflags0.csnumset) {
		g->csnum = from->csnum;
		g->bitflags0.csnumset = 1;
	}

	/* bgcolor */
	if (from->bitflags0.bgcolorset) {
		g->bgcolor = from->bgcolor;
		g->bitflags0.bgcolorset = 1;
	}

	/* penwidth */
	if (from->bitflags0.penwidthset) {
		g->penwidth = from->penwidth;
		g->bitflags0.penwidthset = 1;
	}

	/* color */
	if (from->bitflags0.colorset) {
		g->color = from->color;
		g->bitflags0.colorset = 1;
	}

	/* fontcolor */
	if (from->bitflags0.fontcolorset) {
		g->fontcolor = from->fontcolor;
		g->bitflags0.fontcolorset = 1;
	}

	/* fillcolor */
	if (from->bitflags0.fcolorset) {
		g->fcolor = from->fcolor;
		g->bitflags0.fcolorset = 1;
	}

	/* pencolor */
	if (from->bitflags0.pencolorset) {
		g->pencolor = from->pencolor;
		g->bitflags0.pencolorset = 1;
	}

	/* bb number */
	if (from->bitflags0.bbset) {
		/* at "" set default */
		g->bbx0 = from->bbx0;
		g->bby0 = from->bby0;
		/* todo some hi number */
		g->bbx1 = from->bbx1;
		g->bby1 = from->bby1;
		g->bitflags0.bbset = 1;
	}

	/* url */
	if (from->bitflags0.urlset) {
		g->url = from->url;
		g->bitflags0.urlset = 1;
	}

	/* center */
	if (from->bitflags0.centerset) {
		g->bitflags0.center = from->bitflags0.center;
		g->bitflags0.centerset = 1;
	}

	/* charset */
	if (from->bitflags0.charsset) {
		g->charset = from->charset;
		g->bitflags0.charsset = 1;
	}

	/* using "" turns off default local */
	if (from->bitflags0.clrankset) {
		g->clrank = from->clrank;
		g->bitflags0.clrankset = 1;
	}

	/* comment */
	if (from->bitflags0.commset) {
		g->comment = from->comment;
		g->bitflags0.commset = 1;
	}

	/* compound */
	if (from->bitflags0.compset) {
		g->bitflags0.compound = from->bitflags0.compound;
		g->bitflags0.compset = 1;
	}

	/* concentrate */
	if (from->bitflags0.concenset) {
		g->bitflags0.concentrate = from->bitflags0.concentrate;
		g->bitflags0.concenset = 1;
	}

	/* dpi */
	if (from->bitflags0.dpiset) {
		g->dpi = from->dpi;
		g->bitflags0.dpiset = 1;
	}

	/* fontname */
	if (from->bitflags0.fontnameset) {
		g->fontname = from->fontname;
		g->bitflags0.fontnameset = 1;
	}

	/* fontpath */
	if (from->bitflags0.fontpathset) {
		g->fontpath = from->fontpath;
		g->bitflags0.fontpathset = 1;
	}

	/* fontsize is min. 1 */
	if (from->bitflags0.fontsizeset) {
		g->fontsize = from->fontsize;
		g->bitflags0.fontsizeset = 1;
	}

	/* id */
	if (from->bitflags0.idset) {
		g->id = from->id;
		g->bitflags0.idset = 1;
	}

	/* label */
	if (from->bitflags0.labelset) {
		g->label = from->label;
		g->bitflags0.labelset = 1;
	}

	/* cluster label justify l,r or center */
	if (from->bitflags0.labeljset) {
		g->labelj = from->labelj;
		g->bitflags0.labeljset = 1;
	}

	/* labelloc graph location is bottom */
	if (from->bitflags0.labellset) {
		g->labelloc = from->labelloc;
		g->bitflags0.labellset = 1;
	}

	/* landscape */
	if (from->bitflags0.landscset) {
		g->bitflags0.landscape = from->bitflags0.landscape;
		g->bitflags0.landscset = 1;
	}

	/* layers */
	if (from->bitflags0.layersset) {
		g->layers = from->layers;
		g->bitflags0.layersset = 1;
	}

	/* layerlistsep */
	if (from->bitflags0.layerlsset) {
		g->layerls = from->layerls;
		g->bitflags0.layerlsset = 1;
	}

	/* layersep */
	if (from->bitflags0.layersepset) {
		g->layersep = from->layersep;
		g->bitflags0.layersepset = 1;
	}

	/* layerselect */
	if (from->bitflags0.layerselset) {
		g->layersel = from->layersel;
		g->bitflags0.layerselset = 1;
	}

	/* layout */
	if (from->bitflags1.layoutset) {
		g->layout = from->layout;
		g->bitflags1.layoutset = 1;
	}

	/* lheight */
	if (from->bitflags1.lhset) {
		g->lheight = from->lheight;
		g->bitflags1.lhset = 1;
	}

	/* lwidth */
	if (from->bitflags1.lwset) {
		g->lwidth = from->lwidth;
		g->bitflags1.lwset = 1;
	}

	/* lp */
	if (from->bitflags1.lpset) {
		g->lpx = from->lpx;
		g->lpy = from->lpy;
		g->lpflag = from->lpflag;
		g->lp = from->lp;
		g->bitflags1.lpset = 1;
	}

	/* margin */
	if (from->bitflags1.marginset) {
		g->margin = from->margin;
		g->marginx = from->marginx;
		g->marginy = from->marginy;
		g->bitflags1.marginset = 1;
	}

	/* mclimit stop layout factor */
	if (from->bitflags1.mcset) {
		g->mclimit = from->mclimit;
		g->bitflags1.mcset = 1;
	}

	/* newrank */
	if (from->bitflags1.nrankset) {
		g->bitflags1.newrank = from->bitflags1.newrank;
		g->bitflags1.nrankset = 1;
	}

	/* nodesep */
	if (from->bitflags1.nsepset) {
		g->nodesep = from->nodesep;
		g->bitflags1.nsepset = 1;
	}

	/* nojustify */
	if (from->bitflags1.nojustset) {
		g->bitflags1.nojustify = from->bitflags1.nojustify;
		g->bitflags1.nojustset = 1;
	}

	/* nslimit */
	if (from->bitflags1.nsset) {
		g->nslimit = from->nslimit;
		g->bitflags1.nsset = 1;
	}

	/* nslimit1 */
	if (from->bitflags1.ns1set) {
		g->nslimit1 = from->nslimit1;
		g->bitflags1.ns1set = 1;
	}

	/* ordering */
	if (from->bitflags1.orderset) {
		g->ordering = from->ordering;
		g->bitflags1.orderset = 1;
	}

	/* orientation */
	if (from->bitflags1.oriset) {
		g->orientation = from->orientation;
		g->bitflags1.oriset = 1;
	}

	/* outputorder */
	if (from->bitflags1.ooset) {
		g->oorder = from->oorder;
		g->bitflags1.ooset = 1;
	}

	/* pack */
	if (from->bitflags1.packset) {
		g->pack = from->pack;
		g->bitflags1.packset = 1;
	}

	/* packmode */
	if (from->bitflags1.packmset) {
		g->packmode = from->packmode;
		g->bitflags1.packmset = 1;
	}

	/* pad */
	if (from->bitflags1.padset) {
		g->pad = from->pad;
		g->bitflags1.padset = 1;
	}

	/* cluster peripheries */
	if (from->bitflags1.periset) {
		g->peripheries = from->peripheries;
		g->bitflags1.periset = 1;
	}

	/* quantum */
	if (from->bitflags1.quanset) {
		g->quantum = from->quantum;
		g->bitflags1.quanset = 1;
	}

	/* rank */
	if (from->bitflags1.rankset) {
		g->rank = from->rank;
		g->bitflags1.rankset = 1;
	}

	/* rankdir */
	if (from->bitflags1.rankdset) {
		g->rankdir = from->rankdir;
		g->bitflags1.rankdset = 1;
	}

	/* ranksep */
	if (from->bitflags1.ranksset) {
		g->ranksep = from->ranksep;
		g->bitflags1.ranksset = 1;
		g->bitflags1.rankseq = from->bitflags1.rankseq;
	}

	/* ratio */
	if (from->bitflags1.ratioset) {
		g->ratio = from->ratio;
		g->ratiomode = from->ratiomode;
		g->bitflags1.ratioset = 1;
	}

	/* re-mincross */
	if (from->bitflags1.remset) {
		g->bitflags1.remincross = from->bitflags1.remincross;
		g->bitflags1.remset = 1;
	}

	/* rotate */
	if (from->bitflags1.rotset) {
		g->rotate = from->rotate;
		g->bitflags1.rotset = 1;
	}

	/* searchsize */
	if (from->bitflags1.ssizeset) {
		g->ssize = from->ssize;
		g->bitflags1.ssizeset = 1;
	}

	/* showboxes */
	if (from->bitflags1.sboxesset) {
		g->sboxes = from->sboxes;
		g->bitflags1.sboxesset = 1;
	}

	/* size */
	if (from->bitflags1.sizeset) {
		g->sizex = from->sizex;
		g->sizey = from->sizey;
		g->sizeflag = from->sizeflag;
		g->bitflags1.sizeset = 1;
	}

	/* sortv */
	if (from->bitflags2.sortvset) {
		g->sortv = from->sortv;
		g->bitflags2.sortvset = 1;
	}

	/* splines */
	if (from->bitflags2.splinesset) {
		g->splines = from->splines;
		g->bitflags2.splinesset = 1;
	}

	/* style bits */
	if (from->bitflags2.styleset) {
		g->bitflags2.dashedset = 1;
	}

	if (from->bitflags2.dashedset) {
		g->bitflags2.dashed = from->bitflags2.dashed;
		g->bitflags2.dashedset = 1;
	}

	if (from->bitflags2.dottedset) {
		g->bitflags2.dotted = from->bitflags2.dotted;
		g->bitflags2.dottedset = 1;
	}

	if (from->bitflags2.solidset) {
		g->bitflags2.solid = from->bitflags2.solid;
		g->bitflags2.solidset = 1;
	}

	if (from->bitflags2.boldset) {
		g->bitflags2.bold = from->bitflags2.bold;
		g->bitflags2.boldset = 1;
	}

	if (from->bitflags2.filledset) {
		g->bitflags2.filled = from->bitflags2.filled;
		g->bitflags2.filledset = 1;
	}

	if (from->bitflags2.stripedset) {
		g->bitflags2.striped = from->bitflags2.striped;
		g->bitflags2.stripedset = 1;
	}

	if (from->bitflags2.roundedset) {
		g->bitflags2.rounded = from->bitflags2.rounded;
		g->bitflags2.roundedset = 1;
	}

	/* viewport numbers */
	if (from->bitflags2.vpset) {
		g->viewport = from->viewport;
		g->bitflags2.vpset = 1;
	}

	return;
}

/* end */
