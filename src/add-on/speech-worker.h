#pragma once

#include <string>
#include <nan.h>
#include "espeak.h"

using namespace std;

class SpeechWorker :
	public Nan::AsyncWorker
{

private:
	Espeak* espeak;
	string* text;

public:
	SpeechWorker(Espeak* espeak, string* text, Nan::Callback* callback);
	~SpeechWorker();

	void Execute();
	void HandleOKCallback();

};
