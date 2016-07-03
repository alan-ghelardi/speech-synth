#include "speech-worker.h"

SpeechWorker::SpeechWorker(Espeak* espeak_, string * text_, Nan::Callback* callback)
	: AsyncWorker(callback)
{
	espeak = espeak_;
	text = text_;
}

SpeechWorker::~SpeechWorker()
{
}

void SpeechWorker::Execute()
{
		CoInitialize(nullptr);
		espeak->Speak(*text);
}

void SpeechWorker::HandleOKCallback()
{
	Nan::HandleScope scope;
	v8::Local<v8::Value> args[] = {Nan::Null()};
	callback->Call(1, args);
}
