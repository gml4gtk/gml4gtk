
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

/* edge attributes:
 *
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "splay-tree.h"
#include "dp.h"
#include "dpe.h"
#include "dpus.h"
#include "dpmisc.h"
#include "dpcolor.h"
#include "lex.yy.h"
#include "dpmem.h"

/* edge[] attribute to check
 * URL arrowhead arrowsize arrowtail color colorscheme comment constraint
 * decorate dir edgeURL edgehref edgetarget edgetooltip fontcolor fontname
 * fontsize headURL head_lp headclip headhref headlabel headport headtarget
 * headtooltip href id label labelURL labelangle labeldistance labelfloat
 * labelfontcolor labelfontname labelfontsize labelhref labeltarget
 * labeltooltip layer len lhead lp ltail minlen nojustify penwidth
 * pos samehead sametail showboxes style tailURL tail_lp tailclip tailhref
 * taillabel tailport tailtarget tailtooltip target tooltip weight xlabel xlp
 */
void dp_do_eattr(char *l, char *r)
{
	int tmpi = 0;
	int cc = 0;
	struct dpedge *res = NULL;
	struct dpnum *num = NULL;
	struct dpcolor *colornum = NULL;
	struct dparrow *arrownum = NULL;
	struct dpbool *boolnum = 0;
	struct dpdir *dirnum = NULL;
	struct dppoint *pointnum = NULL;
	struct dpstyle *stylenum = NULL;

	if (dp_cclass == DP_TEDGE) {
		res = dp_curedge;
	} else if (dp_cclass == DP_TEDGEDEF) {
		res = dp_curgraph->defedge;
	} else {
		printf("dot %s(): shouldnothappen dp_cclass=%d\n", __func__, dp_cclass);
		return;
	}

	/* switch on first char */
	cc = (*l);

	switch (cc) {
		/* URL */
	case 'U':
		if (strcmp(l, "URL") == 0) {
			if (r) {
				if (strlen(r)) {
					res->url = r;
				} else {
					res->url = NULL;
				}
				res->bitflags0.urlset = 1;
			}
		} else {
		}
		break;
		/* arrowhead arrowsize arrowtail */
	case 'a':
		if (strcmp(l, "arrowhead") == 0) {
			/* todo fully parse the arrow combinations */
			arrownum = dp_getarrow(r);
			if (arrownum->pe) {
				if (arrownum->es) {
					res->ahnum = DP_EA_NORMAL;
					res->ahstring = dp_uniqstr("normal");
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown edge arrowhead `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				res->ahnum = arrownum->type;
				res->ahstring = arrownum->name;
			}
			res->bitflags0.ahset = 1;
			dp_free(arrownum);
			arrownum = NULL;
		} else if (strcmp(l, "arrowsize") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->asize = 1.0;
					res->bitflags0.asizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for arrowsize at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for arrowsize at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->asize = num->number;
					res->bitflags0.asizeset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "arrowtail") == 0) {
			/* todo fully parse the arrow combinations */
			arrownum = dp_getarrow(r);
			if (arrownum->pe) {
				if (arrownum->es) {
					res->atnum = DP_EA_NORMAL;
					res->atstring = dp_uniqstr("normal");
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown edge arrowtail `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				res->atnum = arrownum->type;
				res->atstring = arrownum->name;
			}
			res->bitflags0.atset = 1;
			dp_free(arrownum);
			arrownum = NULL;
		} else {
		}
		break;
		/* color colorscheme comment constraint */
	case 'c':
		if (strcmp(l, "color") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->ecolor = 0x00000000;
					res->bitflags0.ecolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown edge color `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->ecolor = 0x00000000;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->ecolor = colornum->color;
				}
				res->bitflags0.ecolorset = 1;
			}
			dp_free(colornum);
			colornum = NULL;
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
					res->comment = NULL;
				}
				res->bitflags0.comset = 1;
			}
		} else if (strcmp(l, "constraint") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.constraint = 0;
					res->bitflags0.constrset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for constraint at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.constraint = 1;
				} else {
					res->bitflags0.constraint = 0;
				}
				res->bitflags0.constrset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else {
		}
		break;
		/* decorate dir */
	case 'd':
		if (strcmp(l, "decorate") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.decorate = 0;
					res->bitflags0.decorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for decorate at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.decorate = 1;
				} else {
					res->bitflags0.decorate = 0;
				}
				res->bitflags0.decorset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "dir") == 0) {
			dirnum = dp_getdir(r);
			if (dirnum->pe) {
				if (dirnum->es) {
					res->dir = DP_DIR_FORWARD;
					res->bitflags0.dirset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown dir type `%s' for dir at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				res->dir = dirnum->type;
				res->bitflags0.dirset = 1;
			}
			dp_free(dirnum);
			dirnum = NULL;
		} else {
		}
		break;
		/* edgeURL edgehref edgetarget edgetooltip */
	case 'e':
		if (strcmp(l, "edgeURL") == 0) {
			if (r) {
				if (strlen(r)) {
					res->url = r;
				} else {
					res->url = NULL;
				}
				res->bitflags0.urlset = 1;
			}
		} else if (strcmp(l, "edgehref") == 0) {
			if (r) {
				if (strlen(r)) {
					res->url = r;
				} else {
					res->url = NULL;
				}
				res->bitflags0.urlset = 1;
			}
		} else if (strcmp(l, "edgetarget") == 0) {
			/* svg map only */
			if (r) {
				if (strlen(r)) {
					res->etarg = r;
				} else {
					res->etarg = NULL;
				}
				res->bitflags0.etargset = 1;
			}
		} else if (strcmp(l, "edgetooltip") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ett = r;
				} else {
					res->ett = NULL;
				}
				res->bitflags0.ettset = 1;
			}
		} else {
		}
		break;
		/* fontcolor fontname fontsize */
	case 'f':
		if (strcmp(l, "fontcolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->fontcolor = 0x00000000;
					res->bitflags0.focolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown edge fontcolor `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->ecolor = 0x00000000;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->fontcolor = colornum->color;
				}
				res->bitflags0.focolorset = 1;
			}
			dp_free(colornum);
			colornum = NULL;
		} else if (strcmp(l, "fontname") == 0) {
			if (r) {
				if (strlen(r)) {
					res->fontname = r;
				} else {
					res->fontname = NULL;
				}
				res->bitflags0.fontnameset = 1;
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
						 "dot %s(): fontsize number `%s' at line %d is too low\n", __func__, r,
						 res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		} else {
		}
		break;
		/* headURL head_lp headclip headhref headlabel headport headtarget headtooltip href */
	case 'h':
		if (strcmp(l, "headURL") == 0) {
			/* svg, map */
			if (r) {
				if (strlen(r)) {
					res->hurl = r;
				} else {
					res->hurl = NULL;
				}
				res->bitflags0.hurlset = 1;
			}
		} else if (strcmp(l, "head_lp") == 0) {
			/* point %f,%f for head label as string */
			/* parse (x,y) with optional '!' at end */
			if (r) {
				if (strlen(r)) {
					res->hlp = r;
					pointnum = dp_getpoint(r);
					if (pointnum->pe) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): cannot parse head_lp (x,y) number `%s' at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->hlpx = pointnum->x;
						res->hlpy = pointnum->y;
						res->hlpflag = pointnum->flag;
					}
					dp_free(pointnum);
					pointnum = NULL;
				} else {
					res->hlpx = 0;
					res->hlpy = 0;
					res->hlpflag = 0;
					res->hlp = NULL;
				}
				res->bitflags0.hlpset = 1;
			}
		} else if (strcmp(l, "headclip") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.headclip = 0;
					res->bitflags0.hcset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for headclip at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.headclip = 1;
				} else {
					res->bitflags0.headclip = 0;
				}
				res->bitflags0.hcset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "headhref") == 0) {
			/* same as headURL */
			/* svg, map */
			if (r) {
				if (strlen(r)) {
					res->hurl = r;
				} else {
					res->hurl = NULL;
				}
				res->bitflags0.hurlset = 1;
			}
		} else if (strcmp(l, "headlabel") == 0) {
			if (r) {
				if (strlen(r)) {
					res->hlabel = r;
				} else {
					res->hlabel = NULL;
				}
				res->bitflags0.hlset = 1;
			}
		} else if (strcmp(l, "headport") == 0) {
			/* todo could be portname:compass ? */
			if (r) {
				if (strlen(r) == 0) {
					/* default is center 'c' */
					res->hport = "c";
					res->bitflags0.hportset = 1;
				} else {
					tmpi = dp_iscompass(r);
					if (tmpi == 0) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): not a compass point `%s' for headport at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->hport = r;
						res->bitflags0.hportset = 1;
					}
				}
			}
		} else if (strcmp(l, "headtarget") == 0) {
			/* svg, map */
			if (r) {
				if (strlen(r)) {
					res->htarg = r;
				} else {
					res->htarg = NULL;
				}
				res->bitflags0.htargset = 1;
			}
		} else if (strcmp(l, "headtooltip") == 0) {
			/* svg, cmap */
			if (r) {
				if (strlen(r)) {
					res->htt = r;
				} else {
					res->htt = NULL;
				}
				res->bitflags0.httset = 1;
			}
		} else if (strcmp(l, "href") == 0) {
			if (r) {
				if (strlen(r)) {
					res->url = r;
				} else {
					res->url = NULL;
				}
				res->bitflags0.urlset = 1;
			}
		} else {
		}
		break;
		/* id */
	case 'i':
		if (strcmp(l, "id") == 0) {
			/* svg, map */
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
		/* label labelURL labelangle labeldistance labelfloat labelfontcolor labelfontname labelfontsize labelhref labeltarget labeltooltip layer len lhead lp ltail */
	case 'l':
		if (strcmp(l, "label") == 0) {
			if (r) {
				if (strlen(r)) {
					res->label = r;
				} else {
					/* using "" turns off the edge label */
					res->label = NULL;
				}
				res->bitflags0.labelset = 1;
			}
		} else if (strcmp(l, "labelURL") == 0) {
			/* url */
			if (r) {
				if (strlen(r)) {
					res->lurl = r;
				} else {
					/* using "" turns off the edge url */
					res->lurl = NULL;
				}
				res->bitflags0.lurlset = 1;
			}
		} else if (strcmp(l, "labelangle") == 0) {
			/*  */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->la = -25;
					res->bitflags0.laset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse labelangle number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number > -180.0 && num->number < 360) {
					/* round to int in double format */
					res->la = rint(num->number);
					res->bitflags0.laset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): labelangle number `%s' at line %d is out-of-range -180...360\n",
						 __func__, r, res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "labeldistance") == 0) {
			/*  */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->ldist = 1;
					res->bitflags0.ldistset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse labeldistance number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number > 0) {
					/* */
					res->ldist = num->number;
					res->bitflags0.ldistset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): labeldistance number `%s' at line %d is too low\n",
						 __func__, r, res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "labelfloat") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags1.lfloat = 0;
					res->bitflags1.lfloatset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for labelfloat at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.lfloat = 1;
				} else {
					res->bitflags1.lfloat = 0;
				}
				res->bitflags1.lfloatset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "labelfontcolor") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->lfontcolor = 0x00000000;
					res->bitflags1.lfocolorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown labelfontcolor `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->ecolor = 0x00000000;
					printf("dot %s(): color list at line %d not supported\n", __func__, res->yylineno);
				} else {
					res->lfontcolor = colornum->color;
				}
				res->bitflags1.lfocolorset = 1;
			}
			dp_free(colornum);
			colornum = NULL;
		} else if (strcmp(l, "labelfontname") == 0) {
			if (r) {
				if (strlen(r)) {
					res->lfontname = r;
				} else {
					res->lfontname = NULL;
				}
				res->bitflags1.lfontnameset = 1;
			}
		} else if (strcmp(l, "labelfontsize") == 0) {
			/* size of font */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->lfontsize = 14;
					res->bitflags1.lfontsizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse labelfontsize number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number >= 1.0) {
					/* round to int in double format */
					res->lfontsize = rint(num->number);
					res->bitflags1.lfontsizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): labelfontsize number `%s' at line %d is too low\n",
						 __func__, r, res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "labelhref") == 0) {
			/* url same as labelURL */
			if (r) {
				if (strlen(r)) {
					res->lurl = r;
				} else {
					/* using "" turns off the edge url */
					res->lurl = NULL;
				}
				res->bitflags0.lurlset = 1;
			}
		} else if (strcmp(l, "labeltarget") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ltarg = r;
				} else {
					/* using "" turns off */
					res->ltarg = NULL;
				}
				res->bitflags1.ltargset = 1;
			}
		} else if (strcmp(l, "labeltooltip") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ltt = r;
				} else {
					/* using "" turns off */
					res->ltt = NULL;
				}
				res->bitflags1.lttset = 1;
			}
		} else if (strcmp(l, "layer") == 0) {
			/* layer control string */
			if (r) {
				if (strlen(r)) {
					res->layer = r;
				} else {
					/* using "" turns off */
					res->layer = NULL;
				}
				res->bitflags1.layerset = 1;
			}
		} else if (strcmp(l, "len") == 0) {
			/* edge len in inches neato */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->len = 1;
					res->bitflags1.lenset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse len number `%s' at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				if (num->number >= 0) {
					/* */
					res->len = num->number;
					res->bitflags1.lenset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): len number `%s' at line %d is negative\n", __func__, r, res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "lhead") == 0) {
			if (r) {
				if (strlen(r)) {
					res->lhead = r;
				} else {
					/* using "" turns off */
					res->lhead = NULL;
				}
				res->bitflags1.lheadset = 1;
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
					dp_free(pointnum);
					pointnum = NULL;
				} else {
					res->lp = NULL;
				}
				res->bitflags1.lpset = 1;
			}
		} else if (strcmp(l, "ltail") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ltail = r;
				} else {
					/* using "" turns off */
					res->ltail = NULL;
				}
				res->bitflags1.ltailset = 1;
			}
		} else {
		}
		break;
		/* minlen */
	case 'm':
		if (strcmp(l, "minlen") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->minlen = 0;
					res->bitflags1.minlenset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for penwidth at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for minlen at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->minlen = rint(num->number);
					res->bitflags1.minlenset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else {
			/* something else */
		}
		break;
		/* nojustify */
	case 'n':
		if (strcmp(l, "nojustify") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags1.nojust = 0;
					res->bitflags1.nojustset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for nojustify at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.nojust = 1;
				} else {
					res->bitflags1.nojust = 0;
				}
				res->bitflags1.nojustset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else {
		}
		break;
		/* penwidth pos */
	case 'p':
		if (strcmp(l, "penwidth") == 0) {
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
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "pos") == 0) {
			/* example:[pos="e,1110,867.67 1110,904.33 1110,896.26 1110,886.65 1110,877.71"];
			 * todo parse this pos string
			 */
			if (r) {
				if (strlen(r)) {
					res->pos = r;
				} else {
					/* using "" turns off */
					res->pos = NULL;
				}
				res->bitflags1.posset = 1;
			}
		} else {
		}
		break;
		/* samehead sametail showboxes style */
	case 's':
		if (strcmp(l, "samehead") == 0) {
			if (r) {
				if (strlen(r)) {
					res->sameh = r;
				} else {
					/* using "" turns off */
					res->sameh = NULL;
				}
				res->bitflags1.samehset = 1;
			}
		} else if (strcmp(l, "sametail") == 0) {
			if (r) {
				if (strlen(r)) {
					res->samet = r;
				} else {
					/* using "" turns off */
					res->samet = NULL;
				}
				res->bitflags1.sametset = 1;
			}
		} else if (strcmp(l, "showboxes") == 0) {
			/* postscript, 0, 1, 2 */
		} else if (strcmp(l, "style") == 0) {
			stylenum = dp_getstyle(r);
			if (stylenum->pe) {
				if (stylenum->es) {
					/* at "" clear all */
					res->bitflags0.styleset = 0;
					res->bitflags1.dashed = 0;
					res->bitflags1.dashedset = 1;
					res->bitflags1.dotted = 0;
					res->bitflags1.dottedset = 1;
					res->bitflags1.solid = 0;
					res->bitflags1.solidset = 1;
					res->bitflags1.invis = 0;
					res->bitflags1.invisset = 1;
					res->bitflags1.bold = 0;
					res->bitflags1.boldset = 1;
					res->bitflags1.tapered = 0;
					res->bitflags1.taperedset = 1;
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
							 "dot %s(): wrong number or negative number `%s' for setlinewidth in style at line %d\nuse penwidth instead of setlinewidth.\n",
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
				/* no parse errors if here, the E marked are for a edge: */
				/* int dashed;  "dashed" parsed N+E */
				/* int dotted;  "dotted" parsed N+E */
				/* int solid;   "solid" parsed N+E */
				/* int invis;   "invis" parsed N+E */
				/* int bold;    "bold" parsed N+E */
				/* int tapered; "tapered" parsed E */
				/* tolerated by dot is "filled" in E */
				/* tolerated by dot is "rounded" in E */

				if (stylenum->filled) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): filled does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf
						    ("dot %s(): filled does not apply to edge in `%s' for style at line %d\n",
						     __func__, r, res->yylineno);
					}
				} else if (stylenum->striped) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): striped does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf("dot %s(): striped does not apply to edge in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->wedged) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): wedged does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf("dot %s(): wedged does not apply to edge in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->diagonals) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): diagonals does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf("dot %s(): diagonals does not apply to edge in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->rounded) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): rounded does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf("dot %s(): rounded does not apply to edge in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else if (stylenum->radial) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): radial does not apply to edge in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {	/* as warning */
						printf("dot %s(): radial does not apply to edge in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else {
					res->bitflags0.styleset = 1;
					if (stylenum->slwset) {
						res->penwidth = stylenum->slw;
						res->bitflags0.penwidthset = 1;
					}
					if (stylenum->tapered) {
						res->bitflags1.tapered = 1;
						res->bitflags1.taperedset = 1;
					}
					if (stylenum->dashed) {
						res->bitflags1.dashed = 1;
						res->bitflags1.dashedset = 1;
					}
					if (stylenum->dotted) {
						res->bitflags1.dotted = 1;
						res->bitflags1.dottedset = 1;
					}
					if (stylenum->solid) {
						res->bitflags1.solid = 1;
						res->bitflags1.solidset = 1;
					}
					if (stylenum->invis) {
						res->bitflags1.invis = 1;
						res->bitflags1.invisset = 1;
					}
					if (stylenum->bold) {
						res->bitflags1.bold = 1;
						res->bitflags1.boldset = 1;
					}
				}
			}
			dp_free(stylenum);
			stylenum = NULL;
		} else {
		}
		break;
		/* tailURL tail_lp tailclip tailhref taillabel tailport tailtarget tailtooltip target tooltip */
	case 't':
		if (strcmp(l, "tailURL") == 0) {
			/* same as headURL */
			/* svg, map */
			if (r) {
				if (strlen(r)) {
					res->turl = r;
				} else {
					res->turl = NULL;
				}
				res->bitflags1.turlset = 1;
			}
		} else if (strcmp(l, "tail_lp") == 0) {
			/* point %f,%f for head label as string */
			/* parse (x,y) with optional '!' at end */
			if (r) {
				if (strlen(r)) {
					res->tlp = r;
					pointnum = dp_getpoint(r);
					if (pointnum->pe) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): cannot parse tail_lp (x,y) number `%s' at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->tlpx = pointnum->x;
						res->tlpy = pointnum->y;
						res->tlpflag = pointnum->flag;
					}
					dp_free(pointnum);
					pointnum = NULL;
				} else {
					res->hlp = NULL;
				}
				res->bitflags1.tlpset = 1;
			}
		} else if (strcmp(l, "tailclip") == 0) {
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default is 1 but "" set it to zero todo here 1 or 0 ? */
					res->bitflags2.tailc = 0;
					res->bitflags2.tailcset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for tailclip at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags2.tailc = 1;
				} else {
					res->bitflags2.tailc = 0;
				}
				res->bitflags2.tailcset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "tailhref") == 0) {
			/* same as headURL */
			/* svg, map */
			if (r) {
				if (strlen(r)) {
					res->turl = r;
				} else {
					res->turl = NULL;
				}
				res->bitflags1.turlset = 1;
			}
		} else if (strcmp(l, "taillabel") == 0) {
			if (r) {
				if (strlen(r)) {
					res->tlabel = r;
				} else {
					res->tlabel = NULL;
				}
				res->bitflags2.tlabelset = 1;
			}
		} else if (strcmp(l, "tailport") == 0) {
			/* todo could be portname:compass ? */
			if (r) {
				if (strlen(r) == 0) {
					/* default is center 'c' */
					res->tlport = "c";
					res->bitflags2.tportset = 1;
				} else {
					tmpi = dp_iscompass(r);
					if (tmpi == 0) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): not a compass point `%s' for tailport at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->tlport = r;
						res->bitflags2.tportset = 1;
					}
				}
			}
		} else if (strcmp(l, "tailtarget") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ttarg = r;
				} else {
					res->ttarg = NULL;
				}
				res->bitflags2.ttargset = 1;
			}
		} else if (strcmp(l, "tailtooltip") == 0) {
			if (r) {
				if (strlen(r)) {
					res->ttt = r;
				} else {
					res->ttt = NULL;
				}
				res->bitflags2.tttset = 1;
			}
		} else if (strcmp(l, "target") == 0) {
			if (r) {
				if (strlen(r)) {
					res->target = r;
				} else {
					res->target = NULL;
				}
				res->bitflags2.targetset = 1;
			}
		} else if (strcmp(l, "tooltip") == 0) {
			if (r) {
				if (strlen(r)) {
					res->tt = r;
				} else {
					res->tt = NULL;
				}
				res->bitflags2.ttset = 1;
			}
		} else {
			/* something else */
		}
		break;
		/* weight */
	case 'w':
		if (strcmp(l, "weight") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->weight = 1;
					res->bitflags2.weightset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for weight at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for weight at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->weight = num->number;
					res->bitflags2.weightset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else {
			/* something else */
		}
		break;
		/* xlabel xlp */
	case 'x':
		if (strcmp(l, "xlabel") == 0) {
			if (r) {
				if (strlen(r)) {
					res->xlabel = r;
				} else {
					res->xlabel = NULL;
				}
				res->bitflags2.xlabelset = 1;
			}
		} else if (strcmp(l, "xlp") == 0) {
			/* point %f,%f for head label as string */
			/* parse (x,y) with optional '!' at end */
			if (r) {
				if (strlen(r)) {
					res->xlp = r;
					pointnum = dp_getpoint(r);
					if (pointnum->pe) {
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): cannot parse xlp (x,y) number `%s' at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						res->xlpx = pointnum->x;
						res->xlpy = pointnum->y;
						res->xlpflag = pointnum->flag;
					}
					dp_free(pointnum);
					pointnum = NULL;
				} else {
					res->xlp = NULL;
				}
				res->bitflags2.xlpset = 1;
			}
		} else {
			/* something else */
		}
		break;
	default:
		/* something else */
		break;
	}

	return;
}

/* set factory default */
void dp_edgefdef(struct dpedge *e)
{

	/* url is (char *)0 */

	/* arrowhead is normal as default */
	e->ahnum = DP_EA_NORMAL;
	e->ahstring = dp_uniqstr("normal");
	e->bitflags0.ahset = 1;

	/* arrowsize mult factor is 1 */
	e->asize = 1.0;
	e->bitflags0.asizeset = 1;

	/* arrowtail is normal as default */
	e->atnum = DP_EA_NORMAL;
	e->atstring = dp_uniqstr("normal");
	e->bitflags0.atset = 1;

	/* colorscheme is 0 undefined */

	/* comment is (char *)0 */

	/* constraint is 0 false bool */
	e->bitflags0.constraint = 1;
	e->bitflags0.constrset = 1;

	/* decorate is 0 bool false */

	/* arrow direction */
	e->dir = DP_DIR_FORWARD;
	e->bitflags0.dirset = 1;

	/* edgetarget is (char *)0 svg */

	/* edgetooltip is (char *)0 */

	/* fontcolor is 0 black */

	/* fontname is (char *)0 */

	/* fontsize is 14, min 1. */
	e->fontsize = 14;
	e->bitflags0.fontsizeset = 1;

	/* headurl is (char *)0 */

	/* headhref is same as headURL */

	/* head_lp is (char *)0 */

	/* headclip is 0 false */

	/* headlabel is (char *)0 */

	/* headport is default center, 'c' */
	e->hport = "c";
	e->bitflags0.hportset = 1;

	/* headtarget is (char *)0 */

	/* headtooltip is (char *)0 */

	/* id is (char *)0 */

	/* edge label is (char *)0 */

	/* labelurl is (char *)0 */

	/* labelangle */
	e->la = -25;
	e->bitflags0.laset = 1;

	/* labeldistance */
	e->ldist = 1;
	e->bitflags0.ldistset = 1;

	/* labelfloat is 0 false */

	/* labelfontcolor is black 8 */

	/* labelfontname is (char *)0 */

	/* labelfontsize is 14, min 1. */
	e->lfontsize = 14;
	e->bitflags1.lfontsizeset = 1;

	/* labeltarget is (char *)0 */

	/* labeltooltip is (char *)0 */

	/* layer is  (char *)0 */

	/* len neato */
	e->len = 1;
	e->bitflags1.lenset = 1;

	/* lhead is (char *)0 */

	/* ltail is (char *)0 */

	/* lp is (char *)0 */

	/* minlen is 0 */

	/* nojustify is 0 false */

	/* edge line thickness */
	e->penwidth = 1;
	e->bitflags0.penwidthset = 1;

	/* pos is (char *)0 */

	/* samehead is (char *)0 */

	/* sametail is (char *)0 */

	/* style bits are 0 off */

	/* tailclip is true */
	e->bitflags2.tailc = 1;
	e->bitflags2.tailcset = 1;

	/* tail label is (char *)0 */

	/* tailport is default center, 'c' */
	e->tlport = "c";
	e->bitflags2.tportset = 1;

	/* tailtarget is (char *)0 */

	/* tailtooltip is (char *)0 */

	/* target is (char *)0 */

	/* tooltip is (char *)0 */

	/* weight */
	e->weight = 1;
	e->bitflags2.weightset = 1;

	/* xlabel is (char *)0 */

	/* xlp is (char *)0 */

	return;
}

/* set edge default */
void dp_edgegdef(struct dpedge *from, struct dpedge *e)
{

	/* edge color */
	if (from->bitflags0.ecolorset) {
		e->ecolor = from->ecolor;
		e->bitflags0.ecolorset = 1;
	}

	/* edge style */
	if (from->bitflags0.styleset) {
		e->style = from->style;
		e->bitflags0.styleset = 1;
	}

	/* url */
	if (from->bitflags0.urlset) {
		e->url = from->url;
		e->bitflags0.urlset = 1;
	}

	/* colorscheme */
	if (from->bitflags0.csnumset) {
		e->csnum = from->csnum;
		e->bitflags0.csnumset = 1;
	}

	/* arrowhead */
	if (from->bitflags0.ahset) {
		e->ahnum = from->ahnum;
		e->ahstring = from->ahstring;
		e->bitflags0.ahset = 1;
	}

	/* arrowsize */
	if (from->bitflags0.asizeset) {
		e->asize = from->asize;
		e->bitflags0.asizeset = 1;
	}

	/* arrowtail */
	if (from->bitflags0.atset) {
		e->atnum = from->atnum;
		e->atstring = from->atstring;
		e->bitflags0.atset = 1;
	}

	/* comment output data */
	if (from->bitflags0.comset) {
		e->comment = from->comment;
		e->bitflags0.comset = 1;
	}

	/* constraint */
	if (from->bitflags0.constrset) {
		e->bitflags0.constraint = from->bitflags0.constraint;
		e->bitflags0.constrset = 1;
	}

	/* decorate */
	if (from->bitflags0.decorset) {
		e->bitflags0.decorate = from->bitflags0.decorate;
		e->bitflags0.decorset = 1;
	}

	/* arrow direction */
	if (from->bitflags0.dirset) {
		e->dir = from->dir;
		e->bitflags0.dirset = 1;
	}

	/* edgetarget svg */
	if (from->bitflags0.etargset) {
		e->etarg = from->etarg;
		e->bitflags0.etargset = 1;
	}

	/* edge tooltip for url */
	if (from->bitflags0.ettset) {
		e->ett = from->ett;
		e->bitflags0.ettset = 1;
	}

	/* font color */
	if (from->bitflags0.focolorset) {
		e->fontcolor = from->fontcolor;
		e->bitflags0.focolorset = 1;
	}

	/* fontname */
	if (from->bitflags0.fontnameset) {
		e->fontname = from->fontname;
		e->bitflags0.fontnameset = 1;
	}

	/* fontsize is 14, min 1. */
	if (from->bitflags0.fontsizeset) {
		e->fontsize = from->fontsize;
		e->bitflags0.fontsizeset = 1;
	}

	/* headurl svg.map */
	if (from->bitflags0.hurlset) {
		e->hurl = from->hurl;
		e->bitflags0.hurlset = 1;
	}

	/* %f,%f head_lp point as string */
	if (from->bitflags0.hlpset) {
		e->hlpx = from->hlpx;
		e->hlpy = from->hlpy;
		e->hlpflag = from->hlpflag;
		e->hlp = from->hlp;
		e->bitflags0.hlpset = 1;
	}

	/* headclip bool */
	if (from->bitflags0.hcset) {
		e->bitflags0.headclip = from->bitflags0.headclip;
		e->bitflags0.hcset = 1;
	}

	/* headlabel string */
	if (from->bitflags0.hlset) {
		e->hlabel = from->hlabel;
		e->bitflags0.hlset = 1;
	}

	/* headport */
	if (from->bitflags0.hportset) {
		e->hport = from->hport;
		e->bitflags0.hportset = 1;
	}

	/* headtarget svg map */
	if (from->bitflags0.htargset) {
		e->htarg = from->htarg;
		e->bitflags0.htargset = 1;
	}

	/* headtooltip svg cmap */
	if (from->bitflags0.httset) {
		e->htt = from->htt;
		e->bitflags0.httset = 1;
	}

	/* svg id */
	if (from->bitflags0.idset) {
		e->id = from->id;
		e->bitflags0.idset = 1;
	}

	/* edge label */
	if (from->bitflags0.labelset) {
		e->label = from->label;
		e->bitflags0.labelset = 1;
	}

	/* label url */
	if (from->bitflags0.lurlset) {
		e->lurl = from->lurl;
		e->bitflags0.lurlset = 1;
	}

	/* labelangle */
	if (from->bitflags0.laset) {
		e->la = from->la;
		e->bitflags0.laset = 1;
	}

	/* labeldistance */
	if (from->bitflags0.ldistset) {
		e->ldist = from->ldist;
		e->bitflags0.ldistset = 1;
	}

	/* labelfloat */
	if (from->bitflags1.lfloatset) {
		e->bitflags1.lfloat = from->bitflags1.lfloat;
		e->bitflags1.lfloatset = 1;
	}

	/* labelfont color */
	if (from->bitflags1.lfocolorset) {
		e->lfontcolor = from->lfontcolor;
		e->bitflags1.lfocolorset = 1;
	}

	/* labelfontname */
	if (from->bitflags1.lfontnameset) {
		e->lfontname = from->lfontname;
		e->bitflags1.lfontnameset = 1;
	}

	/* labelfontsize is 14, min 1. */
	if (from->bitflags1.lfontsizeset) {
		e->lfontsize = from->lfontsize;
		e->bitflags1.lfontsizeset = 1;
	}

	/* labeltarget */
	if (from->bitflags1.ltargset) {
		e->ltarg = from->ltarg;
		e->bitflags1.ltargset = 1;
	}

	/* labeltooltip svg cmap */
	if (from->bitflags1.lttset) {
		e->ltt = from->ltt;
		e->bitflags1.lttset = 1;
	}

	/* layer control string */
	if (from->bitflags1.layerset) {
		e->layer = from->layer;
		e->bitflags1.layerset = 1;
	}

	/* len neto */
	if (from->bitflags1.lenset) {
		e->len = from->len;
		e->bitflags1.lenset = 1;
	}

	/* lhead */
	if (from->bitflags1.lheadset) {
		e->lhead = from->lhead;
		e->bitflags1.lheadset = 1;
	}

	/* ltail */
	if (from->bitflags1.ltailset) {
		e->ltail = from->ltail;
		e->bitflags1.ltailset = 1;
	}

	/* %f,%f lp point as string */
	if (from->bitflags1.lpset) {
		e->lpx = from->lpx;
		e->lpy = from->lpy;
		e->lpflag = from->lpflag;
		e->lp = from->lp;
		e->bitflags1.lpset = 1;
	}

	/* minlen */
	if (from->bitflags1.minlenset) {
		e->minlen = from->minlen;
		e->bitflags1.minlenset = 1;
	}

	/* nojustify */
	if (from->bitflags1.nojustset) {
		e->bitflags1.nojust = from->bitflags1.nojust;
		e->bitflags1.nojustset = 1;
	}

	/* edge line thickness */
	if (from->bitflags0.penwidthset) {
		e->penwidth = from->penwidth;
		e->bitflags0.penwidthset = 1;
	}

	/* pos string */
	if (from->bitflags1.posset) {
		e->pos = from->pos;
		e->bitflags1.posset = 1;
	}

	/* samehead */
	if (from->bitflags1.samehset) {
		e->sameh = from->sameh;
		e->bitflags1.samehset = 1;
	}

	/* sametail */
	if (from->bitflags1.sametset) {
		e->samet = from->samet;
		e->bitflags1.sametset = 1;
	}

	/* style bits */
	if (from->bitflags0.styleset) {
		e->bitflags0.styleset = 1;
	}

	if (from->bitflags1.taperedset) {
		e->bitflags1.tapered = from->bitflags1.tapered;
		e->bitflags1.taperedset = 1;
	}

	if (from->bitflags1.dashedset) {
		e->bitflags1.dashed = from->bitflags1.dashed;
		e->bitflags1.dashedset = 1;
	}

	if (from->bitflags1.dottedset) {
		e->bitflags1.dotted = from->bitflags1.dotted;
		e->bitflags1.dottedset = 1;
	}

	if (from->bitflags1.solidset) {
		e->bitflags1.solid = from->bitflags1.solid;
		e->bitflags1.solidset = 1;
	}

	if (from->bitflags1.invisset) {
		e->bitflags1.invis = from->bitflags1.invis;
		e->bitflags1.invisset = 1;
	}

	if (from->bitflags1.boldset) {
		e->bitflags1.bold = from->bitflags1.bold;
		e->bitflags1.boldset = 1;
	}

	/* tail url */
	if (from->bitflags1.turlset) {
		e->turl = from->turl;
		e->bitflags1.turlset = 1;
	}

	/* %f,%f tail_lp point as string */
	if (from->bitflags1.tlpset) {
		e->tlpx = from->tlpx;
		e->tlpy = from->tlpy;
		e->tlpflag = from->tlpflag;
		e->tlp = from->tlp;
		e->bitflags1.tlpset = 1;
	}

	/* tailclip */
	if (from->bitflags2.tailcset) {
		e->bitflags2.tailc = from->bitflags2.tailc;
		e->bitflags2.tailcset = 1;
	}

	/* taillabel */
	if (from->bitflags2.tlabelset) {
		e->tlabel = from->tlabel;
		e->bitflags2.tlabelset = 1;
	}

	/* tailport */
	if (from->bitflags2.tportset) {
		e->tlport = from->tlport;
		e->bitflags2.tportset = 1;
	}

	/* tailtarget svg map */
	if (from->bitflags2.ttargset) {
		e->ttarg = from->ttarg;
		e->bitflags2.ttargset = 1;
	}

	/* tailtooltip svg cmap */
	if (from->bitflags2.tttset) {
		e->ttt = from->ttt;
		e->bitflags2.tttset = 1;
	}

	/* target */
	if (from->bitflags2.targetset) {
		e->target = from->target;
		e->bitflags2.targetset = 1;
	}

	/* tooltip */
	if (from->bitflags2.ttset) {
		e->tt = from->tt;
		e->bitflags2.ttset = 1;
	}

	/* weight */
	if (from->bitflags2.weightset) {
		e->weight = from->weight;
		e->bitflags2.weightset = 1;
	}

	/* xlabel */
	if (from->bitflags2.xlabelset) {
		e->xlabel = from->xlabel;
		e->bitflags2.xlabelset = 1;
	}

	/* %f,%f xlp point as string */
	if (from->bitflags2.xlpset) {
		e->xlpx = from->xlpx;
		e->xlpy = from->xlpy;
		e->xlpflag = from->xlpflag;
		e->xlp = from->xlp;
		e->bitflags2.xlpset = 1;
	}

	return;
}

/* end */
