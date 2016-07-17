#pragma once

class WaveData
{

	const short* chunks;
	const unsigned numberOfSamples;

public:
	WaveData(const short* chunks, const unsigned numberOfSamples);

	const unsigned GetSize() const;
	void CopyTo(void* address, const size_t size) const;

};
