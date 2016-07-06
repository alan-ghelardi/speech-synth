#include <excpt.h>
#include "helpers.h"

void HandlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context)
{
	if (result != ENS_OK)
	{
		char message[512];
		espeak_ng_GetStatusCodeMessage(result, message, sizeof(message));

		if (context != nullptr)
		{
			espeak_ng_ClearErrorContext(context);
		}

		throw runtime_error(message);
	}
}

const string ToString(v8::Local<v8::String> value)
{
	Nan::Utf8String utf8String(value);
	const string aString(*utf8String);
	return aString;
}
