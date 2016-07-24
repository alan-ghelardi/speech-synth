#pragma once

#include <espeak/speak_lib.h>
#include <vector>
#include "wave-player.h"

using std::vector;

class Espeak
{

private:
	const char* dataPath;
	bool isSpeaking;
	WavePlayer* player;
	vector<const char*> availableVoices;

	void InitializeLibEspeak(const bool setPathOnly);
	void FillAvailableVoices();
	void CompileAllDictionaries(const char* dictionariesPath);
	void CompileDictionary(const char* voice, const char* dictionariesPath);
	static int SynthesizerCallback(short* wav, int numberOfSamples, espeak_EVENT* events);

public:
	Espeak(const char* dataPath, const bool isCompiling = false);

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
	void CompileData(const char* dictionariesPath);
	void Speak(const char* text);
	void Stop();
	void Release();

};
