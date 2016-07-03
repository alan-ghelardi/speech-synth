#pragma once

#define _WINSOCKAPI_
#include <Windows.h>

class Disposable
{

private:
	HRESULT result;

public:
	Disposable();
	~Disposable();

};

