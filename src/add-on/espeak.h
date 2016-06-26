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

	unsigned int getPitch();

	void setPitch(unsigned int pitch);

	unsigned int getSpeed();

	void setSpeed(unsigned int speed);

	unsigned int getVolume();

	void setVolume(unsigned int volume);

	string getVoice();

	void setVoice(const string voiceName);

	string getLanguage();

	void setLanguage(const string language);

	void speak(const string text);

	void cancel();

};
