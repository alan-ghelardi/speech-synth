#pragma once

#include <string>
#include <nan.h>
#include <espeak-ng/espeak_ng.h>

using namespace std;

void HandlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context = nullptr);

const string ToString(v8::Local<v8::String> value);
