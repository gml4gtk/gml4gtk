
/*
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

/* dphl.* is about Dot Parsing Html Labels */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <math.h>
#include <errno.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dphl.h"
#include "dpmisc.h"
#include "dphlparser.h"
#include "dot.tab.h"
#include "dpus.h"
#include "dpmem.h"

/* max unsigned long value from html "&#nnn;" or "&#xnn;" */
#define UNICODE_MAX 0x10FFFFul

/* resulting parts of html label */
static struct hlpart *hlinf = NULL;

/* data for <table> */
static struct tabledata *curtable = NULL;

/* data for <table> */
static splay_tree tablestack = NULL;

/* data for <td> */
static struct tddata *curtd = NULL;

/* data for <td> */
static splay_tree tdstack = NULL;

/* data for <tr> */
static struct trdata *curtr = NULL;

/* data for <tr> */
static splay_tree trstack = NULL;

/* data for <font> */
static struct fontdata *curfont = NULL;

/* data for <font> */
static struct fontldata *fontlist = NULL;
static struct fontldata *fontlistend = NULL;

/* data for <font> */
static splay_tree fontstack = NULL;

/* data for <br> */
static struct brdata *curbr = NULL;

/* data for <img> */
static struct imgdata *curimg = NULL;

/* data */
static char *curdata = NULL;

/* <s> strike-through */
static int curs = 0;

/* <sup> superscript text */
static int cursup = 0;

/* <sub> subscript text */
static int cursub = 0;

/* <o> overline text */
static int curo = 0;

/* <u> underline text */
static int curu = 0;

/* <b> bold text */
static int curb = 0;

/* <i> italic text */
static int curi = 0;

/* at error clear parsed info data */
static void dphl_clearhlinfo(void);

/* parse html label of one node, return 0 if oke */
int htmlparse(struct dpnode *node)
{
	int lexonly = 0;
	int i = 0;
	int token = 0;
	char *p = NULL;
	int c = 0;
	int status = 0;

	/* no parser errors */
	memset(dp_errmsg, 0, 256);

	/* check for <> to be sure for a good string */
	/* use of <> in a <!-- comment --> can cause errors */
	p = node->label;
	while (*p) {
		if (*p == '<') {
			c++;
		} else if (*p == '>') {
			c--;
		} else {
			/* nop */
		}
		p++;
	}

	/* check for mis-match <> */
	if (c != 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): non-matching '<' and '>' in html string\n", __func__);
		return (1);
	}

	/* test mode to only lex () */
	if (lexonly) {
		html_lex_init(1 /* debug */ , node->label, node->yylineno);
		printf("html %s(): lexing string \"%s\"\n", __func__, node->label);
		for (i = 0; i < 100; i++) {
			token = html_lex();
			printf("%s(%d): token %d [%s]\n", __func__, i, token, hlylval.string);
			if (token == 0 || token == EOF) {
				break;
			}
		}

		html_lex_deinit();

		printf("error message is: \"%s\"\n", dp_errmsg);

		return (0);
	}

	/*
	 * run the parser on the html string
	 */

	/* where to build the data structures */
	hlinf = dp_calloc(1, sizeof(struct hlpart));

	if (hlinf == NULL) {
		/* shouldnothappen */
		return (1);
	}

	/* unknown mode yet */
	hlinf->mode = 0;	/* or (-1); */

	html_lex_init(yydebug /* debug */ , node->label, node->yylineno);

	status = hlyparse();

	/* check for error message */
	if (dphl_chk_err()) {
		status++;
	}

	html_lex_deinit();

	if (yydebug || 0) {
		printf("html %s(): %d status from html parser '%s'\n", __func__, status, dp_errmsg);
	}

	if (status) {
		/* at error clear all data */
		dphl_clearhlinfo();
	} else {
		/* parsed oke and convert parsed data */
		/* todo verify() then at error clear all data */
		/* set the resulted parsed data as structures */
		node->hlinfo = hlinf;
		if (yydebug || 0) {
			printf("%s(): node %d \"%s\" \"%s\" mode=%d il=%p tl=%p\n", __func__, node->nr, node->name, node->label,
			       hlinf->mode, (void *)hlinf->il, (void *)hlinf->tl);
		}
		if (hlinf->mode == 0) {
			/* item mode should not have tables data */
			if (hlinf->tl) {
				printf("%s(): node \"%s\" \"%s\" mode=%d il=%p tl=%p shouldnothappen tl\n", __func__, node->name,
				       node->label, hlinf->mode, (void *)hlinf->il, (void *)hlinf->tl);
			}
		} else if (hlinf->mode == 1) {
			/* table mode should not have item data */
			if (hlinf->il) {
				printf("%s(): node \"%s\" \"%s\" mode=%d il=%p tl=%p shouldnothappen il\n", __func__, node->name,
				       node->label, hlinf->mode, (void *)hlinf->il, (void *)hlinf->tl);
			}
		} else {
			/* hlinf->mode == -1 does happen todo */
			printf("%s(): node \"%s\" \"%s\" mode=%d il=%p tl=%p shouldnothappen wrong mode\n", __func__, node->name,
			       node->label, hlinf->mode, (void *)hlinf->il, (void *)hlinf->tl);
		}
	}

	return (status);
}

/* at error clear parsed info data */
static void dphl_clearhlinfo(void)
{
	struct ilist *pil = NULL;
	struct ilist *pilnext = NULL;

	if (hlinf == NULL) {	/* no data */
		return;
	}

	/* item data to free */
	if (hlinf->il) {
		pil = hlinf->il;
		while (pil) {
			pilnext = pil->next;
			if (pil->items) {
				dp_free(pil->items);
				pil->items = NULL;
			}
			dp_free(pil);
			pil = pilnext;
		}
		hlinf->il = NULL;
		hlinf->ilend = NULL;
	}

	/* table data to free */
	if (hlinf->tl) {
		/* todo */
		hlinf->tl = NULL;
		hlinf->tlend = NULL;
	}

	/* final free */
	dp_free(hlinf);
	hlinf = NULL;

	return;
}

/* add data to items */
static struct item *dphl_makeitem(char *str, char *alt, int opt, struct tabledata *newtable)
{
	struct item *item = NULL;
	char *msg = NULL;

	item = dp_calloc(1, sizeof(struct item));

	msg = str;

	/* preset item */
	item->text = str;	/* text to display */
	item->atext = alt;	/* modified text to display */
	item->fontname = NULL;	/* optional font */
	item->fontsize = (-1);	/* optional pointsize */
	item->fontcolor = (-1);	/* optional color of text */
	item->ncolor = (-1);	/* optional background color from <td> or <table> */
	item->table = NULL;	/* optional <table> in <td> */
	/* the bitflags are all 0 */

	/* check if a <br> */
	if (opt == 1) {
		item->bitflags.br = 1;
	}

	/* check if a <hr> */
	if (opt == 2) {
		item->bitflags.hr = 1;
	}

	/* check if a <vr> */
	if (opt == 3) {
		item->bitflags.vr = 1;
	}

	/* check if a <table> */
	if (opt == 5) {
		item->bitflags.table = 1;
		/* this is the <table> in the <td> */
		item->table = newtable;
		msg = "<table> in <td>";
	}

	/* check if str has html chars */
	if (alt) {
		item->bitflags.at = 1;
	}

	/* set italic bitflags etc. */
	if (curb) {
		/* <b> italic */
		item->bitflags.b = 1;
	}
	if (curi) {
		/* <i> italic */
		item->bitflags.i = 1;
	}
	if (curo) {
		/* <o> overline */
		item->bitflags.o = 1;
	}
	if (curu) {
		/* <u> underline */
		item->bitflags.u = 1;
	}
	if (curs) {
		/* <s> strike-through */
		item->bitflags.s = 1;
	}
	if (cursub) {
		/* <sub> subscript */
		item->bitflags.sub = 1;
	}
	if (cursup) {
		/* <sup> superscript */
		item->bitflags.sup = 1;
	}
	if (curimg) {
		/* <img> image */
		item->bitflags.img = 1;
	}

	/* add extra optional data in table mode */
	if (hlinf->mode) {
		/* <table> settings */
		if (curtable) {
			if (curtable->color < 0) {
				/* not specified */
			} else {
				item->fontcolor = curtable->color;
			}
			if (curtable->bgcolor < 0) {
				/* not specified */
			} else {
				item->ncolor = curtable->bgcolor;
			}
		}
		/* <td> settings override curtable settings */
		if (curtd) {
			if (curtd->color < 0) {
				/* not specified */
			} else {
				item->fontcolor = curtd->color;
			}
			if (curtd->bgcolor < 0) {
				/* not specified */
			} else {
				if (yydebug || 1) {
					printf("%s(): setting background color 0x%x for \"%s\"\n", __func__, curtd->bgcolor, msg);
				}
				item->ncolor = curtd->bgcolor;
			}
		}
	}
	/* if there is a optional font */
	if (curfont) {
		/* fontname */
		if (curfont->face == NULL) {
			/* not specified */
		} else {
			item->fontname = curfont->face;
		}
		/* fontsize */
		if (curfont->pointsize < 0) {
			/* not specified */
		} else {
			item->fontsize = curfont->pointsize;
		}
		/* fontcolor */
		if (curfont->color < 0) {
			/* not specified */
		} else {
			item->fontcolor = curfont->color;
		}
	}

	return (item);
}

/* add data to items */
static void dphl_itemitems(char *str, char *alt, int opt)
{
	struct ilist *il = NULL;

	/* if opt is set it is br=1 */
	if (hlinf == NULL) {
		/* shouldnohappen */
		return;
	}

	il = dp_calloc(1, sizeof(struct ilist));

	/* set linkage to data */
	il->items = dphl_makeitem(str, alt, opt, NULL);

	if (il->items == NULL) {
		/* shouldnothappen */
		return;
	}

	/* link the new data field */
	if (hlinf->il == NULL) {
		hlinf->il = il;
		hlinf->ilend = il;
	} else {
		hlinf->ilend->next = il;
		hlinf->ilend = il;
	}

	return;
}

/* add data to tables */
static void dphl_itemtables(char *str, char *alt, int opt)
{
	struct ilist *il = NULL;

	/* if opt is set it is br=1, hr=2, vr=3, img=4 */
	if (hlinf == NULL) {
		/* shouldnothappen */
		return;
	}

	if (hlinf->mode == 0) {
		/* shouldnothappen */
		return;
	}

	if (curtable == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtable\n", __func__);
		return;
	}

	if (curtd == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtd\n", __func__);
		return;
	}

	il = dp_calloc(1, sizeof(struct ilist));

	/* set linkage to data */
	il->items = dphl_makeitem(str, alt, opt, NULL);

	curtd->table = curtable;

	if (curtd->il == NULL) {
		curtd->il = il;
		curtd->ilend = il;
	} else {
		curtd->ilend->next = il;
		curtd->ilend = il;
	}

	return;
}

/* put char in buffer */
static int dplh_putc_utf8(unsigned long cp, char *buffer)
{
	unsigned char *bytes = (unsigned char *)buffer;

	if (cp <= 0x007Ful) {
		bytes[0] = (unsigned char)cp;
		return (1);
	}

	if (cp <= 0x07FFul) {
		bytes[1] = (unsigned char)((2 << 6) | (cp & 0x3F));
		bytes[0] = (unsigned char)((6 << 5) | (cp >> 6));
		return (2);
	}

	if (cp <= 0xFFFFul) {
		bytes[2] = (unsigned char)((2 << 6) | (cp & 0x3F));
		bytes[1] = (unsigned char)((2 << 6) | ((cp >> 6) & 0x3F));
		bytes[0] = (unsigned char)((14 << 4) | (cp >> 12));
		return (3);
	}

	if (cp <= 0x10FFFFul) {
		bytes[3] = (unsigned char)((2 << 6) | (cp & 0x3F));
		bytes[2] = (unsigned char)((2 << 6) | ((cp >> 6) & 0x3F));
		bytes[1] = (unsigned char)((2 << 6) | ((cp >> 12) & 0x3F));
		bytes[0] = (unsigned char)((30 << 3) | (cp >> 18));
		return (4);
	}

	return (0);
}

/* html chars */
static struct mi {
	char *key;
	char *data;
} entdata[] = {
	{ "&AElig;", "Æ" },
	{ "&Aacute;", "Á" },
	{ "&Acirc;", "Â" },
	{ "&Agrave;", "À" },
	{ "&Alpha;", "Α" },
	{ "&Aring;", "Å" },
	{ "&Atilde;", "Ã" },
	{ "&Auml;", "Ä" },
	{ "&Beta;", "Β" },
	{ "&Ccedil;", "Ç" },
	{ "&Chi;", "Χ" },
	{ "&Dagger;", "‡" },
	{ "&Delta;", "Δ" },
	{ "&ETH;", "Ð" },
	{ "&Eacute;", "É" },
	{ "&Ecirc;", "Ê" },
	{ "&Egrave;", "È" },
	{ "&Epsilon;", "Ε" },
	{ "&Eta;", "Η" },
	{ "&Euml;", "Ë" },
	{ "&Gamma;", "Γ" },
	{ "&Iacute;", "Í" },
	{ "&Icirc;", "Î" },
	{ "&Igrave;", "Ì" },
	{ "&Iota;", "Ι" },
	{ "&Iuml;", "Ï" },
	{ "&Kappa;", "Κ" },
	{ "&Lambda;", "Λ" },
	{ "&Mu;", "Μ" },
	{ "&Ntilde;", "Ñ" },
	{ "&Nu;", "Ν" },
	{ "&OElig;", "Œ" },
	{ "&Oacute;", "Ó" },
	{ "&Ocirc;", "Ô" },
	{ "&Ograve;", "Ò" },
	{ "&Omega;", "Ω" },
	{ "&Omicron;", "Ο" },
	{ "&Oslash;", "Ø" },
	{ "&Otilde;", "Õ" },
	{ "&Ouml;", "Ö" },
	{ "&Phi;", "Φ" },
	{ "&Pi;", "Π" },
	{ "&Prime;", "″" },
	{ "&Psi;", "Ψ" },
	{ "&Rho;", "Ρ" },
	{ "&Scaron;", "Š" },
	{ "&Sigma;", "Σ" },
	{ "&THORN;", "Þ" },
	{ "&Tau;", "Τ" },
	{ "&Theta;", "Θ" },
	{ "&Uacute;", "Ú" },
	{ "&Ucirc;", "Û" },
	{ "&Ugrave;", "Ù" },
	{ "&Upsilon;", "Υ" },
	{ "&Uuml;", "Ü" },
	{ "&Xi;", "Ξ" },
	{ "&Yacute;", "Ý" },
	{ "&Yuml;", "Ÿ" },
	{ "&Zeta;", "Ζ" },
	{ "&aacute;", "á" },
	{ "&acirc;", "â" },
	{ "&acute;", "´" },
	{ "&aelig;", "æ" },
	{ "&agrave;", "à" },
	{ "&alefsym;", "ℵ" },
	{ "&alpha;", "α" },
	{ "&amp;", "&" },
	{ "&and;", "∧" },
	{ "&ang;", "∠" },
	{ "&apos;", "'" },
	{ "&aring;", "å" },
	{ "&asymp;", "≈" },
	{ "&atilde;", "ã" },
	{ "&auml;", "ä" },
	{ "&bdquo;", "„" },
	{ "&beta;", "β" },
	{ "&brvbar;", "¦" },
	{ "&bull;", "•" },
	{ "&cap;", "∩" },
	{ "&ccedil;", "ç" },
	{ "&cedil;", "¸" },
	{ "&cent;", "¢" },
	{ "&chi;", "χ" },
	{ "&circ;", "ˆ" },
	{ "&clubs;", "♣" },
	{ "&cong;", "≅" },
	{ "&copy;", "©" },
	{ "&crarr;", "↵" },
	{ "&cup;", "∪" },
	{ "&curren;", "¤" },
	{ "&dArr;", "⇓" },
	{ "&dagger;", "†" },
	{ "&darr;", "↓" },
	{ "&deg;", "°" },
	{ "&delta;", "δ" },
	{ "&diams;", "♦" },
	{ "&divide;", "÷" },
	{ "&eacute;", "é" },
	{ "&ecirc;", "ê" },
	{ "&egrave;", "è" },
	{ "&empty;", "∅" },
	{ "&emsp;", "\xE2\x80\x83" },
	{ "&ensp;", "\xE2\x80\x82" },
	{ "&epsilon;", "ε" },
	{ "&equiv;", "≡" },
	{ "&eta;", "η" },
	{ "&eth;", "ð" },
	{ "&euml;", "ë" },
	{ "&euro;", "€" },
	{ "&exist;", "∃" },
	{ "&fnof;", "ƒ" },
	{ "&forall;", "∀" },
	{ "&frac12;", "½" },
	{ "&frac14;", "¼" },
	{ "&frac34;", "¾" },
	{ "&frasl;", "⁄" },
	{ "&gamma;", "γ" },
	{ "&ge;", "≥" },
	{ "&gt;", ">" },
	{ "&hArr;", "⇔" },
	{ "&harr;", "↔" },
	{ "&hearts;", "♥" },
	{ "&hellip;", "…" },
	{ "&iacute;", "í" },
	{ "&icirc;", "î" },
	{ "&iexcl;", "¡" },
	{ "&igrave;", "ì" },
	{ "&image;", "ℑ" },
	{ "&infin;", "∞" },
	{ "&int;", "∫" },
	{ "&iota;", "ι" },
	{ "&iquest;", "¿" },
	{ "&isin;", "∈" },
	{ "&iuml;", "ï" },
	{ "&kappa;", "κ" },
	{ "&lArr;", "⇐" },
	{ "&lambda;", "λ" },
	{ "&lang;", "〈" },
	{ "&laquo;", "«" },
	{ "&larr;", "←" },
	{ "&lceil;", "⌈" },
	{ "&ldquo;", "“" },
	{ "&le;", "≤" },
	{ "&lfloor;", "⌊" },
	{ "&lowast;", "∗" },
	{ "&loz;", "◊" },
	{ "&lrm;", "\xE2\x80\x8E" },
	{ "&lsaquo;", "‹" },
	{ "&lsquo;", "‘" },
	{ "&lt;", "<" },
	{ "&macr;", "¯" },
	{ "&mdash;", "—" },
	{ "&micro;", "µ" },
	{ "&middot;", "·" },
	{ "&minus;", "−" },
	{ "&mu;", "μ" },
	{ "&nabla;", "∇" },
	{ "&nbsp;", "\xC2\xA0" },
	{ "&ndash;", "–" },
	{ "&ne;", "≠" },
	{ "&ni;", "∋" },
	{ "&not;", "¬" },
	{ "&notin;", "∉" },
	{ "&nsub;", "⊄" },
	{ "&ntilde;", "ñ" },
	{ "&nu;", "ν" },
	{ "&oacute;", "ó" },
	{ "&ocirc;", "ô" },
	{ "&oelig;", "œ" },
	{ "&ograve;", "ò" },
	{ "&oline;", "‾" },
	{ "&omega;", "ω" },
	{ "&omicron;", "ο" },
	{ "&oplus;", "⊕" },
	{ "&or;", "∨" },
	{ "&ordf;", "ª" },
	{ "&ordm;", "º" },
	{ "&oslash;", "ø" },
	{ "&otilde;", "õ" },
	{ "&otimes;", "⊗" },
	{ "&ouml;", "ö" },
	{ "&para;", "¶" },
	{ "&part;", "∂" },
	{ "&permil;", "‰" },
	{ "&perp;", "⊥" },
	{ "&phi;", "φ" },
	{ "&pi;", "π" },
	{ "&piv;", "ϖ" },
	{ "&plusmn;", "±" },
	{ "&pound;", "£" },
	{ "&prime;", "′" },
	{ "&prod;", "∏" },
	{ "&prop;", "∝" },
	{ "&psi;", "ψ" },
	{ "&quot;", "\"" },
	{ "&rArr;", "⇒" },
	{ "&radic;", "√" },
	{ "&rang;", "〉" },
	{ "&raquo;", "»" },
	{ "&rarr;", "→" },
	{ "&rceil;", "⌉" },
	{ "&rdquo;", "”" },
	{ "&real;", "ℜ" },
	{ "&reg;", "®" },
	{ "&rfloor;", "⌋" },
	{ "&rho;", "ρ" },
	{ "&rlm;", "\xE2\x80\x8F" },
	{ "&rsaquo;", "›" },
	{ "&rsquo;", "’" },
	{ "&sbquo;", "‚" },
	{ "&scaron;", "š" },
	{ "&sdot;", "⋅" },
	{ "&sect;", "§" },
	{ "&shy;", "\xC2\xAD" },
	{ "&sigma;", "σ" },
	{ "&sigmaf;", "ς" },
	{ "&sim;", "∼" },
	{ "&spades;", "♠" },
	{ "&sub;", "⊂" },
	{ "&sube;", "⊆" },
	{ "&sum;", "∑" },
	{ "&sup1;", "¹" },
	{ "&sup2;", "²" },
	{ "&sup3;", "³" },
	{ "&sup;", "⊃" },
	{ "&supe;", "⊇" },
	{ "&szlig;", "ß" },
	{ "&tau;", "τ" },
	{ "&there4;", "∴" },
	{ "&theta;", "θ" },
	{ "&thetasym;", "ϑ" },
	{ "&thinsp;", "\xE2\x80\x89" },
	{ "&thorn;", "þ" },
	{ "&tilde;", "˜" },
	{ "&times;", "×" },
	{ "&trade;", "™" },
	{ "&uArr;", "⇑" },
	{ "&uacute;", "ú" },
	{ "&uarr;", "↑" },
	{ "&ucirc;", "û" },
	{ "&ugrave;", "ù" },
	{ "&uml;", "¨" },
	{ "&upsih;", "ϒ" },
	{ "&upsilon;", "υ" },
	{ "&uuml;", "ü" },
	{ "&weierp;", "℘" },
	{ "&xi;", "ξ" },
	{ "&yacute;", "ý" },
	{ "&yen;", "¥" },
	{ "&yuml;", "ÿ" },
	{ "&zeta;", "ζ" },
	{ "&zwj;", "\xE2\x80\x8D" },
	{ "&zwnj;", "\xE2\x80\x8C" }
};

/* search compare */
static int entcmp(const void *key, const void *value)
{
	struct mi *mi1 = (struct mi *)key;
	struct mi *mi2 = (struct mi *)value;
	return (strcasecmp(mi1->key, mi2->key));
}

/* translate html chars like "&amp;" into "&" */
static char *dplh_htrans(char *str)
{
	struct mi thekey = { NULL, NULL };
	char *ret = NULL;
	int blen = 0;		/* buffer length */
	char *buf = NULL;	/* output buffer */
	char *ebuf = NULL;	/* entity buffer */
	char *p = NULL;
	char *q = NULL;
	char *tmpp = NULL;
	char *tmpq = NULL;
	int nc = 0;
	unsigned long cp = 0;
	char *tail = NULL;
	struct mi *entity = NULL;
	int elen = 0;

	/* check str */
	if (str == NULL) {
		return (NULL);
	}
	if (strlen(str) == 0) {
		return (NULL);
	}
	if (strchr(str, '&') == NULL) {
		return (NULL);
	}
	if (strchr(str, ';') == NULL) {
		/* parse error */
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): missing ';' in `%s' for html char in html string at line %d\n", __func__, str, hllineno);
		return (NULL);
	}
	/* if only "&;" */
	if (strlen(str) < 3) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too short `%s' for html char in html string at line %d\n", __func__, str, hllineno);
		return (NULL);
	}
	/* create buffers for modified string */
	blen = strlen(str) + 1;
	buf = dp_calloc(1, blen);
	if (buf == NULL) {
		/* shouldnothappen */
		return (NULL);
	}
	ebuf = dp_calloc(1, blen);
	if (ebuf == NULL) {
		/* shouldnothappen */
		dp_free(buf);
		return (NULL);
	}
	/* scan str and replace or copy chars */
	p = str;
	q = buf;
	while (*p) {
		/* check for start of a html char */
		if (*p == '&') {
			/* copy to entity buf */
			memset(ebuf, 0, blen);
			tmpp = p;
			tmpq = ebuf;
			while (*tmpp) {
				/* check for end of entity */
				if (*tmpp == ';') {
					/* put the final ';' in ebuf */
					*tmpq = *tmpp;
					break;
				} else {
					/* copy chars */
					*tmpq = *tmpp;
					tmpp++;
					tmpq++;
				}
			}
			/* check end of str */
			if (*tmpp == 0) {
				/* parse error */
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "html %s(): missing ';' in `%s' for html char in html string at line %d\n", __func__,
					 ebuf, hllineno);
				/* stop parsing string */
				break;
			}
			/* check for &; */
			if (strlen(ebuf) < 3) {
				/* parse error */
				memset(dp_errmsg, 0, 256);
				snprintf(dp_errmsg, (256 - 1),
					 "html %s(): empty entity `%s' for html char in html string at line %d\n", __func__,
					 ebuf, hllineno);
				/* stop parsing string */
				break;
			}
			/* check if has dec or hex value */
			if (strchr(ebuf, '#')) {
				errno = 0;
				tail = NULL;
				/* dec or hex entity with 'x' or 'X' */
				if (strchr(ebuf, 'x') || strchr(ebuf, 'X')) {
					/* hex entity as "&#x80;" */
					cp = strtoul((char *)(ebuf + 3), (char **)(&tail), 16);
				} else {
					/* decimal entity as "&#160;" */
					cp = strtoul((char *)(ebuf + 2), (char **)(&tail), 10);
				}
				/* check for errors */
				if (errno || (*tail != ';') || (cp > UNICODE_MAX)) {
					/* parse error */
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "html %s(): bad value `%s' for html char in html string at line %d\n", __func__,
						 ebuf, hllineno);
					/* stop parsing string */
					break;
				} else {
					/* cp is always a positive number, unsigned but it can be 0 */
					if (cp == 0) {
						printf
						    ("html %s(): zero value `%s' for html char terminates early html string at line %d\n",
						     __func__, ebuf, hllineno);
						/* stop parsing string */
						break;
					}
					/* oke */
					nc = dplh_putc_utf8(cp, q);
					/* a duff device to update q */
					/* this fall-thru is intentional but gcc may warn */
					/* also gcc does detect these specific comments below to suppress a warning */
					switch (nc) {
					case 4:
						q++;
						/* FALLTHRU */
					case 3:
						q++;
						/* FALLTHRU */
					case 2:
						q++;
						/* FALLTHRU */
					case 1:
						q++;
						/* FALLTHRU */
					default:
						break;
					}
				}
			} else {
				/* textual entity as "&amp;" is in ebuf */
				thekey.key = ebuf;
				entity =
				    bsearch(&thekey, entdata, (sizeof(entdata) / sizeof(entdata[0])), sizeof(struct mi), entcmp);
				if (entity == NULL) {
					/* parse error */
					memset(dp_errmsg, 0, 256);
					snprintf(dp_errmsg, (256 - 1),
						 "html %s(): bad value `%s' for html char in html string at line %d\n", __func__,
						 ebuf, hllineno);
					/* stop parsing string */
				} else {
					elen = strlen(entity->data);
					/* there is enough room in buf because replacements are shorter */
					memcpy(q, entity->data, elen);
					q = q + elen;
				}
			}
			/* now skip p past the entity */
			while (*p) {
				if (*p == ';') {
					p++;
					break;
				}
				p++;
			}
		} else {
			/* regular char to copy */
			*q = *p;
			p++;
			q++;
		}
	}
	/* check for error */
	if (dphl_chk_err()) {
		ret = NULL;
	} else {
		ret = dp_uniqstr(buf);
	}
	dp_free(buf);
	buf = NULL;
	dp_free(ebuf);
	ebuf = NULL;
	return (ret);
}

/* unknown attribute */
void dphl_attr_huh(char *tag, char *attr, char *value)
{
	printf("html %s(): at tag %s unknown attribute %s=\"%s\" skipped in html string at line %d\n", __func__, tag, attr, value,
	       hllineno);
	fflush(stdout);
	return;
}

/* check for error message */
int dphl_chk_err(void)
{
	int ret = 0;
	if (strlen(dp_errmsg)) {
		/* there is a error message, fflush std */
		fflush(stdout);
		fflush(stderr);
		ret = 1;
	} else {
		ret = 0;
	}
	return (ret);
}

/* return 1 if string is only spaces */
static int dphl_isws(char *str)
{
	int ret = 1;
	char *p = NULL;

	p = str;

	while (*p) {
		/* keep scanning when spaces */
		if (*p == ' ') {
		} else if (*p == '\n') {
		} else if (*p == '\t') {
		} else if (*p == '\r') {
		} else if (*p == '\f') {
		} else {
			ret = 0;
			break;
		}
		p++;
	}

	return (ret);
}

/* check data before/after <table></table> */
void dphl_tabledata(char *str)
{

	/* check if spaces */
	if (dphl_isws(str) == 0) {
		printf("html %s(): skipped `%s' around <table></table> tag in html string at line %d\n", __func__, str, hllineno);
	}

	return;
}

/* check align="value"
 * for <br> "center|left|right"
 * for <table> "center|left|right"
 * for <td> "center|left|right|text"
 */
int dphl_chk_align(char *str, int mode)
{
	int status = 0;
	int val = 0;
	int err = 0;

	if (strcasecmp(str, "center") == 0) {
		val = DP_ALIGNC;
	} else if (strcasecmp(str, "left") == 0) {
		val = DP_ALIGNL;
	} else if (strcasecmp(str, "right") == 0) {
		val = DP_ALIGNR;
	} else {
		/* only <td> */
		if (mode == T_TD) {
			if (strcasecmp(str, "text") == 0) {
				val = DP_ALIGNT;
			} else {
				status = 1;
			}
		} else {
			status = 1;
		}
	}

	/* check error status */
	if (status) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): unknown value `%s' for align in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	/* value is oke for align */

	if (mode == T_TD) {
		/* <td> align */
		if (curtd->align == -1) {
			curtd->align = val;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> align */
		if (curtable->align == -1) {
			curtable->align = val;
		} else {
			err = 1;
		}
	} else if (mode == T_BR) {
		/* <br> align */
		if (curbr->align == -1) {
			curbr->align = val;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}

	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for align in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	return (0);
}

/*
 * for <td> "center|left|right"
 */
int dphl_chk_balign(char *str)
{
	int status = 0;
	int val = 0;

	if (strcasecmp(str, "center") == 0) {
		val = DP_ALIGNC;
	} else if (strcasecmp(str, "left") == 0) {
		val = DP_ALIGNL;
	} else if (strcasecmp(str, "right") == 0) {
		val = DP_ALIGNR;
	} else {
		status = 1;
	}

	/* check error status */
	if (status) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): unknown value `%s' for balign in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	/* value is oke for <td> balign */
	if (curtd->balign == -1) {
		curtd->balign = val;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for balign in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	return (0);
}

/* check bgcolor value */
int dphl_chk_bgcolor(char *str, int mode)
{
	struct dpcolor *c = NULL;
	int pe = 0;
	int es = 0;
	int il = 0;
	int rgb = 0;
	int err = 0;

	/* get color without colorscheme number */
	c = dp_getcolor(0, 0, str);
	pe = c->pe;
	es = c->es;
	il = c->islist;
	rgb = c->color;
	dp_free(c);
	c = NULL;

	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for bgAcolor in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for bgcolor in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (il) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): color-list value `%s' for bgcolor in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (mode == T_TD) {
		/* <td> bgcolor */
		if (curtd->bgcolor == -1) {
			curtd->bgcolor = rgb;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> bgcolor */
		if (curtable->bgcolor == -1) {
			curtable->bgcolor = rgb;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for bgcolor in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check border value */
int dphl_chk_border(char *str, int mode)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for border in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for border in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for border in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for border in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (ival > 255) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): too high value `%s' for border (max is 255) in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed */
	if (mode == T_TD) {
		/* <td> border */
		if (curtd->border == -1) {
			curtd->border = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> border */
		if (curtable->border == -1) {
			curtable->border = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for border in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check cellborder value in <table> */
int dphl_chk_cellborder(char *str)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellborder in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for cellborder in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for cellborder in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellborder in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	if (ival > 255) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for cellborder (max is 255) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed */
	/* <table> cellborder */
	if (curtable->cellborder == -1) {
		curtable->cellborder = ival;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for cellborder in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	return (0);
}

/* check cellpadding value, default is 2 px */
int dphl_chk_cellpadding(char *str, int mode)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellpadding in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for cellpadding in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for cellpadding in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellpadding in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	if (ival > 255) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for cellpadding (max is 255) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed */
	if (mode == T_TD) {
		/* <td> cellpadding */
		if (curtd->cellpadding == -1) {
			curtd->cellpadding = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> cellpadding */
		if (curtable->cellpadding == -1) {
			curtable->cellpadding = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for cellpadding in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	return (0);
}

/* check cellspacing value default is 2 px */
/* cellspacing="0.5" is used in dot data, parse fp number */
int dphl_chk_cellspacing(char *str, int mode)
{
	int ival = 0;
	double dval = 0.0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpnum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellspacing in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	num = dp_getnum(str);
	dval = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for cellspacing in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for cellspacing in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (dval < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for cellspacing in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	if (dval > INT_MAX) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): too high value `%s' for cellspacing in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	dval = round(dval);
	ival = (int)dval;
	if (ival > 127) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for cellspacing (max is 127) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the spacing */
	/* size 0 is allowed */
	if (mode == T_TD) {
		/* <td> cellspacing */
		if (curtd->cellspacing == -1) {
			curtd->cellspacing = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> cellspacing */
		if (curtable->cellspacing == -1) {
			curtable->cellspacing = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for cellspacing in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	return (0);
}

/* check color value */
int dphl_chk_color(char *str, int mode)
{
	struct dpcolor *c = NULL;
	int pe = 0;
	int es = 0;
	int il = 0;
	int rgb = 0;
	int err = 0;
	/* get color without colorscheme number */
	c = dp_getcolor(0, 0, str);
	pe = c->pe;
	es = c->es;
	il = c->islist;
	rgb = c->color;
	dp_free(c);
	c = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for color in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for color in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (il) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): color-list value `%s' for color in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (mode == T_TD) {
		/* <td> color */
		if (curtd->color == -1) {
			curtd->color = rgb;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> color */
		if (curtable->color == -1) {
			curtable->color = rgb;
		} else {
			err = 1;
		}
	} else if (mode == T_FONT) {
		/* <font> color */
		if (curfont->color == -1) {
			curfont->color = rgb;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}

	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for color in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	return (0);
}

/* check columns value in <table> */
int dphl_chk_columns(char *str)
{
	/* only '*' is allowed */
	if (strlen(str) != 1) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for columns in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (*str != '*') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for columns in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	/* <table> columns */
	if (curtable->columns == NULL) {
		curtable->columns = str;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for columns in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check colspan value in <td> */
int dphl_chk_colspan(char *str)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for colspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for colspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for colspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for colspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (ival == 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): zero value `%s' for colspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (ival > 65535) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for colspan (max is 65535) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is not allowed */
	/* <td> colspan */
	if (curtd->colspan == -1) {
		curtd->colspan = ival;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for colspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	/* todo */
	if (curtd->colspan > 1) {
		printf("%s(): colspan=%d is not yet implemented in this version\n", __func__, curtd->colspan);
	}

	return (0);
}

/* check face value for font - the fontname */
int dphl_chk_face(char *str)
{
	if (strlen(str) == 0) {
		/* "" is same as not specified */
		return (0);
	}

	/* <font> face */
	if (curfont->face == NULL) {
		curfont->face = str;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for font face in html string\n", __func__, str);
		return (1);
	}

	return (0);
}

/* check fixedsize value */
int dphl_chk_fixedsize(char *str, int mode)
{
	int val = 0;
	int err = 0;

	if (strlen(str) == 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for fixedsize in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (strcasecmp(str, "true") == 0) {
		val = DP_TRUE;
	} else if (strcasecmp(str, "false") == 0) {
		val = DP_FALSE;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): bad value `%s' for fixedsize instead of true/false in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (mode == T_TD) {
		/* <td> fixedsize */
		if (curtd->fixedsize == -1) {
			curtd->fixedsize = val;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> fixedsize */
		if (curtable->fixedsize == -1) {
			curtable->fixedsize = val;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): multiple value `%s' for fixedsize in html string at line %d\n", __func__, str, hllineno);
		return (1);
	}

	return (0);
}

/* check gradientangle value */
int dphl_chk_gradientangle(char *str, int mode)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for gradientangle in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for gradientangle in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for gradientangle in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for gradientangle in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}
	if (ival > 360) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): value `%s' for gradientangle is > 360 degrees in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed ... 360 */
	if (mode == T_TD) {
		/* <td> gradientangle */
		if (curtd->gradientangle == -1) {
			curtd->gradientangle = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> gradientangle */
		if (curtable->gradientangle == -1) {
			curtable->gradientangle = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for gradientangle in html string at line %d\n",
			 __func__, str, hllineno);
		return (1);
	}

	return (0);
}

/* check height value */
int dphl_chk_height(char *str, int mode)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for height in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for height in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for height in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for height in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (ival > 65535) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for height (max is 65535) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed */
	if (mode == T_TD) {
		/* <td> height */
		if (curtd->height == -1) {
			curtd->height = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> height */
		if (curtable->height == -1) {
			curtable->height = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for height in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	return (0);
}

/* check href value */
int dphl_chk_href(char *str, int mode)
{
	int err = 0;

	if (strlen(str) == 0) {
		/* href="" is oke */
		return (0);
	}
	/* twice href is not allowed */
	if (mode == T_TD) {
		/* <td> href */
		if (curtd->href == NULL) {
			curtd->href = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> href */
		if (curtable->href == NULL) {
			curtable->href = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for href in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	return (0);
}

/* check id value */
int dphl_chk_id(char *str, int mode)
{
	int err = 0;

	if (strlen(str) == 0) {
		/* id="" is oke */
		return (0);
	}
	/* twice id is not allowed */
	if (mode == T_TD) {
		/* <td> id */
		if (curtd->id == NULL) {
			curtd->id = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> id */
		if (curtable->id == NULL) {
			curtable->id = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for id in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	return (0);
}

/* check port value */
int dphl_chk_port(char *str, int mode)
{
	int err = 0;

	if (strlen(str) == 0) {
		/* port="" is oke */
		return (0);
	}
	/* twice port is not allowed */
	/* check portname and compass point here todo */
	if (mode == T_TD) {
		/* <td> port */
		if (curtd->port == NULL) {
			curtd->port = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> port */
		if (curtable->port == NULL) {
			curtable->port = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for port in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	return (0);
}

/* check point-size value for font */
int dphl_chk_pointsize(char *str)
{
	int ival = 0;
	int pe = 0;
	int es = 0;
	double dnum = 0.0;
	struct dpnum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for point-size in html string\n", __func__, str);
		return (1);
	}
	num = dp_getnum(str);
	dnum = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for point-size in html string\n", __func__, str);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for point-size in html string\n", __func__, str);
		return (1);
	}

	if (dnum < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for point-size in html string\n", __func__, str);
		return (1);
	}
	if (dnum > 255) {
		printf("%s(): limiting too high pointsize %f to 255\n", __func__, dnum);
		dnum = 255;
	}
	ival = (int)dnum;
	/* ival is the font pointsize */
	/* pointsize 0 is allowed */
	/* <font> point-size */
	if (curfont->pointsize == -1) {
		curfont->pointsize = ival;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for point-size in html string\n", __func__, str);
		return (1);
	}

	return (0);
}

/* check rows value in <table> */
int dphl_chk_rows(char *str)
{
	/* only a single '*' is allowed */
	if (strlen(str) != 1) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for rows in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	if (*str != '*') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for rows in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (curtable->rows == NULL) {
		curtable->rows = str;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for rows in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}

	return (0);
}

/* check rowspan value in <td> */
int dphl_chk_rowspan(char *str)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for rowspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for rowspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for rowspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for rowspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (ival == 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): zero value `%s' for rowspan in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (ival > 65535) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for rowspan (max is 65535) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is not allowed */
	/* <td> rowspan */
	if (curtd->rowspan == -1) {
		curtd->rowspan = ival;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for rowspan in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}

	/* todo */
	if (curtd->rowspan > 1) {
		printf("%s(): rowspan=%d is not yet implemented in this version\n", __func__, curtd->rowspan);
	}

	return (0);
}

/* check scale value for img */
int dphl_chk_scale(char *str)
{
	int status = 0;
	int val = 0;

	if (strcasecmp(str, "false") == 0) {
		val = DP_IMGF;
	} else if (strcasecmp(str, "true") == 0) {
		val = DP_IMGT;
	} else if (strcasecmp(str, "width") == 0) {
		val = DP_IMGW;
	} else if (strcasecmp(str, "height") == 0) {
		val = DP_IMGH;
	} else if (strcasecmp(str, "both") == 0) {
		val = DP_IMGB;
	} else {
		status = 1;
	}

	/* check error status */
	if (status) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): unknown value `%s' for img scale in html string\n", __func__, str);
		return (1);
	}

	/* <img> scale */
	if (curimg->scale == -1) {
		curimg->scale = val;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): unknown value `%s' for img scale in html string\n", __func__, str);
		return (1);
	}

	return (0);
}

/* check sides value */
int dphl_chk_sides(char *str, int mode)
{
	int err = 0;
	char *p = NULL;
	if (strlen(str) == 0) {
		/* sides="" is oke */
		return (0);
	}
	/* twice sides is not allowed */
	/* check sides letters ltrb in string */
	p = str;
	err = 0;
	while (*p) {
		if (*p == 'l' || *p == 't' || *p == 'r' || *p == 'b' || *p == 'L' || *p == 'T' || *p == 'R' || *p == 'B') {
			/* oke */
		} else {
			err = 1;
			break;
		}
		p++;
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for sides in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (mode == T_TD) {
		/* <td> sides */
		if (curtd->sides == NULL) {
			curtd->sides = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> sides */
		if (curtable->sides == NULL) {
			curtable->sides = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for sides in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check src value for img */
int dphl_chk_src(char *str)
{
	/* there must be something set as image source */
	if (strlen(str) == 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for img src in html string\n", __func__, str);
		return (1);
	}

	/* <img> src */
	if (curimg->src == NULL) {
		curimg->src = str;
	} else {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for img src in html string\n", __func__, str);
		return (1);
	}

	return (0);
}

/* check style value
 * dot uses strtok() at multiple places and that has a problem
 * that empty args are not detected, so a string like "invis,,,,," is valid
 * todo: solution can be own strtok() which returns "" at empty string
 * and then issue warning on a unusual string. see below.
 */
int dphl_chk_style(char *str, int mode)
{
	int rounded = 0;
	int radial = 0;
	int invis = 0;
	int dotted = 0;
	int dashed = 0;
	int err = 0;
	char *ptr = NULL;
	char *res = NULL;
	int once = 0;
	if (strlen(str) == 0) {
		/* style="" is oke */
		return (0);
	}
	/* twice style is not allowed */
	/* check style args in string todo */
	if (mode == T_TD) {
		/* <td> style */
		if (curtd->style == NULL) {
			curtd->style = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> style */
		if (curtable->style == NULL) {
			curtable->style = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for style in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	/* check style string */
	if (strlen(str)) {
		err = 0;
		ptr = dp_calloc(1, strlen(str) + 1);
		if (ptr == NULL) {
			return (1);
		}
		strcat(ptr, str);
		/* this does not detect strings like "  ,,,,," */
		once = 0;
		/* strsep() is replacement for old strtok() todo */
		res = strtok(ptr, " ,");
		while (res) {
			once = 1;
			if (strcasecmp(res, "rounded") == 0) {
				rounded = 1;
			} else if (strcasecmp(res, "radial") == 0) {
				radial = 1;
			} else if (strcasecmp(res, "solid") == 0) {
				dotted = 1;
				dashed = 1;
			} else if (strcasecmp(res, "invis") == 0) {
				invis = 1;
			} else if (strcasecmp(res, "invisible") == 0) {
				invis = 1;
			} else if (strcasecmp(res, "dotted") == 0) {
				dotted = 1;
			} else if (strcasecmp(res, "dashed") == 0) {
				dashed = 1;
			} else {
				err = 1;
			}
			res = strtok(NULL, " ,");
		}
		dp_free(ptr);
		ptr = NULL;
		if (once == 0) {
			/* strtok did not detect valid tokens as in a string like ",,   ,," */
			err = 1;
		}
		if (err) {
			memset(dp_errmsg, 0, 256);
			snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for style in html string at line %d\n", __func__,
				 str, hllineno);
			return (1);
		}
	}
	/* set the options */
	if (mode == T_TD) {
		curtd->stylerounded = rounded;	/* style options */
		curtd->styleradial = radial;	/* style options */
		curtd->styleinvis = invis;	/* style options */
		curtd->styledotted = dotted;	/* style options */
		curtd->styledashed = dashed;	/* style options */
	} else if (mode == T_TABLE) {
		curtable->stylerounded = rounded;	/* style options */
		curtable->styleradial = radial;	/* style options */
		curtable->styleinvis = invis;	/* style options */
		curtable->styledotted = dotted;	/* style options */
		curtable->styledashed = dashed;	/* style options */
	} else {
		/* shouldnothappen */
	}

	return (0);
}

/* check target value */
int dphl_chk_target(char *str, int mode)
{
	int err = 0;
	if (strlen(str) == 0) {
		/* target="" is oke */
		return (0);
	}
	/* twice target is not allowed */
	/* check target args in string todo */
	if (mode == T_TD) {
		/* <td> target */
		if (curtd->target == NULL) {
			curtd->target = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> target */
		if (curtable->target == NULL) {
			curtable->target = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for target in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check title value */
int dphl_chk_title(char *str, int mode)
{
	int err = 0;
	if (strlen(str) == 0) {
		/* title="" is oke */
		return (0);
	}
	/* twice title is not allowed */
	if (mode == T_TD) {
		/* <td> title or tooltip */
		if (curtd->title == NULL) {
			curtd->title = str;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> title or tooltip */
		if (curtable->title == NULL) {
			curtable->title = str;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for title in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check valign value */
int dphl_chk_valign(char *str, int mode)
{
	int status = 0;
	int val = 0;
	int err = 0;
	if (strcasecmp(str, "middle") == 0) {
		val = DP_VALIGNM;
	} else if (strcasecmp(str, "bottom") == 0) {
		val = DP_VALIGNB;
	} else if (strcasecmp(str, "top") == 0) {
		val = DP_VALIGNT;
	} else {
		status = 1;
	}

	/* check error status */
	if (status) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): unknown value `%s' for valign in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	/* twice valign is not allowed */
	if (mode == T_TD) {
		/* <td> valign */
		if (curtd->valign == -1) {
			curtd->valign = val;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> valign */
		if (curtable->valign == -1) {
			curtable->valign = val;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for valign in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* check width value */
int dphl_chk_width(char *str, int mode)
{
	int n = 0;
	int ival = 0;
	int pe = 0;
	int es = 0;
	int err = 0;
	struct dpinum *num = NULL;
	if (*str == '-') {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for width in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	num = dp_getinum(str);
	n = num->number;
	pe = num->pe;
	es = num->es;
	dp_free(num);
	num = NULL;
	if (es) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): empty value `%s' for width in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	if (pe) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): bad value `%s' for width in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	ival = n;
	if (ival < 0) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): negative value `%s' for width in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	if (ival > 65535) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1),
			 "html %s(): too high value `%s' for width (max is 65535) in html string at line %d\n", __func__, str,
			 hllineno);
		return (1);
	}
	/* ival is the size */
	/* size 0 is allowed */
	if (mode == T_TD) {
		/* <td> width */
		if (curtd->width == -1) {
			curtd->width = ival;
		} else {
			err = 1;
		}
	} else if (mode == T_TABLE) {
		/* <table> width */
		if (curtable->width == -1) {
			curtable->width = ival;
		} else {
			err = 1;
		}
	} else {
		/* shouldnothappen */
	}
	if (err) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): multiple value `%s' for width in html string at line %d\n", __func__,
			 str, hllineno);
		return (1);
	}
	return (0);
}

/* reset <br> newline */
void dphl_rbr(void)
{
	if (curbr) {
		dp_free(curbr);
		curbr = NULL;
	}

	curbr = dp_calloc(1, sizeof(struct brdata));

	if (curbr == NULL) {
		return;
	}

	curbr->align = (-1);	/* ="center|left|right" */

	return;
}

/* end <br> newline */
void dphl_ebr(void)
{

	if (hlinf == NULL) {
		/* shouldnothappen */
		return;
	}

	/* only at first data token
	 * or at <br>
	 */
	if (hlinf->mode < 0) {
		/* check for <table> token */
		if (curtable == NULL) {
			/* mode=items */
			hlinf->mode = 0;
		} else {
			/* mode=tables */
			hlinf->mode = 1;
			/* shouldnothappen */
		}
	}

	/* add <br> */
	if (hlinf->mode) {
		/* add <br> to tables */
		dphl_itemtables(NULL, NULL, 1);
	} else {
		/* add <br> to items */
		dphl_itemitems(NULL, NULL, 1);
	}

	return;
}

/* reset <i> italic text */
void dphl_ri(void)
{
	curi++;
	return;
}

/* end </i> */
void dphl_ei(void)
{
	if (curi) {
		curi--;
	}
	return;
}

/* reset <b> bold text */
void dphl_rb(void)
{
	curb++;
	return;
}

/* end </b> */
void dphl_eb(void)
{
	if (curb) {
		curb--;
	}
	return;
}

/* reset <u> underline text */
void dphl_ru(void)
{
	curu++;
	return;
}

/* end </u> */
void dphl_eu(void)
{
	if (curu) {
		curu--;
	}
	return;
}

/* reset <o> overline text */
void dphl_ro(void)
{
	curo++;
	return;
}

/* end </o> */
void dphl_eo(void)
{
	if (curo) {
		curo--;
	}
	return;
}

/* reset <sub> subscript text */
void dphl_rsub(void)
{
	cursub++;
	if (cursup) {
		printf("html %s(): turning superscript <sup> off because of subscript <sub> tag in html string at line %d\n",
		       __func__, hllineno);
	}
	/* force superscript off */
	cursup = 0;
	return;
}

/* end </sub> */
void dphl_esub(void)
{
	if (cursub) {
		cursub--;
	}
	return;
}

/* reset <sup> superscript text */
void dphl_rsup(void)
{
	cursup++;
	if (cursub) {
		printf("html %s(): turning subscript <sub> off because of superscript <sup> tag in html string at line %d\n",
		       __func__, hllineno);
	}
	/* force subscript off */
	cursub = 0;
	return;
}

/* end </sup> */
void dphl_esup(void)
{
	if (cursup) {
		cursup--;
	}
	return;
}

/* reset <s> strike-through text */
void dphl_rs(void)
{
	curs++;
	return;
}

/* end </s> */
void dphl_es(void)
{
	if (curs) {
		curs--;
	}
	return;
}

/* reset <vr/> vertical-ruler */
void dphl_rvr(void)
{
	/* set token <vr> is opt 3 */
	dphl_itemtables(NULL, NULL, 3);
	return;
}

/* reset <hr/> horizontal-ruler */
void dphl_rhr(void)
{
	/* set token <hr> is opt 2 */
	dphl_itemtables(NULL, NULL, 2);
	return;
}

/* reset <img> image-data */
void dphl_rimg(void)
{
	if (curimg) {
		dp_free(curimg);
		curimg = NULL;
	}

	curimg = dp_calloc(1, sizeof(struct imgdata));

	if (curimg == NULL) {
		return;
	}

	curimg->scale = (-1);	/* ="false|true|width|height|both" */
	curimg->src = NULL;	/* ="imagename" */

	return;
}

/* end <img>
 * there should be a image source be set now.
 */
void dphl_eimg(void)
{

	if (curimg == NULL) {
		/* shouldnothappen */
		return;
	}

	if (curimg->src == NULL) {
		memset(dp_errmsg, 0, 256);
		snprintf(dp_errmsg, (256 - 1), "html %s(): no image name set in src in <img> tag in html string at line %d\n",
			 __func__, hllineno);
	} else {
		/* ignore src="" as image name */
		if (strlen(curimg->src) != 0) {
			/* set token <img> is opt 4 */
			dphl_itemtables(NULL, NULL, 4);
		}
	}

	dp_free(curimg);
	curimg = NULL;

	return;
}

/* font on stack */
static void dphl_pushfont(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <font> */
	if (fontstack == NULL) {
		fontstack = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
		if (fontstack == NULL) {
			return;
		}
	}

	if (splay_tree_has_data(fontstack) == 0) {
		/* first entry */
		splay_tree_insert(fontstack, (splay_tree_key) 0, (splay_tree_value) curfont);
		return;
	}

	spn = splay_tree_max(fontstack);

	/* current highest */
	val = (int)spn->key;

	/* incr. index in stack */
	val++;

	/* next entry */
	splay_tree_insert(fontstack, (splay_tree_key) val, (splay_tree_value) curfont);

	return;
}

/* font off stack */
static void dphl_pullfont(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <font> */
	if (fontstack == NULL) {
		curfont = NULL;
		return;
	}

	if (splay_tree_has_data(fontstack) == 0) {
		/* no data in tree */
		fontstack = splay_tree_delete(fontstack);
		curfont = NULL;
		return;
	}

	spn = splay_tree_max(fontstack);

	/* current highest */
	val = (int)spn->key;

	/* restore highest fontdata */
	curfont = (struct fontdata *)spn->value;

	/* delete highest entry */
	splay_tree_remove(fontstack, (splay_tree_key) val);

	return;
}

/* reset <font> */
void dphl_rfont(void)
{
	struct fontdata *curfont2 = NULL;
	struct fontldata *curfontl = NULL;

	curfontl = dp_calloc(1, sizeof(struct fontldata));

	if (curfontl == NULL) {
		/* shouldnothappen */
		return;
	}

	/* fresh table data */
	curfont2 = dp_calloc(1, sizeof(struct fontdata));

	if (curfont2 == NULL) {
		/* shouldnothappen */
		dp_free(curfontl);
		return;
	}

	curfontl->fd = curfont2;

	/* preset <font> */
	curfont2->color = (-1);	/* ="colorname" */
	curfont2->face = NULL;	/* ="fontname" */
	curfont2->pointsize = (-1);	/* ="int-number" */

	/* link in curfont */
	if (fontlist == NULL) {
		fontlist = curfontl;
		fontlistend = curfontl;
	} else {
		fontlistend->next = curfontl;
		fontlistend = curfontl;
	}

	/* push old curfont if any */
	if (curfont) {
		dphl_pushfont();
	}

	curfont = curfont2;

	return;
}

/* end <font> */
void dphl_efont(void)
{
	/* pull font */
	dphl_pullfont();
	return;
}

/* table on stack */
static void dphl_pushtable(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <table> */
	if (tablestack == NULL) {
		tablestack = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
		if (tablestack == NULL) {
			return;
		}
	}

	if (splay_tree_has_data(tablestack) == 0) {
		/* first entry */
		splay_tree_insert(tablestack, (splay_tree_key) 0, (splay_tree_value) curtable);
		return;
	}

	spn = splay_tree_max(tablestack);

	/* current highest */
	val = (int)spn->key;

	/* incr. index in stack */
	val++;

	/* next entry */
	splay_tree_insert(tablestack, (splay_tree_key) val, (splay_tree_value) curtable);

	return;
}

/* table off stack */
static void dphl_pulltable(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <table> */
	if (tablestack == NULL) {
		curtable = NULL;
		return;
	}

	if (splay_tree_has_data(tablestack) == 0) {
		/* no data in tree */
		tablestack = splay_tree_delete(tablestack);
		curtable = NULL;
		return;
	}

	spn = splay_tree_max(tablestack);

	/* current highest */
	val = (int)spn->key;

	/* restore highest tabledata */
	curtable = (struct tabledata *)spn->value;

	/* delete highest entry */
	splay_tree_remove(tablestack, (splay_tree_key) val);

	return;
}

/* at new <table> to current <td> */
static void dphl_addtableitem(struct tabledata *newtable)
{
	struct ilist *il = NULL;

	if (yydebug || 0) {
		printf("%s(): setting new <table> in current <td> items\n", __func__);
	}

	/* if opt is set it is br=1, hr=2, vr=3, img=4, table=5 */
	if (hlinf == NULL) {
		/* shouldnothappen */
		return;
	}

	if (hlinf->mode == 0) {
		/* shouldnothappen */
		return;
	}

	if (curtable == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtable\n", __func__);
		return;
	}

	if (curtd == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtd\n", __func__);
		return;
	}

	if (curtr == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtr\n", __func__);
		return;
	}

	il = dp_calloc(1, sizeof(struct ilist));

	/* set linkage to data */
	il->items = dphl_makeitem( /* str */ NULL, /* alt */ NULL, /* opt */ 5, newtable);

	/* <td> belongs to this <table> */
	curtd->table = curtable;

	/* indicate in <td> this is a <table> */
	curtd->istab = 1;

	/* indicate in <tr> there is a <td> with a <table> statement */
	curtr->hastab = 1;

	if (curtd->il == NULL) {
		curtd->il = il;
		curtd->ilend = il;
	} else {
		curtd->ilend->next = il;
		curtd->ilend = il;
	}

	return;
}

/* reset <table> at start */
void dphl_rtable(void)
{
	struct tlist *tli = NULL;	/* list of table items */
	struct tabledata *curtable2 = NULL;
	struct tableldata *curtablel = NULL;

	if (hlinf->mode < 1) {
		/* mode=tables */
		hlinf->mode = 1;
		if (hlinf->il) {
			/* todo, clear no il and ilend items */
			printf("%s(): switch to <table> mode and hlinf->il=%p to clear\n", __func__, (void *)hlinf->il);
		}
	}

	curtablel = dp_calloc(1, sizeof(struct tableldata));

	tli = dp_calloc(1, sizeof(struct tlist));

	/* fresh table data */
	curtable2 = dp_calloc(1, sizeof(struct tabledata));

	curtablel->tabdata = curtable2;

	/* set as table item */
	tli->titem = curtablel;

	/* preset <table> */
	curtable2->align = (-1);	/* ="center|left|right" */

	if (curtable) {
		curtable2->bgcolor = curtable->bgcolor;	/* ="colorname" */
	} else {
		curtable2->bgcolor = (-1);	/* ="colorname" */
	}
	if (curtd) {
		curtable2->bgcolor = curtd->bgcolor;	/* ="colorname" */
	} else {
		curtable2->bgcolor = (-1);	/* ="colorname" */
	}

	curtable2->border = (-1);	/* ="int-value" */
	curtable2->cellborder = (-1);	/* ="int-value" */
	curtable2->cellpadding = (-1);	/* ="int-value" */
	curtable2->cellspacing = (-1);	/* ="int-value" */

	/* todo see above for fontcolor */
	curtable2->color = (-1);	/* ="colorname" */
	curtable2->columns = NULL;	/* ="string" */
	curtable2->fixedsize = (-1);	/* ="true|false" */
	curtable2->gradientangle = (-1);	/* ="int-value" */
	curtable2->height = (-1);	/* ="int-value" */
	curtable2->href = NULL;	/* ="string" */
	curtable2->id = NULL;	/* ="string" */
	curtable2->port = NULL;	/* ="string" */
	curtable2->rows = NULL;	/* ="string" */
	curtable2->sides = NULL;	/* ="string" */
	curtable2->style = NULL;	/* ="string" */
	curtable2->stylerounded = (-1);	/* style options */
	curtable2->styleradial = (-1);	/* style options */
	curtable2->styleinvis = (-1);	/* style options */
	curtable2->styledotted = (-1);	/* style options */
	curtable2->styledashed = (-1);	/* style options */
	curtable2->target = NULL;	/* ="string" */
	curtable2->title = NULL;	/* ="string" */
	curtable2->valign = (-1);	/* ="middle|bottom|top" */
	curtable2->width = (-1);	/* ="int-value" */

	curtable2->table = curtable;	/* rooted on this table or 0 */

	/* not at first <table> entry */
	if (curtd) {
		dphl_addtableitem(curtable2);
	}

	/* push old curtable if any */
	if (curtable) {
		dphl_pushtable();
	}

	/* first entry if 0 */
	if (curtable == NULL) {
		/* add to main hlinf */
		if (hlinf->tl == NULL) {
			hlinf->tl = tli;
			hlinf->tlend = tli;
		} else {
			hlinf->tlend->next = tli;
			hlinf->tlend = tli;
		}
	} else {
		if (yydebug || 0) {
			printf("%s(): add to sub %p ", __func__, (void *)tli);
		}
		/* add as sub table entry */
		if (curtable->tl == NULL) {
			curtable->tl = tli;
			curtable->tlend = tli;
		} else {
			curtable->tlend->next = tli;
			curtable->tlend = tli;
		}
	}

	if (yydebug || 0) {
		printf("hlinf->tl=%p\n table from %p to %p", (void *)hlinf->tl, (void *)curtable, (void *)curtable2);
	}

	curtable = curtable2;

	return;
}

/* end <table> */
void dphl_etable(void)
{
	/* pull curtable if any */
	dphl_pulltable();
	return;
}

/* td on stack */
static void dphl_pushtd(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <td> */
	if (tdstack == NULL) {
		tdstack = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
		if (tdstack == NULL) {
			return;
		}
	}

	if (splay_tree_has_data(tdstack) == 0) {
		/* first entry */
		splay_tree_insert(tdstack, (splay_tree_key) 0, (splay_tree_value) curtd);
		return;
	}

	spn = splay_tree_max(tdstack);

	/* current highest */
	val = (int)spn->key;

	/* incr. index in stack */
	val++;

	/* next entry */
	splay_tree_insert(tdstack, (splay_tree_key) val, (splay_tree_value) curtd);

	return;
}

/* td off stack */
static void dphl_pulltd(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <td> */
	if (tdstack == NULL) {
		curtd = NULL;
		return;
	}

	if (splay_tree_has_data(tdstack) == 0) {
		/* no data in tree */
		tdstack = splay_tree_delete(tdstack);
		curtd = NULL;
		return;
	}

	spn = splay_tree_max(tdstack);

	/* current highest */
	val = (int)spn->key;

	/* restore highest tddata */
	curtd = (struct tddata *)spn->value;

	/* delete highest entry */
	splay_tree_remove(tdstack, (splay_tree_key) val);

	return;
}

/* reset <td> table data */
void dphl_rtd(void)
{
	struct tddata *curtd2 = NULL;
	struct tdldata *curtdl = NULL;

	if (curtr == NULL) {
		/* shouldnothappen */
		printf("%s(): nil tr\n", __func__);
		return;
	}

	curtdl = dp_calloc(1, sizeof(struct tdldata));

	/* fresh table data */
	curtd2 = dp_calloc(1, sizeof(struct tddata));

	/* push old curtd if any */
	if (curtd) {
		dphl_pushtd();
	}

	/* preset <td> */
	curtd2->align = (-1);	/* ="center|left|right|text" */
	curtd2->balign = (-1);	/* ="center|left|right" */
	curtd2->bgcolor = (-1);	/* ="colorname" */
	curtd2->border = (-1);	/* ="int-value" */
	curtd2->cellpadding = (-1);	/* ="int-value" */
	curtd2->cellspacing = (-1);	/* ="int-value" */
	curtd2->color = (-1);	/* ="colorname" */
	curtd2->colspan = (-1);	/* ="int-value" */
	curtd2->fixedsize = (-1);	/* ="true|false" */
	curtd2->gradientangle = (-1);	/* ="int-value" */
	curtd2->height = (-1);	/* ="int-value" */
	curtd2->href = NULL;	/* ="string" */
	curtd2->id = NULL;	/* ="string" */
	curtd2->port = NULL;	/* ="string" */
	curtd2->rowspan = (-1);	/* ="int-value" */
	curtd2->sides = NULL;	/* ="string" */
	curtd2->style = NULL;	/* ="string" */
	curtd2->stylerounded = (-1);	/* style options */
	curtd2->styleradial = (-1);	/* style options */
	curtd2->styleinvis = (-1);	/* style options */
	curtd2->styledotted = (-1);	/* style options */
	curtd2->styledashed = (-1);	/* style options */
	curtd2->target = NULL;	/* ="string" */
	curtd2->title = NULL;	/* ="string" */
	curtd2->valign = (-1);	/* ="middle|bottom|top" */
	curtd2->width = (-1);	/* ="int-value" */

	curtd = curtd2;

	curtdl->tdd = curtd;

	if (curtr->td == NULL) {
		/* td items in tr */
		curtr->td = curtdl;
		curtr->tdend = curtdl;
	} else {
		curtr->tdend->next = curtdl;
		curtr->tdend = curtdl;
	}

	return;
}

/* end <td>
 * code is 0 for text item or new table data
 * code is 1 for image data
 * code is 2 for <tr><td></td></tr>
 */
void dphl_etd(int code)
{
	/* curdata has data, with curtd settings */
	if (code == 2) {
		/* this can indicate there is something wrong in generated grph data */
		printf("%s(): <td> with no items found\n", __func__);
	}

	/* pull curtd if any */
	dphl_pulltd();

	return;
}

/* tr on stack */
static void dphl_pushtr(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <tr> */
	if (trstack == NULL) {
		trstack = splay_tree_new(splay_tree_compare_ints, NULL, NULL);
	}

	if (splay_tree_has_data(trstack) == 0) {
		/* first entry */
		splay_tree_insert(trstack, (splay_tree_key) 0, (splay_tree_value) curtr);
		return;
	}

	spn = splay_tree_max(trstack);

	/* current highest */
	val = (int)spn->key;

	/* incr. index in stack */
	val++;

	/* next entry */
	splay_tree_insert(trstack, (splay_tree_key) val, (splay_tree_value) curtr);

	return;
}

/* tr off stack */
static void dphl_pulltr(void)
{
	splay_tree_node spn = NULL;
	int val = 0;

	/* data for <tr> */
	if (trstack == NULL) {
		curtr = NULL;
		return;
	}

	if (splay_tree_has_data(trstack) == 0) {
		/* no data in tree */
		trstack = splay_tree_delete(trstack);
		curtr = NULL;
		return;
	}

	spn = splay_tree_max(trstack);

	/* current highest */
	val = (int)spn->key;

	/* restore highest trdata */
	curtr = (struct trdata *)spn->value;

	/* delete highest entry */
	splay_tree_remove(trstack, (splay_tree_key) val);

	return;
}

/* reset <tr> */
void dphl_rtr(void)
{
	struct trdata *tri = NULL;
	struct trlist *trl = NULL;

	if (curtable == NULL) {
		/* shouldnothappen */
		printf("%s(): nil curtable\n", __func__);
		return;
	}

	trl = dp_calloc(1, sizeof(struct trlist));

	tri = dp_calloc(1, sizeof(struct trdata));

	trl->tritem = tri;

	tri->table = curtable;

	if (curtable->tr == NULL) {
		curtable->tr = trl;
		curtable->trend = trl;
	} else {
		curtable->trend->next = trl;
		curtable->trend = trl;
	}

	if (curtr) {
		dphl_pushtr();
	}

	curtr = tri;

	return;
}

/* end </tr> */
void dphl_etr(void)
{

	/* pull curtr if any */
	dphl_pulltr();

	return;
}

/* gets data part */
void dphl_data(char *str)
{
	char *altstr = NULL;

	if (yydebug || 0) {
		printf("html %s(): data is \"%s\"\n", __func__, str);
	}

	if (str == NULL) {
		/* shouldnothappen */
		return;
	}

	/* translate html chars if any */
	if (strchr(str, '&')) {
		/* this can set error status */
		altstr = dplh_htrans(str);
		if (yydebug || 0) {
			printf("%s(): translated html char is \"%s\"\n", __func__, altstr);
		}
		if (dphl_chk_err()) {
			return;
		}
	}

	curdata = str;

	if (hlinf == NULL) {
		/* shouldnothappen */
		return;
	}

	/* only at first data token
	 * or at <br>
	 */
	if (hlinf->mode < 0) {
		/* check for <table> token */
		if (curtable == NULL) {
			/* mode=items */
			hlinf->mode = 0;
		} else {
			/* mode=tables */
			hlinf->mode = 1;
		}
	}

	/* add to items or tables */
	if (hlinf->mode == 0) {
		dphl_itemitems(str, altstr, 0);
	} else {
		dphl_itemtables(str, altstr, 0);
	}

	return;
}

/* free mem used by html label parsing, node hlinfo data is cleared later in dp_clearall() */
void dphl_freemem(void)
{
	struct fontldata *fptr = NULL;
	struct fontldata *fptrnext = NULL;

	/* data for <br> */
	if (curbr) {
		dp_free(curbr);
		curbr = NULL;
	}

	/* data for <img> */
	if (curimg) {
		dp_free(curimg);
		curimg = NULL;
	}

	/* <table> data */
	if (tablestack) {
		tablestack = splay_tree_delete(tablestack);
	}

	/* <td> data */
	if (tdstack) {
		tdstack = splay_tree_delete(tdstack);
	}

	/* <tr> data */
	if (trstack) {
		trstack = splay_tree_delete(trstack);
	}

	/* <font> data */
	fptr = fontlist;

	while (fptr) {
		fptrnext = fptr->next;
		if (fptr->fd) {
			dp_free(fptr->fd);
		}
		fptr->fd = NULL;
		dp_free(fptr);
		fptr = fptrnext;
	}

	fontlist = NULL;
	fontlistend = NULL;

	/* <font> data */
	if (fontstack) {
		fontstack = splay_tree_delete(fontstack);
	}

	/* data */
	curdata = NULL;

	/* <s> strike-through */
	curs = 0;

	/* <sup> superscript text */
	cursup = 0;

	/* <sub> subscript text */
	cursub = 0;

	/* <o> overline text */
	curo = 0;

	/* <u> underline text */
	curu = 0;

	/* <b> bold text */
	curb = 0;

	/* <i> italic text */
	curi = 0;

	return;
}

/* end */
