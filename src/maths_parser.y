%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Base *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Base *expr;
  double number;
  std::string *string;
}

%token T_INT T_RETURN T_SEMIC
%token T_LCURL T_RCURL T_LCURVE T_RCURVE
%token T_BNOT T_NOT
%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_MOD
%token T_AND T_OR T_EQUAL T_NEQUAL T_LT T_GT T_LEQUAL T_GEQUAL
%token T_BAND T_BOR T_BXOR T_LSHIFT T_RSHIFT
%token T_ASSIGN
%token T_AUTO T_BREAK T_CASE T_CHAR T_CONST T_CONTINUE T_DEFAULT
%token T_DO T_DOUBLE T_ELSE T_ENUM T_EXTERN T_FLOAT T_FOR T_GOTO
%token T_IF T_INLINE T_LONG T_REG T_RESTRICT T_SHORT T_SIGNED
%token T_SIZEOF T_STATIC T_STRUCT T_SWITCH T_TYPEDEF T_UNION
%token T_VARIABLE T_NUMBER FUNCTION_NAME

%type <expr> EXPR TERM UNARY FACTOR
%type <number> T_INT
%type <string> T_VARIABLE FUNCTION_NAME

%start ROOT

%%

/* The TODO notes a are just a guide, and are non-exhaustive.
   The expectation is that you do each one, then compile and test.
   Testing should be done using patterns that target the specific
   feature; the testbench is there to make sure that you haven't
   broken anything while you added it.
*/

ROOT : EXPR { g_root = $1; }

EXPR :    TERM                          { $$ = $1; }
        | EXPR T_PLUS TERM              { $$ = new AddOperator( $1, $3 ); }
        | EXPR T_MINUS TERM             { $$ = new SubOperator( $1, $3 ); }

TERM :    UNARY                         { $$ = $1; }
        | TERM T_TIMES UNARY            { $$ = new MulOperator( $1, $3 ); }
        | TERM T_DIVIDE UNARY           { $$ = new DivOperator( $1, $3 ); }
        | TERM T_MOD UNARY              { $$ = new ModOperator( $1, $3 ); }

UNARY :   FACTOR                        { $$ = $1; }
        | T_MINUS UNARY                 { $$ = new NegOperator( $2 ); }


FACTOR :  T_NUMBER                      { $$ = new Number( $1 ); }
        | T_VARIABLE                    { $$ = new Variable( *$1 );}
        | T_LCURVE EXPR T_RCURVE        { $$ = $2; }




/* TODO-7 : Extend support to other functions. Requires modifications here, and to FACTOR. */
/*FUNCTION_NAME : T_LOG { $$ = new std::string("log"); }
               | T_EXP { $$ = new std::string("exp"); }
               | T_SQRT { $$ = new std::string("sqrt"); } */

%%

const Base *g_root; // Definition of variable (to match declaration earlier)

const Base *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
