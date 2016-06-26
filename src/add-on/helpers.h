#pragma once

#include <string>
#include <nan.h>
#include <espeak-ng/espeak_ng.h>

using namespace std;

void HandlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context = nullptr);

string toString(v8::Local<v8::Value> value);
