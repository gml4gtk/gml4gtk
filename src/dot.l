
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

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#include "splay-tree.h"
#include "lex.yy.h"
#include "dot.tab.h"
#include "dp.h"
#include "dpus.h"
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

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
  if ( (result = fread( (char*)buf, sizeof(char), max_size, yyin)) < 0) \
		YY_FATAL_ERROR( "fread() in dot.l flex scanner failed");


static char *tmpp = NULL;
static char *p = NULL;
static char *q = NULL;
static int htmlnest = 0;
static void dp_check_c_comment (char *s);


/* own yyalloc
 * void *yyalloc (size_t n) { return(calloc(1,n)); }
 * void yyfree (void *ptr) { if (ptr) { free (ptr); } return; }
 * void *yyrealloc (void *ptr, size_t n) { return (realloc(ptr,n)); }
*/

%}

%x htmlstr

/* empty string "" with length 0 is troublesome in dot: */
/* digraph {} has no name */
/* digraph "" {} is digraph  {} has no name but a space is set */
/* digraph " " {} is digraph with string " " */
/* node label="" is two chars in output drawing */
/* allow in fnum1,2,3 also numbers as "23.1" or "23." and ".23" */

	/* use own yyalloc
	 * %option noyyalloc
	 * %option noyyfree
	 * %option noyyrealloc
	*/

%option noinput
%option nounput
%option noyywrap
%option 8bit
%option never-interactive
%option yylineno
%option noread
%option debug

ISTR	[^\\\"]|\\.|\\\n
STR	\"({ISTR}*)\"

CCS	\/\*[^\*]*\*+([^\*\/][^\*]*\*+)*\/
CCE	\/\/[^\n]*
CCS1	\*\/

ALPHA	[A-Za-z]
DIGIT	[0-9]
ID	([_]|{ALPHA})([_]|{ALPHA}|{DIGIT})*
INUM	[-+]?{DIGIT}+
FNUM1	[-+]?{DIGIT}*\.{DIGIT}+
FNUM2	[-+]?{DIGIT}*\.
FNUM3	[-+]?\.{DIGIT}+
NUM	{INUM}|{FNUM1}|{FNUM2}|{FNUM3}

%%

{CCS}				{ /* c-comment style */ /* lexer does update yylineno */ dp_check_c_comment(yytext+1); }
{CCS1}				{ /* end of c comment but no start of c comment shouldnothappen */ printf("%s(): end of c-comment without start of c-comment \"*\\\" at line %d skipped\n",__func__,yylineno); }
{CCE}				{ /* c++ comment style */ /* lexer does update yylineno */ }

"#".*				{ /* dot comment line */ }
"\xef\xbb\xbf"			{ /* this is dot specific */ return (TOKEN_UTF8BOM); }
[\f ]+				{ /* skip form feed chars and spaces */ }
[\t]				{ /* skip tabs */ }
[\n]				{ /* skip new line */ /* lexer does update yylineno */ }
[\r]				{ /* skip carriage return */ }

"@"				{ return (EOF); }
"+"				{ return (TOKEN_PLUS); }
","				{ return (TOKEN_COMMA); }
":"				{ return (TOKEN_COLON); }
";"				{ return (TOKEN_SC); }
"="				{ return (TOKEN_IS); }
"["				{ return (TOKEN_BRACKETOPEN); }
"]"				{ return (TOKEN_BRACKETCLOSE); }
"{"				{ return (TOKEN_BRACEOPEN); }
"}"				{ return (TOKEN_BRACECLOSE); }
"--"				{ yylval.string = "--"; return (TOKEN_EOP); }
"->"				{ yylval.string = "->"; return (TOKEN_EOP); }

[Ee][Dd][Gg][Ee]		{ return(TOKEN_EDGE); }
[Nn][Oo][Dd][Ee]		{ return(TOKEN_NODE); }
[Dd][Ii][Gg][Rr][Aa][Pp][Hh]	{ return(TOKEN_DIGRAPH); }
[Gg][Rr][Aa][Pp][Hh]		{ return(TOKEN_GRAPH); }
[Ss][Uu][Bb][Gg][Rr][Aa][Pp][Hh]	{ return(TOKEN_SUBGRAPH); }
[Ss][Tt][Rr][Ii][Cc][Tt]	{ return(TOKEN_STRICT); }

{STR}				{
				  if(yyleng == 2) {
				    /* string is "" */
				    p = dp_uniqstr ("");
				    yylval.string = p;
				    return (TOKEN_QTEXT);
				  }
				  /* copy and filter the text, and clear last " */
				  yytext[yyleng-1] = 0;
				  tmpp = (char *) dp_calloc (1, yyleng);
				  p = yytext;
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
				      } else if (*(p+1) == ' ') {
				        *q = ' '; /* "\ " is " " special in html label */
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '|') {
				        *q = '\\'; /* special in record label */
				        q++;
				        *q = '|';
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '{') {
				        *q = '\\'; /* special in record label */
				        q++;
				        *q = '{';
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '}') {
				        *q = '\\'; /* special in record label */
				        q++;
				        *q = '}';
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '\\') {
				        /* \\ is translated into a single \ */
				        *q = '\\';
				        q++;
				        p = p + 2;
				      } else if (*(p+1) == '"') {
				        /* \" becomes " */
				        *q = '"';
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
				  p = dp_uniqstr (tmpp);
				  yylval.string = p;
				  dp_free (tmpp);
				  tmpp = NULL;
				  p = NULL;
				  q = NULL;
				  return (TOKEN_QTEXT);
				}

{ID}				{
				  p = dp_uniqstr (yytext);
				  yylval.string = p;
				  return (TOKEN_TEXT);
				}

{NUM}				{
				  p = dp_uniqstr (yytext);
				  yylval.string = p;
				  return (TOKEN_NUM);
				}

	/* html label, but if it is <> return "" */
[<]				{ BEGIN(htmlstr); htmlnest = 1; yylval.string = "<"; }
<htmlstr>[>]			{ htmlnest--; if(htmlnest) { yylval.string = dp_ccat(yylval.string,yytext); } else { yylval.string = dp_ccat(yylval.string,">"); BEGIN(INITIAL); if (strlen(yylval.string) == 2) { yylval.string = ""; } return (TOKEN_HTEXT); } }
<htmlstr>[<]			{ htmlnest++; yylval.string = dp_ccat(yylval.string,yytext); }
<htmlstr>[\\][<]		{ yylval.string = dp_ccat(yylval.string,"&lt;"); }
<htmlstr>[\\][>]		{ yylval.string = dp_ccat(yylval.string,"&gt;"); }
<htmlstr>[\\][\n]		{ /* yylineno++ is update by lexer code */ ; }
<htmlstr>([^><\\]*|[\\].)	{ yylval.string = dp_ccat(yylval.string,yytext); }


.				{ return ((int)yytext[0]); }

%%

/* */
void dp_lex_init (FILE *f, int debugflag)
{
  yylineno=1;
  yyin = f;
  /* activate debug in lexer */
  yy_flex_debug = debugflag;
  /* activate debug in glr parser */
  yydebug = debugflag;
  htmlnest = 0;
  return;
}

/* */
static void dp_lex_clear (void)
{
  if (tmpp) {
    dp_free (tmpp);
    tmpp = NULL;
  }
  p = NULL;
  q = NULL;
  htmlnest = 0;

  return;
}

void dp_lex_deinit (void)
{
  yy_flex_debug = 0;
  dp_lex_clear ();
  yylex_destroy ();
  return;
}

void dp_yydebug (int debugflag)
{

  /* activate debug in lexer */
  yy_flex_debug = debugflag;

  /* activate debug in glr parser */
  yydebug = debugflag;

  return;
}

/* check for comment inside comment */
static void dp_check_c_comment (char *str)
{
  char *ptr0 = NULL;
  char *ptr = NULL;
  if(str == NULL) {
    return;
  }
  if(strlen(str) < 1) {
    return;
  }
  ptr=str;
  while (*ptr) {
    ptr0 = strchr (ptr, '/');
    if (ptr0) {
      if ((*(ptr0+1)) == '*') {
        printf ("%s(): start of c-comment \"/*\" inside c-comment at line %d\n",__func__,yylineno);
        ptr0++;
      } else if ((*(ptr0+1)) == '/') {
        printf ("%s(): start of c++-comment \"//\" inside c-comment at line %d\n",__func__,yylineno);
        ptr0++;
      } else {
        /* nop */
      }
      ptr=ptr0;
    }
    ptr++;
  }
  return;
}

/* end */
