#include "wave-player.h"

#ifdef _WIN32
#include "direct-sound-player.h"
#endif

WavePlayer::WavePlayer(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds) :
	samplesPerSecond(samplesPerSecond),
	bufferSizeInMilliseconds(bufferSizeInMilliseconds)
{
}

WavePlayer* WavePlayer::New(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds)
{
#ifdef _WIN32
	return new DirectSoundPlayer(samplesPerSecond, bufferSizeInMilliseconds);
#endif
}
