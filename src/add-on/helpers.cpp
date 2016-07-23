#include <stdexcept>
#include <stdio.h>
#include "helpers.h"

using namespace std;

char* ReadMessageFrom(FILE*& stream)
{
	fseek(stream, 0, SEEK_END);
	long size = ftell(stream);
	rewind(stream);
	char* message = new char[size * sizeof(char)];
	fgets(message, size, stream);
	return message;
}

const char* GetErrorMessage(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT context)
{
	FILE* stream = nullptr;
	char* message = nullptr;
	tmpfile_s(&stream);

	if (stream != nullptr)
	{
		espeak_ng_PrintStatusCodeMessage(result, stream, context);
		message = ReadMessageFrom(stream);
	}
	else
	{
		int size = 512;
		message = new char[size * sizeof(char)];
		espeak_ng_GetStatusCodeMessage(result, message, size);
	}

	return message;
}

void RaiseExceptionUnlessSucceeded(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context)
{
	if (result != ENS_OK)
	{
		const char* message = GetErrorMessage(result, *context);

		if (context != nullptr)
		{
			espeak_ng_ClearErrorContext(context);
		}

		throw runtime_error(message);
	}
}

const char* ToString(v8::Local<v8::String> value)
{
	Nan::Utf8String utf8String(value);
	return *utf8String;
}
