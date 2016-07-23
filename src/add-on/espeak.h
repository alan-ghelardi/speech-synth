#pragma once

#include <espeak/speak_lib.h>
#include <vector>
#include "wave-player.h"

using std::vector;

class Espeak 
{

private:
	bool isSpeaking;
	WavePlayer* player;
	vector<const char*> availableVoices;

	static int SynthesizerCallback(short* wav, int numberOfSamples, espeak_EVENT* events);
	void FillAvailableVoices();

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
	const vector<const char*> GetAvailableVoices();
	void Speak(const char* text);
	void Stop();
	void Release();

};
