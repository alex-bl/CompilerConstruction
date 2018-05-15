#ifndef MCC_AST_BASIC_PRINTING_H
#define MCC_AST_BASIC_PRINTING_H

#include <stdio.h>

#define LABEL_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_begin(FILE *out);

void mCc_ast_print_dot_end(FILE *out);

void mCc_ast_print_dot_node(FILE *out, const void *node, const char *label);

void mCc_ast_print_dot_edge(FILE *out, const void *src_node, const void *dst_node,
                    const char *label);

void mCc_ast_print_dot_edge_if_dest_exists(FILE *out, const void *src_node,
                                   const void *dst_node, const char *label);

#ifdef __cplusplus
}
#endif

#endif
