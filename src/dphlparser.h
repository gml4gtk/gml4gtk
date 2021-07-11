/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Skeleton interface for Bison GLR parsers in C

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

/* Token type.  */
#ifndef HLYTOKENTYPE
# define HLYTOKENTYPE
  enum hlytokentype
  {
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

union HLYSTYPE
{
#line 183 "dphl.y" /* glr.c:197  */
 char *string; 

#line 135 "dphlparser.h" /* glr.c:197  */
};

typedef union HLYSTYPE HLYSTYPE;
# define HLYSTYPE_IS_TRIVIAL 1
# define HLYSTYPE_IS_DECLARED 1
#endif


extern HLYSTYPE hlylval;

int hlyparse (void);

#endif /* !YY_HLY_DPHLPARSER_H_INCLUDED  */
