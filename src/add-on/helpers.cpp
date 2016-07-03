#include "helpers.h"

void HandlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context)
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

const string ToString(v8::Local<v8::String> value)
{
	Nan::Utf8String utf8String(value);
	const string aString(*utf8String);
	return aString;
}
