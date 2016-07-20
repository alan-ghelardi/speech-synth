#pragma once

#include <espeak/speak_lib.h>
#include "wave-player.h"

class Espeak 
{

private:
	bool isSpeaking;
	WavePlayer* player;

	static int SynthesizerCallback(short* wav, int numberOfSamples, espeak_EVENT* events);

public:
	Espeak(const char* dataPath);

	unsigned int GetPitch();
	void SetPitch(unsigned int pitch);
	unsigned int GetSpeed();
	void SetSpeed(unsigned int speed);
	unsigned int GetVolume();
	void SetVolume(unsigned int volume);
	const char* GetVoice();
	void SetVoice(const char* voiceName);
	const char* GetLanguage();
	void SetLanguage(const char* language);
	void Speak(const char* text);
	void Stop();
	void Release();

};
