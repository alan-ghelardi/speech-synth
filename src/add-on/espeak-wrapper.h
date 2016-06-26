#pragma once

#include <string>
#include <nan.h>
#include "espeak.h"

using namespace std;

class EspeakWrapper : public Nan::ObjectWrap
{

private:
	static Nan::Persistent<v8::Function> constructor;
	Espeak espeak;

	explicit EspeakWrapper(const string dataPath);
	~EspeakWrapper();

	static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Speak(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Cancel(const Nan::FunctionCallbackInfo<v8::Value>& info);

public:
	static void Init(v8::Local<v8::Object> exports);

};
