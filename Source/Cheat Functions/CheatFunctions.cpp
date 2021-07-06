#include "../Header/stdafx.h"


void Cheat::CheatFunctions::CreateNewDirectory(std::string Path)
{
	if (!std::filesystem::create_directory(Path))
	{
		std::string String = "Failed to create directory '" + Path + "' Error: " + Cheat::CheatFunctions::GetLastErrorAsString();
		Cheat::LogFunctions::DebugMessage(CheatFunctions::StringToChar(String));
	}
	else
	{
		std::string String = "Created directory '" + Path + "'";
		Cheat::LogFunctions::DebugMessage((CheatFunctions::StringToChar(String)));
	}
}

//See https://en.cppreference.com/w/cpp/io/manip/put_time
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
	return std::filesystem::path{ CheatModuleFilePath }.parent_path().string();
}

const std::string Cheat::CheatFunctions::ReturnConfigFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Config.ini";
}

bool Cheat::CheatFunctions::FileOrDirectoryExists(std::string Path)
{
	if (std::filesystem::exists(Path))
	{
		return true;
	}
	return false;
}

std::string Cheat::CheatFunctions::GetLastErrorAsString()
{
	DWORD errorMessageID = GetLastError();
	if (errorMessageID == 0) { return std::string(); }

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				  NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)& messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);
	return message;
}


Player Cheat::GameFunctions::PlayerID;
Ped Cheat::GameFunctions::PlayerPedID;
void Cheat::CheatFunctions::LoopedFunctions()
{
	//Player ID and Player Ped ID
	Cheat::GameFunctions::PlayerID = PLAYER::PLAYER_ID();
	Cheat::GameFunctions::PlayerPedID = PLAYER::PLAYER_PED_ID();

	//Features
	Cheat::CheatFeatures::Looped();

	//Controls
	Cheat::GUI::ControlsLoop();

	//Submenu handlers - additional submenu logic is looped here
	if (Cheat::GUI::currentMenu == SelectedPlayerMenu ||
		Cheat::GUI::currentMenu == SelectedPlayerFriendlyMenu ||
		Cheat::GUI::currentMenu == SelectedPlayerRemoteOptions ||
		Cheat::GUI::currentMenu == SelectedPlayerTeleportMenu ||
		Cheat::GUI::currentMenu == SelectedPlayerMoneyMenu ||
		Cheat::GUI::currentMenu == SelectedPlayerAttachmentOptions ||
		Cheat::GUI::currentMenu == SelectedPlayerTrollMenu ||
		Cheat::GUI::currentMenu == SelectedPlayerRemoteOptions)
	{
		if (Cheat::GameFunctions::IsPlayerIDValid(Cheat::CheatFeatures::selectedPlayer))
		{
			Cheat::GameFunctions::ShowPlayerInformationBox(Cheat::CheatFeatures::selectedPlayer);
		}
		else
		{
			Cheat::GUI::PreviousMenu = NOMENU;
			Cheat::GUI::MoveMenu(MainMenu);
			Cheat::GameFunctions::MinimapNotification("~r~Invalid Player ID");
		}
	}
}

bool Cheat::CheatFunctions::IsGameWindowFocussed()
{
	if (FindWindowA("grcWindow", "Grand Theft Auto V") == GetForegroundWindow())
	{ 
		return true; 
	} 
	else 
	{ 
		return false; 
	}
}

bool Cheat::CheatFunctions::StringIsInteger(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Cheat::CheatFunctions::IsIntegerInRange(unsigned low, unsigned high, unsigned x)
{
	return  ((x - low) <= (high - low));
}

std::string Cheat::CheatFunctions::TextureFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Textures.ytd";
}

int Cheat::CheatFunctions::WaitForAndReturnPressedKey()
{
	while (true)
	{
		Cheat::GUI::Drawing::Text("~bold~Press any key, press Escape to cancel", { 255, 255, 255, 255 }, { 0.525f, 0.400f }, { 0.900f, 0.900f }, true); GameHooking::PauseMainFiber(0, false);
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

void Cheat::CheatFunctions::SaveOption(std::string OptionName, std::string OptionValue, bool IsSavable)
{
	if (IsSavable) 
	{
		GUI::CurrentOptionIsSavable = true;
	}
	else 
	{
		GUI::CurrentOptionIsSavable = false;
	}

	if (IsKeyCurrentlyPressed(GUI::SaveItemKey))
	{
		if (IsSavable)
		{
			std::string LogMessage = "'" + OptionName + "' saved";
			Cheat::GameFunctions::AdvancedMinimapNotification(CheatFunctions::StringToChar(LogMessage), "Textures", "AdvancedNotificationImage", false, 4, "Config", "", 0.5f, "");
			IniFileWriteString(OptionValue, ReturnConfigFilePath(), "SETTINGS", OptionName);
		}
	}
}

std::string Cheat::CheatFunctions::GetOptionValueFromConfig(std::string OptionName)
{
	return IniFileReturnKeyValueAsString(ReturnConfigFilePath(), "SETTINGS", OptionName);
}

void LoadSettingsThreadFunction()
{
	Cheat::GUI::ChangeControlsState(false);
	Cheat::GUI::HideGUIElements = true;
	for (int SubMenuInt = MainMenu; SubMenuInt != SUBMENUS_END; SubMenuInt++)
	{
		Cheat::GUI::MoveMenu(static_cast<SubMenus>(SubMenuInt));
		Sleep(100);
	}
	Cheat::GUI::CloseGUI();
	Cheat::GUI::PreviousMenu = NOMENU;
	Cheat::GUI::CheatGUIHasBeenOpened = false;
	Cheat::GUI::ChangeControlsState(true);
	Cheat::GUI::HideGUIElements = false;
}

void Cheat::CheatFunctions::LoadConfig()
{
	Cheat::LogFunctions::Message("Loading Config");
	std::thread LoadSettingsThreadHandle(LoadSettingsThreadFunction);
	LoadSettingsThreadHandle.detach();

	//Load Active Theme Name
	std::string ActiveThemeSetting = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(Cheat::CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "active_theme");
	if (ActiveThemeSetting != "NOT_FOUND") { Cheat::GUI::LoadTheme(CheatFunctions::StringToChar(ActiveThemeSetting), true); }
}

std::vector <std::string> LoadedOptionsVector;
bool Cheat::CheatFunctions::IsOptionRegisteredAsLoaded(std::string OptionName)
{
	for (auto const& i : LoadedOptionsVector)
	{
		if (i == OptionName)
		{
			return true;
		}
	}
	return false;
}

/*
Description: loads the specified configuration option
Note(s): Data is read from config.ini
		 Function overloading is used for each data type (boolean, integer & float)
*/

//Bool
void Cheat::CheatFunctions::LoadConfigOption(std::string OptionName, bool& ReturnedBool)
{
	if (!CheatFunctions::IsOptionRegisteredAsLoaded(OptionName))
	{
		try
		{
			std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
			if (ConfigFileValue != "NOT_FOUND")
			{
				ReturnedBool = CheatFunctions::StringToBool(CheatFunctions::GetOptionValueFromConfig(OptionName));
				Cheat::LogFunctions::DebugMessage("Loaded savable option (Boolean) '" + OptionName + "'");
			}
			LoadedOptionsVector.push_back(OptionName);
		}
		catch (...)
		{
			Cheat::LogFunctions::DebugMessage("Failed to load savable option (Boolean) '" + OptionName + "'");
		}
	}
}
//Integer
void Cheat::CheatFunctions::LoadConfigOption(std::string OptionName, int& ReturnedInt)
{
	if (!CheatFunctions::IsOptionRegisteredAsLoaded(OptionName))
	{
		try
		{
			std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
			if (ConfigFileValue != "NOT_FOUND")
			{
				ReturnedInt = std::stoi(CheatFunctions::GetOptionValueFromConfig(OptionName));
				Cheat::LogFunctions::DebugMessage("Loaded savable option (Integer) '" + OptionName + "'");
			}
			LoadedOptionsVector.push_back(OptionName);
		}
		catch (...)
		{
			Cheat::LogFunctions::DebugMessage("Failed to load savable option (Integer) '" + OptionName + "'");
		}
	}
}
//Float
void Cheat::CheatFunctions::LoadConfigOption(std::string OptionName, float& ReturnedFloat)
{
	if (!CheatFunctions::IsOptionRegisteredAsLoaded(OptionName))
	{
		try
		{
			std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
			if (ConfigFileValue != "NOT_FOUND")
			{
				ReturnedFloat = std::stof(CheatFunctions::GetOptionValueFromConfig(OptionName));
				Cheat::LogFunctions::DebugMessage("Loaded savable option (Float) '" + OptionName + "'");
			}
			LoadedOptionsVector.push_back(OptionName);
		}
		catch (...)
		{
			Cheat::LogFunctions::DebugMessage("Failed to load savable option (Float) '" + OptionName + "'");
		}
	}
}

char* Cheat::CheatFunctions::StringToChar(std::string string)
{
	return _strdup(string.c_str());
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

void Cheat::CheatFunctions::CreateConsole()
{
	AllocConsole();
	SetConsoleTitleA("GTAV Cheat Console");

	// Set Console Dimensions so all text is properly visible
	HWND ConsoleWindowHandle = GetConsoleWindow();
	RECT CurrentRect;
	GetWindowRect(ConsoleWindowHandle, &CurrentRect);
	MoveWindow(ConsoleWindowHandle, CurrentRect.left, CurrentRect.top, 1100, 500, TRUE);

	//Disable Close Button Console Window And Set Max Window Size
	SetWindowLong(ConsoleWindowHandle, GWL_STYLE, GetWindowLong(ConsoleWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	HMENU hMenu = GetSystemMenu(ConsoleWindowHandle, FALSE);
	if (hMenu != NULL) { DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND); }

	//Disable Console Quick Edit Mode
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (stdIn != INVALID_HANDLE_VALUE) 
	{
		DWORD dwMode = 0;
		if (GetConsoleMode(stdIn, &dwMode)) {
			dwMode &= ~ENABLE_QUICK_EDIT_MODE;
			SetConsoleMode(stdIn, dwMode | ENABLE_EXTENDED_FLAGS);
		}
	}
	CloseHandle(ConsoleWindowHandle);

	//Redirect Std Outputs to Console
	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE* COutputHandle = _fdopen(SystemOutput, "w");
	HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
	int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE* CErrorHandle = _fdopen(SystemError, "w");
	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE* CInputHandle = _fdopen(SystemInput, "r");
	std::ios::sync_with_stdio(true);
	freopen_s(&CInputHandle, "CONIN$", "r", stdin);
	freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
	freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	//Print build info
	std::cout << "Build: " << CHEAT_BUILD_NUMBER << " | Compile Date & Time: " << __DATE__ << " " << __TIME__ << std::endl;
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
	File.write(IniStruct);
}

/*
Description: returns the value for the provided initialization file section and key
Note(s):
*/
std::string Cheat::CheatFunctions::IniFileReturnKeyValueAsString(std::string FilePath, std::string Section, std::string Key)
{
	mINI::INIFile File(FilePath);
	mINI::INIStructure IniStruct;
	File.read(IniStruct);
	if (!IniStruct.has(Section) || !IniStruct[Section].has(Key)) { return "NOT_FOUND"; }
	return IniStruct.get(Section).get(Key);
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


bool Cheat::CheatFunctions::IsKeyCurrentlyPressed(int vKey, bool PressedOnce)
{
	if (Cheat::CheatFunctions::IsGameWindowFocussed() && !Cheat::GUI::ControlsDisabled)
	{
		if (PressedOnce)
		{
			if (GetAsyncKeyState(vKey) & 1)
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