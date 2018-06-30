#ifndef MCC_ASSEMBLY_DATA_H
#define MCC_ASSEMBLY_DATA_H

#include "basic_tac.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_assembly_argument_list {
	struct mCc_tac_element *argument;
	int open_scope;
	struct mCc_assembly_argument_list *next;
};

struct mCc_assembly_data {
	int current_stack_pos;
	int func_scope_counter;
	int arg_scope_counter;
	struct mCc_assembly_argument_list *arg_list;
};

#ifdef __cplusplus
}
#endif

#endif
