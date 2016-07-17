#pragma once
#pragma comment(lib, "Dsound.lib")
#pragma comment(lib, "dxguid.lib")

#include <Windows.h>
#include <dsound.h>
#include "wave-player.h"

class DirectSoundPlayer :
	public WavePlayer
{

private:
	LPDIRECTSOUND8 device;
	LPDIRECTSOUNDBUFFER soundBuffer;
	DSBUFFERDESC bufferDescriptor;
	WAVEFORMATEX waveFormat;
	LPDIRECTSOUNDNOTIFY8 stopNotification;
	DSBPOSITIONNOTIFY positionNotify;

	void CreateDevice();
	void CreateSoundBuffer();
	void CreateBufferDescriptor();
	void CreateWaveFormat();
	void CreateStopNotification();
	void WriteWaveData(const WaveData& data);

public:

	DirectSoundPlayer(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds);

	unsigned GetBufferSizeInBytes() const;
	void Play(const WaveData& data);
	void Stop();
	void Release();

};
