#pragma once

#include "espeak-ng/espeak_ng.h" 

void handlePossibleError(espeak_ng_STATUS result, espeak_ng_ERROR_CONTEXT* context = nullptr);
