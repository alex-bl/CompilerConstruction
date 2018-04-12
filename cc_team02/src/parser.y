%define api.prefix {mCc_parser_}

%define api.pure full
%lex-param   {void *scanner} 
%parse-param {void *scanner} {struct mCc_parser_result* result}

%define parse.trace
%define parse.error verbose

%code requires {
#include "mCc/parser.h"
}

%{
#include <string.h>

int mCc_parser_lex();
void mCc_parser_error();

#define loc(ast_node, ast_sloc) \
		if(ast_node){ \
			(ast_node)->node.sloc.start_col = (ast_sloc).first_column; \
			(ast_node)->node.sloc.end_col = (ast_sloc).last_column; \
			(ast_node)->node.sloc.start_line = (ast_sloc).first_line; \
			(ast_node)->node.sloc.end_line = (ast_sloc).last_line; \
		}
%}

%define api.value.type union
%define api.token.prefix {TK_}

%destructor {mCc_ast_delete_expression($$);} expression single_expr_lev2 single_expr_lev1 single_expr arguments
%destructor {mCc_ast_delete_function_call($$);} call_expr
%destructor {mCc_ast_delete_declaration($$);} parameters 
%destructor {mCc_ast_delete_identifier($$);} IDENTIFIER 
%destructor {mCc_ast_delete_literal($$);} literal 
%destructor {mCc_ast_delete_assignment($$);} assignment 
%destructor {mCc_ast_delete_function_def($$);} function_def 
%destructor {mCc_ast_delete_statement($$);} statement_list statement 
%destructor {mCc_ast_delete_program($$);} program 
%destructor {mCc_ast_delete_declaration($$);} declaration


%token END 0 "EOF"

%token <struct mCc_ast_identifier* > 		IDENTIFIER "IDENTIFIER"
%token <long>   			INT_LITERAL   "integer literal"
%token <double> 			FLOAT_LITERAL "float literal"
%token <const char*>        STRING_LITERAL "string literal"
%token <bool>               BOOL_LITERAL "bool literal"

%token START_STATEMENT
%token START_EXPRESSION
%token START_ASSIGNMENT
%token START_DECLARATION
%token START_PROGRAM

%token INT_TYPE "integer type"
%token FLOAT_TYPE "float type"
%token STRING_TYPE "string type"
%token BOOL_TYPE "bool type"
%token VOID_TYPE "void type"

%token IF_KEYWORD    "if"
%token ELSE_KEYWORD  "else"
%token WHILE_KEYWORD "while"
%token RETURN_KEYWORD "return"

%token LPARENTH "("
%token RPARENTH ")"

%token LBRACE "{"
%token RBRACE "}"

%token LBRACKET "["
%token RBRACKET "]"

//%left PLUS MINUS 
//%left ASTER SLASH
//%precedence NEG

%token PLUS  "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"


%token NEGATION "!"

%token SEMICOLON ";"
%token COMMA ","

%token ASSIGNMENT "="
%token LESSEQ "<="
%token LESS "<"
%token GREATEREQ ">="
%token GREATER ">"
%token OR "||"
%token AND "&&"
%token EQUALS "=="
%token NOTEQUALS "!="

%type <enum mCc_ast_binary_op> binary_op binary_op_add binary_op_mul
%type <enum mCc_ast_unary_op> unary_op
%type <enum mCc_ast_data_type> type VOID_TYPE

%type <struct mCc_ast_expression *> expression single_expr arguments single_expr_lev1 single_expr_lev2
%type <struct mCc_ast_literal *> literal
%type <struct mCc_ast_assignment *> assignment
%type <struct mCc_ast_declaration *> declaration parameters
%type <struct mCc_ast_function_def *> function_def function_list
%type <struct mCc_ast_statement *> statement if_stmt while_stmt ret_stmt compound_stmt statement_list
%type <struct mCc_ast_function_call *> call_expr
%type <struct mCc_ast_program *> program


%start toplevel

%%

toplevel: statement_list  	{ result->top_level_type=MCC_PARSER_TOP_LEVEL_STATEMENT; result->statement = $1;}
		| expression 	{ result->top_level_type=MCC_PARSER_TOP_LEVEL_EXPRESSION; result->expression = $1;}
		| program 	  	{ result->top_level_type=MCC_PARSER_TOP_LEVEL_PROGRAM; result->program = $1; } 
		;

declaration: type IDENTIFIER									{ $$ = mCc_ast_new_primitive_declaration($1, $2); loc($$, @1);}
		   | type LBRACKET INT_LITERAL RBRACKET IDENTIFIER		{ $$ = mCc_ast_new_array_declaration($1, $5, $3); loc($$, @1);}
		   ;

assignment: IDENTIFIER ASSIGNMENT expression								{ $$ = mCc_ast_new_primitive_assignment($1, $3); loc($$, @1);}
		  | IDENTIFIER LBRACKET expression RBRACKET ASSIGNMENT expression	{ $$ = mCc_ast_new_array_assignment($1, $3, $6); loc($$, @1);}
		  ;

unary_op: 	MINUS		{ $$ = MCC_AST_UNARY_OP_MINUS; }
		|	NEGATION	{ $$ = MCC_AST_UNARY_OP_NEGATION; }
		;
			
binary_op:	LESSEQ		{ $$ = MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN; }
		 | 	LESS		{ $$ = MCC_AST_BINARY_OP_LESS_THAN; }
		 | 	GREATEREQ	{ $$ = MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN; }
		 |	GREATER		{ $$ = MCC_AST_BINARY_OP_GREATER_THAN; }
		 |	OR			{ $$ = MCC_AST_BINARY_OP_OR; }
		 |	AND			{ $$ = MCC_AST_BINARY_OP_AND; }
		 |	EQUALS		{ $$ = MCC_AST_BINARY_OP_EQUALS; }
		 |	NOTEQUALS	{ $$ = MCC_AST_BINARY_OP_NOT_EQUALS; }
         ;

binary_op_add:	PLUS 		{ $$ = MCC_AST_BINARY_OP_ADD; }
          	 |	MINUS		{ $$ = MCC_AST_BINARY_OP_SUB; }
			 ;

binary_op_mul:	ASTER		{ $$ = MCC_AST_BINARY_OP_MUL; }
             |	SLASH		{ $$ = MCC_AST_BINARY_OP_DIV; }
			 ;


single_expr:  literal                      			    { $$ = mCc_ast_new_expression_literal($1); loc($$, @1);}
		   | unary_op INT_LITERAL						{ $$ = mCc_ast_new_expression_unary_op($1, mCc_ast_new_expression_literal(mCc_ast_new_literal_int($2))); loc($$, @1);}
		   | unary_op FLOAT_LITERAL						{ $$ = mCc_ast_new_expression_unary_op($1, mCc_ast_new_expression_literal(mCc_ast_new_literal_float($2))); loc($$, @1);}
		   | IDENTIFIER									{ $$ = mCc_ast_new_expression_identifier($1); loc($$, @1);}
		   | IDENTIFIER LBRACKET expression RBRACKET	{ $$ = mCc_ast_new_expression_array_identifier($1, $3); loc($$, @1);}
	       | call_expr									{ $$ = mCc_ast_new_expression_function_call($1); loc($$, @1);}
		   | unary_op expression						{ $$ = mCc_ast_new_expression_unary_op($1, $2); loc($$, @1);}
           | LPARENTH expression RPARENTH    			{ $$ = mCc_ast_new_expression_parenth($2); loc($$, @1);}
		  // | error										{ yyerror(scanner, "error");}
           ;											

single_expr_lev1:	single_expr_lev2 binary_op_add single_expr_lev1	{ $$ = mCc_ast_new_expression_binary_op($2, $1, $3); loc($$, @1);}
				|	single_expr_lev2								{ $$ = $1; loc($$, @1);}
				;

single_expr_lev2:	single_expr binary_op_mul single_expr_lev2 	{ $$ = mCc_ast_new_expression_binary_op($2, $1, $3); loc($$, @1);}
				|	single_expr									{ $$ = $1; loc($$, @1);}
				;

expression: single_expr_lev1 binary_op expression { $$ = mCc_ast_new_expression_binary_op($2, $1, $3); loc($$, @1);}
		| 	single_expr_lev1                      { $$ = $1; loc($$, @1);}
        ;

literal: INT_LITERAL  		{ $$ = mCc_ast_new_literal_int($1); loc($$, @1); }
       | FLOAT_LITERAL 		{ $$ = mCc_ast_new_literal_float($1); loc($$, @1); }
	   | BOOL_LITERAL		{ $$ = mCc_ast_new_literal_bool($1); loc($$, @1); }
	   | STRING_LITERAL 	{ $$ = mCc_ast_new_literal_string($1); loc($$, @1); }
       ;

type:	INT_TYPE 	{ $$ = MCC_AST_DATA_TYPE_INT; }
	|	FLOAT_TYPE	{ $$ = MCC_AST_DATA_TYPE_FLOAT; }
	|	BOOL_TYPE	{ $$ = MCC_AST_DATA_TYPE_BOOL; }
	|	STRING_TYPE	{ $$ = MCC_AST_DATA_TYPE_STRING; }
	;

statement_list:	statement_list statement	{	
													struct mCc_ast_statement* t = $1;
													if(t == NULL){
														$$ = $2;
													}else{
														while(t->next_statement != NULL){
															t = t->next_statement;
														}
														t->next_statement = $2;
														$$ = $1;
														loc($$, @1);
													}
												}
			|	statement					{ $$ = $1; loc($$, @1);}
			;

statement:	 if_stmt			{ $$ = $1; loc($$, @1); }
         |   while_stmt		{ $$ = $1; loc($$, @1); }
         |   ret_stmt		{ $$ = $1; loc($$, @1); }
         |   declaration SEMICOLON { $$ = mCc_ast_new_declaration_statement($1); loc($$, @1); }
         |   assignment SEMICOLON  { $$ = mCc_ast_new_assign_statement($1); loc($$, @1); }
    	 |   expression SEMICOLON  { $$ = mCc_ast_new_expression_statement($1); loc($$, @1); }
         |   compound_stmt	{ $$ = $1; loc($$, @1); }
    	 ;



if_stmt:    IF_KEYWORD LPARENTH expression RPARENTH statement							{ $$ = mCc_ast_new_if_statement($3, $5, NULL); loc($$, @1); } /*else part missing, check if passing NULL is possible*/
        |   IF_KEYWORD LPARENTH expression RPARENTH statement ELSE_KEYWORD statement	{ $$ = mCc_ast_new_if_statement($3, $5, $7); loc($$, @1); }
        ;

while_stmt:   WHILE_KEYWORD LPARENTH expression RPARENTH statement			{ $$ = mCc_ast_new_while_statement($3, $5); loc($$, @1); }
          ;

ret_stmt:  RETURN_KEYWORD SEMICOLON												{ $$ = mCc_ast_new_return_statement(NULL); loc($$, @1); } /*check if return with no expression is possible*/
    	|  RETURN_KEYWORD expression SEMICOLON									{ $$ = mCc_ast_new_return_statement($2); loc($$, @1); }
        ;

compound_stmt: LBRACE statement_list RBRACE					{ 
																$$ = $2;
															}
			|  LBRACE  RBRACE								{ $$ = NULL;}
            ;




function_def:   type IDENTIFIER LPARENTH RPARENTH compound_stmt				{ $$ = mCc_ast_new_non_parameterized_function_def($2, $1, $5); loc($$, @1); }
        	|   type IDENTIFIER LPARENTH parameters RPARENTH compound_stmt  { $$ = mCc_ast_new_parameterized_function_def($2, $1, $4, $6); loc($$, @1); }
			|	VOID_TYPE IDENTIFIER LPARENTH RPARENTH compound_stmt		{ $$ = mCc_ast_new_non_parameterized_function_def($2, $1, $5); loc($$, @1); }
			|	VOID_TYPE IDENTIFIER LPARENTH parameters RPARENTH compound_stmt  { $$ = mCc_ast_new_parameterized_function_def($2, $1, $4, $6); loc($$, @1); }
			;

function_list:	function_list function_def	{ 
													struct mCc_ast_function_def* t = $1;
													if(t == NULL){
														$$ = $2;
													}else{
														while(t->next_function_def != NULL){
															t = t->next_function_def;
														}
														t->next_function_def = $2;
														$$ = $1;
														loc($$, @1);
													}
													
											}
			|	function_def				{ $$ = $1; loc($$, @1); }
			;


parameters:   declaration					{ $$ = $1; loc($$, @1); }
          |   parameters COMMA declaration	{
												struct mCc_ast_declaration* t = $1;
												if(t == NULL){
													$$ = $3;
												}else{
													while(t->next_declaration != NULL){
														t = t->next_declaration;
													}
													t->next_declaration = $3;
													$$ = $1;
													loc($$, @1);
												}
											}
          ;

call_expr:	IDENTIFIER LPARENTH RPARENTH		    { $$ = 	mCc_ast_new_non_parameterized_function_call($1); loc($$, @1); }
		|	IDENTIFIER LPARENTH arguments RPARENTH	{ $$ = mCc_ast_new_parameterized_function_call($1, $3); loc($$, @1); }
		;

arguments:	expression					{ $$ = $1; }
		| 	arguments COMMA expression 	{
												struct mCc_ast_expression* t = $1;
												if(t == NULL){
													$$ = $3;
												}else{
													while(t->next_expr != NULL){
														t = t->next_expr;
													}
													t->next_expr = $3;
													$$ = $1;
													loc($$, @1);
												}

											}
		;


program:	function_list			{ $$ = mCc_ast_new_program($1); loc($$, @1); }
	   ;
%%

#include <assert.h>

#include "scanner.h"

void mCc_parser_error(
    YYLTYPE *locp, yyscan_t *scanner, struct mCc_parser_result *result)
{
	result->status = MCC_PARSER_STATUS_SYNTAX_ERROR;
	//just store error-location
	result->error_location.sloc.start_line = locp->first_line;
	result->error_location.sloc.start_col = locp->first_column;
	result->error_location.sloc.end_line = locp->last_line;
	result->error_location.sloc.end_col = locp->last_column;
}

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
	
	if (yyparse(scanner, &result) != 0) {
		// is already set inside the yyerror-function during parsing
		//result.status = MCC_PARSER_STATUS_UNKNOWN_ERROR;
	}	

	mCc_parser_lex_destroy(scanner);

	return result;
}

/*
 * Free ast depending on the parsed-top-level and already parsed ast-elements
 * (=> do cleanup if necessary)
 */
void mCc_parser_destroy_parser(struct mCc_parser_result result)
{
	switch (result.top_level_type) {
	case MCC_PARSER_TOP_LEVEL_EXPRESSION:
		if (result.expression) {
			mCc_ast_delete_expression(result.expression);
		}
		break;
	case MCC_PARSER_TOP_LEVEL_PROGRAM:
		if (result.program) {
			mCc_ast_delete_program(result.program);
		}
		break;
	case MCC_PARSER_TOP_LEVEL_STATEMENT:
		if (result.statement) {
			mCc_ast_delete_statement(result.statement);
		}
		break;
	case MCC_PARSER_TOP_LEVEL_ASSIGNMENT:
		if (result.assignment) {
			mCc_ast_delete_assignment(result.assignment);
		}
		break;
	case MCC_PARSER_TOP_LEVEL_DECLARATION:
		if (result.declaration) {
			mCc_ast_delete_declaration(result.declaration);
		}
		break;
	case MCC_PARSER_TOP_LEVEL_FUNCTION_DEF:
		if (result.function_def) {
			mCc_ast_delete_function_def(result.function_def);
		}
		break;
	}
}

void mCc_parser_print_status(FILE *out, struct mCc_parser_result result)
{
	switch (result.status) {
	case MCC_PARSER_STATUS_OK: fprintf(out, "Parsing successfull\n"); break;
	case MCC_PARSER_STATUS_UNABLE_TO_OPEN_STREAM:
		fprintf(out, "Could not open stream\n");
		break;
	case MCC_PARSER_STATUS_UNKNOWN_ERROR:
		fprintf(out, "Unknown error occurred\n");
		break;
	case MCC_PARSER_STATUS_SYNTAX_ERROR:
		fprintf(out, "Syntax error near line %d col %d\n",
		        result.error_location.sloc.start_line,
		        result.error_location.sloc.start_col);
		break;
	}
}