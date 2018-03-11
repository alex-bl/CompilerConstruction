%define api.prefix {mCc_parser_}

%define api.pure full
%lex-param   {void *scanner}
%parse-param {void *scanner} {struct mCc_ast_expression** result}

%define parse.trace
%define parse.error verbose

%code requires {
#include "mCc/parser.h"
}

%{
#include <string.h>

int mCc_parser_lex();
void mCc_parser_error();
%}

%define api.value.type union
%define api.token.prefix {TK_}

%token END 0 "EOF"

%token <long>   INT_LITERAL   "integer literal"
%token <double> FLOAT_LITERAL "float literal"

%token LPARENTH "("
%token RPARENTH ")"

%token PLUS  "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"

%type <enum mCc_ast_binary_op> binary_op

%type <struct mCc_ast_expression *> expression single_expr
%type <struct mCc_ast_literal *> literal

%start toplevel

%%

toplevel : expression { *result = $1; }
         ;

binary_op : PLUS  { $$ = MCC_AST_BINARY_OP_ADD; }
          | MINUS { $$ = MCC_AST_BINARY_OP_SUB; }
          | ASTER { $$ = MCC_AST_BINARY_OP_MUL; }
          | SLASH { $$ = MCC_AST_BINARY_OP_DIV; }
          ;

single_expr : literal                         { $$ = mCc_ast_new_expression_literal($1); }
            | LPARENTH expression RPARENTH    { $$ = mCc_ast_new_expression_parenth($2); }
            ;

expression : single_expr                      { $$ = $1;                                           }
           | single_expr binary_op expression { $$ = mCc_ast_new_expression_binary_op($2, $1, $3); }
           ;

literal : INT_LITERAL   { $$ = mCc_ast_new_literal_int($1);   }
        | FLOAT_LITERAL { $$ = mCc_ast_new_literal_float($1); }
        ;

%%

#include <assert.h>

#include "scanner.h"

void yyerror(yyscan_t *scanner, const char *msg) {}

struct mCc_parser_result mCc_parser_parse_string(const char *input)
{
	assert(input);

	struct mCc_parser_result result = { 0 };

	FILE *in = fmemopen((void *)input, strlen(input), "r");
	if (!in) {
		result.status = MCC_PARSER_STATUS_UNABLE_TO_OPEN_STREAM;
		return result;
	}

	result = mCc_parser_parse_file(in);

	fclose(in);

	return result;
}

struct mCc_parser_result mCc_parser_parse_file(FILE *input)
{
	assert(input);

	yyscan_t scanner;
	mCc_parser_lex_init(&scanner);
	mCc_parser_set_in(input, scanner);

	struct mCc_parser_result result = {
		.status = MCC_PARSER_STATUS_OK,
	};

	if (yyparse(scanner, &result.expression) != 0) {
		result.status = MCC_PARSER_STATUS_UNKNOWN_ERROR;
	}

	mCc_parser_lex_destroy(scanner);

	return result;
}
