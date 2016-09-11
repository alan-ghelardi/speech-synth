#pragma once

#include <espeak/speak_lib.h>
#include <string>
#include <vector>
#include "wave-player.h"

using std::string;
using std::vector;

class Espeak
{

private:
	const string dataPath;
	bool isSpeaking;
	WavePlayer* player;
	vector<string> availableVoices;

	void InitializeLibEspeak(const bool setPathOnly);
	void FillAvailableVoices();
	void CompileAllDictionaries(const string dictionariesPath);
	void CompileDictionary(const string voice, const string dictionariesPath);
	static int SynthesizerCallback(short* wav, int numberOfSamples, espeak_EVENT* events);

public:
	Espeak(const string dataPath, const bool isCompiling = false);

	unsigned int GetPitch();
	void SetPitch(unsigned int pitch);
	unsigned int GetSpeed();
	void SetSpeed(unsigned int speed);
	unsigned int GetVolume();
	void SetVolume(unsigned int volume);
	const string GetVoice();
	void SetVoice(const string voiceName);
	const string GetLanguage();
	void SetLanguage(const string language);
	const vector<string> GetAvailableVoices();
	void CompileData(const string dictionariesPath);
	void Speak(const string text);
	void Stop();
	void Release();

};
