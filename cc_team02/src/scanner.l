%option prefix="mCc_parser_"

%option batch
%option bison-bridge
%option bison-locations
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
//#define YY_USER_ACTION \
//	yylloc->first_column = yylloc->last_column; \
//	yylloc->last_column += yyleng; \
//	yylloc->first_line = yylloc->last_line; \
//	yylloc->last_line = yylineno;

//from https://stackoverflow.com/questions/656703/how-does-flex-support-bison-location-exactly/22125500#22125500
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }		
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

scomment       \/\/.*\n

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
                    char* tmp = calloc(strlen(yytext)-1, sizeof(char));
                    strncpy(tmp, &yytext[1], strlen(yytext)-2);
                   // tmp[strlen(yytext)-1] = '\0';  
                    yylval->TK_STRING_LITERAL = tmp;
                    return TK_STRING_LITERAL;
                  }
{identifier}      { 
                    yylval->TK_IDENTIFIER = mCc_ast_new_identifier(strdup(yytext));
                    return TK_IDENTIFIER;
                  }

"/*"             {                
                    char c;
                    int done = 0;
                    do{
                        while((c=input(yyscanner)) != '*' && c != EOF){
                             if(c == '\n'){
                                yylloc->last_line++;   
                            }
                        }
                        if(c == '*'){
                            while((c=input(yyscanner)) == '*');
                            if(c == '/'){
                                done = 1;
                            }
                        }
                        if(c == EOF){
                            fprintf(stderr, "EOF in comment\n");
                        }
                    }while( done == 0 );
                  }

{scomment}        {}               

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
