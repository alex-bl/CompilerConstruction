%option prefix="mCc_parser_"

%option batch
%option bison-bridge
%option bison-locations
%option noinput
%option nounput
%option noyywrap
%option reentrant
%option yylineno
%array

%{
#include "parser.tab.h"

#define YYSTYPE MCC_PARSER_STYPE

#define YYLTYPE MCC_PARSER_LTYPE

/* TODO:
 * - track lines
 * - take line breaks into account
 */
#define YY_USER_ACTION \
	yylloc->first_column = yylloc->last_column; \
	yylloc->last_column += yyleng; \
	yylloc->first_line = yylloc->last_line; \
	yylloc->last_line = yylineno;

%}

int_literal   [0-9]+
float_literal [0-9]+\.[0-9]+

string_literal \"(\\.|[^\\])*\"
bool_literal   true|false

int_type       int
float_type     float
bool_type      bool
string_type    string
void_type      void

if_keyword     if
else_keyword   else
while_keyword  while
return_keyword return

identifier     [a-zA-Z_]+[0-9a-zA-Z_]*

%%

{int_type}		  { return TK_INT_TYPE; }
{float_type}	  { return TK_FLOAT_TYPE; }
{bool_type}		  { return TK_BOOL_TYPE; }
{string_type}	  { return TK_STRING_TYPE; }
{void_type}       { return TK_VOID_TYPE; }

{if_keyword}	    { return TK_IF_KEYWORD; }
{else_keyword}    { return TK_ELSE_KEYWORD; }
{while_keyword}	  { return TK_WHILE_KEYWORD; }
{return_keyword}  { return TK_RETURN_KEYWORD; }

{int_literal}     { yylval->TK_INT_LITERAL = atol(yytext); return TK_INT_LITERAL; }
{float_literal}   { yylval->TK_FLOAT_LITERAL = atof(yytext); return TK_FLOAT_LITERAL; }
{bool_literal}    { yylval->TK_BOOL_LITERAL = strcmp(yytext, "true") == 0 ? true : false; return TK_BOOL_LITERAL; }
{string_literal}  {   
                    yylval->TK_STRING_LITERAL = strdup(yytext);
                    return TK_STRING_LITERAL;
                  }
{identifier}      { 
                    yylval->TK_IDENTIFIER = mCc_ast_new_identifier(strdup(yytext));
                    return TK_IDENTIFIER;
                  }

"+"               { return TK_PLUS; }
"-"               { return TK_MINUS; }
"*"               { return TK_ASTER; }
"/"               { return TK_SLASH; }

"("               { return TK_LPARENTH; }
")"               { return TK_RPARENTH; }

"{"               { return TK_LBRACE; }
"}"               { return TK_RBRACE; }

"["               { return TK_LBRACKET; }
"]"               { return TK_RBRACKET; }

"<"               { return TK_LESS; }
">"               { return TK_GREATER; }

"<="              { return TK_LESSEQ; }
">="              { return TK_GREATEREQ; }
"=="              { return TK_EQUALS; }
"!="              { return TK_NOTEQUALS; }

"="               { return TK_ASSIGNMENT; }
";"               { return TK_SEMICOLON; }
","               { return TK_COMMA; }

"!"               { return TK_NEGATION; }

"&&"              { return TK_AND; }
"||"              { return TK_OR; }

[ \t\r\n]+        { /* ignore */ }

<<EOF>>           { return TK_END; }

.                 { fprintf(stderr, "invalid character '%c'\n", yytext[0]); }
