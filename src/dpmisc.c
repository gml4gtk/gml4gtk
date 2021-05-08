
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

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpmisc.h"
#include "dpus.h"
#include "dot.tab.h"
#include "dpcolor.h"
#include "dphl.h"
#include "dpmem.h"

/* parse edge arrow style todo:
 * name = aname[anema[anema[aname]]]
 * aname = [mod] shape
 * mod = ['o'] side
 * side = 'l' | 'r'
 * shape = box
 *  | crow
 *  | curve
 *  | icurve
 *  | diamond
 *  | dot
 *  | inv
 *  | none
 *  | normal
 *  | tee
 *  | vee
 */
struct dparrow *dp_getarrow(char *s)
{
	struct dparrow *ret = NULL;
	int t = 0;

	ret = dp_calloc(1, sizeof(struct dparrow));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	/* the raw name */
	ret->name = dp_uniqstr(s);

	/* parse the basic shapes */
	if (strcasecmp(s, "box") == 0) {
		t = DP_EA_BOX;
	} else if (strcasecmp(s, "crow") == 0) {
		t = DP_EA_CROW;
	} else if (strcasecmp(s, "curve") == 0) {
		t = DP_EA_CURVE;
	} else if (strcasecmp(s, "icurve") == 0) {
		t = DP_EA_ICURVE;
	} else if (strcasecmp(s, "diamond") == 0) {
		t = DP_EA_DIAMOND;
	} else if (strcasecmp(s, "dot") == 0) {
		t = DP_EA_DOT;
	} else if (strcasecmp(s, "inv") == 0) {
		t = DP_EA_INV;
	} else if (strcasecmp(s, "none") == 0) {
		t = DP_EA_NONE;
	} else if (strcasecmp(s, "normal") == 0) {
		t = DP_EA_NORMAL;
	} else if (strcasecmp(s, "tee") == 0) {
		t = DP_EA_TEE;
	} else if (strcasecmp(s, "vee") == 0) {
		t = DP_EA_VEE;
	} else {
		t = DP_EA_UNKNOWN;
	}

	/* todo parse the full string with all modifiers */
	ret->type = t;

	return (ret);
}

/* edge arrow direction */
struct dpdir *dp_getdir(char *s)
{
	struct dpdir *ret = NULL;

	ret = dp_calloc(1, sizeof(struct dpdir));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	if (strcasecmp(s, "none") == 0) {
		ret->type = DP_DIR_NONE;
	} else if (strcasecmp(s, "both") == 0) {
		ret->type = DP_DIR_BOTH;
	} else if (strcasecmp(s, "back") == 0) {
		ret->type = DP_DIR_BACK;
	} else if (strcasecmp(s, "forward") == 0) {
		ret->type = DP_DIR_FORWARD;
	} else {
		/* unknown is type=0 */
		ret->pe = 1;
	}

	return (ret);
}

/* return 0 if str is a number string */
int dp_chknum(char *str)
{
	int c = 0;
	char *p = NULL;
	if (str == NULL) {
		return (0);
	}
	if (strlen(str) == 0) {
		return (0);
	}
	c = 0;
	p = str;
	while (*p) {
		switch (*p) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case ' ':
		case ',':
		case '.':
		case '-':	/* for negative numbers */
			break;
		default:
			c++;
			break;
		}
		if (c) {
			break;
		}
		p++;
	}
	return (c);
}

/* return 1 if is a compass point */
int dp_iscompass(char *compass)
{
	int yes = 0;
	if (compass == NULL) {
		return (0);
	}
	/* check for valid compass point */
	yes = 1;
	if (strcmp(compass, "n") == 0) {
	} else if (strcmp(compass, "ne") == 0) {
	} else if (strcmp(compass, "e") == 0) {
	} else if (strcmp(compass, "se") == 0) {
	} else if (strcmp(compass, "s") == 0) {
	} else if (strcmp(compass, "sw") == 0) {
	} else if (strcmp(compass, "w") == 0) {
	} else if (strcmp(compass, "nw") == 0) {
	} else if (strcmp(compass, "c") == 0) {
		/* c is center of node */
	} else if (strcmp(compass, "_") == 0) {
	} else {
		/* not valid */
		yes = 0;
	}
	return (yes);
}

/* is a known shape name, -1 at error */
int dp_isdotshape(char *s)
{
	int ret = -1;
	if (s == NULL) {
		return (-1);
	}
	if (strlen(s) == 0) {
		return (DPSHAPE_ELLIPSE);
	}
	if (strcasecmp("assembly", s) == 0) {
		ret = DPSHAPE_ASSEMBLY;
	} else if (strcasecmp("box", s) == 0) {
		ret = DPSHAPE_BOX;
	} else if (strcasecmp("box3d", s) == 0) {
		ret = DPSHAPE_BOX3D;
	} else if (strcasecmp("cds", s) == 0) {
		ret = DPSHAPE_CDS;
	} else if (strcasecmp("circle", s) == 0) {
		ret = DPSHAPE_CIRCLE;
	} else if (strcasecmp("component", s) == 0) {
		ret = DPSHAPE_COMPONENT;
	} else if (strcasecmp("cylinder", s) == 0) {
		ret = DPSHAPE_CYLINDER;
	} else if (strcasecmp("diamond", s) == 0) {
		ret = DPSHAPE_DIAMOND;
	} else if (strcasecmp("doublecircle", s) == 0) {
		ret = DPSHAPE_DOUBLECIRCLE;
	} else if (strcasecmp("doubleoctagon", s) == 0) {
		ret = DPSHAPE_DOUBLEOCTAGON;
	} else if (strcasecmp("egg", s) == 0) {
		ret = DPSHAPE_EGG;
	} else if (strcasecmp("ellipse", s) == 0) {
		ret = DPSHAPE_ELLIPSE;
	} else if (strcasecmp("fivepoverhang", s) == 0) {
		ret = DPSHAPE_FIVEPOVERHANG;
	} else if (strcasecmp("folder", s) == 0) {
		ret = DPSHAPE_FOLDER;
	} else if (strcasecmp("hexagon", s) == 0) {
		ret = DPSHAPE_HEXAGON;
	} else if (strcasecmp("house", s) == 0) {
		ret = DPSHAPE_HOUSE;
	} else if (strcasecmp("insulator", s) == 0) {
		ret = DPSHAPE_INSULATOR;
	} else if (strcasecmp("invhouse", s) == 0) {
		ret = DPSHAPE_INVHOUSE;
	} else if (strcasecmp("invtrapezium", s) == 0) {
		ret = DPSHAPE_INVTRAPEZIUM;
	} else if (strcasecmp("invtriangle", s) == 0) {
		ret = DPSHAPE_INVTRIANGLE;
	} else if (strcasecmp("larrow", s) == 0) {
		ret = DPSHAPE_LARROW;
	} else if (strcasecmp("lpromoter", s) == 0) {
		ret = DPSHAPE_LPROMOTOR;
	} else if (strcasecmp("Mcircle", s) == 0) {
		ret = DPSHAPE_MCIRCLE;
	} else if (strcasecmp("Mdiamond", s) == 0) {
		ret = DPSHAPE_MDIAMOND;
	} else if (strcasecmp("Msquare", s) == 0) {
		ret = DPSHAPE_MSQUARE;
	} else if (strcasecmp("Mrecord", s) == 0) {
		/* special */
		ret = DPSHAPE_MRECORD;
	} else if (strcasecmp("none", s) == 0) {
		ret = DPSHAPE_NONE;
	} else if (strcasecmp("note", s) == 0) {
		ret = DPSHAPE_NOTE;
	} else if (strcasecmp("noverhang", s) == 0) {
		ret = DPSHAPE_NOVERHANG;
	} else if (strcasecmp("octagon", s) == 0) {
		ret = DPSHAPE_OCTAGON;
	} else if (strcasecmp("oval", s) == 0) {
		ret = DPSHAPE_OVAL;
	} else if (strcasecmp("parallelogram", s) == 0) {
		ret = DPSHAPE_PARALLELOGRAM;
	} else if (strcasecmp("pentagon", s) == 0) {
		ret = DPSHAPE_PENTAGON;
	} else if (strcasecmp("plain", s) == 0) {
		ret = DPSHAPE_PLAIN;
	} else if (strcasecmp("plaintext", s) == 0) {
		ret = DPSHAPE_PLAINTEXT;
	} else if (strcasecmp("point", s) == 0) {
		ret = DPSHAPE_POINT;
	} else if (strcasecmp("polygon", s) == 0) {
		ret = DPSHAPE_POLYGON;
	} else if (strcasecmp("primersite", s) == 0) {
		ret = DPSHAPE_PRIMERSITE;
	} else if (strcasecmp("promoter", s) == 0) {
		ret = DPSHAPE_PROMOTER;
	} else if (strcasecmp("proteasesite", s) == 0) {
		ret = DPSHAPE_PROTEASESITE;
	} else if (strcasecmp("proteinstab", s) == 0) {
		ret = DPSHAPE_PROTEINSTAB;
	} else if (strcasecmp("rarrow", s) == 0) {
		ret = DPSHAPE_RARROW;
	} else if (strcasecmp("record", s) == 0) {
		/* special */
		ret = DPSHAPE_RECORD;
	} else if (strcasecmp("rect", s) == 0) {
		ret = DPSHAPE_RECT;
	} else if (strcasecmp("rectangle", s) == 0) {
		ret = DPSHAPE_RECTANGLE;
	} else if (strcasecmp("restrictionsite", s) == 0) {
		ret = DPSHAPE_RESTRICTIONSITE;
	} else if (strcasecmp("ribosite", s) == 0) {
		ret = DPSHAPE_RIBOSITE;
	} else if (strcasecmp("rnastab", s) == 0) {
		ret = DPSHAPE_RNASTAB;
	} else if (strcasecmp("rpromoter", s) == 0) {
		ret = DPSHAPE_RPROMOTER;
	} else if (strcasecmp("septagon", s) == 0) {
		ret = DPSHAPE_SEPTAGON;
	} else if (strcasecmp("signature", s) == 0) {
		ret = DPSHAPE_SIGNATURE;
	} else if (strcasecmp("square", s) == 0) {
		ret = DPSHAPE_SQUARE;
	} else if (strcasecmp("star", s) == 0) {
		ret = DPSHAPE_STAR;
	} else if (strcasecmp("tab", s) == 0) {
		ret = DPSHAPE_TAB;
	} else if (strcasecmp("terminator", s) == 0) {
		ret = DPSHAPE_TERMINATOR;
	} else if (strcasecmp("threepoverhang", s) == 0) {
		ret = DPSHAPE_THREEPOVERHANG;
	} else if (strcasecmp("trapezium", s) == 0) {
		ret = DPSHAPE_TRAPEZIUM;
	} else if (strcasecmp("triangle", s) == 0) {
		ret = DPSHAPE_TRIANGLE;
	} else if (strcasecmp("tripleoctagon", s) == 0) {
		ret = DPSHAPE_TRIPLEOCTAGON;
	} else if (strcasecmp("underline", s) == 0) {
		ret = DPSHAPE_UNDERLINE;
	} else if (strcasecmp("utr", s) == 0) {
		ret = DPSHAPE_UTR;
	} else {
		/* unknown node shape */
		ret = -1;
	}
	return (ret);
}

/* labelloc can be t,b,c, for graph only t,b */
int dp_islabelloc(char *loc)
{
	int ret = 0;
	if (loc == NULL) {
		return (DP_LLC);
	}
	/* use default 'c' at "" */
	if (strlen(loc) == 0) {
		return (DP_LLC);
	}
	if (strcasecmp("t", loc) == 0) {
		ret = DP_LLT;
	} else if (strcasecmp("b", loc) == 0) {
		ret = DP_LLB;
	} else if (strcasecmp("c", loc) == 0) {
		ret = DP_LLC;
	} else {
		/* wrong value */
		ret = 0;
	}
	return (ret);
}

/* tmp label char */
static char *clb = NULL;
static size_t clblen = 0;

/* parse */
static struct dppart *dp_2chkrec(struct dpnode *node, int dir)
{
	struct dppart *nrec = NULL;
	struct dppart *fp = NULL;
	char *s = NULL;
	int c = 0;
	int nf = 0;
	char *rs1 = NULL;
	char *prs = NULL;
	char *prt = NULL;
	char *pprt = NULL;
	int pos1 = 0;
	int maxpos = 0;
	int ndir = 0;
	char *lastport = NULL;
	char *lastfield = NULL;
	int hassub = 0;

	nrec = (struct dppart *)dp_calloc(1, sizeof(struct dppart));

	if (nrec == NULL) {
		/* shouldnothappen */
		return (nrec);
	}

	/* get number of fields now */
	s = clb;
	c = 0;
	nf = 0;

	while (*s) {
		if ((*s) == '\\') {
			s++;
			if ((*s) == 0) {
				break;
			}
		} else {
			if ((*s) == '{') {
				/* increase nesting count */
				c++;
			} else if ((*s) == '}') {
				c--;
			} else if ((*s) == '|') {
				if (c == 0) {
					nf++;
				}
			} else {
				/* nop */
			}
		}
		if (c < 0) {
			break;
		}
		s++;
	}

	/* todo valgrind says memleak and errors in this routine */
	/* tmp fix (nrec->ndpparts + 1) */
	nrec->dir = dir;
	nrec->ndpparts = (nf + 1);
	nrec->parts = dp_calloc(1, ((nrec->ndpparts + 0) * sizeof(struct dppart *)));
	maxpos = (nf + 1);

	if (nrec->parts == NULL) {
		return (NULL);
	}

	if (yydebug || 0) {
		printf("dot %s(): %d parts with direction %d\n", __func__, nrec->ndpparts, nrec->dir);
		fflush(stdout);
	}

	/* tmp buffer for string and port */
	rs1 = (char *)dp_calloc(1, clblen + 1);

	if (rs1 == NULL) {
		return (NULL);
	}

	lastfield = NULL;

	prt = (char *)dp_calloc(1, clblen + 1);

	if (prt == NULL) {
		return (NULL);
	}

	pprt = prt;
	lastport = NULL;

	pos1 = 0;

	while (*clb) {
		/* get port as in "<portname>" creating string in lastport */
		if ((*clb) == '<') {
			lastport = NULL;
			clb++;
			while (*clb) {
				if (*clb == '>') {
					break;
				}
				if (*clb == '\\') {
					(*pprt) = (*clb);
					pprt++;
					clb++;
					(*pprt) = (*clb);
					pprt++;
					clb++;
				} else {
					(*pprt) = (*clb);
					pprt++;
					clb++;
				}
			}
			lastport = dp_uniqstr(prt);
			memset(prt, 0, clblen + 1);
			pprt = prt;
			if (*clb) {
				clb++;
			}
		} else if ((*clb) == '{') {
			clb++;
			/* toggle direction */
			if (dir == 0) {
				/* vertical */
				ndir = 1;
			} else {
				/* horizontal */
				ndir = 0;
			}
			hassub = 1;
			fp = dp_2chkrec(node, ndir);
			nrec->parts[pos1] = fp;
			pos1++;
		} else if ((*clb) == '}' || (*clb) == '|') {
			fp = (struct dppart *)dp_calloc(1, sizeof(struct dppart));

			if (fp == NULL) {
				return (NULL);
			}

			/* check for "{aa|bb|}" */
			if (*clb == '}') {
				if (*(clb - 1) == '|') {
					lastfield = dp_uniqstr(" ");
				}
			}
			/* for "|aa", "|", "aa||bb" */
			if (*clb == '|') {
				if (lastfield == NULL) {
					lastfield = dp_uniqstr(" ");
				}
			}
			fp->lp = lastfield;
			fp->id = lastport;
			fp->dir = dir;
			if (lastfield || lastport) {
				fp->hd = 1;
			}
			if (fp->hd || fp->id || fp->lp) {
				if (hassub == 0) {
					if (pos1 >= maxpos) {
						printf("dot %s(): pos1=%d maxpos=%d fixme (1)\n", __func__, pos1, maxpos);
					}
					nrec->parts[pos1] = fp;
					pos1++;
				} else {
					/* nothing if at "...}|..." */
					dp_free(fp);
					fp = NULL;
				}
				hassub = 0;
			} else {
				dp_free(fp);
				fp = NULL;
			}
			lastfield = NULL;
			lastport = NULL;
			if ((*clb) == '}') {
				clb++;

				if (rs1) {
					dp_free(rs1);
					rs1 = NULL;
				}
				if (prt) {
					dp_free(prt);
					prt = NULL;
				}
				return (nrec);
			}

			if (*clb) {
				clb++;
			}

		} else {
			prs = rs1;
			/* copy field part */
			while (*clb) {
				if (*clb == '{' || *clb == '}' || *clb == '|' || *clb == '<' || *clb == '>') {
					/* stop on ctrl char */
					break;
				}
				/* copy to text part */
				if ((*clb) == '\\') {
					(*prs) = (*clb);
					prs++;
					clb++;
					(*prs) = (*clb);
					prs++;
					clb++;
				} else {
					(*prs) = (*clb);
					prs++;
					clb++;
				}
			}
			lastfield = dp_uniqstr(rs1);
			memset(rs1, 0, (clblen + 1));
		}

	}

	/* */
	fp = (struct dppart *)dp_calloc(1, sizeof(struct dppart));

	if (fp == NULL) {
		return (NULL);
	}

	/* example "aa|bb|" or "aa|bb|<pos>" */
	if ((*(clb - 1) == '|') || (*(clb - 1) == '>')) {
		lastfield = dp_uniqstr(" ");
		fp->hd = 1;
	}
	fp->lp = lastfield;

	if (lastfield || lastport) {
		fp->hd = 1;
	}

	fp->id = lastport;
	fp->dir = dir;

	if (fp->hd || fp->id || fp->lp) {
		if (pos1 >= maxpos) {
			/* this happens normally */
			if (0) {
				printf
				    ("dot %s(): pos1=%d maxpos=%d fixme (2) id=\"%s\" lp=\"%s\"\n",
				     __func__, pos1, maxpos, lastfield, lastport);
			}
			dp_free(fp);
			fp = NULL;
		} else {
			nrec->parts[pos1] = fp;
		}
	} else {
		dp_free(fp);
		fp = NULL;
	}

	if (rs1) {
		dp_free(rs1);
		rs1 = NULL;
	}
	if (prt) {
		dp_free(prt);
		prt = NULL;
	}

	return (nrec);
}

static void dp_1chkrecpr(struct dppart *info, int ind)
{
	int i = 0;

	if (info == NULL) {
		printf("dot %s(): nil info\n", __func__);
		return;
	}
	for (i = 0; i < ind; i++) {
		printf("  ");
	}

	printf("%p---begin\n", (void *)info);

	for (i = 0; i < ind; i++) {
		printf("\t");
	}

	printf("`%s' `%s' %d parts dir=%d hd=%d\n", info->id, info->lp, info->ndpparts, info->dir, info->hd);

	for (i = 0; i < info->ndpparts; i++) {
		ind++;
		if (info->parts[i]) {
			dp_1chkrecpr(info->parts[i], (ind + 1));
		}
		ind--;
	}

	for (i = 0; i < ind; i++) {
		printf("  ");
	}

	printf("%p---end\n", (void *)info);
	return;
}

/* check 1 node record label */
static int dp_1chkrec(struct dpnode *node)
{
	int bo = 0;
	int bc = 0;
	char *p = NULL;
	int status = 0;
	struct dppart *inf = NULL;

	/* check for matching {} in string */
	p = node->label;
	status = 0;

	if (p == NULL) {
		return (0);
	}

	/* if "" */
	if (strlen(p) == 0) {
		/* oke */
		return (0);
	}

	bo = 0;
	bc = 0;
	while ((*p)) {
		if ((*p) == '\\') {
			p++;
			if ((*p) == 0) {
				break;
			}
		} else if (((*p) == '{') || ((*p) == '<')) {
			bo++;
		} else if (((*p) == '}') || ((*p) == '>')) {
			bc++;
		} else {	/* nop */
		}
		p++;
	}

	/* check for matching {} and issue error */
	if (bo != bc) {
		/* todo change in parse error */
		memset(dp_errmsg, 0, (256 - 1));
		snprintf(dp_errmsg, (256 - 1),
			 "dot %s(): mismatch in record label string in node `%s' at line %d\n", __func__, node->name,
			 node->yylineno);
		return (1);
	}

	/* string is oke, parse rest of format string */
	clb = node->label;
	clblen = strlen(clb);
	inf = dp_2chkrec(node, /* direction hor. */ 0);
	if (yydebug || 0) {
		dp_1chkrecpr(inf, 0);
	}
	fflush(stdout);
	/* tmp label char */
	clb = NULL;
	clblen = 0;
	node->labelinfo = inf;
	return (status);
}

/* check nodes with record labels */
static int dp_chkrec(void)
{
	int status = 0;
	struct dpnlink *nl = NULL;
	nl = dp_anodes;
	while (nl) {
		status = 0;
		if (nl->n->shape == DPSHAPE_RECORD || nl->n->shape == DPSHAPE_MRECORD) {
			status = dp_1chkrec(nl->n);
		}
		if (status) {
			break;
		}
		nl = nl->next;
	}

	return (status);
}

/* check one node html label starting with '<' */
static int dp1_chkhmln(struct dpnode *node)
{
	int status = 0;
	status = htmlparse(node);
	if (status) {		/*parse error */
	}
	return (status);
}

/* check nodes with html labels */
static int dp_chkhtmln(void)
{
	int status = 0;
	struct dpnlink *nl = NULL;
	nl = dp_anodes;
	while (nl) {
		if (nl->n->name == NULL) {
			/* shouldnothappen */
			printf("%s(): nil node name for node with label \"%s\"\n", __func__, nl->n->label);
		}
		if (nl->n->label) {
			if (strlen(nl->n->label) > 0) {
				/* non-record shape node with optional <> html label */
				if (nl->n->htmllabel) {
					status = dp1_chkhmln(nl->n);
				}
				if (yydebug || 0) {
					printf("%s(): node \"%s\" html-label=%d ", __func__, nl->n->name, nl->n->htmllabel);
					if (nl->n->htmllabel) {
						if (nl->n->hlinfo) {
							printf("hlinfo=%p mode=%d il=%p tl=%p\n", (void *)nl->n->hlinfo,
							       nl->n->hlinfo->mode, (void *)nl->n->hlinfo->il,
							       (void *)nl->n->hlinfo->tl);
						} else {
							printf("hlinfo=nil\n");
						}
					} else {
						printf("\n");
					}
				}
				if (status) {
					break;
				}
			}
		}
		nl = nl->next;
	}

	return (status);
}

/* check data, return 0 if oke. */
int dp_datachk(void)
{
	int status1 = 0;
	int status2 = 0;
	/* check nodes with record labels */
	status1 = dp_chkrec();
	if (yydebug || 0) {
		printf("%s(): status=%d dp_chkrec();\n", __func__, status1);
	}
	/* check nodes with html labels */
	status2 = dp_chkhtmln();
	if (yydebug || 0) {
		printf("%s(): status=%d dp_chkhtmln();\n", __func__, status2);
	}
	/* check edges with html labels */
	/* todo */
	if (yydebug || 0) {
		printf("%s(): status=%d\n", __func__, status1 + status2);
	}
	return (status1 + status2);
}

/* parse number, use default at "" string */
struct dpnum *dp_getnum(char *s)
{
	struct dpnum *ret = NULL;
	double n = 0.0;
	char *ep = NULL;

	ret = dp_calloc(1, sizeof(struct dpnum));

	if (ret == NULL) {
		return (NULL);
	}

	if (s == NULL) {
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->es = 1;
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	errno = 0;

	n = strtod(s, &ep);

	if (ep) {
		if (strlen(ep)) {
			/* parse error */
			ret->pe = 1;
			return (ret);
		}
	}

	if (errno) {
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	/* check for unusual "-0", different languages handle -0 different, go language does not implement -0 correctly */
	if (n == 0) {
		if (strchr(s, '-')) {
			printf("%s(): number `%s' is negative zero\n", __func__, s);
		}
	}

	ret->number = n;
	ret->pe = 0;
	ret->es = 0;

	return (ret);
}

/* parse int number */
struct dpinum *dp_getinum(char *s)
{
	struct dpinum *ret = NULL;
	long n = 0;
	char *ep = NULL;

	ret = dp_calloc(1, sizeof(struct dpinum));

	if (ret == NULL) {
		return (NULL);
	}

	if (s == NULL) {
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->es = 1;
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	errno = 0;

	/* base 10 */
	n = strtol(s, &ep, 10);

	if (ep) {
		if (strlen(ep)) {
			/* parse error */
			ret->pe = 1;
			return (ret);
		}
	}

	if (errno) {
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	/* check for unusual "-0" */
	if (n == 0) {
		if (strchr(s, '-')) {
			printf("%s(): number `%s' is negative zero\n", __func__, s);
		}
	}

	ret->number = (int)n;
	ret->pe = 0;
	ret->es = 0;

	return (ret);
}

/* parse boolean
 * dot accepts also " No " and " Yes " with the spaces,
 * this does now accept strings as "  true" or " 1   "
 */
struct dpbool *dp_getbool(char *s)
{
	struct dpbool *ret = NULL;
	char *s2 = NULL;
	char *p = NULL;
	char *q = NULL;

	ret = dp_calloc(1, sizeof(struct dpbool));

	if (ret == NULL) {
		return (NULL);
	}

	if (s == NULL) {
		/* parse error */
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		/* parse error */
		ret->es = 1;
		ret->pe = 1;
		return (ret);
	}

	s2 = dp_calloc(1, (strlen(s) + 1));

	if (s2 == NULL) {
		ret->es = 1;
		ret->pe = 1;
		return (ret);
	}

	/* skip leading spaces */
	p = s;

	while (*p) {
		if (*p != ' ') {
			break;
		}
		p++;
	}

	/* copy chars until trailing spaces */
	q = s2;

	while (*p) {
		if (*p == ' ') {
			break;
		}
		*q = *p;
		p++;
		q++;
	}

	if (strcasecmp(s2, "true") == 0) {
		ret->number = 1;
	} else if (strcasecmp(s2, "false") == 0) {
		ret->number = 0;
	} else if (strcasecmp(s2, "1") == 0) {
		ret->number = 1;
	} else if (strcasecmp(s2, "0") == 0) {
		ret->number = 0;
	} else if (strcasecmp(s2, "on") == 0) {
		ret->number = 1;
	} else if (strcasecmp(s2, "off") == 0) {
		ret->number = 0;
	} else if (strcasecmp(s2, "yes") == 0) {
		ret->number = 1;
	} else if (strcasecmp(s2, "no") == 0) {
		ret->number = 0;
	} else {
		/* parse error */
		ret->pe = 1;
	}

	dp_free(s2);

	return (ret);
}

/* parse color */
struct dpcolor *dp_getcolor(int cs, int csnum, char *s)
{
	struct dpcolor *ret = NULL;
	int tmpi = 0;

	ret = dp_calloc(1, sizeof(struct dpcolor));

	if (ret == NULL) {
		return (NULL);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	if (cs) {
		tmpi = dp_findcolor(csnum, s);
	} else {
		tmpi = dp_findcolor(0, s);
	}

	if (tmpi == -1) {
		ret->pe = 1;
		return (ret);
	}

	if (tmpi == -2) {
		ret->islist = 1;
		ret->pe = 1;
		return (ret);
	}

	if (tmpi == -3) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	ret->color = tmpi;

	return (ret);
}

/* parse style= */
struct dpstyle *dp_getstyle(char *s)
{
	struct dpstyle *ret = NULL;
	size_t lens = 0;
	char *buf = NULL;
	char *sep = NULL;
	char *token = NULL;
	int slwnext = 0;
	double n = 0.0;
	char *ep = NULL;

	ret = dp_calloc(1, sizeof(struct dpstyle));

	if (ret == NULL) {
		return (NULL);
	}

	if (s == NULL) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	lens = strlen(s);

	if (lens == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	/* copy string in tmp buffer */
	buf = dp_calloc(1, (lens + 1));

	if (buf == NULL) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	strcpy(buf, s);

	/* possible seperators in string */
	sep = dp_uniqstr(",() ");

	slwnext = 0;

	/* strsep() is a replacement for old strtok() */
	token = strtok(buf, sep);

	while (token) {
		if (0) {
			printf("dot %s(): token `%s'\n", __func__, token);
		}
		if (slwnext) {
			/* expect number for setlinewidth */
			errno = 0;
			n = strtod(token, &ep);

			if (ep) {
				if (strlen(ep)) {
					/* parse error on number */
					ret->pe = 1;
					ret->pe_slw = 1;
					break;
				}
			}

			if (errno) {
				/* parse error on number */
				ret->pe = 1;
				ret->pe_slw = 1;
				break;
			}

			if (n < 0) {
				/* parse error on number */
				ret->pe = 1;
				ret->pe_slw = 1;
				break;
			}

			ret->slwset = 1;
			ret->slw = n;
			slwnext = 0;
		} else {
			if (strcasecmp(token, "dashed") == 0) {
				ret->dashed = 1;
			} else if (strcasecmp(token, "dotted") == 0) {
				ret->dotted = 1;
			} else if (strcasecmp(token, "solid") == 0) {
				ret->solid = 1;
			} else if (strcasecmp(token, "invis") == 0) {
				ret->invis = 1;
			} else if (strcasecmp(token, "invisible") == 0) {
				ret->invis = 1;
			} else if (strcasecmp(token, "bold") == 0) {
				ret->bold = 1;
			} else if (strcasecmp(token, "tapered") == 0) {
				ret->tapered = 1;
			} else if (strcasecmp(token, "filled") == 0) {
				ret->filled = 1;
			} else if (strcasecmp(token, "striped") == 0) {
				ret->striped = 1;
			} else if (strcasecmp(token, "wedged") == 0) {
				ret->wedged = 1;
			} else if (strcasecmp(token, "diagonals") == 0) {
				ret->diagonals = 1;
			} else if (strcasecmp(token, "rounded") == 0) {
				ret->rounded = 1;
			} else if (strcasecmp(token, "radial") == 0) {
				ret->radial = 1;
			} else if (strncmp(token, "setlinewidth", 12) == 0) {
				printf("dot %s(): setlinewidth is depreciated, use penwidth instead\n", __func__);
				/* next token must be the number */
				slwnext = 1;
			} else {
				/* something else */
				ret->unknown = dp_uniqstr(token);
				ret->pe = 1;
				ret->pe_unk = 1;
				break;
			}
		}
		token = strtok(NULL, sep);
	}

	/* check for missing number for setlinewidth as last item */
	if (slwnext) {
		ret->pe_exp = 1;
		ret->pe = 1;
	}

	dp_free(buf);
	buf = NULL;

	return (ret);
}

/* point (x,y) with optional '!' flag */
/* neato: if dim=3 is set point can also be %f,%f,%f for (x,y,z) */
struct dppoint *dp_getpoint(char *s)
{
	struct dppoint *ret = NULL;
	char *str = NULL;
	int f = 0;
	int n = 0;
	float x = 0.0;
	float y = 0.0;

	ret = dp_calloc(1, sizeof(struct dppoint));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		return (ret);
	}

	str = dp_calloc(1, (strlen(s) + 1));

	if (str == NULL) {
		ret->pe = 1;
		return (ret);
	}

	strcpy(str, s);

	/* if last char is '!' set the flag and erase the '!' from the string */
	if (str[strlen(s) - 1] == '!') {
		f = 1;
		str[strlen(s) - 1] = 0;
	} else {
		f = 0;
	}

	/* in neato data and dim=3 it can be x,y,z */

	errno = 0;

	if (strchr(str, ',')) {
		n = sscanf(str, "%f,%f", &x, &y);
	} else {
		n = sscanf(str, "%f %f", &x, &y);
	}

	if (n != 2 || errno != 0) {
		ret->pe = 1;
	} else {
		ret->flag = f;
		ret->x = x;
		ret->y = y;
	}

	dp_free(str);
	str = NULL;

	return (ret);
}

/* get rect %f,%f,%f,%f */
struct dprect *dp_getrect(char *s)
{
	struct dprect *ret = NULL;
	float x0 = 0;
	float y0 = 0;
	float x1 = 0;
	float y1 = 0;
	int n = 0;
	ret = dp_calloc(1, sizeof(struct dprect));
	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	errno = 0;
	/* try ',' or ' ' as sep. char */
	if (strchr(s, ',')) {
		n = sscanf(s, "%f,%f,%f,%f", &x0, &y0, &x1, &y1);
	} else {
		/* assume sep. char is a ' ' space */
		n = sscanf(s, "%f %f %f %f", &x0, &y0, &x1, &y1);
	}

	if (n != 4 || errno != 0) {
		/* some parse error */
		ret->pe = 1;
	} else {
		/* oke */
		ret->x0 = x0;
		ret->y0 = y0;
		ret->x1 = x1;
		ret->y1 = y1;
	}

	return (ret);
}

/* clusterrank value */
int dp_getclrank(char *s)
{
	int ret = 0;
	if (s == NULL) {
		return (0);
	}
	if (strlen(s) == 0) {
		return (0);
	}
	if (strcasecmp(s, "local") == 0) {
		ret = 0;
	} else if (strcasecmp(s, "global") == 0) {
		ret = 1;
	} else if (strcasecmp(s, "none") == 0) {
		ret = 2;
	} else {
		ret = -1;
	}
	return (ret);
}

/* margin %f,%f or %f */
struct dpmargin *dp_getmargin(char *s)
{
	struct dpmargin *ret = NULL;
	float x = 0;
	float y = 0;
	int n = 0;
	ret = dp_calloc(1, sizeof(struct dpmargin));
	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	errno = 0;
	/* try ',' or ' ' as sep. char */
	if (strchr(s, ',')) {
		n = sscanf(s, "%f,%f", &x, &y);
	} else {
		n = sscanf(s, "%f %f", &x, &y);
	}

	if (errno) {
		ret->pe = 1;
	} else {
		if (n == 1) {
			ret->x = x;
			ret->y = x;
		} else if (n == 2) {
			ret->x = x;
			ret->y = y;
		} else {
			ret->pe = 1;
		}
	}

	return (ret);
}

/* outputorder */
struct dpoo *dp_getoo(char *s)
{
	struct dpoo *ret = NULL;
	ret = dp_calloc(1, sizeof(struct dpoo));
	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	if (strcasecmp(s, "breadthfirst") == 0) {
		ret->mode = DP_OO_BF;
	} else if (strcasecmp(s, "nodesfirst") == 0) {
		ret->mode = DP_OO_NF;
	} else if (strcasecmp(s, "edgesfirst") == 0) {
		ret->mode = DP_OO_EF;
	} else {
		ret->pe = 1;
	}
	return (ret);
}

/* rank */
struct dprank *dp_getrank(char *s)
{
	struct dprank *ret = NULL;

	ret = dp_calloc(1, sizeof(struct dprank));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	/* added: rank=none */
	if (strcasecmp(s, "same") == 0) {
		ret->mode = DP_RANK_SAME;
	} else if (strcasecmp(s, "none") == 0) {
		ret->mode = DP_RANK_NONE;
	} else if (strcasecmp(s, "min") == 0) {
		ret->mode = DP_RANK_MIN;
	} else if (strcasecmp(s, "source") == 0) {
		ret->mode = DP_RANK_SRC;
	} else if (strcasecmp(s, "max") == 0) {
		ret->mode = DP_RANK_MAX;
	} else if (strcasecmp(s, "sink") == 0) {
		ret->mode = DP_RANK_SINK;
	} else {
		ret->pe = 1;
	}

	return (ret);
}

/* rankdir */
struct dprankdir *dp_getrankdir(char *s)
{
	struct dprankdir *ret = NULL;

	ret = dp_calloc(1, sizeof(struct dprankdir));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	if (strcasecmp(s, "tb") == 0) {
		ret->mode = DP_RANKDIR_TB;
	} else if (strcasecmp(s, "lr") == 0) {
		ret->mode = DP_RANKDIR_LR;
	} else if (strcasecmp(s, "bt") == 0) {
		ret->mode = DP_RANKDIR_BT;
	} else if (strcasecmp(s, "rl") == 0) {
		ret->mode = DP_RANKDIR_RL;
	} else {
		ret->pe = 1;
	}

	return (ret);
}

/* ranksep */
struct dpranksep *dp_getranksep(char *s)
{
	struct dpranksep *ret = NULL;
	float f = 0;
	int n = 0;

	ret = dp_calloc(1, sizeof(struct dpranksep));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->pe = 1;
		ret->es = 1;
		return (ret);
	}

	errno = 0;

	n = sscanf(s, "%f", &f);

	if (errno) {
		ret->pe = 1;
		return (ret);
	}

	if (n == 1) {
		ret->number = f;
		return (ret);
	}

	errno = 0;

	n = sscanf(s, "%f equally", &f);

	if (errno) {
		ret->pe = 1;
		return (ret);
	}

	if (n == 1) {
		ret->number = f;
		ret->eq = 1;
		return (ret);
	}

	ret->pe = 1;

	return (ret);
}

/* ratio */
struct dpratio *dp_getratio(char *s)
{
	struct dpratio *ret = NULL;
	float f = 0;
	int n = 0;

	ret = dp_calloc(1, sizeof(struct dpratio));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->es = 1;
		ret->pe = 1;
		return (ret);
	}

	if (strcasecmp(s, "fill") == 0) {
		ret->mode = DP_RATIO_FILL;
	} else if (strcasecmp(s, "compress") == 0) {
		ret->mode = DP_RATIO_COM;
	} else if (strcasecmp(s, "expand") == 0) {
		ret->mode = DP_RATIO_EXP;
	} else if (strcasecmp(s, "auto") == 0) {
		ret->mode = DP_RATIO_AUTO;
	} else {
		ret->mode = 0;
	}

	if (ret->mode) {
		return (ret);
	}

	errno = 0;

	n = sscanf(s, "%f", &f);

	if (errno) {
		ret->pe = 1;
		return (ret);
	}

	if (n == 1) {
		ret->number = f;
	} else {
		ret->pe = 1;
	}

	return (ret);
}

/* splines */
struct dpsplines *dp_getsplines(char *s)
{
	struct dpsplines *ret = NULL;

	ret = dp_calloc(1, sizeof(struct dpsplines));

	if (ret == NULL) {
		return (ret);
	}

	if (s == NULL) {
		ret->pe = 1;
		return (ret);
	}

	if (strlen(s) == 0) {
		ret->mode = DP_SPLINE_NONE;
		return (ret);
	}

	if (strcasecmp(s, "none") == 0) {
		ret->mode = DP_SPLINE_NONE;
	} else if (strcasecmp(s, "line") == 0) {
		ret->mode = DP_SPLINE_LINE;
	} else if (strcasecmp(s, "false") == 0) {
		ret->mode = DP_SPLINE_LINE;
	} else if (strcasecmp(s, "polyline") == 0) {
		ret->mode = DP_SPLINE_POLY;
	} else if (strcasecmp(s, "curved") == 0) {
		ret->mode = DP_SPLINE_CURVED;
	} else if (strcasecmp(s, "ortho") == 0) {
		ret->mode = DP_SPLINE_ORTHO;
	} else if (strcasecmp(s, "spline") == 0) {
		ret->mode = DP_SPLINE_SPLINE;
	} else if (strcasecmp(s, "true") == 0) {
		ret->mode = DP_SPLINE_SPLINE;
	} else {
		ret->pe = 1;
	}

	return (ret);
}

/* end */
