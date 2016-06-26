#pragma once

#include <string>
#include <espeak/speak_lib.h>

using namespace std;

class Espeak 
{

private:
	int synthesizerFlags = espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE;

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
	void Cancel();

};
