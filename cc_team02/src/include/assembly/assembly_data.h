#ifndef MCC_ASSEMBLY_DATA_H
#define MCC_ASSEMBLY_DATA_H

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_assembly_argument_list {
	struct mCc_tac_element *argument;
	struct mCc_assembly_argument_list *next;
};

struct mCc_assembly_data {
	int current_stack_pos;
	struct mCc_assembly_argument_list *arg_list;
};

#ifdef __cplusplus
}
#endif

#endif
