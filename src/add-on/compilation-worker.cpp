#include "compilation-worker.h"

CompilationWorker::CompilationWorker(Espeak* espeak, const char* dictionariesPath, Nan::Callback* callback)
	: AsyncWorker(callback),
	espeak(espeak),
	dictionariesPath(dictionariesPath)
{
}

CompilationWorker::~CompilationWorker()
{
}

void CompilationWorker::Execute()
{
	try
	{
		espeak->CompileData(dictionariesPath);
	}
	catch (const std::exception& error)
	{
		SetErrorMessage(error.what());
	}
}
