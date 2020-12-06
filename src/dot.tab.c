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

/* First part of user prologue.  */
#line 21 "dot.y"		/* glr.c:237  */

#include "config.h"

#include <stdio.h>
#include <string.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "lex.yy.h"

#define YY_DEBUG 1

#define YYERROR_VERBOSE 1

/* utf8 code at start if 1 */
static int utfseen = 0;

/* graph is strict if 1 */
static int isstrict = 0;

extern int yylex(void);

void yyerror(const char *msg)
{
	if (strlen(dp_errmsg) == 0) {
		snprintf(dp_errmsg, 256 - 1, "%s(): %s at line %d yytext is %s'\n", __func__, msg, yylineno, yytext);
	}
	printf("%s(): %s at line %d yytext is `%s'\n", __func__, msg, yylineno, yytext);
	fflush(stdout);
	fflush(stderr);
	return;
}

#line 94 "dot.tab.c"		/* glr.c:237  */

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

#include "dot.tab.h"

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 7
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token number (for yychar).  */
#define YYMAXUTOK   278
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
	15, 16, 17, 18, 19, 20, 21, 22, 23
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] = {
	0, 109, 109, 109, 110, 111, 115, 116, 120, 121,
	122, 123, 127, 128, 133, 134, 138, 139, 140, 141,
	145, 146, 152, 153, 154, 164, 165, 166, 167, 167,
	171, 171, 182, 183, 184, 194, 195, 196, 201, 205,
	206, 210, 211, 212, 213, 217, 221, 222, 226, 226,
	226, 227, 227, 227, 232, 233, 233, 234, 235, 235,
	240, 241, 245, 246, 247, 251, 255, 256, 256, 261,
	262
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
	"$end", "error", "$undefined", "TOKEN_BRACEOPEN", "TOKEN_BRACECLOSE",
	"TOKEN_PLUS", "TOKEN_COMMA", "TOKEN_COLON", "TOKEN_IS", "TOKEN_SC",
	"TOKEN_BRACKETOPEN", "TOKEN_BRACKETCLOSE", "TOKEN_UTF8BOM",
	"TOKEN_STRICT", "TOKEN_GRAPH", "TOKEN_SUBGRAPH", "TOKEN_DIGRAPH",
	"TOKEN_NODE", "TOKEN_EDGE", "TOKEN_TEXT", "TOKEN_NUM", "TOKEN_QTEXT",
	"TOKEN_HTEXT", "TOKEN_EOP", "$accept", "startdot", "$@1", "utf",
	"thetype", "thename", "ctext", "text", "statements", "statement",
	"statement2", "$@2", "nstatement", "$@3", "nidid", "nid", "sattr",
	"sattr2", "iattr", "tattr", "oattrib", "estatement", "$@4", "$@5", "$@6",
	"$@7", "erhs", "$@8", "$@9", "astatement", "atype", "aset", "sstatement",
	"$@10", "shead", YY_NULLPTR
};
#endif

#define YYPACT_NINF -52
#define YYTABLE_NINF -59

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const signed char yypact[] = {
	103, -52, -52, 5, 97, -52, 51, -52, -52, 38,
	-52, -52, -52, -52, -52, -52, -52, 1, -52, 4,
	9, 0, -52, -52, -52, 38, -52, -52, 3, 29,
	-52, 18, -52, -52, -52, -52, -52, 2, -52, 15,
	36, 0, -52, 38, 38, -52, -52, -52, -52, 2,
	22, 38, -52, 2, 22, 0, 60, 6, -52, 2,
	-52, 70, -52, 47, -52, 87, 50, -52, -52, 80,
	-52, 38, -52, 59, 48, 49, 2, 38, 38, 38,
	-52, -52, 2, -52, 63, 38, 22, 22, -52, -52,
	-52, -52, -52, 81, -52, -52, 38, -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] = {
	0, 4, 6, 0, 0, 1, 0, 9, 11, 13,
	8, 10, 16, 17, 14, 18, 2, 19, 12, 0,
	0, 0, 15, 67, 62, 70, 63, 64, 32, 0,
	20, 22, 25, 30, 48, 26, 27, 0, 61, 28,
	0, 0, 69, 0, 0, 3, 21, 24, 23, 47,
	0, 44, 60, 47, 0, 0, 0, 33, 65, 47,
	31, 0, 49, 40, 39, 44, 0, 29, 52, 0,
	68, 0, 46, 35, 54, 57, 47, 0, 44, 44,
	41, 45, 47, 66, 34, 0, 0, 0, 50, 38,
	42, 43, 53, 36, 56, 59, 0, 37
};

  /* YYPGOTO[NTERM-NUM].  */
static const signed char yypgoto[] = {
	-52, -52, -52, -52, -52, -52, -52, -9, -32, -28,
	-52, -52, -52, -52, -52, 44, -52, -52, -25, 75,
	-51, -52, -52, -52, -52, -52, -50, -52, -52, -52,
	-52, -52, 53, -52, -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const signed char yydefgoto[] = {
	-1, 3, 19, 4, 9, 16, 17, 28, 29, 30,
	31, 53, 32, 49, 33, 34, 64, 65, 66, 59,
	60, 35, 50, 76, 54, 82, 62, 86, 87, 36,
	37, 38, 39, 41, 40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const signed char yytable[] = {
	18, 46, 67, 23, 68, 5, 20, 21, 72, 56,
	43, 44, 51, 71, 24, 25, 42, 26, 27, 12,
	13, 14, 15, 69, 47, 88, -35, 48, 46, -36,
	22, 92, 23, 45, 57, 58, 94, 95, -51, 55,
	80, 46, 63, 24, 25, 61, 26, 27, 12, 13,
	14, 15, 73, 90, 91, 77, 63, 12, 13, 14,
	15, 81, 84, 23, 70, 10, 85, 11, 89, 63,
	63, -55, -58, 23, 24, 25, 93, 26, 27, 12,
	13, 14, 15, 23, 83, 25, -37, 97, 96, 12,
	13, 14, 15, 78, 24, 25, 79, 26, 27, 12,
	13, 14, 15, -5, 1, 74, 12, 13, 14, 15,
	6, 7, 52, 8, 75, 2, -7, -7, 0, -7
};

static const signed char yycheck[] = {
	9, 29, 53, 3, 54, 0, 5, 3, 59, 41,
	7, 8, 10, 7, 14, 15, 25, 17, 18, 19,
	20, 21, 22, 55, 6, 76, 23, 9, 56, 23,
	21, 82, 3, 4, 43, 44, 86, 87, 23, 3,
	65, 69, 51, 14, 15, 23, 17, 18, 19, 20,
	21, 22, 61, 78, 79, 8, 65, 19, 20, 21,
	22, 11, 71, 3, 4, 14, 7, 16, 77, 78,
	79, 23, 23, 3, 14, 15, 85, 17, 18, 19,
	20, 21, 22, 3, 4, 15, 23, 96, 7, 19,
	20, 21, 22, 6, 14, 15, 9, 17, 18, 19,
	20, 21, 22, 0, 1, 61, 19, 20, 21, 22,
	13, 14, 37, 16, 61, 12, 13, 14, -1, 16
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] = {
	0, 1, 12, 25, 27, 0, 13, 14, 16, 28,
	14, 16, 19, 20, 21, 22, 29, 30, 31, 26,
	5, 3, 21, 3, 14, 15, 17, 18, 31, 32,
	33, 34, 36, 38, 39, 45, 53, 54, 55, 56,
	58, 57, 31, 7, 8, 4, 33, 6, 9, 37,
	46, 10, 43, 35, 48, 3, 32, 31, 31, 43,
	44, 23, 50, 31, 40, 41, 42, 44, 50, 32,
	4, 7, 44, 31, 39, 56, 47, 8, 6, 9,
	42, 11, 49, 4, 31, 7, 51, 52, 44, 31,
	42, 42, 44, 31, 50, 50, 7, 31
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] = {
	0, 24, 26, 25, 25, 25, 27, 27, 28, 28,
	28, 28, 29, 29, 30, 30, 31, 31, 31, 31,
	32, 32, 33, 33, 33, 34, 34, 34, 35, 34,
	37, 36, 38, 38, 38, 39, 39, 39, 40, 41,
	41, 42, 42, 42, 42, 43, 44, 44, 46, 47,
	45, 48, 49, 45, 50, 51, 50, 50, 52, 50,
	53, 53, 54, 54, 54, 55, 56, 57, 56, 58,
	58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] = {
	0, 2, 0, 7, 1, 0, 1, 0, 2, 1,
	2, 1, 1, 0, 1, 3, 1, 1, 1, 1,
	1, 2, 1, 2, 2, 1, 1, 1, 0, 3,
	0, 3, 1, 3, 5, 1, 3, 5, 3, 1,
	1, 2, 3, 3, 0, 3, 2, 0, 0, 0,
	5, 0, 0, 5, 2, 0, 4, 2, 0, 4,
	2, 1, 1, 1, 1, 3, 4, 0, 4, 2,
	1
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
	0
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
	0
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
	0
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
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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

#if YYDEBUG

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

#else /* !YYDEBUG */

#define YYDPRINTF(Args)
#define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

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

#if YYDEBUG || YYERROR_VERBOSE
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
#if YYDEBUG
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
	case 2:
#line 109 "dot.y"		/* glr.c:880  */
		{
			dp_sg((((yyGLRStackItem const *)yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string),
			      (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 976 "dot.tab.c"		/* glr.c:880  */
		break;

	case 3:
#line 109 "dot.y"		/* glr.c:880  */
		{
			dp_eg();
		}
#line 982 "dot.tab.c"		/* glr.c:880  */
		break;

	case 4:
#line 110 "dot.y"		/* glr.c:880  */
		{
			dp_eg();
		}
#line 988 "dot.tab.c"		/* glr.c:880  */
		break;

	case 5:
#line 111 "dot.y"		/* glr.c:880  */
		{
			dp_eg();
		}
#line 994 "dot.tab.c"		/* glr.c:880  */
		break;

	case 6:
#line 115 "dot.y"		/* glr.c:880  */
		{
			utfseen = 1;
		}
#line 1000 "dot.tab.c"		/* glr.c:880  */
		break;

	case 7:
#line 116 "dot.y"		/* glr.c:880  */
		{
			utfseen = 0;
		}
#line 1006 "dot.tab.c"		/* glr.c:880  */
		break;

	case 8:
#line 120 "dot.y"		/* glr.c:880  */
		{
			isstrict = 1;
			((*yyvalp).string) = "--";
		}
#line 1012 "dot.tab.c"		/* glr.c:880  */
		break;

	case 9:
#line 121 "dot.y"		/* glr.c:880  */
		{
			isstrict = 0;
			((*yyvalp).string) = "--";
		}
#line 1018 "dot.tab.c"		/* glr.c:880  */
		break;

	case 10:
#line 122 "dot.y"		/* glr.c:880  */
		{
			isstrict = 1;
			((*yyvalp).string) = "->";
		}
#line 1024 "dot.tab.c"		/* glr.c:880  */
		break;

	case 11:
#line 123 "dot.y"		/* glr.c:880  */
		{
			isstrict = 0;
			((*yyvalp).string) = "->";
		}
#line 1030 "dot.tab.c"		/* glr.c:880  */
		break;

	case 12:
#line 127 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1036 "dot.tab.c"		/* glr.c:880  */
		break;

	case 13:
#line 128 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = NULL;
		}
#line 1042 "dot.tab.c"		/* glr.c:880  */
		break;

	case 14:
#line 133 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1048 "dot.tab.c"		/* glr.c:880  */
		break;

	case 15:
#line 134 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) =
			    dp_ccat((((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				    (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1054 "dot.tab.c"		/* glr.c:880  */
		break;

	case 16:
#line 138 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1060 "dot.tab.c"		/* glr.c:880  */
		break;

	case 17:
#line 139 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1066 "dot.tab.c"		/* glr.c:880  */
		break;

	case 18:
#line 140 "dot.y"		/* glr.c:880  */
		{
			printf("%s(): html label at line %d is not supported yet\n", __func__, yylineno);
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1072 "dot.tab.c"		/* glr.c:880  */
		break;

	case 19:
#line 141 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1078 "dot.tab.c"		/* glr.c:880  */
		break;

	case 22:
#line 152 "dot.y"		/* glr.c:880  */
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1084 "dot.tab.c"		/* glr.c:880  */
		break;

	case 23:
#line 153 "dot.y"		/* glr.c:880  */
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1090 "dot.tab.c"		/* glr.c:880  */
		break;

	case 24:
#line 154 "dot.y"		/* glr.c:880  */
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1096 "dot.tab.c"		/* glr.c:880  */
		break;

	case 28:
#line 167 "dot.y"		/* glr.c:880  */
		{
			dp_atype_sgraph();
		}
#line 1102 "dot.tab.c"		/* glr.c:880  */
		break;

	case 29:
#line 167 "dot.y"		/* glr.c:880  */
		{
			dp_atype_graph();
		}
#line 1108 "dot.tab.c"		/* glr.c:880  */
		break;

	case 30:
#line 171 "dot.y"		/* glr.c:880  */
		{
			dp_mknode0((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
			dp_atype_node();
		}
#line 1114 "dot.tab.c"		/* glr.c:880  */
		break;

	case 31:
#line 171 "dot.y"		/* glr.c:880  */
		{
			dp_atype_graph();
		}
#line 1120 "dot.tab.c"		/* glr.c:880  */
		break;

	case 32:
#line 182 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1126 "dot.tab.c"		/* glr.c:880  */
		break;

	case 33:
#line 183 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string);	/* ignore $3 */
		}
#line 1132 "dot.tab.c"		/* glr.c:880  */
		break;

	case 34:
#line 184 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).string) = (((yyGLRStackItem const *)yyvsp)[YYFILL(-4)].yystate.yysemantics.yysval.string);	/* ignore $3 $5 */
		}
#line 1138 "dot.tab.c"		/* glr.c:880  */
		break;

	case 35:
#line 194 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).dp) =
			    dp_mknid((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), NULL, NULL);
		}
#line 1144 "dot.tab.c"		/* glr.c:880  */
		break;

	case 36:
#line 195 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).dp) =
			    dp_mknid((((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				     (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), NULL);
		}
#line 1150 "dot.tab.c"		/* glr.c:880  */
		break;

	case 37:
#line 196 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).dp) =
			    dp_mknid((((yyGLRStackItem const *)yyvsp)[YYFILL(-4)].yystate.yysemantics.yysval.string),
				     (((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				     (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1156 "dot.tab.c"		/* glr.c:880  */
		break;

	case 38:
#line 201 "dot.y"		/* glr.c:880  */
		{
			dp_aset((((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1162 "dot.tab.c"		/* glr.c:880  */
		break;

	case 40:
#line 206 "dot.y"		/* glr.c:880  */
		{
			dp_aset((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), "true");
		}
#line 1168 "dot.tab.c"		/* glr.c:880  */
		break;

	case 48:
#line 226 "dot.y"		/* glr.c:880  */
		{
			dp_starte1((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1174 "dot.tab.c"		/* glr.c:880  */
		break;

	case 49:
#line 226 "dot.y"		/* glr.c:880  */
		{
			dp_newe();
		}
#line 1180 "dot.tab.c"		/* glr.c:880  */
		break;

	case 50:
#line 226 "dot.y"		/* glr.c:880  */
		{
			dp_ende();
			dp_clrep();
		}
#line 1186 "dot.tab.c"		/* glr.c:880  */
		break;

	case 51:
#line 227 "dot.y"		/* glr.c:880  */
		{
			dp_starte2((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1192 "dot.tab.c"		/* glr.c:880  */
		break;

	case 52:
#line 227 "dot.y"		/* glr.c:880  */
		{
			dp_newe();
		}
#line 1198 "dot.tab.c"		/* glr.c:880  */
		break;

	case 53:
#line 227 "dot.y"		/* glr.c:880  */
		{
			dp_ende();
			dp_clrep();
		}
#line 1204 "dot.tab.c"		/* glr.c:880  */
		break;

	case 54:
#line 232 "dot.y"		/* glr.c:880  */
		{
			dp_cke((((yyGLRStackItem const *)yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1210 "dot.tab.c"		/* glr.c:880  */
		break;

	case 55:
#line 233 "dot.y"		/* glr.c:880  */
		{
			dp_cke((((yyGLRStackItem const *)yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1216 "dot.tab.c"		/* glr.c:880  */
		break;

	case 57:
#line 234 "dot.y"		/* glr.c:880  */
		{
			dp_cke((((yyGLRStackItem const *)yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1222 "dot.tab.c"		/* glr.c:880  */
		break;

	case 58:
#line 235 "dot.y"		/* glr.c:880  */
		{
			dp_cke((((yyGLRStackItem const *)yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1228 "dot.tab.c"		/* glr.c:880  */
		break;

	case 60:
#line 240 "dot.y"		/* glr.c:880  */
		{
			dp_atype_graph();
		}
#line 1234 "dot.tab.c"		/* glr.c:880  */
		break;

	case 61:
#line 241 "dot.y"		/* glr.c:880  */
		{
			dp_atype_graph();
		}
#line 1240 "dot.tab.c"		/* glr.c:880  */
		break;

	case 62:
#line 245 "dot.y"		/* glr.c:880  */
		{
			dp_atype_graphdef();
		}
#line 1246 "dot.tab.c"		/* glr.c:880  */
		break;

	case 63:
#line 246 "dot.y"		/* glr.c:880  */
		{
			dp_atype_nodedef();
		}
#line 1252 "dot.tab.c"		/* glr.c:880  */
		break;

	case 64:
#line 247 "dot.y"		/* glr.c:880  */
		{
			dp_atype_edgedef();
		}
#line 1258 "dot.tab.c"		/* glr.c:880  */
		break;

	case 65:
#line 251 "dot.y"		/* glr.c:880  */
		{
			dp_aset((((yyGLRStackItem const *)yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1264 "dot.tab.c"		/* glr.c:880  */
		break;

	case 66:
#line 255 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).dp) = dp_endss();
		}
#line 1270 "dot.tab.c"		/* glr.c:880  */
		break;

	case 67:
#line 256 "dot.y"		/* glr.c:880  */
		{
			dp_namedsubg( /* name */ NULL, /* type compound */ DP_SG_CO);
		}
#line 1276 "dot.tab.c"		/* glr.c:880  */
		break;

	case 68:
#line 256 "dot.y"		/* glr.c:880  */
		{
			((*yyvalp).dp) = dp_endss();
		}
#line 1282 "dot.tab.c"		/* glr.c:880  */
		break;

	case 69:
#line 261 "dot.y"		/* glr.c:880  */
		{
			dp_namedsubg( /* name */ (((yyGLRStackItem const *)yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string),
				     /* type named subgraph */ DP_SG_NM);
		}
#line 1288 "dot.tab.c"		/* glr.c:880  */
		break;

	case 70:
#line 262 "dot.y"		/* glr.c:880  */
		{
			dp_namedsubg( /* name */ NULL, /* type unnamed subgraph */ DP_SG_NN);
		}
#line 1294 "dot.tab.c"		/* glr.c:880  */
		break;

#line 1298 "dot.tab.c"		/* glr.c:880  */
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
#if YYDEBUG
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
  (!!((Yystate) == (-52)))

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

#if !YYDEBUG
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

#if YYDEBUG
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

#if YYDEBUG
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
#if YYDEBUG
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

#line 265 "dot.y"		/* glr.c:2603  */

/* end. */