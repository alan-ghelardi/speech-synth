#pragma once

#include <nan.h>
#include "espeak.h"

class EspeakWrapper 
	: public Nan::ObjectWrap
{

private:
	static Nan::Persistent<v8::Function> constructor;
	Espeak* espeak;

	EspeakWrapper(const char* dataPath, bool isCompiling);
	~EspeakWrapper();

	static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void CompileData(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Speak(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Stop(const Nan::FunctionCallbackInfo<v8::Value>& info);

public:
	static void Init(v8::Local<v8::Object> exports);

};
