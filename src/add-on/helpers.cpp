#include "helpers.h"

void handlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context)
{
	if (result != ENS_OK)
	{
		espeak_ng_PrintStatusCodeMessage(result, stderr, *context);
		if (context != nullptr)
		{
			espeak_ng_ClearErrorContext(context);
		}
	}
}
