#ifndef MCC_PARSER_H
#define MCC_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mC_parser_status {
	MC_PARSER_STATUS_OK,
	MC_PARSER_STATUS_UNABLE_TO_OPEN_STREAM,
	MC_PARSER_STATUS_UNKNOWN_ERROR,
};

struct mC_parser_result {
	enum mC_parser_status status;
	struct mC_ast_expression *expression;
};

struct mC_parser_result mC_parser_parse_string(const char *input);

struct mC_parser_result mC_parser_parse_file(FILE *input);

#ifdef __cplusplus
}
#endif

#endif
