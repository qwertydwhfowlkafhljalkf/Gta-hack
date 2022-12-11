#include "../../src/cheat/fibermain.h"
#include "version.hpp"
#include "file_system.hpp"

bool Cheat::CheatFunctions::NewerCheatVersionAvailable = false;
bool Cheat::CheatFunctions::CheatInitEntirelyCompleted = false;									// Set when both CheatInitCompleted and ConfigLoaded are set
bool Cheat::CheatFunctions::CheatInitCompleted = false;											// Set when all initialization is completed (except for async tasks such as LoadConfig())
bool Cheat::CheatFunctions::ConfigLoaded = false;												// Set when the LoadConfig thread is completed
std::vector <std::string> Cheat::CheatFunctions::LoadedSelectablesVector;						// Used during the async LoadConfig process to determine which selectables have been loaded
bool Cheat::CheatFunctions::StopThreads = false;												// Used to stop all cheat threads during the unloading process

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

bool Cheat::CheatFunctions::IsGameWindowFocussed()
{
	if (FindWindowA("grcWindow", NULL) == GetForegroundWindow())
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
					Cheat::GameFunctions::MinimapNotification((char*)"Canceled Key Selection");
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
			Cheat::GameFunctions::AdvancedMinimapNotification(StringToChar(LogMessage), (char*)"Textures", (char*)"AdvancedNotificationImage", false, 4, (char*)"Config", (char*)"", 0.5f, (char*)"");
			Logger::LogMsg(LOGGER_DBG_MSG, "'%s' (%s submenu) selectable state saved", OptionName.c_str(), GUI::CurrentSubmenu.c_str());
			IniFileWriteString(OptionValue, file_system::paths::ConfigFile, "submenu_" + GUI::CurrentSubmenu, OptionName);
		}
	}
}

std::string Cheat::CheatFunctions::GetSelectableValueFromConfig(std::string OptionName)
{
	return IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_" + GUI::CurrentSubmenu, OptionName);
}

void LoadConfigThreadFunction()
{
	Cheat::Controls::KeyInputDisabled = true;
	Cheat::GUI::HideGUIElements = true;
	for (int FuncPointerIndex = 0; FuncPointerIndex < Cheat::GUI::Submenus::NumberOfSubmenus; ++FuncPointerIndex)
	{
		Cheat::GUI::MoveMenu((*Cheat::GUI::Submenus::FunctionPointers[FuncPointerIndex]));
		Sleep(150);
	}
	Cheat::GUI::CloseMenuGUI();
	Cheat::GUI::PreviousMenu = nullptr;
	Cheat::Controls::KeyInputDisabled = false;
	Cheat::GUI::HideGUIElements = false;
	Cheat::CheatFunctions::LoadedSelectablesVector.clear();
	Cheat::CheatFunctions::ConfigLoaded = true;
}

void Cheat::CheatFunctions::LoadConfig()
{
	Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_INFO_MSG, "Loading Configuration");

	// Load hotkeys
	std::string MenuGUIKey = CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_settings", "Menu GUI Key");
	if (!MenuGUIKey.empty()) { Controls::OpenMenuGUIKey = StringToInt(MenuGUIKey); }
	
	std::string CursorNavigationKeyString = CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_settings", "Cursor Navigation Key");
	if (!CursorNavigationKeyString.empty()) { Controls::CursorNavigationKey = StringToInt(CursorNavigationKeyString); }

	std::string SaveSelectableKey = CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_settings", "Save Selectable Key");
	if (!SaveSelectableKey.empty()) { Controls::SaveSelectableKey = StringToInt(SaveSelectableKey); }

	// Load Active Theme
	std::string ActiveThemeSetting = CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_settings", "Active Theme");
	if (!ActiveThemeSetting.empty()) { GUI::LoadTheme(ActiveThemeSetting, true); }

	// Load Vehicle Spawner Custom License Plate Text
	std::string VehicleSpawnerCustomLicensePlateText = CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_vehicle spawn settings", "Custom License Plate Text");
	if (!VehicleSpawnerCustomLicensePlateText.empty()) { CheatFeatures::VehicleSpawnerCustomLicensePlateTextString = VehicleSpawnerCustomLicensePlateText; }

	// Do not overwrite "Textures.ytd" at init feature - setting must be loaded immediately (not async)
	CheatFeatures::NoTextureFileOverwrite = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(file_system::paths::ConfigFile, "submenu_settings", "do not overwrite \"textures.ytd\" at init"));

	std::thread LoadConfigThreadHandle(LoadConfigThreadFunction);
	LoadConfigThreadHandle.detach();
}

bool Cheat::CheatFunctions::IsSelectableRegisteredAsLoaded(std::string SelectableName)
{
	for (auto const& i : LoadedSelectablesVector)
	{
		if (i == SelectableName)
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
			if (GetAsyncKeyState(vKey) & 0x01)
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
	auto Modes = std::ofstream::out;
	auto ModesAppend = Modes + std::ofstream::app;
	std::ofstream FileHandle;
	FileHandle.open(FilePath, Append ? ModesAppend : Modes);
	FileHandle << text;
	FileHandle.close();
}

int Cheat::CheatFunctions::GetLatestCheatBuildNumber()
{
	std::string VersionString;
	int VersionInt = NULL;
	std::wstring URL = L"https://api.github.com/repos/HatchesPls/GrandTheftAutoV-Cheat/releases/latest";
	HINTERNET hopen = InternetOpen(L"GTAVCheat", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	if (hopen)
	{
		HINTERNET hinternet = InternetOpenUrl(hopen, URL.c_str(), NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_SECURE, NULL);
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
				VersionString = JsonData["name"].asString();
				RemoveChars(VersionString, "v.");
				try
				{
					VersionInt = std::stoi(VersionString);
				}
				catch (...) { }
			}
			else
			{
				Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "GetLatestCheatBuildNumber() : failed to parse JSON data. Error: %s", JsonError);
				return NULL;
			}
			InternetCloseHandle(hinternet);
		}
		InternetCloseHandle(hopen);
	}
	return VersionInt;
}

// Removes specified characters from the supplied string by reference
void Cheat::CheatFunctions::RemoveChars(std::string &String, const char* CharactersToRemove)
{
	for (unsigned int i = 0; i < strlen(CharactersToRemove); ++i)
	{
		String.erase(remove(String.begin(), String.end(), CharactersToRemove[i]), String.end());
	}
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
	if (GlobalPtrn != NULL)
	{
		memcpy(GlobalPtrn, String.c_str(), String.size() + 1);
	}
	GlobalUnlock(Global);
	SetClipboardData(CF_TEXT, Global);
	CloseClipboard();
	GlobalFree(Global);
}

bool Cheat::CheatFunctions::GetJsonFromFile(std::string Path, Json::Value& Object)
{
	Json::Value JsonObject;
	std::fstream FileHandle(Path, std::ifstream::in);
	if (std::filesystem::exists(Path))
	{
		try
		{
			FileHandle >> JsonObject;
		}
		catch (...)
		{
			FileHandle.close();
			return false;
		}
	}
	Object = JsonObject;
	FileHandle.close();
	return true;
}

bool Cheat::CheatFunctions::AddCustomTeleportLocation(std::string CustomTeleportLocationName)
{
	// Create the JsonCPP Value variable
	Json::Value JsonData;

	// Only procceed if getting the JSON data succeeds and 'CustomTeleportLocationName' is in the JSON data
	if (GetJsonFromFile(file_system::paths::CusTelLocFile, JsonData))
	{
		// Remove the member if it already exists
		if (JsonData.isMember(CustomTeleportLocationName))
		{
			JsonData.removeMember(CustomTeleportLocationName);
		}

		// Get local player coordinates
		Vector3 LocalPlayerCoords = ENTITY::GET_ENTITY_COORDS(GameFunctions::PlayerPedID, false);
		JsonData[CustomTeleportLocationName]["X"] = LocalPlayerCoords.x;
		JsonData[CustomTeleportLocationName]["Y"] = LocalPlayerCoords.y;
		JsonData[CustomTeleportLocationName]["Z"] = LocalPlayerCoords.z;

		// Rewrite the JSON file
		std::fstream FileHandle(file_system::paths::CusTelLocFile, std::ios_base::out);
		FileHandle << JsonData;
		FileHandle.close();
		return true;
	}

	// Return false in case of any preceding failure(s)
	return false;
}

bool Cheat::CheatFunctions::DeleteCustomTeleportLocation(std::string CustomTeleportLocationName)
{
	// Create the JsonCPP Value variable
	Json::Value JsonData;

	// Only procceed if getting the JSON data succeeds and 'CustomTeleportLocationName' is in the JSON data
	if (GetJsonFromFile(file_system::paths::CusTelLocFile, JsonData) && JsonData.isMember(CustomTeleportLocationName))
	{
		// Remove the specified member from the JSON data
		JsonData.removeMember(CustomTeleportLocationName);

		// Rewrite the JSON file
		std::fstream FileHandle(file_system::paths::CusTelLocFile, std::ios_base::out);
		FileHandle << JsonData;
		FileHandle.close();
		return true;
	}

	// Return false in case of any preceding failure(s)
	return false;
}

DWORD WINAPI UnloadThread(LPVOID lpParam)
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();

	Cheat::CheatFunctions::StopThreads = true;

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
}

void Cheat::CheatFunctions::UnloadCheat()
{
	CreateThread(NULL, NULL, UnloadThread, NULL, NULL, NULL);
}

void Cheat::CheatFunctions::LoadSelectableSaveStateBool(std::string SelectableName, bool& ReturnedBool)
{
	if (!CheatFunctions::IsSelectableRegisteredAsLoaded(SelectableName))
	{
		std::string ConfigFileValue = GetSelectableValueFromConfig(SelectableName);
		if (!ConfigFileValue.empty())
		{
			ReturnedBool = CheatFunctions::StringToBool(ConfigFileValue);
			Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Loaded savable selectable (Boolean) '%s'", SelectableName.c_str());
			LoadedSelectablesVector.push_back(SelectableName);
		}
	}
}

void Cheat::CheatFunctions::LoadSelectableSaveStateInt(std::string SelectableName, int& ReturnedInt)
{
	if (!CheatFunctions::IsSelectableRegisteredAsLoaded(SelectableName))
	{
		std::string ConfigFileValue = GetSelectableValueFromConfig(SelectableName);
		if (!ConfigFileValue.empty())
		{
			ReturnedInt = CheatFunctions::StringToInt(ConfigFileValue);
			Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Loaded savable selectable (Integer) '%s'", SelectableName.c_str());
			LoadedSelectablesVector.push_back(SelectableName);
		}	
	}
}

void Cheat::CheatFunctions::LoadSelectableSaveStateFloat(std::string SelectableName, float& ReturnedFloat)
{
	if (!CheatFunctions::IsSelectableRegisteredAsLoaded(SelectableName))
	{
		std::string ConfigFileValue = GetSelectableValueFromConfig(SelectableName);
		if (!ConfigFileValue.empty())
		{
			ReturnedFloat = std::stof(ConfigFileValue);
			Cheat::Logger::LogMsg(LoggerMsgTypes::LOGGER_DBG_MSG, "Loaded savable selectable (Float) '%s'", SelectableName.c_str());
			LoadedSelectablesVector.push_back(SelectableName);
		}
	}
}