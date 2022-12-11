#include "../../src/cheat/fibermain.h"
#include "file_system.hpp"

using namespace Cheat;

DWORD WINAPI InitializationThread(LPVOID lpParam)
{
	// Create directories
	if (!std::filesystem::exists(file_system::paths::DataDir)) { std::filesystem::create_directory(file_system::paths::DataDir); }

	if (!std::filesystem::exists(file_system::paths::LogDir)) { std::filesystem::create_directory(file_system::paths::LogDir); }

	if (!std::filesystem::exists(file_system::paths::ThemesDir)) { std::filesystem::create_directory(file_system::paths::ThemesDir); }

	// Data migration for existing config and data prior to v2.2.1.0
	std::string OldDataPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + "\\gtav";
	std::string NewDataPath = file_system::paths::DataDir;
	if (std::filesystem::exists(OldDataPath))
	{
		// Move Logs directory
		std::string OldLogsDirectory = OldDataPath + "\\Logs";
		MoveFileExA(OldLogsDirectory.c_str(), NewDataPath.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED);

		// Move Themes directory
		std::string OldThemesDirectory = OldDataPath + "\\Themes";
		MoveFileExA(OldThemesDirectory.c_str(), NewDataPath.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED);

		// Move Config.ini
		std::string OldConfigPath = OldDataPath + "\\Config.ini";
		MoveFileExA(OldConfigPath.c_str(), file_system::paths::ConfigFile.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED);

		// Move CustomTeleportLocations.json
		std::string OldCustomTeleportLocationsPath = OldDataPath + "\\CustomTeleportLocations.json";
		MoveFileExA(OldCustomTeleportLocationsPath.c_str(), file_system::paths::CusTelLocFile.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED);

		// Move HUDColors.ini
		std::string OldHUDColorsPath = OldDataPath + "\\HUDColors.ini";
		MoveFileExA(OldHUDColorsPath.c_str(), file_system::paths::HUDColorsFile.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED);

		// Delete old data folder
		std::filesystem::remove_all(OldDataPath);
	}
	
	// Initalize Logger
	Logger::Init();

	// Initialize MinHook
	if (MH_Initialize() != MH_OK) { Logger::LogMsg(LOGGER_FATAL_MSG, "Initialize MinHook failed"); std::exit(EXIT_FAILURE); }
	Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG,"Initialized MH");

	// Initalize RAGE hooks
	GameHooking::Init();

	// Exit thread
	return EXIT_SUCCESS;
}

HMODULE Cheat::CheatModuleHandle;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpvReserved)
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