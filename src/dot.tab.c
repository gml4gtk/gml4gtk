/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0

/* First part of user prologue.  */
#line 23 "dot.y"

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "splay-tree.h"
#include "main.h"
#include "dp.h"
#include "dpus.h"
#include "lex.yy.h"
#include "dpmem.h"

#define YY_DEBUG 1

#define YYERROR_VERBOSE 1

/* GNU Bison 3.7.4 bug wrongly uses this attribute not supported in C99 mode */
#undef _Noreturn
#define _Noreturn /**/
/* memory usage wrapping feature */
#ifndef YYFREE
#define YYFREE free
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#endif
#ifndef YYREALLOC
#define YYREALLOC realloc
#endif
/* utf8 code at start if 1 */
static int utfseen = 0;

/* graph is strict if 1 */
static int isstrict = 0;

extern int yylex(void);

static void yyerror(const char *msg)
{
	if (strlen(dp_errmsg) == 0) {
		snprintf(dp_errmsg, 256 - 1, "dot %s(): %s at line %d yytext is %s'\n", __func__, msg, yylineno, yytext);
	}
	printf("dot %s(): %s at line %d yytext is `%s'\n", __func__, msg, yylineno, yytext);
	fflush(stdout);
	fflush(stderr);
	return;
}

#line 114 "dot.tab.c"

#ifndef YY_CAST
#ifdef __cplusplus
#define YY_CAST(Type, Val) static_cast<Type> (Val)
#define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#else
#define YY_CAST(Type, Val) ((Type) (Val))
#define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#endif
#endif
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

/* Symbol kind.  */
enum yysymbol_kind_t {
	YYSYMBOL_YYEMPTY = -2,
	YYSYMBOL_YYEOF = 0,	/* "end of file"  */
	YYSYMBOL_YYerror = 1,	/* error  */
	YYSYMBOL_YYUNDEF = 2,	/* "invalid token"  */
	YYSYMBOL_TOKEN_BRACEOPEN = 3,	/* "{"  */
	YYSYMBOL_TOKEN_BRACECLOSE = 4,	/* "}"  */
	YYSYMBOL_TOKEN_PLUS = 5,	/* "+"  */
	YYSYMBOL_TOKEN_COMMA = 6,	/* ","  */
	YYSYMBOL_TOKEN_COLON = 7,	/* ":"  */
	YYSYMBOL_TOKEN_IS = 8,	/* "="  */
	YYSYMBOL_TOKEN_SC = 9,	/* ";"  */
	YYSYMBOL_TOKEN_BRACKETOPEN = 10,	/* "["  */
	YYSYMBOL_TOKEN_BRACKETCLOSE = 11,	/* "]"  */
	YYSYMBOL_TOKEN_UTF8BOM = 12,	/* "utf8code"  */
	YYSYMBOL_TOKEN_STRICT = 13,	/* "strict"  */
	YYSYMBOL_TOKEN_GRAPH = 14,	/* "graph"  */
	YYSYMBOL_TOKEN_SUBGRAPH = 15,	/* "subgraph"  */
	YYSYMBOL_TOKEN_DIGRAPH = 16,	/* "digraph"  */
	YYSYMBOL_TOKEN_NODE = 17,	/* "node"  */
	YYSYMBOL_TOKEN_EDGE = 18,	/* "edge"  */
	YYSYMBOL_TOKEN_TEXT = 19,	/* "text"  */
	YYSYMBOL_TOKEN_NUM = 20,	/* "number"  */
	YYSYMBOL_TOKEN_QTEXT = 21,	/* "string"  */
	YYSYMBOL_TOKEN_HTEXT = 22,	/* "<html-string>"  */
	YYSYMBOL_TOKEN_EOP = 23,	/* "-> or --"  */
	YYSYMBOL_YYACCEPT = 24,	/* $accept  */
	YYSYMBOL_startdot = 25,	/* startdot  */
	YYSYMBOL_26_1 = 26,	/* $@1  */
	YYSYMBOL_utf = 27,	/* utf  */
	YYSYMBOL_thetype = 28,	/* thetype  */
	YYSYMBOL_thename = 29,	/* thename  */
	YYSYMBOL_ctext = 30,	/* ctext  */
	YYSYMBOL_text = 31,	/* text  */
	YYSYMBOL_htext = 32,	/* htext  */
	YYSYMBOL_statements = 33,	/* statements  */
	YYSYMBOL_statement = 34,	/* statement  */
	YYSYMBOL_statement2 = 35,	/* statement2  */
	YYSYMBOL_36_2 = 36,	/* $@2  */
	YYSYMBOL_nstatement = 37,	/* nstatement  */
	YYSYMBOL_38_3 = 38,	/* $@3  */
	YYSYMBOL_nidid = 39,	/* nidid  */
	YYSYMBOL_nid = 40,	/* nid  */
	YYSYMBOL_sattr = 41,	/* sattr  */
	YYSYMBOL_sattr2 = 42,	/* sattr2  */
	YYSYMBOL_iattr = 43,	/* iattr  */
	YYSYMBOL_tattr = 44,	/* tattr  */
	YYSYMBOL_oattrib = 45,	/* oattrib  */
	YYSYMBOL_estatement = 46,	/* estatement  */
	YYSYMBOL_47_4 = 47,	/* $@4  */
	YYSYMBOL_48_5 = 48,	/* $@5  */
	YYSYMBOL_49_6 = 49,	/* $@6  */
	YYSYMBOL_50_7 = 50,	/* $@7  */
	YYSYMBOL_erhs = 51,	/* erhs  */
	YYSYMBOL_52_8 = 52,	/* $@8  */
	YYSYMBOL_53_9 = 53,	/* $@9  */
	YYSYMBOL_astatement = 54,	/* astatement  */
	YYSYMBOL_atype = 55,	/* atype  */
	YYSYMBOL_aset = 56,	/* aset  */
	YYSYMBOL_sstatement = 57,	/* sstatement  */
	YYSYMBOL_58_10 = 58,	/* $@10  */
	YYSYMBOL_shead = 59	/* shead  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef short
#undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
#include <limits.h>		/* INFRINGES ON USER NAME SPACE */
#if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stdint.h>		/* INFRINGES ON USER NAME SPACE */
#define YY_STDINT_H
#endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
#undef UINT_LEAST8_MAX
#undef UINT_LEAST16_MAX
#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif
#ifndef YYPTRDIFF_T
#if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#define YYPTRDIFF_T __PTRDIFF_TYPE__
#define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
#elif defined PTRDIFF_MAX
#ifndef ptrdiff_t
#include <stddef.h>		/* INFRINGES ON USER NAME SPACE */
#endif
#define YYPTRDIFF_T ptrdiff_t
#define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
#else
#define YYPTRDIFF_T long
#define YYPTRDIFF_MAXIMUM LONG_MAX
#endif
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#include <stddef.h>		/* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

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

#ifdef __cplusplus
typedef bool yybool;
#define yytrue true
#define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
typedef signed char yybool;
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
   YY_ASSERT (0);                               \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE_PURE
#if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
#else
#define YY_ATTRIBUTE_PURE
#endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
#if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#else
#define YY_ATTRIBUTE_UNUSED
#endif
#endif

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
#if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#define _Noreturn [[noreturn]]
#elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (__4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
#elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#define _Noreturn __attribute__ ((__noreturn__))
#elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#define _Noreturn __declspec (noreturn)
#else
#define _Noreturn
#endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
#define YY_USE(E) ((void) (E))
#else
#define YY_USE(E)		/* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
#define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
#define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_BEGIN
#define YY_IGNORE_USELESS_CAST_END
#endif

#define YY_ASSERT(E) ((void) (0 && (E)))

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  100
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 7
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] = {
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
static const yytype_int16 yyrline[] = {
	0, 131, 131, 131, 132, 133, 137, 138, 142, 143,
	144, 145, 150, 151, 156, 157, 162, 163, 164, 169,
	173, 174, 180, 181, 182, 192, 193, 194, 195, 195,
	199, 199, 210, 211, 212, 222, 223, 224, 232, 233,
	237, 238, 242, 243, 244, 245, 249, 253, 254, 258,
	258, 258, 259, 259, 259, 264, 265, 265, 266, 267,
	267, 272, 273, 277, 278, 279, 284, 285, 289, 290,
	290, 295, 296
};
#endif

#define YYPACT_NINF (-52)
#define YYTABLE_NINF (-60)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] = {
	59, -52, -52, 7, 85, -52, 60, -52, -52, 71,
	-52, -52, -52, -52, -52, -52, -2, -52, 10, 6,
	67, -52, -52, -52, 71, -52, -52, 1, 2, -52,
	5, -52, -52, -52, -52, -52, 39, -52, 31, 52,
	67, -52, 71, 75, -52, -52, -52, -52, 39, 55,
	81, -52, 39, 55, 67, 27, 3, -52, -52, -52,
	39, -52, 37, -52, 94, -52, 74, 68, -52, -52,
	47, -52, 71, -52, 96, 82, 83, 39, 75, 81,
	81, -52, -52, 39, -52, 84, 71, 55, 55, -52,
	-52, -52, -52, -52, -52, 97, -52, -52, 71, -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] = {
	0, 4, 6, 0, 0, 1, 0, 9, 11, 13,
	8, 10, 16, 17, 14, 2, 18, 12, 0, 0,
	0, 15, 69, 63, 72, 64, 65, 32, 0, 21,
	22, 25, 30, 49, 26, 27, 0, 62, 28, 0,
	0, 71, 0, 0, 3, 20, 24, 23, 48, 0,
	45, 61, 48, 0, 0, 0, 33, 19, 66, 67,
	48, 31, 0, 50, 41, 40, 45, 0, 29, 53,
	0, 70, 0, 47, 35, 55, 58, 48, 0, 45,
	45, 42, 46, 48, 68, 34, 0, 0, 0, 51,
	38, 39, 43, 44, 54, 36, 57, 60, 0, 37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] = {
	-52, -52, -52, -52, -52, -52, -52, -9, 30, -22,
	-27, -52, -52, -52, -52, -52, 48, -52, -52, -41,
	73, -48, -52, -52, -52, -52, -52, -51, -52, -52,
	-52, -52, -52, 49, -52, -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] = {
	0, 3, 18, 4, 9, 15, 16, 27, 59, 28,
	29, 30, 52, 31, 48, 32, 33, 65, 66, 67,
	60, 61, 34, 49, 77, 53, 83, 63, 87, 88,
	35, 36, 37, 38, 40, 39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] = {
	17, 45, 69, 19, 68, 22, 44, 5, 42, 43,
	72, 46, 73, 20, 47, 41, 23, 24, 55, 25,
	26, 12, 13, 14, -35, 81, -36, 21, 45, 89,
	22, 71, 70, 56, 58, 94, 96, 97, 92, 93,
	22, 23, 24, 45, 25, 26, 12, 13, 14, 50,
	22, 84, 24, 74, -52, 54, 12, 13, 14, -5,
	1, 23, 24, 85, 25, 26, 12, 13, 14, 90,
	22, 2, -7, -7, 10, -7, 11, 95, 62, 82,
	79, 23, 24, 80, 25, 26, 12, 13, 14, 99,
	12, 13, 14, 64, 12, 13, 14, 57, 6, 7,
	64, 8, 78, 86, 98, -56, -59, -37, 91, 51,
	75, 76
};

static const yytype_int8 yycheck[] = {
	9, 28, 53, 5, 52, 3, 4, 0, 7, 8,
	7, 6, 60, 3, 9, 24, 14, 15, 40, 17,
	18, 19, 20, 21, 23, 66, 23, 21, 55, 77,
	3, 4, 54, 42, 43, 83, 87, 88, 79, 80,
	3, 14, 15, 70, 17, 18, 19, 20, 21, 10,
	3, 4, 15, 62, 23, 3, 19, 20, 21, 0,
	1, 14, 15, 72, 17, 18, 19, 20, 21, 78,
	3, 12, 13, 14, 14, 16, 16, 86, 23, 11,
	6, 14, 15, 9, 17, 18, 19, 20, 21, 98,
	19, 20, 21, 19, 19, 20, 21, 22, 13, 14,
	19, 16, 8, 7, 7, 23, 23, 23, 78, 36,
	62, 62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] = {
	0, 1, 12, 25, 27, 0, 13, 14, 16, 28,
	14, 16, 19, 20, 21, 29, 30, 31, 26, 5,
	3, 21, 3, 14, 15, 17, 18, 31, 33, 34,
	35, 37, 39, 40, 46, 54, 55, 56, 57, 59,
	58, 31, 7, 8, 4, 34, 6, 9, 38, 47,
	10, 44, 36, 49, 3, 33, 31, 22, 31, 32,
	44, 45, 23, 51, 19, 41, 42, 43, 45, 51,
	33, 4, 7, 45, 31, 40, 57, 48, 8, 6,
	9, 43, 11, 50, 4, 31, 7, 52, 53, 45,
	31, 32, 43, 43, 45, 31, 51, 51, 7, 31
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] = {
	0, 24, 26, 25, 25, 25, 27, 27, 28, 28,
	28, 28, 29, 29, 30, 30, 31, 31, 31, 32,
	33, 33, 34, 34, 34, 35, 35, 35, 36, 35,
	38, 37, 39, 39, 39, 40, 40, 40, 41, 41,
	42, 42, 43, 43, 43, 43, 44, 45, 45, 47,
	48, 46, 49, 50, 46, 51, 52, 51, 51, 53,
	51, 54, 54, 55, 55, 55, 56, 56, 57, 58,
	57, 59, 59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] = {
	0, 2, 0, 7, 1, 0, 1, 0, 2, 1,
	2, 1, 1, 0, 1, 3, 1, 1, 1, 1,
	2, 1, 1, 2, 2, 1, 1, 1, 0, 3,
	0, 3, 1, 3, 5, 1, 3, 5, 3, 3,
	1, 1, 2, 3, 3, 0, 3, 2, 0, 0,
	0, 5, 0, 0, 5, 2, 0, 4, 2, 0,
	4, 2, 1, 1, 1, 1, 3, 3, 4, 0,
	4, 2, 1
};

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
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
	0, 0, 0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int8 yyconflp[] = {
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
	0, 0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] = {
	0
};

YYSTYPE yylval;

int yynerrs;
int yychar;

enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

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

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
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
	yy_state_t yylrState;
  /** Preceding state in this stack */
	yyGLRState *yypred;
  /** Source position of the last token produced by my symbol */
	YYPTRDIFF_T yyposn;
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
	YYPTRDIFF_T yysize;
	YYPTRDIFF_T yycapacity;
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
	YYPTRDIFF_T yyspaceLeft;
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

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t yy_accessing_symbol(yy_state_t yystate)
{
	return YY_CAST(yysymbol_kind_t, yystos[yystate]);
}

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name(yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
	"\"end of file\"", "error", "\"invalid token\"", "\"{\"", "\"}\"",
	"\"+\"", "\",\"", "\":\"", "\"=\"", "\";\"", "\"[\"", "\"]\"",
	"\"utf8code\"", "\"strict\"", "\"graph\"", "\"subgraph\"", "\"digraph\"",
	"\"node\"", "\"edge\"", "\"text\"", "\"number\"", "\"string\"",
	"\"<html-string>\"", "\"-> or --\"", "$accept", "startdot", "$@1", "utf",
	"thetype", "thename", "ctext", "text", "htext", "statements",
	"statement", "statement2", "$@2", "nstatement", "$@3", "nidid", "nid",
	"sattr", "sattr2", "iattr", "tattr", "oattrib", "estatement", "$@4",
	"$@5", "$@6", "$@7", "erhs", "$@8", "$@9", "astatement", "atype", "aset",
	"sstatement", "$@10", "shead", YY_NULLPTR
};

static const char *yysymbol_name(yysymbol_kind_t yysymbol)
{
	return yytname[yysymbol];
}
#endif

#if YYDEBUG

#ifndef YYFPRINTF
#define YYFPRINTF fprintf
#endif

#define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

#define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

#define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

#define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
#define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void yy_symbol_value_print(FILE * yyo, yysymbol_kind_t yykind, YYSTYPE const *const yyvaluep)
{
	FILE *yyoutput = yyo;
	YY_USE(yyoutput);
	if (!yyvaluep)
		return;
	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN YY_USE(yykind);
YY_IGNORE_MAYBE_UNINITIALIZED_END}

/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void yy_symbol_print(FILE * yyo, yysymbol_kind_t yykind, YYSTYPE const *const yyvaluep)
{
	YYFPRINTF(yyo, "%s %s (", yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name(yykind));

	yy_symbol_value_print(yyo, yykind, yyvaluep);
	YYFPRINTF(yyo, ")");
}

#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack(yyGLRStack * yystackp, YYPTRDIFF_T yyk) YY_ATTRIBUTE_UNUSED;
static void yypdumpstack(yyGLRStack * yystackp) YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

#define YY_DPRINTF(Args) do {} while (yyfalse)
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location)

#endif /* !YYDEBUG */

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
static inline yysymbol_kind_t yygetToken(int *yycharp)
{
	yysymbol_kind_t yytoken;
	if (*yycharp == YYEMPTY) {
		YY_DPRINTF((stderr, "Reading a token\n"));
		*yycharp = yylex();
	}
	if (*yycharp <= YYEOF) {
		*yycharp = YYEOF;
		yytoken = YYSYMBOL_YYEOF;
		YY_DPRINTF((stderr, "Now at end of input.\n"));
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
	yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
	int yylow;
	YY_USE(yyvalp);
	YY_USE(yyrhslen);
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
	case 2:		/* $@1: %empty  */
#line 131 "dot.y"
		{
			dp_sg((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string),
			      (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1130 "dot.tab.c"
		break;

	case 3:		/* startdot: utf thetype thename $@1 "{" statements "}"  */
#line 131 "dot.y"
		{
			dp_eg();
		}
#line 1136 "dot.tab.c"
		break;

	case 4:		/* startdot: error  */
#line 132 "dot.y"
		{
			dp_eg();
		}
#line 1142 "dot.tab.c"
		break;

	case 5:		/* startdot: %empty  */
#line 133 "dot.y"
		{
			dp_eg();
		}
#line 1148 "dot.tab.c"
		break;

	case 6:		/* utf: "utf8code"  */
#line 137 "dot.y"
		{
			utfseen = 1;
		}
#line 1154 "dot.tab.c"
		break;

	case 7:		/* utf: %empty  */
#line 138 "dot.y"
		{
			utfseen = 0;
		}
#line 1160 "dot.tab.c"
		break;

	case 8:		/* thetype: "strict" "graph"  */
#line 142 "dot.y"
		{
			isstrict = 1;
			((*yyvalp).string) = (char *)dp_uniqstr((char *)"--");
		}
#line 1166 "dot.tab.c"
		break;

	case 9:		/* thetype: "graph"  */
#line 143 "dot.y"
		{
			isstrict = 0;
			((*yyvalp).string) = (char *)dp_uniqstr((char *)"--");
		}
#line 1172 "dot.tab.c"
		break;

	case 10:		/* thetype: "strict" "digraph"  */
#line 144 "dot.y"
		{
			isstrict = 1;
			((*yyvalp).string) = (char *)dp_uniqstr((char *)"->");
		}
#line 1178 "dot.tab.c"
		break;

	case 11:		/* thetype: "digraph"  */
#line 145 "dot.y"
		{
			isstrict = 0;
			((*yyvalp).string) = (char *)dp_uniqstr((char *)"->");
		}
#line 1184 "dot.tab.c"
		break;

	case 12:		/* thename: text  */
#line 150 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1190 "dot.tab.c"
		break;

	case 13:		/* thename: %empty  */
#line 151 "dot.y"
		{
			((*yyvalp).string) = NULL;
		}
#line 1196 "dot.tab.c"
		break;

	case 14:		/* ctext: "string"  */
#line 156 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1202 "dot.tab.c"
		break;

	case 15:		/* ctext: ctext "+" "string"  */
#line 157 "dot.y"
		{
			((*yyvalp).string) =
			    dp_ccat((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				    (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1208 "dot.tab.c"
		break;

	case 16:		/* text: "text"  */
#line 162 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1214 "dot.tab.c"
		break;

	case 17:		/* text: "number"  */
#line 163 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1220 "dot.tab.c"
		break;

	case 18:		/* text: ctext  */
#line 164 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1226 "dot.tab.c"
		break;

	case 19:		/* htext: "<html-string>"  */
#line 169 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1232 "dot.tab.c"
		break;

	case 22:		/* statement: statement2  */
#line 180 "dot.y"
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1238 "dot.tab.c"
		break;

	case 23:		/* statement: statement2 ";"  */
#line 181 "dot.y"
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1244 "dot.tab.c"
		break;

	case 24:		/* statement: statement2 ","  */
#line 182 "dot.y"
		{
			if (dp_chkerr()) {
				YYERROR;	/* YYABORT; does not work as expected */
			}
		}
#line 1250 "dot.tab.c"
		break;

	case 28:		/* $@2: %empty  */
#line 195 "dot.y"
		{		/* $1 is not used here *//* $1 is  read-only object */
			(void)dp_free((void *)(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
			dp_atype_sgraph();
		}
#line 1256 "dot.tab.c"
		break;

	case 29:		/* statement2: sstatement $@2 oattrib  */
#line 195 "dot.y"
		{
			dp_atype_graph();
		}
#line 1262 "dot.tab.c"
		break;

	case 30:		/* $@3: %empty  */
#line 199 "dot.y"
		{
			dp_mknode0((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
			dp_atype_node();
		}
#line 1268 "dot.tab.c"
		break;

	case 31:		/* nstatement: nidid $@3 oattrib  */
#line 199 "dot.y"
		{
			dp_atype_graph();
		}
#line 1274 "dot.tab.c"
		break;

	case 32:		/* nidid: text  */
#line 210 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string);
		}
#line 1280 "dot.tab.c"
		break;

	case 33:		/* nidid: text ":" text  */
#line 211 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string);	/* ignore $3 */
		}
#line 1286 "dot.tab.c"
		break;

	case 34:		/* nidid: text ":" text ":" text  */
#line 212 "dot.y"
		{
			((*yyvalp).string) = (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-4)].yystate.yysemantics.yysval.string);	/* ignore $3 $5 */
		}
#line 1292 "dot.tab.c"
		break;

	case 35:		/* nid: text  */
#line 222 "dot.y"
		{
			((*yyvalp).dp) =
			    dp_mknid((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), NULL,
				     NULL);
		}
#line 1298 "dot.tab.c"
		break;

	case 36:		/* nid: text ":" text  */
#line 223 "dot.y"
		{
			((*yyvalp).dp) =
			    dp_mknid((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				     (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), NULL);
		}
#line 1304 "dot.tab.c"
		break;

	case 37:		/* nid: text ":" text ":" text  */
#line 224 "dot.y"
		{
			((*yyvalp).dp) =
			    dp_mknid((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-4)].yystate.yysemantics.yysval.string),
				     (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				     (YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string));
		}
#line 1310 "dot.tab.c"
		break;

	case 38:		/* sattr: "text" "=" text  */
#line 232 "dot.y"
		{		/* string as in "string" */
			dp_aset((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), 0);
		}
#line 1316 "dot.tab.c"
		break;

	case 39:		/* sattr: "text" "=" htext  */
#line 233 "dot.y"
		{		/* html string as in <html-label> */
			dp_aset((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), 1);
		}
#line 1322 "dot.tab.c"
		break;

	case 41:		/* sattr2: "text"  */
#line 238 "dot.y"
		{
			dp_aset((char *)(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string),
				(char *)"true", 0);
		}
#line 1328 "dot.tab.c"
		break;

	case 49:		/* $@4: %empty  */
#line 258 "dot.y"
		{
			dp_starte1((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1334 "dot.tab.c"
		break;

	case 50:		/* $@5: %empty  */
#line 258 "dot.y"
		{
			dp_newe();
		}
#line 1340 "dot.tab.c"
		break;

	case 51:		/* estatement: nid $@4 erhs $@5 oattrib  */
#line 258 "dot.y"
		{
			dp_ende();
			dp_clrep();
		}
#line 1346 "dot.tab.c"
		break;

	case 52:		/* $@6: %empty  */
#line 259 "dot.y"
		{
			dp_starte2((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1352 "dot.tab.c"
		break;

	case 53:		/* $@7: %empty  */
#line 259 "dot.y"
		{
			dp_newe();
		}
#line 1358 "dot.tab.c"
		break;

	case 54:		/* estatement: sstatement $@6 erhs $@7 oattrib  */
#line 259 "dot.y"
		{
			dp_ende();
			dp_clrep();
		}
#line 1364 "dot.tab.c"
		break;

	case 55:		/* erhs: "-> or --" nid  */
#line 264 "dot.y"
		{
			dp_cke((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1370 "dot.tab.c"
		break;

	case 56:		/* $@8: %empty  */
#line 265 "dot.y"
		{
			dp_cke((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1376 "dot.tab.c"
		break;

	case 58:		/* erhs: "-> or --" sstatement  */
#line 266 "dot.y"
		{
			dp_cke((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1382 "dot.tab.c"
		break;

	case 59:		/* $@9: %empty  */
#line 267 "dot.y"
		{
			dp_cke((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-1)].yystate.yysemantics.yysval.string));
			dp_ine((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.dp));
		}
#line 1388 "dot.tab.c"
		break;

	case 61:		/* astatement: atype tattr  */
#line 272 "dot.y"
		{
			dp_atype_graph();
		}
#line 1394 "dot.tab.c"
		break;

	case 62:		/* astatement: aset  */
#line 273 "dot.y"
		{
			dp_atype_graph();
		}
#line 1400 "dot.tab.c"
		break;

	case 63:		/* atype: "graph"  */
#line 277 "dot.y"
		{
			dp_atype_graphdef();
		}
#line 1406 "dot.tab.c"
		break;

	case 64:		/* atype: "node"  */
#line 278 "dot.y"
		{
			dp_atype_nodedef();
		}
#line 1412 "dot.tab.c"
		break;

	case 65:		/* atype: "edge"  */
#line 279 "dot.y"
		{
			dp_atype_edgedef();
		}
#line 1418 "dot.tab.c"
		break;

	case 66:		/* aset: text "=" text  */
#line 284 "dot.y"
		{
			dp_aset((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), 0);
		}
#line 1424 "dot.tab.c"
		break;

	case 67:		/* aset: text "=" htext  */
#line 285 "dot.y"
		{
			dp_aset((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(-2)].yystate.yysemantics.yysval.string),
				(YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string), 1);
		}
#line 1430 "dot.tab.c"
		break;

	case 68:		/* sstatement: shead "{" statements "}"  */
#line 289 "dot.y"
		{
			((*yyvalp).dp) = dp_endss();
		}
#line 1436 "dot.tab.c"
		break;

	case 69:		/* $@10: %empty  */
#line 290 "dot.y"
		{
			dp_namedsubg(NULL, DP_SG_CO);
		}
#line 1442 "dot.tab.c"
		break;

	case 70:		/* sstatement: "{" $@10 statements "}"  */
#line 290 "dot.y"
		{
			((*yyvalp).dp) = dp_endss();
		}
#line 1448 "dot.tab.c"
		break;

	case 71:		/* shead: "subgraph" text  */
#line 295 "dot.y"
		{
			dp_namedsubg((YY_CAST(yyGLRStackItem const *, yyvsp)[YYFILL(0)].yystate.yysemantics.yysval.string),
				     DP_SG_NM);
		}
#line 1454 "dot.tab.c"
		break;

	case 72:		/* shead: "subgraph"  */
#line 296 "dot.y"
		{
			dp_namedsubg(NULL, DP_SG_NN);
		}
#line 1460 "dot.tab.c"
		break;

#line 1464 "dot.tab.c"

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
	YY_USE(yy0);
	YY_USE(yy1);

	switch (yyn) {

	default:
		break;
	}
}

			      /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void yydestruct(const char *yymsg, yysymbol_kind_t yykind, YYSTYPE * yyvaluep)
{
	YY_USE(yyvaluep);
	if (!yymsg)
		yymsg = "Deleting";
	YY_SYMBOL_PRINT(yymsg, yykind, yyvaluep, yylocationp);

	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN YY_USE(yykind);
YY_IGNORE_MAYBE_UNINITIALIZED_END}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int yyrhsLength(yyRuleNum yyrule)
{
	return yyr2[yyrule];
}

static void yydestroyGLRState(char const *yymsg, yyGLRState * yys)
{
	if (yys->yyresolved)
		yydestruct(yymsg, yy_accessing_symbol(yys->yylrState), &yys->yysemantics.yysval);
	else {
#if YYDEBUG
		if (yydebug) {
			if (yys->yysemantics.yyfirstVal)
				YY_FPRINTF((stderr, "%s unresolved", yymsg));
			else
				YY_FPRINTF((stderr, "%s incomplete", yymsg));
			YY_SYMBOL_PRINT("", yy_accessing_symbol(yys->yylrState), YY_NULLPTR, &yys->yyloc);
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
static inline yysymbol_kind_t yylhsNonterm(yyRuleNum yyrule)
{
	return YY_CAST(yysymbol_kind_t, yyr1[yyrule]);
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool yyisDefaultedState(yy_state_t yystate)
{
	return yypact_value_is_default(yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum yydefaultAction(yy_state_t yystate)
{
	return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int yygetLRActions(yy_state_t yystate, yysymbol_kind_t yytoken, const short **yyconflicts)
{
	int yyindex = yypact[yystate] + yytoken;
	if (yytoken == YYSYMBOL_YYerror) {
		// This is the error token.
		*yyconflicts = yyconfl;
		return 0;
	} else if (yyisDefaultedState(yystate)
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
static inline yy_state_t yyLRgotoState(yy_state_t yystate, yysymbol_kind_t yysym)
{
	int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
	if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
		return yytable[yyr];
	else
		return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool yyisShiftAction(int yyaction)
{
	return 0 < yyaction;
}

static inline yybool yyisErrorAction(int yyaction)
{
	return yyaction == 0;
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
static void yyaddDeferredAction(yyGLRStack * yystackp, YYPTRDIFF_T yyk, yyGLRState * yystate, yyGLRState * yyrhs, yyRuleNum yyrule)
{
	yySemanticOption *yynewOption = &yynewGLRStackItem(yystackp, yyfalse)->yyoption;
	YY_ASSERT(!yynewOption->yyisState);
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
	yyset->yystates = YY_CAST(yyGLRState **, YYMALLOC(YY_CAST(YYSIZE_T, yyset->yycapacity)
							  * sizeof yyset->yystates[0]));
	if (!yyset->yystates)
		return yyfalse;
	yyset->yystates[0] = YY_NULLPTR;
	yyset->yylookaheadNeeds = YY_CAST(yybool *, YYMALLOC(YY_CAST(YYSIZE_T, yyset->yycapacity)
							     * sizeof yyset->yylookaheadNeeds[0]));
	if (!yyset->yylookaheadNeeds) {
		YYFREE(yyset->yystates);
		return yyfalse;
	}
	memset(yyset->yylookaheadNeeds, 0, YY_CAST(YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
	return yytrue;
}

static void yyfreeStateSet(yyGLRStateSet * yyset)
{
	YYFREE(yyset->yystates);
	YYFREE(yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool yyinitGLRStack(yyGLRStack * yystackp, YYPTRDIFF_T yysize)
{
	yystackp->yyerrState = 0;
	yynerrs = 0;
	yystackp->yyspaceLeft = yysize;
	yystackp->yyitems = YY_CAST(yyGLRStackItem *, YYMALLOC(YY_CAST(YYSIZE_T, yysize)
							       * sizeof yystackp->yynextFree[0]));
	if (!yystackp->yyitems)
		return yyfalse;
	yystackp->yynextFree = yystackp->yyitems;
	yystackp->yysplitPoint = YY_NULLPTR;
	yystackp->yylastDeleted = YY_NULLPTR;
	return yyinitStateSet(&yystackp->yytops);
}

#if YYSTACKEXPANDABLE
#define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void yyexpandGLRStack(yyGLRStack * yystackp)
{
	yyGLRStackItem *yynewItems;
	yyGLRStackItem *yyp0, *yyp1;
	YYPTRDIFF_T yynewSize;
	YYPTRDIFF_T yyn;
	YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
	if (YYMAXDEPTH - YYHEADROOM < yysize)
		yyMemoryExhausted(yystackp);
	yynewSize = 2 * yysize;
	if (YYMAXDEPTH < yynewSize)
		yynewSize = YYMAXDEPTH;
	yynewItems = YY_CAST(yyGLRStackItem *, YYMALLOC(YY_CAST(YYSIZE_T, yynewSize)
							* sizeof yynewItems[0]));
	if (!yynewItems)
		yyMemoryExhausted(yystackp);
	for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize; 0 < yyn; yyn -= 1, yyp0 += 1, yyp1 += 1) {
		*yyp1 = *yyp0;
		if (*YY_REINTERPRET_CAST(yybool *, yyp0)) {
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
static inline void yymarkStackDeleted(yyGLRStack * yystackp, YYPTRDIFF_T yyk)
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
	YY_DPRINTF((stderr, "Restoring last deleted stack as stack #0.\n"));
	yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void yyremoveDeletes(yyGLRStack * yystackp)
{
	YYPTRDIFF_T yyi, yyj;
	yyi = yyj = 0;
	while (yyj < yystackp->yytops.yysize) {
		if (yystackp->yytops.yystates[yyi] == YY_NULLPTR) {
			if (yyi == yyj)
				YY_DPRINTF((stderr, "Removing dead stacks.\n"));
			yystackp->yytops.yysize -= 1;
		} else {
			yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
			/* In the current implementation, it's unnecessary to copy
			   yystackp->yytops.yylookaheadNeeds[yyi] since, after
			   yyremoveDeletes returns, the parser immediately either enters
			   deterministic operation or shifts a token.  However, it doesn't
			   hurt, and the code might evolve to need it.  */
			yystackp->yytops.yylookaheadNeeds[yyj] = yystackp->yytops.yylookaheadNeeds[yyi];
			if (yyj != yyi)
				YY_DPRINTF((stderr, "Rename stack %ld -> %ld.\n", YY_CAST(long, yyi), YY_CAST(long, yyj)));
			yyj += 1;
		}
		yyi += 1;
	}
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void yyglrShift(yyGLRStack * yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState, YYPTRDIFF_T yyposn, YYSTYPE * yyvalp)
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
yyglrShiftDefer(yyGLRStack * yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
		YYPTRDIFF_T yyposn, yyGLRState * yyrhs, yyRuleNum yyrule)
{
	yyGLRState *yynewState = &yynewGLRStackItem(yystackp, yytrue)->yystate;
	YY_ASSERT(yynewState->yyisState);

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

static inline void yy_reduce_print(yybool yynormal, yyGLRStackItem * yyvsp, YYPTRDIFF_T yyk, yyRuleNum yyrule)
{
	int yynrhs = yyrhsLength(yyrule);
	int yyi;
	YY_FPRINTF((stderr, "Reducing stack %ld by rule %d (line %d):\n", YY_CAST(long, yyk), yyrule - 1, yyrline[yyrule]));
	if (!yynormal)
		yyfillin(yyvsp, 1, -yynrhs);
	/* The symbols being reduced.  */
	for (yyi = 0; yyi < yynrhs; yyi++) {
		YY_FPRINTF((stderr, "   $%d = ", yyi + 1));
		yy_symbol_print(stderr,
				yy_accessing_symbol(yyvsp[yyi - yynrhs + 1].yystate.yylrState),
				&yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval);
		if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
			YY_FPRINTF((stderr, " (unresolved)"));
		YY_FPRINTF((stderr, "\n"));
	}
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG yydoAction(yyGLRStack * yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule, YYSTYPE * yyvalp)
{
	int yynrhs = yyrhsLength(yyrule);

	if (yystackp->yysplitPoint == YY_NULLPTR) {
		/* Standard special case: single stack.  */
		yyGLRStackItem *yyrhs = YY_REINTERPRET_CAST(yyGLRStackItem *, yystackp->yytops.yystates[yyk]);
		YY_ASSERT(yyk == 0);
		yystackp->yynextFree -= yynrhs;
		yystackp->yyspaceLeft += yynrhs;
		yystackp->yytops.yystates[0] = &yystackp->yynextFree[-1].yystate;
		YY_REDUCE_PRINT((yytrue, yyrhs, yyk, yyrule));
		return yyuserAction(yyrule, yynrhs, yyrhs, yystackp, yyvalp);
	} else {
		yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
		yyGLRState *yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yystackp->yytops.yystates[yyk];
		int yyi;
		for (yyi = 0; yyi < yynrhs; yyi += 1) {
			yys = yys->yypred;
			YY_ASSERT(yys);
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
static inline YYRESULTTAG yyglrReduce(yyGLRStack * yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule, yybool yyforceEval)
{
	YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

	if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR) {
		YYSTYPE yysval;

		YYRESULTTAG yyflag = yydoAction(yystackp, yyk, yyrule, &yysval);
		if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
			YY_DPRINTF((stderr,
				    "Parse on stack %ld rejected by rule %d (line %d).\n",
				    YY_CAST(long, yyk), yyrule - 1, yyrline[yyrule - 1]));
		if (yyflag != yyok)
			return yyflag;
		YY_SYMBOL_PRINT("-> $$ =", yylhsNonterm(yyrule), &yysval, &yyloc);
		yyglrShift(yystackp, yyk,
			   yyLRgotoState(yystackp->yytops.yystates[yyk]->yylrState, yylhsNonterm(yyrule)), yyposn, &yysval);
	} else {
		YYPTRDIFF_T yyi;
		int yyn;
		yyGLRState *yys, *yys0 = yystackp->yytops.yystates[yyk];
		yy_state_t yynewLRState;

		for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength(yyrule); 0 < yyn; yyn -= 1) {
			yys = yys->yypred;
			YY_ASSERT(yys);
		}
		yyupdateSplit(yystackp, yys);
		yynewLRState = yyLRgotoState(yys->yylrState, yylhsNonterm(yyrule));
		YY_DPRINTF((stderr,
			    "Reduced stack %ld by rule %d (line %d); action deferred.  "
			    "Now in state %d.\n", YY_CAST(long, yyk), yyrule - 1, yyrline[yyrule - 1], yynewLRState));
		for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
			if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR) {
				yyGLRState *yysplit = yystackp->yysplitPoint;
				yyGLRState *yyp = yystackp->yytops.yystates[yyi];
				while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn) {
					if (yyp->yylrState == yynewLRState && yyp->yypred == yys) {
						yyaddDeferredAction(yystackp, yyk, yyp, yys0, yyrule);
						yymarkStackDeleted(yystackp, yyk);
						YY_DPRINTF((stderr, "Merging stack %ld into stack %ld.\n",
							    YY_CAST(long, yyk), YY_CAST(long, yyi)));
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

static YYPTRDIFF_T yysplitStack(yyGLRStack * yystackp, YYPTRDIFF_T yyk)
{
	if (yystackp->yysplitPoint == YY_NULLPTR) {
		YY_ASSERT(yyk == 0);
		yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
	}
	if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize) {
		YYPTRDIFF_T state_size = YYSIZEOF(yystackp->yytops.yystates[0]);
		YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
		if (half_max_capacity < yystackp->yytops.yycapacity)
			yyMemoryExhausted(yystackp);
		yystackp->yytops.yycapacity *= 2;

		{
			yyGLRState **yynewStates = YY_CAST(yyGLRState **,
							   YYREALLOC(yystackp->yytops.yystates,
								     (YY_CAST(YYSIZE_T, yystackp->yytops.yycapacity)
								      * sizeof yynewStates[0])));
			if (yynewStates == YY_NULLPTR)
				yyMemoryExhausted(yystackp);
			yystackp->yytops.yystates = yynewStates;
		}

		{
			yybool *yynewLookaheadNeeds = YY_CAST(yybool *,
							      YYREALLOC(yystackp->yytops.yylookaheadNeeds,
									(YY_CAST(YYSIZE_T, yystackp->yytops.yycapacity)
									 * sizeof yynewLookaheadNeeds[0])));
			if (yynewLookaheadNeeds == YY_NULLPTR)
				yyMemoryExhausted(yystackp);
			yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
		}
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
	     yyn = yyrhsLength(yyy0->yyrule); 0 < yyn; yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1) {
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
		YY_ASSERT(yys->yypred);
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
		YY_FPRINTF((stderr, "%*s%s -> <Rule %d, empty>\n",
			    yyindent, "", yysymbol_name(yylhsNonterm(yyx->yyrule)), yyx->yyrule - 1));
	else
		YY_FPRINTF((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
			    yyindent, "", yysymbol_name(yylhsNonterm(yyx->yyrule)),
			    yyx->yyrule - 1, YY_CAST(long, yys->yyposn + 1), YY_CAST(long, yyx->yystate->yyposn)));
	for (yyi = 1; yyi <= yynrhs; yyi += 1) {
		if (yystates[yyi]->yyresolved) {
			if (yystates[yyi - 1]->yyposn + 1 > yystates[yyi]->yyposn)
				YY_FPRINTF((stderr, "%*s%s <empty>\n", yyindent + 2, "",
					    yysymbol_name(yy_accessing_symbol(yystates[yyi]->yylrState))));
			else
				YY_FPRINTF((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent + 2, "",
					    yysymbol_name(yy_accessing_symbol(yystates[yyi]->yylrState)),
					    YY_CAST(long, yystates[yyi - 1]->yyposn + 1), YY_CAST(long, yystates[yyi]->yyposn)));
		} else
			yyreportTree(yystates[yyi]->yysemantics.yyfirstVal, yyindent + 2);
	}
}
#endif

static YYRESULTTAG yyreportAmbiguity(yySemanticOption * yyx0, yySemanticOption * yyx1)
{
	YY_USE(yyx0);
	YY_USE(yyx1);

#if YYDEBUG
	YY_FPRINTF((stderr, "Ambiguity detected.\n"));
	YY_FPRINTF((stderr, "Option 1,\n"));
	yyreportTree(yyx0, 2);
	YY_FPRINTF((stderr, "\nOption 2,\n"));
	yyreportTree(yyx1, 2);
	YY_FPRINTF((stderr, "\n"));
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
				/* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
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
							   yy_accessing_symbol(yys->yylrState), &yysval);
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

	yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
	yystackp->yynextFree = YY_REINTERPRET_CAST(yyGLRStackItem *, yystackp->yysplitPoint) + 1;
	yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
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

static YYRESULTTAG yyprocessOneStack(yyGLRStack * yystackp, YYPTRDIFF_T yyk, YYPTRDIFF_T yyposn)
{
	while (yystackp->yytops.yystates[yyk] != YY_NULLPTR) {
		yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
		YY_DPRINTF((stderr, "Stack %ld Entering state %d\n", YY_CAST(long, yyk), yystate));

		YY_ASSERT(yystate != YYFINAL);

		if (yyisDefaultedState(yystate)) {
			YYRESULTTAG yyflag;
			yyRuleNum yyrule = yydefaultAction(yystate);
			if (yyrule == 0) {
				YY_DPRINTF((stderr, "Stack %ld dies.\n", YY_CAST(long, yyk)));
				yymarkStackDeleted(yystackp, yyk);
				return yyok;
			}
			yyflag = yyglrReduce(yystackp, yyk, yyrule, yyimmediate[yyrule]);
			if (yyflag == yyerr) {
				YY_DPRINTF((stderr,
					    "Stack %ld dies " "(predicate failure or explicit user error).\n", YY_CAST(long, yyk)));
				yymarkStackDeleted(yystackp, yyk);
				return yyok;
			}
			if (yyflag != yyok)
				return yyflag;
		} else {
			yysymbol_kind_t yytoken = yygetToken(&yychar);
			const short *yyconflicts;
			const int yyaction = yygetLRActions(yystate, yytoken, &yyconflicts);
			yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

			for ( /* nothing */ ; *yyconflicts; yyconflicts += 1) {
				YYRESULTTAG yyflag;
				YYPTRDIFF_T yynewStack = yysplitStack(yystackp, yyk);
				YY_DPRINTF((stderr, "Splitting off stack %ld from %ld.\n",
					    YY_CAST(long, yynewStack), YY_CAST(long, yyk)));
				yyflag = yyglrReduce(yystackp, yynewStack, *yyconflicts, yyimmediate[*yyconflicts]);
				if (yyflag == yyok)
					YYCHK(yyprocessOneStack(yystackp, yynewStack, yyposn));
				else if (yyflag == yyerr) {
					YY_DPRINTF((stderr, "Stack %ld dies.\n", YY_CAST(long, yynewStack)));
					yymarkStackDeleted(yystackp, yynewStack);
				} else
					return yyflag;
			}

			if (yyisShiftAction(yyaction))
				break;
			else if (yyisErrorAction(yyaction)) {
				YY_DPRINTF((stderr, "Stack %ld dies.\n", YY_CAST(long, yyk)));
				yymarkStackDeleted(yystackp, yyk);
				break;
			} else {
				YYRESULTTAG yyflag = yyglrReduce(yystackp, yyk, -yyaction,
								 yyimmediate[-yyaction]);
				if (yyflag == yyerr) {
					YY_DPRINTF((stderr,
						    "Stack %ld dies "
						    "(predicate failure or explicit user error).\n", YY_CAST(long, yyk)));
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
	yyerror(YY_("syntax error"));
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
			yysymbol_kind_t yytoken;
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
		YYPTRDIFF_T yyk;
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

	/* Pop stack until we find a state that shifts the error token.  */
	yystackp->yyerrState = 3;
	while (yystackp->yytops.yystates[0] != YY_NULLPTR) {
		yyGLRState *yys = yystackp->yytops.yystates[0];
		int yyj = yypact[yys->yylrState];
		if (!yypact_value_is_default(yyj)) {
			yyj += YYSYMBOL_YYerror;
			if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror && yyisShiftAction(yytable[yyj])) {
				/* Shift the error token.  */
				int yyaction = yytable[yyj];
				YY_SYMBOL_PRINT("Shifting", yy_accessing_symbol(yyaction), &yylval, &yyerrloc);
				yyglrShift(yystackp, 0, yyaction, yys->yyposn, &yylval);
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
	YYPTRDIFF_T yyposn;

	YY_DPRINTF((stderr, "Starting parse\n"));

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
		/* Standard mode. */
		while (yytrue) {
			yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
			YY_DPRINTF((stderr, "Entering state %d\n", yystate));
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
				yysymbol_kind_t yytoken = yygetToken(&yychar);
				const short *yyconflicts;
				int yyaction = yygetLRActions(yystate, yytoken, &yyconflicts);
				if (*yyconflicts)
					/* Enter nondeterministic mode.  */
					break;
				if (yyisShiftAction(yyaction)) {
					YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);
					yychar = YYEMPTY;
					yyposn += 1;
					yyglrShift(&yystack, 0, yyaction, yyposn, &yylval);
					if (0 < yystack.yyerrState)
						yystack.yyerrState -= 1;
				} else if (yyisErrorAction(yyaction)) {
					/* Issue an error message unless the scanner already
					   did. */
					if (yychar != YYerror)
						yyreportSyntaxError(&yystack);
					goto yyuser_error;
				} else
					YYCHK1(yyglrReduce(&yystack, 0, -yyaction, yytrue));
			}
		}

		/* Nondeterministic mode. */
		while (yytrue) {
			yysymbol_kind_t yytoken_to_shift;
			YYPTRDIFF_T yys;

			for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
				yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

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
				YY_DPRINTF((stderr, "Returning to deterministic operation.\n"));
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
				yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
				const short *yyconflicts;
				int yyaction = yygetLRActions(yystate, yytoken_to_shift,
							      &yyconflicts);
				/* Note that yyconflicts were handled by yyprocessOneStack.  */
				YY_DPRINTF((stderr, "On stack %ld, ", YY_CAST(long, yys)));
				YY_SYMBOL_PRINT("shifting", yytoken_to_shift, &yylval, &yylloc);
				yyglrShift(&yystack, yys, yyaction, yyposn, &yylval);
				YY_DPRINTF((stderr, "Stack %ld now in state #%d\n",
					    YY_CAST(long, yys), yystack.yytops.yystates[yys]->yylrState));
			}

			if (yystack.yytops.yysize == 1) {
				YYCHK1(yyresolveStack(&yystack));
				YY_DPRINTF((stderr, "Returning to deterministic operation.\n"));
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
	YY_ASSERT(yyfalse);
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
			YYPTRDIFF_T yysize = yystack.yytops.yysize;
			YYPTRDIFF_T yyk;
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
		YY_FPRINTF((stderr, " -> "));
	}
	YY_FPRINTF((stderr, "%d@%ld", yys->yylrState, YY_CAST(long, yys->yyposn)));
}

static void yypstates(yyGLRState * yyst)
{
	if (yyst == YY_NULLPTR)
		YY_FPRINTF((stderr, "<null>"));
	else
		yy_yypstack(yyst);
	YY_FPRINTF((stderr, "\n"));
}

static void yypstack(yyGLRStack * yystackp, YYPTRDIFF_T yyk)
{
	yypstates(yystackp->yytops.yystates[yyk]);
}

static void yypdumpstack(yyGLRStack * yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

	yyGLRStackItem *yyp;
	for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1) {
		YY_FPRINTF((stderr, "%3ld. ", YY_CAST(long, yyp - yystackp->yyitems)));
		if (*YY_REINTERPRET_CAST(yybool *, yyp)) {
			YY_ASSERT(yyp->yystate.yyisState);
			YY_ASSERT(yyp->yyoption.yyisState);
			YY_FPRINTF((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
				    yyp->yystate.yyresolved, yyp->yystate.yylrState,
				    YY_CAST(long, yyp->yystate.yyposn), YYINDEX(yyp->yystate.yypred)));
			if (!yyp->yystate.yyresolved)
				YY_FPRINTF((stderr, ", firstVal: %ld", YYINDEX(yyp->yystate.yysemantics.yyfirstVal)));
		} else {
			YY_ASSERT(!yyp->yystate.yyisState);
			YY_ASSERT(!yyp->yyoption.yyisState);
			YY_FPRINTF((stderr, "Option. rule: %d, state: %ld, next: %ld",
				    yyp->yyoption.yyrule - 1, YYINDEX(yyp->yyoption.yystate), YYINDEX(yyp->yyoption.yynext)));
		}
		YY_FPRINTF((stderr, "\n"));
	}

	YY_FPRINTF((stderr, "Tops:"));
	{
		YYPTRDIFF_T yyi;
		for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
			YY_FPRINTF((stderr, "%ld: %ld; ", YY_CAST(long, yyi), YYINDEX(yystackp->yytops.yystates[yyi])));
		YY_FPRINTF((stderr, "\n"));
	}
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs

#line 299 "dot.y"

/* end. */
