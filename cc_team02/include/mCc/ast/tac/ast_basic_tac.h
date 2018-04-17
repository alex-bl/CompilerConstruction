#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include <stdio.h>
#include "../basis/ast_data_type.h"

#define LABEL_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

void tac_begin(FILE *out);

void tac_end(FILE *out);

void tac_node(FILE *out, const void *node, const char *label);

void tac_edge(FILE *out, const void *src_node, const void *dst_node,
                    const char *label);

void tac_edge_if_dest_exists(FILE *out, const void *src_node,
                                   const void *dst_node, const char *label);

const char *print_data_type(enum mCc_ast_data_type type);

#ifdef __cplusplus
}
#endif

#endif
