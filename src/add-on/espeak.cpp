#include <espeak-ng/espeak_ng.h>
#include "espeak.h"
#include "helpers.h"

static const unsigned BUFFER_SIZE_IN_MILLISECONDS = 300;
static const int CONTINUE_SYNTHESIS = 0;
static const int STOP_SYNTHESIS = 1;
static const int SYNTHESIZER_FLAGS = espeakCHARS_AUTO | espeakSSML | espeakPHONEMES;

Espeak::Espeak(const char* dataPath) :
	isSpeaking(false)
{
	espeak_ng_InitializePath(dataPath);
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

const char* Espeak::GetVoice()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->name;
}

void Espeak::SetVoice(const char* voiceName)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->name = voiceName;
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	HandlePossibleError(result);
}

const char* Espeak::GetLanguage()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->languages;
}

void Espeak::SetLanguage(const char* language)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->languages = language;
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	HandlePossibleError(result);
}

void Espeak::Speak(const char* text)
{
	isSpeaking = true;
	espeak_ng_STATUS result = espeak_ng_Synthesize(text, 0, 0, POS_CHARACTER, 0, SYNTHESIZER_FLAGS, nullptr, this);
	HandlePossibleError(result);
}

void Espeak::Stop()
{
	isSpeaking = false;
	player->Stop();
}

void Espeak::Release()
{
	player->Release();
	delete player;
	espeak_ng_Terminate();
}
