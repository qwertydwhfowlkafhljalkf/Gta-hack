#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;

DWORD WINAPI InitializationThread(LPVOID lpParam)
{
	LogFunctions::Init();
	GameHooking::Initialize();
	//This thread is no longer needed, goodbye
	return 0;
}

HMODULE Cheat::CheatModuleHandle;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CheatModuleHandle = hModule;
		//Create 'gtav' directory
		std::string GtavDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav";
		if (!CheatFunctions::FileOrDirectoryExists(GtavDirectoryPath)) { CheatFunctions::CreateNewDirectory(GtavDirectoryPath); }
		//Create 'Logs' directory
		std::string LogsDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs";
		if (!CheatFunctions::FileOrDirectoryExists(LogsDirectoryPath)) { CheatFunctions::CreateNewDirectory(LogsDirectoryPath); }
		//Create 'Themes' directory
		std::string ThemesDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
		if (!CheatFunctions::FileOrDirectoryExists(ThemesDirectoryPath)) { CheatFunctions::CreateNewDirectory(ThemesDirectoryPath); }
		//Continue cheat loading
		CreateThread(NULL, NULL, InitializationThread, hModule, NULL, NULL);
		break;
	}
	return TRUE;
}