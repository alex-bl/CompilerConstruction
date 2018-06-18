#ifndef MCC_ASSEMBLY_OFFSET_H
#define MCC_ASSEMBLY_OFFSET_H

#include "basic_tac.h"
#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_assembly_offset_holder {
	map_int_t offset_table;
	map_int_t param_table;
	int actual_offset;
};

void mCc_assembly_calculate_stack_offsets(
    struct mCc_tac_element *first_tac_element);

#ifdef __cplusplus
}
#endif

#endif
