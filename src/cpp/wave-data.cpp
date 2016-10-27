#include <cstring>
#include "wave-data.h"

WaveData::WaveData(const short* chunks, unsigned numberOfSamples) :
	chunks(chunks),
	numberOfSamples(numberOfSamples)
{
}

const unsigned WaveData::GetSize() const
{
	return numberOfSamples * sizeof(short);
}

void WaveData::CopyTo(void* address, const size_t size) const
{
	std::memcpy(address, chunks, size);
}
