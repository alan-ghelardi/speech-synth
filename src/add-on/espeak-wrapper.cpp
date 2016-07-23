#include "espeak-wrapper.h"
#include "speech-worker.h"

Nan::Persistent<v8::Function> EspeakWrapper::constructor;

const char* ToString(v8::Local<v8::String> value)
{
	Nan::Utf8String utf8String(value);
	return *utf8String;
}

EspeakWrapper::EspeakWrapper(const char* dataPath)
{
	espeak = new Espeak(dataPath);
}

EspeakWrapper::~EspeakWrapper()
{
}

void EspeakWrapper::Init(v8::Local<v8::Object> exports)
{
	Nan::HandleScope scope;

	v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
	tpl->SetClassName(Nan::New("Espeak").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	Nan::SetPrototypeMethod(tpl, "speak", Speak);
	Nan::SetPrototypeMethod(tpl, "stop", Stop);
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
		const char* dataPath = ToString(info[0].As<v8::String>());
		EspeakWrapper* wrapper = new EspeakWrapper(dataPath);
		wrapper->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
}

void EspeakWrapper::Speak(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	Espeak* espeak = wrapper->espeak;
	const char* text = ToString(info[0].As<v8::String>());
	Nan::Callback* callback = new Nan::Callback(info[1].As<v8::Function>());

	Nan::AsyncQueueWorker(new SpeechWorker(espeak, text, callback));

	info.GetReturnValue().SetUndefined();
}

void EspeakWrapper::Stop(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	wrapper->espeak->Stop();
	info.GetReturnValue().SetUndefined();
}
