#include "espeak-wrapper.h"
#include "helpers.h"

Nan::Persistent<v8::Function> EspeakWrapper::constructor;

EspeakWrapper::EspeakWrapper(const string dataPath):
	espeak(dataPath)
{
}

EspeakWrapper::~EspeakWrapper()
{
}

void EspeakWrapper::Init(v8::Local<v8::Object> exports)
{
	Nan::HandleScope scope;

	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Espeak").ToLocalChecked());
	Nan::SetPrototypeMethod(tpl, "speak", Speak);
	Nan::SetPrototypeMethod(tpl, "cancel", Cancel);
	constructor.Reset(tpl->GetFunction());
	exports->Set(Nan::New("Espeak").ToLocalChecked(), tpl->GetFunction());
}

void EspeakWrapper::New(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	if (!info.IsConstructCall())
	{
		Nan::ThrowError("Invalid usage. Use the `new` operator for creating a new instance of Espeak");
	}
	else
	{
		const string dataPath = toString(info[0]);
		EspeakWrapper* wrapper = new EspeakWrapper(dataPath);
		wrapper->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
}

void EspeakWrapper::Speak(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	const string text = toString(info[0]);
	wrapper->espeak.Speak(text);
	info.GetReturnValue().SetUndefined();
}

void EspeakWrapper::Cancel(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	wrapper->espeak.Cancel();
	info.GetReturnValue().SetUndefined();
}
