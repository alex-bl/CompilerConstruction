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

%token IDENTIFIER "IDENTIFIER"
%token <long>   			INT_LITERAL   "integer literal"
%token <double> 			FLOAT_LITERAL "float literal"
%token <const char*>        STRING_LITERAL "string literal"
%token <bool>               BOOL_LITERAL "bool literal"

%token INT_TYPE "integer type"
%token FLOAT_TYPE "float type"
%token STRING_TYPE "string type"
%token BOOL_TYPE "bool type"

%token IF    "if"
%token ELSE  "else"
%token WHILE "while"
%token RETURN "return"

%token LPARENTH "("
%token RPARENTH ")"

%token LBRACE "{"
%token RBRACE "}"

%token LBRACKET "["
%token RBRACKET "]"

%token PLUS  "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"

%token NEGATION "!"

%token LESSEQ "<="
%token LESS "<"
%token GREATEREQ ">="
%token GREATER ">"
%token OR "||"
%token AND "&&"
%token EQUALS "=="
%token NOTEQUALS "!="

%type <enum mCc_ast_binary_op> binary_op

%type <struct mCc_ast_expression *> expression single_expr
%type <struct mCc_ast_literal *> literal

%start toplevel

%%

toplevel : expression { *result = $1; }
         ;

declaration : type IDENTIFIER									{ $$ = mCc_ast_new_primitive_declaration($1, $2); }
		    | type LBRACKET INT_LITERAL RBRACKET IDENTIFIER		{ $$ = mCc_ast_new_array_declaration($1, $5, $3); }
			;

assignment : IDENTIFIER "=" expression								{ $$ = mCc_ast_new_primitive_assignment($1, $3); }
		   | IDENTIFIER LBRACKET expression RBRACKET "=" expression	{ $$ = mCc_ast_new_array_assignment($1, $3, $5); }
		   ;

unary_op	: 	MINUS		{ $$ = MCC_AST_UNARY_OP_MINUS; }
			|	NEGATION	{ $$ = MCC_AST_UNARY_OP_NEGATION; }
			;
			
binary_op	:	PLUS 		{ $$ = MCC_AST_BINARY_OP_ADD; }
          	|	MINUS		{ $$ = MCC_AST_BINARY_OP_SUB; }
          	|	ASTER		{ $$ = MCC_AST_BINARY_OP_MUL; }
          	|	SLASH		{ $$ = MCC_AST_BINARY_OP_DIV; }
			|	LESSEQ		{ $$ = MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN; }
			| 	LESS		{ $$ = MCC_AST_BINARY_OP_LESS_THAN; }
			| 	GREATEREQ	{ $$ = MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN; }
			|	GREATER		{ $$ = MCC_AST_BINARY_OP_GREATER_THAN; }
			|	OR			{ $$ = MCC_AST_BINARY_OP_OR; }
			|	AND			{ $$ = MCC_AST_BINARY_OP_AND; }
			|	EQUALS		{ $$ = MCC_AST_BINARY_OP_EQUALS; }
			|	NOTEQUALS	{ $$ = MCC_AST_BINARY_OP_NOT_EQUALS; }
          	;

single_expr : literal                      			    { $$ = mCc_ast_new_expression_literal($1); }
			| IDENTIFIER								{ $$ = mCc_ast_new_identifier($1); }
			| IDENTIFIER LBRACKET expression RBRACKET	{ $$ = mCc_ast_new_expression_array_identifier($1, $3); }
			| call_expr									{ $$ = mCc_ast_new_expression_function_call($1);}
			| unary_op expression						{ $$ = mCc_ast_new_expression_unary_op($1, $2); }
            | LPARENTH expression RPARENTH    			{ $$ = mCc_ast_new_expression_parenth($2); }
            ;

expression : single_expr                      { $$ = $1; }
           | single_expr binary_op expression { $$ = mCc_ast_new_expression_binary_op($2, $1, $3); }
           ;

literal : INT_LITERAL   { $$ = mCc_ast_new_literal_int($1);   }
        | FLOAT_LITERAL { $$ = mCc_ast_new_literal_float($1); }
		| BOOL_LITERAL  { $$ = mCc_ast_new_literal_bool($1);  }
		| STRING_LITERAL { $$ = mCc_ast_new_literal_string($1); }
        ;

type	:	INT_TYPE 	/*Todo*/
		|	FLOAT_TYPE	/*Todo*/
		|	BOOL_TYPE	/*Todo*/
		|	STRING_TYPE	/*Todo*/
		;

statement   :   if_stmt
            |   while_stmt
            |   ret_stmt
            |   declaration ";"
            |   assignment ";"
            |   expression ";"
            |   compound_stmt
            ;

if_stmt :   IF LPARENTH expression RPARENTH statement
        |   IF LPARENTH expression RPARENTH statement ELSE statement
        ;

while_stmt  :   WHILE LPARENTH expression RPARENTH statement
            ;

ret_stmt    :  RETURN ";"
            |  RETURN expression ";"
            ;

compound_stmt   : LBRACE RBRACE
                | LBRACE statement RBRACE
                ;

function_def    :   function_def_return_type IDENTIFIER LPARENTH RPARENTH compound_stmt				{ $$ = mCc_ast_new_non_parameterized_function_def($2, $1, $5); }
                |   function_def_return_type IDENTIFIER LPARENTH parameters RPARENTH compound_stmt  { $$ = mCc_ast_new_parameterized_function_def($2, $1, $4, $6); }
                ;


function_def_return_type   	:   "void"
							|	type
							;

parameters  :   declaration
            |   parameters "," declaration
            ;

call_expr	:	IDENTIFIER LPARENTH RPARENTH			
			|	IDENTIFIER LPARENTH arguments RPARENTH
			;

arguments	:	expression
			| 	expression "," arguments
			;

program	:	function_def
		|	function_def program
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
