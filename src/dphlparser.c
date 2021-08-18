/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

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
#line 77 "dphl.y"


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


#line 156 "dphlparser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "dphlparser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_HL_DATA = 3,                    /* "stringdata"  */
  YYSYMBOL_HL_HTML = 4,                    /* "<html"  */
  YYSYMBOL_HL_C_HTML = 5,                  /* "</html"  */
  YYSYMBOL_HL_B = 6,                       /* "<b"  */
  YYSYMBOL_HL_C_B = 7,                     /* "</b"  */
  YYSYMBOL_HL_BR = 8,                      /* "<br"  */
  YYSYMBOL_HL_C_BR = 9,                    /* "</br"  */
  YYSYMBOL_HL_FONT = 10,                   /* "<font"  */
  YYSYMBOL_HL_C_FONT = 11,                 /* "</font"  */
  YYSYMBOL_HL_HR = 12,                     /* "<hr"  */
  YYSYMBOL_HL_C_HR = 13,                   /* "</hr"  */
  YYSYMBOL_HL_I = 14,                      /* "<i"  */
  YYSYMBOL_HL_C_I = 15,                    /* "</i"  */
  YYSYMBOL_HL_IMG = 16,                    /* "<img"  */
  YYSYMBOL_HL_C_IMG = 17,                  /* "</img"  */
  YYSYMBOL_HL_O = 18,                      /* "<o"  */
  YYSYMBOL_HL_C_O = 19,                    /* "</o"  */
  YYSYMBOL_HL_S = 20,                      /* "<s"  */
  YYSYMBOL_HL_C_S = 21,                    /* "</s"  */
  YYSYMBOL_HL_SUB = 22,                    /* "<sub"  */
  YYSYMBOL_HL_C_SUB = 23,                  /* "</sub"  */
  YYSYMBOL_HL_SUP = 24,                    /* "<sup"  */
  YYSYMBOL_HL_C_SUP = 25,                  /* "</sup"  */
  YYSYMBOL_HL_TABLE = 26,                  /* "<table"  */
  YYSYMBOL_HL_C_TABLE = 27,                /* "</table"  */
  YYSYMBOL_HL_TD = 28,                     /* "<td"  */
  YYSYMBOL_HL_C_TD = 29,                   /* "</td"  */
  YYSYMBOL_HL_TR = 30,                     /* "<tr"  */
  YYSYMBOL_HL_C_TR = 31,                   /* "</tr"  */
  YYSYMBOL_HL_U = 32,                      /* "<u"  */
  YYSYMBOL_HL_C_U = 33,                    /* "</u"  */
  YYSYMBOL_HL_VR = 34,                     /* "<vr"  */
  YYSYMBOL_HL_C_VR = 35,                   /* "</vr"  */
  YYSYMBOL_HL_SC = 36,                     /* "/>"  */
  YYSYMBOL_HL_C = 37,                      /* ">"  */
  YYSYMBOL_HL_IS = 38,                     /* "="  */
  YYSYMBOL_HL_QSTR = 39,                   /* "string"  */
  YYSYMBOL_HL_STR = 40,                    /* "text"  */
  YYSYMBOL_HL_ALIGN = 41,                  /* "align"  */
  YYSYMBOL_HL_BALIGN = 42,                 /* "balign"  */
  YYSYMBOL_HL_BGCOLOR = 43,                /* "bgcolor"  */
  YYSYMBOL_HL_BORDER = 44,                 /* "border"  */
  YYSYMBOL_HL_CELLBORDER = 45,             /* "cellborder"  */
  YYSYMBOL_HL_CELLPADDING = 46,            /* "cellpadding"  */
  YYSYMBOL_HL_CELLSPACING = 47,            /* "cellspacing"  */
  YYSYMBOL_HL_COLOR = 48,                  /* "color"  */
  YYSYMBOL_HL_COLUMNS = 49,                /* "columns"  */
  YYSYMBOL_HL_COLSPAN = 50,                /* "colspan"  */
  YYSYMBOL_HL_FACE = 51,                   /* "face"  */
  YYSYMBOL_HL_FIXEDSIZE = 52,              /* "fixedsize"  */
  YYSYMBOL_HL_GRADIENTANGLE = 53,          /* "gradientangle"  */
  YYSYMBOL_HL_HEIGHT = 54,                 /* "height"  */
  YYSYMBOL_HL_HREF = 55,                   /* "href"  */
  YYSYMBOL_HL_ID = 56,                     /* "id"  */
  YYSYMBOL_HL_PORT = 57,                   /* "port"  */
  YYSYMBOL_HL_POINTSIZE = 58,              /* "point-size"  */
  YYSYMBOL_HL_ROWS = 59,                   /* "rows"  */
  YYSYMBOL_HL_ROWSPAN = 60,                /* "rowspan"  */
  YYSYMBOL_HL_SCALE = 61,                  /* "scale"  */
  YYSYMBOL_HL_SIDES = 62,                  /* "sides"  */
  YYSYMBOL_HL_SRC = 63,                    /* "src"  */
  YYSYMBOL_HL_STYLE = 64,                  /* "style"  */
  YYSYMBOL_HL_TARGET = 65,                 /* "target"  */
  YYSYMBOL_HL_TITLE = 66,                  /* "title"  */
  YYSYMBOL_HL_TOOLTIP = 67,                /* "tooltip"  */
  YYSYMBOL_HL_VALIGN = 68,                 /* "valign"  */
  YYSYMBOL_HL_WIDTH = 69,                  /* "width"  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_begin = 71,                     /* begin  */
  YYSYMBOL_htmlparser = 72,                /* htmlparser  */
  YYSYMBOL_htmlparser2 = 73,               /* htmlparser2  */
  YYSYMBOL_items = 74,                     /* items  */
  YYSYMBOL_item = 75,                      /* item  */
  YYSYMBOL_76_1 = 76,                      /* $@1  */
  YYSYMBOL_77_2 = 77,                      /* $@2  */
  YYSYMBOL_78_3 = 78,                      /* $@3  */
  YYSYMBOL_79_4 = 79,                      /* $@4  */
  YYSYMBOL_80_5 = 80,                      /* $@5  */
  YYSYMBOL_fonttab2 = 81,                  /* fonttab2  */
  YYSYMBOL_font = 82,                      /* font  */
  YYSYMBOL_83_6 = 83,                      /* $@6  */
  YYSYMBOL_italic = 84,                    /* italic  */
  YYSYMBOL_overline = 85,                  /* overline  */
  YYSYMBOL_bold = 86,                      /* bold  */
  YYSYMBOL_underline = 87,                 /* underline  */
  YYSYMBOL_tabe = 88,                      /* tabe  */
  YYSYMBOL_tab = 89,                       /* tab  */
  YYSYMBOL_90_7 = 90,                      /* $@7  */
  YYSYMBOL_rows = 91,                      /* rows  */
  YYSYMBOL_92_8 = 92,                      /* $@8  */
  YYSYMBOL_93_9 = 93,                      /* $@9  */
  YYSYMBOL_row = 94,                       /* row  */
  YYSYMBOL_95_10 = 95,                     /* $@10  */
  YYSYMBOL_cells = 96,                     /* cells  */
  YYSYMBOL_97_11 = 97,                     /* $@11  */
  YYSYMBOL_98_12 = 98,                     /* $@12  */
  YYSYMBOL_cell = 99,                      /* cell  */
  YYSYMBOL_cellimg = 100,                  /* cellimg  */
  YYSYMBOL_celltd = 101,                   /* celltd  */
  YYSYMBOL_table_arg = 102,                /* table_arg  */
  YYSYMBOL_table_1arg = 103,               /* table_1arg  */
  YYSYMBOL_td_arg = 104,                   /* td_arg  */
  YYSYMBOL_td_1arg = 105,                  /* td_1arg  */
  YYSYMBOL_img_arg = 106,                  /* img_arg  */
  YYSYMBOL_img_1arg = 107,                 /* img_1arg  */
  YYSYMBOL_br_arg = 108,                   /* br_arg  */
  YYSYMBOL_br_1arg = 109,                  /* br_1arg  */
  YYSYMBOL_font_arg = 110,                 /* font_arg  */
  YYSYMBOL_font_1arg = 111                 /* font_1arg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
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
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HLYSTYPE_IS_TRIVIAL && HLYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if HLYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   275,   275,   280,   281,   286,   287,   292,   293,   308,
     309,   309,   310,   310,   311,   312,   313,   314,   315,   316,
     316,   317,   317,   318,   318,   332,   333,   334,   335,   336,
     337,   341,   341,   345,   349,   353,   357,   362,   363,   368,
     368,   373,   374,   375,   375,   376,   376,   381,   381,   386,
     387,   388,   388,   389,   389,   397,   398,   399,   400,   404,
     408,   435,   436,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   453,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   489,   490,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   525,   526,   530,   531,   532,   539,   540,   544,   545,
     554,   555,   559,   560,   561,   562
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if HLYDEBUG || 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"stringdata\"",
  "\"<html\"", "\"</html\"", "\"<b\"", "\"</b\"", "\"<br\"", "\"</br\"",
  "\"<font\"", "\"</font\"", "\"<hr\"", "\"</hr\"", "\"<i\"", "\"</i\"",
  "\"<img\"", "\"</img\"", "\"<o\"", "\"</o\"", "\"<s\"", "\"</s\"",
  "\"<sub\"", "\"</sub\"", "\"<sup\"", "\"</sup\"", "\"<table\"",
  "\"</table\"", "\"<td\"", "\"</td\"", "\"<tr\"", "\"</tr\"", "\"<u\"",
  "\"</u\"", "\"<vr\"", "\"</vr\"", "\"/>\"", "\">\"", "\"=\"",
  "\"string\"", "\"text\"", "\"align\"", "\"balign\"", "\"bgcolor\"",
  "\"border\"", "\"cellborder\"", "\"cellpadding\"", "\"cellspacing\"",
  "\"color\"", "\"columns\"", "\"colspan\"", "\"face\"", "\"fixedsize\"",
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

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
#endif

#define YYPACT_NINF (-198)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-38)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     171,   -18,   -20,    -2,     6,  -198,     8,     9,    11,    12,
      17,    18,    37,  -198,  -198,   326,  -198,  -198,   349,   349,
     349,   349,   349,    33,  -198,   349,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   326,
     326,   326,   326,   326,   191,    52,   221,    54,   241,    46,
     261,    60,    50,    38,  -198,    68,    66,    21,   132,   326,
     326,   326,    39,    43,    49,    57,    58,    65,    70,    78,
      79,    85,  -198,    89,    91,  -198,    97,    98,  -198,  -198,
     102,   111,   113,   117,  -198,   274,   294,   317,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,    44,  -198,
    -198,   118,   120,   122,   124,   128,   131,   134,   141,   145,
     135,   146,   148,   149,   150,   154,   158,   160,   162,   166,
     168,   169,   170,   172,   174,   176,   178,   179,   187,   188,
     190,   192,   194,   195,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,   197,   126,  -198,   198,   199,   201,
     203,   207,   209,   211,   213,   215,   217,   218,   219,   223,
     227,   231,   233,   235,   237,   239,   247,   248,   250,   251,
    -198,   -16,   254,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,   271,  -198,   288,
     300,  -198,   -12,  -198,  -198,   135,   268,  -198,  -198,   270,
     -13,  -198,    77,  -198,  -198,  -198,  -198,   275,   144,   273,
     277,   281,   283,   284,   286,   290,   292,   295,   305,   307,
     309,   313,   315,   316,   318,   322,   323,   324,   327,   328,
     330,   332,  -198,   135,   271,   272,  -198,   276,   335,  -198,
     299,   333,   340,   341,   343,   344,   345,   346,   347,   348,
     350,   351,   352,   353,   354,   355,   357,   358,   359,   360,
     361,   362,   363,  -198,  -198,  -198,  -198,   366,   -22,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,   271,  -198,   375,   371,   367,   368,   369,  -198,
    -198,   372,   373,   374,   376,   377,  -198,   379,  -198,  -198,
    -198,   380,  -198
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      38,     9,     0,     0,    10,    31,     0,     0,     0,     0,
       0,     0,     0,     2,     4,     5,     8,     6,    38,    38,
      38,    38,    38,     0,    25,    38,    35,    12,   117,   121,
      33,    34,    23,    19,    21,    36,     1,     9,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,     0,    11,     0,     0,   116,    32,
       0,     0,     0,     0,   120,     0,     0,     0,    14,    26,
      15,    27,    18,    30,    16,    28,    17,    29,     0,     3,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,   119,   118,   125,   122,   123,
     124,    24,    20,    22,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    42,    85,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     0,    43,     0,
      38,    60,     0,    49,    87,     0,     0,    37,    40,     0,
       0,    50,     0,    44,    45,    48,    51,     0,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,    59,     0,     0,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    52,    53,    58,     0,     0,   110,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,     0,    55,     0,     0,     0,     0,     0,   111,
      54,     0,     0,     0,     0,     0,    56,     0,   115,   113,
     114,     0,    57
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,   177,   386,    -9,    -8,  -198,  -198,  -198,  -198,
    -198,  -198,     0,  -198,     1,     2,     3,     4,   212,   356,
    -198,  -198,  -198,  -198,  -139,  -198,  -198,  -198,  -198,  -197,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    28,    56,    60,    61,
      59,    17,    39,    29,    40,    41,    42,    43,    23,    24,
      72,   145,   205,   243,   146,   197,   202,   244,   302,   203,
     249,   204,    98,   134,   212,   242,   278,   309,    57,    78,
      58,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,    19,    20,    21,    22,   211,   173,    38,   -37,    44,
      46,    48,    50,    52,   304,   305,   201,    25,   306,   209,
     198,   199,   210,   216,   217,    18,    19,    20,    21,    22,
      44,    46,    48,    50,    52,    26,    38,    36,    38,   307,
      38,   308,    38,    27,    38,    30,    31,   274,    32,    33,
      85,    86,    87,    37,    34,    35,     3,    75,     4,    54,
       5,    76,    77,    63,     6,    67,   213,    69,     7,    65,
       8,    71,     9,    73,    10,    74,    88,    38,    38,    38,
      89,   110,    11,    70,   111,   112,    90,   113,   114,   115,
     116,   117,   118,   119,    91,    92,   120,   121,   122,   123,
     124,   125,    93,   126,   273,   310,   127,    94,   128,   129,
     130,   131,   132,   133,   218,    95,    96,   219,   220,   221,
     222,   223,    97,   224,   225,   226,    99,   227,   100,   228,
     229,   230,   231,   232,   233,   101,   102,   234,   171,   235,
     103,   236,   237,   238,   239,   240,   241,     1,     2,   104,
       3,   105,     4,   172,     5,   106,   144,   135,     6,   136,
     246,   137,     7,   138,     8,   144,     9,   139,    10,    79,
     140,   141,    80,   247,     1,     2,    11,     3,   142,     4,
      81,     5,   143,    82,   147,     6,   148,   149,   150,     7,
      83,     8,   151,     9,    37,    10,   152,     3,   153,     4,
     154,     5,    62,    11,   155,     6,   156,   157,   158,     7,
     159,     8,   160,     9,   161,    10,   162,   163,    18,    19,
      20,    21,    22,    11,    37,   164,   165,     3,   166,     4,
     167,     5,   168,   169,   170,     6,    64,   174,   175,     7,
     176,     8,   177,     9,    37,    10,   178,     3,   179,     4,
     180,     5,   181,    11,   182,     6,   183,   184,   185,     7,
      66,     8,   186,     9,    37,    10,   187,     3,    68,     4,
     188,     5,   189,    11,   190,     6,   191,    37,   192,     7,
       3,     8,     4,     9,     5,    10,   193,   194,     6,   195,
     196,   200,     7,    11,     8,   107,     9,    37,    10,   201,
       3,   206,     4,   207,     5,   214,    11,   215,     6,   275,
     245,   250,     7,   276,     8,   251,     9,   108,    10,   252,
      37,   253,   254,     3,   255,     4,    11,     5,   256,    37,
     257,     6,     3,   258,     4,     7,     5,     8,   279,     9,
       6,    10,   109,   259,     7,   260,     8,   261,     9,    11,
      10,   262,     1,   263,   264,     3,   265,     4,    11,     5,
     266,   267,   268,     6,   277,   269,   270,     7,   271,     8,
     272,     9,   280,    10,    45,    47,    49,    51,    53,   281,
     282,    11,   283,   284,   285,   286,   287,   288,   312,   289,
     290,   291,   292,   293,   294,   248,   295,   296,   297,   298,
     299,   300,   301,   303,   311,   313,   314,   315,   321,   316,
     317,    55,   208,   318,     0,   319,   320,   322
};

static const yytype_int16 yycheck[] =
{
       0,     0,     0,     0,     0,   202,   145,    15,    26,    18,
      19,    20,    21,    22,    36,    37,    28,    37,    40,    31,
      36,    37,    34,    36,    37,    25,    25,    25,    25,    25,
      39,    40,    41,    42,    43,    37,    44,     0,    46,    61,
      48,    63,    50,    37,    52,    37,    37,   244,    37,    37,
      59,    60,    61,     3,    37,    37,     6,    36,     8,    26,
      10,    40,    41,    11,    14,    19,   205,     7,    18,    15,
      20,    33,    22,     5,    24,     9,    37,    85,    86,    87,
      37,    37,    32,    33,    40,    41,    37,    43,    44,    45,
      46,    47,    48,    49,    37,    37,    52,    53,    54,    55,
      56,    57,    37,    59,   243,   302,    62,    37,    64,    65,
      66,    67,    68,    69,    37,    37,    37,    40,    41,    42,
      43,    44,    37,    46,    47,    48,    37,    50,    37,    52,
      53,    54,    55,    56,    57,    38,    38,    60,    12,    62,
      38,    64,    65,    66,    67,    68,    69,     3,     4,    38,
       6,    38,     8,    27,    10,    38,    30,    39,    14,    39,
      16,    39,    18,    39,    20,    30,    22,    39,    24,    37,
      39,    37,    40,    29,     3,     4,    32,     6,    37,     8,
      48,    10,    37,    51,    38,    14,    38,    38,    38,    18,
      58,    20,    38,    22,     3,    24,    38,     6,    38,     8,
      38,    10,    11,    32,    38,    14,    38,    38,    38,    18,
      38,    20,    38,    22,    38,    24,    38,    38,   218,   218,
     218,   218,   218,    32,     3,    38,    38,     6,    38,     8,
      38,    10,    38,    38,    37,    14,    15,    39,    39,    18,
      39,    20,    39,    22,     3,    24,    39,     6,    39,     8,
      39,    10,    39,    32,    39,    14,    39,    39,    39,    18,
      19,    20,    39,    22,     3,    24,    39,     6,     7,     8,
      39,    10,    39,    32,    39,    14,    39,     3,    39,    18,
       6,    20,     8,    22,    10,    24,    39,    39,    14,    39,
      39,    37,    18,    32,    20,    21,    22,     3,    24,    28,
       6,    13,     8,     3,    10,    37,    32,    37,    14,    37,
      35,    38,    18,    37,    20,    38,    22,    23,    24,    38,
       3,    38,    38,     6,    38,     8,    32,    10,    38,     3,
      38,    14,     6,    38,     8,    18,    10,    20,    39,    22,
      14,    24,    25,    38,    18,    38,    20,    38,    22,    32,
      24,    38,     3,    38,    38,     6,    38,     8,    32,    10,
      38,    38,    38,    14,    29,    38,    38,    18,    38,    20,
      38,    22,    39,    24,    18,    19,    20,    21,    22,    39,
      39,    32,    39,    39,    39,    39,    39,    39,    17,    39,
      39,    39,    39,    39,    39,   218,    39,    39,    39,    39,
      39,    39,    39,    37,    29,    38,    38,    38,    29,    37,
      37,    25,   200,    39,    -1,    39,    39,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,     8,    10,    14,    18,    20,    22,
      24,    32,    71,    72,    73,    74,    75,    81,    82,    84,
      85,    86,    87,    88,    89,    37,    37,    37,    76,    83,
      37,    37,    37,    37,    37,    37,     0,     3,    75,    82,
      84,    85,    86,    87,    74,    89,    74,    89,    74,    89,
      74,    89,    74,    89,    26,    73,    77,   108,   110,    80,
      78,    79,    11,    11,    15,    15,    19,    19,     7,     7,
      33,    33,    90,     5,     9,    36,    40,    41,   109,    37,
      40,    48,    51,    58,   111,    74,    74,    74,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,   102,    37,
      37,    38,    38,    38,    38,    38,    38,    21,    23,    25,
      37,    40,    41,    43,    44,    45,    46,    47,    48,    49,
      52,    53,    54,    55,    56,    57,    59,    62,    64,    65,
      66,    67,    68,    69,   103,    39,    39,    39,    39,    39,
      39,    37,    37,    37,    30,    91,    94,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      37,    12,    27,    94,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    95,    36,    37,
      37,    28,    96,    99,   101,    92,    13,     3,    88,    31,
      34,    99,   104,    94,    37,    37,    36,    37,    37,    40,
      41,    42,    43,    44,    46,    47,    48,    50,    52,    53,
      54,    55,    56,    57,    60,    62,    64,    65,    66,    67,
      68,    69,   105,    93,    97,    35,    16,    29,    72,   100,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    94,    99,    37,    37,    29,   106,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    98,    37,    36,    37,    40,    61,    63,   107,
      99,    29,    17,    38,    38,    38,    37,    37,    39,    39,
      39,    29,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      76,    75,    77,    75,    75,    75,    75,    75,    75,    78,
      75,    79,    75,    80,    75,    81,    81,    81,    81,    81,
      81,    83,    82,    84,    85,    86,    87,    88,    88,    90,
      89,    91,    91,    92,    91,    93,    91,    95,    94,    96,
      96,    97,    96,    98,    96,    99,    99,    99,    99,   100,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   111,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     5,     1,     1,     1,     2,     1,     1,
       0,     4,     0,     5,     4,     4,     4,     4,     4,     0,
       6,     0,     6,     0,     6,     1,     4,     4,     4,     4,
       4,     0,     4,     2,     2,     2,     2,     1,     0,     0,
       9,     1,     2,     0,     5,     0,     7,     0,     6,     1,
       2,     0,     5,     0,     7,     6,     8,    10,     5,     1,
       1,     2,     0,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     0,     3,     3,     3,     2,     0,     3,     3,
       2,     0,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = HLYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == HLYEMPTY)                                        \
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

/* Backward compatibility with an undocumented macro.
   Use HLYerror or HLYUNDEF. */
#define YYERRCODE HLYUNDEF


/* Enable debugging if requested.  */
#if HLYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HLYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HLYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = HLYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == HLYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= HLYEOF)
    {
      yychar = HLYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == HLYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = HLYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = HLYEMPTY;
  goto yynewstate;


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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6: /* htmlparser2: fonttab2  */
#line 287 "dphl.y"
                   { if (dphl_chk_err ()) { YYERROR; } }
#line 1488 "dphlparser.c"
    break;

  case 7: /* items: items item  */
#line 292 "dphl.y"
                     { if (dphl_chk_err ()) { YYERROR; } }
#line 1494 "dphlparser.c"
    break;

  case 8: /* items: item  */
#line 293 "dphl.y"
               { if (dphl_chk_err ()) { YYERROR; } }
#line 1500 "dphlparser.c"
    break;

  case 9: /* item: "stringdata"  */
#line 308 "dphl.y"
                  { dphl_data ((yyvsp[0].string)); }
#line 1506 "dphlparser.c"
    break;

  case 10: /* $@1: %empty  */
#line 309 "dphl.y"
                { dphl_rbr(); }
#line 1512 "dphlparser.c"
    break;

  case 11: /* item: "<br" $@1 br_arg "/>"  */
#line 309 "dphl.y"
                                             { dphl_ebr (); }
#line 1518 "dphlparser.c"
    break;

  case 12: /* $@2: %empty  */
#line 310 "dphl.y"
                     { dphl_rbr(); }
#line 1524 "dphlparser.c"
    break;

  case 13: /* item: "<br" ">" $@2 "</br" ">"  */
#line 310 "dphl.y"
                                                  { dphl_ebr (); }
#line 1530 "dphlparser.c"
    break;

  case 14: /* item: font items "</font" ">"  */
#line 311 "dphl.y"
                                    { dphl_efont (); }
#line 1536 "dphlparser.c"
    break;

  case 15: /* item: italic items "</i" ">"  */
#line 312 "dphl.y"
                                   { dphl_ei (); }
#line 1542 "dphlparser.c"
    break;

  case 16: /* item: bold items "</b" ">"  */
#line 313 "dphl.y"
                                 { dphl_eb (); }
#line 1548 "dphlparser.c"
    break;

  case 17: /* item: underline items "</u" ">"  */
#line 314 "dphl.y"
                                      { dphl_eu (); }
#line 1554 "dphlparser.c"
    break;

  case 18: /* item: overline items "</o" ">"  */
#line 315 "dphl.y"
                                     { dphl_eo (); }
#line 1560 "dphlparser.c"
    break;

  case 19: /* $@3: %empty  */
#line 316 "dphl.y"
                      { dphl_rsub(); }
#line 1566 "dphlparser.c"
    break;

  case 20: /* item: "<sub" ">" $@3 items "</sub" ">"  */
#line 316 "dphl.y"
                                                           { dphl_esub (); }
#line 1572 "dphlparser.c"
    break;

  case 21: /* $@4: %empty  */
#line 317 "dphl.y"
                      { dphl_rsup(); }
#line 1578 "dphlparser.c"
    break;

  case 22: /* item: "<sup" ">" $@4 items "</sup" ">"  */
#line 317 "dphl.y"
                                                           { dphl_esup (); }
#line 1584 "dphlparser.c"
    break;

  case 23: /* $@5: %empty  */
#line 318 "dphl.y"
                    { dphl_rs(); }
#line 1590 "dphlparser.c"
    break;

  case 24: /* item: "<s" ">" $@5 items "</s" ">"  */
#line 318 "dphl.y"
                                                     { dphl_es (); }
#line 1596 "dphlparser.c"
    break;

  case 26: /* fonttab2: font tab "</font" ">"  */
#line 333 "dphl.y"
                                  { dphl_efont(); }
#line 1602 "dphlparser.c"
    break;

  case 27: /* fonttab2: italic tab "</i" ">"  */
#line 334 "dphl.y"
                                 { dphl_ei (); }
#line 1608 "dphlparser.c"
    break;

  case 28: /* fonttab2: bold tab "</b" ">"  */
#line 335 "dphl.y"
                               { dphl_eb (); }
#line 1614 "dphlparser.c"
    break;

  case 29: /* fonttab2: underline tab "</u" ">"  */
#line 336 "dphl.y"
                                    { dphl_eu (); }
#line 1620 "dphlparser.c"
    break;

  case 30: /* fonttab2: overline tab "</o" ">"  */
#line 337 "dphl.y"
                                   { dphl_eo (); }
#line 1626 "dphlparser.c"
    break;

  case 31: /* $@6: %empty  */
#line 341 "dphl.y"
                  { dphl_rfont(); }
#line 1632 "dphlparser.c"
    break;

  case 33: /* italic: "<i" ">"  */
#line 345 "dphl.y"
                    { dphl_ri(); }
#line 1638 "dphlparser.c"
    break;

  case 34: /* overline: "<o" ">"  */
#line 349 "dphl.y"
                    { dphl_ro(); }
#line 1644 "dphlparser.c"
    break;

  case 35: /* bold: "<b" ">"  */
#line 353 "dphl.y"
                    { dphl_rb(); }
#line 1650 "dphlparser.c"
    break;

  case 36: /* underline: "<u" ">"  */
#line 357 "dphl.y"
                    { dphl_ru(); }
#line 1656 "dphlparser.c"
    break;

  case 37: /* tabe: "stringdata"  */
#line 362 "dphl.y"
                  { dphl_tabledata ((yyvsp[0].string)); }
#line 1662 "dphlparser.c"
    break;

  case 39: /* $@7: %empty  */
#line 368 "dphl.y"
                        { dphl_rtable(); }
#line 1668 "dphlparser.c"
    break;

  case 40: /* tab: tabe "<table" $@7 table_arg ">" rows "</table" ">" tabe  */
#line 368 "dphl.y"
                                                                                    { dphl_etable(); }
#line 1674 "dphlparser.c"
    break;

  case 43: /* $@8: %empty  */
#line 375 "dphl.y"
                           { dphl_rhr(); }
#line 1680 "dphlparser.c"
    break;

  case 45: /* $@9: %empty  */
#line 376 "dphl.y"
                                       { dphl_rhr(); }
#line 1686 "dphlparser.c"
    break;

  case 47: /* $@10: %empty  */
#line 381 "dphl.y"
                     { dphl_rtr(); }
#line 1692 "dphlparser.c"
    break;

  case 48: /* row: "<tr" ">" $@10 cells "</tr" ">"  */
#line 381 "dphl.y"
                                                        { dphl_etr (); }
#line 1698 "dphlparser.c"
    break;

  case 51: /* $@11: %empty  */
#line 388 "dphl.y"
                            { dphl_rvr(); }
#line 1704 "dphlparser.c"
    break;

  case 53: /* $@12: %empty  */
#line 389 "dphl.y"
                                        { dphl_rvr(); }
#line 1710 "dphlparser.c"
    break;

  case 55: /* cell: celltd td_arg ">" htmlparser "</td" ">"  */
#line 397 "dphl.y"
                                                     { dphl_etd(0); }
#line 1716 "dphlparser.c"
    break;

  case 56: /* cell: celltd td_arg ">" cellimg img_arg "/>" "</td" ">"  */
#line 398 "dphl.y"
                                                                { dphl_eimg(); dphl_etd(1); }
#line 1722 "dphlparser.c"
    break;

  case 57: /* cell: celltd td_arg ">" cellimg img_arg ">" "</img" ">" "</td" ">"  */
#line 399 "dphl.y"
                                                                             { dphl_eimg(); dphl_etd(1); }
#line 1728 "dphlparser.c"
    break;

  case 58: /* cell: celltd td_arg ">" "</td" ">"  */
#line 400 "dphl.y"
                                          { dphl_etd(2); }
#line 1734 "dphlparser.c"
    break;

  case 59: /* cellimg: "<img"  */
#line 404 "dphl.y"
                 { dphl_rimg(); }
#line 1740 "dphlparser.c"
    break;

  case 60: /* celltd: "<td"  */
#line 408 "dphl.y"
                { dphl_rtd(); }
#line 1746 "dphlparser.c"
    break;

  case 63: /* table_1arg: "align" "=" "string"  */
#line 440 "dphl.y"
                                 { if (dphl_chk_align ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1752 "dphlparser.c"
    break;

  case 64: /* table_1arg: "bgcolor" "=" "string"  */
#line 441 "dphl.y"
                                   { if (dphl_chk_bgcolor ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1758 "dphlparser.c"
    break;

  case 65: /* table_1arg: "border" "=" "string"  */
#line 442 "dphl.y"
                                  { if (dphl_chk_border ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1764 "dphlparser.c"
    break;

  case 66: /* table_1arg: "cellborder" "=" "string"  */
#line 443 "dphl.y"
                                      { if (dphl_chk_cellborder ((yyvsp[0].string))) { YYERROR; } }
#line 1770 "dphlparser.c"
    break;

  case 67: /* table_1arg: "cellpadding" "=" "string"  */
#line 444 "dphl.y"
                                       { if (dphl_chk_cellpadding ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1776 "dphlparser.c"
    break;

  case 68: /* table_1arg: "cellspacing" "=" "string"  */
#line 445 "dphl.y"
                                       { if (dphl_chk_cellspacing ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1782 "dphlparser.c"
    break;

  case 69: /* table_1arg: "color" "=" "string"  */
#line 446 "dphl.y"
                                 { if (dphl_chk_color ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1788 "dphlparser.c"
    break;

  case 70: /* table_1arg: "columns" "=" "string"  */
#line 447 "dphl.y"
                                   { if (dphl_chk_columns ((yyvsp[0].string))) { YYERROR; } }
#line 1794 "dphlparser.c"
    break;

  case 71: /* table_1arg: "fixedsize" "=" "string"  */
#line 448 "dphl.y"
                                     { if (dphl_chk_fixedsize ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1800 "dphlparser.c"
    break;

  case 72: /* table_1arg: "gradientangle" "=" "string"  */
#line 449 "dphl.y"
                                         { if (dphl_chk_gradientangle ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1806 "dphlparser.c"
    break;

  case 73: /* table_1arg: "height" "=" "string"  */
#line 450 "dphl.y"
                                  { if (dphl_chk_height ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1812 "dphlparser.c"
    break;

  case 74: /* table_1arg: "href" "=" "string"  */
#line 451 "dphl.y"
                                { if (dphl_chk_href ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1818 "dphlparser.c"
    break;

  case 75: /* table_1arg: "id" "=" "string"  */
#line 452 "dphl.y"
                              { if (dphl_chk_id ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1824 "dphlparser.c"
    break;

  case 76: /* table_1arg: "port" "=" "string"  */
#line 453 "dphl.y"
                                { if (dphl_chk_port ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1830 "dphlparser.c"
    break;

  case 77: /* table_1arg: "rows" "=" "string"  */
#line 454 "dphl.y"
                                { if (dphl_chk_rows ((yyvsp[0].string))) { YYERROR; } }
#line 1836 "dphlparser.c"
    break;

  case 78: /* table_1arg: "sides" "=" "string"  */
#line 455 "dphl.y"
                                 { if (dphl_chk_sides ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1842 "dphlparser.c"
    break;

  case 79: /* table_1arg: "style" "=" "string"  */
#line 456 "dphl.y"
                                 { if (dphl_chk_style ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1848 "dphlparser.c"
    break;

  case 80: /* table_1arg: "target" "=" "string"  */
#line 457 "dphl.y"
                                  { if (dphl_chk_target ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1854 "dphlparser.c"
    break;

  case 81: /* table_1arg: "title" "=" "string"  */
#line 458 "dphl.y"
                                 { if (dphl_chk_title ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1860 "dphlparser.c"
    break;

  case 82: /* table_1arg: "tooltip" "=" "string"  */
#line 459 "dphl.y"
                                   { if (dphl_chk_title ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1866 "dphlparser.c"
    break;

  case 83: /* table_1arg: "valign" "=" "string"  */
#line 460 "dphl.y"
                                  { if (dphl_chk_valign ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1872 "dphlparser.c"
    break;

  case 84: /* table_1arg: "width" "=" "string"  */
#line 461 "dphl.y"
                                 { if (dphl_chk_width ((yyvsp[0].string),T_TABLE)) { YYERROR; } }
#line 1878 "dphlparser.c"
    break;

  case 85: /* table_1arg: "text" "=" "string"  */
#line 462 "dphl.y"
                               { dphl_attr_huh ((char *) "<table>", (yyvsp[-2].string), (yyvsp[0].string)); }
#line 1884 "dphlparser.c"
    break;

  case 88: /* td_1arg: "align" "=" "string"  */
#line 494 "dphl.y"
                                 { if (dphl_chk_align ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1890 "dphlparser.c"
    break;

  case 89: /* td_1arg: "balign" "=" "string"  */
#line 495 "dphl.y"
                                  { if (dphl_chk_balign ((yyvsp[0].string))) { YYERROR; } }
#line 1896 "dphlparser.c"
    break;

  case 90: /* td_1arg: "bgcolor" "=" "string"  */
#line 496 "dphl.y"
                                   { if (dphl_chk_bgcolor ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1902 "dphlparser.c"
    break;

  case 91: /* td_1arg: "border" "=" "string"  */
#line 497 "dphl.y"
                                  { if (dphl_chk_border ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1908 "dphlparser.c"
    break;

  case 92: /* td_1arg: "cellpadding" "=" "string"  */
#line 498 "dphl.y"
                                       { if (dphl_chk_cellpadding ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1914 "dphlparser.c"
    break;

  case 93: /* td_1arg: "cellspacing" "=" "string"  */
#line 499 "dphl.y"
                                       { if (dphl_chk_cellspacing ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1920 "dphlparser.c"
    break;

  case 94: /* td_1arg: "color" "=" "string"  */
#line 500 "dphl.y"
                                 { if (dphl_chk_color ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1926 "dphlparser.c"
    break;

  case 95: /* td_1arg: "colspan" "=" "string"  */
#line 501 "dphl.y"
                                   { if (dphl_chk_colspan ((yyvsp[0].string))) { YYERROR; } }
#line 1932 "dphlparser.c"
    break;

  case 96: /* td_1arg: "fixedsize" "=" "string"  */
#line 502 "dphl.y"
                                     { if (dphl_chk_fixedsize ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1938 "dphlparser.c"
    break;

  case 97: /* td_1arg: "gradientangle" "=" "string"  */
#line 503 "dphl.y"
                                         { if (dphl_chk_gradientangle ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1944 "dphlparser.c"
    break;

  case 98: /* td_1arg: "height" "=" "string"  */
#line 504 "dphl.y"
                                  { if (dphl_chk_height ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1950 "dphlparser.c"
    break;

  case 99: /* td_1arg: "href" "=" "string"  */
#line 505 "dphl.y"
                                { if (dphl_chk_href ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1956 "dphlparser.c"
    break;

  case 100: /* td_1arg: "id" "=" "string"  */
#line 506 "dphl.y"
                              { if (dphl_chk_id ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1962 "dphlparser.c"
    break;

  case 101: /* td_1arg: "port" "=" "string"  */
#line 507 "dphl.y"
                                { if (dphl_chk_port ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1968 "dphlparser.c"
    break;

  case 102: /* td_1arg: "rowspan" "=" "string"  */
#line 508 "dphl.y"
                                   { if (dphl_chk_rowspan ((yyvsp[0].string))) { YYERROR; } }
#line 1974 "dphlparser.c"
    break;

  case 103: /* td_1arg: "sides" "=" "string"  */
#line 509 "dphl.y"
                                 { if (dphl_chk_sides ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1980 "dphlparser.c"
    break;

  case 104: /* td_1arg: "style" "=" "string"  */
#line 510 "dphl.y"
                                 { if (dphl_chk_sides ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1986 "dphlparser.c"
    break;

  case 105: /* td_1arg: "target" "=" "string"  */
#line 511 "dphl.y"
                                  { if (dphl_chk_target ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1992 "dphlparser.c"
    break;

  case 106: /* td_1arg: "title" "=" "string"  */
#line 512 "dphl.y"
                                 { if (dphl_chk_title ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 1998 "dphlparser.c"
    break;

  case 107: /* td_1arg: "tooltip" "=" "string"  */
#line 513 "dphl.y"
                                   { if (dphl_chk_title ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 2004 "dphlparser.c"
    break;

  case 108: /* td_1arg: "valign" "=" "string"  */
#line 514 "dphl.y"
                                  { if (dphl_chk_valign ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 2010 "dphlparser.c"
    break;

  case 109: /* td_1arg: "width" "=" "string"  */
#line 515 "dphl.y"
                                 { if (dphl_chk_width ((yyvsp[0].string),T_TD)) { YYERROR; } }
#line 2016 "dphlparser.c"
    break;

  case 110: /* td_1arg: "text" "=" "string"  */
#line 516 "dphl.y"
                               { dphl_attr_huh ((char *) "<td>", (yyvsp[-2].string), (yyvsp[0].string)); }
#line 2022 "dphlparser.c"
    break;

  case 113: /* img_1arg: "scale" "=" "string"  */
#line 530 "dphl.y"
                                 { if (dphl_chk_scale ((yyvsp[0].string))) { YYERROR; } }
#line 2028 "dphlparser.c"
    break;

  case 114: /* img_1arg: "src" "=" "string"  */
#line 531 "dphl.y"
                               { if (dphl_chk_src ((yyvsp[0].string))) { YYERROR; } }
#line 2034 "dphlparser.c"
    break;

  case 115: /* img_1arg: "text" "=" "string"  */
#line 532 "dphl.y"
                               { dphl_attr_huh ((char *) "<img>", (yyvsp[-2].string), (yyvsp[0].string)); }
#line 2040 "dphlparser.c"
    break;

  case 118: /* br_1arg: "align" "=" "string"  */
#line 544 "dphl.y"
                                 { if (dphl_chk_align ((yyvsp[0].string),T_BR)) { YYERROR; } }
#line 2046 "dphlparser.c"
    break;

  case 119: /* br_1arg: "text" "=" "string"  */
#line 545 "dphl.y"
                               { dphl_attr_huh ((char *) "<br>", (yyvsp[-2].string), (yyvsp[0].string)); }
#line 2052 "dphlparser.c"
    break;

  case 122: /* font_1arg: "color" "=" "string"  */
#line 559 "dphl.y"
                                 { if (dphl_chk_color ((yyvsp[0].string),T_FONT)) { YYERROR; } }
#line 2058 "dphlparser.c"
    break;

  case 123: /* font_1arg: "face" "=" "string"  */
#line 560 "dphl.y"
                                { if (dphl_chk_face ((yyvsp[0].string))) { YYERROR; } }
#line 2064 "dphlparser.c"
    break;

  case 124: /* font_1arg: "point-size" "=" "string"  */
#line 561 "dphl.y"
                                     { if (dphl_chk_pointsize ((yyvsp[0].string))) { YYERROR; } }
#line 2070 "dphlparser.c"
    break;

  case 125: /* font_1arg: "text" "=" "string"  */
#line 562 "dphl.y"
                               { dphl_attr_huh ((char *) "<font>", (yyvsp[-2].string), (yyvsp[0].string)); }
#line 2076 "dphlparser.c"
    break;


#line 2080 "dphlparser.c"

      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == HLYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= HLYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == HLYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = HLYEMPTY;
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
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != HLYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 565 "dphl.y"


/* end */
