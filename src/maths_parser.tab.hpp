/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/maths_parser.y" /* yacc.c:1909  */

  #include "ast.hpp"

  #include <cassert>

  extern const Base *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 58 "src/maths_parser.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_TIMES = 258,
    T_DIVIDE = 259,
    T_PLUS = 260,
    T_MINUS = 261,
    T_EXPONENT = 262,
    T_LBRAC = 263,
    T_RBRAC = 264,
    T_LCURL = 265,
    T_RCURL = 266,
    T_NUMBER = 267,
    T_VARIABLE = 268,
    T_SEMIC = 269,
    T_COMMA = 270,
    T_LSHIFT = 271,
    T_RSHIFT = 272,
    T_EQUAL = 273,
    T_NEQUAL = 274,
    T_GT = 275,
    T_LT = 276,
    T_LEQUAL = 277,
    T_GEQUAL = 278,
    T_BNOT = 279,
    T_NOT = 280,
    T_AND = 281,
    T_OR = 282,
    T_BAND = 283,
    T_BOR = 284,
    T_BXOR = 285,
    T_MOD = 286,
    T_ADDEQUAL = 287,
    T_SUBEQUAL = 288,
    T_INCREM = 289,
    T_DECREM = 290,
    T_WHILE = 291,
    T_DO = 292,
    T_IF = 293,
    T_ELSE = 294,
    T_FOR = 295,
    T_INT = 296,
    T_VOID = 297,
    T_CHAR = 298,
    T_SHORT = 299,
    T_LONG = 300,
    T_FLOAT = 301,
    T_DOUBLE = 302,
    T_SIGNED = 303,
    T_RETURN = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "src/maths_parser.y" /* yacc.c:1909  */

  const Base *expr;
  double number;
  std::string *string;

#line 126 "src/maths_parser.tab.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MATHS_PARSER_TAB_HPP_INCLUDED  */
