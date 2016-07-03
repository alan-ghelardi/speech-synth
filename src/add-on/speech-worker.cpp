#include "disposable.h"
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
	Disposable disposable;
		espeak->Speak(*text);
}
