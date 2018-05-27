#ifndef MCC_ASSEMBLY_GENERATOR_H
#define MCC_ASSEMBLY_GENERATOR_H

#include <stdio.h>

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mCc_generate_assembly_cb)(FILE *, struct mCc_tac_element *);

struct mCc_assembly_generator {
	FILE *out;
	mCc_generate_assembly_cb empty;
	mCc_generate_assembly_cb add;
	mCc_generate_assembly_cb sub;
	mCc_generate_assembly_cb mul;
	mCc_generate_assembly_cb div;
	mCc_generate_assembly_cb less_than;
	mCc_generate_assembly_cb greater_than;
	mCc_generate_assembly_cb less_or_equals_than;
	mCc_generate_assembly_cb greater_or_equals_than;
	mCc_generate_assembly_cb and;
	mCc_generate_assembly_cb or ;
	mCc_generate_assembly_cb equals;
	mCc_generate_assembly_cb not_equals;
	mCc_generate_assembly_cb minus;
	mCc_generate_assembly_cb negation;
	mCc_generate_assembly_cb copy;
	mCc_generate_assembly_cb unconditional_jump;
	mCc_generate_assembly_cb conditional_jump;
	mCc_generate_assembly_cb procedural_call;
	mCc_generate_assembly_cb return_op;
	mCc_generate_assembly_cb indexing;
	mCc_generate_assembly_cb label;
};

#ifdef __cplusplus
}
#endif

#endif
