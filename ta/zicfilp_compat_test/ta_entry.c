/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2026, RISCStar Solutions Limited
 */

#include <ta_zicfilp_compat.h>
#include <ta_zicfilp_test.h>
#include <tee_internal_api.h>

void zicfilp_compat_indirect_jump(void (*fn)(void));
void zicfilp_compat_non_lpad_target(void);

static TEE_Result call_guarded_ta(void)
{
	const TEE_UUID uuid = TA_ZICFILP_TEST_UUID;
	TEE_TASessionHandle session = TEE_HANDLE_NULL;
	TEE_Param params[4] = { };
	uint32_t types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_OUTPUT,
					 TEE_PARAM_TYPE_NONE, TEE_PARAM_TYPE_NONE,
					 TEE_PARAM_TYPE_NONE);
	TEE_Result res = TEE_OpenTASession(&uuid, TEE_TIMEOUT_INFINITE, 0,
					   NULL, &session, NULL);

	if (res != TEE_SUCCESS)
		return res;
	res = TEE_InvokeTACommand(session, TEE_TIMEOUT_INFINITE,
				  TA_ZICFILP_CMD_INDIRECT_CALL,
				  types, params, NULL);
	TEE_CloseTASession(session);
	if (res == TEE_SUCCESS && params[0].value.a != 42)
		return TEE_ERROR_GENERIC;
	return res;
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
	TEE_Result res = TEE_SUCCESS;

	if ((cmd != TA_ZICFILP_COMPAT_CMD_INDIRECT_CALL &&
	     cmd != TA_ZICFILP_COMPAT_CMD_AFTER_GUARDED &&
	     cmd != TA_ZICFILP_COMPAT_CMD_AFTER_WAIT) ||
	    param_types != TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_OUTPUT,
					    TEE_PARAM_TYPE_NONE,
					    TEE_PARAM_TYPE_NONE,
					    TEE_PARAM_TYPE_NONE))
		return TEE_ERROR_BAD_PARAMETERS;

	if (cmd == TA_ZICFILP_COMPAT_CMD_AFTER_GUARDED)
		res = call_guarded_ta();
	else if (cmd == TA_ZICFILP_COMPAT_CMD_AFTER_WAIT)
		res = TEE_Wait(1);
	if (res != TEE_SUCCESS)
		return res;

	/* This target has no LPAD and must be reached with LPE disabled. */
	zicfilp_compat_indirect_jump(zicfilp_compat_non_lpad_target);
	params[0].value.a = 17;
	return TEE_SUCCESS;
}
