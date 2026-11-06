/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#include <asm.S>

FUNC zicfilp_indirect_jump, :
	jr a0
END_FUNC zicfilp_indirect_jump

/*
 * This is deliberately not declared with FUNC(): an indirect transfer to
 * it must raise a software-check exception when senvcfg.LPE is enabled.
 */
	.section .text.zicfilp_non_lpad_target, "ax", %progbits
	.p2align 2
	.global zicfilp_non_lpad_target
	.type zicfilp_non_lpad_target, %function
zicfilp_non_lpad_target:
	ret
	.size zicfilp_non_lpad_target, .-zicfilp_non_lpad_target

/* Preserve CFI_LP_UNLABELED for this otherwise hand-written object. */
RISCV_CFI(emit_riscv_feature_1_and RISCV_TA_FEATURE_1_AND)
