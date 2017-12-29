#ifndef MCC_PARSER_H
#define MCC_PARSER_H

#include <stdio.h>

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mC_ast_expression* mC_parser_run(FILE *in);

#ifdef __cplusplus
}
#endif

#endif
