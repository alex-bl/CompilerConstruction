#include "assembly_generator.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "assembly_arithmetic_op.h"
#include "assembly_binary_op_logical.h"
#include "assembly_jump.h"
#include "assembly_special.h"
#include "assembly_unary_op.h"

void mCc_assembly_generate_tac_elem(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *tac_elem)
{
	enum mCc_tac_operation tac_op = tac_elem->tac_operation;

	switch (tac_op) {
	case MCC_TAC_OPARATION_EMPTY: gen_cb.empty(gen_cb.out, tac_elem); break;
	case MCC_TAC_OPARATION_BINARY_OP_ADD:
		gen_cb.add(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_SUB:
		gen_cb.sub(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_MUL:
		gen_cb.mul(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_DIV:
		gen_cb.div(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_LESS_THAN:
		gen_cb.less_than(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_GREATER_THAN:
		gen_cb.greater_than(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_LESS_OR_EQUALS_THAN:
		gen_cb.less_or_equals_than(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_GREATER_OR_EQUALS_THAN:
		gen_cb.greater_or_equals_than(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_AND:
		gen_cb.and (gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_OR:
		gen_cb.or (gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_EQUALS:
		gen_cb.equals(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_BINARY_OP_NOT_EQUALS:
		gen_cb.not_equals(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_UNARY_OP_MINUS:
		gen_cb.minus(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_UNARY_OP_NEGATION:
		gen_cb.negation(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_COPY: gen_cb.copy(gen_cb.out, tac_elem); break;
	case MCC_TAC_OPARATION_UNCONDITIONAL_JUMP:
		gen_cb.unconditional_jump(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_CONDITIONAL_JUMP:
		gen_cb.conditional_jump(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_PROCEDURAL_CALL:
		gen_cb.procedural_call(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_RETURN:
		gen_cb.return_op(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_INDEXING:
		gen_cb.indexing(gen_cb.out, tac_elem);
		break;
	case MCC_TAC_OPARATION_LABLE: gen_cb.label(gen_cb.out, tac_elem); break;
	}
}

void mCc_assembly_generate(struct mCc_assembly_generator gen_cb,
                           struct mCc_tac_element *first_tac_elem)
{
	struct mCc_tac_element *next_tac_elem = first_tac_elem;
	while (next_tac_elem) {
		mCc_assembly_generate_tac_elem(gen_cb, next_tac_elem);
		next_tac_elem = next_tac_elem->tac_next_element;
	}
}

struct mCc_assembly_generator gen_setup(FILE *out)
{
	return (struct mCc_assembly_generator){
		.out = out,
		.empty = mCc_assembly_generate_empty,
		.add = mCc_assembly_generate_add,
		.sub = mCc_assembly_generate_sub,
		.mul = mCc_assembly_generate_mul,
		.div = mCc_assembly_generate_div,
		.less_than = mCc_assembly_generate_less_than,
		.greater_than = mCc_assembly_generate_greater_than,
		.less_or_equals_than = mCc_assembly_generate_less_or_equals_than,
		.greater_or_equals_than = mCc_assembly_generate_greater_or_equals_than,
		.and = mCc_assembly_generate_and,
		.or = mCc_assembly_generate_or,
		.equals = mCc_assembly_generate_equals,
		.not_equals = mCc_assembly_generate_not_equals,
		.minus = mCc_assembly_generate_minus,
		.negation = mCc_assembly_generate_negation,
		.copy = mCc_assembly_generate_copy,
		.unconditional_jump = mCc_assembly_generate_unconditional_jump,
		.conditional_jump = mCc_assembly_generate_conditional_jump,
		.procedural_call = mCc_assembly_generate_procedural_call,
		.return_op = mCc_assembly_generate_return_op,
		.indexing = mCc_assembly_generate_indexing,
		.label = mCc_assembly_generate_label,
	};
}
