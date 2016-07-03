#include "disposable.h"

Disposable::Disposable()
{
	result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

Disposable::~Disposable()
{
	if (SUCCEEDED(result))
	{
		CoUninitialize();
	}
}
