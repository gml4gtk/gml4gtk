/* gcc-10 -fanalyzer
vcg.flex.c:4433:1: warning: leak of ‘<unknown>’ [CWE-401] [-Wanalyzer-malloc-leak]
vcg.flex.c:5003:9: warning: leak of ‘<unknown>’ [CWE-401] [-Wanalyzer-malloc-leak]
vcg.flex.c:5003:9: warning: leak of ‘<unknown>’ [CWE-401] [-Wanalyzer-malloc-leak]
*/

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

/* lex the vcg data generated with gcc -fcallgraph-info option which is a subset of vcg language */

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#include "splay-tree.h"
#include "vcg.yy.h"
#include "vcg.tab.h"
#include "vcgus.h"
#include "dpmem.h"

/* use GNU GCC compiler builtin strlen */
#undef YY_NEED_STRLEN

/* increase read buffer */
#undef YY_READ_BUF_SIZE
/* #define YY_READ_BUF_SIZE (16*1024) */
/* fread() with 128kb at once is fastest on Linux */
#define YY_READ_BUF_SIZE (128*1024)

/* Size of default input buffer. Do not tune. */
#undef YY_BUF_SIZE
#define YY_BUF_SIZE 16384

/* at malloc error there will be a memory leak but it does also
 * #define YY_FATAL_ERROR(msg) exit(0)
 */

/* char *p is used in flex coe */
static char *ppointer = NULL;
static char *qpointer = NULL;
static char *tmpp = NULL;

char *vcglaststring = NULL;

static gzFile vcgzin = (gzFile)0;

/* gzfread cannot be used because of older zlib in the dll */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) do { \
	if ( (result = gzread(vcgzin, (char*)buf, (sizeof(char) * max_size) )) == 0) { \
		int estatus = 0; \
		const char *es = gzerror (vcgzin, &estatus); \
		if (estatus == Z_BUF_ERROR) { \
			YY_FATAL_ERROR( "gzread() in vcg.l flex scanner failed"); \
		} else { \
			if (estatus) { \
				printf ("%s(): zlib error status %d %s in vcg.l\n",__func__,(int)estatus,es); \
			} \
		} \
	} } while (0);

/* own yyalloc
 * void *yyalloc (size_t n) { return(calloc(1,n)); }
 * void yyfree (void *ptr) { if (ptr) { free (ptr); } return; }
 * void *yyrealloc (void *ptr, size_t n) { return (realloc(ptr,n)); }
 */

%}

	/* use own yyalloc
	 * %option noyyalloc
	 * %option noyyrealloc
	 * %option noyyfree
	 */

%option noinput
%option nounput
%option noyywrap
%option 8bit
%option never-interactive
%option yylineno
%option noread

ISTR	[^\\\"]|\\.|\\\n
STR	\"({ISTR}*)\"

CCS	\/\*[^\*]*\*+([^\*\/][^\*]*\*+)*\/
CCS0	\/\*
CCS1	\*\/
CCE	\/\/[^\n]*

%%

{CCS}				{ /* c-comment style */ /* lexer does update yylineno */ }
{CCS0}				{ /* start of c comment but no end of c comment */ }
{CCS1} 				{ /* end of c comment but no start of c comment */ }
{CCE}				{ /* c++ comment style */ /* lexer does update yylineno */ }

[\f ]+				{ /* skip form feed chars and spaces */ }
[\t]				{ /* skip tabs */ }
[\n]				{ /* skip new line */ /* lexer does update yylineno */ }
[\r]				{ /* skip carriage return */ }

":"				{ return (VCG_COLON); }
"{"				{ return (VCG_BO); }
"}"				{ return (VCG_BC); }

"graph"				{ return (VCG_GRAPH); }
"edge"				{ return (VCG_EDGE); }
"ellipse"			{ return (VCG_ELLIPSE); }
"label"				{ return (VCG_LABEL); }
"node"				{ return (VCG_NODE); }
"shape"				{ return (VCG_SHAPE); }
"sourcename"			{ return (VCG_SOURCENAME); }
"targetname"			{ return (VCG_TARGETNAME); }
"title"				{ return (VCG_TITLE); }

{STR}				{
				  if (yyleng == 2) {
				    /* string is "" */
				    vcglaststring = vcg_uniqstr ("");
				    return (VCG_STRING);
				  }
				  /* copy and filter the text, and clear last " */
				  yytext[yyleng-1] = 0;
				  /* one byte to much but that is later on corrected */
				  tmpp = (char *) dp_calloc (1, (yyleng+1));
				  ppointer = yytext;
				  ppointer++; /* skip first " */
				  qpointer = tmpp;
				  while (*ppointer)
				  {
				    if ((*ppointer) =='\\') {
				      if((*(ppointer+1)) == 0) {
				        *qpointer = '\\';
				        qpointer++;
				        ppointer++; /* "\" as last char */
				      } else if ((*(ppointer+1)) =='\n') {
				        ppointer = ppointer + 2; /* skip "\\n" sequence */
				      } else if ((*(ppointer+1)) == 'n') {
				        *qpointer = '\n'; /* */
				        qpointer++;
				        ppointer = ppointer + 2;
				      } else if ((*(ppointer+1)) == '"') {
				        *qpointer = '"'; /* */
				        qpointer++;
				        ppointer = ppointer + 2;
				      } else if ((*(ppointer+1)) == '\\') {
				        *qpointer = '\\';
				        qpointer++;
				        ppointer = ppointer + 2;
				      } else {
				        *qpointer = *ppointer; /* copy other esc sequences */
				        ppointer++;
				        qpointer++;
				      }
				    } else {
				      *qpointer = *ppointer; /* copy regular chars */
				      ppointer++;
				      qpointer++;
				    }
				  }
				  /* do a strdup() */
				  ppointer = vcg_uniqstr (tmpp);
				  vcglaststring = ppointer;
				  tmpp = dp_free (tmpp);
				  ppointer = NULL;
				  qpointer = NULL;
				  if (ppointer) {}
				  if (qpointer) {}
				  return (VCG_STRING);
				}

.				{ return ((int)yytext[0]); }

%%

/* */
void vcg_lex_init (gzFile f, int debugflag)
{
  vcglineno=1;
  yyin = (FILE *)0;
  vcgzin = (gzFile)f;
  /* activate debug in lexer */
  yy_flex_debug = debugflag;
  /* activate debug in vcg parser */
  vcgdebug = debugflag;
  return;
}

/* */
void vcg_lex_clear (void)
{
  vcglineno=1;
  yylex_destroy();
  yy_flex_debug = 0;
  vcgzin = (gzFile)0;
  yyin = (FILE *)0;
  return;
}

void vcg_yydebug (int debugflag)
{

  /* activate debug in lexer */
  vcg_flex_debug = debugflag;
  /* activate debug in vcg parser */
  vcgdebug = debugflag;

  return;
}

/* end. */
