/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

/*
 * This shared object deliberately has no RISC-V CFI property. A protected
 * TA must reject it when it is requested through dlopen().
 */
	.section .text.zicfilp_late, "ax", %progbits
	.p2align 2
	.global zicfilp_late_no_lpad
	.type zicfilp_late_no_lpad, %function
zicfilp_late_no_lpad:
	ret
	.size zicfilp_late_no_lpad, .-zicfilp_late_no_lpad

	.section .note.GNU-stack, "", %progbits
