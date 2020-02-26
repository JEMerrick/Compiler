%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "maths_parser.tab.hpp"
%}

%%

"int"           { return T_INT; }
"return"        { return T_RETURN; }
[;]             { return T_SEMIC; }

[{]             { return T_LCURL; }
[}]             { return T_RCURL; }
[(]             { return T_LCURVE; }
[)]             { return T_RCURVE; }

[~]             { return T_BNOT; }
[!]             { return T_NOT; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[%]             { return T_MOD; }

[&][&]            { return T_AND; }
[|][|]            { return T_OR; }
[=][=]            { return T_EQUAL; }
[!][=]            { return T_NEQUAL; }
[<]             { return T_LT; }
[>]             { return T_GT; }
[<][=]            { return T_LEQUAL; }
[>][=]            { return T_GEQUAL; }

[&]             { return T_BAND; }
[|]             { return T_BOR; }
[\^]             { return T_BXOR; }
[<][<]            { return T_LSHIFT; }
[>][>]            { return T_RSHIFT; }

[=]             { return T_ASSIGN; }

"auto"          { return T_AUTO; }
"break"         { return T_BREAK; }
"case"          { return T_CASE; }
"char"          { return T_CHAR; }
"const"         { return T_CONST; }
"continue"      { return T_CONTINUE; }
"default"       { return T_DEFAULT; }
"do"            { return T_DO; }
"double"        { return T_DOUBLE; }
"else"          { return T_ELSE; }
"enum"          { return T_ENUM; }
"extern"        { return T_EXTERN; }
"float"         { return T_FLOAT; }
"for"           { return T_FOR; }
"goto"          { return T_GOTO; }
"if"            { return T_IF; }
"inline"        { return T_INLINE; }
"long"          { return T_LONG; }
"register"      { return T_REG; }
"restrict"      { return T_RESTRICT; }
"short"         { return T_SHORT; }
"signed"        { return T_SIGNED; }
"sizeof"        { return T_SIZEOF; }
"static"        { return T_STATIC; }
"struct"        { return T_STRUCT; }
"switch"        { return T_SWITCH; }
"typedef"       { return T_TYPEDEF; }
"union"         { return T_UNION; }



[a-zA-Z_]([a-zA-Z_] | [0-9])* { yylval.string=new std::string(yytext); return T_IDENTIFIER; }
[0-9]+ { yylval.number=strtod(yytext, 0); return T_INT; }


[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
