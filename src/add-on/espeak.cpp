#include <espeak-ng/espeak_ng.h>
#include "espeak.h"
#include "helpers.h"

#ifndef PLAYBACK_MODE
#define PLAYBACK_MODE ENOUTPUT_MODE_SPEAK_AUDIO
#endif

Espeak::Espeak(const string dataPath)
{
	espeak_ng_InitializePath(dataPath.c_str());
	espeak_ng_ERROR_CONTEXT context = nullptr;
	espeak_ng_STATUS result = espeak_ng_Initialize(&context);
	handlePossibleError(result, &context);
	result = espeak_ng_InitializeOutput(PLAYBACK_MODE, 0, nullptr);
	handlePossibleError(result);
}

unsigned int Espeak::getPitch()
{
	return espeak_GetParameter(espeakPITCH, 1);
}

void Espeak::setPitch(unsigned int pitch)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakPITCH, pitch, 0);
	handlePossibleError(result);
}

unsigned int Espeak::getSpeed()
{
	return espeak_GetParameter(espeakRATE, 1);
}

void Espeak::setSpeed(unsigned int speed)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakRATE, speed, 0);
	handlePossibleError(result);
}

unsigned int Espeak::getVolume()
{
	return espeak_GetParameter(espeakVOLUME, 1);
}

void Espeak::setVolume(unsigned int volume)
{
	espeak_ng_STATUS result = espeak_ng_SetParameter(espeakVOLUME, volume, 0);
	handlePossibleError(result);
}

string Espeak::getVoice()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->name;
}

void Espeak::setVoice(const string voiceName)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->name = voiceName.c_str();
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	handlePossibleError(result);
}

string Espeak::getLanguage()
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	return voice->languages;
}

void Espeak::setLanguage(string language)
{
	espeak_VOICE* voice = espeak_GetCurrentVoice();
	voice->languages = language.c_str();
	espeak_ng_STATUS result = espeak_ng_SetVoiceByProperties(voice);
	handlePossibleError(result);
}

void Espeak::speak(const string text) 
{
	const char* textToBeSpoken = text.c_str();
	int size = static_cast<int>(text.length());
	espeak_Synth(textToBeSpoken, size + 1, 0, POS_CHARACTER, 0, synthesizerFlags, nullptr, nullptr);
}

void Espeak::cancel()
{
	espeak_ng_STATUS result = espeak_ng_Cancel();
	handlePossibleError(result);
}
