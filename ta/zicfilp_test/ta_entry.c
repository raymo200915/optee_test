/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#include <dlfcn.h>
#include <ta_zicfilp_test.h>
#include <tee_internal_api.h>

void zicfilp_indirect_jump(void (*fn)(void));
void zicfilp_non_lpad_target(void);

static __attribute__((noinline)) int zicfilp_target(int value)
{
	return value + 1;
}

static __attribute__((noinline)) int zicfilp_indirect_call(int (*fn)(int))
{
	return fn(41);
}

TEE_Result TA_CreateEntryPoint(void)
{
	return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types __unused,
				    TEE_Param params[4] __unused,
				    void **session_ctx __unused)
{
	return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void *session_ctx __unused)
{
}

TEE_Result TA_InvokeCommandEntryPoint(void *session_ctx __unused,
				      uint32_t cmd, uint32_t param_types,
				      TEE_Param params[4])
{
	int (*volatile fn)(int) = zicfilp_target;

	switch (cmd) {
	case TA_ZICFILP_CMD_INDIRECT_CALL:
		if (param_types != TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_OUTPUT,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE))
			return TEE_ERROR_BAD_PARAMETERS;

		params[0].value.a = zicfilp_indirect_call(fn);
		return TEE_SUCCESS;
	case TA_ZICFILP_CMD_NON_LPAD:
	case TA_ZICFILP_CMD_NON_LPAD_FPU_OFF:
		if (param_types != TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE))
			return TEE_ERROR_BAD_PARAMETERS;

		zicfilp_indirect_jump(zicfilp_non_lpad_target);
		return TEE_ERROR_GENERIC;
	case TA_ZICFILP_CMD_LATE_UNMARKED_LIBRARY:
		if (param_types != TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE,
						    TEE_PARAM_TYPE_NONE))
			return TEE_ERROR_BAD_PARAMETERS;

		if (dlopen("c6d22818-48c1-460e-87d3-8569d6959a70",
			   RTLD_NOW | RTLD_GLOBAL | RTLD_NODELETE))
			return TEE_ERROR_GENERIC;
		return TEE_SUCCESS;
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}
