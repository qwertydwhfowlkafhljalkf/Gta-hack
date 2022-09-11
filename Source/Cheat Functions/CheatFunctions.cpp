#include "../Header/Cheat Functions/FiberMain.h"

std::string Cheat::CheatFunctions::NewCheatVersionString;
bool Cheat::CheatFunctions::CheatInitEntirelyCompleted = false;									// Set when both CheatInitCompleted and ConfigLoaded are set
bool Cheat::CheatFunctions::CheatInitCompleted = false;											// Set when all initialization is completed (except for async tasks such as LoadConfig())
bool Cheat::CheatFunctions::ConfigLoaded = false;												// Set when the LoadConfig thread is completed
std::vector <std::string> Cheat::CheatFunctions::LoadedSelectablesVector;						// Used during the async LoadConfig process to determine which selectables have been loaded

void Cheat::CheatFunctions::CreateNewDirectory(std::string Path)
{
	if (!std::filesystem::create_directory(Path))
	{
		std::string String = __func__ + (std::string)"() Failed to create directory '" + Path + "' WinAPI Error Code: " + std::to_string(GetLastError());
		Cheat::Logger::DebugMessage(String);
	}
	else
	{
		std::string String = __func__ + (std::string)"() Created directory '" + Path + "'";
		Cheat::Logger::DebugMessage(String);
	}
}

// See https://en.cppreference.com/w/cpp/io/manip/put_time
std::string Cheat::CheatFunctions::ReturnDateTimeFormatAsString(const char* DateTimeFormat)
{
	struct tm NewTimeHandle;
	time_t CurrentTimeHandle = time(0);
	localtime_s(&NewTimeHandle, &CurrentTimeHandle);
	std::ostringstream TimeDateString;
	TimeDateString << std::put_time(&NewTimeHandle, DateTimeFormat);
	return TimeDateString.str();
}

std::string Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath()
{
	char CheatModuleFilePath[MAX_PATH];
	GetModuleFileNameA(CheatModuleHandle, CheatModuleFilePath, MAX_PATH);
	return std::filesystem::path(CheatModuleFilePath).parent_path().string();
}

std::string Cheat::CheatFunctions::GetWindowsUserDocumentsFolderPath()
{
	return std::getenv("userprofile") + (std::string)"\\Documents";
}

const std::string Cheat::CheatFunctions::ReturnConfigFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Config.ini";
}

const std::string Cheat::CheatFunctions::ReturnMainLogFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Logs\\Main.log";
}

const std::string Cheat::CheatFunctions::ReturnChatLogFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Logs\\Chats.log";
}

const std::string Cheat::CheatFunctions::ReturnCustomTeleportLocationsFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\CustomTeleportLocations.json";
}

const std::string Cheat::CheatFunctions::ReturnHUDColorsFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\HUDColors.ini";
}

const std::string Cheat::CheatFunctions::ReturnThemeFilePath(std::string ThemeName)
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Themes\\" + ThemeName + ".ini";
}

std::string Cheat::CheatFunctions::ReturnTextureFilePath()
{
	return GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Textures.ytd";
}

bool Cheat::CheatFunctions::FileOrDirectoryExists(std::string Path)
{
	if (std::filesystem::exists(Path))
	{
		return true;
	}
	return false;
}

static std::once_flag CheatInitialization;
void Cheat::CheatFunctions::Loop()
{
	std::call_once(CheatInitialization, []()
	{
		// Check for newer cheat version
		CheckCheatUpdate();

		// Create Menu Selectable Arrow Animation Thread
		std::thread MenuSelectableAnimationThreadHandle([]()
			{
				if (GUI::menuLevel > 0)
				{
					GUI::MenuOptionArrowAnimationState = !GUI::MenuOptionArrowAnimationState;
					Sleep(GUI::MenuArrowAnimationDelay);
				}
			});
		MenuSelectableAnimationThreadHandle.detach();

		// Load configuration file
		LoadConfig();

		// Load texture file
		GUI::LoadTextureFile();

		// Load 'multiplayer vehicles in Single Player' bypass
		globalHandle(GLOBAL_SP_DESPAWN_BYPASS).As<BOOL>() = true;
		Cheat::Logger::DebugMessage("Loaded SPVSB");

		// Fetch default HUD colors
		for (int i = 0; i <= GameArrays::HUDColors.size(); i++)
		{
			DefaultHUDColorsStruct data{};
			UI::GET_HUD_COLOUR(i, &data.R, &data.G, &data.B, &data.A);
			GameArrays::DefaultHUDColors.push_back(data);
		}
		Cheat::Logger::DebugMessage("Fetched DHC");

		// Load saved HUD colors
		if (FileOrDirectoryExists(ReturnHUDColorsFilePath()))
		{
			int SavedHUDColorsIndex = 0;
			for (auto const& HUDColorComponentName : GameArrays::HUDColors)
			{
				std::string Red = IniFileReturnKeyValueAsString(ReturnHUDColorsFilePath(), HUDColorComponentName, "r");
				std::string Green = IniFileReturnKeyValueAsString(ReturnHUDColorsFilePath(), HUDColorComponentName, "g");
				std::string Blue = IniFileReturnKeyValueAsString(ReturnHUDColorsFilePath(), HUDColorComponentName, "b");
				std::string Alpha = IniFileReturnKeyValueAsString(ReturnHUDColorsFilePath(), HUDColorComponentName, "a");

				if (!Red.empty() && !Green.empty() && !Blue.empty() && !Alpha.empty())
				{
					try
					{
						UI::REPLACE_HUD_COLOUR_WITH_RGBA(SavedHUDColorsIndex, std::stoi(Red), std::stoi(Green), std::stoi(Blue), std::stoi(Alpha));
					}
					catch (...) {}
					Cheat::Logger::DebugMessage("Loaded CHC '" + HUDColorComponentName + "'");
				}
				SavedHUDColorsIndex++;
			}
		}

		// Cheat init completed
		CheatFunctions::CheatInitCompleted = true;
		Logger::DebugMessage("Cheat init completed");
	});

	// Submenu handlers - additional submenu logic is looped here
	for (int FuncPointerIndex = 0; FuncPointerIndex < Cheat::GUI::Submenus::NumberOfSubmenus; ++FuncPointerIndex)
	{
		if (GUI::currentMenu == (*Cheat::GUI::Submenus::FunctionPointers[FuncPointerIndex]))
		{
			(*Cheat::GUI::Submenus::FunctionPointers[FuncPointerIndex])();
		}
	}
	if (GUI::currentMenu == GUI::Submenus::SelectedPlayer ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerFriendly ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerRemote ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerTeleport ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerAttachments ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerGriefing ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerApartmentTeleport ||
		GUI::currentMenu == GUI::Submenus::SelectedPlayerRemote)
	{
		if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(CheatFeatures::SelectedPlayer))
		{
			GUI::ShowPlayerInformationBox(CheatFeatures::SelectedPlayer);
		}
		else
		{
			GUI::PreviousMenu = nullptr;
			GUI::MoveMenu(GUI::Submenus::Home);
			GUI::MoveMenu(GUI::Submenus::Session);
		}
	}
	if (GUI::currentMenu == GUI::Submenus::ThemeFiles)
	{
		GUI::ThemeFilesVector.clear();
		std::string ThemeFolderPath = CheatFunctions::GetWindowsUserDocumentsFolderPath() + (std::string)"\\GTAV Cheat\\Themes";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(ThemeFolderPath)) { CheatFunctions::CreateNewDirectory(ThemeFolderPath); }
		for (const auto& file : std::filesystem::directory_iterator(ThemeFolderPath))
		{
			if (file.path().extension() == ".ini")
			{
				GUI::ThemeFilesVector.push_back(file.path().stem().string());
			}
		}
	}

	// Cheat initializing message
	if (!CheatFunctions::ConfigLoaded && CheatFunctions::CheatInitCompleted)
	{
		GUI::DrawTextInGame("GTAV Cheat is loading, one moment please", { 255, 255, 255, 255 }, { 0.900f, 0.900f }, { 0.400f, 0.400f }, true);
	}

	// GUI - must be called after (^) rendering a submenu
	GUI::MenuGUIBottom();

	// Set CheatInitEntirelyCompleted when all init is completed
	CheatInitEntirelyCompleted = CheatInitCompleted && ConfigLoaded;
}

bool Cheat::CheatFunctions::IsGameWindowFocussed()
{
	if (FindWindowA("grcWindow", "Grand Theft Auto V") == GetForegroundWindow())
	{ 
		return true;
	}
	return false;
}

bool Cheat::CheatFunctions::StringIsInteger(std::string String)
{
	return !String.empty() && std::find_if(String.begin(), String.end(), [](unsigned char c) { return !std::isdigit(c); }) == String.end();
}

int Cheat::CheatFunctions::WaitForAndReturnPressedKey()
{
	while (true)
	{
		GUI::DrawTextInGame("~bold~Press any key, press Escape to cancel", { 255, 255, 255, 255 }, { 0.525f, 0.400f }, { 0.900f, 0.900f }, true); GameHooking::PauseMainFiber(0, false);
		for (int i = 1; i < 256; i++)
		{
			if (IsKeyCurrentlyPressed(i) && i != VK_RETURN && i != VK_NUMPAD5)
			{
				if (i == VK_ESCAPE)
				{
					Cheat::GameFunctions::MinimapNotification("Canceled Key Selection");
					return 0;
				}
				return i;
			}
		}
	}
}

void Cheat::CheatFunctions::SaveSelectable(std::string OptionName, std::string OptionValue, bool IsSavable)
{
	GUI::CurrentSelectableIsSavable = IsSavable;
	if (IsKeyCurrentlyPressed(Controls::SaveSelectableKey))
	{
		if (IsSavable)
		{
			std::string LogMessage = "'" + OptionName + "' (" + GUI::CurrentSubmenu + " submenu) selectable state saved";
			Cheat::GameFunctions::AdvancedMinimapNotification(StringToChar(LogMessage), "Textures", "AdvancedNotificationImage", false, 4, "Config", "", 0.5f, "");
			Logger::DebugMessage(LogMessage);
			IniFileWriteString(OptionValue, ReturnConfigFilePath(), "submenu_" + GUI::CurrentSubmenu, OptionName);
		}
	}
}

std::string Cheat::CheatFunctions::GetSelectableValueFromConfig(std::string OptionName)
{
	return IniFileReturnKeyValueAsString(ReturnConfigFilePath(), "submenu_" + GUI::CurrentSubmenu, OptionName);
}

void LoadConfigThreadFunction()
{
	Cheat::Controls::ChangeKeyInputState(false);
	Cheat::GUI::HideGUIElements = true;
	for (int FuncPointerIndex = 0; FuncPointerIndex < Cheat::GUI::Submenus::NumberOfSubmenus; ++FuncPointerIndex)
	{
		Cheat::GUI::MoveMenu((*Cheat::GUI::Submenus::FunctionPointers[FuncPointerIndex]));
		Sleep(150);
	}
	Cheat::GUI::CloseMenuGUI();
	Cheat::GUI::PreviousMenu = nullptr;
	Cheat::Controls::ChangeKeyInputState(true);
	Cheat::GUI::HideGUIElements = false;
	Cheat::CheatFunctions::LoadedSelectablesVector.clear();
	Cheat::CheatFunctions::ConfigLoaded = true;
}

void Cheat::CheatFunctions::LoadConfig()
{
	Cheat::Logger::Message("Loading Configuration");

	// Load hotkeys
	std::string MenuGUIKey = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_settings", "Menu GUI Key");
	if (!MenuGUIKey.empty()) { Controls::OpenMenuGUIKey = StringToInt(MenuGUIKey); }
	
	std::string CursorNavigationKeyString = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_settings", "Cursor Navigation Key");
	if (!CursorNavigationKeyString.empty()) { Controls::CursorNavigationKey = StringToInt(CursorNavigationKeyString); }

	std::string SaveSelectableKey = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_settings", "Save Selectable Key");
	if (!SaveSelectableKey.empty()) { Controls::SaveSelectableKey = StringToInt(SaveSelectableKey); }

	// Load Active Theme
	std::string ActiveThemeSetting = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_settings", "Active Theme");
	if (!ActiveThemeSetting.empty()) { GUI::LoadTheme(ActiveThemeSetting, true); }

	// Load Vehicle Spawner Custom License Plate Text
	std::string VehicleSpawnerCustomLicensePlateText = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_vehicle spawn settings", "Custom License Plate Text");
	if (!VehicleSpawnerCustomLicensePlateText.empty()) { CheatFeatures::VehicleSpawnerCustomLicensePlateTextString = VehicleSpawnerCustomLicensePlateText; }

	// Do not overwrite "Textures.ytd" at init feature - setting must be loaded immediatly (not async)
	CheatFeatures::NoTextureFileOverwrite = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "submenu_settings", "do not overwrite \"textures.ytd\" at init"));

	std::thread LoadConfigThreadHandle(LoadConfigThreadFunction);
	LoadConfigThreadHandle.detach();
}

bool Cheat::CheatFunctions::IsSelectableRegisteredAsLoaded(std::string OptionName)
{
	for (auto const& i : LoadedSelectablesVector)
	{
		if (i == OptionName)
		{
			return true;
		}
	}
	return false;
}

char* Cheat::CheatFunctions::StringToChar(std::string String)
{
	return _strdup(String.c_str());
}

const char* Cheat::CheatFunctions::StringToConstChar(std::string String)
{
	auto Temp = String.c_str();
	return Temp;
}

std::string Cheat::CheatFunctions::VirtualKeyCodeToString(UCHAR virtualKey)
{
	UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	CHAR szName[128];
	int result = 0;
	switch (virtualKey)
	{
	case VK_LEFT:		case VK_UP: case VK_RIGHT: case VK_DOWN:
	case VK_RCONTROL:	case VK_RMENU:
	case VK_LWIN:		case VK_RWIN: case VK_APPS:
	case VK_PRIOR:		case VK_NEXT:
	case VK_END:		case VK_HOME:
	case VK_INSERT:		case VK_DELETE:
	case VK_DIVIDE:
	case VK_NUMLOCK:
		scanCode |= KF_EXTENDED;
		break;
	default:
		result = GetKeyNameTextA(scanCode << 16, szName, 128);
	}
	if (result == 0) { return "Unknown"; }
	return szName;
}

int Cheat::CheatFunctions::ReturnNumberOfDigitsInValue(double Number) 
{
	int i = 0;
	if (Number < 0)
	{
		Number *= -1;
	}
	while (Number > pow(10, i))
	{
		i++;
	}
	return i;
}

void Cheat::CheatFunctions::IniFileWriteString(std::string string, std::string FilePath, std::string Section, std::string Key)
{
	mINI::INIFile File(FilePath);
	mINI::INIStructure IniStruct;
	File.read(IniStruct);
	IniStruct[Section][Key] = string;
	File.write(IniStruct, true);
}

std::string Cheat::CheatFunctions::IniFileReturnKeyValueAsString(std::string FilePath, std::string Section, std::string Key)
{
	mINI::INIFile File(FilePath);
	mINI::INIStructure IniStruct;
	File.read(IniStruct);
	if (!IniStruct.has(Section) || !IniStruct[Section].has(Key)) { return std::string(); }
	return IniStruct.get(Section).get(Key);
}

void Cheat::CheatFunctions::IniFileRemoveKey(std::string FilePath, std::string Section, std::string Key)
{
	mINI::INIFile File(FilePath);
	mINI::INIStructure IniStruct;
	File.read(IniStruct);
	if (IniStruct[Section].has(Key))
	{
		IniStruct[Section].remove(Key);
		File.write(IniStruct);
	}
}

void Cheat::CheatFunctions::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	IniFileWriteString(b00l ? "true" : "false", file, app, key);
}

bool Cheat::CheatFunctions::StringToBool(std::string String)
{
	std::transform(String.begin(), String.end(), String.begin(), tolower);
	if (String == "true" || String == "1")
	{
		return true;
	}
	else if (String == "false" || String == "0")
	{
		return false;
	}
	return false;
}

bool Cheat::CheatFunctions::IsKeyCurrentlyPressed(int vKey, bool RepeatInput)
{
	if (IsGameWindowFocussed() && !Controls::KeyInputDisabled)
	{
		if (!RepeatInput)
		{
			if (GetAsyncKeyState(vKey) & 0x0001)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (GetAsyncKeyState(vKey) & 0x8000)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

void Cheat::CheatFunctions::WriteToFile(std::string FilePath, std::string text, bool Append)
{
	std::ios_base::openmode Modes = std::ofstream::out;
	std::ios_base::openmode ModesAppend = Modes + std::ofstream::app;
	std::ofstream FileHandle;
	FileHandle.open(FilePath, Append ? ModesAppend : Modes);
	FileHandle << text;
	FileHandle.close();
}

Json::Value Cheat::CheatFunctions::ReturnGithubAPIJsonDataCheat(std::string Build)
{
	if (Build.empty()) { return NULL; }
	CA2W wstringver(Build.c_str());
	Json::Value JsonData;
	std::wstring URL = L"https://api.github.com/repos/HatchesPls/GrandTheftAutoV-Cheat/releases/tags/" + (std::wstring)wstringver;
	HINTERNET hopen = InternetOpen(L"GTAVCheat", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hopen)
	{
		DWORD flags = INTERNET_FLAG_DONT_CACHE;
		HINTERNET hinternet = InternetOpenUrl(hopen, URL.c_str(), NULL, 0, flags, 0);
		if (hinternet)
		{
			char tmp[2048 + 1];
			DWORD received = 0;
			std::string buffer;
			while (InternetReadFile(hinternet, tmp, 2048, &received) && received > 0)
			{
				if (!received) break;
				tmp[received] = '\0';
				buffer += (std::string)tmp;
			}

			Json::CharReaderBuilder CharBuilder;
			JSONCPP_STRING JsonError;
			const std::unique_ptr<Json::CharReader> reader(CharBuilder.newCharReader());

			if (reader->parse(buffer.c_str(), buffer.c_str() + buffer.length(), &JsonData, &JsonError))
			{
				if (JsonData["message"].asString() == "Not Found")
				{
					// Non existent version provided
					return NULL;
				}
			}
			else
			{
				Cheat::Logger::DebugMessage(__func__ + (std::string)"() : failed to parse JSON data. Error message returned by JsonCPP: " + JsonError);
				return NULL;
			}
			InternetCloseHandle(hinternet);
		}
		InternetCloseHandle(hopen);
	}
	return JsonData;
}

std::string Cheat::CheatFunctions::GetLatestCheatBuildNumber()
{
	std::string Version;
	std::wstring URL = L"https://api.github.com/repos/HatchesPls/GrandTheftAutoV-Cheat/releases/latest";
	HINTERNET hopen = InternetOpen(L"GTAVCheat", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hopen)
	{
		DWORD flags = INTERNET_FLAG_DONT_CACHE;
		HINTERNET hinternet = InternetOpenUrl(hopen, URL.c_str(), NULL, 0, flags, 0);
		if (hinternet)
		{
			char tmp[2048 + 1];
			DWORD received = 0;
			std::string buffer;
			while (InternetReadFile(hinternet, tmp, 2048, &received) && received > 0)
			{
				if (!received) break;
				tmp[received] = '\0';
				buffer += (std::string)tmp;
			}

			Json::CharReaderBuilder CharBuilder;
			Json::Value JsonData;
			JSONCPP_STRING JsonError;
			const std::unique_ptr<Json::CharReader> reader(CharBuilder.newCharReader());

			if (reader->parse(buffer.c_str(), buffer.c_str() + buffer.length(), &JsonData, &JsonError))
			{
				Version = JsonData["name"].asString();
			}
			else
			{
				Cheat::Logger::DebugMessage(__func__ + (std::string)"() : failed to parse JSON data. Error message returned by JsonCPP: " + JsonError);
				return "";
			}
			InternetCloseHandle(hinternet);
		}
		InternetCloseHandle(hopen);
	}
	if (!Version.empty())
	{
		return Version;
	}	
	else
	{
		return "";
	}
}

void Cheat::CheatFunctions::CheckCheatUpdate()
{
	Cheat::Logger::Message("Checking for newer cheat version");
	std::string CurrentLocalVersionString = RemoveCharactersFromStringAndReturn(CHEAT_BUILD_NUMBER, ".");
	std::string LatestOnlineVersionString = RemoveCharactersFromStringAndReturn(GetLatestCheatBuildNumber(), "v.");

	if (!LatestOnlineVersionString.empty())
	{
		if (StringIsInteger(CurrentLocalVersionString) && StringIsInteger(LatestOnlineVersionString))
		{
			int CurrentLocalVersion = StringToInt(CurrentLocalVersionString);
			int LatestOnlineVersion = StringToInt(LatestOnlineVersionString);

			if (CurrentLocalVersion < LatestOnlineVersion)
			{
				NewCheatVersionString = "v" + LatestOnlineVersionString;
				Logger::DebugMessage("A newer version of the cheat is available on GitHub");
			}
			else
			{
				Logger::DebugMessage("No newer cheat version available");
			}
		}
	}
}

//https://stackoverflow.com/questions/5891610/how-to-remove-certain-characters-from-a-string-in-c
std::string Cheat::CheatFunctions::RemoveCharactersFromStringAndReturn(std::string String, char* CharactersToRemove)
{
	std::string Temp = String;
	for (unsigned int i = 0; i < strlen(CharactersToRemove); ++i)
	{
		Temp.erase(remove(Temp.begin(), Temp.end(), CharactersToRemove[i]), Temp.end());
	}
	return Temp;
}

//https://www.geeksforgeeks.org/write-your-own-atoi/
int Cheat::CheatFunctions::StringToInt(std::string String)
{
	int sign = 1, base = 0, i = 0;
	while (String[i] == ' ')
	{
		i++;
	}

	if (String[i] == '-' || String[i] == '+')
	{
		sign = 1 - 2 * (String[i++] == '-');
	}

	while (String[i] >= '0' && String[i] <= '9')
	{
		if (base > INT_MAX / 10
			|| (base == INT_MAX / 10
				&& String[i] - '0' > 7))
		{
			if (sign == 1)
			{
				return INT_MAX;
			}
			else
			{
				return INT_MIN;
			}
		}
		base = 10 * base + (String[i++] - '0');
	}
	return base * sign;
}

std::string Cheat::CheatFunctions::TextWrap(std::string String, int Location) 
{
	int NewLine = static_cast<int>(String.rfind(' ', Location));
	if (NewLine != std::string::npos)
	{
		String.at(NewLine) = '\n';
	}
	return String;
}

void Cheat::CheatFunctions::CopyStringToClipboard(const std::string& String)
{
	OpenClipboard(NULL);
	EmptyClipboard();
	HGLOBAL Global = GlobalAlloc(GMEM_MOVEABLE, String.size() + 1);
	if (!Global) { CloseClipboard(); return; }
	LPVOID GlobalPtrn = GlobalLock(Global);
	memcpy(GlobalPtrn, String.c_str(), String.size() + 1);
	GlobalUnlock(Global);
	SetClipboardData(CF_TEXT, Global);
	CloseClipboard();
	GlobalFree(Global);
}

Json::Value Cheat::CheatFunctions::ReadJsonFileAndReturnDataObject(std::string FilePath)
{
	Json::Value JsonHandle;
	std::fstream FileHandle(FilePath, std::ifstream::in);
	if (FileOrDirectoryExists(FilePath))
	{
		try
		{
			FileHandle >> JsonHandle;
		}
		catch (...) { }
	}

	FileHandle.close();
	return JsonHandle;
}

void Cheat::CheatFunctions::AddCustomTeleportLocation(std::string CustomTeleportLocationName)
{
	Json::Value JsonHandle = ReadJsonFileAndReturnDataObject(ReturnCustomTeleportLocationsFilePath());
	remove(StringToConstChar(ReturnCustomTeleportLocationsFilePath()));
	if (JsonHandle.isMember(CustomTeleportLocationName)) { JsonHandle.removeMember(CustomTeleportLocationName); }

	Vector3 LocalPlayerCoords = ENTITY::GET_ENTITY_COORDS(GameFunctions::PlayerPedID, false);
	JsonHandle[CustomTeleportLocationName]["X"] = LocalPlayerCoords.x;
	JsonHandle[CustomTeleportLocationName]["Y"] = LocalPlayerCoords.y;
	JsonHandle[CustomTeleportLocationName]["Z"] = LocalPlayerCoords.z;

	std::fstream FileHandle(ReturnCustomTeleportLocationsFilePath(), std::ios_base::out);
	FileHandle << JsonHandle;
	FileHandle.close();
}

void Cheat::CheatFunctions::DeleteCustomTeleportLocation(std::string CustomTeleportLocationName)
{
	Json::Value JsonHandle = ReadJsonFileAndReturnDataObject(ReturnCustomTeleportLocationsFilePath());
	remove(StringToConstChar(ReturnCustomTeleportLocationsFilePath()));
	if (JsonHandle.isMember(CustomTeleportLocationName)) { JsonHandle.removeMember(CustomTeleportLocationName); }
	std::fstream FileHandle(ReturnCustomTeleportLocationsFilePath(), std::ios_base::out);
	FileHandle << JsonHandle;
	FileHandle.close();
}