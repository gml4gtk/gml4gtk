
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
/* lex the vcg data generated with gcc -fcallgraph-info option which is a subset of vcg language */

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#include "splay-tree.h"
#include "vcg.yy.h"
#include "vcg.tab.h"
#include "vcgus.h"

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

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
  if ( (result = fread( (char*)buf, sizeof(char), max_size, yyin)) < 0) \
		YY_FATAL_ERROR( "fread() in vcg.l flex scanner failed");

static char *p = NULL;
static char *q = NULL;
static char *tmpp = NULL;

char *vcglaststring = NULL;

%}

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
				  if (vcgleng == 2) {
				    /* string is "" */
				    vcglaststring = vcg_uniqstr ("");
				    return (VCG_STRING);
				  }
				  /* copy and filter the text, and clear last " */
				  vcgtext[vcgleng-1] = 0;
				  tmpp = (char *) calloc (1, (vcgleng+1));
				  p = vcgtext;
				  p++; /* skip first " */
				  q = tmpp;
				  while (*p)
				  {
				    if (*p =='\\') {
				      if(*(p+1) == 0) {
				        *q = '\\';
				        q++;
				        p++; /* "\" as last char */
				      } else if (*(p+1) =='\n') {
				        p = p + 2; /* skip "\\n" sequence */
				      } else if (*(p+1) == 'n') {
				        *q = '\n'; /* */
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '"') {
				        *q = '"'; /* */
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '\\') {
				        *q = '\\';
				        q++;
				        p = p + 2;
				      } else {
				        *q = *p; /* copy other esc sequences */
				        p++;
				        q++;
				      }
				    } else {
				      *q = *p; /* copy regular chars */
				      p++;
				      q++;
				    }
				  }
				  p = vcg_uniqstr (tmpp);
				  vcglaststring = p;
				  free (tmpp);
				  tmpp = NULL;
				  p = NULL;
				  q = NULL;
				  return (VCG_STRING);
				}

.				{ return ((int)yytext[0]); }

%%

/* */
void vcg_lex_init (FILE *f, int debugflag)
{
  vcglineno=1;
  vcgin = f;
  /* activate debug in lexer */
  vcg_flex_debug = debugflag;
  /* activate debug in vcg parser */
  vcgdebug = debugflag;
  return;
}

/* */
void vcg_lex_clear (void)
{
  vcglineno=1;

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

/* end */
