/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0

/* Substitute the type names.  */
#define YYSTYPE HLYSTYPE
/* Substitute the variable and function names.  */
#define yyparse hlyparse
#define yylex   hlylex
#define yyerror hlyerror
#define yydebug hlydebug
#define yylval  hlylval
#define yychar  hlychar
#define yynerrs hlynerrs

/* First part of user prologue.  */
#line 75 "dphl.y"		/* glr.c:237  */

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
extern int html_lex(void);

/*
 * In GLR generated parser is:
 * YYLEX -- calling `yylex' with the right arguments.
 * #define YYLEX yylex (&yylval, &yylloc, pc)
 * YYSTYPE *lvalp, YYLTYPE *llocp, struct parser_control *pc
 */
static int hlylex(void)
{
	int tokencode = 0;

	tokencode = html_lex();

	if (tokencode == 0) {
		tokencode = EOF;
	}

	/* */
	return (tokencode);
}

static void yyerror(const char *msg)
{
	if (strlen(dp_errmsg) == 0) {
		snprintf(dp_errmsg, 256 - 1, "html %s(): %s at line %d yytext is %s'\n", __func__, msg, hllineno, hltext);
	}
	printf("html %s(): %s at line %d yytext is `%s'\n", __func__, msg, hllineno, hltext);
	fflush(stdout);
	fflush(stderr);
	return;
}

#line 142 "dphlparser.c"	/* glr.c:237  */

#ifndef YY_NULLPTR
#if defined __cplusplus
#if 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#else
#define YY_NULLPTR ((void*)0)
#endif
#endif

#include "dphlparser.h"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
#undef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#else
#define YYERROR_VERBOSE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h>		/* INFRINGES ON USER NAME SPACE */
#define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#endif
#endif
#ifndef YY_
#define YY_(Msgid) Msgid
#endif
#endif

#ifndef YYFREE
#define YYFREE free
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#endif
#ifndef YYREALLOC
#define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
typedef bool yybool;
#define yytrue true
#define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
typedef unsigned char yybool;
#define yytrue 1
#define yyfalse 0
#endif

#ifndef YYSETJMP
#include <setjmp.h>
#define YYJMP_BUF jmp_buf
#define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
#define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YYASSERT (0);                                \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE
#if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#define YY_ATTRIBUTE(Spec) __attribute__(Spec)
#else
#define YY_ATTRIBUTE(Spec)	/* empty */
#endif
#endif

#ifndef YY_ATTRIBUTE_PURE
#define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* The _Noreturn keyword of C11.  */
#if ! defined _Noreturn
#if defined __cplusplus && 201103L <= __cplusplus
#define _Noreturn [[noreturn]]
#elif !(defined __STDC_VERSION__ && 201112 <= __STDC_VERSION__)
#if (3 <= __GNUC__ || (__GNUC__ == 2 && 8 <= __GNUC_MINOR__) \
       || 0x5110 <= __SUNPRO_C)
#define _Noreturn __attribute__ ((__noreturn__))
#elif defined _MSC_VER && 1200 <= _MSC_VER
#define _Noreturn __declspec (noreturn)
#else
#define _Noreturn
#endif
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
#define YYUSE(E) ((void) (E))
#else
#define YYUSE(E)		/* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
#define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
#define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
#define YY_INITIAL_VALUE(Value)	/* Nothing. */
#endif

#ifndef YYASSERT
#define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 10
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token number (for yychar).  */
#define YYMAXUTOK   324
/* YYUNDEFTOK -- Symbol number (for yytoken) that denotes an unknown
   token.  */
#define YYUNDEFTOK  2

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const unsigned char yytranslate[] = {
	0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
	45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
	65, 66, 67, 68, 69
};

#if HLYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] = {
	0, 270, 270, 275, 276, 281, 282, 287, 288, 303,
	304, 304, 305, 305, 306, 307, 308, 309, 310, 311,
	311, 312, 312, 313, 313, 327, 328, 329, 330, 331,
	332, 336, 336, 340, 344, 348, 352, 357, 358, 363,
	363, 368, 369, 370, 370, 371, 371, 376, 376, 381,
	382, 383, 383, 384, 384, 392, 393, 394, 395, 399,
	403, 430, 431, 435, 436, 437, 438, 439, 440, 441,
	442, 443, 444, 445, 446, 447, 448, 449, 450, 451,
	452, 453, 454, 455, 456, 457, 484, 485, 489, 490,
	491, 492, 493, 494, 495, 496, 497, 498, 499, 500,
	501, 502, 503, 504, 505, 506, 507, 508, 509, 510,
	511, 520, 521, 525, 526, 527, 534, 535, 539, 540,
	549, 550, 554, 555, 556, 557
};
#endif

#if HLYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
	"$end", "error", "$undefined", "\"stringdata\"", "\"<html\"",
	"\"</html\"", "\"<b\"", "\"</b\"", "\"<br\"", "\"</br\"", "\"<font\"",
	"\"</font\"", "\"<hr\"", "\"</hr\"", "\"<i\"", "\"</i\"", "\"<img\"",
	"\"</img\"", "\"<o\"", "\"</o\"", "\"<s\"", "\"</s\"", "\"<sub\"",
	"\"</sub\"", "\"<sup\"", "\"</sup\"", "\"<table\"", "\"</table\"",
	"\"<td\"", "\"</td\"", "\"<tr\"", "\"</tr\"", "\"<u\"", "\"</u\"",
	"\"<vr\"", "\"</vr\"", "\"/>\"", "\">\"", "\"=\"", "\"string\"",
	"\"text\"", "\"align\"", "\"balign\"", "\"bgcolor\"", "\"border\"",
	"\"cellborder\"", "\"cellpadding\"", "\"cellspacing\"", "\"color\"",
	"\"columns\"", "\"colspan\"", "\"face\"", "\"fixedsize\"",
	"\"gradientangle\"", "\"height\"", "\"href\"", "\"id\"", "\"port\"",
	"\"point-size\"", "\"rows\"", "\"rowspan\"", "\"scale\"", "\"sides\"",
	"\"src\"", "\"style\"", "\"target\"", "\"title\"", "\"tooltip\"",
	"\"valign\"", "\"width\"", "$accept", "begin", "htmlparser",
	"htmlparser2", "items", "item", "$@1", "$@2", "$@3", "$@4", "$@5",
	"fonttab2", "font", "$@6", "italic", "overline", "bold", "underline",
	"tabe", "tab", "$@7", "rows", "$@8", "$@9", "row", "$@10", "cells",
	"$@11", "$@12", "cell", "cellimg", "celltd", "table_arg", "table_1arg",
	"td_arg", "td_1arg", "img_arg", "img_1arg", "br_arg", "br_1arg",
	"font_arg", "font_1arg", YY_NULLPTR
};
#endif

#define YYPACT_NINF -198
#define YYTABLE_NINF -38

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short yypact[] = {
	171, -18, -20, -2, 6, -198, 8, 9, 11, 12,
	17, 18, 37, -198, -198, 326, -198, -198, 349, 349,
	349, 349, 349, 33, -198, 349, -198, -198, -198, -198,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, 326,
	326, 326, 326, 326, 191, 52, 221, 54, 241, 46,
	261, 60, 50, 38, -198, 68, 66, 21, 132, 326,
	326, 326, 39, 43, 49, 57, 58, 65, 70, 78,
	79, 85, -198, 89, 91, -198, 97, 98, -198, -198,
	102, 111, 113, 117, -198, 274, 294, 317, -198, -198,
	-198, -198, -198, -198, -198, -198, -198, -198, 44, -198,
	-198, 118, 120, 122, 124, 128, 131, 134, 141, 145,
	135, 146, 148, 149, 150, 154, 158, 160, 162, 166,
	168, 169, 170, 172, 174, 176, 178, 179, 187, 188,
	190, 192, 194, 195, -198, -198, -198, -198, -198, -198,
	-198, -198, -198, -198, 197, 126, -198, 198, 199, 201,
	203, 207, 209, 211, 213, 215, 217, 218, 219, 223,
	227, 231, 233, 235, 237, 239, 247, 248, 250, 251,
	-198, -16, 254, -198, -198, -198, -198, -198, -198, -198,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, -198,
	-198, -198, -198, -198, -198, -198, -198, 271, -198, 288,
	300, -198, -12, -198, -198, 135, 268, -198, -198, 270,
	-13, -198, 77, -198, -198, -198, -198, 275, 144, 273,
	277, 281, 283, 284, 286, 290, 292, 295, 305, 307,
	309, 313, 315, 316, 318, 322, 323, 324, 327, 328,
	330, 332, -198, 135, 271, 272, -198, 276, 335, -198,
	299, 333, 340, 341, 343, 344, 345, 346, 347, 348,
	350, 351, 352, 353, 354, 355, 357, 358, 359, 360,
	361, 362, 363, -198, -198, -198, -198, 366, -22, -198,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, -198,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, -198,
	-198, -198, 271, -198, 375, 371, 367, 368, 369, -198,
	-198, 372, 373, 374, 376, 377, -198, 379, -198, -198,
	-198, 380, -198
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] = {
	38, 9, 0, 0, 10, 31, 0, 0, 0, 0,
	0, 0, 0, 2, 4, 5, 8, 6, 38, 38,
	38, 38, 38, 0, 25, 38, 35, 12, 117, 121,
	33, 34, 23, 19, 21, 36, 1, 9, 7, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 39, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 62, 0, 0, 11, 0, 0, 116, 32,
	0, 0, 0, 0, 120, 0, 0, 0, 14, 26,
	15, 27, 18, 30, 16, 28, 17, 29, 0, 3,
	13, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 61, 119, 118, 125, 122, 123,
	124, 24, 20, 22, 0, 0, 41, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	47, 0, 0, 42, 85, 63, 64, 65, 66, 67,
	68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
	78, 79, 80, 81, 82, 83, 84, 0, 43, 0,
	38, 60, 0, 49, 87, 0, 0, 37, 40, 0,
	0, 50, 0, 44, 45, 48, 51, 0, 38, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 86, 0, 0, 0, 59, 0, 0, 112,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 46, 52, 53, 58, 0, 0, 110,
	88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
	98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
	108, 109, 0, 55, 0, 0, 0, 0, 0, 111,
	54, 0, 0, 0, 0, 0, 56, 0, 115, 113,
	114, 0, 57
};

  /* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] = {
	-198, -198, 177, 386, -9, -8, -198, -198, -198, -198,
	-198, -198, 0, -198, 1, 2, 3, 4, 212, 356,
	-198, -198, -198, -198, -139, -198, -198, -198, -198, -197,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, -198,
	-198, -198
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short yydefgoto[] = {
	-1, 12, 13, 14, 15, 16, 28, 56, 60, 61,
	59, 17, 39, 29, 40, 41, 42, 43, 23, 24,
	72, 145, 205, 243, 146, 197, 202, 244, 302, 203,
	249, 204, 98, 134, 212, 242, 278, 309, 57, 78,
	58, 84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short yytable[] = {
	18, 19, 20, 21, 22, 211, 173, 38, -37, 44,
	46, 48, 50, 52, 304, 305, 201, 25, 306, 209,
	198, 199, 210, 216, 217, 18, 19, 20, 21, 22,
	44, 46, 48, 50, 52, 26, 38, 36, 38, 307,
	38, 308, 38, 27, 38, 30, 31, 274, 32, 33,
	85, 86, 87, 37, 34, 35, 3, 75, 4, 54,
	5, 76, 77, 63, 6, 67, 213, 69, 7, 65,
	8, 71, 9, 73, 10, 74, 88, 38, 38, 38,
	89, 110, 11, 70, 111, 112, 90, 113, 114, 115,
	116, 117, 118, 119, 91, 92, 120, 121, 122, 123,
	124, 125, 93, 126, 273, 310, 127, 94, 128, 129,
	130, 131, 132, 133, 218, 95, 96, 219, 220, 221,
	222, 223, 97, 224, 225, 226, 99, 227, 100, 228,
	229, 230, 231, 232, 233, 101, 102, 234, 171, 235,
	103, 236, 237, 238, 239, 240, 241, 1, 2, 104,
	3, 105, 4, 172, 5, 106, 144, 135, 6, 136,
	246, 137, 7, 138, 8, 144, 9, 139, 10, 79,
	140, 141, 80, 247, 1, 2, 11, 3, 142, 4,
	81, 5, 143, 82, 147, 6, 148, 149, 150, 7,
	83, 8, 151, 9, 37, 10, 152, 3, 153, 4,
	154, 5, 62, 11, 155, 6, 156, 157, 158, 7,
	159, 8, 160, 9, 161, 10, 162, 163, 18, 19,
	20, 21, 22, 11, 37, 164, 165, 3, 166, 4,
	167, 5, 168, 169, 170, 6, 64, 174, 175, 7,
	176, 8, 177, 9, 37, 10, 178, 3, 179, 4,
	180, 5, 181, 11, 182, 6, 183, 184, 185, 7,
	66, 8, 186, 9, 37, 10, 187, 3, 68, 4,
	188, 5, 189, 11, 190, 6, 191, 37, 192, 7,
	3, 8, 4, 9, 5, 10, 193, 194, 6, 195,
	196, 200, 7, 11, 8, 107, 9, 37, 10, 201,
	3, 206, 4, 207, 5, 214, 11, 215, 6, 275,
	245, 250, 7, 276, 8, 251, 9, 108, 10, 252,
	37, 253, 254, 3, 255, 4, 11, 5, 256, 37,
	257, 6, 3, 258, 4, 7, 5, 8, 279, 9,
	6, 10, 109, 259, 7, 260, 8, 261, 9, 11,
	10, 262, 1, 263, 264, 3, 265, 4, 11, 5,
	266, 267, 268, 6, 277, 269, 270, 7, 271, 8,
	272, 9, 280, 10, 45, 47, 49, 51, 53, 281,
	282, 11, 283, 284, 285, 286, 287, 288, 312, 289,
	290, 291, 292, 293, 294, 248, 295, 296, 297, 298,
	299, 300, 301, 303, 311, 313, 314, 315, 321, 316,
	317, 55, 208, 318, 0, 319, 320, 322
};

static const short yycheck[] = {
	0, 0, 0, 0, 0, 202, 145, 15, 26, 18,
	19, 20, 21, 22, 36, 37, 28, 37, 40, 31,
	36, 37, 34, 36, 37, 25, 25, 25, 25, 25,
	39, 40, 41, 42, 43, 37, 44, 0, 46, 61,
	48, 63, 50, 37, 52, 37, 37, 244, 37, 37,
	59, 60, 61, 3, 37, 37, 6, 36, 8, 26,
	10, 40, 41, 11, 14, 19, 205, 7, 18, 15,
	20, 33, 22, 5, 24, 9, 37, 85, 86, 87,
	37, 37, 32, 33, 40, 41, 37, 43, 44, 45,
	46, 47, 48, 49, 37, 37, 52, 53, 54, 55,
	56, 57, 37, 59, 243, 302, 62, 37, 64, 65,
	66, 67, 68, 69, 37, 37, 37, 40, 41, 42,
	43, 44, 37, 46, 47, 48, 37, 50, 37, 52,
	53, 54, 55, 56, 57, 38, 38, 60, 12, 62,
	38, 64, 65, 66, 67, 68, 69, 3, 4, 38,
	6, 38, 8, 27, 10, 38, 30, 39, 14, 39,
	16, 39, 18, 39, 20, 30, 22, 39, 24, 37,
	39, 37, 40, 29, 3, 4, 32, 6, 37, 8,
	48, 10, 37, 51, 38, 14, 38, 38, 38, 18,
	58, 20, 38, 22, 3, 24, 38, 6, 38, 8,
	38, 10, 11, 32, 38, 14, 38, 38, 38, 18,
	38, 20, 38, 22, 38, 24, 38, 38, 218, 218,
	218, 218, 218, 32, 3, 38, 38, 6, 38, 8,
	38, 10, 38, 38, 37, 14, 15, 39, 39, 18,
	39, 20, 39, 22, 3, 24, 39, 6, 39, 8,
	39, 10, 39, 32, 39, 14, 39, 39, 39, 18,
	19, 20, 39, 22, 3, 24, 39, 6, 7, 8,
	39, 10, 39, 32, 39, 14, 39, 3, 39, 18,
	6, 20, 8, 22, 10, 24, 39, 39, 14, 39,
	39, 37, 18, 32, 20, 21, 22, 3, 24, 28,
	6, 13, 8, 3, 10, 37, 32, 37, 14, 37,
	35, 38, 18, 37, 20, 38, 22, 23, 24, 38,
	3, 38, 38, 6, 38, 8, 32, 10, 38, 3,
	38, 14, 6, 38, 8, 18, 10, 20, 39, 22,
	14, 24, 25, 38, 18, 38, 20, 38, 22, 32,
	24, 38, 3, 38, 38, 6, 38, 8, 32, 10,
	38, 38, 38, 14, 29, 38, 38, 18, 38, 20,
	38, 22, 39, 24, 18, 19, 20, 21, 22, 39,
	39, 32, 39, 39, 39, 39, 39, 39, 17, 39,
	39, 39, 39, 39, 39, 218, 39, 39, 39, 39,
	39, 39, 39, 37, 29, 38, 38, 38, 29, 37,
	37, 25, 200, 39, -1, 39, 39, 37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] = {
	0, 3, 4, 6, 8, 10, 14, 18, 20, 22,
	24, 32, 71, 72, 73, 74, 75, 81, 82, 84,
	85, 86, 87, 88, 89, 37, 37, 37, 76, 83,
	37, 37, 37, 37, 37, 37, 0, 3, 75, 82,
	84, 85, 86, 87, 74, 89, 74, 89, 74, 89,
	74, 89, 74, 89, 26, 73, 77, 108, 110, 80,
	78, 79, 11, 11, 15, 15, 19, 19, 7, 7,
	33, 33, 90, 5, 9, 36, 40, 41, 109, 37,
	40, 48, 51, 58, 111, 74, 74, 74, 37, 37,
	37, 37, 37, 37, 37, 37, 37, 37, 102, 37,
	37, 38, 38, 38, 38, 38, 38, 21, 23, 25,
	37, 40, 41, 43, 44, 45, 46, 47, 48, 49,
	52, 53, 54, 55, 56, 57, 59, 62, 64, 65,
	66, 67, 68, 69, 103, 39, 39, 39, 39, 39,
	39, 37, 37, 37, 30, 91, 94, 38, 38, 38,
	38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
	38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
	37, 12, 27, 94, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 95, 36, 37,
	37, 28, 96, 99, 101, 92, 13, 3, 88, 31,
	34, 99, 104, 94, 37, 37, 36, 37, 37, 40,
	41, 42, 43, 44, 46, 47, 48, 50, 52, 53,
	54, 55, 56, 57, 60, 62, 64, 65, 66, 67,
	68, 69, 105, 93, 97, 35, 16, 29, 72, 100,
	38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
	38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
	38, 38, 38, 94, 99, 37, 37, 29, 106, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
	39, 39, 98, 37, 36, 37, 40, 61, 63, 107,
	99, 29, 17, 38, 38, 38, 37, 37, 39, 39,
	39, 29, 37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] = {
	0, 70, 71, 72, 72, 73, 73, 74, 74, 75,
	76, 75, 77, 75, 75, 75, 75, 75, 75, 78,
	75, 79, 75, 80, 75, 81, 81, 81, 81, 81,
	81, 83, 82, 84, 85, 86, 87, 88, 88, 90,
	89, 91, 91, 92, 91, 93, 91, 95, 94, 96,
	96, 97, 96, 98, 96, 99, 99, 99, 99, 100,
	101, 102, 102, 103, 103, 103, 103, 103, 103, 103,
	103, 103, 103, 103, 103, 103, 103, 103, 103, 103,
	103, 103, 103, 103, 103, 103, 104, 104, 105, 105,
	105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
	105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
	105, 106, 106, 107, 107, 107, 108, 108, 109, 109,
	110, 110, 111, 111, 111, 111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] = {
	0, 2, 1, 5, 1, 1, 1, 2, 1, 1,
	0, 4, 0, 5, 4, 4, 4, 4, 4, 0,
	6, 0, 6, 0, 6, 1, 4, 4, 4, 4,
	4, 0, 4, 2, 2, 2, 2, 1, 0, 0,
	9, 1, 2, 0, 5, 0, 7, 0, 6, 1,
	2, 0, 5, 0, 7, 6, 8, 10, 5, 1,
	1, 2, 0, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 2, 0, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 2, 0, 3, 3, 3, 2, 0, 3, 3,
	2, 0, 3, 3, 3, 3
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] = {
	0
};

/* Error token number */
#define YYTERROR 1

YYSTYPE yylval;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if HLYDEBUG

#ifndef YYFPRINTF
#define YYFPRINTF fprintf
#endif

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
#define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

#define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE * yyo, int yytype, YYSTYPE const *const yyvaluep)
{
	FILE *yyoutput = yyo;
	YYUSE(yyoutput);
	if (!yyvaluep)
		return;
	YYUSE(yytype);
}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE * yyo, int yytype, YYSTYPE const *const yyvaluep)
{
	YYFPRINTF(yyo, "%s %s (", yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

	yy_symbol_value_print(yyo, yytype, yyvaluep);
	YYFPRINTF(yyo, ")");
}

#define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack(struct yyGLRStack *yystackp, size_t yyk) YY_ATTRIBUTE_UNUSED;
static void yypdumpstack(struct yyGLRStack *yystackp) YY_ATTRIBUTE_UNUSED;

#else /* !HLYDEBUG */

#define YYDPRINTF(Args)
#define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !HLYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
#define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
#define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

#if YYERROR_VERBOSE

#ifndef yystpcpy
#if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#define yystpcpy stpcpy
#else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *yystpcpy(char *yydest, const char *yysrc)
{
	char *yyd = yydest;
	const char *yys = yysrc;

	while ((*yyd++ = *yys++) != '\0')
		continue;

	return yyd - 1;
}
#endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t yytnamerr(char *yyres, const char *yystr)
{
	if (*yystr == '"') {
		size_t yyn = 0;
		char const *yyp = yystr;

		for (;;)
			switch (*++yyp) {
			case '\'':
			case ',':
				goto do_not_strip_quotes;

			case '\\':
				if (*++yyp != '\\')
					goto do_not_strip_quotes;
				else
					goto append;

append:
			default:
				if (yyres)
					yyres[yyn] = *yyp;
				yyn++;
				break;

			case '"':
				if (yyres)
					yyres[yyn] = '\0';
				return yyn;
			}
do_not_strip_quotes:;
	}

	if (!yyres)
		return strlen(yystr);

	return (size_t)(yystpcpy(yyres, yystr) - yyres);
}
#endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
	yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
	yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
	yyStateNum yylrState;
  /** Preceding state in this stack */
	yyGLRState *yypred;
  /** Source position of the last token produced by my symbol */
	size_t yyposn;
	union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
		yySemanticOption *yyfirstVal;
    /** Semantic value for this state.  */
		YYSTYPE yysval;
	} yysemantics;
};

struct yyGLRStateSet {
	yyGLRState **yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
	yybool *yylookaheadNeeds;
	size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
	yybool yyisState;
  /** Rule number for this reduction */
	yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
	yyGLRState *yystate;
  /** The lookahead for this reduction.  */
	int yyrawchar;
	YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
	yySemanticOption *yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
	yyGLRState yystate;
	yySemanticOption yyoption;
};

struct yyGLRStack {
	int yyerrState;

	YYJMP_BUF yyexception_buffer;
	yyGLRStackItem *yyitems;
	yyGLRStackItem *yynextFree;
	size_t yyspaceLeft;
	yyGLRState *yysplitPoint;
	yyGLRState *yylastDeleted;
	yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack(yyGLRStack * yystackp);
#endif

_Noreturn static void yyFail(yyGLRStack * yystackp, const char *yymsg)
{
	if (yymsg != YY_NULLPTR)
		yyerror(yymsg);
	YYLONGJMP(yystackp->yyexception_buffer, 1);
}

_Noreturn static void yyMemoryExhausted(yyGLRStack * yystackp)
{
	YYLONGJMP(yystackp->yyexception_buffer, 2);
}

#if HLYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char *yytokenName(yySymbol yytoken)
{
	if (yytoken == YYEMPTY)
		return "";

	return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin(yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void yyfillin(yyGLRStackItem * yyvsp, int yylow0, int yylow1)
{
	int i;
	yyGLRState *s = yyvsp[yylow0].yystate.yypred;
	for (i = yylow0 - 1; i >= yylow1; i -= 1) {
#if HLYDEBUG
		yyvsp[i].yystate.yylrState = s->yylrState;
#endif
		yyvsp[i].yystate.yyresolved = s->yyresolved;
		if (s->yyresolved)
			yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
		else
			/* The effect of using yysval or yyloc (in an immediate rule) is
			 * undefined.  */
			yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
		s = yyvsp[i].yystate.yypred = s->yypred;
	}
}

/** If yychar is empty, fetch the next token.  */
static inline yySymbol yygetToken(int *yycharp)
{
	yySymbol yytoken;
	if (*yycharp == YYEMPTY) {
		YYDPRINTF((stderr, "Reading a token: "));
		*yycharp = yylex();
	}
	if (*yycharp <= YYEOF) {
		*yycharp = yytoken = YYEOF;
		YYDPRINTF((stderr, "Now at end of input.\n"));
	} else {
		yytoken = YYTRANSLATE(*yycharp);
		YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
	}
	return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill(yyGLRStackItem *, int *, int, yybool) YY_ATTRIBUTE_UNUSED;
static inline int yyfill(yyGLRStackItem * yyvsp, int *yylow, int yylow1, yybool yynormal)
{
	if (!yynormal && yylow1 < *yylow) {
		yyfillin(yyvsp, *yylow, yylow1);
		*yylow = yylow1;
	}
	return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG yyuserAction(yyRuleNum yyn, int yyrhslen, yyGLRStackItem * yyvsp, yyGLRStack * yystackp, YYSTYPE * yyvalp)
{
	yybool yynormal YY_ATTRIBUTE_UNUSED = (yybool) (yystackp->yysplitPoint == YY_NULLPTR);
	int yylow;
	YYUSE(yyvalp);
	YYUSE(yyrhslen);
#undef yyerrok
#define yyerrok (yystackp->yyerrState = 0)
#undef YYACCEPT
#define YYACCEPT return yyaccept
#undef YYABORT
#define YYABORT return yyabort
#undef YYERROR
#define YYERROR return yyerrok, yyerr
#undef YYRECOVERING
#define YYRECOVERING() (yystackp->yyerrState != 0)
#undef yyclearin
#define yyclearin (yychar = YYEMPTY)
#undef YYFILL
#define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
#undef YYBACKUP
#define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

	yylow = 1;
	if (yyrhslen == 0)
		*yyvalp = yyval_default;
	else
		*yyvalp = yyvsp[YYFILL(1 - yyrhslen)].yystate.yysemantics.yysval;
	switch (yyn) {
	case 6:
#line 282 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1229 "dphlparser.c"	/* glr.c:880  */
		break;

	case 7:
#line 287 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1235 "dphlparser.c"	/* glr.c:880  */
		break;

	case 8:
#line 288 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1241 "dphlparser.c"	/* glr.c:880  */
		break;

	case 9:
#line 303 "dphl.y"		/* glr.c:880  */
		{
			dphl_data((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1247 "dphlparser.c"	/* glr.c:880  */
		break;

	case 10:
#line 304 "dphl.y"		/* glr.c:880  */
		{
			dphl_rbr();
		}
#line 1253 "dphlparser.c"	/* glr.c:880  */
		break;

	case 11:
#line 304 "dphl.y"		/* glr.c:880  */
		{
			dphl_ebr();
		}
#line 1259 "dphlparser.c"	/* glr.c:880  */
		break;

	case 12:
#line 305 "dphl.y"		/* glr.c:880  */
		{
			dphl_rbr();
		}
#line 1265 "dphlparser.c"	/* glr.c:880  */
		break;

	case 13:
#line 305 "dphl.y"		/* glr.c:880  */
		{
			dphl_ebr();
		}
#line 1271 "dphlparser.c"	/* glr.c:880  */
		break;

	case 14:
#line 306 "dphl.y"		/* glr.c:880  */
		{
			dphl_efont();
		}
#line 1277 "dphlparser.c"	/* glr.c:880  */
		break;

	case 15:
#line 307 "dphl.y"		/* glr.c:880  */
		{
			dphl_ei();
		}
#line 1283 "dphlparser.c"	/* glr.c:880  */
		break;

	case 16:
#line 308 "dphl.y"		/* glr.c:880  */
		{
			dphl_eb();
		}
#line 1289 "dphlparser.c"	/* glr.c:880  */
		break;

	case 17:
#line 309 "dphl.y"		/* glr.c:880  */
		{
			dphl_eu();
		}
#line 1295 "dphlparser.c"	/* glr.c:880  */
		break;

	case 18:
#line 310 "dphl.y"		/* glr.c:880  */
		{
			dphl_eo();
		}
#line 1301 "dphlparser.c"	/* glr.c:880  */
		break;

	case 19:
#line 311 "dphl.y"		/* glr.c:880  */
		{
			dphl_rsub();
		}
#line 1307 "dphlparser.c"	/* glr.c:880  */
		break;

	case 20:
#line 311 "dphl.y"		/* glr.c:880  */
		{
			dphl_esub();
		}
#line 1313 "dphlparser.c"	/* glr.c:880  */
		break;

	case 21:
#line 312 "dphl.y"		/* glr.c:880  */
		{
			dphl_rsup();
		}
#line 1319 "dphlparser.c"	/* glr.c:880  */
		break;

	case 22:
#line 312 "dphl.y"		/* glr.c:880  */
		{
			dphl_esup();
		}
#line 1325 "dphlparser.c"	/* glr.c:880  */
		break;

	case 23:
#line 313 "dphl.y"		/* glr.c:880  */
		{
			dphl_rs();
		}
#line 1331 "dphlparser.c"	/* glr.c:880  */
		break;

	case 24:
#line 313 "dphl.y"		/* glr.c:880  */
		{
			dphl_es();
		}
#line 1337 "dphlparser.c"	/* glr.c:880  */
		break;

	case 26:
#line 328 "dphl.y"		/* glr.c:880  */
		{
			dphl_efont();
		}
#line 1343 "dphlparser.c"	/* glr.c:880  */
		break;

	case 27:
#line 329 "dphl.y"		/* glr.c:880  */
		{
			dphl_ei();
		}
#line 1349 "dphlparser.c"	/* glr.c:880  */
		break;

	case 28:
#line 330 "dphl.y"		/* glr.c:880  */
		{
			dphl_eb();
		}
#line 1355 "dphlparser.c"	/* glr.c:880  */
		break;

	case 29:
#line 331 "dphl.y"		/* glr.c:880  */
		{
			dphl_eu();
		}
#line 1361 "dphlparser.c"	/* glr.c:880  */
		break;

	case 30:
#line 332 "dphl.y"		/* glr.c:880  */
		{
			dphl_eo();
		}
#line 1367 "dphlparser.c"	/* glr.c:880  */
		break;

	case 31:
#line 336 "dphl.y"		/* glr.c:880  */
		{
			dphl_rfont();
		}
#line 1373 "dphlparser.c"	/* glr.c:880  */
		break;

	case 33:
#line 340 "dphl.y"		/* glr.c:880  */
		{
			dphl_ri();
		}
#line 1379 "dphlparser.c"	/* glr.c:880  */
		break;

	case 34:
#line 344 "dphl.y"		/* glr.c:880  */
		{
			dphl_ro();
		}
#line 1385 "dphlparser.c"	/* glr.c:880  */
		break;

	case 35:
#line 348 "dphl.y"		/* glr.c:880  */
		{
			dphl_rb();
		}
#line 1391 "dphlparser.c"	/* glr.c:880  */
		break;

	case 36:
#line 352 "dphl.y"		/* glr.c:880  */
		{
			dphl_ru();
		}
#line 1397 "dphlparser.c"	/* glr.c:880  */
		break;

	case 37:
#line 357 "dphl.y"		/* glr.c:880  */
		{
			dphl_tabledata((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1403 "dphlparser.c"	/* glr.c:880  */
		break;

	case 39:
#line 363 "dphl.y"		/* glr.c:880  */
		{
			dphl_rtable();
		}
#line 1409 "dphlparser.c"	/* glr.c:880  */
		break;

	case 40:
#line 363 "dphl.y"		/* glr.c:880  */
		{
			dphl_etable();
		}
#line 1415 "dphlparser.c"	/* glr.c:880  */
		break;

	case 43:
#line 370 "dphl.y"		/* glr.c:880  */
		{
			dphl_rhr();
		}
#line 1421 "dphlparser.c"	/* glr.c:880  */
		break;

	case 45:
#line 371 "dphl.y"		/* glr.c:880  */
		{
			dphl_rhr();
		}
#line 1427 "dphlparser.c"	/* glr.c:880  */
		break;

	case 47:
#line 376 "dphl.y"		/* glr.c:880  */
		{
			dphl_rtr();
		}
#line 1433 "dphlparser.c"	/* glr.c:880  */
		break;

	case 48:
#line 376 "dphl.y"		/* glr.c:880  */
		{
			dphl_etr();
		}
#line 1439 "dphlparser.c"	/* glr.c:880  */
		break;

	case 51:
#line 383 "dphl.y"		/* glr.c:880  */
		{
			dphl_rvr();
		}
#line 1445 "dphlparser.c"	/* glr.c:880  */
		break;

	case 53:
#line 384 "dphl.y"		/* glr.c:880  */
		{
			dphl_rvr();
		}
#line 1451 "dphlparser.c"	/* glr.c:880  */
		break;

	case 55:
#line 392 "dphl.y"		/* glr.c:880  */
		{
			dphl_etd(0);
		}
#line 1457 "dphlparser.c"	/* glr.c:880  */
		break;

	case 56:
#line 393 "dphl.y"		/* glr.c:880  */
		{
			dphl_eimg();
			dphl_etd(1);
		}
#line 1463 "dphlparser.c"	/* glr.c:880  */
		break;

	case 57:
#line 394 "dphl.y"		/* glr.c:880  */
		{
			dphl_eimg();
			dphl_etd(1);
		}
#line 1469 "dphlparser.c"	/* glr.c:880  */
		break;

	case 58:
#line 395 "dphl.y"		/* glr.c:880  */
		{
			dphl_etd(2);
		}
#line 1475 "dphlparser.c"	/* glr.c:880  */
		break;

	case 59:
#line 399 "dphl.y"		/* glr.c:880  */
		{
			dphl_rimg();
		}
#line 1481 "dphlparser.c"	/* glr.c:880  */
		break;

	case 60:
#line 403 "dphl.y"		/* glr.c:880  */
		{
			dphl_rtd();
		}
#line 1487 "dphlparser.c"	/* glr.c:880  */
		break;

	case 63:
#line 435 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_align((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1493 "dphlparser.c"	/* glr.c:880  */
		break;

	case 64:
#line 436 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_bgcolor
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1499 "dphlparser.c"	/* glr.c:880  */
		break;

	case 65:
#line 437 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_border
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1505 "dphlparser.c"	/* glr.c:880  */
		break;

	case 66:
#line 438 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_cellborder((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1511 "dphlparser.c"	/* glr.c:880  */
		break;

	case 67:
#line 439 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_cellpadding
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1517 "dphlparser.c"	/* glr.c:880  */
		break;

	case 68:
#line 440 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_cellspacing
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1523 "dphlparser.c"	/* glr.c:880  */
		break;

	case 69:
#line 441 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_color((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1529 "dphlparser.c"	/* glr.c:880  */
		break;

	case 70:
#line 442 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_columns((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1535 "dphlparser.c"	/* glr.c:880  */
		break;

	case 71:
#line 443 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_fixedsize
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1541 "dphlparser.c"	/* glr.c:880  */
		break;

	case 72:
#line 444 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_gradientangle
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1547 "dphlparser.c"	/* glr.c:880  */
		break;

	case 73:
#line 445 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_height
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1553 "dphlparser.c"	/* glr.c:880  */
		break;

	case 74:
#line 446 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_href((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1559 "dphlparser.c"	/* glr.c:880  */
		break;

	case 75:
#line 447 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_id((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1565 "dphlparser.c"	/* glr.c:880  */
		break;

	case 76:
#line 448 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_port((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1571 "dphlparser.c"	/* glr.c:880  */
		break;

	case 77:
#line 449 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_rows((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1577 "dphlparser.c"	/* glr.c:880  */
		break;

	case 78:
#line 450 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_sides((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1583 "dphlparser.c"	/* glr.c:880  */
		break;

	case 79:
#line 451 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_style((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1589 "dphlparser.c"	/* glr.c:880  */
		break;

	case 80:
#line 452 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_target
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1595 "dphlparser.c"	/* glr.c:880  */
		break;

	case 81:
#line 453 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_title((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1601 "dphlparser.c"	/* glr.c:880  */
		break;

	case 82:
#line 454 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_title((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1607 "dphlparser.c"	/* glr.c:880  */
		break;

	case 83:
#line 455 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_valign
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1613 "dphlparser.c"	/* glr.c:880  */
		break;

	case 84:
#line 456 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_width((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1619 "dphlparser.c"	/* glr.c:880  */
		break;

	case 85:
#line 457 "dphl.y"		/* glr.c:880  */
		{
			dphl_attr_huh("<table>", (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1625 "dphlparser.c"	/* glr.c:880  */
		break;

	case 88:
#line 489 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_align((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1631 "dphlparser.c"	/* glr.c:880  */
		break;

	case 89:
#line 490 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_balign((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1637 "dphlparser.c"	/* glr.c:880  */
		break;

	case 90:
#line 491 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_bgcolor((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1643 "dphlparser.c"	/* glr.c:880  */
		break;

	case 91:
#line 492 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_border((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1649 "dphlparser.c"	/* glr.c:880  */
		break;

	case 92:
#line 493 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_cellpadding
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1655 "dphlparser.c"	/* glr.c:880  */
		break;

	case 93:
#line 494 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_cellspacing
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1661 "dphlparser.c"	/* glr.c:880  */
		break;

	case 94:
#line 495 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_color((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1667 "dphlparser.c"	/* glr.c:880  */
		break;

	case 95:
#line 496 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_colspan((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1673 "dphlparser.c"	/* glr.c:880  */
		break;

	case 96:
#line 497 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_fixedsize
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1679 "dphlparser.c"	/* glr.c:880  */
		break;

	case 97:
#line 498 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_gradientangle
			    ((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1685 "dphlparser.c"	/* glr.c:880  */
		break;

	case 98:
#line 499 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_height((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1691 "dphlparser.c"	/* glr.c:880  */
		break;

	case 99:
#line 500 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_href((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1697 "dphlparser.c"	/* glr.c:880  */
		break;

	case 100:
#line 501 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_id((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1703 "dphlparser.c"	/* glr.c:880  */
		break;

	case 101:
#line 502 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_port((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1709 "dphlparser.c"	/* glr.c:880  */
		break;

	case 102:
#line 503 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_rowspan((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1715 "dphlparser.c"	/* glr.c:880  */
		break;

	case 103:
#line 504 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_sides((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1721 "dphlparser.c"	/* glr.c:880  */
		break;

	case 104:
#line 505 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_sides((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1727 "dphlparser.c"	/* glr.c:880  */
		break;

	case 105:
#line 506 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_target((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1733 "dphlparser.c"	/* glr.c:880  */
		break;

	case 106:
#line 507 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_title((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1739 "dphlparser.c"	/* glr.c:880  */
		break;

	case 107:
#line 508 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_title((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1745 "dphlparser.c"	/* glr.c:880  */
		break;

	case 108:
#line 509 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_valign((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1751 "dphlparser.c"	/* glr.c:880  */
		break;

	case 109:
#line 510 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_width((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_TD)) {
				YYERROR;
			}
		}
#line 1757 "dphlparser.c"	/* glr.c:880  */
		break;

	case 110:
#line 511 "dphl.y"		/* glr.c:880  */
		{
			dphl_attr_huh("<td>", (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1763 "dphlparser.c"	/* glr.c:880  */
		break;

	case 113:
#line 525 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_scale((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1769 "dphlparser.c"	/* glr.c:880  */
		break;

	case 114:
#line 526 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_src((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1775 "dphlparser.c"	/* glr.c:880  */
		break;

	case 115:
#line 527 "dphl.y"		/* glr.c:880  */
		{
			dphl_attr_huh("<img>", (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1781 "dphlparser.c"	/* glr.c:880  */
		break;

	case 118:
#line 539 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_align((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_BR)) {
				YYERROR;
			}
		}
#line 1787 "dphlparser.c"	/* glr.c:880  */
		break;

	case 119:
#line 540 "dphl.y"		/* glr.c:880  */
		{
			dphl_attr_huh("<br>", (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1793 "dphlparser.c"	/* glr.c:880  */
		break;

	case 122:
#line 554 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_color((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), T_FONT)) {
				YYERROR;
			}
		}
#line 1799 "dphlparser.c"	/* glr.c:880  */
		break;

	case 123:
#line 555 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_face((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1805 "dphlparser.c"	/* glr.c:880  */
		break;

	case 124:
#line 556 "dphl.y"		/* glr.c:880  */
		{
			if (dphl_chk_pointsize((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string))) {
				YYERROR;
			}
		}
#line 1811 "dphlparser.c"	/* glr.c:880  */
		break;

	case 125:
#line 557 "dphl.y"		/* glr.c:880  */
		{
			dphl_attr_huh("<font>", (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1817 "dphlparser.c"	/* glr.c:880  */
		break;

#line 1821 "dphlparser.c"	/* glr.c:880  */
	default:
		break;
	}

	return yyok;
#undef yyerrok
#undef YYABORT
#undef YYACCEPT
#undef YYERROR
#undef YYBACKUP
#undef yyclearin
#undef YYRECOVERING
}

static void yyuserMerge(int yyn, YYSTYPE * yy0, YYSTYPE * yy1)
{
	YYUSE(yy0);
	YYUSE(yy1);

	switch (yyn) {

	default:
		break;
	}
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char *yymsg, int yytype, YYSTYPE * yyvaluep)
{
	YYUSE(yyvaluep);
	if (!yymsg)
		yymsg = "Deleting";
	YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN YYUSE(yytype);
YY_IGNORE_MAYBE_UNINITIALIZED_END}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int yyrhsLength(yyRuleNum yyrule)
{
	return yyr2[yyrule];
}

static void yydestroyGLRState(char const *yymsg, yyGLRState * yys)
{
	if (yys->yyresolved)
		yydestruct(yymsg, yystos[yys->yylrState], &yys->yysemantics.yysval);
	else {
#if HLYDEBUG
		if (yydebug) {
			if (yys->yysemantics.yyfirstVal)
				YYFPRINTF(stderr, "%s unresolved", yymsg);
			else
				YYFPRINTF(stderr, "%s incomplete", yymsg);
			YY_SYMBOL_PRINT("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
		}
#endif

		if (yys->yysemantics.yyfirstVal) {
			yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
			yyGLRState *yyrh;
			int yyn;
			for (yyrh = yyoption->yystate, yyn = yyrhsLength(yyoption->yyrule); yyn > 0; yyrh = yyrh->yypred, yyn -= 1)
				yydestroyGLRState(yymsg, yyrh);
		}
	}
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol yylhsNonterm(yyRuleNum yyrule)
{
	return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-198)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool yyisDefaultedState(yyStateNum yystate)
{
	return (yybool) yypact_value_is_default(yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum yydefaultAction(yyStateNum yystate)
{
	return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int yygetLRActions(yyStateNum yystate, yySymbol yytoken, const short **yyconflicts)
{
	int yyindex = yypact[yystate] + yytoken;
	if (yyisDefaultedState(yystate)
	    || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken) {
		*yyconflicts = yyconfl;
		return -yydefact[yystate];
	} else if (!yytable_value_is_error(yytable[yyindex])) {
		*yyconflicts = yyconfl + yyconflp[yyindex];
		return yytable[yyindex];
	} else {
		*yyconflicts = yyconfl + yyconflp[yyindex];
		return 0;
	}
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum yyLRgotoState(yyStateNum yystate, yySymbol yysym)
{
	int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
	if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
		return yytable[yyr];
	else
		return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool yyisShiftAction(int yyaction)
{
	return (yybool) (0 < yyaction);
}

static inline yybool yyisErrorAction(int yyaction)
{
	return (yybool) (yyaction == 0);
}

				/* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem *yynewGLRStackItem(yyGLRStack * yystackp, yybool yyisState)
{
	yyGLRStackItem *yynewItem = yystackp->yynextFree;
	yystackp->yyspaceLeft -= 1;
	yystackp->yynextFree += 1;
	yynewItem->yystate.yyisState = yyisState;
	return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void yyaddDeferredAction(yyGLRStack * yystackp, size_t yyk, yyGLRState * yystate, yyGLRState * yyrhs, yyRuleNum yyrule)
{
	yySemanticOption *yynewOption = &yynewGLRStackItem(yystackp, yyfalse)->yyoption;
	YYASSERT(!yynewOption->yyisState);
	yynewOption->yystate = yyrhs;
	yynewOption->yyrule = yyrule;
	if (yystackp->yytops.yylookaheadNeeds[yyk]) {
		yynewOption->yyrawchar = yychar;
		yynewOption->yyval = yylval;
	} else
		yynewOption->yyrawchar = YYEMPTY;
	yynewOption->yynext = yystate->yysemantics.yyfirstVal;
	yystate->yysemantics.yyfirstVal = yynewOption;

	YY_RESERVE_GLRSTACK(yystackp);
}

				/* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool yyinitStateSet(yyGLRStateSet * yyset)
{
	yyset->yysize = 1;
	yyset->yycapacity = 16;
	yyset->yystates = (yyGLRState **) YYMALLOC(16 * sizeof yyset->yystates[0]);
	if (!yyset->yystates)
		return yyfalse;
	yyset->yystates[0] = YY_NULLPTR;
	yyset->yylookaheadNeeds = (yybool *) YYMALLOC(16 * sizeof yyset->yylookaheadNeeds[0]);
	if (!yyset->yylookaheadNeeds) {
		YYFREE(yyset->yystates);
		return yyfalse;
	}
	return yytrue;
}

static void yyfreeStateSet(yyGLRStateSet * yyset)
{
	YYFREE(yyset->yystates);
	YYFREE(yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool yyinitGLRStack(yyGLRStack * yystackp, size_t yysize)
{
	yystackp->yyerrState = 0;
	yynerrs = 0;
	yystackp->yyspaceLeft = yysize;
	yystackp->yyitems = (yyGLRStackItem *) YYMALLOC(yysize * sizeof yystackp->yynextFree[0]);
	if (!yystackp->yyitems)
		return yyfalse;
	yystackp->yynextFree = yystackp->yyitems;
	yystackp->yysplitPoint = YY_NULLPTR;
	yystackp->yylastDeleted = YY_NULLPTR;
	return yyinitStateSet(&yystackp->yytops);
}

#if YYSTACKEXPANDABLE
#define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void yyexpandGLRStack(yyGLRStack * yystackp)
{
	yyGLRStackItem *yynewItems;
	yyGLRStackItem *yyp0, *yyp1;
	size_t yynewSize;
	size_t yyn;
	size_t yysize = (size_t)(yystackp->yynextFree - yystackp->yyitems);
	if (YYMAXDEPTH - YYHEADROOM < yysize)
		yyMemoryExhausted(yystackp);
	yynewSize = 2 * yysize;
	if (YYMAXDEPTH < yynewSize)
		yynewSize = YYMAXDEPTH;
	yynewItems = (yyGLRStackItem *) YYMALLOC(yynewSize * sizeof yynewItems[0]);
	if (!yynewItems)
		yyMemoryExhausted(yystackp);
	for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize; 0 < yyn; yyn -= 1, yyp0 += 1, yyp1 += 1) {
		*yyp1 = *yyp0;
		if (*(yybool *) yyp0) {
			yyGLRState *yys0 = &yyp0->yystate;
			yyGLRState *yys1 = &yyp1->yystate;
			if (yys0->yypred != YY_NULLPTR)
				yys1->yypred = YYRELOC(yyp0, yyp1, yys0->yypred, yystate);
			if (!yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
				yys1->yysemantics.yyfirstVal = YYRELOC(yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
		} else {
			yySemanticOption *yyv0 = &yyp0->yyoption;
			yySemanticOption *yyv1 = &yyp1->yyoption;
			if (yyv0->yystate != YY_NULLPTR)
				yyv1->yystate = YYRELOC(yyp0, yyp1, yyv0->yystate, yystate);
			if (yyv0->yynext != YY_NULLPTR)
				yyv1->yynext = YYRELOC(yyp0, yyp1, yyv0->yynext, yyoption);
		}
	}
	if (yystackp->yysplitPoint != YY_NULLPTR)
		yystackp->yysplitPoint = YYRELOC(yystackp->yyitems, yynewItems, yystackp->yysplitPoint, yystate);

	for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
		if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
			yystackp->yytops.yystates[yyn] =
			    YYRELOC(yystackp->yyitems, yynewItems, yystackp->yytops.yystates[yyn], yystate);
	YYFREE(yystackp->yyitems);
	yystackp->yyitems = yynewItems;
	yystackp->yynextFree = yynewItems + yysize;
	yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void yyfreeGLRStack(yyGLRStack * yystackp)
{
	YYFREE(yystackp->yyitems);
	yyfreeStateSet(&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void yyupdateSplit(yyGLRStack * yystackp, yyGLRState * yys)
{
	if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
		yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void yymarkStackDeleted(yyGLRStack * yystackp, size_t yyk)
{
	if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
		yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
	yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void yyundeleteLastStack(yyGLRStack * yystackp)
{
	if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
		return;
	yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
	yystackp->yytops.yysize = 1;
	YYDPRINTF((stderr, "Restoring last deleted stack as stack #0.\n"));
	yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void yyremoveDeletes(yyGLRStack * yystackp)
{
	size_t yyi, yyj;
	yyi = yyj = 0;
	while (yyj < yystackp->yytops.yysize) {
		if (yystackp->yytops.yystates[yyi] == YY_NULLPTR) {
			if (yyi == yyj) {
				YYDPRINTF((stderr, "Removing dead stacks.\n"));
			}
			yystackp->yytops.yysize -= 1;
		} else {
			yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
			/* In the current implementation, it's unnecessary to copy
			   yystackp->yytops.yylookaheadNeeds[yyi] since, after
			   yyremoveDeletes returns, the parser immediately either enters
			   deterministic operation or shifts a token.  However, it doesn't
			   hurt, and the code might evolve to need it.  */
			yystackp->yytops.yylookaheadNeeds[yyj] = yystackp->yytops.yylookaheadNeeds[yyi];
			if (yyj != yyi) {
				YYDPRINTF((stderr, "Rename stack %lu -> %lu.\n", (unsigned long)yyi, (unsigned long)yyj));
			}
			yyj += 1;
		}
		yyi += 1;
	}
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void yyglrShift(yyGLRStack * yystackp, size_t yyk, yyStateNum yylrState, size_t yyposn, YYSTYPE * yyvalp)
{
	yyGLRState *yynewState = &yynewGLRStackItem(yystackp, yytrue)->yystate;

	yynewState->yylrState = yylrState;
	yynewState->yyposn = yyposn;
	yynewState->yyresolved = yytrue;
	yynewState->yypred = yystackp->yytops.yystates[yyk];
	yynewState->yysemantics.yysval = *yyvalp;
	yystackp->yytops.yystates[yyk] = yynewState;

	YY_RESERVE_GLRSTACK(yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer(yyGLRStack * yystackp, size_t yyk, yyStateNum yylrState, size_t yyposn, yyGLRState * yyrhs, yyRuleNum yyrule)
{
	yyGLRState *yynewState = &yynewGLRStackItem(yystackp, yytrue)->yystate;
	YYASSERT(yynewState->yyisState);

	yynewState->yylrState = yylrState;
	yynewState->yyposn = yyposn;
	yynewState->yyresolved = yyfalse;
	yynewState->yypred = yystackp->yytops.yystates[yyk];
	yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
	yystackp->yytops.yystates[yyk] = yynewState;

	/* Invokes YY_RESERVE_GLRSTACK.  */
	yyaddDeferredAction(yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !HLYDEBUG
#define YY_REDUCE_PRINT(Args)
#else
#define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void yy_reduce_print(yybool yynormal, yyGLRStackItem * yyvsp, size_t yyk, yyRuleNum yyrule)
{
	int yynrhs = yyrhsLength(yyrule);
	int yyi;
	YYFPRINTF(stderr, "Reducing stack %lu by rule %d (line %lu):\n",
		  (unsigned long)yyk, yyrule - 1, (unsigned long)yyrline[yyrule]);
	if (!yynormal)
		yyfillin(yyvsp, 1, -yynrhs);
	/* The symbols being reduced.  */
	for (yyi = 0; yyi < yynrhs; yyi++) {
		YYFPRINTF(stderr, "   $%d = ", yyi + 1);
		yy_symbol_print(stderr,
				yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
				&yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval);
		if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
			YYFPRINTF(stderr, " (unresolved)");
		YYFPRINTF(stderr, "\n");
	}
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG yydoAction(yyGLRStack * yystackp, size_t yyk, yyRuleNum yyrule, YYSTYPE * yyvalp)
{
	int yynrhs = yyrhsLength(yyrule);

	if (yystackp->yysplitPoint == YY_NULLPTR) {
		/* Standard special case: single stack.  */
		yyGLRStackItem *yyrhs = (yyGLRStackItem *) yystackp->yytops.yystates[yyk];
		YYASSERT(yyk == 0);
		yystackp->yynextFree -= yynrhs;
		yystackp->yyspaceLeft += (size_t)yynrhs;
		yystackp->yytops.yystates[0] = &yystackp->yynextFree[-1].yystate;
		YY_REDUCE_PRINT((yytrue, yyrhs, yyk, yyrule));
		return yyuserAction(yyrule, yynrhs, yyrhs, yystackp, yyvalp);
	} else {
		int yyi;
		yyGLRState *yys;
		yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
		yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yystackp->yytops.yystates[yyk];
		for (yyi = 0; yyi < yynrhs; yyi += 1) {
			yys = yys->yypred;
			YYASSERT(yys);
		}
		yyupdateSplit(yystackp, yys);
		yystackp->yytops.yystates[yyk] = yys;
		YY_REDUCE_PRINT((yyfalse, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
		return yyuserAction(yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yystackp, yyvalp);
	}
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG yyglrReduce(yyGLRStack * yystackp, size_t yyk, yyRuleNum yyrule, yybool yyforceEval)
{
	size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

	if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR) {
		YYSTYPE yysval;

		YYRESULTTAG yyflag = yydoAction(yystackp, yyk, yyrule, &yysval);
		if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR) {
			YYDPRINTF((stderr, "Parse on stack %lu rejected by rule #%d.\n", (unsigned long)yyk, yyrule - 1));
		}
		if (yyflag != yyok)
			return yyflag;
		YY_SYMBOL_PRINT("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
		yyglrShift(yystackp, yyk,
			   yyLRgotoState(yystackp->yytops.yystates[yyk]->yylrState, yylhsNonterm(yyrule)), yyposn, &yysval);
	} else {
		size_t yyi;
		int yyn;
		yyGLRState *yys, *yys0 = yystackp->yytops.yystates[yyk];
		yyStateNum yynewLRState;

		for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength(yyrule); 0 < yyn; yyn -= 1) {
			yys = yys->yypred;
			YYASSERT(yys);
		}
		yyupdateSplit(yystackp, yys);
		yynewLRState = yyLRgotoState(yys->yylrState, yylhsNonterm(yyrule));
		YYDPRINTF((stderr,
			   "Reduced stack %lu by rule #%d; action deferred.  "
			   "Now in state %d.\n", (unsigned long)yyk, yyrule - 1, yynewLRState));
		for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
			if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR) {
				yyGLRState *yysplit = yystackp->yysplitPoint;
				yyGLRState *yyp = yystackp->yytops.yystates[yyi];
				while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn) {
					if (yyp->yylrState == yynewLRState && yyp->yypred == yys) {
						yyaddDeferredAction(yystackp, yyk, yyp, yys0, yyrule);
						yymarkStackDeleted(yystackp, yyk);
						YYDPRINTF((stderr, "Merging stack %lu into stack %lu.\n",
							   (unsigned long)yyk, (unsigned long)yyi));
						return yyok;
					}
					yyp = yyp->yypred;
				}
			}
		yystackp->yytops.yystates[yyk] = yys;
		yyglrShiftDefer(yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
	}
	return yyok;
}

static size_t yysplitStack(yyGLRStack * yystackp, size_t yyk)
{
	if (yystackp->yysplitPoint == YY_NULLPTR) {
		YYASSERT(yyk == 0);
		yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
	}
	if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity) {
		yyGLRState **yynewStates = YY_NULLPTR;
		yybool *yynewLookaheadNeeds;

		if (yystackp->yytops.yycapacity > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
			yyMemoryExhausted(yystackp);
		yystackp->yytops.yycapacity *= 2;

		yynewStates =
		    (yyGLRState **) YYREALLOC(yystackp->yytops.yystates, (yystackp->yytops.yycapacity * sizeof yynewStates[0]));
		if (yynewStates == YY_NULLPTR)
			yyMemoryExhausted(yystackp);
		yystackp->yytops.yystates = yynewStates;

		yynewLookaheadNeeds =
		    (yybool *) YYREALLOC(yystackp->yytops.yylookaheadNeeds,
					 (yystackp->yytops.yycapacity * sizeof yynewLookaheadNeeds[0]));
		if (yynewLookaheadNeeds == YY_NULLPTR)
			yyMemoryExhausted(yystackp);
		yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
	}
	yystackp->yytops.yystates[yystackp->yytops.yysize]
	    = yystackp->yytops.yystates[yyk];
	yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
	    = yystackp->yytops.yylookaheadNeeds[yyk];
	yystackp->yytops.yysize += 1;
	return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool yyidenticalOptions(yySemanticOption * yyy0, yySemanticOption * yyy1)
{
	if (yyy0->yyrule == yyy1->yyrule) {
		yyGLRState *yys0, *yys1;
		int yyn;
		for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
		     yyn = yyrhsLength(yyy0->yyrule); yyn > 0; yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
			if (yys0->yyposn != yys1->yyposn)
				return yyfalse;
		return yytrue;
	} else
		return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void yymergeOptionSets(yySemanticOption * yyy0, yySemanticOption * yyy1)
{
	yyGLRState *yys0, *yys1;
	int yyn;
	for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
	     yyn = yyrhsLength(yyy0->yyrule); yyn > 0; yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1) {
		if (yys0 == yys1)
			break;
		else if (yys0->yyresolved) {
			yys1->yyresolved = yytrue;
			yys1->yysemantics.yysval = yys0->yysemantics.yysval;
		} else if (yys1->yyresolved) {
			yys0->yyresolved = yytrue;
			yys0->yysemantics.yysval = yys1->yysemantics.yysval;
		} else {
			yySemanticOption **yyz0p = &yys0->yysemantics.yyfirstVal;
			yySemanticOption *yyz1 = yys1->yysemantics.yyfirstVal;
			while (yytrue) {
				if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
					break;
				else if (*yyz0p == YY_NULLPTR) {
					*yyz0p = yyz1;
					break;
				} else if (*yyz0p < yyz1) {
					yySemanticOption *yyz = *yyz0p;
					*yyz0p = yyz1;
					yyz1 = yyz1->yynext;
					(*yyz0p)->yynext = yyz;
				}
				yyz0p = &(*yyz0p)->yynext;
			}
			yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
		}
	}
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int yypreference(yySemanticOption * y0, yySemanticOption * y1)
{
	yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
	int p0 = yydprec[r0], p1 = yydprec[r1];

	if (p0 == p1) {
		if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
			return 0;
		else
			return 1;
	}
	if (p0 == 0 || p1 == 0)
		return 0;
	if (p0 < p1)
		return 3;
	if (p1 < p0)
		return 2;
	return 0;
}

static YYRESULTTAG yyresolveValue(yyGLRState * yys, yyGLRStack * yystackp);

/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG yyresolveStates(yyGLRState * yys, int yyn, yyGLRStack * yystackp)
{
	if (0 < yyn) {
		YYASSERT(yys->yypred);
		YYCHK(yyresolveStates(yys->yypred, yyn - 1, yystackp));
		if (!yys->yyresolved)
			YYCHK(yyresolveValue(yys, yystackp));
	}
	return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG yyresolveAction(yySemanticOption * yyopt, yyGLRStack * yystackp, YYSTYPE * yyvalp)
{
	yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
	int yynrhs = yyrhsLength(yyopt->yyrule);
	YYRESULTTAG yyflag = yyresolveStates(yyopt->yystate, yynrhs, yystackp);
	if (yyflag != yyok) {
		yyGLRState *yys;
		for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
			yydestroyGLRState("Cleanup: popping", yys);
		return yyflag;
	}

	yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
	{
		int yychar_current = yychar;
		YYSTYPE yylval_current = yylval;
		yychar = yyopt->yyrawchar;
		yylval = yyopt->yyval;
		yyflag = yyuserAction(yyopt->yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yystackp, yyvalp);
		yychar = yychar_current;
		yylval = yylval_current;
	}
	return yyflag;
}

#if HLYDEBUG
static void yyreportTree(yySemanticOption * yyx, int yyindent)
{
	int yynrhs = yyrhsLength(yyx->yyrule);
	int yyi;
	yyGLRState *yys;
	yyGLRState *yystates[1 + YYMAXRHS];
	yyGLRState yyleftmost_state;

	for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
		yystates[yyi] = yys;
	if (yys == YY_NULLPTR) {
		yyleftmost_state.yyposn = 0;
		yystates[0] = &yyleftmost_state;
	} else
		yystates[0] = yys;

	if (yyx->yystate->yyposn < yys->yyposn + 1)
		YYFPRINTF(stderr, "%*s%s -> <Rule %d, empty>\n",
			  yyindent, "", yytokenName(yylhsNonterm(yyx->yyrule)), yyx->yyrule - 1);
	else
		YYFPRINTF(stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
			  yyindent, "", yytokenName(yylhsNonterm(yyx->yyrule)),
			  yyx->yyrule - 1, (unsigned long)(yys->yyposn + 1), (unsigned long)yyx->yystate->yyposn);
	for (yyi = 1; yyi <= yynrhs; yyi += 1) {
		if (yystates[yyi]->yyresolved) {
			if (yystates[yyi - 1]->yyposn + 1 > yystates[yyi]->yyposn)
				YYFPRINTF(stderr, "%*s%s <empty>\n", yyindent + 2, "",
					  yytokenName(yystos[yystates[yyi]->yylrState]));
			else
				YYFPRINTF(stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent + 2, "",
					  yytokenName(yystos[yystates[yyi]->yylrState]),
					  (unsigned long)(yystates[yyi - 1]->yyposn + 1), (unsigned long)yystates[yyi]->yyposn);
		} else
			yyreportTree(yystates[yyi]->yysemantics.yyfirstVal, yyindent + 2);
	}
}
#endif

static YYRESULTTAG yyreportAmbiguity(yySemanticOption * yyx0, yySemanticOption * yyx1)
{
	YYUSE(yyx0);
	YYUSE(yyx1);

#if HLYDEBUG
	YYFPRINTF(stderr, "Ambiguity detected.\n");
	YYFPRINTF(stderr, "Option 1,\n");
	yyreportTree(yyx0, 2);
	YYFPRINTF(stderr, "\nOption 2,\n");
	yyreportTree(yyx1, 2);
	YYFPRINTF(stderr, "\n");
#endif

	yyerror(YY_("syntax is ambiguous"));
	return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG yyresolveValue(yyGLRState * yys, yyGLRStack * yystackp)
{
	yySemanticOption *yyoptionList = yys->yysemantics.yyfirstVal;
	yySemanticOption *yybest = yyoptionList;
	yySemanticOption **yypp;
	yybool yymerge = yyfalse;
	YYSTYPE yysval;
	YYRESULTTAG yyflag;

	for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR;) {
		yySemanticOption *yyp = *yypp;

		if (yyidenticalOptions(yybest, yyp)) {
			yymergeOptionSets(yybest, yyp);
			*yypp = yyp->yynext;
		} else {
			switch (yypreference(yybest, yyp)) {
			case 0:
				return yyreportAmbiguity(yybest, yyp);
				break;
			case 1:
				yymerge = yytrue;
				break;
			case 2:
				break;
			case 3:
				yybest = yyp;
				yymerge = yyfalse;
				break;
			default:
				/* This cannot happen so it is not worth a YYASSERT (yyfalse),
				   but some compilers complain if the default case is
				   omitted.  */
				break;
			}
			yypp = &yyp->yynext;
		}
	}

	if (yymerge) {
		yySemanticOption *yyp;
		int yyprec = yydprec[yybest->yyrule];
		yyflag = yyresolveAction(yybest, yystackp, &yysval);
		if (yyflag == yyok)
			for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext) {
				if (yyprec == yydprec[yyp->yyrule]) {
					YYSTYPE yysval_other;
					yyflag = yyresolveAction(yyp, yystackp, &yysval_other);
					if (yyflag != yyok) {
						yydestruct("Cleanup: discarding incompletely merged value for",
							   yystos[yys->yylrState], &yysval);
						break;
					}
					yyuserMerge(yymerger[yyp->yyrule], &yysval, &yysval_other);
				}
			}
	} else
		yyflag = yyresolveAction(yybest, yystackp, &yysval);

	if (yyflag == yyok) {
		yys->yyresolved = yytrue;
		yys->yysemantics.yysval = yysval;
	} else
		yys->yysemantics.yyfirstVal = YY_NULLPTR;
	return yyflag;
}

static YYRESULTTAG yyresolveStack(yyGLRStack * yystackp)
{
	if (yystackp->yysplitPoint != YY_NULLPTR) {
		yyGLRState *yys;
		int yyn;

		for (yyn = 0, yys = yystackp->yytops.yystates[0]; yys != yystackp->yysplitPoint; yys = yys->yypred, yyn += 1)
			continue;
		YYCHK(yyresolveStates(yystackp->yytops.yystates[0], yyn, yystackp));
	}
	return yyok;
}

static void yycompressStack(yyGLRStack * yystackp)
{
	yyGLRState *yyp, *yyq, *yyr;

	if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
		return;

	for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
	     yyp != yystackp->yysplitPoint; yyr = yyp, yyp = yyq, yyq = yyp->yypred)
		yyp->yypred = yyr;

	yystackp->yyspaceLeft += (size_t)(yystackp->yynextFree - yystackp->yyitems);
	yystackp->yynextFree = ((yyGLRStackItem *) yystackp->yysplitPoint) + 1;
	yystackp->yyspaceLeft -= (size_t)(yystackp->yynextFree - yystackp->yyitems);
	yystackp->yysplitPoint = YY_NULLPTR;
	yystackp->yylastDeleted = YY_NULLPTR;

	while (yyr != YY_NULLPTR) {
		yystackp->yynextFree->yystate = *yyr;
		yyr = yyr->yypred;
		yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
		yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
		yystackp->yynextFree += 1;
		yystackp->yyspaceLeft -= 1;
	}
}

static YYRESULTTAG yyprocessOneStack(yyGLRStack * yystackp, size_t yyk, size_t yyposn)
{
	while (yystackp->yytops.yystates[yyk] != YY_NULLPTR) {
		yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
		YYDPRINTF((stderr, "Stack %lu Entering state %d\n", (unsigned long)yyk, yystate));

		YYASSERT(yystate != YYFINAL);

		if (yyisDefaultedState(yystate)) {
			YYRESULTTAG yyflag;
			yyRuleNum yyrule = yydefaultAction(yystate);
			if (yyrule == 0) {
				YYDPRINTF((stderr, "Stack %lu dies.\n", (unsigned long)yyk));
				yymarkStackDeleted(yystackp, yyk);
				return yyok;
			}
			yyflag = yyglrReduce(yystackp, yyk, yyrule, yyimmediate[yyrule]);
			if (yyflag == yyerr) {
				YYDPRINTF((stderr,
					   "Stack %lu dies " "(predicate failure or explicit user error).\n", (unsigned long)yyk));
				yymarkStackDeleted(yystackp, yyk);
				return yyok;
			}
			if (yyflag != yyok)
				return yyflag;
		} else {
			yySymbol yytoken;
			int yyaction;
			const short *yyconflicts;

			yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
			yytoken = yygetToken(&yychar);
			yyaction = yygetLRActions(yystate, yytoken, &yyconflicts);

			while (*yyconflicts != 0) {
				YYRESULTTAG yyflag;
				size_t yynewStack = yysplitStack(yystackp, yyk);
				YYDPRINTF((stderr, "Splitting off stack %lu from %lu.\n",
					   (unsigned long)yynewStack, (unsigned long)yyk));
				yyflag = yyglrReduce(yystackp, yynewStack, *yyconflicts, yyimmediate[*yyconflicts]);
				if (yyflag == yyok)
					YYCHK(yyprocessOneStack(yystackp, yynewStack, yyposn));
				else if (yyflag == yyerr) {
					YYDPRINTF((stderr, "Stack %lu dies.\n", (unsigned long)yynewStack));
					yymarkStackDeleted(yystackp, yynewStack);
				} else
					return yyflag;
				yyconflicts += 1;
			}

			if (yyisShiftAction(yyaction))
				break;
			else if (yyisErrorAction(yyaction)) {
				YYDPRINTF((stderr, "Stack %lu dies.\n", (unsigned long)yyk));
				yymarkStackDeleted(yystackp, yyk);
				break;
			} else {
				YYRESULTTAG yyflag = yyglrReduce(yystackp, yyk, -yyaction,
								 yyimmediate[-yyaction]);
				if (yyflag == yyerr) {
					YYDPRINTF((stderr,
						   "Stack %lu dies "
						   "(predicate failure or explicit user error).\n", (unsigned long)yyk));
					yymarkStackDeleted(yystackp, yyk);
					break;
				} else if (yyflag != yyok)
					return yyflag;
			}
		}
	}
	return yyok;
}

static void yyreportSyntaxError(yyGLRStack * yystackp)
{
	if (yystackp->yyerrState != 0)
		return;
#if ! YYERROR_VERBOSE
	yyerror(YY_("syntax error"));
#else
	{
		yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);
		size_t yysize0 = yytnamerr(YY_NULLPTR, yytokenName(yytoken));
		size_t yysize = yysize0;
		yybool yysize_overflow = yyfalse;
		char *yymsg = YY_NULLPTR;
		enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
		/* Internationalized format string. */
		const char *yyformat = YY_NULLPTR;
		/* Arguments of yyformat. */
		char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
		/* Number of reported tokens (one for the "unexpected", one per
		   "expected").  */
		int yycount = 0;

		/* There are many possibilities here to consider:
		   - If this state is a consistent state with a default action, then
		   the only way this function was invoked is if the default action
		   is an error action.  In that case, don't check for expected
		   tokens because there are none.
		   - The only way there can be no lookahead present (in yychar) is if
		   this state is a consistent state with a default action.  Thus,
		   detecting the absence of a lookahead is sufficient to determine
		   that there is no unexpected or expected token to report.  In that
		   case, just report a simple "syntax error".
		   - Don't assume there isn't a lookahead just because this state is a
		   consistent state with a default action.  There might have been a
		   previous inconsistent state, consistent state with a non-default
		   action, or user semantic action that manipulated yychar.
		   - Of course, the expected token list depends on states to have
		   correct lookahead information, and it depends on the parser not
		   to perform extra reductions after fetching a lookahead from the
		   scanner and before detecting a syntax error.  Thus, state merging
		   (from LALR or IELR) and default reductions corrupt the expected
		   token list.  However, the list is correct for canonical LR with
		   one exception: it will still contain any token that will not be
		   accepted due to an error action in a later state.
		 */
		if (yytoken != YYEMPTY) {
			int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
			yyarg[yycount++] = yytokenName(yytoken);
			if (!yypact_value_is_default(yyn)) {
				/* Start YYX at -YYN if negative to avoid negative indexes in
				   YYCHECK.  In other words, skip the first -YYN actions for this
				   state because they are default actions.  */
				int yyxbegin = yyn < 0 ? -yyn : 0;
				/* Stay within bounds of both yycheck and yytname.  */
				int yychecklim = YYLAST - yyn + 1;
				int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
				int yyx;
				for (yyx = yyxbegin; yyx < yyxend; ++yyx)
					if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
					    && !yytable_value_is_error(yytable[yyx + yyn])) {
						if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM) {
							yycount = 1;
							yysize = yysize0;
							break;
						}
						yyarg[yycount++] = yytokenName(yyx);
						{
							size_t yysz = yysize + yytnamerr(YY_NULLPTR, yytokenName(yyx));
							if (yysz < yysize)
								yysize_overflow = yytrue;
							yysize = yysz;
						}
					}
			}
		}

		switch (yycount) {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
		default:	/* Avoid compiler warnings. */
			YYCASE_(0, YY_("syntax error"));
			YYCASE_(1, YY_("syntax error, unexpected %s"));
			YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
			YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
			YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
			YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
		}

		{
			size_t yysz = yysize + strlen(yyformat);
			if (yysz < yysize)
				yysize_overflow = yytrue;
			yysize = yysz;
		}

		if (!yysize_overflow)
			yymsg = (char *)YYMALLOC(yysize);

		if (yymsg) {
			char *yyp = yymsg;
			int yyi = 0;
			while ((*yyp = *yyformat)) {
				if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount) {
					yyp += yytnamerr(yyp, yyarg[yyi++]);
					yyformat += 2;
				} else {
					yyp++;
					yyformat++;
				}
			}
			yyerror(yymsg);
			YYFREE(yymsg);
		} else {
			yyerror(YY_("syntax error"));
			yyMemoryExhausted(yystackp);
		}
	}
#endif /* YYERROR_VERBOSE */
	yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void yyrecoverSyntaxError(yyGLRStack * yystackp)
{
	if (yystackp->yyerrState == 3)
		/* We just shifted the error token and (perhaps) took some
		   reductions.  Skip tokens until we can proceed.  */
		while (yytrue) {
			yySymbol yytoken;
			int yyj;
			if (yychar == YYEOF)
				yyFail(yystackp, YY_NULLPTR);
			if (yychar != YYEMPTY) {
				yytoken = YYTRANSLATE(yychar);
				yydestruct("Error: discarding", yytoken, &yylval);
				yychar = YYEMPTY;
			}
			yytoken = yygetToken(&yychar);
			yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
			if (yypact_value_is_default(yyj))
				return;
			yyj += yytoken;
			if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken) {
				if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
					return;
			} else if (!yytable_value_is_error(yytable[yyj]))
				return;
		}

	/* Reduce to one stack.  */
	{
		size_t yyk;
		for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
			if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
				break;
		if (yyk >= yystackp->yytops.yysize)
			yyFail(yystackp, YY_NULLPTR);
		for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
			yymarkStackDeleted(yystackp, yyk);
		yyremoveDeletes(yystackp);
		yycompressStack(yystackp);
	}

	/* Now pop stack until we find a state that shifts the error token.  */
	yystackp->yyerrState = 3;
	while (yystackp->yytops.yystates[0] != YY_NULLPTR) {
		yyGLRState *yys = yystackp->yytops.yystates[0];
		int yyj = yypact[yys->yylrState];
		if (!yypact_value_is_default(yyj)) {
			yyj += YYTERROR;
			if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR && yyisShiftAction(yytable[yyj])) {
				/* Shift the error token.  */
				YY_SYMBOL_PRINT("Shifting", yystos[yytable[yyj]], &yylval, &yyerrloc);
				yyglrShift(yystackp, 0, yytable[yyj], yys->yyposn, &yylval);
				yys = yystackp->yytops.yystates[0];
				break;
			}
		}
		if (yys->yypred != YY_NULLPTR)
			yydestroyGLRState("Error: popping", yys);
		yystackp->yytops.yystates[0] = yys->yypred;
		yystackp->yynextFree -= 1;
		yystackp->yyspaceLeft += 1;
	}
	if (yystackp->yytops.yystates[0] == YY_NULLPTR)
		yyFail(yystackp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int yyparse(void)
{
	int yyresult;
	yyGLRStack yystack;
	yyGLRStack *const yystackp = &yystack;
	size_t yyposn;

	YYDPRINTF((stderr, "Starting parse\n"));

	yychar = YYEMPTY;
	yylval = yyval_default;

	if (!yyinitGLRStack(yystackp, YYINITDEPTH))
		goto yyexhaustedlab;
	switch (YYSETJMP(yystack.yyexception_buffer)) {
	case 0:
		break;
	case 1:
		goto yyabortlab;
	case 2:
		goto yyexhaustedlab;
	default:
		goto yybuglab;
	}
	yyglrShift(&yystack, 0, 0, 0, &yylval);
	yyposn = 0;

	while (yytrue) {
		/* For efficiency, we have two loops, the first of which is
		   specialized to deterministic operation (single stack, no
		   potential ambiguity).  */
		/* Standard mode */
		while (yytrue) {
			yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
			YYDPRINTF((stderr, "Entering state %d\n", yystate));
			if (yystate == YYFINAL)
				goto yyacceptlab;
			if (yyisDefaultedState(yystate)) {
				yyRuleNum yyrule = yydefaultAction(yystate);
				if (yyrule == 0) {
					yyreportSyntaxError(&yystack);
					goto yyuser_error;
				}
				YYCHK1(yyglrReduce(&yystack, 0, yyrule, yytrue));
			} else {
				yySymbol yytoken = yygetToken(&yychar);
				const short *yyconflicts;
				int yyaction = yygetLRActions(yystate, yytoken, &yyconflicts);
				if (*yyconflicts != 0)
					break;
				if (yyisShiftAction(yyaction)) {
					YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
					yychar = YYEMPTY;
					yyposn += 1;
					yyglrShift(&yystack, 0, yyaction, yyposn, &yylval);
					if (0 < yystack.yyerrState)
						yystack.yyerrState -= 1;
				} else if (yyisErrorAction(yyaction)) {
					yyreportSyntaxError(&yystack);
					goto yyuser_error;
				} else
					YYCHK1(yyglrReduce(&yystack, 0, -yyaction, yytrue));
			}
		}

		while (yytrue) {
			yySymbol yytoken_to_shift;
			size_t yys;

			for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
				yystackp->yytops.yylookaheadNeeds[yys] = (yybool) (yychar != YYEMPTY);

			/* yyprocessOneStack returns one of three things:

			   - An error flag.  If the caller is yyprocessOneStack, it
			   immediately returns as well.  When the caller is finally
			   yyparse, it jumps to an error label via YYCHK1.

			   - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
			   (&yystack, yys), which sets the top state of yys to NULL.  Thus,
			   yyparse's following invocation of yyremoveDeletes will remove
			   the stack.

			   - yyok, when ready to shift a token.

			   Except in the first case, yyparse will invoke yyremoveDeletes and
			   then shift the next token onto all remaining stacks.  This
			   synchronization of the shift (that is, after all preceding
			   reductions on all stacks) helps prevent double destructor calls
			   on yylval in the event of memory exhaustion.  */

			for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
				YYCHK1(yyprocessOneStack(&yystack, yys, yyposn));
			yyremoveDeletes(&yystack);
			if (yystack.yytops.yysize == 0) {
				yyundeleteLastStack(&yystack);
				if (yystack.yytops.yysize == 0)
					yyFail(&yystack, YY_("syntax error"));
				YYCHK1(yyresolveStack(&yystack));
				YYDPRINTF((stderr, "Returning to deterministic operation.\n"));
				yyreportSyntaxError(&yystack);
				goto yyuser_error;
			}

			/* If any yyglrShift call fails, it will fail after shifting.  Thus,
			   a copy of yylval will already be on stack 0 in the event of a
			   failure in the following loop.  Thus, yychar is set to YYEMPTY
			   before the loop to make sure the user destructor for yylval isn't
			   called twice.  */
			yytoken_to_shift = YYTRANSLATE(yychar);
			yychar = YYEMPTY;
			yyposn += 1;
			for (yys = 0; yys < yystack.yytops.yysize; yys += 1) {
				yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
				const short *yyconflicts;
				int yyaction = yygetLRActions(yystate, yytoken_to_shift,
							      &yyconflicts);
				/* Note that yyconflicts were handled by yyprocessOneStack.  */
				YYDPRINTF((stderr, "On stack %lu, ", (unsigned long)yys));
				YY_SYMBOL_PRINT("shifting", yytoken_to_shift, &yylval, &yylloc);
				yyglrShift(&yystack, yys, yyaction, yyposn, &yylval);
				YYDPRINTF((stderr, "Stack %lu now in state #%d\n",
					   (unsigned long)yys, yystack.yytops.yystates[yys]->yylrState));
			}

			if (yystack.yytops.yysize == 1) {
				YYCHK1(yyresolveStack(&yystack));
				YYDPRINTF((stderr, "Returning to deterministic operation.\n"));
				yycompressStack(&yystack);
				break;
			}
		}
		continue;
yyuser_error:
		yyrecoverSyntaxError(&yystack);
		yyposn = yystack.yytops.yystates[0]->yyposn;
	}

yyacceptlab:
	yyresult = 0;
	goto yyreturn;

yybuglab:
	YYASSERT(yyfalse);
	goto yyabortlab;

yyabortlab:
	yyresult = 1;
	goto yyreturn;

yyexhaustedlab:
	yyerror(YY_("memory exhausted"));
	yyresult = 2;
	goto yyreturn;

yyreturn:
	if (yychar != YYEMPTY)
		yydestruct("Cleanup: discarding lookahead", YYTRANSLATE(yychar), &yylval);

	/* If the stack is well-formed, pop the stack until it is empty,
	   destroying its entries as we go.  But free the stack regardless
	   of whether it is well-formed.  */
	if (yystack.yyitems) {
		yyGLRState **yystates = yystack.yytops.yystates;
		if (yystates) {
			size_t yysize = yystack.yytops.yysize;
			size_t yyk;
			for (yyk = 0; yyk < yysize; yyk += 1)
				if (yystates[yyk]) {
					while (yystates[yyk]) {
						yyGLRState *yys = yystates[yyk];
						if (yys->yypred != YY_NULLPTR)
							yydestroyGLRState("Cleanup: popping", yys);
						yystates[yyk] = yys->yypred;
						yystack.yynextFree -= 1;
						yystack.yyspaceLeft += 1;
					}
					break;
				}
		}
		yyfreeGLRStack(&yystack);
	}

	return yyresult;
}

/* DEBUGGING ONLY */
#if HLYDEBUG
static void yy_yypstack(yyGLRState * yys)
{
	if (yys->yypred) {
		yy_yypstack(yys->yypred);
		YYFPRINTF(stderr, " -> ");
	}
	YYFPRINTF(stderr, "%d@%lu", yys->yylrState, (unsigned long)yys->yyposn);
}

static void yypstates(yyGLRState * yyst)
{
	if (yyst == YY_NULLPTR)
		YYFPRINTF(stderr, "<null>");
	else
		yy_yypstack(yyst);
	YYFPRINTF(stderr, "\n");
}

static void yypstack(yyGLRStack * yystackp, size_t yyk)
{
	yypstates(yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)

static void yypdumpstack(yyGLRStack * yystackp)
{
	yyGLRStackItem *yyp;
	size_t yyi;
	for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1) {
		YYFPRINTF(stderr, "%3lu. ", (unsigned long)(yyp - yystackp->yyitems));
		if (*(yybool *) yyp) {
			YYASSERT(yyp->yystate.yyisState);
			YYASSERT(yyp->yyoption.yyisState);
			YYFPRINTF(stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
				  yyp->yystate.yyresolved, yyp->yystate.yylrState,
				  (unsigned long)yyp->yystate.yyposn, (long)YYINDEX(yyp->yystate.yypred));
			if (!yyp->yystate.yyresolved)
				YYFPRINTF(stderr, ", firstVal: %ld", (long)YYINDEX(yyp->yystate.yysemantics.yyfirstVal));
		} else {
			YYASSERT(!yyp->yystate.yyisState);
			YYASSERT(!yyp->yyoption.yyisState);
			YYFPRINTF(stderr, "Option. rule: %d, state: %ld, next: %ld",
				  yyp->yyoption.yyrule - 1,
				  (long)YYINDEX(yyp->yyoption.yystate), (long)YYINDEX(yyp->yyoption.yynext));
		}
		YYFPRINTF(stderr, "\n");
	}
	YYFPRINTF(stderr, "Tops:");
	for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
		YYFPRINTF(stderr, "%lu: %ld; ", (unsigned long)yyi, (long)YYINDEX(yystackp->yytops.yystates[yyi]));
	YYFPRINTF(stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs

/* Substitute the variable and function names.  */
#define yyparse hlyparse
#define yylex   hlylex
#define yyerror hlyerror
#define yylval  hlylval
#define yychar  hlychar
#define yydebug hlydebug
#define yynerrs hlynerrs

#line 560 "dphl.y"		/* glr.c:2603  */

/* end */
