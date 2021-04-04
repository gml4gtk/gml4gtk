
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
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "lex.yy.h"
#include "dpmem.h"

#define YY_DEBUG 1

#define YYERROR_VERBOSE 1

/* memory usage wrapping feature */
#ifndef YYFREE
# define YYFREE dp_free
#endif
#ifndef YYMALLOC
# define YYMALLOC dp_malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC dp_realloc
#endif

/* utf8 code at start if 1 */
static int utfseen = 0;

/* graph is strict if 1 */
static int isstrict = 0;

extern int yylex (void);

static void yyerror (const char *msg)
{
  if (strlen(dp_errmsg)==0) {
    snprintf(dp_errmsg,256-1,"dot %s(): %s at line %d yytext is %s'\n",__func__,msg,yylineno,yytext);
  }
  printf("dot %s(): %s at line %d yytext is `%s'\n",__func__,msg,yylineno,yytext);
  fflush(stdout);
  fflush(stderr);
  return;
}

%}

	/* this is a glr parser. not a yacc lalr parser */
%glr-parser

%union { char *string; struct dpepoint *dp; }

%debug

%defines

%start startdot

%verbose

%token TOKEN_BRACEOPEN /* { */
%token TOKEN_BRACECLOSE /* } */
%token TOKEN_PLUS /* + */
%token TOKEN_COMMA /* , */
%token TOKEN_COLON /* : */
%token TOKEN_IS /* = */
%token TOKEN_SC /* ; */
%token TOKEN_BRACKETOPEN /* [ */
%token TOKEN_BRACKETCLOSE /* ] */
%token TOKEN_UTF8BOM
%token TOKEN_STRICT
%token TOKEN_GRAPH
%token TOKEN_SUBGRAPH
%token TOKEN_DIGRAPH
%token TOKEN_NODE
%token TOKEN_EDGE

%token <string> TOKEN_TEXT
%token <string> TOKEN_NUM
%token <string> TOKEN_QTEXT
%token <string> TOKEN_HTEXT
%token <string> TOKEN_EOP

%type <string> text
%type <string> ctext
%type <string> thename
%type <string> thetype
%type <string> nidid
%type <dp> nid
%type <dp> sstatement

%left TOKEN_SUBGRAPH
%left TOKEN_BRACEOPEN


%%

startdot:
	  utf thetype thename { dp_sg ($2,$3); } TOKEN_BRACEOPEN statements TOKEN_BRACECLOSE { dp_eg (); }
	| error { dp_eg (); }
	| /* empty */ { dp_eg (); }
	;

utf:
	  TOKEN_UTF8BOM { utfseen = 1; }
	| /* empty */ { utfseen = 0; }
	;

thetype:
	  TOKEN_STRICT TOKEN_GRAPH { isstrict = 1; $$ = "--"; }
	| TOKEN_GRAPH { isstrict = 0; $$ = "--"; }
	| TOKEN_STRICT TOKEN_DIGRAPH { isstrict = 1; $$ = "->"; }
	| TOKEN_DIGRAPH { isstrict = 0; $$ = "->"; }
	;

thename:
	  text { $$ = $1; }
	| /* empty */ { $$ = NULL; }
	;

/* example: "string" or "s"+"t"+"r"+"ing" */
ctext:
	  TOKEN_QTEXT { $$ = $1; }
	| ctext TOKEN_PLUS TOKEN_QTEXT { $$ = dp_ccat ($1,$3); }
	;

text:
	  TOKEN_TEXT { $$ = $1; }
	| TOKEN_NUM { $$ = $1; }
	| TOKEN_HTEXT { $$ = $1; }
	| ctext { $$ = $1; }
	;

statements:
	  statements statement
	| statement
	;

/* the semicolon or comma after statement is optional */
/* parse error if support routines have set a message */
statement:
	  statement2 { if (dp_chkerr()) { YYERROR; /* YYABORT; does not work as expected */ } }
	| statement2 TOKEN_SC  { if (dp_chkerr()) { YYERROR; /* YYABORT; does not work as expected */ } }
	| statement2 TOKEN_COMMA  { if (dp_chkerr()) { YYERROR; /* YYABORT; does not work as expected */ } }
	;

/* node, edge, attribute, subgraph statement
 * dot allows attributes after a subgraph statement
 * example: subgraph "huh" { ... } [ ... ]
 * but not when in a edge, example: {...}[...] -> ...
 * bug-or-feature?
 */
statement2:
	  nstatement
	| estatement
	| astatement
	| sstatement { dp_atype_sgraph(); } oattrib { dp_atype_graph (); }
	;

nstatement:
	  nidid { dp_mknode0 ($1); dp_atype_node(); } oattrib { dp_atype_graph (); }
	;

/*
 * only for node definition and port+compass is ignored
 * nodeid
 * nodeid:port
 * nodeid:compass
 * nodeid:port:compass (port as in record/html label)
 */
nidid:
	  text { $$=$1; }
	| text TOKEN_COLON text { $$=$1; /* ignore $3 */ }
	| text TOKEN_COLON text TOKEN_COLON text { $$=$1; /* ignore $3 $5 */ }
	;

/*
 * nodeid
 * nodeid:port
 * nodeid:compass
 * nodeid:port:compass (port as in record/html label)
 */
nid:
	  text { $$ = dp_mknid ($1,NULL,NULL); }
	| text TOKEN_COLON text { $$ = dp_mknid ($1,$3,NULL); }
	| text TOKEN_COLON text TOKEN_COLON text { $$ = dp_mknid ($1,$3,$5); }
	;

sattr:
	  text TOKEN_IS text  { dp_aset ($1,$3); }
	;

sattr2:
	  sattr
	| text { dp_aset ($1,"true"); }
	;

iattr:
	  sattr2 iattr
	| sattr2 TOKEN_COMMA iattr
	| sattr2 TOKEN_SC iattr
	| /* empty */
	;

tattr:
	  TOKEN_BRACKETOPEN iattr TOKEN_BRACKETCLOSE
	;

oattrib:
	  tattr oattrib
	| /* empty */
	;

estatement:
	  nid { dp_starte1 ($1); } erhs { dp_newe (); } oattrib { dp_ende (); dp_clrep(); }
	| sstatement { dp_starte2 ($1); } erhs { dp_newe (); } oattrib { dp_ende (); dp_clrep(); }
	;

/* right hand */
erhs:
	  TOKEN_EOP nid { dp_cke ($1); dp_ine ($2); }
	| TOKEN_EOP nid { dp_cke ($1); dp_ine ($2); } erhs
	| TOKEN_EOP sstatement { dp_cke ($1); dp_ine ($2); }
	| TOKEN_EOP sstatement { dp_cke ($1); dp_ine ($2); } erhs
	;


astatement:
	  atype tattr { dp_atype_graph (); }
	| aset { dp_atype_graph (); }
	;

atype:
	  TOKEN_GRAPH { dp_atype_graphdef (); }
	| TOKEN_NODE { dp_atype_nodedef (); }
	| TOKEN_EDGE { dp_atype_edgedef (); }
	;

aset:
	  text TOKEN_IS text { dp_aset ($1,$3); }
	;

sstatement:
	  shead TOKEN_BRACEOPEN statements TOKEN_BRACECLOSE %prec TOKEN_BRACEOPEN { $$=dp_endss (); }
	| TOKEN_BRACEOPEN { dp_namedsubg (NULL,DP_SG_CO); } statements TOKEN_BRACECLOSE { $$=dp_endss (); }
	;

/* allow subgraph foo {} or subgraph {} */
shead:
	  TOKEN_SUBGRAPH text { dp_namedsubg ($2,DP_SG_NM); }
	| TOKEN_SUBGRAPH { dp_namedsubg (NULL,DP_SG_NN); }
	;

%%

/* end. */
