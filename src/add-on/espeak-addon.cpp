#include <nan.h>
#include "espeak-wrapper.h"

void InitAll(v8::Local<v8::Object> exports) {
	EspeakWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)
