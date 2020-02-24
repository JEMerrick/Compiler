%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "maths_parser.tab.hpp"
%}

%%

"int"           { return T_INT; }
"return"        { return T_RETURN; }

[{]             { return T_LCURL; }
[}]             { return T_RCURL; }
[(]             { return T_LCURVE; }
[)]             { return T_RCURVE; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[\^]            { return T_EXPONENT; }
[-]             { return T_MINUS; }

[&]             { return T_AND; }
[|]             { return T_OR; }
[^]             { return T_XOR; }
[<<]            { return T_LSHIFT; }
[>>]            { return T_RSHIFT; }
[%]             { return T_MOD; }

auto            { return T_AUTO; }
break           { return T_BREAK; }
case            { return T_CASE; }
char            { return T_CHAR; }
const           { return T_CONST; }
continue        { return T_CONTINUE; }
default         { return T_DEFAULT; }


[a-zA-Z_][a-zA-Z_0-9]* { yylval.string=new std::string(yytext); return T_IDENTIFIER; }
[-]?[0-9]+ { yylval.number=strtod(yytext, 0); return T_INT; }


[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
