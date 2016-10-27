#include <iostream>
#include <espeak-ng/espeak_ng.h>
#include <sstream>
#include "espeak.h"
#include "helpers.h"

using std::stringstream;

static const unsigned BUFFER_SIZE_IN_MILLISECONDS = 300;
static const int CONTINUE_SYNTHESIS = 0;
static const int STOP_SYNTHESIS = 1;
static const int SYNTHESIZER_FLAGS = espeakCHARS_AUTO | espeakSSML | espeakPHONEMES;

Espeak::Espeak(const string dataPath, const bool isCompiling) :
	dataPath(dataPath),
	isSpeaking(false),
	player(nullptr),
	availableVoices(vector<string>())
{
	InitializeLibEspeak(isCompiling);
	FillAvailableVoices();

	if (!isCompiling)
	{
		player = WavePlayer::New(espeak_ng_GetSampleRate(), BUFFER_SIZE_IN_MILLISECONDS);
		espeak_SetSynthCallback(Espeak::SynthesizerCallback);
	}
}

void Espeak::InitializeLibEspeak(const bool setPathOnly)
{
	espeak_ng_InitializePath(dataPath.c_str());

	if (!setPathOnly)
	{
		espeak_ng_ERROR_CONTEXT context = nullptr;
		espeak_ng_STATUS result = espeak_ng_Initialize(&context);
		RaiseExceptionUnlessSucceeded(result, &context);
		result = espeak_ng_InitializeOutput(ENOUTPUT_MODE_SYNCHRONOUS, BUFFER_SIZE_IN_MILLISECONDS, nullptr);
		RaiseExceptionUnlessSucceeded(result);
	}
}

void Espeak::FillAvailableVoices()
{
	const espeak_VOICE** voices = espeak_ListVoices(nullptr);
	const espeak_VOICE* currentVoice;

	for (int i = 0; (currentVoice = voices[i]) != nullptr; i++)
	{
		availableVoices.push_back(currentVoice->name);
	}
}

int Espeak::SynthesizerCallback(short* chunks, int numberOfSamples, espeak_EVENT* events)
{
	Espeak* espeak = (Espeak*)events->user_data;
	WavePlayer* player = espeak->player;
	int result = CONTINUE_SYNTHESIS;

	if (!espeak->isSpeaking)
	{
		result = STOP_SYNTHESIS;
	}
	else if (numberOfSamples)
	{
		WaveData data(chunks, numberOfSamples);
		player->Play(data);
	}

	return result;
}

int Espeak::GetParameter(int parameterIdentifier) const
{
	return espeak_GetParameter((espeak_PARAMETER)parameterIdentifier, 1);
}

void Espeak::SetParameter(int parameterIdentifier, int value)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter((espeak_PARAMETER)parameterIdentifier, value, 0);
	RaiseExceptionUnlessSucceeded(result);
}

const string Espeak::GetVoice()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->name;
}

void Espeak::SetVoice(const string voiceName)
{
	espeak_ng_STATUS result = espeak_ng_SetVoiceByName(voiceName.c_str());

	stringstream buffer;
	buffer << "Failed to switch to voice '" << voiceName << "'";
	RaiseExceptionUnlessSucceeded(result, buffer.str());
}

const vector<string> Espeak::GetAvailableVoices()
{
	return availableVoices;
}

void Espeak::CompileData(const string dictionariesPath)
{
	espeak_ng_ERROR_CONTEXT context = nullptr;
	espeak_ng_STATUS result = espeak_ng_CompileIntonation(stdout, &context);
	RaiseExceptionUnlessSucceeded(result, &context);
	result = espeak_ng_CompilePhonemeData(22050, stdout, &context);
	RaiseExceptionUnlessSucceeded(result, &context);
	CompileAllDictionaries(dictionariesPath);
}

void Espeak::CompileAllDictionaries(const string dictionariesPath)
{
	for (const string voice : availableVoices)
	{
		InitializeLibEspeak(false);

		try
		{
			CompileDictionary(voice, dictionariesPath);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void Espeak::CompileDictionary(const string voice, const string dictionariesPath)
{
	SetVoice(voice);
	espeak_ng_ERROR_CONTEXT context = nullptr;
	espeak_ng_STATUS result = espeak_ng_CompileDictionary(dictionariesPath.c_str(), nullptr, nullptr, 0, &context);
	RaiseExceptionUnlessSucceeded(result, &context);
}

void Espeak::Speak(const string text)
{
	isSpeaking = true;
	espeak_ng_STATUS result = espeak_ng_Synthesize(text.c_str(), 0, 0, POS_CHARACTER, 0, SYNTHESIZER_FLAGS, nullptr, this);
	RaiseExceptionUnlessSucceeded(result);
}

void Espeak::Stop()
{
	isSpeaking = false;
	player->Stop();
}

void Espeak::Release()
{
	if (player != nullptr)
	{
		player->Release();
		delete player;
	}
	espeak_ng_Terminate();
}
