#include <espeak-ng/espeak_ng.h>
#include "espeak.h"
#include "helpers.h"

static const unsigned BUFFER_SIZE_IN_MILLISECONDS = 300;

Espeak::Espeak(const string dataPath)
{
	espeak_ng_InitializePath(dataPath.c_str());
	espeak_ng_ERROR_CONTEXT context = nullptr;
	espeak_ng_STATUS result = espeak_ng_Initialize(&context);
	HandlePossibleError(result, &context);
	result = espeak_ng_InitializeOutput(ENOUTPUT_MODE_SYNCHRONOUS, BUFFER_SIZE_IN_MILLISECONDS, nullptr);
	HandlePossibleError(result);
	player = WavePlayer::New(espeak_ng_GetSampleRate(), BUFFER_SIZE_IN_MILLISECONDS);
	espeak_SetSynthCallback(Espeak::SynthesizerCallback);
}

int Espeak::SynthesizerCallback(short* chunks, int numberOfSamples, espeak_EVENT* events)
{
	WavePlayer* player = (WavePlayer*)events->user_data;

	if (chunks == nullptr)
	{
		player->Stop();
	}
	else if (numberOfSamples)
	{
		WaveData data(chunks, numberOfSamples);
		player->Play(data);
	}

	return 0;
}

unsigned int Espeak::GetPitch()
{
	return espeak_GetParameter(espeakPITCH, 1);
}

void Espeak::SetPitch(unsigned int pitch)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakPITCH, pitch, 0);
	HandlePossibleError(result);
}

unsigned int Espeak::GetSpeed()
{
	return espeak_GetParameter(espeakRATE, 1);
}

void Espeak::SetSpeed(unsigned int speed)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakRATE, speed, 0);
	HandlePossibleError(result);
}

unsigned int Espeak::GetVolume()
{
	return espeak_GetParameter(espeakVOLUME, 1);
}

void Espeak::SetVolume(unsigned int volume)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakVOLUME, volume, 0);
	HandlePossibleError(result);
}

string Espeak::GetVoice()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->name;
}

void Espeak::SetVoice(const string voiceName)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->name = voiceName.c_str();
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	HandlePossibleError(result);
}

string Espeak::GetLanguage()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->languages;
}

void Espeak::SetLanguage(string language)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->languages = language.c_str();
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	HandlePossibleError(result);
}

void Espeak::Speak(const string text)
{
	const char* textToBeSpoken = text.c_str();
	espeak_ng_STATUS result = espeak_ng_Synthesize(textToBeSpoken, 0, 0, POS_CHARACTER, 0, synthesizerFlags, nullptr, this->player);
	HandlePossibleError(result);
}

void Espeak::Cancel()
{
	espeak_ng_STATUS result = espeak_ng_Cancel();
	HandlePossibleError(result);
}

void Espeak::Release()
{
	player->Release();
	delete player;
	espeak_ng_Terminate();
}
