%option prefix="mC_parser_"

%option batch
%option bison-bridge
%option noinput
%option nounput
%option noyywrap
%option reentrant

%{
#include "parser.tab.h"

#define YYSTYPE MC_PARSER_STYPE
%}

int_literal   -?[0-9]+
float_literal -?[0-9]+\.[0-9]+

%%

{int_literal}     { yylval->MC_PARSER_TOKEN_INT_LITERAL = atol(yytext); return MC_PARSER_TOKEN_INT_LITERAL; }

{float_literal}   { yylval->MC_PARSER_TOKEN_FLOAT_LITERAL = atof(yytext); return MC_PARSER_TOKEN_FLOAT_LITERAL; }

"+"               { return MC_PARSER_TOKEN_PLUS; }
"-"               { return MC_PARSER_TOKEN_MINUS; }
"*"               { return MC_PARSER_TOKEN_ASTER; }
"/"               { return MC_PARSER_TOKEN_SLASH; }

"("               { return MC_PARSER_TOKEN_LPARENTH; }
")"               { return MC_PARSER_TOKEN_RPARENTH; }

[ \t\r\n]+        { /* ignore */ }

<<EOF>>           { return MC_PARSER_TOKEN_END; }

.                 { fprintf(stderr, "invalid character '%c'\n", yytext[0]); }
