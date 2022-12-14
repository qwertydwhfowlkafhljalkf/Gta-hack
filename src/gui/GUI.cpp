#include "../../src/cheat/fibermain.h"
#include "../../src/cheat/file_system.hpp"
#include "../../src/cheat/version.hpp"

using namespace Cheat;

const float GUI::guiX_Default				= 0.15f;
const float GUI::guiY_Default				= 0.30f;
const float GUI::guiWidth_Default			= 0.25f;
const float GUI::SelectableInfoBoxX_Default	= 0.50f;
const float GUI::SelectableInfoBoxY_Default	= 0.040f;
float GUI::guiX								= 0.15f;
float GUI::guiY								= 0.30f;
float GUI::guiWidth							= 0.25f;
float GUI::SelectableInfoBoxX				= 0.50f;
float GUI::SelectableInfoBoxY				= 0.850f;
float GUI::SelectableHeight					= 0.040f;
bool GUI::ShowHeaderBackground				= true;
bool GUI::ShowHeaderTexture					= true;
bool GUI::DisableMenuGUIOpenCloseFade		= false;
bool GUI::HideGUIElements					= false;		// Prevents all GUI elements from being visible
bool GUI::MenuGUIHasBeenOpened				= false;		// Set when the Menu GUI has been opened at least once
bool GUI::CurrentSelectableIsSavable		= false;
bool GUI::RestorePreviousSubmenu			= true;
std::string GUI::CurrentTheme;
std::string GUI::CurrentSubmenu;
int GUI::maxVisOptions						= 11;
int GUI::currentOption						= 0;
int GUI::currentOptionVisible				= 0; // This has GUI::Break excluded
int GUI::previousOption						= 0;
int GUI::optionCount						= 0;
int GUI::optionCountVisible					= 0; // This has GUI::Break excluded
int GUI::TotalOptionsCount					= 0;
int GUI::menuLevel							= 0;
void* GUI::PreviousMenu						= nullptr;
void* GUI::currentMenu						= nullptr;
int GUI::PreviousMenuLevel					= 0;
int GUI::optionsArray						[1000];
void* GUI::menusArray						[1000];
std::vector <std::string> GUI::ThemeFilesVector;
                 
RGBA GUI::PrimaryColor						{ 0, 0, 255, 255 };
RGBAF GUI::TextColorAndFont					{ 255, 255, 255, 255, FontChaletLondon };
int GUI::SelectableTransparency				= 150;
int GUI::HeaderBackgroundTransparency		= 200;
int GUI::TitleAndEndTransparency			= 210;
int GUI::ToggleSelectableTransparency		= 255;
int GUI::HeaderTextureTransparency			= 255;
int GUI::EndSmallLogoTransparency			= 255;
int GUI::OnlinePlayerPictureTransparency	= 255;

int GUI::MenuArrowAnimationDelay			= 1000;

void GUI::Loop()
{
	// Draw menu bottom
	if (GUI::menuLevel > 0)
	{
		GUI::TotalOptionsCount = GUI::optionCount;
		float OptionCountPositionX = GUI::guiX - (GUI::guiWidth * 43 / 100);
		float BuildNumberPositionX = GUI::guiX + (GUI::guiWidth * 42 / 100);
		float OptionCountAndBuildNumberY, RectY, LogoSmall;
		if (GUI::optionCount >= GUI::maxVisOptions)
		{
			OptionCountAndBuildNumberY = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.172f);
			RectY = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.1585f);
			LogoSmall = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.159f);
		}
		else if (GUI::optionCount > 0)
		{
			OptionCountAndBuildNumberY = GUI::guiY + (GUI::optionCount + 1) * SelectableHeight - 0.172f;
			RectY = GUI::guiY + (GUI::optionCount + 1) * SelectableHeight - 0.1585f;
			LogoSmall = GUI::guiY + ((GUI::optionCount + 1) * SelectableHeight - 0.159f);
		}

		if (GUI::currentOptionVisible != 0 && GUI::optionCountVisible != 0)
		{
			DrawTextInGame(std::to_string(GUI::currentOptionVisible) + "/" + std::to_string(GUI::optionCountVisible), TextColorAndFont, { OptionCountPositionX, OptionCountAndBuildNumberY }, { 0.30f, 0.30f }, true);
		}
		DrawTextInGame(build_info::VersionString, TextColorAndFont, { BuildNumberPositionX, OptionCountAndBuildNumberY }, { 0.30f, 0.30f }, true);
		DrawRectInGame({ 0, 0, 0, TitleAndEndTransparency }, { GUI::guiX, RectY }, { GUI::guiWidth, SelectableHeight });
		DrawSpriteInGame("Textures", "LogoSmall", GUI::guiX, LogoSmall, 0.030f, 0.045f, 0, GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b, EndSmallLogoTransparency);
	}
}

void GUI::MoveMenu(void* Submenu)
{
	GUI::menusArray[GUI::menuLevel] = GUI::currentMenu;
	GUI::optionsArray[GUI::menuLevel] = GUI::currentOption;
	GUI::menuLevel++;
	GUI::currentMenu = Submenu;
	GUI::currentOption = 1;
}

void GUI::CloseMenuGUI()
{
	GUI::PreviousMenu = GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel = 0;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
	if (Controls::DisableCursorNavigationWhenMenuGUIIsClosed)
	{
		if (CheatFeatures::CursorNavigationState)
		{
			GameFunctions::EnableDisableCursorNavigation();
		}
	}
}

void GUI::BackMenu()
{
	if (GUI::currentMenu == GUI::Submenus::Home)
	{
		CloseMenuGUI();
	}
	else
	{
		GUI::PreviousMenu = GUI::currentMenu;
		GUI::PreviousMenuLevel = GUI::menuLevel;
		GUI::previousOption = GUI::currentOption;
		GUI::menuLevel--;
		GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
		GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
	}
}

void GUI::AddPlayerInfoBoxTextEntry(std::string text, int Row1, int Row2, int Row3, int Row4)
{
	if (GUI::guiX < 0.55f)
	{
		if (Row1 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX + (GUI::guiWidth / 2) + 0.010f, GUI::guiY + (Row1 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX + (GUI::guiWidth / 2) + 0.105f, GUI::guiY + (Row2 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX + (GUI::guiWidth / 2) + 0.195f, GUI::guiY + (Row3 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX + (GUI::guiWidth / 2) + 0.265f, GUI::guiY + (Row4 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
	}
	else
	{
		if (Row1 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX - (GUI::guiWidth / 2) - 0.325f, GUI::guiY + (Row1 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX - (GUI::guiWidth / 2) - 0.255f, GUI::guiY + (Row2 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX - (GUI::guiWidth / 2) - 0.175f, GUI::guiY + (Row3 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { guiX - (GUI::guiWidth / 2) - 0.070f, GUI::guiY + (Row4 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
	}
}

void GUI::LoadTheme(std::string ThemeFileName, bool StartUp)
{
	std::string TargetThemePath = file_system::paths::ThemesDir + "\\" + ThemeFileName + ".ini";

	if (!std::filesystem::exists(TargetThemePath))
	{ 
		GameFunctions::MinimapNotification((char*)"Requested Theme does not exist. Auto load entry removed from config file.");
		CheatFunctions::IniFileRemoveKey(file_system::paths::ConfigFile, "submenu_settings", "Active Theme");
		return;
	}

	GUI::CurrentTheme = ThemeFileName;
	try
	{
		DisableMenuGUIOpenCloseFade = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Menu", "open/close_fade_disabled"));
		GUI::guiWidth = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Menu", "menu_gui_width"));

		GUI::guiX = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Positioning", "menu_gui_x"));
		GUI::guiY = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Positioning", "menu_gui_y"));

		GUI::SelectableInfoBoxX = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Positioning", "selectable_information_box_x"));
		GUI::SelectableInfoBoxY = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Positioning", "selectable_information_box_y"));
		GUI::SelectableHeight = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Positioning", "selectable_height"));

		GUI::ShowHeaderTexture = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Header", "header_texture"));
		GUI::ShowHeaderBackground = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Header", "header_background"));
	
		CheatFeatures::RGBDiscoBool = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "rgb_disco"));

		if (!CheatFeatures::RGBDiscoBool)
		{
			GUI::PrimaryColor.r = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "primary_color_r"));
			GUI::PrimaryColor.g = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "primary_color_g"));
			GUI::PrimaryColor.b = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "primary_color_b"));

			GUI::TextColorAndFont.r = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "text_color_r"));
			GUI::TextColorAndFont.g = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "text_color_g"));
			GUI::TextColorAndFont.b = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Color", "text_color_b"));
		}

		GUI::TextColorAndFont.f = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Font", "text_font"));
	}
	catch (...) {}

	// Check Theme File Version
	if (CheatFunctions::IniFileReturnKeyValueAsString(TargetThemePath, "Theme", "theme_file_version") != "2.3")
	{
		GameFunctions::SubtitleNotification((char*)"The loaded Theme is outdated. Please resave it", 5000);
	}

	// Save New Active Theme Name To Config File
	if (!StartUp) 
	{
		CheatFunctions::IniFileWriteString(GUI::CurrentTheme, file_system::paths::ConfigFile, "submenu_settings", "Active Theme");
		GameFunctions::MinimapNotification((char*)"Theme Loaded");
	}
}

void GUI::DeleteLoadedTheme()
{
	remove(CheatFunctions::StringToChar(file_system::paths::ThemesDir + "\\" + CurrentTheme + ".ini"));
	CheatFunctions::IniFileRemoveKey(file_system::paths::ConfigFile, "submenu_settings", "Active Theme");
	GUI::CurrentTheme.clear();
	GUI::currentOption = 1;
	GameFunctions::MinimapNotification((char*)"Theme Removed");
}

void GUI::SaveTheme(std::string ThemeFileName)
{
	std::string TargetThemePath = file_system::paths::ThemesDir + "\\" + ThemeFileName + ".ini";

	CheatFunctions::IniFileWriteString("2.3", TargetThemePath, "Theme", "theme_file_version");

	CheatFunctions::WriteBoolToIni(DisableMenuGUIOpenCloseFade, TargetThemePath, "Menu", "open/close_fade_disabled");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::guiWidth), TargetThemePath, "Menu", "menu_gui_width");

	CheatFunctions::IniFileWriteString(std::to_string(GUI::guiX), TargetThemePath, "Positioning", "menu_gui_x");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::guiY), TargetThemePath, "Positioning", "menu_gui_y");

	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableInfoBoxX), TargetThemePath, "Positioning", "selectable_information_box_x");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableInfoBoxY), TargetThemePath, "Positioning", "selectable_information_box_y");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableHeight), TargetThemePath, "Positioning", "selectable_height");

	CheatFunctions::WriteBoolToIni(GUI::ShowHeaderTexture, TargetThemePath, "Header", "header_texture");
	CheatFunctions::WriteBoolToIni(GUI::ShowHeaderBackground, TargetThemePath, "Header", "header_background");

	CheatFunctions::WriteBoolToIni(CheatFeatures::RGBDiscoBool, TargetThemePath, "Color", "rgb_disco");
	if (!CheatFeatures::RGBDiscoBool)
	{
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.r), TargetThemePath, "Color", "primary_color_r");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.g), TargetThemePath, "Color", "primary_color_g");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.b), TargetThemePath, "Color", "primary_color_b");

		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.r), TargetThemePath, "Color", "text_color_r");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.g), TargetThemePath, "Color", "text_color_g");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.b), TargetThemePath, "Color", "text_color_b");
	}

	CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.f), TargetThemePath, "Font", "text_font");

	GameFunctions::MinimapNotification((char*)"Theme Saved");
}

void GUI::LoadTextureFile()
{
	Logger::LogMsg(LoggerMsgTypes::LOGGER_INFO_MSG, "Loading Custom Textures");
	if (!CheatFeatures::NoTextureFileOverwrite)
	{
		remove(CheatFunctions::StringToChar(file_system::paths::TextureFile));

		// Find and load the resource
		HRSRC hResource = FindResourceA(CheatModuleHandle, MAKEINTRESOURCEA(140), "CHEAT_DATA");
		if (!hResource) { goto Error; }
		HGLOBAL hFileResource = LoadResource(CheatModuleHandle, hResource);
		if (!hFileResource) { goto Error; }

		// Open and map this to a disk file
		LPVOID lpFile = LockResource(hFileResource);
		DWORD dwSize = SizeofResource(CheatModuleHandle, hResource);

		// Open the file and filemap
		HANDLE hFile = CreateFileA(CheatFunctions::StringToChar(file_system::paths::TextureFile), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
		if (!hFileMap) { goto Error; }

		LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
		if (!lpAddress) { goto Error; }

		// Write the file
		CopyMemory(lpAddress, lpFile, dwSize);

		// Un-map the file and close the handles
		UnmapViewOfFile(lpAddress);
		CloseHandle(hFileMap);
		CloseHandle(hFile);
	}

	int textureID;
	if (std::filesystem::exists(file_system::paths::TextureFile))
	{
		GameHooking::texture_file_register(&textureID, CheatFunctions::StringToChar(file_system::paths::TextureFile), true, "Textures.ytd", false);
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Textures", false); // Ensure the custom textures are loaded by RAGE because we need them soon
		return;
	}
	else
	{
		goto Error;
	}

	//Error
Error:
	GameFunctions::MinimapNotification((char*)"~r~Failed to load Texture file");
	Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Failed to load Texture file; missing");
}

void GUI::DrawTextInGame(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool Outline)
{
	if (!GUI::HideGUIElements)
	{
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		UI::SET_TEXT_FONT(rgbaf.f);
		if (Outline) { UI::SET_TEXT_OUTLINE(); }
		UI::SET_TEXT_SCALE(size.w, size.h);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(CheatFunctions::StringToChar(text));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
	}
}

void GUI::DrawSpriteInGame(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GUI::HideGUIElements)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE(Streamedtexture.c_str(), textureName.c_str(), x, y, width, height, rotation, r, g, b, a, false, 0);
		}
	}
}

void GUI::DrawRectInGame(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	if (!GUI::HideGUIElements)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a, false);
	}
}

void GUI::ShowPlayerInformationBox(Player PlayerID)
{
	if (!CheatFeatures::HidePlayerInformationBox)
	{
		//Definitions
		Ped SelectedPlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PlayerID);
		GameFunctions::RequestNetworkControlOfEntity(SelectedPlayerPed);

		//Draw Title and Background
		if (GUI::guiX < 0.54f)
		{
			GUI::DrawRectInGame(GUI::PrimaryColor, { guiX + (GUI::guiWidth / 2) + 0.166f, GUI::guiY + 0.014f }, { 0.32f, 0.31f }); //Main Background Rect
			GUI::DrawTextInGame("Player Information", { GUI::TextColorAndFont }, { guiX + (GUI::guiWidth / 2) + 0.155f, GUI::guiY - 0.170f }, { 0.50f, 0.37f }, true);
			GUI::DrawRectInGame({ 0, 0, 0, GUI::PrimaryColor.a }, { guiX + (GUI::guiWidth / 2) + 0.166f, GUI::guiY - 0.156f }, { 0.32f, 0.030f });
		}
		else
		{
			GUI::DrawRectInGame(GUI::PrimaryColor, { guiX - (GUI::guiWidth / 2) - 0.166f, GUI::guiY + 0.014f }, { 0.32f, 0.31f }); //Main Background Rect
			GUI::DrawTextInGame("Player Information", { GUI::TextColorAndFont }, { guiX - (GUI::guiWidth / 2) - 0.155f, GUI::guiY - 0.170f }, { 0.50f, 0.37f }, true);
			GUI::DrawRectInGame({ 0, 0, 0, GUI::PrimaryColor.a }, { guiX - (GUI::guiWidth / 2) - 0.166f,GUI::guiY - 0.156f }, { 0.32f, 0.030f });
		}


		
		//Text Entry's
		GUI::AddPlayerInfoBoxTextEntry("Name", 1);
		GUI::AddPlayerInfoBoxTextEntry(PLAYER::GET_PLAYER_NAME(PlayerID), NULL, 1);

		// Statistics
		GUI::AddPlayerInfoBoxTextEntry("Rank", 2);
		GUI::AddPlayerInfoBoxTextEntry("Money (bank & cash)", 3);
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			std::ostringstream PlayerRank;
			PlayerRank << globalHandle(GLOBAL_PLAYERSTAT_RANK[0]).At(PlayerID, GLOBAL_PLAYERSTAT_RANK[1]).At(GLOBAL_PLAYERSTAT_RANK[2]).At(GLOBAL_PLAYERSTAT_RANK[3]).As<int>();
			GUI::AddPlayerInfoBoxTextEntry(PlayerRank.str(), NULL, 2);

			std::ostringstream PlayerMoney;
			PlayerMoney << "$" << globalHandle(GLOBAL_PLAYERSTAT_TOTALMONEY[0]).At(PlayerID, GLOBAL_PLAYERSTAT_TOTALMONEY[1]).At(GLOBAL_PLAYERSTAT_TOTALMONEY[2]).At(GLOBAL_PLAYERSTAT_TOTALMONEY[3]).As<__int64>();
			GUI::AddPlayerInfoBoxTextEntry(PlayerMoney.str(), NULL, 3);
		}
		else
		{
			GUI::AddPlayerInfoBoxTextEntry("N/A", NULL, 2);
			GUI::AddPlayerInfoBoxTextEntry("N/A", NULL, 3);
		}

		
		//Health
		std::ostringstream Health;
		float health = ENTITY::GET_ENTITY_HEALTH(SelectedPlayerPed);
		float HealthValue = health * 100 / ENTITY::GET_ENTITY_MAX_HEALTH(SelectedPlayerPed);
		GUI::AddPlayerInfoBoxTextEntry("Health", 4);
		if (HealthValue == 100)
		{
			GUI::AddPlayerInfoBoxTextEntry("Full", NULL, 4);
		}
		else
		{
			Health << HealthValue << "%";
			GUI::AddPlayerInfoBoxTextEntry(Health.str(), NULL, 4);
		}

		//Armor
		std::ostringstream Armor;
		int ArmorValue = PED::GET_PED_ARMOUR(SelectedPlayerPed) * 100 / PLAYER::GET_PLAYER_MAX_ARMOUR(PlayerID);
		GUI::AddPlayerInfoBoxTextEntry("Armor", 5);
		if (ArmorValue == 99 || ArmorValue == 100)
		{
			GUI::AddPlayerInfoBoxTextEntry("Full", NULL, 5);
		}
		else
		{
			Armor << ArmorValue;
			GUI::AddPlayerInfoBoxTextEntry(Armor.str(), NULL, 5);
		}

		//Status
		std::ostringstream Status;
		GUI::AddPlayerInfoBoxTextEntry("Status", 6);
		if (TASK::IS_PED_STILL(SelectedPlayerPed)) { Status << "Player is still"; }
		else if (TASK::IS_PED_WALKING(SelectedPlayerPed)) { Status << "Player is walking"; }
		else if (TASK::IS_PED_RUNNING(SelectedPlayerPed)) { Status << "Player is running"; }
		else if (TASK::IS_PED_SPRINTING(SelectedPlayerPed)) { Status << "Player is sprinting"; }
		else if (PED::IS_PED_CLIMBING(SelectedPlayerPed)) { Status << "Player is climbing"; }
		else if (PED::IS_PED_DIVING(SelectedPlayerPed)) { Status << "Player is diving"; }
		else if (PED::IS_PED_FALLING(SelectedPlayerPed)) { Status << "Player is falling"; }
		else if (PED::IS_PED_DEAD_OR_DYING(SelectedPlayerPed, true)) { Status << "Player is dead"; }
		else { Status << "~c~Unknown"; }
		GUI::AddPlayerInfoBoxTextEntry(Status.str(), NULL, 6);

		

		//Vehicle
		bool InAnyVehicle = PED::IS_PED_IN_ANY_VEHICLE(SelectedPlayerPed, 0);
		std::ostringstream Vehicle;
		GUI::AddPlayerInfoBoxTextEntry("Vehicle", 7);
		if (InAnyVehicle)
		{
			Vehicle << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(SelectedPlayerPed, 0))));
		}
		else
		{
			Vehicle << "~c~Not in a vehicle";
		}
		GUI::AddPlayerInfoBoxTextEntry(Vehicle.str(), NULL, 7);

		
		//Speed
		std::ostringstream Speed;
		if (InAnyVehicle)
		{
			GUI::AddPlayerInfoBoxTextEntry("Vehicle Speed", 8);
			float VehicleSpeed = round(ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(SelectedPlayerPed, false)) * 100) / 100;
			if (MISC::SHOULD_USE_METRIC_MEASUREMENTS())
			{
				Speed << GameFunctions::MSToKMH(VehicleSpeed) << " KM/H";
			}
			else
			{
				Speed << GameFunctions::MSToMPH(VehicleSpeed) << " MP/H";
			}
			GUI::AddPlayerInfoBoxTextEntry(Speed.str(), NULL, 8);
		}
		else
		{
			GUI::AddPlayerInfoBoxTextEntry("Movement Speed", 8);
			Speed << round(ENTITY::GET_ENTITY_SPEED(SelectedPlayerPed) * 100) / 100 << " M/S";
			GUI::AddPlayerInfoBoxTextEntry(Speed.str(), NULL, 8);
		}


		//Wanted Level
		std::ostringstream WantedLevel;
		int PlayerWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(PlayerID);
		GUI::AddPlayerInfoBoxTextEntry("Wanted Level", 9);
		WantedLevel << PlayerWantedLevel << "/5";
		GUI::AddPlayerInfoBoxTextEntry(WantedLevel.str(), NULL, 9);

		

		Hash WeaponHash;
		GUI::AddPlayerInfoBoxTextEntry("Weapon", 10);
		std::string WeaponName;
		if (WEAPON::GET_CURRENT_PED_WEAPON(SelectedPlayerPed, &WeaponHash, true))
		{
			for (auto const& i : GameArrays::WeaponsHashList)
			{
				if (WeaponHash == i.WeaponHash)
				{
					WeaponName = i.WeaponName;
				}
			}
		}
		else
		{
			WeaponName = "Unarmed";
		}
		GUI::AddPlayerInfoBoxTextEntry(WeaponName, NULL, 10);

		
		//Coords
		Vector3 SelectedPlayerPedCoords = ENTITY::GET_ENTITY_COORDS(SelectedPlayerPed, false);
		std::ostringstream CoordX;
		std::ostringstream CoordY;
		std::ostringstream CoordZ;

		CoordX << SelectedPlayerPedCoords.x;
		CoordY << SelectedPlayerPedCoords.y;
		CoordZ << SelectedPlayerPedCoords.z;

		GUI::AddPlayerInfoBoxTextEntry("X", 11);
		GUI::AddPlayerInfoBoxTextEntry("Y", 12);
		GUI::AddPlayerInfoBoxTextEntry("Z", 13);
		GUI::AddPlayerInfoBoxTextEntry(CoordX.str(), NULL, 11);
		GUI::AddPlayerInfoBoxTextEntry(CoordY.str(), NULL, 12);
		GUI::AddPlayerInfoBoxTextEntry(CoordZ.str(), NULL, 13);
		

		std::ostringstream Zone;
		GUI::AddPlayerInfoBoxTextEntry("Zone", 14);
		Zone << UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(SelectedPlayerPedCoords.x, SelectedPlayerPedCoords.y, SelectedPlayerPedCoords.z));
		GUI::AddPlayerInfoBoxTextEntry(Zone.str(), NULL, 14);


		/*
		Hash streetName, crossingRoad;
		PATHFIND::GET_STREET_NAME_AT_COORD(SelectedPlayerPedCoords.x, SelectedPlayerPedCoords.y, SelectedPlayerPedCoords.z, &streetName, &crossingRoad);
		GUI::AddPlayerInfoBoxTextEntry("Street", 15);
		std::ostringstream Street;
		Street << UI::GET_STREET_NAME_FROM_HASH_KEY(streetName);
		GUI::AddPlayerInfoBoxTextEntry(Street.str(), NULL, 15);

		float distance = GameFunctions::Get3DDistance(SelectedPlayerPedCoords, ENTITY::GET_ENTITY_COORDS(GameFunctions::PlayerPedID, false));
		std::ostringstream Distance;

		if (PlayerID != GameFunctions::PlayerID)
		{
			if (distance > 1000)
			{
				distance = round((distance / 1000) * 100) / 100;
				Distance << distance << " KM";
			}
			else
			{
				distance = round(distance * 1000) / 100;
				Distance << distance << " M";
			}
		}
		else
		{
			Distance << "N/A";
		}
		GUI::AddPlayerInfoBoxTextEntry("Distance", NULL, NULL, 1);
		GUI::AddPlayerInfoBoxTextEntry(Distance.str(), NULL, NULL, NULL, 1);
		*/
		
		//Modded Model
		Hash SelectedPlayerPedModel = ENTITY::GET_ENTITY_MODEL(SelectedPlayerPed);
		GUI::AddPlayerInfoBoxTextEntry("Modded Model", NULL, NULL, 2);
		if (NETWORK::NETWORK_IS_SESSION_STARTED() && SelectedPlayerPedModel != 0x705E61F2 && SelectedPlayerPedModel != 0x9C9EFFD8)
		{
			GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 2);
		}
		else
		{
			GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 2);
		}

		//Is in interior
		GUI::AddPlayerInfoBoxTextEntry("In Interior", NULL, NULL, 3);
		if (GameFunctions::IsEntityInInterior(SelectedPlayerPed))
		{
			GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 3);
		}
		else
		{
			GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 3);
		}

		//Cutscene
		GUI::AddPlayerInfoBoxTextEntry("Cutscene", NULL, NULL, 4);
		if (NETWORK::IS_PLAYER_IN_CUTSCENE(PlayerID))
		{
			GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 4);
		}
		else
		{
			GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 4);
		}
		
		//Rockstar ID
		GUI::AddPlayerInfoBoxTextEntry("Rockstar ID", NULL, NULL, 5);
		GUI::AddPlayerInfoBoxTextEntry(std::to_string(GameFunctions::ReturnPlayerRockstarID(PlayerID)), NULL, NULL, NULL, 5);

		//IP Address
		std::string PlayerIPString = GameFunctions::ReturnPlayerIPAddressAsString(PlayerID);
		GUI::AddPlayerInfoBoxTextEntry("IP Address", NULL, NULL, 6);
		GUI::AddPlayerInfoBoxTextEntry(PlayerIPString, NULL, NULL, NULL, 6);
	}
}