#include <stdexcept>
#include <stdio.h>
#include <sstream>
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

const string GetErrorMessage(espeak_ng_STATUS result, const string reason, espeak_ng_ERROR_CONTEXT& context)
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

	if (reason != "")
	{
		stringstream buffer;
		buffer << reason << ". " << message;
		return buffer.str();
	}

	return message;
}

void RaiseExceptionUnlessSucceeded(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context)
{
	RaiseExceptionUnlessSucceeded(result, "", context);
}

void RaiseExceptionUnlessSucceeded(espeak_ng_STATUS result, const string reason, espeak_ng_ERROR_CONTEXT* context)
{
	if (result != ENS_OK)
	{
		espeak_ng_ERROR_CONTEXT errorContext = context != nullptr ? *context : nullptr;
		const string message = GetErrorMessage(result, reason, errorContext);

		if (context != nullptr)
		{
			espeak_ng_ClearErrorContext(context);
		}

		throw runtime_error(message);
	}
}
