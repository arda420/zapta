#include "includes.h"

UCHAR
szFileSys[255],
szVolNameBuff[255];

DWORD
dwMFL,
dwSysFlags,
dwSerial;


/*
#define dev (-121220618)

VOID CheckValidHardwareID()
{

	GetVolumeInformation("C:\\", (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);
	if (dwSerial == dev )
	{
		MessageBox(0, "Build Date: " __DATE__ " ", "Counter-Strike: Global Offensive", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(0, "You are not authorized" + dwSerial, "Counter-Strike: Global Offensive", MB_OK | MB_ICONERROR);
		ExitProcess(1);
	}
}*/


int __stdcall DllMain(HMODULE self, ulong_t reason, void* reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		//CheckValidHardwareID();
#ifndef KOLO

		HANDLE thread = CreateThread(nullptr, 0, Core::init, nullptr, 0, nullptr);
		if (!thread)
			return 0;

		// CloseHandle( thread );
#else
		Core::init(nullptr);
#endif
		return 1;
	}

	return 0;
}

