/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#include <ta_zicfilp_compat.h>
#include <tee_internal_api.h>

void zicfilp_compat_indirect_jump(void (*fn)(void));
void zicfilp_compat_non_lpad_target(void);

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
	if (cmd != TA_ZICFILP_COMPAT_CMD_INDIRECT_CALL ||
	    param_types != TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_OUTPUT,
					    TEE_PARAM_TYPE_NONE,
					    TEE_PARAM_TYPE_NONE,
					    TEE_PARAM_TYPE_NONE))
		return TEE_ERROR_BAD_PARAMETERS;

	/* This target has no LPAD and must be reached with LPE disabled. */
	zicfilp_compat_indirect_jump(zicfilp_compat_non_lpad_target);
	params[0].value.a = 17;
	return TEE_SUCCESS;
}
