#pragma once

#include <nan.h>
#include "espeak.h"

class SpeechWorker :
	public Nan::AsyncWorker
{

private:
	Espeak* espeak;
	const char* text;

public:
	SpeechWorker(Espeak* espeak, const char* text, Nan::Callback* callback);
	~SpeechWorker();

	void Execute();

};
