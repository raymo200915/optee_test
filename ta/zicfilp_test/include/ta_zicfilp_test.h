/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#ifndef TA_ZICFILP_TEST_H
#define TA_ZICFILP_TEST_H

#define TA_ZICFILP_TEST_UUID \
	{ 0xa25e40ad, 0xe1f9, 0x4e1e, \
		{ 0x9d, 0x5b, 0x72, 0x03, 0xc4, 0xd8, 0x28, 0xc6 } }

#define TA_ZICFILP_CMD_INDIRECT_CALL		0
#define TA_ZICFILP_CMD_NON_LPAD		1
#define TA_ZICFILP_CMD_NON_LPAD_FPU_OFF	2
#define TA_ZICFILP_CMD_LATE_UNMARKED_LIBRARY	3

#endif /* TA_ZICFILP_TEST_H */
