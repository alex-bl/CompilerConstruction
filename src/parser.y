%define api.prefix {mC_parser_}

%define api.pure full
%lex-param   {void *scanner}
%parse-param {void *scanner} {struct mC_ast_expression** result}

%define parse.trace
%define parse.error verbose

%code requires {
#include "mCc/parser.h"
}

%{
#include <assert.h>

int mC_parser_lex();
void mC_parser_error();
%}

%define api.value.type union
%define api.token.prefix {MC_PARSER_TOKEN_}

%token END 0 "EOF"

%token <long>   INT_LITERAL   "integer literal"
%token <double> FLOAT_LITERAL "float literal"

%token LPARENTH "("
%token RPARENTH ")"

%token PLUS  "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"

%type <enum mC_ast_binary_op> binary_op

%type <struct mC_ast_expression*> single_expr
%type <struct mC_ast_expression*> expression

%type <struct mC_ast_literal*> literal

%start toplevel

%%

toplevel : expression { *result = $1; }
         ;

binary_op : PLUS  { $$ = MC_AST_BINARY_OP_ADD; }
          | MINUS { $$ = MC_AST_BINARY_OP_SUB; }
          | ASTER { $$ = MC_AST_BINARY_OP_MUL; }
          | SLASH { $$ = MC_AST_BINARY_OP_DIV; }
          ;

single_expr : literal                         { $$ = mC_ast_new_expression_literal($1); }
            | LPARENTH expression RPARENTH    { $$ = mC_ast_new_expression_parenth($2); }
            ;

expression : single_expr                      { $$ = $1;                                          }
           | single_expr binary_op expression { $$ = mC_ast_new_expression_binary_op($2, $1, $3); }
           ;

literal : INT_LITERAL   { $$ = mC_ast_new_literal_int($1);   }
        | FLOAT_LITERAL { $$ = mC_ast_new_literal_float($1); }
        ;

%%

#include "scanner.h"

void yyerror(yyscan_t *scanner, const char *msg) {}

struct mC_ast_expression *mC_parser_parse_string(const char *input, size_t len)
{
	assert(len > 0);
	FILE *in = fmemopen((void *)input, len - 1, "r");
	if (!in) {
		fprintf(stderr, "could not open in-memory stream\n");
		return NULL;
	}

	struct mC_ast_expression *result = mC_parser_parse_file(in);

	fclose(in);

	return result;
}

struct mC_ast_expression *mC_parser_parse_file(FILE *input)
{
	yyscan_t scanner;
	mC_parser_lex_init(&scanner);
	mC_parser_set_in(input, scanner);

	struct mC_ast_expression *result = NULL;
	if (yyparse(scanner, &result) != 0) {
		fprintf(stderr, "syntax error\n");
	}

	mC_parser_lex_destroy(scanner);

	return result;
}
