#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;

DWORD WINAPI InitializationThread(LPVOID lpParam)
{
	std::string GtavDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav";
	if (!CheatFunctions::FileOrDirectoryExists(GtavDirectoryPath)) { CheatFunctions::CreateNewDirectory(GtavDirectoryPath); }
	std::string LogsDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs";
	if (!CheatFunctions::FileOrDirectoryExists(LogsDirectoryPath)) { CheatFunctions::CreateNewDirectory(LogsDirectoryPath); }
	std::string ThemesDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	if (!CheatFunctions::FileOrDirectoryExists(ThemesDirectoryPath)) { CheatFunctions::CreateNewDirectory(ThemesDirectoryPath); }

	LogFunctions::Init();
	GameHooking::Initialize();
	return EXIT_SUCCESS;
}

HMODULE Cheat::CheatModuleHandle;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CheatModuleHandle = hModule;
		DisableThreadLibraryCalls(CheatModuleHandle);
		CreateThread(NULL, NULL, InitializationThread, CheatModuleHandle, NULL, NULL);
		break;
	}
	return TRUE;
}