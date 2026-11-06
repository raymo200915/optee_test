/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

/*
 * Intentionally do not include asm.S or emit a GNU property. This object
 * clears CFI_LP_UNLABELED during the final ELF AND merge.
 */
	.section .text.zicfilp_compat, "ax", %progbits
	.p2align 2
	.global zicfilp_compat_indirect_jump
	.type zicfilp_compat_indirect_jump, %function
zicfilp_compat_indirect_jump:
	jr a0
	.size zicfilp_compat_indirect_jump, .-zicfilp_compat_indirect_jump

	.p2align 2
	.global zicfilp_compat_non_lpad_target
	.type zicfilp_compat_non_lpad_target, %function
zicfilp_compat_non_lpad_target:
	ret
	.size zicfilp_compat_non_lpad_target, .-zicfilp_compat_non_lpad_target

	.section .note.GNU-stack, "", %progbits
