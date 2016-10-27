#include <nan.h>
#include "espeak-wrapper.h"

void Init(v8::Local<v8::Object> exports) 
{
	EspeakWrapper::Init(exports);
}

NODE_MODULE(espeak_addon, Init)
