#pragma once

#include <espeak-ng/espeak_ng.h>

void RaiseExceptionUnlessSucceeded(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context = nullptr);
