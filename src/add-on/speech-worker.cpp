#include "speech-worker.h"

SpeechWorker::SpeechWorker(Espeak* espeak, string * text, Nan::Callback* callback)
	: AsyncWorker(callback),
	espeak(espeak),
	text(text)
{
}

SpeechWorker::~SpeechWorker()
{
}

void SpeechWorker::Execute()
{
	try
	{
		espeak->Speak(*text);
	}
	catch (const std::exception& error)
	{
		SetErrorMessage(error.what());
	}
}
