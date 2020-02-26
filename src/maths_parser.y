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

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT
%token T_LBRACKET T_RBRACKET
%token T_LOG T_EXP T_SQRT
%token T_NUMBER T_VARIABLE

%type <expr> EXPR TERM UNARY FACTOR
%type <number> T_NUMBER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT FUNCTION_NAME

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
        | TERM T_EXPONENT UNARY          { $$ = new ExpOperator( $1, $3 ); }
        
UNARY :   FACTOR                        { $$ = $1; }
        | T_MINUS UNARY                 { $$ = new NegOperator( $2 ); }
        | UNARY T_EXPONENT UNARY        { $$ = new ExpOperator( $1, $3 ); }
        

FACTOR :  T_NUMBER                      { $$ = new Number( $1 ); }
        | T_VARIABLE                    { $$ = new Variable( *$1 );}
        | T_LBRACKET EXPR T_RBRACKET    { $$ = $2; }
        | FUNCTION_NAME T_LBRACKET EXPR T_RBRACKET { if(*$1 == "log"){$$ = new LogFunction ( $3 );} if(*$1 == "exp"){$$ = new ExpFunction ( $3 );} if(*$1 == "sqrt"){$$ = new SqrtFunction ( $3 );}}
        

/* TODO-6 : Add support log(x), by modifying the rule for FACTOR. */

/* TODO-7 : Extend support to other functions. Requires modifications here, and to FACTOR. */
FUNCTION_NAME : T_LOG { $$ = new std::string("log"); }
               | T_EXP { $$ = new std::string("exp"); }
               | T_SQRT { $$ = new std::string("sqrt"); }

%%

const Base *g_root; // Definition of variable (to match declaration earlier)

const Base *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
