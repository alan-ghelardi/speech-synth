#pragma once

#include "wave-data.h"

class WavePlayer
{

protected:
	const unsigned samplesPerSecond;
	const unsigned bufferSizeInMilliseconds;

	WavePlayer(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds);

public:

	virtual void Play(const WaveData& data) = 0;
	virtual void Stop() = 0;
	virtual void Release() = 0;
	static WavePlayer* New(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds);

};
