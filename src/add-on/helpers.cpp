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

string toString(v8::Local<v8::Value> value)
{
	Nan::Utf8String utf8String(value);
	string aString(*utf8String);
	return aString;
}
