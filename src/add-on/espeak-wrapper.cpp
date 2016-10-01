#include "compilation-worker.h"
#include "espeak-wrapper.h"
#	include "speech-worker.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

const char* ToString(v8::Local<v8::String> value)
{
	Nan::Utf8String utf8String(value);
	return *utf8String;
}

const bool ToBoolean(const v8::Local<v8::Value> value)
{
	Nan::Maybe<bool> maybeValue = Nan::To<bool>(value);
	return maybeValue.FromMaybe(false);
}

Nan::Persistent<v8::Function> EspeakWrapper::constructor;

EspeakWrapper::EspeakWrapper(const char* dataPath, const bool isCompiling)
{
	try
	{
		espeak = new Espeak(dataPath, isCompiling);
	}
	catch (const std::exception& error)
	{
		Nan::ThrowError(error.what());
	}
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

	Nan::SetPrototypeMethod(tpl, "voice", Voice);
	Nan::SetPrototypeMethod(tpl, "getAllVoices", GetAllVoices);
	Nan::SetPrototypeMethod(tpl, "compileData", CompileData);
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
		const bool isCompiling = ToBoolean(info[1]);

		EspeakWrapper* wrapper = new EspeakWrapper(dataPath, isCompiling);
		wrapper->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}
}

void EspeakWrapper::Voice(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	try
	{
		EspeakWrapper::TryGetOrSetVoice(info);
	}
	catch (const std::exception& error)
	{
		Nan::ThrowError(error.what());
	}
}

void EspeakWrapper::TryGetOrSetVoice(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	Espeak* espeak = EspeakWrapper::GetEspeak(info);

	if (info.Length())
	{
		const char* voice = ToString(info[0].As<v8::String>());
		espeak->SetVoice(voice);
		info.GetReturnValue().SetUndefined();
	}
	else
	{
		string voice = espeak->GetVoice();
		info.GetReturnValue().Set(Nan::New(voice).ToLocalChecked());
	}
}

Espeak* EspeakWrapper::GetEspeak(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	return wrapper->espeak;
}

void EspeakWrapper::GetAllVoices(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	Espeak* espeak = wrapper->espeak;
	vector<string> voices = espeak->GetAvailableVoices();
	v8::Local<v8::Array> wrappedVoices = Nan::New<v8::Array>(voices.size());

	int i = 0;

	for (const string voice : voices)
	{
		Nan::Set(wrappedVoices, i++, Nan::New(voice).ToLocalChecked());
	}

	info.GetReturnValue().Set(wrappedVoices);
}

void EspeakWrapper::CompileData(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
	EspeakWrapper* wrapper = ObjectWrap::Unwrap<EspeakWrapper>(info.Holder());
	Espeak* espeak = wrapper->espeak;
	const char* dictionariesPath = ToString(info[0].As<v8::String>());
	Nan::Callback* callback = new Nan::Callback(info[1].As<v8::Function>());

	Nan::AsyncQueueWorker(new CompilationWorker(espeak, dictionariesPath, callback));

	info.GetReturnValue().SetUndefined();
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
