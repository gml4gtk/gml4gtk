/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Skeleton interface for Bison GLR parsers in C

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

#ifndef YY_YY_DOT_TAB_H_INCLUDED
# define YY_YY_DOT_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_BRACEOPEN = 258,         /* "{"  */
    TOKEN_BRACECLOSE = 259,        /* "}"  */
    TOKEN_PLUS = 260,              /* "+"  */
    TOKEN_COMMA = 261,             /* ","  */
    TOKEN_COLON = 262,             /* ":"  */
    TOKEN_IS = 263,                /* "="  */
    TOKEN_SC = 264,                /* ";"  */
    TOKEN_BRACKETOPEN = 265,       /* "["  */
    TOKEN_BRACKETCLOSE = 266,      /* "]"  */
    TOKEN_UTF8BOM = 267,           /* "utf8code"  */
    TOKEN_STRICT = 268,            /* "strict"  */
    TOKEN_GRAPH = 269,             /* "graph"  */
    TOKEN_SUBGRAPH = 270,          /* "subgraph"  */
    TOKEN_DIGRAPH = 271,           /* "digraph"  */
    TOKEN_NODE = 272,              /* "node"  */
    TOKEN_EDGE = 273,              /* "edge"  */
    TOKEN_TEXT = 274,              /* "text"  */
    TOKEN_NUM = 275,               /* "number"  */
    TOKEN_QTEXT = 276,             /* "string"  */
    TOKEN_HTEXT = 277,             /* "<html-string>"  */
    TOKEN_EOP = 278                /* "-> or --"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 82 "dot.y"
 char *string; struct dpepoint *dp; 

#line 85 "dot.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DOT_TAB_H_INCLUDED  */
