/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HLYSTYPE
/* Substitute the variable and function names.  */
#define yyparse         hlyparse
#define yylex           hlylex
#define yyerror         hlyerror
#define yydebug         hlydebug
#define yynerrs         hlynerrs

#define yylval          hlylval
#define yychar          hlychar

/* First part of user prologue.  */
#line 75 "dphl.y"		/* yacc.c:337  */

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

/* memory usage wrapping feature */
#ifndef YYFREE
#define YYFREE dp_free
#endif
#ifndef YYMALLOC
#define YYMALLOC dp_malloc
#endif
#ifndef YYREALLOC
#define YYREALLOC dp_realloc
#endif

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

#line 155 "dphlparser.c"	/* yacc.c:337  */
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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
#undef YYERROR_VERBOSE
#define YYERROR_VERBOSE 1
#else
#define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "dphlparser.h".  */
#ifndef YY_HLY_DPHLPARSER_H_INCLUDED
#define YY_HLY_DPHLPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HLYDEBUG
#if defined YYDEBUG
#if YYDEBUG
#define HLYDEBUG 1
#else
#define HLYDEBUG 0
#endif
#else /* ! defined YYDEBUG */
#define HLYDEBUG 1
#endif /* ! defined YYDEBUG */
#endif /* ! defined HLYDEBUG */
#if HLYDEBUG
extern int hlydebug;
#endif

/* Token type.  */
#ifndef HLYTOKENTYPE
#define HLYTOKENTYPE
enum hlytokentype {
	HL_DATA = 258,
	HL_HTML = 259,
	HL_C_HTML = 260,
	HL_B = 261,
	HL_C_B = 262,
	HL_BR = 263,
	HL_C_BR = 264,
	HL_FONT = 265,
	HL_C_FONT = 266,
	HL_HR = 267,
	HL_C_HR = 268,
	HL_I = 269,
	HL_C_I = 270,
	HL_IMG = 271,
	HL_C_IMG = 272,
	HL_O = 273,
	HL_C_O = 274,
	HL_S = 275,
	HL_C_S = 276,
	HL_SUB = 277,
	HL_C_SUB = 278,
	HL_SUP = 279,
	HL_C_SUP = 280,
	HL_TABLE = 281,
	HL_C_TABLE = 282,
	HL_TD = 283,
	HL_C_TD = 284,
	HL_TR = 285,
	HL_C_TR = 286,
	HL_U = 287,
	HL_C_U = 288,
	HL_VR = 289,
	HL_C_VR = 290,
	HL_SC = 291,
	HL_C = 292,
	HL_IS = 293,
	HL_QSTR = 294,
	HL_STR = 295,
	HL_ALIGN = 296,
	HL_BALIGN = 297,
	HL_BGCOLOR = 298,
	HL_BORDER = 299,
	HL_CELLBORDER = 300,
	HL_CELLPADDING = 301,
	HL_CELLSPACING = 302,
	HL_COLOR = 303,
	HL_COLUMNS = 304,
	HL_COLSPAN = 305,
	HL_FACE = 306,
	HL_FIXEDSIZE = 307,
	HL_GRADIENTANGLE = 308,
	HL_HEIGHT = 309,
	HL_HREF = 310,
	HL_ID = 311,
	HL_PORT = 312,
	HL_POINTSIZE = 313,
	HL_ROWS = 314,
	HL_ROWSPAN = 315,
	HL_SCALE = 316,
	HL_SIDES = 317,
	HL_SRC = 318,
	HL_STYLE = 319,
	HL_TARGET = 320,
	HL_TITLE = 321,
	HL_TOOLTIP = 322,
	HL_VALIGN = 323,
	HL_WIDTH = 324
};
#endif

/* Value type.  */
#if ! defined HLYSTYPE && ! defined HLYSTYPE_IS_DECLARED

union HLYSTYPE {
#line 177 "dphl.y"		/* yacc.c:352  */
	char *string;

#line 279 "dphlparser.c"	/* yacc.c:352  */
};

typedef union HLYSTYPE HLYSTYPE;
#define HLYSTYPE_IS_TRIVIAL 1
#define HLYSTYPE_IS_DECLARED 1
#endif

extern HLYSTYPE hlylval;

int hlyparse(void);

#endif /* !YY_HLY_DPHLPARSER_H_INCLUDED  */

#ifdef short
#undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
#ifdef __SIZE_TYPE__
#define YYSIZE_T __SIZE_TYPE__
#elif defined size_t
#define YYSIZE_T size_t
#elif ! defined YYSIZE_T
#include <stddef.h>		/* INFRINGES ON USER NAME SPACE */
#define YYSIZE_T size_t
#else
#define YYSIZE_T unsigned
#endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

#ifdef YYSTACK_USE_ALLOCA
#if YYSTACK_USE_ALLOCA
#ifdef __GNUC__
#define YYSTACK_ALLOC __builtin_alloca
#elif defined __BUILTIN_VA_ARG_INCR
#include <alloca.h>		/* INFRINGES ON USER NAME SPACE */
#elif defined _AIX
#define YYSTACK_ALLOC __alloca
#elif defined _MSC_VER
#include <malloc.h>		/* INFRINGES ON USER NAME SPACE */
#define alloca _alloca
#else
#define YYSTACK_ALLOC alloca
#if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#include <stdlib.h>		/* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#endif
#endif
#endif

#ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#define YYSTACK_ALLOC_MAXIMUM 4032	/* reasonable circa 2006 */
#endif
#else
#define YYSTACK_ALLOC YYMALLOC
#define YYSTACK_FREE YYFREE
#ifndef YYSTACK_ALLOC_MAXIMUM
#define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#endif
#if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#include <stdlib.h>		/* INFRINGES ON USER NAME SPACE */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#endif
#ifndef YYMALLOC
#define YYMALLOC malloc
#if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc(YYSIZE_T);		/* INFRINGES ON USER NAME SPACE */
#endif
#endif
#ifndef YYFREE
#define YYFREE free
#if ! defined free && ! defined EXIT_SUCCESS
void free(void *);		/* INFRINGES ON USER NAME SPACE */
#endif
#endif
#endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HLYSTYPE_IS_TRIVIAL && HLYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
	yytype_int16 yyss_alloc;
	YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
#define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
#define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

#define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
#define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
#ifndef YYCOPY
#if defined __GNUC__ && 1 < __GNUC__
#define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#else
#define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#endif
#endif
#endif /* !YYCOPY_NEEDED */

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

#define YYUNDEFTOK  2
#define YYMAXUTOK   324

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] = {
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] = {
	0, 266, 266, 271, 272, 277, 278, 283, 284, 299,
	300, 300, 301, 301, 302, 303, 304, 305, 306, 307,
	307, 308, 308, 309, 309, 323, 324, 325, 326, 327,
	328, 332, 332, 336, 340, 344, 348, 353, 354, 359,
	359, 364, 365, 366, 366, 367, 367, 372, 372, 377,
	378, 379, 379, 380, 380, 388, 389, 390, 391, 395,
	399, 426, 427, 431, 432, 433, 434, 435, 436, 437,
	438, 439, 440, 441, 442, 443, 444, 445, 446, 447,
	448, 449, 450, 451, 452, 453, 480, 481, 485, 486,
	487, 488, 489, 490, 491, 492, 493, 494, 495, 496,
	497, 498, 499, 500, 501, 502, 503, 504, 505, 506,
	507, 516, 517, 521, 522, 523, 530, 531, 535, 536,
	545, 546, 550, 551, 552, 553
};
#endif

#if HLYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
	"$end", "error", "$undefined", "HL_DATA", "HL_HTML", "HL_C_HTML",
	"HL_B", "HL_C_B", "HL_BR", "HL_C_BR", "HL_FONT", "HL_C_FONT", "HL_HR",
	"HL_C_HR", "HL_I", "HL_C_I", "HL_IMG", "HL_C_IMG", "HL_O", "HL_C_O",
	"HL_S", "HL_C_S", "HL_SUB", "HL_C_SUB", "HL_SUP", "HL_C_SUP", "HL_TABLE",
	"HL_C_TABLE", "HL_TD", "HL_C_TD", "HL_TR", "HL_C_TR", "HL_U", "HL_C_U",
	"HL_VR", "HL_C_VR", "HL_SC", "HL_C", "HL_IS", "HL_QSTR", "HL_STR",
	"HL_ALIGN", "HL_BALIGN", "HL_BGCOLOR", "HL_BORDER", "HL_CELLBORDER",
	"HL_CELLPADDING", "HL_CELLSPACING", "HL_COLOR", "HL_COLUMNS",
	"HL_COLSPAN", "HL_FACE", "HL_FIXEDSIZE", "HL_GRADIENTANGLE", "HL_HEIGHT",
	"HL_HREF", "HL_ID", "HL_PORT", "HL_POINTSIZE", "HL_ROWS", "HL_ROWSPAN",
	"HL_SCALE", "HL_SIDES", "HL_SRC", "HL_STYLE", "HL_TARGET", "HL_TITLE",
	"HL_TOOLTIP", "HL_VALIGN", "HL_WIDTH", "$accept", "begin", "htmlparser",
	"htmlparser2", "items", "item", "$@1", "$@2", "$@3", "$@4", "$@5",
	"fonttab2", "font", "$@6", "italic", "overline", "bold", "underline",
	"tabe", "tab", "$@7", "rows", "$@8", "$@9", "row", "$@10", "cells",
	"$@11", "$@12", "cell", "cellimg", "celltd", "table_arg", "table_1arg",
	"td_arg", "td_1arg", "img_arg", "img_1arg", "br_arg", "br_1arg",
	"font_arg", "font_1arg", YY_NULLPTR
};
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] = {
	0, 256, 257, 258, 259, 260, 261, 262, 263, 264,
	265, 266, 267, 268, 269, 270, 271, 272, 273, 274,
	275, 276, 277, 278, 279, 280, 281, 282, 283, 284,
	285, 286, 287, 288, 289, 290, 291, 292, 293, 294,
	295, 296, 297, 298, 299, 300, 301, 302, 303, 304,
	305, 306, 307, 308, 309, 310, 311, 312, 313, 314,
	315, 316, 317, 318, 319, 320, 321, 322, 323, 324
};
#endif

#define YYPACT_NINF -198

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-198)))

#define YYTABLE_NINF -38

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] = {
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
static const yytype_uint8 yydefact[] = {
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
static const yytype_int16 yypgoto[] = {
	-198, -198, 177, 386, -9, -8, -198, -198, -198, -198,
	-198, -198, 0, -198, 1, 2, 3, 4, 212, 356,
	-198, -198, -198, -198, -139, -198, -198, -198, -198, -197,
	-198, -198, -198, -198, -198, -198, -198, -198, -198, -198,
	-198, -198
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] = {
	-1, 12, 13, 14, 15, 16, 28, 56, 60, 61,
	59, 17, 39, 29, 40, 41, 42, 43, 23, 24,
	72, 145, 205, 243, 146, 197, 202, 244, 302, 203,
	249, 204, 98, 134, 212, 242, 278, 309, 57, 78,
	58, 84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] = {
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

static const yytype_int16 yycheck[] = {
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
static const yytype_uint8 yystos[] = {
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
static const yytype_uint8 yyr1[] = {
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
static const yytype_uint8 yyr2[] = {
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

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256

/* Enable debugging if requested.  */
#if HLYDEBUG

#ifndef YYFPRINTF
#include <stdio.h>		/* INFRINGES ON USER NAME SPACE */
#define YYFPRINTF fprintf
#endif

#define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
#define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif

#define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
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
#ifdef YYPRINT
	if (yytype < YYNTOKENS)
		YYPRINT(yyo, yytoknum[yytype], *yyvaluep);
#endif
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

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void yy_stack_print(yytype_int16 * yybottom, yytype_int16 * yytop)
{
	YYFPRINTF(stderr, "Stack now");
	for (; yybottom <= yytop; yybottom++) {
		int yybot = *yybottom;
		YYFPRINTF(stderr, " %d", yybot);
	}
	YYFPRINTF(stderr, "\n");
}

#define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)

/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void yy_reduce_print(yytype_int16 * yyssp, YYSTYPE * yyvsp, int yyrule)
{
	unsigned long yylno = yyrline[yyrule];
	int yynrhs = yyr2[yyrule];
	int yyi;
	YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n", yyrule - 1, yylno);
	/* The symbols being reduced.  */
	for (yyi = 0; yyi < yynrhs; yyi++) {
		YYFPRINTF(stderr, "   $%d = ", yyi + 1);
		yy_symbol_print(stderr, yystos[yyssp[yyi + 1 - yynrhs]], &yyvsp[(yyi + 1) - (yynrhs)]
		    );
		YYFPRINTF(stderr, "\n");
	}
}

#define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HLYDEBUG */
#define YYDPRINTF(Args)
#define YY_SYMBOL_PRINT(Title, Type, Value, Location)
#define YY_STACK_PRINT(Bottom, Top)
#define YY_REDUCE_PRINT(Rule)
#endif /* !HLYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

#if YYERROR_VERBOSE

#ifndef yystrlen
#if defined __GLIBC__ && defined _STRING_H
#define yystrlen strlen
#else
/* Return the length of YYSTR.  */
static YYSIZE_T yystrlen(const char *yystr)
{
	YYSIZE_T yylen;
	for (yylen = 0; yystr[yylen]; yylen++)
		continue;
	return yylen;
}
#endif
#endif

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
static YYSIZE_T yytnamerr(char *yyres, const char *yystr)
{
	if (*yystr == '"') {
		YYSIZE_T yyn = 0;
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
		return yystrlen(yystr);

	return (YYSIZE_T) (yystpcpy(yyres, yystr) - yyres);
}
#endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int yysyntax_error(YYSIZE_T * yymsg_alloc, char **yymsg, yytype_int16 * yyssp, int yytoken)
{
	YYSIZE_T yysize0 = yytnamerr(YY_NULLPTR, yytname[yytoken]);
	YYSIZE_T yysize = yysize0;
	enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
	/* Internationalized format string. */
	const char *yyformat = YY_NULLPTR;
	/* Arguments of yyformat. */
	char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	/* Number of reported tokens (one for the "unexpected", one per
	   "expected"). */
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
		int yyn = yypact[*yyssp];
		yyarg[yycount++] = yytname[yytoken];
		if (!yypact_value_is_default(yyn)) {
			/* Start YYX at -YYN if negative to avoid negative indexes in
			   YYCHECK.  In other words, skip the first -YYN actions for
			   this state because they are default actions.  */
			int yyxbegin = yyn < 0 ? -yyn : 0;
			/* Stay within bounds of both yycheck and yytname.  */
			int yychecklim = YYLAST - yyn + 1;
			int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
			int yyx;

			for (yyx = yyxbegin; yyx < yyxend; ++yyx)
				if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR && !yytable_value_is_error(yytable[yyx + yyn])) {
					if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM) {
						yycount = 1;
						yysize = yysize0;
						break;
					}
					yyarg[yycount++] = yytname[yyx];
					{
						YYSIZE_T yysize1 = yysize + yytnamerr(YY_NULLPTR, yytname[yyx]);
						if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
							yysize = yysize1;
						else
							return 2;
					}
				}
		}
	}

	switch (yycount) {
#define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
	default:		/* Avoid compiler warnings. */
		YYCASE_(0, YY_("syntax error"));
		YYCASE_(1, YY_("syntax error, unexpected %s"));
		YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
		YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
		YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
		YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
	}

	{
		YYSIZE_T yysize1 = yysize + yystrlen(yyformat);
		if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
			yysize = yysize1;
		else
			return 2;
	}

	if (*yymsg_alloc < yysize) {
		*yymsg_alloc = 2 * yysize;
		if (!(yysize <= *yymsg_alloc && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
			*yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
		return 1;
	}

	/* Avoid sprintf, as that infringes on the user's name space.
	   Don't have undefined behavior even if the translation
	   produced a string with the wrong number of "%s"s.  */
	{
		char *yyp = *yymsg;
		int yyi = 0;
		while ((*yyp = *yyformat) != '\0')
			if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount) {
				yyp += yytnamerr(yyp, yyarg[yyi++]);
				yyformat += 2;
			} else {
				yyp++;
				yyformat++;
			}
	}
	return 0;
}
#endif /* YYERROR_VERBOSE */

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

/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;

/*----------.
| yyparse.  |
`----------*/

int yyparse(void)
{
	int yystate;
	/* Number of tokens to shift before error messages enabled.  */
	int yyerrstatus;

	/* The stacks and their tools:
	   'yyss': related to states.
	   'yyvs': related to semantic values.

	   Refer to the stacks through separate pointers, to allow yyoverflow
	   to reallocate them elsewhere.  */

	/* The state stack.  */
	yytype_int16 yyssa[YYINITDEPTH];
	yytype_int16 *yyss;
	yytype_int16 *yyssp;

	/* The semantic value stack.  */
	YYSTYPE yyvsa[YYINITDEPTH];
	YYSTYPE *yyvs;
	YYSTYPE *yyvsp;

	YYSIZE_T yystacksize;

	int yyn;
	int yyresult;
	/* Lookahead token as an internal (translated) token number.  */
	int yytoken = 0;
	/* The variables used to return semantic value and location from the
	   action routines.  */
	YYSTYPE yyval;

#if YYERROR_VERBOSE
	/* Buffer for error messages, and its allocated size.  */
	char yymsgbuf[128];
	char *yymsg = yymsgbuf;
	YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

	/* The number of symbols on the RHS of the reduced rule.
	   Keep to zero when no symbol should be popped.  */
	int yylen = 0;

	yyssp = yyss = yyssa;
	yyvsp = yyvs = yyvsa;
	yystacksize = YYINITDEPTH;

	YYDPRINTF((stderr, "Starting parse\n"));

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;	/* Cause a token to be read.  */
	goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
	/* In all cases, when you get here, the value and location stacks
	   have just been pushed.  So pushing a state here evens the stacks.  */
	yyssp++;

/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
	*yyssp = (yytype_int16) yystate;

	if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
		goto yyexhaustedlab;
#else
	{
		/* Get the current used size of the three stacks, in elements.  */
		YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

#if defined yyoverflow
		{
			/* Give user a chance to reallocate the stack.  Use copies of
			   these so that the &'s don't force the real ones into
			   memory.  */
			YYSTYPE *yyvs1 = yyvs;
			yytype_int16 *yyss1 = yyss;

			/* Each stack pointer address is followed by the size of the
			   data in use in that stack, in bytes.  This used to be a
			   conditional around just the two extra args, but that might
			   be undefined if yyoverflow is a macro.  */
			yyoverflow(YY_("memory exhausted"),
				   &yyss1, yysize * sizeof(*yyssp), &yyvs1, yysize * sizeof(*yyvsp), &yystacksize);
			yyss = yyss1;
			yyvs = yyvs1;
		}
#else /* defined YYSTACK_RELOCATE */
		/* Extend the stack our own way.  */
		if (YYMAXDEPTH <= yystacksize)
			goto yyexhaustedlab;
		yystacksize *= 2;
		if (YYMAXDEPTH < yystacksize)
			yystacksize = YYMAXDEPTH;

		{
			yytype_int16 *yyss1 = yyss;
			union yyalloc *yyptr = (union yyalloc *)YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
			if (!yyptr)
				goto yyexhaustedlab;
			YYSTACK_RELOCATE(yyss_alloc, yyss);
			YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#undef YYSTACK_RELOCATE
			if (yyss1 != yyssa)
				YYSTACK_FREE(yyss1);
		}
#endif

		yyssp = yyss + yysize - 1;
		yyvsp = yyvs + yysize - 1;

		YYDPRINTF((stderr, "Stack size increased to %lu\n", (unsigned long)yystacksize));

		if (yyss + yystacksize - 1 <= yyssp)
			YYABORT;
	}
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

	YYDPRINTF((stderr, "Entering state %d\n", yystate));

	if (yystate == YYFINAL)
		YYACCEPT;

	goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:
	/* Do appropriate processing given the current state.  Read a
	   lookahead token if we need one and don't already have one.  */

	/* First try to decide what to do without reference to lookahead token.  */
	yyn = yypact[yystate];
	if (yypact_value_is_default(yyn))
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
	if (yychar == YYEMPTY) {
		YYDPRINTF((stderr, "Reading a token: "));
		yychar = yylex();
	}

	if (yychar <= YYEOF) {
		yychar = yytoken = YYEOF;
		YYDPRINTF((stderr, "Now at end of input.\n"));
	} else {
		yytoken = YYTRANSLATE(yychar);
		YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
	}

	/* If the proper action on seeing token YYTOKEN is to reduce or to
	   detect an error, take that action.  */
	yyn += yytoken;
	if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
		goto yydefault;
	yyn = yytable[yyn];
	if (yyn <= 0) {
		if (yytable_value_is_error(yyn))
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}

	/* Count tokens shifted since error; after three, turn off error
	   status.  */
	if (yyerrstatus)
		yyerrstatus--;

	/* Shift the lookahead token.  */
	YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

	/* Discard the shifted token.  */
	yychar = YYEMPTY;

	yystate = yyn;
	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN * ++yyvsp = yylval;
	YY_IGNORE_MAYBE_UNINITIALIZED_END goto yynewstate;

/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;
	goto yyreduce;

/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
	/* yyn is the number of a rule to reduce with.  */
	yylen = yyr2[yyn];

	/* If YYLEN is nonzero, implement the default value of the action:
	   '$$ = $1'.

	   Otherwise, the following line sets YYVAL to garbage.
	   This behavior is undocumented and Bison
	   users should not rely upon it.  Assigning to YYVAL
	   unconditionally makes the parser a bit smaller, and it avoids a
	   GCC warning that YYVAL may be used uninitialized.  */
	yyval = yyvsp[1 - yylen];

	YY_REDUCE_PRINT(yyn);
	switch (yyn) {
	case 6:
#line 278 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1610 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 7:
#line 283 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1616 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 8:
#line 284 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_err()) {
				YYERROR;
			}
		}
#line 1622 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 9:
#line 299 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_data((yyvsp[0].string));
		}
#line 1628 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 10:
#line 300 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rbr();
		}
#line 1634 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 11:
#line 300 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ebr();
		}
#line 1640 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 12:
#line 301 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rbr();
		}
#line 1646 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 13:
#line 301 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ebr();
		}
#line 1652 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 14:
#line 302 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_efont();
		}
#line 1658 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 15:
#line 303 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ei();
		}
#line 1664 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 16:
#line 304 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eb();
		}
#line 1670 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 17:
#line 305 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eu();
		}
#line 1676 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 18:
#line 306 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eo();
		}
#line 1682 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 19:
#line 307 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rsub();
		}
#line 1688 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 20:
#line 307 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_esub();
		}
#line 1694 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 21:
#line 308 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rsup();
		}
#line 1700 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 22:
#line 308 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_esup();
		}
#line 1706 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 23:
#line 309 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rs();
		}
#line 1712 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 24:
#line 309 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_es();
		}
#line 1718 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 26:
#line 324 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_efont();
		}
#line 1724 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 27:
#line 325 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ei();
		}
#line 1730 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 28:
#line 326 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eb();
		}
#line 1736 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 29:
#line 327 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eu();
		}
#line 1742 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 30:
#line 328 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eo();
		}
#line 1748 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 31:
#line 332 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rfont();
		}
#line 1754 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 33:
#line 336 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ri();
		}
#line 1760 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 34:
#line 340 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ro();
		}
#line 1766 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 35:
#line 344 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rb();
		}
#line 1772 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 36:
#line 348 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_ru();
		}
#line 1778 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 37:
#line 353 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_tabledata((yyvsp[0].string));
		}
#line 1784 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 39:
#line 359 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rtable();
		}
#line 1790 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 40:
#line 359 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_etable();
		}
#line 1796 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 43:
#line 366 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rhr();
		}
#line 1802 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 45:
#line 367 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rhr();
		}
#line 1808 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 47:
#line 372 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rtr();
		}
#line 1814 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 48:
#line 372 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_etr();
		}
#line 1820 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 51:
#line 379 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rvr();
		}
#line 1826 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 53:
#line 380 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rvr();
		}
#line 1832 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 55:
#line 388 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_etd(0);
		}
#line 1838 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 56:
#line 389 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eimg();
			dphl_etd(1);
		}
#line 1844 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 57:
#line 390 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_eimg();
			dphl_etd(1);
		}
#line 1850 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 58:
#line 391 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_etd(2);
		}
#line 1856 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 59:
#line 395 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rimg();
		}
#line 1862 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 60:
#line 399 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_rtd();
		}
#line 1868 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 63:
#line 431 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_align((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1874 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 64:
#line 432 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_bgcolor((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1880 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 65:
#line 433 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_border((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1886 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 66:
#line 434 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_cellborder((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 1892 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 67:
#line 435 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_cellpadding((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1898 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 68:
#line 436 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_cellspacing((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1904 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 69:
#line 437 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_color((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1910 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 70:
#line 438 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_columns((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 1916 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 71:
#line 439 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_fixedsize((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1922 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 72:
#line 440 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_gradientangle((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1928 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 73:
#line 441 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_height((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1934 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 74:
#line 442 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_href((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1940 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 75:
#line 443 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_id((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1946 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 76:
#line 444 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_port((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1952 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 77:
#line 445 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_rows((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 1958 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 78:
#line 446 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_sides((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1964 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 79:
#line 447 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_style((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1970 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 80:
#line 448 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_target((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1976 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 81:
#line 449 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_title((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1982 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 82:
#line 450 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_title((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1988 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 83:
#line 451 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_valign((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 1994 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 84:
#line 452 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_width((yyvsp[0].string), T_TABLE)) {
				YYERROR;
			}
		}
#line 2000 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 85:
#line 453 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_attr_huh("<table>", (yyvsp[-2].string), (yyvsp[0].string));
		}
#line 2006 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 88:
#line 485 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_align((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2012 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 89:
#line 486 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_balign((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2018 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 90:
#line 487 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_bgcolor((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2024 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 91:
#line 488 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_border((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2030 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 92:
#line 489 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_cellpadding((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2036 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 93:
#line 490 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_cellspacing((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2042 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 94:
#line 491 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_color((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2048 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 95:
#line 492 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_colspan((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2054 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 96:
#line 493 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_fixedsize((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2060 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 97:
#line 494 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_gradientangle((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2066 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 98:
#line 495 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_height((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2072 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 99:
#line 496 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_href((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2078 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 100:
#line 497 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_id((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2084 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 101:
#line 498 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_port((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2090 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 102:
#line 499 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_rowspan((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2096 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 103:
#line 500 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_sides((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2102 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 104:
#line 501 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_sides((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2108 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 105:
#line 502 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_target((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2114 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 106:
#line 503 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_title((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2120 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 107:
#line 504 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_title((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2126 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 108:
#line 505 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_valign((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2132 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 109:
#line 506 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_width((yyvsp[0].string), T_TD)) {
				YYERROR;
			}
		}
#line 2138 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 110:
#line 507 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_attr_huh("<td>", (yyvsp[-2].string), (yyvsp[0].string));
		}
#line 2144 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 113:
#line 521 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_scale((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2150 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 114:
#line 522 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_src((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2156 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 115:
#line 523 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_attr_huh("<img>", (yyvsp[-2].string), (yyvsp[0].string));
		}
#line 2162 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 118:
#line 535 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_align((yyvsp[0].string), T_BR)) {
				YYERROR;
			}
		}
#line 2168 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 119:
#line 536 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_attr_huh("<br>", (yyvsp[-2].string), (yyvsp[0].string));
		}
#line 2174 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 122:
#line 550 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_color((yyvsp[0].string), T_FONT)) {
				YYERROR;
			}
		}
#line 2180 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 123:
#line 551 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_face((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2186 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 124:
#line 552 "dphl.y"		/* yacc.c:1652  */
		{
			if (dphl_chk_pointsize((yyvsp[0].string))) {
				YYERROR;
			}
		}
#line 2192 "dphlparser.c"	/* yacc.c:1652  */
		break;

	case 125:
#line 553 "dphl.y"		/* yacc.c:1652  */
		{
			dphl_attr_huh("<font>", (yyvsp[-2].string), (yyvsp[0].string));
		}
#line 2198 "dphlparser.c"	/* yacc.c:1652  */
		break;

#line 2202 "dphlparser.c"	/* yacc.c:1652  */
	default:
		break;
	}
	/* User semantic actions sometimes alter yychar, and that requires
	   that yytoken be updated with the new translation.  We take the
	   approach of translating immediately before every use of yytoken.
	   One alternative is translating here after every semantic action,
	   but that translation would be missed if the semantic action invokes
	   YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
	   if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
	   incorrect destructor might then be invoked immediately.  In the
	   case of YYERROR or YYBACKUP, subsequent parser actions might lead
	   to an incorrect destructor call or verbose syntax error message
	   before the lookahead is translated.  */
	YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

	YYPOPSTACK(yylen);
	yylen = 0;
	YY_STACK_PRINT(yyss, yyssp);

	*++yyvsp = yyval;

	/* Now 'shift' the result of the reduction.  Determine what state
	   that goes to, based on the state we popped back to and the rule
	   number reduced by.  */
	{
		const int yylhs = yyr1[yyn] - YYNTOKENS;
		const int yyi = yypgoto[yylhs] + *yyssp;
		yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp ? yytable[yyi]
			   : yydefgoto[yylhs]);
	}

	goto yynewstate;

/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
	/* Make sure we have latest lookahead translation.  See comments at
	   user semantic actions for why this is necessary.  */
	yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE(yychar);

	/* If not already recovering from an error, report this error.  */
	if (!yyerrstatus) {
		++yynerrs;
#if ! YYERROR_VERBOSE
		yyerror(YY_("syntax error"));
#else
#define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
		{
			char const *yymsgp = YY_("syntax error");
			int yysyntax_error_status;
			yysyntax_error_status = YYSYNTAX_ERROR;
			if (yysyntax_error_status == 0)
				yymsgp = yymsg;
			else if (yysyntax_error_status == 1) {
				if (yymsg != yymsgbuf)
					YYSTACK_FREE(yymsg);
				yymsg = (char *)YYSTACK_ALLOC(yymsg_alloc);
				if (!yymsg) {
					yymsg = yymsgbuf;
					yymsg_alloc = sizeof yymsgbuf;
					yysyntax_error_status = 2;
				} else {
					yysyntax_error_status = YYSYNTAX_ERROR;
					yymsgp = yymsg;
				}
			}
			yyerror(yymsgp);
			if (yysyntax_error_status == 2)
				goto yyexhaustedlab;
		}
#undef YYSYNTAX_ERROR
#endif
	}

	if (yyerrstatus == 3) {
		/* If just tried and failed to reuse lookahead token after an
		   error, discard it.  */

		if (yychar <= YYEOF) {
			/* Return failure if at end of input.  */
			if (yychar == YYEOF)
				YYABORT;
		} else {
			yydestruct("Error: discarding", yytoken, &yylval);
			yychar = YYEMPTY;
		}
	}

	/* Else will try to reuse lookahead token after shifting the error
	   token.  */
	goto yyerrlab1;

/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
	/* Pacify compilers when the user code never invokes YYERROR and the
	   label yyerrorlab therefore never appears in user code.  */
	if (0)
		YYERROR;

	/* Do not reclaim the symbols of the rule whose action triggered
	   this YYERROR.  */
	YYPOPSTACK(yylen);
	yylen = 0;
	YY_STACK_PRINT(yyss, yyssp);
	yystate = *yyssp;
	goto yyerrlab1;

/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
	yyerrstatus = 3;	/* Each real token shifted decrements this.  */

	for (;;) {
		yyn = yypact[yystate];
		if (!yypact_value_is_default(yyn)) {
			yyn += YYTERROR;
			if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR) {
				yyn = yytable[yyn];
				if (0 < yyn)
					break;
			}
		}

		/* Pop the current state because it cannot handle the error token.  */
		if (yyssp == yyss)
			YYABORT;

		yydestruct("Error: popping", yystos[yystate], yyvsp);
		YYPOPSTACK(1);
		yystate = *yyssp;
		YY_STACK_PRINT(yyss, yyssp);
	}

	YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN * ++yyvsp = yylval;
	YY_IGNORE_MAYBE_UNINITIALIZED_END
	    /* Shift the error token.  */
	    YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

	yystate = yyn;
	goto yynewstate;

/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
	yyresult = 0;
	goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
	yyresult = 1;
	goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
	yyerror(YY_("memory exhausted"));
	yyresult = 2;
	/* Fall through.  */
#endif

/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
	if (yychar != YYEMPTY) {
		/* Make sure we have latest lookahead translation.  See comments at
		   user semantic actions for why this is necessary.  */
		yytoken = YYTRANSLATE(yychar);
		yydestruct("Cleanup: discarding lookahead", yytoken, &yylval);
	}
	/* Do not reclaim the symbols of the rule whose action triggered
	   this YYABORT or YYACCEPT.  */
	YYPOPSTACK(yylen);
	YY_STACK_PRINT(yyss, yyssp);
	while (yyssp != yyss) {
		yydestruct("Cleanup: popping", yystos[*yyssp], yyvsp);
		YYPOPSTACK(1);
	}
#ifndef yyoverflow
	if (yyss != yyssa)
		YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
	if (yymsg != yymsgbuf)
		YYSTACK_FREE(yymsg);
#endif
	return yyresult;
}

#line 556 "dphl.y"		/* yacc.c:1918  */

/* end */
