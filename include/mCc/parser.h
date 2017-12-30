#ifndef MCC_PARSER_H
#define MCC_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mC_ast_expression *mC_parser_parse_string(const char *input, size_t len);

struct mC_ast_expression *mC_parser_parse_file(FILE *input);

#ifdef __cplusplus
}
#endif

#endif
