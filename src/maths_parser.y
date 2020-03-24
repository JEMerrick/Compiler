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
%token T_SEMIC T_COMMA
%token T_LSHIFT T_RSHIFT
%token T_EQUAL T_NEQUAL T_GT T_LT T_LEQUAL T_GEQUAL T_ASSIGN
%token T_BNOT T_NOT T_AND T_OR T_BAND T_BOR T_BXOR T_MOD
%token T_ADDEQUAL T_SUBEQUAL T_INCREM T_DECREM
%token T_WHILE T_DO T_IF T_ELSE T_FOR T_BREAK T_CONTINUE T_SWITCH
%token T_INT T_VOID T_CHAR T_SHORT T_LONG T_FLOAT T_DOUBLE T_SIGNED T_RETURN

%type <expr> PROG DECLR_ALL FUNDEC PARAM_LIST SCOPE EXPR_ST EXPR EXPR_ASSIGN EXPR_COND OR AND BOR BXOR BAND EQUAL LESS SHIFT ADD MUL UNARY POSTFIX PRIMATIVE STMT JMP_ST IF_ST ITER_ST NEW_SCOPE DEC_ST DEC_LIST VAR_DEC
%type <number> T_NUMBER
%type <string> T_INT T_VOID T_CHAR T_SHORT T_LONG T_FLOAT T_DOUBLE T_SIGNED
%type <string> T_VARIABLE TYPE

%start ROOT
%%
/* The TODO notes a are just a guide, and are non-exhaustive.
   The expectation is that you do each one, then compile and test.
   Testing should be done using patterns that target the specific
   feature; the testbench is there to make sure that you haven't
   broken anything while you added it.
*/
ROOT : PROG { g_root = $1; }

PROG :  DECLR_ALL {$$ = $1;}
        | PROG DECLR_ALL { $$ = $1; }

DECLR_ALL : FUNDEC { /* new global list */}
            | DEC_ST { /* new global list*/ }

FUNDEC : TYPE T_VARIABLE T_LBRAC PARAM_LIST T_RBRAC T_LCURL SCOPE T_RCURL { $$ = new DefFunc(*$1, *$2, $4, $7)}
        | TYPE T_VARIABLE T_LBRAC T_RBRAC T_LCURL SCOPE T_RCURL { $$ = new DefFunc(*$1, *$2, NULL, $6); }
        | TYPE T_VARIABLE T_LBRAC PARAM_LIST T_RBRAC T_SEMIC { $$ = new CallFunc(*$1, *$2, $4);}
        | TYPE T_VARIABLE T_LBRAC T_RBRAC T_SEMIC { $$ = new CallFunc(*$1, *$2, NULL); }

TYPE : T_INT { $$ = $1; }
        | T_VOID { $$ = $1; }
        | T_CHAR { $$ = $1; }
        | T_SHORT { $$ = $1; }
        | T_LONG { $$ = $1; }
        | T_FLOAT { $$ = $1; }
        | T_DOUBLE { $$ = $1; }
        | T_SIGNED  { $$ = $1; }


PARAM_LIST : PARAM_LIST T_COMMA TYPE T_VARIABLE { /* new arg*/ }
             TYPE T_VARIABLE { /* new arg*/ }

SCOPE : SCOPE STMT { /* new branch?*/ }
        | STMT { /* new branch empty? */}

EXPR_ST : T_SEMIC { /* new empty expression statement*/ }
        | EXPR T_SEMIC { /* new expression statement*/ }

EXPR : EXPR_ASSIGN { $$ = $1; }

EXPR_ASSIGN : EXPR_COND { $$ = $1; }
            | T_VARIABLE T_ASSIGN EXPR_ASSIGN {/*new assign expr*/}
            | T_VARIABLE T_ADDEQUAL EXPR_ASSIGN {//addequal}
            | T_VARIABLE T_SUBEQUAL EXPR_ASSIGN {//subequal}

EXPR_COND : OR { $$ = $1; }

OR : AND { $$ = $1; }
    | AND T_OR BOR {$$ = new OrOperator($1, $3); }

AND : BOR { $$ = $1; }
    | AND T_AND BOR {$$ = new AndOperator($1, $3);}

BOR : BXOR { $$ = $1; }
    | BOR T_BOR BXOR {$$ = new BitOr($1, $3);}

BXOR : BAND { $$ = $1; }
    | BOR T_BXOR BXOR {$$ = new ExorOperator($1, $3);}

BAND : EQUAL { $$ = $1; }
    | BAND T_BAND EQUAL {$$ = new OrOperator($1, $3);}

EQUAL : LESS { $$ = $1; }
    | EQUAL T_EQUAL LESS {$$ = new EqualOperator($1, $3);}
    | EQUAL T_NEQUAL LESS {$$ = new NotEqOperator($1, $3);}

LESS : SHIFT { $$ = $1; }
    | LESS T_LT SHIFT {$$ = new LessOperator($1, $3);}
    | LESS T_GT SHIFT {$$ = new GreaterOperator($1, $3);}
    | LESS T_LEQUAL SHIFT {$$ = new LeqOperator($1, $3);}
    | LESS T_GEQUAL SHIFT {$$ = new GeqOperator($1, $3);}

SHIFT : ADD { $$ = $1; }
        | SHIFT T_LSHIFT ADD {$$ = new LshiftOperator($1, $3);}
        | SHIFT T_RSHIFT ADD {$$ = new RshiftOperator($1, $3);}

ADD : MUL { $$ = $1; }
    | ADD T_PLUS MUL {$$ = new AddOperator($1, $3);}
    | ADD T_MINUS MUL {$$ = new SubOperator($1, $3);}

MUL : UNARY { $$ = $1; }
    | MUL T_TIMES UNARY {$$ = new MulOperator($1, $3);}
    | MUL T_DIVIDE UNARY {$$ = new DivOperator($1, $3);}
    | MUL T_MOD UNARY {$$ = new ModOperator($1, $3);}

UNARY : POSTFIX { $$ = $1; }
        | T_DECREM UNARY { /* new prefix decrement */}
        | T_INCREM UNARY { /* new prefix increment */}

POSTFIX : PRIMATIVE { $$ = $1; }
        | POSTFIX T_INCREM { /* new postfix increment */ }
        | POSTFIX T_DECREM { /* new postfix decrement */ }

PRIMATIVE : T_VARIABLE { $$ = new Variable(*$1); }
            | T_NUMBER { $$ = new Number($1); }
            | T_LBRAC EXPR T_RBRAC { $$ = $2; }

STMT : JMP_ST { $$ = $1; }
        | EXPR_ST { $$ = $1; }
        | IF_ST { $$ = $1; }
        | ITER_ST { $$ = $1; }
        | NEW_SCOPE { $$ = $1; }
        | DEC_ST { $$ = $1; }

JMP_ST : T_RETURN T_SEMIC { /* new return 0 */}
        | T_RETURN EXPR T_SEMIC { /* new return expr */}
        | T_BREAK {/* new break statement */}
        | T_CONTINUE { /* new continue statement */}

IF_ST : T_IF T_LBRAC EXPR T_RBRAC STMT { /* new if */}
        | T_IF T_LBRAC EXPR T_RBRAC STMT T_ELSE STMT {/* new if else */}
        | T_SWITCH EXPR STMT {/*new switch */}

ITER_ST : T_WHILE T_LBRAC EXPR T_RBRAC STMT { /* new while*/}
        | T_DO STMT T_WHILE T_LBRAC EXPR T_RBRAC T_SEMIC {/* new do while*/}
        | T_FOR T_LBRAC EXPR_ST EXPR_ST T_RBRAC STMT {/* new for (no increment)*/}
        | T_FOR T_LBRAC EXPR_ST EXPR_ST EXPR T_RBRAC STMT {/* new for */}

NEW_SCOPE : T_LCURL SCOPE T_RCURL {/* new scope */}

DEC_ST : TYPE DEC_LIST T_SEMIC { /* new declare statement */}

DEC_LIST : VAR_DEC { /* new declare variable list length 0 */}
        | DEC_LIST T_COMMA VAR_DEC { /* new declare variable list */}

VAR_DEC : T_VARIABLE T_ASSIGN EXPR { /* new declare variableS */}
        | T_VARIABLE { /* new declare variable */}


%%
const Base *g_root; // Definition of variable (to match declaration earlier)
const Base *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
