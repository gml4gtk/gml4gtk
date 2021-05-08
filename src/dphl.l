
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

/*
 * <br    /> is oke but < br/> not or <br/ > is not oke
 * <br/> is lexed as token "<br" and token "/>"
 */

/* gcc-11 analyzer has several problems with the flex-2.4.6 generated lexers, even with own customized skeleton */

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "splay-tree.h"
#include "lex.yy.h"
#include "dot.tab.h"
#include "dp.h"
#include "dpus.h"
#include "dphlparser.h"
#include "dphl.h"
#include "dpmem.h"

/* use GNU GCC compiler builtin strlen */
#undef YY_NEED_STRLEN

/* temp buffer */
static char *tmp = NULL;
static char *pt = NULL;
static char *q = NULL;

/* ws */
static int skipws = 1;

/* own yyalloc
 * void *yyalloc (size_t n) { return(calloc(1,n)); }
 * void yyfree (void *ptr) { if(ptr) { free (ptr); } return; }
 * void *yyrealloc (void *ptr, size_t n) { return (realloc (ptr,n)); }
 */

%}

	/* use own yyalloc
	 * %option noyyalloc
	 * %option noyyfree
	 * %option noyyrealloc
	 */

	/* no yywrap() at end-of-file */
%option noyywrap

	/* do not push back chars in stream function() */
%option nounput

	/* no input() function */
%option noinput

	/* input does not come from a tty. */
%option never-interactive

	/* no yywrap() at end of file */
%option noyywrap

	/* 8-bits scanner */
%option 8bit

	/* use nameprefix for routines */
%option prefix="hl"

	/* add debug output */
%option debug

	/* use clib to read data */
%option noread

	/* line no */
%option yylineno

	/* "string" as in var="value" */
ISTR	[^\\\"]|\\.|\\\n
STR	\"({ISTR}*)\"

	/* 'string' as in var='value' */
ISTRA	[^\\\']|\\.|\\\n
STRA	\'({ISTRA}*)\'

	/* chars in a <var> */
chars [a-zA-Z]*

	/* chars in a tag with a '-' for point-size */
charsattr [a-zA-Z-]*

nl		(\r\n|\r|\n)
open		{nl}?"<"
close		">"{nl}?
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}



%%

{comment}		{ /* skip comment and it does not allow <> chars in it or nested comments */ }

[\f ]+			{ /* skip form feed chars and spaces */ }
[\t]			{ /* skip tabs */ }
[\n]			{ /* skip new line */ /* lexer does update yylineno */ }
[\r]			{ /* skip carriage return */ }

"<"{chars}		{
			hlylval.string = dp_uniqstr (yytext);
			/* start of tag */
			if (strcasecmp (yytext, "<b") == 0) {
			  skipws = 0;
			  return (HL_B);
			} else if (strcasecmp (yytext, "<br") == 0) {
			  skipws = 0;
			  dphl_rbr ();
			  return (HL_BR);
			} else if (strcasecmp (yytext, "<font") == 0) {
			  skipws = 0;
			  return (HL_FONT);
			} else if (strcasecmp (yytext, "<hr") == 0) {
			  dphl_rhr ();
			  return (HL_HR);
			} else if (strcasecmp (yytext, "<html") == 0) {
			  return (HL_HTML);
			} else if (strcasecmp (yytext, "<i") == 0) {
			  skipws = 0;
			  return (HL_I);
			} else if (strcasecmp (yytext, "<img") == 0) {
			  return (HL_IMG);
			} else if (strcasecmp (yytext, "<o") == 0) {
			  skipws = 0;
			  return (HL_O);
			} else if (strcasecmp (yytext, "<s") == 0) {
			  skipws = 0;
			  return (HL_S);
			} else if (strcasecmp (yytext, "<sub") == 0) {
			  skipws = 0;
			  return (HL_SUB);
			} else if (strcasecmp (yytext, "<sup") == 0) {
			  skipws = 0;
			  return (HL_SUP);
			} else if (strcasecmp (yytext, "<table") == 0) {
			  return (HL_TABLE);
			} else if (strcasecmp (yytext, "<th") == 0) {
			  /* undocumented that "th" is same as "td" */
			  return (HL_TD);
			} else if (strcasecmp (yytext, "<td") == 0) {
			  return (HL_TD);
			} else if (strcasecmp (yytext, "<tr") == 0) {
			  return (HL_TR);
			} else if (strcasecmp (yytext, "<u") == 0) {
			  skipws = 0;
			  return (HL_U);
			} else if (strcasecmp (yytext, "<vr") == 0) {
			  dphl_rvr ();
			  return (HL_VR);
			} else {
			  /* this is a unknown tag at start */
			  memset(dp_errmsg, 0, 256);
			  snprintf(dp_errmsg, (256 - 1), "%s(): unknown start tag `%s' in html string at line %d\n", __func__, yytext, hllineno);
			  return (EOF);
			}
			}

"</"{chars}		{
			hlylval.string = dp_uniqstr (yytext);
			/* end tag */
			if (strcasecmp (yytext, "</b") == 0) {
			  return (HL_C_B);
			} else if (strcasecmp (yytext, "</br") == 0) {
			  /* undocumented that <br></br> is same as <br/> */
			  return (HL_C_BR);
			} else if (strcasecmp (yytext, "</font") == 0) {
			  return (HL_C_FONT);
			} else if (strcasecmp (yytext, "</html") == 0) {
			  return (HL_C_HTML);
			} else if (strcasecmp (yytext, "</hr") == 0) {
			  /* it seems <hr></hr> could be same as <hr/> */
			  return (HL_C_HR);
			} else if (strcasecmp (yytext, "</i") == 0) {
			  return (HL_C_I);
			} else if (strcasecmp (yytext, "</img") == 0) {
			  /* it seems <img></img> couble be same ad <img/> */
			  return (HL_C_IMG);
			} else if (strcasecmp (yytext, "</o") == 0) {
			  return (HL_C_O);
			} else if (strcasecmp (yytext, "</s") == 0) {
			  return (HL_C_S);
			} else if (strcasecmp (yytext, "</sub") == 0) {
			  return (HL_C_SUB);
			} else if (strcasecmp (yytext, "</sup") == 0) {
			  return (HL_C_SUP);
			} else if (strcasecmp (yytext, "</table") == 0) {
			  return (HL_C_TABLE);
			} else if (strcasecmp (yytext, "</th") == 0) {
			  /* undocumented that "th" is same as "td" */
			  return (HL_C_TD);
			} else if (strcasecmp (yytext, "</td") == 0) {
			  return (HL_C_TD);
			} else if (strcasecmp (yytext, "</tr") == 0) {
			  return (HL_C_TR);
			} else if (strcasecmp (yytext, "</u") == 0) {
			  return (HL_C_U);
			} else if (strcasecmp (yytext, "</vr") == 0) {
			  /* it seems <vr></vr> could be same as <vr/> */
			  return (HL_C_VR);
			} else {
			  /* this is a unknown end tag */
			  memset(dp_errmsg, 0, 256);
			  snprintf(dp_errmsg, (256 - 1), "%s(): unknown end tag `%s' in html string at line %d\n", __func__, yytext, hllineno);
			  return (EOF);
			}
			}

"/>"			{
			/* end tag for br and hr, vr and img */
			hlylval.string = dp_uniqstr (yytext);
			return (HL_SC);
			}

">"			{
			/* end tag for others */
			hlylval.string = dp_uniqstr (yytext);
			return (HL_C);
			}

"="			{
			/* as in var=value */
			hlylval.string = dp_uniqstr (yytext);
			return (HL_IS);
			}

{STR}			{
			/* "string" as in var="value" */
			if (strlen (yytext) == 2) {
			hlylval.string = dp_uniqstr ("");
			return (HL_QSTR);
			}
			/* create copy buffer */
			tmp = dp_calloc (1, (yyleng+1));
			/* wipe last double quote */
			yytext[yyleng-1] = 0;
			/* copy past first char */
			pt = yytext;
			pt++;
			q = tmp;
			while (*pt)
			{
			  if (*pt == '\\') {
			   if (*(pt+1) == 0) {
			    *q = '\\';
			    q++;
			    pt++;
			   } else if (*(pt+1) == '\n') {
			    /* skip \\n */
			    pt = pt + 2;
			   } else if (*(pt+1) == '"') {
			    /* \" becomes " */
			    *q = '"';
			    q++;
			    pt = pt + 2;
			   } else if (*(pt+1) == '\\') {
			    /* \\ becomes \ */
			    *q = '\\';
			    q++;
			    pt = pt + 2;
			   } else {
			    *q = '\\';
			    q++;
			    *q = *(pt+1);
			    q++;
			    pt = pt + 2;
			   }
			  } else {
			    /* copy regular chars */
			    *q = *pt;
			    pt++;
			    q++;
			  }
			}
			hlylval.string = dp_uniqstr (tmp);
			dp_free (tmp);
			tmp = NULL;
			pt = NULL;
			q = NULL;
			return (HL_QSTR);
			}

{STRA}			{
			/* 'string' as in var='value' */
			if (strlen (yytext) == 2) {
			hlylval.string = dp_uniqstr ("");
			return (HL_QSTR);
			}
			/* create copy buffer */
			tmp = dp_calloc (1, (yyleng+1));
			/* wipe last quote */
			yytext[yyleng-1] = 0;
			/* copy past first char */
			pt = yytext;
			pt++;
			q = tmp;
			while (*pt)
			{
			  if (*pt == '\\') {
			   if (*(pt+1) == 0) {
			    *q = '\\';
			    q++;
			    pt++;
			   } else if (*(pt+1) == '\n') {
			    /* skip \\n */
			    pt = pt + 2;
			   } else if (*(pt+1) == '\'') {
			    /* \' becomes ' */
			    *q = '\'';
			    q++;
			    pt = pt + 2;
			   } else if (*(pt+1) == '\\') {
			    /* \\ becomes \ */
			    *q = '\\';
			    q++;
			    pt = pt + 2;
			   } else {
			    *q = '\\';
			    q++;
			    *q = *(pt+1);
			    q++;
			    pt = pt + 2;
			   }
			  } else {
			    /* copy regular chars */
			    *q = *pt;
			    pt++;
			    q++;
			  }
			}
			hlylval.string = dp_uniqstr (tmp);
			dp_free (tmp);
			tmp = NULL;
			pt = NULL;
			q = NULL;
			return (HL_QSTR);
			}

{charsattr}		{
			/* var */
			hlylval.string = dp_uniqstr (yytext);
			switch (*yytext)
			{
			case 'a':
			case 'A':
			if (strcasecmp (yytext, "align") == 0) {
			return (HL_ALIGN);
			}
			break;
			case 'b':
			case 'B':
			if (strcasecmp (yytext, "balign") == 0) {
			return (HL_BALIGN);
			} else if (strcasecmp (yytext, "bgcolor") == 0) {
			return (HL_BGCOLOR);
			} else if (strcasecmp (yytext, "border") == 0) {
			return (HL_BORDER);
			} else {
			/* unknown */
			}
			break;
			case 'c':
			case 'C':
			if (strcasecmp (yytext, "cellborder") == 0) {
			return (HL_CELLBORDER);
			} else if (strcasecmp (yytext, "cellpadding") == 0) {
			return (HL_CELLPADDING);
			} else if (strcasecmp (yytext, "cellspacing") == 0) {
			return (HL_CELLSPACING);
			} else if (strcasecmp (yytext, "color") == 0) {
			return (HL_COLOR);
			} else if (strcasecmp (yytext, "columns") == 0) {
			return (HL_COLUMNS);
			} else if (strcasecmp (yytext, "colspan") == 0) {
			return (HL_COLSPAN);
			} else {
			/* unknown */
			}
			break;
			case 'f':
			case 'F':
			if (strcasecmp (yytext, "face") == 0) {
			return (HL_FACE);
			} else if (strcasecmp (yytext, "fixedsize") == 0) {
			return (HL_FIXEDSIZE);
			} else {
			/* unknown */
			}
			break;
			case 'g':
			case 'G':
			if (strcasecmp (yytext, "gradientangle") == 0) {
			return (HL_GRADIENTANGLE);
			}
			break;
			case 'h':
			case 'H':
			if (strcasecmp (yytext, "height") == 0) {
			return (HL_HEIGHT);
			} else if (strcasecmp (yytext, "href") == 0) {
			return (HL_HREF);
			} else {
			/* unknown */
			}
			break;
			case 'i':
			case 'I':
			if (strcasecmp (yytext, "id") == 0) {
			return (HL_ID);
			}
			break;
			case 'p':
			case 'P':
			if (strcasecmp (yytext, "point-size") == 0) {
			return (HL_POINTSIZE);
			} else if (strcasecmp (yytext, "pointsize") == 0) {
			return (HL_POINTSIZE);
			} else if (strcasecmp (yytext, "port") == 0) {
			return (HL_PORT);
			} else {
			/* unknown */
			}
			break;
			case 'r':
			case 'R':
			if (strcasecmp (yytext, "rows") == 0) {
			return (HL_ROWS);
			} else if (strcasecmp (yytext, "rowspan") == 0) {
			return (HL_ROWSPAN);
			} else {
			/* unknown */
			}
			break;
			case 's':
			case 'S':
			if (strcasecmp (yytext, "scale") == 0) {
			return (HL_SCALE);
			} else if (strcasecmp (yytext, "sides") == 0) {
			return (HL_SIDES);
			} else if (strcasecmp (yytext, "src") == 0) {
			return (HL_SRC);
			} else if (strcasecmp (yytext, "style") == 0) {
			return (HL_STYLE);
			} else {
			/* unknown */
			}
			break;
			case 't':
			case 'T':
			if (strcasecmp (yytext, "target") == 0) {
			return (HL_TARGET);
			} else if (strcasecmp (yytext, "title") == 0) {
			return (HL_TITLE);
			} else if (strcasecmp (yytext, "tooltip") == 0) {
			return (HL_TOOLTIP);
			} else {
			/* unknown */
			}
			break;
			case 'v':
			case 'V':
			if (strcasecmp (yytext, "valign") == 0) {
			return (HL_VALIGN);
			}
			break;
			case 'w':
			case 'W':
			if (strcasecmp (yytext, "width") == 0) {
			return (HL_WIDTH);
			}
			break;
			default:
			/* unknown */
			break;
			}
			/* unknown */
			return (HL_STR);
			}

<<EOF>>			{
			/* end of buffer */
			return (EOF);
			}

.			{
			/* something unknown causes parse error */
			return ((int)yytext[0]);
			}

%%

/* lex buffer */
static YY_BUFFER_STATE buffer = NULL;

/* clear buffer */
static int clearit = 0;

/* lex buffer pending */
static int pending = 0;

/* lex buffer length */
static int buflen = 0;

/* data buffer */
static char *dbuf = (char *)0;

/* tag buffer */
static char *tbuf = (char *)0;

/* input buffer */
static char *ibuf = (char *)0;

/* pointer in ibuf */
static char *bufptr = (char *)0;


/* init
 * the string has at least 1 char as in "< >"
 */
void html_lex_init (int dbg, char *str, int line)
{

  if (dbg || 0) {
    hl_flex_debug = 1;
    hlydebug = 1;
  } else {
    hl_flex_debug = 0;
    hlydebug = 0;
  }

  /* set lineno to where the node is defind */
  hllineno = line;

  /* extra space for \0\0 */
  buflen = strlen (str) + 2;

  ibuf = dp_calloc (1, buflen);

  if (ibuf == NULL) { return; }

  /* copy, skip first < */
  strcpy (ibuf, (str+1));

  /* wipe last > */
  ibuf[strlen(ibuf)-1] = 0;

  /* set where to start lexing */
  bufptr = ibuf;

  /* skip leading ws todo XXX is this always correct? */
  while (*bufptr)
  {
    if (*bufptr == ' ') {
    } else if (*bufptr == '\n') {
      hllineno++;
    } else if (*bufptr == '\r') {
    } else if (*bufptr == '\f') {
    } else if (*bufptr == '\t') {
    } else {
      break;
    }
    bufptr++;
  }

  skipws = 1;

  /* data buffer */
  dbuf = (char *) dp_calloc (1, buflen);

  if (dbuf == NULL) { return; }

  /* tag buffer */
  tbuf = (char *) dp_calloc (1, buflen);

  if (tbuf == NULL) { return; }

  /* lex buffer pending */
  pending = 0;

  /* clear buffer */
  clearit = 0;

  return;
}

/* de-init */
void html_lex_deinit (void)
{

  hl_flex_debug = 0;

  /* clear buffer */
  if (clearit || 1) {
    /* this may fix valgrind issue */
    yylex_destroy();
    /* yy_delete_buffer (buffer); */
    buffer = NULL;
    clearit = 0;
  }

  /* lex buffer pending */
  pending = 0;

  /* lex buffer length */
  buflen = 0;

  /* data buffer */
  if (dbuf) {
    dp_free (dbuf);
    dbuf = (char *)0;
  }

  /* tag buffer */
  if (tbuf) {
    dp_free (tbuf);
    tbuf = (char *)0;
  }

  /* input buffer */
  if( ibuf) {
    dp_free (ibuf);
    ibuf = (char *)0;
  }

  /* pointer in ibuf */
  bufptr = (char *)0;

  return;
}

/* lex one token */
int html_lex (void)
{
  int token = 0;
  int i = 0;
  int j = 0;
  char *p = NULL;

  for (i=0; i < 100 ; i++)
  {
    /* lex buffer pending */
    if (pending == 1) {
      /* lex from buffer */
      token = hllex ();
      /* at end-of-string in tbuf */
      if (token == EOF) {
        /* this may fix valgrind issue */
        yylex_destroy();
        /* yy_delete_buffer (buffer); */
        buffer = NULL;
        clearit = 0;
        pending = 0;
        continue;
      }
      /* at regular token */
      pending = 1;
      /* hlylval.string is set in the actions */
      return (token);
    } else {
      /* refill buffer */
      if (*bufptr == 0) {
        /* no data anymore */
        return (EOF);
      }

      if (skipws) {
      /* skip leading ws */
      while (*bufptr)
      {
        if (*bufptr == ' ') {
        } else if (*bufptr == '\n') {
          hllineno++;
        } else if (*bufptr == '\r') {
        } else if (*bufptr == '\f') {
        } else if (*bufptr == '\t') {
        } else {
          break;
       }
       bufptr++;
      }
      } else {
       skipws = 1;
      }

      if (*bufptr == 0) {
        /* no data anymore */
        return (EOF);
      }

      if (*bufptr == '<') {
        /* fill tag buffer */
        for (j=0; j < buflen ; j++)
        {
          tbuf[j] = 0;
        }
        j = 0;
        while (*bufptr)
        {
          if (*bufptr == '>') {
            tbuf[j] = *bufptr;
            j++;
            bufptr++;
            break;
          }
          tbuf[j] = *bufptr;
          j++;
          bufptr++;
        }
        if (j == 0) {
          return (EOF);
        }
        /* start lexing from buffer */
        buffer = yy_scan_string (tbuf);
        clearit = 1;
        /* lex tag buffer */
        pending = 1;
        continue;
      } else {
        /* fill data buffer */
        for (j=0; j < buflen ; j++)
        {
          dbuf[j] = 0;
        }
        j = 0;
        p = dbuf;
        while (*bufptr)
        {
          if (*bufptr == '<') {
            break;
          }
          /* update yylineno */
          if (*bufptr == '\n') {
            hllineno++;
          }
          p[j] = *bufptr;
          j++;
          bufptr++;
        }
        if (j == 0) {
          return (EOF);
        }
        pending = 0;
        /* return copy of the data area */
        hlylval.string = dp_uniqstr (dbuf);
        if (hlydebug) {
          printf ("token HL_DATA \"%s\"\n",hlylval.string);
        }
        return (HL_DATA);
      }
    }
  }

  /* shouldnothappen */
  printf ("%s(): huh?\n",__func__);

  return (EOF);
}

/* end */
