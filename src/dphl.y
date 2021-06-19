
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

/* Notes:
 * result of parsing html label can be "" at <> as input
 * or <<!-- comment -->> as input.
 * some chars in html labels need to be escaped, this is in GNU GCC:
 * + As pp_write_text_to_stream, but for GraphViz HTML-like strings.
 * +
 * +   Flush the formatted text of pretty-printer PP onto the attached stream,
 * +   escaping these characters
 * +     " & < >
 * +   using XML escape sequences.
 * +
 * +   http://www.graphviz.org/doc/info/lang.html#html states:
 * +      special XML escape sequences for ", &, <, and > may be necessary in
 * +      order to embed these characters in attribute values or raw text
 * +   This doesn't list "'" (which would normally be escaped in XML
 * +   as "&apos;" or in HTML as "&#39;");.
 * +
 * +   Experiments show that escaping "'" doesn't seem to be necessary.
 * +
 * +void
 * +pp_write_text_as_html_like_dot_to_stream (pretty_printer *pp)
 * +{
 * +  const char *text = pp_formatted_text (pp);
 * +  const char *p = text;
 * +  FILE *fp = pp_buffer (pp)->stream;
 * +
 * +  for (;*p; p++)
 * +    {
 * +      switch (*p)
 * +	{
 * +	case '"':
 * +	  fputs ("&quot;", fp);
 * +	  break;
 * +	case '&':
 * +	  fputs ("&amp;", fp);
 * +	  break;
 * +	case '<':
 * +	  fputs ("&lt;", fp);
 * +	  break;
 * +	case '>':
 * +	  fputs ("&gt;",fp);
 * +	  break;
 * +
 * +	default:
 * +	  fputc (*p, fp);
 * +	  break;
 * +	}
 * +    }
 * +
 * +  pp_clear_output_area (pp);
 * +}
 */

%{

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dphl.h"
#include "dpmem.h"

/* make sure extra debug code is available */
#define YYDEBUG 1

/*
 * When Using Bison-2.5.1
 * The variable error controls the verbosity of error messages.  The
 * use of the %error-verbose directive is deprecated in favor of
 * %define parse.error "verbose".
 */
#define YYERROR_VERBOSE 1


/* memory usage wrapping feature
#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif
*/

/* in lexer */
extern int hllineno;
extern char *hltext;
extern int html_lex (void);

/*
 * In GLR generated parser is:
 * YYLEX -- calling `yylex' with the right arguments.
 * #define YYLEX yylex (&yylval, &yylloc, pc)
 * YYSTYPE *lvalp, YYLTYPE *llocp, struct parser_control *pc
 */
static int hlylex (void)
{
	int tokencode = 0;

	tokencode = html_lex();

	if (tokencode == 0) {
		tokencode = EOF;
	}

	/* */
	return (tokencode);
}


static void yyerror (const char *msg)
{
  if (strlen(dp_errmsg)==0) {
    snprintf(dp_errmsg,256-1,"html %s(): %s at line %d yytext is %s'\n",__func__,msg,hllineno,hltext);
  }
  printf("html %s(): %s at line %d yytext is `%s'\n",__func__,msg,hllineno,hltext);
  fflush(stdout);
  fflush(stderr);
  return;
}

%}


/* prefix for internal names */
/* for older bison versions use this:
 * %name-prefix "hly"
 */
%define api.prefix {hly}

/* not a yacc parser and gcc-11 analyzer has a problem with bison yacc parsers. */
%glr-parser

/* where to start in the grammar */
%start begin

/* token name array in the parser code */
%token-table

/* write defines file */
%defines

/* output file */
%output "dphlparser.c"

/* add verbose debug */
%verbose

/* add debug */
%debug

/* u */
%union { char *string; }

%token <string>HL_DATA	"stringdata" /* string with data area */
%token HL_HTML		"<html" /* "<html" */
%token HL_C_HTML	"</html" /* "</html" */
%token HL_B		"<b" /* "<b" */
%token HL_C_B		"</b" /* "</b" */
%token HL_BR		"<br" /* "<br" */
%token HL_C_BR		"</br" /* "</br" */
%token HL_FONT		"<font" /* "<font" */
%token HL_C_FONT	"</font" /* "</font" */
%token HL_HR		"<hr" /* "<hr" */
%token HL_C_HR		"</hr" /* "</hr" */
%token HL_I		"<i" /* "<i" */
%token HL_C_I		"</i" /* "</i" */
%token HL_IMG		"<img" /* "<img" */
%token HL_C_IMG		"</img" /* "</img" */
%token HL_O		"<o" /* "<o" */
%token HL_C_O		"</o" /* "</o" */
%token HL_S		"<s" /* "<s" */
%token HL_C_S		"</s" /* "</s" */
%token HL_SUB		"<sub" /* "<sub" */
%token HL_C_SUB		"</sub" /* "</sub" */
%token HL_SUP		"<sup" /* "<sup" */
%token HL_C_SUP		"</sup" /* "</sup" */
%token HL_TABLE		"<table" /* "<table" */
%token HL_C_TABLE	"</table" /* "</table" */
%token HL_TD		"<td" /* "<td" */
%token HL_C_TD		"</td" /* "</td" */
%token HL_TR		"<tr" /* "<tr" */
%token HL_C_TR		"</tr" /* "</tr" */
%token HL_U		"<u" /* "<u" */
%token HL_C_U		"</u" /* "</u" */
%token HL_VR		"<vr" /* "<vr" */
%token HL_C_VR		"</vr" /* "</vr" */

%token HL_SC		"/>" /* "/>" */
%token HL_C		">" /* ">" */
%token HL_IS		"=" /* "=" */
%token <string>HL_QSTR	"string" /* "string" */
%token <string>HL_STR	"text" /* attribute variable name */

%token HL_ALIGN		"align" /* "align" */
%token HL_BALIGN	"balign" /* "balign" */
%token HL_BGCOLOR	"bgcolor" /* "bgcolor" */
%token HL_BORDER	"border" /* "border" */
%token HL_CELLBORDER	"cellborder" /* "cellborder" */
%token HL_CELLPADDING	"cellpadding" /* "cellpadding" */
%token HL_CELLSPACING	"cellspacing" /* "cellspacing" */
%token HL_COLOR		"color" /* "color" */
%token HL_COLUMNS	"columns" /* "columns" */
%token HL_COLSPAN	"colspan" /* "colspan" */
%token HL_FACE		"face" /* "face" */
%token HL_FIXEDSIZE	"fixedsize" /* "fixedsize" */
%token HL_GRADIENTANGLE	"gradientangle" /* "gradientangle" */
%token HL_HEIGHT	"height" /* "height" */
%token HL_HREF		"href" /* "href" */
%token HL_ID		"id" /* "id" */
%token HL_PORT		"port" /* "port" */
%token HL_POINTSIZE	"point-size" /* "point-size" */
%token HL_ROWS		"rows" /* "rows" */
%token HL_ROWSPAN	"rowspan" /* "rowspan" */
%token HL_SCALE		"scale" /* "scale" */
%token HL_SIDES		"sides" /* "sides" */
%token HL_SRC		"src" /* "src" */
%token HL_STYLE		"style" /* "style" */
%token HL_TARGET	"target" /* "target" */
%token HL_TITLE		"title" /* "title" */
%token HL_TOOLTIP	"tooltip" /* "tooltip" */
%token HL_VALIGN	"valign" /* "valign" */
%token HL_WIDTH		"width" /* "width" */


%%

/*
 * html label=< > is accepted by dot
 * or label=<<!-- comment --> >
 * the html label is a list of strings
 * or a list of tables with data but
 * not both at once.
 * a <table> has rows and cols with text like this:
 *
 *      col1  col2  col3  col4
 * row1 text1 text2 text3 text4
 * row2 text1 text2 text3 text4
 * row3 text1 text2 text3 text4
 */
begin:
	  htmlparser
	;

/* html string can be <...> or <html>...</html> */
htmlparser:
	  HL_HTML HL_C htmlparser2 HL_C_HTML HL_C
	| htmlparser2
	;

/* text items or table items */
htmlparser2:
	  items
	| fonttab2 { if (dphl_chk_err ()) { YYERROR; } }
	;

/* one or more text items */
items:
	  items item { if (dphl_chk_err ()) { YYERROR; } }
	| item { if (dphl_chk_err ()) { YYERROR; } }
	;

/* item can be a string
 * item can be a newline <br/> or <br></br>
 * item can be font with optional parameters
 * item can be italics <i> text
 * item can be bold <b> text
 * item can be underline <u> text
 * item can be overline <o> text
 * item can be subscript <sub> text
 * item can be superscript <sup> text
 * item can be strike-through <s> text
 */
item:
	  HL_DATA { dphl_data ($1); }
	| HL_BR { dphl_rbr(); } br_arg HL_SC { dphl_ebr (); }
	| HL_BR HL_C { dphl_rbr(); } HL_C_BR HL_C { dphl_ebr (); }
	| font items HL_C_FONT HL_C { dphl_efont (); }
	| italic items HL_C_I HL_C { dphl_ei (); }
	| bold items HL_C_B HL_C { dphl_eb (); }
	| underline items HL_C_U HL_C { dphl_eu (); }
	| overline items HL_C_O HL_C { dphl_eo (); }
	| HL_SUB HL_C { dphl_rsub(); } items HL_C_SUB HL_C { dphl_esub (); }
	| HL_SUP HL_C { dphl_rsup(); } items HL_C_SUP HL_C { dphl_esup (); }
	| HL_S HL_C { dphl_rs(); } items HL_C_S HL_C { dphl_es (); }
	;

/* at least one table statement.
 * <font ...></font> args can be empty.
 * tab is <table>...</table>
 * <table>...</table><table>...</table> is not allowed.
 * <td><table>...</table></td><td><table>...</table></td> is allowed.
 * table can be italics <i> text
 * table can be bold <b> text
 * table can be underline <u> text
 * table can be overline <o> text
 */
fonttab2:
	  tab
	| font tab HL_C_FONT HL_C { dphl_efont(); }
	| italic tab HL_C_I HL_C { dphl_ei (); }
	| bold tab HL_C_B HL_C { dphl_eb (); }
	| underline tab HL_C_U HL_C { dphl_eu (); }
	| overline tab HL_C_O HL_C { dphl_eo (); }
	;

font:
	  HL_FONT { dphl_rfont(); } font_arg HL_C
	;

italic:
	  HL_I HL_C { dphl_ri(); }
	;

overline:
	  HL_O HL_C { dphl_ro(); }
	;

bold:
	  HL_B HL_C { dphl_rb(); }
	;

underline:
	  HL_U HL_C { dphl_ru(); }
	;

/* optional data before and after a <table></table> tag */
tabe:
	  HL_DATA { dphl_tabledata ($1); }
	| /* empty */
	;

/* a <table> statement can have data around it in tabe which is ignored */
tab:
	  tabe HL_TABLE { dphl_rtable(); } table_arg HL_C rows HL_C_TABLE HL_C tabe { dphl_etable(); }
	;

/* row can have <hr/> or <hr></hr> */
rows:
	  row
	| rows row
	| rows HL_HR HL_SC { dphl_rhr(); } row
	| rows HL_HR HL_C HL_C_HR HL_C { dphl_rhr(); } row
	;

/* <tr> cell </tr> */
row:
	  HL_TR HL_C { dphl_rtr(); } cells HL_C_TR HL_C { dphl_etr (); }
	;

/* cell can have <vr/> or <vr></vr> */
cells:
	  cell
	| cells cell
	| cells HL_VR HL_SC { dphl_rvr(); } cell
	| cells HL_VR HL_C HL_C_VR HL_C { dphl_rvr(); }cell
	;

/* table data is a string, or more data, or image or nothing
 * <td> data </td> or <td></td>
 * <img src="foo"/> or <img src="foo"></img> or <img/> or <img></img>
 */
cell:
	  celltd td_arg HL_C htmlparser HL_C_TD HL_C { dphl_etd(0); }
	| celltd td_arg HL_C cellimg img_arg HL_SC HL_C_TD HL_C { dphl_eimg(); dphl_etd(1); }
	| celltd td_arg HL_C cellimg img_arg HL_C HL_C_IMG HL_C HL_C_TD HL_C { dphl_eimg(); dphl_etd(1); }
	| celltd td_arg HL_C HL_C_TD HL_C { dphl_etd(2); }
	;

cellimg:
	  HL_IMG { dphl_rimg(); }
	;

celltd:
	  HL_TD { dphl_rtd(); }
	;

/* for <table> wit optional args
 * int      align="center|left|right"
 * int      bgcolor="colorname"
 * int      border="int-value"
 * int      cellborder="int-value"
 * int      cellpadding="int-value"
 * int      cellspacing="int-value"
 * int      color="colorname"
 * char *)  columns="string" only "*" allowed
 * int      fixedsize="true|false"
 * int      gradientangle="int-value"
 * int      height="int-value"
 * (char *) href="string"
 * (char *) id="string"
 * (char *) port="string"
 * (char *) rows="string" only "*" allowed
 * (char *) sides="string"
 * (char *) style="string"
 * (char *) target="string"
 * (char *) title="string"
 * int      valign="middle|bottom|top"
 * int      width="int-value"
 */
table_arg:
	  table_arg table_1arg
	| /* empty */
	;

table_1arg:
	  HL_ALIGN HL_IS HL_QSTR { if (dphl_chk_align ($3,T_TABLE)) { YYERROR; } }
	| HL_BGCOLOR HL_IS HL_QSTR { if (dphl_chk_bgcolor ($3,T_TABLE)) { YYERROR; } }
	| HL_BORDER HL_IS HL_QSTR { if (dphl_chk_border ($3,T_TABLE)) { YYERROR; } }
	| HL_CELLBORDER HL_IS HL_QSTR { if (dphl_chk_cellborder ($3)) { YYERROR; } }
	| HL_CELLPADDING HL_IS HL_QSTR { if (dphl_chk_cellpadding ($3,T_TABLE)) { YYERROR; } }
	| HL_CELLSPACING HL_IS HL_QSTR { if (dphl_chk_cellspacing ($3,T_TABLE)) { YYERROR; } }
	| HL_COLOR HL_IS HL_QSTR { if (dphl_chk_color ($3,T_TABLE)) { YYERROR; } }
	| HL_COLUMNS HL_IS HL_QSTR { if (dphl_chk_columns ($3)) { YYERROR; } }
	| HL_FIXEDSIZE HL_IS HL_QSTR { if (dphl_chk_fixedsize ($3,T_TABLE)) { YYERROR; } }
	| HL_GRADIENTANGLE HL_IS HL_QSTR { if (dphl_chk_gradientangle ($3,T_TABLE)) { YYERROR; } }
	| HL_HEIGHT HL_IS HL_QSTR { if (dphl_chk_height ($3,T_TABLE)) { YYERROR; } }
	| HL_HREF HL_IS HL_QSTR { if (dphl_chk_href ($3,T_TABLE)) { YYERROR; } }
	| HL_ID HL_IS HL_QSTR { if (dphl_chk_id ($3,T_TABLE)) { YYERROR; } }
	| HL_PORT HL_IS HL_QSTR { if (dphl_chk_port ($3,T_TABLE)) { YYERROR; } }
	| HL_ROWS HL_IS HL_QSTR { if (dphl_chk_rows ($3)) { YYERROR; } }
	| HL_SIDES HL_IS HL_QSTR { if (dphl_chk_sides ($3,T_TABLE)) { YYERROR; } }
	| HL_STYLE HL_IS HL_QSTR { if (dphl_chk_style ($3,T_TABLE)) { YYERROR; } }
	| HL_TARGET HL_IS HL_QSTR { if (dphl_chk_target ($3,T_TABLE)) { YYERROR; } }
	| HL_TITLE HL_IS HL_QSTR { if (dphl_chk_title ($3,T_TABLE)) { YYERROR; } }
	| HL_TOOLTIP HL_IS HL_QSTR { if (dphl_chk_title ($3,T_TABLE)) { YYERROR; } }
	| HL_VALIGN HL_IS HL_QSTR { if (dphl_chk_valign ($3,T_TABLE)) { YYERROR; } }
	| HL_WIDTH HL_IS HL_QSTR { if (dphl_chk_width ($3,T_TABLE)) { YYERROR; } }
	| HL_STR HL_IS HL_QSTR { dphl_attr_huh ("<table>", $1, $3); }
	;

/* for <td> with optional args
 * int      align="center|left|right|text"
 * int      balign="center|left|right"
 * int      bgcolor="colorname"
 * int      border="int-value"
 * int      cellpadding="int-value"
 * int      cellspacing="int-value"
 * int      color="colorname"
 * int      colspan="int-value"
 * int      fixedsize="true|false"
 * int      gradientangle="int-value"
 * int      height="int-value"
 * (char *) href="string"
 * (char *) id="string"
 * (char *) port="string"
 * int      rowspan="int-value"
 * (char *) sides="string"
 * (char *) style="string"
 * (char *) target="string"
 * (char *) title="string"
 * int      valign="middle|bottom|top"
 * int      width="int-value"
 */
td_arg:
	  td_arg td_1arg
	| /* empty */
	;

td_1arg:
	  HL_ALIGN HL_IS HL_QSTR { if (dphl_chk_align ($3,T_TD)) { YYERROR; } }
	| HL_BALIGN HL_IS HL_QSTR { if (dphl_chk_balign ($3)) { YYERROR; } }
	| HL_BGCOLOR HL_IS HL_QSTR { if (dphl_chk_bgcolor ($3,T_TD)) { YYERROR; } }
	| HL_BORDER HL_IS HL_QSTR { if (dphl_chk_border ($3,T_TD)) { YYERROR; } }
	| HL_CELLPADDING HL_IS HL_QSTR { if (dphl_chk_cellpadding ($3,T_TD)) { YYERROR; } }
	| HL_CELLSPACING HL_IS HL_QSTR { if (dphl_chk_cellspacing ($3,T_TD)) { YYERROR; } }
	| HL_COLOR HL_IS HL_QSTR { if (dphl_chk_color ($3,T_TD)) { YYERROR; } }
	| HL_COLSPAN HL_IS HL_QSTR { if (dphl_chk_colspan ($3)) { YYERROR; } }
	| HL_FIXEDSIZE HL_IS HL_QSTR { if (dphl_chk_fixedsize ($3,T_TD)) { YYERROR; } }
	| HL_GRADIENTANGLE HL_IS HL_QSTR { if (dphl_chk_gradientangle ($3,T_TD)) { YYERROR; } }
	| HL_HEIGHT HL_IS HL_QSTR { if (dphl_chk_height ($3,T_TD)) { YYERROR; } }
	| HL_HREF HL_IS HL_QSTR { if (dphl_chk_href ($3,T_TD)) { YYERROR; } }
	| HL_ID HL_IS HL_QSTR { if (dphl_chk_id ($3,T_TD)) { YYERROR; } }
	| HL_PORT HL_IS HL_QSTR { if (dphl_chk_port ($3,T_TD)) { YYERROR; } }
	| HL_ROWSPAN HL_IS HL_QSTR { if (dphl_chk_rowspan ($3)) { YYERROR; } }
	| HL_SIDES HL_IS HL_QSTR { if (dphl_chk_sides ($3,T_TD)) { YYERROR; } }
	| HL_STYLE HL_IS HL_QSTR { if (dphl_chk_sides ($3,T_TD)) { YYERROR; } }
	| HL_TARGET HL_IS HL_QSTR { if (dphl_chk_target ($3,T_TD)) { YYERROR; } }
	| HL_TITLE HL_IS HL_QSTR { if (dphl_chk_title ($3,T_TD)) { YYERROR; } }
	| HL_TOOLTIP HL_IS HL_QSTR { if (dphl_chk_title ($3,T_TD)) { YYERROR; } }
	| HL_VALIGN HL_IS HL_QSTR { if (dphl_chk_valign ($3,T_TD)) { YYERROR; } }
	| HL_WIDTH HL_IS HL_QSTR { if (dphl_chk_width ($3,T_TD)) { YYERROR; } }
	| HL_STR HL_IS HL_QSTR { dphl_attr_huh ("<td>", $1, $3); }
	;

/* for <img> with optional args but src must be set
 * int      scale="false|true|width|height|both"
 * (char *) src="imagename"
 * <img src=""/> is skipped and ignored.
 */
img_arg:
	  img_arg img_1arg
	| /* empty */
	;

img_1arg:
	  HL_SCALE HL_IS HL_QSTR { if (dphl_chk_scale ($3)) { YYERROR; } }
	| HL_SRC HL_IS HL_QSTR { if (dphl_chk_src ($3)) { YYERROR; } }
	| HL_STR HL_IS HL_QSTR { dphl_attr_huh ("<img>", $1, $3); }
	;

/* for <br> with optional arg
 * int  align="center|left|right"
 */
br_arg:
	  br_arg br_1arg
	| /* empty */
	;

br_1arg:
	  HL_ALIGN HL_IS HL_QSTR { if (dphl_chk_align ($3,T_BR)) { YYERROR; } }
	| HL_STR HL_IS HL_QSTR { dphl_attr_huh ("<br>", $1, $3); }
	;

/* for <font> with optional args
 * int      color="colorname"
 * (char *) face="fontname"
 * int      point-size="int-number"
 */
font_arg:
	  font_arg font_1arg
	| /* empty */
	;

font_1arg:
	  HL_COLOR HL_IS HL_QSTR { if (dphl_chk_color ($3,T_FONT)) { YYERROR; } }
	| HL_FACE HL_IS HL_QSTR { if (dphl_chk_face ($3)) { YYERROR; } }
	| HL_POINTSIZE HL_IS HL_QSTR { if (dphl_chk_pointsize ($3)) { YYERROR; } }
	| HL_STR HL_IS HL_QSTR { dphl_attr_huh ("<font>", $1, $3); }
	;

%%

/* end */
