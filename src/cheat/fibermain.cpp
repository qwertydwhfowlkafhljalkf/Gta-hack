#include "fibermain.h"
#include "file_system.hpp"
#include "version.hpp"

bool Cheat::c_running = true;
void Cheat::FiberMain(LPVOID lpParameter)
{
	// Check for availability of newer cheat version
	Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_INFO_MSG, "Checking for newer version");
	int LocalVersion = build_info::VersionInt;
	int LatestVersion = CheatFunctions::GetLatestCheatBuildNumber();
	if (LatestVersion != NULL)
	{
		if (LocalVersion < LatestVersion)
		{
			CheatFunctions::NewerCheatVersionAvailable = true;
			Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "A newer version of the cheat is available on GitHub");
		}
		else
		{
			Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "No newer cheat version available");
		}
	}

	// Create Menu Selectable Arrow Animation Thread
	std::thread MenuSelectableAnimationThreadHandle([]()
		{
			while (Cheat::c_running)
			{
				if (GUI::menuLevel > 0)
				{
					GUI::MenuOptionArrowAnimationState = !GUI::MenuOptionArrowAnimationState;
					Sleep(GUI::MenuArrowAnimationDelay);
				}
			}
		});
	MenuSelectableAnimationThreadHandle.detach();

	// Load configuration file
	CheatFunctions::LoadConfig();

	// Load texture file
	GUI::LoadTextureFile();

	// Load 'multiplayer vehicles in Single Player' bypass
	globalHandle(GLOBAL_SP_DESPAWN_BYPASS).As<BOOL>() = true;
	Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Loaded SPVSB");

	// Fetch default HUD colors
	for (int i = 0; i <= GameArrays::HUDColors.size(); i++)
	{
		DefaultHUDColorsStruct data{};
		UI::GET_HUD_COLOUR(i, &data.R, &data.G, &data.B, &data.A);
		GameArrays::DefaultHUDColors.push_back(data);
	}
	Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Fetched DHC");

	// Load saved HUD colors
	if (std::filesystem::exists(file_system::paths::HUDColorsFile))
	{
		int SavedHUDColorsIndex = 0;
		for (auto const& HUDColorComponentName : GameArrays::HUDColors)
		{
			std::string Red = file_system::ini_file::get(file_system::paths::HUDColorsFile, HUDColorComponentName, "r");
			std::string Green = file_system::ini_file::get(file_system::paths::HUDColorsFile, HUDColorComponentName, "g");
			std::string Blue = file_system::ini_file::get(file_system::paths::HUDColorsFile, HUDColorComponentName, "b");
			std::string Alpha = file_system::ini_file::get(file_system::paths::HUDColorsFile, HUDColorComponentName, "a");

			if (!Red.empty() && !Green.empty() && !Blue.empty() && !Alpha.empty())
			{
				UI::REPLACE_HUD_COLOUR_WITH_RGBA(SavedHUDColorsIndex, CheatFunctions::StringToInt(Red), CheatFunctions::StringToInt(Green), CheatFunctions::StringToInt(Blue), CheatFunctions::StringToInt(Alpha));
				Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Loaded CHC %s", HUDColorComponentName.c_str());
			}
			SavedHUDColorsIndex++;
		}
	}

	// Cheat init completed
	CheatFunctions::CheatInitCompleted = true;
	Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Cheat init completed");

	// Main cheat loop within the created fiber - this runs in the IS_DLC_PRESENT hook (thus, game natives can be called only from within this loop)
	while (c_running)
	{
		// Set CheatInitEntirelyCompleted when all init is completed
		CheatFunctions::CheatInitEntirelyCompleted = CheatFunctions::CheatInitCompleted && CheatFunctions::ConfigLoaded;

		// Core component loops
		CheatFeatures::Loop();		// Responsible for looping most cheat-technical and game-feature related functions
		GUI::Submenus::Loop();		// Responsible for looping the submenu logical; this is also responsible for rendering the menu GUI title
		GUI::Loop();				// Responsible for some core GUI elements; currently only the menu bottom
		Controls::Loop();			// Responsible for control inputs (keyboard and mouse)

		// Switch Fiber
		SwitchToFiber(GameHooking::fiber_main);
	}

	// Create shutdown thread
	auto unload = [](LPVOID data) -> DWORD
	{ 
		// Disable & remove MinHook hooks
		for (int i = 0; i < GameHooking::GetMH_Hooked().size(); i++)
		{
			MH_DisableHook(GameHooking::GetMH_Hooked()[i]);
			MH_RemoveHook(GameHooking::GetMH_Hooked()[i]);
		}

		// Uninit MinHook
		MH_Uninitialize();

		// Unload DLL from game process
		FreeLibraryAndExitThread(Cheat::CheatModuleHandle, EXIT_SUCCESS);
	};
	CreateThread(NULL, NULL, unload, NULL, NULL, NULL);
}