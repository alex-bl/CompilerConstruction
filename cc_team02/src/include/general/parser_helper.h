#ifndef MCC_PARSER_HELPER_H
#define MCC_PARSER_HELPER_H

#include "ast_function.h"
#include "ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_parser_include_functions(struct mCc_ast_program *to_include,
                                  struct mCc_ast_program *prog);

#ifdef __cplusplus
}
#endif

#endif
