/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

#include <ta_zicfilp_test.h>

#define TA_UUID		TA_ZICFILP_TEST_UUID

#define TA_FLAGS	(TA_FLAG_USER_MODE | TA_FLAG_EXEC_DDR)
#define TA_STACK_SIZE	(2 * 1024)
#define TA_DATA_SIZE	(32 * 1024)

#endif /* USER_TA_HEADER_DEFINES_H */
