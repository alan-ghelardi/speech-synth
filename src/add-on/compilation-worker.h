#pragma once

#include <nan.h>
#include "espeak.h"

class CompilationWorker :
	public Nan::AsyncWorker
{

private:
	Espeak* espeak;
	const char* dictionariesPath;

public:
	CompilationWorker(Espeak* espeak, const char* dictionariesPath, Nan::Callback* callback);
	~CompilationWorker();

	void Execute() override;

};

