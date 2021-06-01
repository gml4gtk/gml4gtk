
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

/* node attributes:
 * color colorscheme comment distortion fillcolor fixedsize fontcolor fontname
 * fontsize group height id image imagescale label labelloc layer margin nojustify
 * orientation penwidth peripheries pin pos rects regular root samplepoints shape
 * shapefile showboxes sides skew sortv style target tooltip vertices width z
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "splay-tree.h"
#include "dp.h"
#include "dpn.h"
#include "dpcolor.h"
#include "dpmisc.h"
#include "dot.tab.h"
#include "lex.yy.h"
#include "dpus.h"
#include "dpmem.h"

/* node[] attribute to check */
void dp_do_nattr(char *l, char *r, int ishtml)
{
	int cc = 0;
	int tmpi = 0;
	struct dpnode *res = NULL;
	struct dpnum *num = NULL;
	struct dpbool *boolnum = NULL;
	struct dpcolor *colornum = NULL;
	struct dpstyle *stylenum = NULL;
	struct dpmargin *mnum = NULL;

	if (dp_cclass == DP_TNODE) {
		res = dp_curnode;
	} else if (dp_cclass == DP_TNODEDEF) {
		res = dp_curgraph->defnode;
	} else {
		printf("dot %s(): shouldnothappen dp_cclass=%d\n", __func__, dp_cclass);
		return;
	}

	/* switch on first char */
	cc = (*l);

	switch (cc) {
	case 'c':
		if (strcmp(l, "color") == 0) {
			colornum = dp_getcolor(res->bitflags0.csnumset, res->csnum, r);
			if (colornum->pe) {
				if (colornum->es) {
					/* default black color */
					res->color = 0x00000000;
					res->bitflags0.colorset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown color `%s' at node `%s' line %d\n",
						 __func__, r, res->name, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->color = 0x00000000;
					printf
					    ("dot %s(): color list at node `%s' line %d not supported\n",
					     __func__, res->name, res->yylineno);
				} else {
					res->color = colornum->color;
				}
				res->bitflags0.colorset = 1;
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
			/* device dep. string */
			if (r) {
				if (strlen(r)) {
					res->comment = r;
				} else {
					res->comment = NULL;
				}
				res->bitflags0.comset = 1;
			}
		} else {
			/* something other */
		}
		break;

	case 'd':
		if (strcmp(l, "distortion") == 0) {
			/* factor for shape polygon, default 0, min -100 max ? */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* number is "", use default. */
					res->distortion = 0;
					res->bitflags0.distortionset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse distortion number `%s' at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number > -100) {
					res->distortion = num->number;
					res->bitflags0.distortionset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): distortion number `%s' at line %d is too low\n",
						 __func__, r, res->yylineno);
				}
			}
			dp_free(num);
			num = NULL;
		}
		break;

		/* fillcolor fixedsize fontcolor fontname fontsize */
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
						 "dot %s(): unknown color `%s' at node `%s' line %d\n",
						 __func__, r, res->name, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default white color */
					res->fcolor = 0x00ffffff;
					printf
					    ("dot %s(): color list at node `%s' line %d not supported\n",
					     __func__, res->name, res->yylineno);
				} else {
					res->fcolor = colornum->color;
				}
				res->bitflags0.fcolorset = 1;
			}
			dp_free(colornum);
			colornum = NULL;
		} else if (strcmp(l, "fixedsize") == 0) {
			/* if fixedsize=true, the width parameter is used for node x size */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.fixsize = 0;
					res->bitflags0.fixsizeset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' at fixedsize line %d\n", __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.fixsize = 1;
				} else {
					res->bitflags0.fixsize = 0;
				}
				res->bitflags0.fixsizeset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
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
						 "dot %s(): unknown color `%s' at node `%s' line %d\n",
						 __func__, r, res->name, res->yylineno);
				}
			} else {
				/* todo */
				if (colornum->islist) {
					/* default black color */
					res->fontcolor = 0x00000000;
					printf
					    ("dot %s(): color list at node `%s' line %d not supported\n",
					     __func__, res->name, res->yylineno);
				} else {
					res->fontcolor = colornum->color;
				}
				res->bitflags0.fontcolorset = 1;
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
			/* something else */
		}
		break;

		/* group */
	case 'g':
		if (strcmp(l, "group") == 0) {
			if (r) {
				if (strlen(r)) {
					res->group = r;
				} else {
					res->group = NULL;
				}
				res->bitflags0.groupset = 1;
			}
		} else {
			/* something else */
		}
		break;

		/* height href */
	case 'h':
		if (strcmp(l, "height") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->height = 0.5;
					res->bitflags0.heightset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): cannot parse `%s' for height at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				/* allow 0 for gprof2dot */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for height at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					/* min. is 0.02 */
					res->height = num->number;
					if (res->height < 0.02) {
						printf("dot %s(): minimum value for height is 0.02 but specified is %s\n", __func__,
						       r);
						res->height = 0.02;
					}
					res->bitflags0.heightset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "href") == 0) {
			/* url node */
			if (r) {
				if (strlen(r)) {
					res->url = NULL;
				} else {
					res->url = NULL;
				}
				res->bitflags1.urlset = 1;
			}
		} else {
			/* something else */
		}
		break;

		/* id image imagescale */
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
		} else if (strcmp(l, "image") == 0) {
			/* image for node */
			if (r) {
				if (strlen(r)) {
					res->image = r;
				} else {
					res->image = NULL;
				}
				res->bitflags0.imgset = 1;
			}
		} else if (strcmp(l, "imagescale") == 0) {
			/* scale for image */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.iscale = 0;
					res->bitflags0.iscaleset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for imagescale at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.iscale = 1;
				} else {
					res->bitflags0.iscale = 0;
				}
				res->bitflags0.iscaleset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else {
			/* something else */
		}
		break;

		/* label labelloc layer */
	case 'l':
		/* node[label=<>] does remove the label texts if no label at node specified */
		/* node[label=""] does remove the label texts if no label at node specified */
		/* label can have html entity chars as &#x20; or &#231; or &#amp; */
		/* \N set node name */
		if (strcmp(l, "label") == 0) {
			if (r) {
				if (strlen(r)) {
					res->label = r;
					res->htmllabel = ishtml;
				} else {
					/* label="" does empty the label text */
					/* dot sets few spaces at "" to get ellipse default shape */
					res->label = dp_uniqstr("  ");
					res->htmllabel = 0;
				}
				res->bitflags0.labelset = 1;
				/* at \N de-select */
				/* todo, this must be done more complicated. */
				if (strcmp(r, "\\N") == 0) {
					res->label = NULL;
					res->htmllabel = 0;
					res->bitflags0.labelset = 0;
				}
				if (yydebug || 0) {
					printf("%s(): node label \"%s\" type html-label=%d\n", __func__, res->label,
					       res->htmllabel);
				}
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
		} else if (strcmp(l, "layer") == 0) {
			/* layer control string */
			if (r) {
				if (strlen(r)) {
					res->layer = r;
				} else {
					res->layer = NULL;
				}
				res->bitflags0.layerset = 1;
			}
		} else {
			/* something else */
		}
		break;

		/* margin */
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
								 "dot %s(): cannot parse `%s' for margin at line %d\n",
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
					dp_free(mnum);
					mnum = NULL;
					res->bitflags0.marginset = 1;
				}
			}
		} else {
			/* something else */
		}
		break;

		/* nojustify */
	case 'n':
		if (strcmp(l, "nojustify") == 0) {
			/* */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.nojust = 0;
					res->bitflags0.nojustset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for nojustify at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.nojust = 1;
				} else {
					res->bitflags0.nojust = 0;
				}
				res->bitflags0.nojustset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else {
			/* something else */
		}
		break;

		/* orientation */
	case 'o':
		if (strcmp(l, "orientation") == 0) {
			/* rotate polygon shape, 0..360 */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->orientation = 0;
					res->bitflags0.oriset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for orientation at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0 || num->number > 360) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number or too large number `%s' for orientation at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->orientation = rint(num->number);
					res->bitflags0.oriset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else {
			/* something else */
		}
		break;

		/* penwidth peripheries pin pos */
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
					/* allow 0.25, 1.25 etc */
					res->penwidth = num->number;
					res->bitflags0.penwidthset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "peripheries") == 0) {
			/* for polygonal shapes */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->peripheries = 1;
					res->bitflags0.periset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for peripheries at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for peripheries at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					/* is a int number */
					res->peripheries = rint(num->number);
					res->bitflags0.periset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "pin") == 0) {
			/* fixed pos of node if pos specified */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags0.pin = 0;
					res->bitflags0.pinset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for pin at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags0.pin = 1;
				} else {
					res->bitflags0.pin = 0;
				}
				res->bitflags0.pinset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "pos") == 0) {
			/* position of node %f,%f as string */
			if (r) {
				if (dp_chknum(r)) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a number `%s' for position at line %d\n", __func__, r,
						 res->yylineno);
				} else {
					if (strlen(r)) {
						res->pos = r;
					} else {
						res->pos = NULL;
					}
					res->bitflags1.posset = 1;
					/* todo parse the numbers */
				}
			}
		} else {
			/* something else */
		}
		break;

		/* rects regular root */
	case 'r':
		if (strcmp(l, "rects") == 0) {
			/* record rects as %f,%f,%f,%f as string */
			if (r) {
				if (dp_chknum(r)) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a number `%s' for rects at line %d\n", __func__, r, res->yylineno);
				} else {
					if (strlen(r)) {
						res->rects = r;
					} else {
						res->rects = NULL;
					}
					res->bitflags1.rectsset = 1;
					/* todo parse the numbers */
				}
			}
		} else if (strcmp(l, "regular") == 0) {
			/* polygon regular bool */
			boolnum = dp_getbool(r);
			if (boolnum->pe) {
				if (boolnum->es) {
					/* default */
					res->bitflags1.regular = 0;
					res->bitflags1.reguset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not a boolean `%s' for regular at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (boolnum->number) {
					res->bitflags1.regular = 1;
				} else {
					res->bitflags1.regular = 0;
				}
				res->bitflags1.reguset = 1;
			}
			dp_free(boolnum);
			boolnum = NULL;
		} else if (strcmp(l, "root") == 0) {
			/* this is not a dot but twopi keyword */
		} else {
			/* something else */
		}
		break;

		/* samplepoints shape shapefile showboxes sides skew sortv style */
	case 's':
		if (strcmp(l, "samplepoints") == 0) {
			/* int number of point for shape */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->samplepoints = 20;
					res->bitflags1.spset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for samplepoints at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for samplepoints at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					/* is a int number */
					res->samplepoints = rint(num->number);
					res->bitflags1.spset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "shape") == 0) {
			tmpi = dp_isdotshape(r);
			if (tmpi == (-1)) {
				/* todo, make into parse error */
				printf("dot %s(): unknown shape `%s' for node `%s' at line %d\n",
				       __func__, r, res->name, res->yylineno);
			} else {
				res->shape = tmpi;
				res->bitflags0.shapeset = 1;
			}
		} else if (strcmp(l, "shapefile") == 0) {
			/* external node shape */
			if (r) {
				if (strlen(r)) {
					res->shapefile = r;
				} else {
					res->shapefile = NULL;
				}
				res->bitflags1.shapefset = 1;
			}
		} else if (strcmp(l, "showboxes") == 0) {
			/* boxes in postscript, (int) 0,1,2 */
			/* int number of point for shape */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->showboxes = 0;
					res->bitflags1.showbset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for showboxes at line %d\n",
						 __func__, r, res->yylineno);
				}
			} else {
				if (num->number < 0 || num->number > 2) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number or too high number `%s' for showboxes at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					/* is a int number */
					res->showboxes = rint(num->number);
					res->bitflags1.showbset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "sides") == 0) {
			/* number of sides in a polygon shape */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* dot defaults to 4, not 3 */
					res->sides = 4;
					res->bitflags0.sidesset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for sides at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* todo: dot allows sides=0 without warning */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative number `%s' for sides at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					if (num->number < 3) {
						printf
						    ("dot %s(): sides number `%s' is too low, minimum is 3 and using now default 4\n",
						     __func__, r);
						res->sides = 4;
					} else {
						res->sides = num->number;
					}
					res->bitflags0.sidesset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "skew") == 0) {
			/* +/- skew factor polygon shape */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->skew = 0;
					res->bitflags1.skewset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for skew at line %d\n", __func__, r, res->yylineno);
				}
			} else {
				if (num->number < -100) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): too low number `%s' for skew at line %d\n", __func__, r, res->yylineno);
				} else {
					res->skew = num->number;
					res->bitflags1.skewset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "sortv") == 0) {
			/* packing modus */
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					res->sortv = 0;
					res->bitflags1.sortvset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for sortv at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): negative number `%s' for sortv at line %d\n", __func__, r,
						 res->yylineno);
				} else {
					res->sortv = rint(num->number);
					res->bitflags1.sortvset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else if (strcmp(l, "style") == 0) {
			stylenum = dp_getstyle(r);
			if (stylenum->pe) {
				if (stylenum->es) {
					/* at "" clear all */
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
					res->bitflags1.filled = 0;
					res->bitflags1.filledset = 1;
					res->bitflags1.striped = 0;
					res->bitflags1.stripedset = 1;
					res->bitflags1.wedged = 0;
					res->bitflags1.wedgedset = 1;
					res->bitflags1.dia = 0;
					res->bitflags1.diaset = 1;
					res->bitflags1.rounded = 0;
					res->bitflags1.roundedset = 1;
					res->bitflags1.radial = 0;
					res->bitflags0.radialset = 1;
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
				/* no parse errors if here, the N marked are for a node: */
				/* int slwset;  set if setlinewidth N */
				/* double slw;  setlinewidth number */
				/* int dashed;  "dashed" parsed N+E */
				/* int dotted;  "dotted" parsed N+E */
				/* int solid;   "solid" parsed N+E */
				/* int invis;   "invis" parsed N+E */
				/* int bold;    "bold" parsed N+E */
				/* int tapered; "tapered" parsed E */
				/* int filled;  "filled" parsed N+c */
				/* int striped; "striped" parsed N+c */
				/* int wedged;  "wedged" parsed N */
				/* int diagonals; "diagonals" parsed N */
				/* int rounded;  "rounded" parsed N+C */
				/* int radial;   "radial" parsed N+C+G */
				if (stylenum->tapered) {
					if (0) {	/* as error */
						memset(dp_errmsg, 0, 256);
						snprintf(dp_errmsg, (256 - 1),
							 "dot %s(): tapered does not apply to node in `%s' for style at line %d\n",
							 __func__, r, res->yylineno);
					} else {
						printf("dot %s(): tapered does not apply to node in `%s' for style at line %d\n",
						       __func__, r, res->yylineno);
					}
				} else {
					if (stylenum->slwset) {
						/* allow 0.25, 1.25 etc */
						res->penwidth = stylenum->slw;
						res->bitflags0.penwidthset = 1;
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
					if (stylenum->filled) {
						res->bitflags1.filled = 1;
						res->bitflags1.filledset = 1;
					}
					if (stylenum->striped) {
						res->bitflags1.striped = 1;
						res->bitflags1.stripedset = 1;
					}
					if (stylenum->wedged) {
						res->bitflags1.wedged = 1;
						res->bitflags1.wedgedset = 1;
					}
					if (stylenum->diagonals) {
						res->bitflags1.dia = 1;
						res->bitflags1.diaset = 1;
					}
					if (stylenum->rounded) {
						res->bitflags1.rounded = 1;
						res->bitflags1.roundedset = 1;
					}
					if (stylenum->radial) {
						res->bitflags1.radial = 1;
						res->bitflags0.radialset = 1;
					}
				}
			}
			dp_free(stylenum);
			stylenum = NULL;
		} else {
			/* something else */
		}
		break;

		/* target tooltip */
	case 't':
		if (strcmp(l, "target") == 0) {
			/* map only */
		} else if (strcmp(l, "tooltip") == 0) {
			/* cmap only */
		} else {
			/* something else */
		}
		break;

		/* vertices */
	case 'v':
		if (strcmp(l, "vertices") == 0) {
			/* coords of node polygon */
			if (r) {
				if (strlen(r)) {
					res->vertices = r;
				} else {
					res->vertices = NULL;
				}
				res->bitflags1.vertset = 1;
			}
		} else {
			/* something else */
		}
		break;

		/* width */
	case 'w':
		if (strcmp(l, "width") == 0) {
			num = dp_getnum(r);
			if (num->pe) {
				if (num->es) {
					/* default */
					res->width = 0.75;
					res->bitflags0.widthset = 1;
				} else {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): unknown number `%s' for width at line %d\n", __func__, r,
						 res->yylineno);
				}
			} else {
				/* allow 0 for prof2dot */
				if (num->number < 0) {
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "dot %s(): not allowed negative numbe `%s' for width at line %d\n",
						 __func__, r, res->yylineno);
				} else {
					res->width = num->number;
					/* min is 0.01 */
					if (res->width < 0.01) {
						printf("dot %s(): minimum value for width is 0.01 but specified is %s\n", __func__,
						       r);
						res->width = 0.01;
					}
					res->bitflags0.widthset = 1;
				}
			}
			dp_free(num);
			num = NULL;
		} else {
			/* something else */
		}
		break;

		/* z */
	case 'z':
		if (strcmp(l, "z") == 0) {
			/* neato keyword */
		} else {
			/* something else */
		}
		break;

		/* URL */
	case 'U':
		if (strcmp(l, "URL") == 0) {
			/* url node */
			if (r) {
				if (strlen(r)) {
					res->url = NULL;
				} else {
					res->url = NULL;
				}
				res->bitflags1.urlset = 1;
			}
		} else {
			/* something else */
		}
		break;

	default:
		/* something else */
		break;
	}

	/* dot supports html label in record shapes.
	 * todo in gml4gtk not yet supported.
	 */
	if (res->shape == DPSHAPE_RECORD || res->shape == DPSHAPE_MRECORD) {
		if (res->bitflags0.labelset) {
			if (res->htmllabel) {
				printf("%s(): html label in record node shape not yet supported in node \"%s\"\n", __func__,
				       dp_curnode->name);
				/* turn it off */
				res->shape = 0;
				res->bitflags0.shapeset = 0;
				res->label = dp_curnode->name;
				res->bitflags0.labelset = 1;
				res->htmllabel = 0;
			}
		}
	}

	fflush(stdout);

	return;
}

/* set factory default */
void dp_nodefdef(struct dpnode *n)
{

	/* no style=filled */

	/* fillcolor is white rgb #00ffffff */

	/* bordercolor is black rgb #00000000 */

	/* fontcolor is black rgb #00000000 */

	n->penwidth = 1;
	n->bitflags0.penwidthset = 1;

	/* width of node, min. 0.01 */
	n->width = 0.75;
	n->bitflags0.widthset = 1;

	/* height of node, min. 0.02 */
	n->height = 0.5;
	n->bitflags0.heightset = 1;

	/* group is (char *)0 */

	/* comment is (char *)0 */

	/* distortion for polygon is 0.0 */

	/* fontname = (char *)0 */

	/* fontsize is 14 */
	n->fontsize = 14.0;
	n->bitflags0.fontsizeset = 1;

	/* imagemap id is (char *)0 */

	/* label is default node name if not specified or \N
	 * n->label = n->name;
	 * n->bitflags0.labelset = 1;
	 */

	/* image is (char *)0 */

	/* imagescale is false */

	/* label location is center */
	n->labelloc = DP_LLC;
	n->bitflags0.labellset = 1;

	/* layer is (char *)0 */

	/* margin is (char *)0, has 2 fp numbers */

	/* nojustify is 0 false */

	/* orientation is 0 */

	/* for polygon shapes */
	n->peripheries = 1;
	n->bitflags0.periset = 1;

	/* pin is bool false 0 */

	/* pos is 0,0 as (char *)0 */

	/* rects is %f,%f,%f,%f (char *)0 as string */

	/* regular is false */

	/* number of points for shape */
	n->samplepoints = 20;
	n->bitflags1.spset = 1;

	/* number of sides in polygon, 4 is a rectangle */
	n->sides = 4;
	n->bitflags0.sidesset = 1;

	/* shape is ellipse */

	/* shapefile is (char *)0 */

	/* showboxes is (int)0 */

	/* skew is 0.0 */

	/* sortv is 0 */

	/* vertices = (char *)0 */

	/* url is (char *)0 */

	return;
}

/* set graph default */
void dp_nodegdef(struct dpnode *from, struct dpnode *n)
{

	/* optional colorscheme */
	if (from->bitflags0.csnumset) {
		n->csnum = from->csnum;
		n->bitflags0.csnumset = 1;
	}

	/* fillcolor */
	if (from->bitflags0.fcolorset) {
		n->fcolor = from->fcolor;
		n->bitflags0.fcolorset = 1;
	}

	/* fontcolor */
	if (from->bitflags0.fontcolorset) {
		n->fontcolor = from->fontcolor;
		n->bitflags0.fontcolorset = 1;
	}

	/* color */
	if (from->bitflags0.colorset) {
		n->color = from->color;
		n->bitflags0.colorset = 1;
	}

	/* node shape */
	if (from->bitflags0.shapeset) {
		n->shape = from->shape;
		n->bitflags0.shapeset = 1;
	}

	/* node style */
	if (from->bitflags1.dashedset) {
		n->bitflags1.dashed = from->bitflags1.dashed;
		n->bitflags1.dashedset = 1;
	}

	if (from->bitflags1.dottedset) {
		n->bitflags1.dotted = from->bitflags1.dotted;
		n->bitflags1.dottedset = 1;
	}

	if (from->bitflags1.solidset) {
		n->bitflags1.solid = from->bitflags1.solid;
		n->bitflags1.solidset = 1;
	}

	if (from->bitflags1.invisset) {
		n->bitflags1.invis = from->bitflags1.invis;
		n->bitflags1.invisset = 1;
	}

	if (from->bitflags1.boldset) {
		n->bitflags1.bold = from->bitflags1.bold;
		n->bitflags1.boldset = 1;
	}

	if (from->bitflags1.filledset) {
		n->bitflags1.filled = from->bitflags1.filled;
		n->bitflags1.filledset = 1;
	}

	if (from->bitflags1.stripedset) {
		n->bitflags1.striped = from->bitflags1.striped;
		n->bitflags1.stripedset = 1;
	}

	if (from->bitflags1.wedgedset) {
		n->bitflags1.wedged = from->bitflags1.wedged;
		n->bitflags1.wedgedset = 1;
	}

	if (from->bitflags1.diaset) {
		n->bitflags1.dia = from->bitflags1.dia;
		n->bitflags1.diaset = 1;
	}

	if (from->bitflags1.roundedset) {
		n->bitflags1.rounded = from->bitflags1.rounded;
		n->bitflags1.roundedset = 1;
	}

	if (from->bitflags0.radialset) {
		n->bitflags1.radial = from->bitflags1.radial;
		n->bitflags0.radialset = 1;
	}

	/* border line thickness */
	if (from->bitflags0.penwidthset) {
		n->penwidth = from->penwidth;
		n->bitflags0.penwidthset = 1;
	}

	/* number of sides in polygon */
	if (from->bitflags0.sidesset) {
		n->sides = from->sides;
		n->bitflags0.sidesset = 1;
	}

	/* width of node */
	if (from->bitflags0.widthset) {
		n->width = from->width;
		n->bitflags0.widthset = 1;
	}

	/* height of node */
	if (from->bitflags0.heightset) {
		n->height = from->height;
		n->bitflags0.heightset = 1;
	}

	/* bool use node width fixedsize in width param */
	if (from->bitflags0.fixsizeset) {
		n->bitflags0.fixsize = from->bitflags0.fixsize;
		n->bitflags0.fixsizeset = 1;
	}

	/* group */
	if (from->bitflags0.groupset) {
		n->group = from->group;
		n->bitflags0.groupset = 1;
	}

	/* comment */
	if (from->bitflags0.comset) {
		n->comment = from->comment;
		n->bitflags0.comset = 1;
	}

	/* distortion for shape polygon */
	if (from->bitflags0.distortionset) {
		n->distortion = from->distortion;
		n->bitflags0.distortionset = 1;
	}

	/* char * fontname */
	if (from->bitflags0.fontnameset) {
		n->fontname = from->fontname;
		n->bitflags0.fontnameset = 1;
	}

	/* fontsize */
	if (from->bitflags0.fontsizeset) {
		n->fontsize = from->fontsize;
		n->bitflags0.fontsizeset = 1;
	}

	/* imagemap id */
	if (from->bitflags0.idset) {
		n->id = from->id;
		n->bitflags0.idset = 1;
	}

	/* node label */
	if (from->bitflags0.labelset) {
		n->label = from->label;
		n->bitflags0.labelset = 1;
	}

	/* image for node */
	if (from->bitflags0.imgset) {
		n->image = from->image;
		n->bitflags0.imgset = 1;
	}

	/* bool imagescale */
	if (from->bitflags0.iscaleset) {
		n->bitflags0.iscale = from->bitflags0.iscale;
		n->bitflags0.iscaleset = 1;
	}

	/* label location */
	if (from->bitflags0.labellset) {
		n->labelloc = from->labelloc;
		n->bitflags0.labellset = 1;
	}

	/* layer control string */
	if (from->bitflags0.layerset) {
		n->layer = from->layer;
		n->bitflags0.layerset = 1;
	}

	/* margin string, 2 fp numbers */
	if (from->bitflags0.marginset) {
		n->margin = from->margin;
		n->marginx = from->marginx;
		n->marginy = from->marginy;
		n->bitflags0.marginset = 1;
	}

	/* nojustify bool */
	if (from->bitflags0.nojustset) {
		n->bitflags0.nojust = from->bitflags0.nojust;
		n->bitflags0.nojustset = 1;
	}

	/* rotate polygon shape, 0..360 */
	if (from->bitflags0.oriset) {
		n->orientation = from->orientation;
		n->bitflags0.oriset = 1;
	}

	/* for polygon shapes */
	if (from->bitflags0.periset) {
		n->peripheries = from->peripheries;
		n->bitflags0.periset = 1;
	}

	/* fixed pos of node */
	if (from->bitflags0.pinset) {
		n->bitflags0.pin = from->bitflags0.pin;
		n->bitflags0.pinset = 1;
	}

	/* pos of node %f,%f as string */
	if (from->bitflags1.posset) {
		n->pos = from->pos;
		n->bitflags1.posset = 1;
	}

	/* rect */
	if (from->bitflags1.rectsset) {
		n->rects = from->rects;
		n->bitflags1.rectsset = 1;
	}

	/* regular polygon bool */
	if (from->bitflags1.reguset) {
		n->bitflags1.regular = from->bitflags1.regular;
		n->bitflags1.reguset = 1;
	}

	/* number of points for shape */
	if (from->bitflags1.spset) {
		from->samplepoints = from->samplepoints;
		n->bitflags1.spset = 1;
	}

	/* external node shape */
	if (from->bitflags1.shapefset) {
		n->shapefile = from->shapefile;
		n->bitflags1.shapefset = 1;
	}

	/* postscript showboxes, 0,1,2 */
	if (from->bitflags1.showbset) {
		n->showboxes = from->showboxes;
		n->bitflags1.showbset = 1;
	}

	/* polygon skew factor */
	if (from->bitflags1.skewset) {
		n->skew = from->skew;
		n->bitflags1.skewset = 1;
	}

	/* packing modus */
	if (from->bitflags1.sortvset) {
		n->sortv = from->sortv;
		n->bitflags1.sortvset = 1;
	}

	/* coord of polygon string */
	if (from->bitflags1.vertset) {
		n->vertices = from->vertices;
		n->bitflags1.vertset = 1;
	}

	/* url */
	if (from->bitflags1.urlset) {
		n->url = from->url;
		n->bitflags1.urlset = 1;
	}

	return;
}

/* end */
