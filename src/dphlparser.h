/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_HLY_DPHLPARSER_H_INCLUDED
# define YY_HLY_DPHLPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HLYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HLYDEBUG 1
#  else
#   define HLYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HLYDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HLYDEBUG */
#if HLYDEBUG
extern int hlydebug;
#endif

/* Token kinds.  */
#ifndef HLYTOKENTYPE
# define HLYTOKENTYPE
  enum hlytokentype
  {
    HLYEMPTY = -2,
    HLYEOF = 0,                    /* "end of file"  */
    HLYerror = 256,                /* error  */
    HLYUNDEF = 257,                /* "invalid token"  */
    HL_DATA = 258,                 /* "stringdata"  */
    HL_HTML = 259,                 /* "<html"  */
    HL_C_HTML = 260,               /* "</html"  */
    HL_B = 261,                    /* "<b"  */
    HL_C_B = 262,                  /* "</b"  */
    HL_BR = 263,                   /* "<br"  */
    HL_C_BR = 264,                 /* "</br"  */
    HL_FONT = 265,                 /* "<font"  */
    HL_C_FONT = 266,               /* "</font"  */
    HL_HR = 267,                   /* "<hr"  */
    HL_C_HR = 268,                 /* "</hr"  */
    HL_I = 269,                    /* "<i"  */
    HL_C_I = 270,                  /* "</i"  */
    HL_IMG = 271,                  /* "<img"  */
    HL_C_IMG = 272,                /* "</img"  */
    HL_O = 273,                    /* "<o"  */
    HL_C_O = 274,                  /* "</o"  */
    HL_S = 275,                    /* "<s"  */
    HL_C_S = 276,                  /* "</s"  */
    HL_SUB = 277,                  /* "<sub"  */
    HL_C_SUB = 278,                /* "</sub"  */
    HL_SUP = 279,                  /* "<sup"  */
    HL_C_SUP = 280,                /* "</sup"  */
    HL_TABLE = 281,                /* "<table"  */
    HL_C_TABLE = 282,              /* "</table"  */
    HL_TD = 283,                   /* "<td"  */
    HL_C_TD = 284,                 /* "</td"  */
    HL_TR = 285,                   /* "<tr"  */
    HL_C_TR = 286,                 /* "</tr"  */
    HL_U = 287,                    /* "<u"  */
    HL_C_U = 288,                  /* "</u"  */
    HL_VR = 289,                   /* "<vr"  */
    HL_C_VR = 290,                 /* "</vr"  */
    HL_SC = 291,                   /* "/>"  */
    HL_C = 292,                    /* ">"  */
    HL_IS = 293,                   /* "="  */
    HL_QSTR = 294,                 /* "string"  */
    HL_STR = 295,                  /* "text"  */
    HL_ALIGN = 296,                /* "align"  */
    HL_BALIGN = 297,               /* "balign"  */
    HL_BGCOLOR = 298,              /* "bgcolor"  */
    HL_BORDER = 299,               /* "border"  */
    HL_CELLBORDER = 300,           /* "cellborder"  */
    HL_CELLPADDING = 301,          /* "cellpadding"  */
    HL_CELLSPACING = 302,          /* "cellspacing"  */
    HL_COLOR = 303,                /* "color"  */
    HL_COLUMNS = 304,              /* "columns"  */
    HL_COLSPAN = 305,              /* "colspan"  */
    HL_FACE = 306,                 /* "face"  */
    HL_FIXEDSIZE = 307,            /* "fixedsize"  */
    HL_GRADIENTANGLE = 308,        /* "gradientangle"  */
    HL_HEIGHT = 309,               /* "height"  */
    HL_HREF = 310,                 /* "href"  */
    HL_ID = 311,                   /* "id"  */
    HL_PORT = 312,                 /* "port"  */
    HL_POINTSIZE = 313,            /* "point-size"  */
    HL_ROWS = 314,                 /* "rows"  */
    HL_ROWSPAN = 315,              /* "rowspan"  */
    HL_SCALE = 316,                /* "scale"  */
    HL_SIDES = 317,                /* "sides"  */
    HL_SRC = 318,                  /* "src"  */
    HL_STYLE = 319,                /* "style"  */
    HL_TARGET = 320,               /* "target"  */
    HL_TITLE = 321,                /* "title"  */
    HL_TOOLTIP = 322,              /* "tooltip"  */
    HL_VALIGN = 323,               /* "valign"  */
    HL_WIDTH = 324                 /* "width"  */
  };
  typedef enum hlytokentype hlytoken_kind_t;
#endif

/* Value type.  */
#if ! defined HLYSTYPE && ! defined HLYSTYPE_IS_DECLARED
union HLYSTYPE
{
#line 191 "dphl.y"
 char *string; 

#line 144 "dphlparser.h"

};
typedef union HLYSTYPE HLYSTYPE;
# define HLYSTYPE_IS_TRIVIAL 1
# define HLYSTYPE_IS_DECLARED 1
#endif


extern HLYSTYPE hlylval;

int hlyparse (void);

#endif /* !YY_HLY_DPHLPARSER_H_INCLUDED  */
