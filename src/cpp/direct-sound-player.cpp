#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "direct-sound-player.h"

std::string ToHexString(HRESULT result)
{
	std::stringstream stream;
	stream << std::hex << "0x"
		<< std::setfill('0') << std::setw(sizeof(HRESULT) * 2)
		<< result;
	return stream.str();
}

void RaiseExceptionUnlessSucceeded(HRESULT result, const char* message)
{
	if (FAILED(result))
	{
		std::stringstream stream;
		stream << message << ". The Microsoft Direct Sound API has returned the code " << ToHexString(result)
			<< "." << std::endl
			<< "See the Direct Sound return values and the corresponding error description for further information." << std::endl;
		throw std::runtime_error(stream.str());
	}
}

void RaiseExceptionUnlessSucceeded(HANDLE handle, const char* message)
{
	if (handle == nullptr)
	{
		std::stringstream stream;
		stream << message << ". The Windows API has returned the following message: "
			<< GetLastError() << std::endl;
	}
}

DirectSoundPlayer::DirectSoundPlayer(const unsigned samplesPerSecond, const unsigned bufferSizeInMilliseconds) :
	WavePlayer(samplesPerSecond, bufferSizeInMilliseconds)
{
	CreateDevice();
	CreateSoundBuffer();
	CreateStopNotification();
}

void DirectSoundPlayer::CreateDevice()
{
	HRESULT result = DirectSoundCreate8(nullptr, &device, nullptr);
	RaiseExceptionUnlessSucceeded(result, "Unable to create a IDirectSound8 object");

	HWND windowHandle = GetForegroundWindow();

	if (windowHandle == nullptr)
	{
		windowHandle = GetDesktopWindow();
	}

	result = device->SetCooperativeLevel(windowHandle, DSSCL_PRIORITY);
	RaiseExceptionUnlessSucceeded(result, "Unable to set the cooperative level");
}

void DirectSoundPlayer::CreateSoundBuffer()
{
	CreateBufferDescriptor();
	HRESULT result = device->CreateSoundBuffer(&bufferDescriptor, &soundBuffer, nullptr);
	RaiseExceptionUnlessSucceeded(result, "Unable to create a IDirectSoundBuffer object");
}

void DirectSoundPlayer::CreateBufferDescriptor()
{
	CreateWaveFormat();
	std::memset(&bufferDescriptor, 0, sizeof(DSBUFFERDESC));
	bufferDescriptor.dwSize = sizeof(DSBUFFERDESC);
	bufferDescriptor.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS;
	bufferDescriptor.dwBufferBytes = waveFormat.nAvgBytesPerSec * bufferSizeInMilliseconds / 1000;
	bufferDescriptor.lpwfxFormat = &waveFormat;
}

void DirectSoundPlayer::CreateWaveFormat()
{
	std::memset(&waveFormat, 0, sizeof(WAVEFORMATEX));
	waveFormat.nChannels = 1;
	waveFormat.nSamplesPerSec = samplesPerSecond;
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
}

void DirectSoundPlayer::CreateStopNotification()
{
	HANDLE stopEvent = CreateEvent(nullptr, false, true, nullptr);
	RaiseExceptionUnlessSucceeded(stopEvent, "Unable to create Windows event");
	HRESULT result = soundBuffer->QueryInterface(IID_IDirectSoundNotify8, (LPVOID*)&stopNotification);
	RaiseExceptionUnlessSucceeded(result, "Unable to create an IDirectNotify8 object");

	positionNotify.dwOffset = DSBPN_OFFSETSTOP;
	positionNotify.hEventNotify = stopEvent;

	result = stopNotification->SetNotificationPositions(1, &positionNotify);
	RaiseExceptionUnlessSucceeded(result, "Unable to set the stop notification");
}

unsigned DirectSoundPlayer::GetBufferSizeInBytes() const
{
	return bufferDescriptor.dwBufferBytes;
}

void DirectSoundPlayer::Play(const WaveData& data)
{
	WaitForSingleObject(positionNotify.hEventNotify, INFINITE);
	WriteWaveData(data);
	HRESULT result = soundBuffer->Play(0, 0, 0);
	RaiseExceptionUnlessSucceeded(result, "Unable to play wave data");
}

void DirectSoundPlayer::WriteWaveData(const WaveData& data)
{
	DWORD offset = 0;
	DWORD numberOfBytes = data.GetSize();
	LPVOID portionAddress1 = nullptr;
	LPVOID portionAddress2 = nullptr;
	DWORD portionSize1 = 0;
	DWORD portionSize2 = 0;

	HRESULT result = soundBuffer->GetCurrentPosition(nullptr, &offset);
	RaiseExceptionUnlessSucceeded(result, "Unable to obtain the write cursor");

	result = soundBuffer->Lock(offset, numberOfBytes, &portionAddress1, &portionSize1, &portionAddress2, &portionSize2, 0);
	RaiseExceptionUnlessSucceeded(result, "Unable to lock the sound buffer");

	data.CopyTo(portionAddress1, portionSize1);

	if (portionAddress2 != nullptr)
	{
		data.CopyTo(portionAddress2, portionSize2);
	}

	result = soundBuffer->Unlock(portionAddress1, portionSize1, portionAddress2, portionSize2);
	RaiseExceptionUnlessSucceeded(result, "Failed to unlock the sound buffer");
}

void DirectSoundPlayer::Stop()
{
	HRESULT result = soundBuffer->Stop();
	RaiseExceptionUnlessSucceeded(result, "Failed to stop the playback");
}

void DirectSoundPlayer::Release()
{
	stopNotification->Release();
	CloseHandle(positionNotify.hEventNotify);
	soundBuffer->Release();
	device->Release();
}
