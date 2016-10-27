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

	int GetParameter(int parameterIdentifier) const;
	void SetParameter(int parameterIdentifier, int value);
	const string GetVoice();
	void SetVoice(const string voiceName);
	const vector<string> GetAvailableVoices();
	void CompileData(const string dictionariesPath);
	void Speak(const string text);
	void Stop();
	void Release();

};
