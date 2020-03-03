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
%token T_LBRAC T_RBRAC T_LCURL T_RCURL
%token T_NUMBER T_VARIABLE
%token T_SEMIC
%token T_LSHIFT T_RSHIFT
%token T_EQUAL T_NEQUAL T_GT T_LT T_LEQUAL T_GEQUAL
%token T_BNOT T_NOT T_AND T_OR T_BAND T_BOR T_BXOR

%type <expr> PROG 
%type <expr> 
%type <number> T_INT
%type <number> T_NUMBER
%type <string> T_VARIABLE FUNCTION_NAME

%start ROOT
%%
/* The TODO notes a are just a guide, and are non-exhaustive.
   The expectation is that you do each one, then compile and test.
   Testing should be done using patterns that target the specific
   feature; the testbench is there to make sure that you haven't
   broken anything while you added it.
*/
ROOT : PROG { g_root = $1; }

PROG :  DECLR {$$ = $1;}

DECLR : FUNDEC { $$ = $1;}
        //Global var also here
        
FUNDEC : TYPE T_VARIABLE T_LBRAC PARAM_LIST T_RBRAC T_LCURL SCOPE T_RCURL {}

TYPE : T_INT { $$ = $1; }

PARAM_LIST : PARAM_LIST T_COMMA TYPE T_VARIABLE {}
             TYPE T_VARIABLE {}

SCOPE : SCOPE EXPR_ST {}
        | EXPR_ST {}

EXPR_ST : T_SEMIC {}
        | EXPR T_SEMIC {}

EXPR : EXPR_ASSIGN { $$ = $1; }

EXPR_ASSIGN : EXPR_COND { $$ = $1; }

EXPR_COND : OR { $$ = $1; }

OR : AND { $$ = $1; }
    | AND T_OR BOR {}

AND : BOR { $$ = $1; }
    | AND T_AND BOR {}

BOR : BXOR { $$ = $1; }
    | BOR T_BOR BXOR {}

BXOR : BAND { $$ = $1; }
    | BOR T_BXOR BXOR {}

BAND : EQUAL { $$ = $1; }
    | BAND T_BAND EQUAL {}

EQUAL : LESS { $$ = $1; }
    | EQUAL T_EQUAL LESS {}
    | EQUAL T_NEQUAL LESS {}

LESS : SHIFT { $$ = $1; }
    | LESS T_LT SHIFT {}
    | LESS T_GT SHIFT {}
    | LESS T_LEQUAL SHIFT {}
    | LESS T_GEQUAL SHIFT {}

SHIFT : ADD { $$ = $1; }
        | SHIFT T_LSHIFT ADD {}
        | SHIFT T_RSHIFT ADD {}

ADD : MUL { $$ = $1; }
    | ADD T_PLUS MUL {}
    | ADD T_MINUS MUL {}
    
MUL : UNARY { $$ = $1; }
    | MUL T_TIMES UNARY {}
    | MUL T_DIVIDE UNARY {}
    | MUL T_MOD UNARY {}

UNARY :
    //PRE / POST FIX
    //should we also do -x here?


%%
const Base *g_root; // Definition of variable (to match declaration earlier)
const Base *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
