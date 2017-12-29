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

single_expr : literal                         { $$ = mC_ast_expression_new_literal_expression($1); }
            | LPARENTH expression RPARENTH    { $$ = mC_ast_expression_new_parenth_expression($2); }
            ;

expression : single_expr                      { $$ = $1;                                                     }
           | single_expr binary_op expression { $$ = mC_ast_expression_new_binary_op_expression($2, $1, $3); }
           ;

literal : INT_LITERAL   { $$ = mC_ast_literal_new_int_literal($1);   }
        | FLOAT_LITERAL { $$ = mC_ast_literal_new_float_literal($1); }
        ;

%%

#include "scanner.h"

void yyerror(yyscan_t *scanner, const char* msg) {}

struct mC_ast_expression* mC_parser_run(FILE *in)
{
	yyscan_t scanner;
	mC_parser_lex_init(&scanner);
	mC_parser_set_in(in, scanner);

	struct mC_ast_expression *result = NULL;
	if (yyparse(scanner, &result) != 0) {
		fprintf(stderr, "syntax error\n");
	}

	mC_parser_lex_destroy(scanner);

	return result;
}
