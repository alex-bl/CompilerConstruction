#ifndef MCC_PARSER_H
#define MCC_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_parser_status {
	MCC_PARSER_STATUS_OK,
	MCC_PARSER_STATUS_UNABLE_TO_OPEN_STREAM,
	MCC_PARSER_STATUS_UNKNOWN_ERROR,
};

struct mCc_parser_result {
	enum mCc_parser_status status;
	
	union{
		struct mCc_ast_expression *expression;
		struct mCc_ast_program *program;
		struct mCc_ast_statement *statement;
		struct mCc_ast_assignment *assignment;
		struct mCc_ast_declaration *declaration;
		struct mCc_ast_function_def *function_def;
	};
};

struct mCc_parser_result_final {
	enum mCc_parser_status status;
	struct mCc_ast_program *program;
};

struct mCc_parser_result mCc_parser_parse_string(const char *input);

struct mCc_parser_result mCc_parser_parse_file(FILE *input);

#ifdef __cplusplus
}
#endif

#endif
