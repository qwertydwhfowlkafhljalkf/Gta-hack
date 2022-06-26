#include "../Header/Cheat Functions/FiberMain.h"
#include "../../Header/GUI/DirectX/ImGuiMain.h"

using namespace Cheat;

DWORD WINAPI InitializationThread(LPVOID lpParam)
{
	// Define paths
	std::string GtavDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav";
	if (!CheatFunctions::FileOrDirectoryExists(GtavDirectoryPath)) { CheatFunctions::CreateNewDirectory(GtavDirectoryPath); }
	std::string LogsDirectoryPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs";
	if (!CheatFunctions::FileOrDirectoryExists(LogsDirectoryPath)) { CheatFunctions::CreateNewDirectory(LogsDirectoryPath); }
	std::string ThemesDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	if (!CheatFunctions::FileOrDirectoryExists(ThemesDirectoryPath)) { CheatFunctions::CreateNewDirectory(ThemesDirectoryPath); }
	
	// Initalize Logger
	Logger::Init();

	// Initialize MinHook
	if (MH_Initialize() != MH_OK) { Cheat::Logger::Error("Failed to initialize MinHook", true); std::exit(EXIT_SUCCESS); }
	Logger::DebugMessage("Initialized MinHook");

	// Initialize DirectX hook and ImGui
	DirectX::ImGuiInit();
	Logger::DebugMessage("Initialized DirectX hook & ImGui");

	// Initalize RAGE hooks
	GameHooking::Initialize();

	// Exit thread
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