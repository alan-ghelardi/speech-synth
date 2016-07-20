#pragma once

#include <string>
#include <espeak/speak_lib.h>
#include "wave-player.h"

using namespace std;

class Espeak 
{

private:
	bool isSpeaking;
	WavePlayer* player;

	static int SynthesizerCallback(short* wav, int numberOfSamples, espeak_EVENT* events);

public:
	Espeak(const string dataPath);

	unsigned int GetPitch();
	void SetPitch(unsigned int pitch);
	unsigned int GetSpeed();
	void SetSpeed(unsigned int speed);
	unsigned int GetVolume();
	void SetVolume(unsigned int volume);
	string GetVoice();
	void SetVoice(const string voiceName);
	string GetLanguage();
	void SetLanguage(const string language);
	void Speak(const string text);
	void Stop();
	void Release();

};
