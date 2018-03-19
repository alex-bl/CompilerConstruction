#ifndef MCC_AST_H
#define MCC_AST_H

#ifdef __cplusplus
extern "C" {
#endif

/* Forward Declarations */
struct mCc_ast_expression;
struct mCc_ast_literal;

/* ---------------------------------------------------------------- AST Node */

struct mCc_ast_source_location {
	int start_line;
	int start_col;
	int end_line;
	int end_col;
};

/* Data contained by every AST node. */
struct mCc_ast_node {
	struct mCc_ast_source_location sloc;
};

/* --------------------------------------------------------------- Operators */

enum mCc_ast_binary_op {
	MCC_AST_BINARY_OP_ADD,
	MCC_AST_BINARY_OP_SUB,
	MCC_AST_BINARY_OP_MUL,
	MCC_AST_BINARY_OP_DIV,
};

enum mCc_ast_unary_op {
	MCC_AST_UNARY_OP_MINUS,
	MCC_AST_UNARY_OP_NEGATION,
};

/* ------------------------------------------------------------- Expressions */

enum mCc_ast_expression_type {
	MCC_AST_EXPRESSION_TYPE_LITERAL,
	MCC_AST_EXPRESSION_TYPE_BINARY_OP,
	MCC_AST_EXPRESSION_TYPE_PARENTH,
	/*newly added*/
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER,
	MCC_AST_EXPRESSION_TYPE_CALL_EXPR,
	MCC_AST_EXPRESSION_TYPE_UNARY_OP
};

struct mCc_ast_expression {
	struct mCc_ast_node node;

	enum mCc_ast_expression_type type;
	union {
		/* MCC_AST_EXPRESSION_TYPE_LITERAL */
		struct mCc_ast_literal *literal;

		/* MCC_AST_EXPRESSION_TYPE_BINARY_OP */
		struct {
			enum mCc_ast_binary_op op;
			struct mCc_ast_expression *lhs;
			struct mCc_ast_expression *rhs;
		};

		/* MCC_AST_EXPRESSION_TYPE_PARENTH */
		struct mCc_ast_expression *expression;

		/* MCC_AST_EXPRESSION_TYPE_UNARY_OP */
		struct {
			enum mCc_ast_unary_op unary_op;
			struct mCc_ast_expression *unary_rhs;
		};
	};
};

struct mCc_ast_expression *
mCc_ast_new_expression_literal(struct mCc_ast_literal *literal);

struct mCc_ast_expression *
mCc_ast_new_expression_binary_op(enum mCc_ast_binary_op op,
                                 struct mCc_ast_expression *lhs,
                                 struct mCc_ast_expression *rhs);

struct mCc_ast_expression *
mCc_ast_new_expression_parenth(struct mCc_ast_expression *expression);

/*added*/
struct mCc_ast_expression *
mCc_ast_new_expression_unary_op(struct mCc_ast_expression *expression);

void mCc_ast_delete_expression(struct mCc_ast_expression *expression);

/* ---------------------------------------------------------------- Literals */

enum mCc_ast_literal_type {
	MCC_AST_LITERAL_TYPE_INT,
	MCC_AST_LITERAL_TYPE_FLOAT,
	MCC_AST_LITERAL_TYPE_BOOL,
	MCC_AST_LITERAL_TYPE_STRING
};

struct mCc_ast_literal {
	struct mCc_ast_node node;

	enum mCc_ast_literal_type type;
	union {
		/* MCC_AST_LITERAL_TYPE_INT */
		long i_value;

		/* MCC_AST_LITERAL_TYPE_FLOAT */
		double f_value;

		/* MCC_AST_LITERAL_TYPE_BOOL */
		bool b_value;

		/* MCC_AST_LITERAL_TYPE_STRING */
		const char *s_value;
	};
};

struct mCc_ast_literal *mCc_ast_new_literal_int(long value);

struct mCc_ast_literal *mCc_ast_new_literal_float(double value);

/* added */
struct mCc_ast_literal *mCc_ast_new_literal_bool(bool value);

struct mCc_ast_literal *mCc_ast_new_literal_string(const char *value);

void mCc_ast_delete_literal(struct mCc_ast_literal *literal);

/* ---------------------------------------------------------------- Identifiers
 */

struct mCc_ast_identifier {
	struct mCc_ast_node node;
	const char *identifier_name;
};

struct mCc_ast_identifier *mCc_ast_new_identifier(const char *name);

void mCc_ast_delete_identifier(struct mCc_ast_identifier *name);

/* ---------------------------------------------------------------- Declaration
 */
enum mCc_ast_declaration_type {
	MCC_AST_DECLARATION_PRIMITIVE,
	MCC_AST_DECLARATION_ARRAY
};

struct mCc_ast_declaration {
	struct mCc_ast_node node;

	enum mCc_ast_declaration_type declaration_type;
	enum mCc_ast_literal_type data_type;

	union {
		/* MCC_AST_IDENTIFIER */
		struct mCc_ast_identifier identifier;

		/* MCC_AST_DECLARATION_TYPE_ARRAY */
		struct {
			struct mCc_ast_identifier array_identifier;
			size_t size;
		};
	};
};

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  const char *identifier);

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              const char *identifier, size_t size);

void mCc_ast_delete_primitive_declaration(struct mCc_ast_declaration *name);

void mCc_ast_delete_array_declaration(struct mCc_ast_declaration *name);

/* ---------------------------------------------------------------- Assignment
 */

enum mCc_ast_assignment_type {
	MCC_AST_ASSIGNMENT_PRIMITIVE,
	MCC_AST_ASSIGNMENT_ARRAY
};

struct mCc_ast_assignment {
	struct mCc_ast_node node;
	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier *identifier;
	enum mCc_ast_assignment_type assignment_type;

	union {
		/* MCC_AST_EXPRESSION */
		struct mCc_ast_expression *assigned_expression;

		struct {
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *array_index_expression;
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *array_assigned_expression;
		};
	};
};

struct mCc_ast_assignment *mCc_ast_new_primitive_assignment(
    const char *identifier,
    struct mCc_ast_expression *assigned_expresion_value);

struct mCc_ast_assignment *
mCc_ast_new_array_assignment(const char *identifier,
                             struct mCc_ast_expression *index,
                             struct mCc_ast_expression *value);

void mCc_ast_delete_primitive_declaration(struct mCc_ast_assignment *name);

void mCc_ast_delete_array_declaration(struct mCc_ast_assignment *name);

/* ---------------------------------------------------------------- Statements
 */

enum mCc_ast_statement_type {
	MCC_AST_STATEMENT_IF,
	MCC_AST_STATEMENT_WHILE,
	MCC_AST_STATEMENT_RETURN,
	MCC_AST_STATEMENT_COMPOUND
};

/**
 * This is just a "helper-struct" because it is needed inside the
 * "function-block"
 */
struct mCc_ast_compound_statement {
	/* MCC_AST_EXPRESSION */
	struct mCc_ast_statement *statements;
	/*TODO: a long or smaller? :-)*/
	long nr_of_statements;
};

struct mCc_ast_statement {
	struct mCc_ast_node node;

	enum mCc_ast_statement_type statement_type;

	union {

		// if
		struct {
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *condition_expression;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *if_statement;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *else_statement;
		};

		// while
		struct {
			struct mCc_ast_expression *loop_condition_expression;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *while_statement;
		};

		// return
		/* MCC_AST_EXPRESSION */
		struct mCc_ast_expression *return_expression;

		// compound-statement
		struct mCc_ast_compound_statement *compound_statement;
	};
};

struct mCc_ast_statement
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt);

struct mCc_ast_statement
mCc_ast_new_while_statement(struct mCc_ast_expression *loop_expr,
                            struct mCc_ast_statement *while_stmt);
struct mCc_ast_statement
mCc_ast_new_return_statement(struct mCc_ast_statement *return_stmt);

struct mCc_ast_statement mCc_ast_new_compound_statement(
    struct mCc_ast_compound_statement *compound_stmt);

/**
 * It just initializes the "helper-struct". It is not intended to use
 * immediately as action inside the parser
 *
 * @param stmts
 * @param nr_of_stmts
 * @return
 */
struct mCc_ast_compound_statement
mCc_ast_new_compound_statement_build(struct mCc_ast_statement *_stmts,
                                     long nr_of_stmts);

void mCc_ast_delete_if_statement(struct mCc_ast_statement *stmt);

void mCc_ast_delete_while_statement(struct mCc_ast_statement *stmt);

void mCc_ast_delete_return_statement(struct mCc_ast_statement *stmt);

void mCc_ast_delete_compound_statement(struct mCc_ast_statement *stmt);

/* ---------------------------------------------------------------- Function
 * definition*/

// TODO: really required separately or using mcc_type?
enum mCc_ast_function_return_type {
	MCC_AST_FUNCTION_RETURN_TYPE_VOID,
	MCC_AST_FUNCTION_RETURN_TYPE_INT,
	MCC_AST_FUNCTION_RETURN_TYPE_FLOAT,
	MCC_AST_FUNCTION_RETURN_TYPE_BOOL,
	MCC_AST_FUNCTION_RETURN_TYPE_STRING
};

struct mCc_ast_function_def {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier identifier;
	enum mCc_ast_function_return_type return_type;
	/* Just a helper */
	struct mCc_ast_compound_statement *compound_statement;

	struct {
		mCc_ast_declaration *parameters;
		/*TODO: size_t enough?*/
		size_t nr_of_parameters;
	};
};

struct mCc_ast_function_def
mCc_ast_new_void_function_def(const char *identifier);

struct mCc_ast_function_def mCc_ast_new_int_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_float_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_bool_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_string_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

void mCc_ast_delete_void_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_int_function_def(struct mCc_ast_function_def *function_def);

void mCc_ast_delete_float_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_bool_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_string_function_def(
    struct mCc_ast_function_def *function_def);

/* ---------------------------------------------------------------- Function
 * call*/

struct mCc_ast_function_call {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier identifier;

	struct {
		/* MCC_AST_EXPRESSION*/
		struct mCc_ast_expression *arguments;
		/*TODO: long here?*/
		long nr_expressions;
	};
};

struct mCc_ast_function_call
mCc_ast_new_int_function_def(const char *identifier,
                             struct mCc_ast_expression *args, long nr_args);

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call);

/* ---------------------------------------------------------------- Program */

struct mCc_ast_program {
	struct mCc_ast_node node;

	struct mCc_ast_function_def *function_defs;

	size_t nr_function_defs;
};

struct mCc_ast_program
mCc_ast_new_program(struct mCc_ast_function_def *function_defs,
                    size_t nr_function_defs);

void mCc_ast_delete_program(struct mCc_ast_program *program);

/*--------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
