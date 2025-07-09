/* A Bison parser, made by GNU Bison 3.8.2.  */

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PROIECTULMEU_TAB_H_INCLUDED
# define YY_YY_PROIECTULMEU_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    TOK_TEXT_PRINTF = 258,         /* TOK_TEXT_PRINTF  */
    TOK_PRINTF = 259,              /* TOK_PRINTF  */
    TOK_SCANF = 260,               /* TOK_SCANF  */
    TOK_PLUS = 261,                /* TOK_PLUS  */
    TOK_MINUS = 262,               /* TOK_MINUS  */
    TOK_MULTIPLY = 263,            /* TOK_MULTIPLY  */
    TOK_DIVIDE = 264,              /* TOK_DIVIDE  */
    TOK_LEFT = 265,                /* TOK_LEFT  */
    TOK_RIGHT = 266,               /* TOK_RIGHT  */
    TOK_DECLARE = 267,             /* TOK_DECLARE  */
    TOK_PRINT = 268,               /* TOK_PRINT  */
    TOK_ERROR = 269,               /* TOK_ERROR  */
    TOK_INT = 270,                 /* TOK_INT  */
    TOK_FLOAT = 271,               /* TOK_FLOAT  */
    TOK_DOUBLE = 272,              /* TOK_DOUBLE  */
    TOK_VOID = 273,                /* TOK_VOID  */
    TOK_IF = 274,                  /* TOK_IF  */
    TOK_ELSE = 275,                /* TOK_ELSE  */
    TOK_WHILE = 276,               /* TOK_WHILE  */
    TOK_LBRACE = 277,              /* TOK_LBRACE  */
    TOK_RBRACE = 278,              /* TOK_RBRACE  */
    TOK_GT = 279,                  /* TOK_GT  */
    TOK_LT = 280,                  /* TOK_LT  */
    TOK_GE = 281,                  /* TOK_GE  */
    TOK_LE = 282,                  /* TOK_LE  */
    TOK_EQ = 283,                  /* TOK_EQ  */
    TOK_NE = 284,                  /* TOK_NE  */
    TOK_RETURN = 285,              /* TOK_RETURN  */
    TOK_NUMBER_INT = 286,          /* TOK_NUMBER_INT  */
    TOK_NUMBER_FLOAT = 287,        /* TOK_NUMBER_FLOAT  */
    TOK_NUMBER_DOUBLE = 288,       /* TOK_NUMBER_DOUBLE  */
    TOK_VARIABLE = 289,            /* TOK_VARIABLE  */
    TOK_FUNCTION_BODY = 290        /* TOK_FUNCTION_BODY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 645 "proiectulmeu.y"

    char* sir;         // Pentru variabile (TOK_VARIABLE)
    int val;           // Pentru numere întregi (TOK_NUMBER_INT)
    float fval;        // Pentru numere float (TOK_NUMBER_FLOAT)
    double dval;       // Pentru numere double (TOK_NUMBER_DOUBLE)

#line 106 "proiectulmeu.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_PROIECTULMEU_TAB_H_INCLUDED  */
