#include "../Header/Cheat Functions/FiberMain.h"

bool Cheat::CheatFunctions::NewerCheatVersionAvailable = false;
std::string Cheat::CheatFunctions::NewCheatVersionString;
bool Cheat::CheatFunctions::LoadConfigThreadFunctionCompleted = false;
std::vector <std::string> Cheat::CheatFunctions::LoadedOptionsVector;

void Cheat::CheatFunctions::CreateNewDirectory(std::string Path)
{
	if (!std::filesystem::create_directory(Path))
	{
		std::string String = __func__ + (std::string)"() Failed to create directory '" + Path + "' Error: " + Cheat::CheatFunctions::GetLastErrorAsString();
		Cheat::LogFunctions::DebugMessage(String);
	}
	else
	{
		std::string String = __func__ + (std::string)"() Created directory '" + Path + "'";
		Cheat::LogFunctions::DebugMessage(String);
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
	return std::filesystem::path(CheatModuleFilePath).parent_path().string();
}

const std::string Cheat::CheatFunctions::ReturnConfigFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Config.ini";
}

const std::string Cheat::CheatFunctions::ReturnMainLogFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs\\Main.log";
}

const std::string Cheat::CheatFunctions::ReturnChatLogFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs\\Chats.log";
}

const std::string Cheat::CheatFunctions::ReturnCustomTeleportLocationsFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\CustomTeleportLocations.json";
}

const std::string Cheat::CheatFunctions::ReturnThemeFilePath(std::string ThemeName)
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + ThemeName + ".ini";
}

std::string Cheat::CheatFunctions::ReturnTextureFilePath()
{
	return ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Textures.ytd";
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
	// Player ID & Player Ped ID
	GameFunctions::PlayerID = PLAYER::PLAYER_ID();
	GameFunctions::PlayerPedID = PLAYER::PLAYER_PED_ID();

	// Features
	CheatFeatures::Looped();

	// Controls
	Controls::Loop();

	//Submenu handlers - additional submenu logic is looped here
	if (GUI::currentMenu == SelectedPlayerMenu ||
		GUI::currentMenu == SelectedPlayerFriendlyMenu ||
		GUI::currentMenu == SelectedPlayerRemoteOptions ||
		GUI::currentMenu == SelectedPlayerTeleportMenu ||
		GUI::currentMenu == SelectedPlayerAttachmentOptions ||
		GUI::currentMenu == SelectedPlayerTrollMenu ||
		GUI::currentMenu == SelectedPlayerRemoteOptions)
	{
		if (GameFunctions::IsPlayerIDValid(CheatFeatures::SelectedPlayer))
		{
			GameFunctions::ShowPlayerInformationBox(CheatFeatures::SelectedPlayer);
		}
		else
		{
			GUI::PreviousMenu = NOMENU;
			GUI::MoveMenu(MainMenu);
			GameFunctions::MinimapNotification("~r~Invalid Player ID");
		}
	}
	if (GUI::currentMenu == ThemeFilesMenu)
	{
		GUI::ThemeFilesVector.clear();
		std::string ThemeFolderPath = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(ThemeFolderPath)) { CheatFunctions::CreateNewDirectory(ThemeFolderPath); }
		for (const auto& file : std::filesystem::directory_iterator(ThemeFolderPath.c_str()))
		{
			if (file.path().extension() == ".ini")
			{
				GUI::ThemeFilesVector.push_back(file.path().stem().string());
			}
		}
	}

	// Cursor Navigation Handler
	if (CheatFeatures::CursorGUINavigationEnabled)
	{
		PLAYER::SET_PLAYER_CONTROL(GameFunctions::PlayerID, false, 0);
		UI::_SHOW_CURSOR_THIS_FRAME();
		UI::_SET_CURSOR_SPRITE(Normal);

		if (GameFunctions::IsCursorAtXYPosition({ GUI::guiX, GUI::guiY - 0.213f }, { GUI::guiWidth, 0.084f }))
		{
			UI::_SET_CURSOR_SPRITE(PreGrab);
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
			{
				UI::_SET_CURSOR_SPRITE(Grab);
				GUI::guiX = GameFunctions::ReturnCursorYXCoords().x;
				GUI::guiY = GameFunctions::ReturnCursorYXCoords().y + 0.20f;
			}
		}
		if (GameFunctions::IsCursorAtXYPosition({ GUI::SelectableInfoBoxX, GUI::SelectableInfoBoxY }, { 0.25f, 0.080f }))
		{
			UI::_SET_CURSOR_SPRITE(PreGrab);
			if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
			{
				UI::_SET_CURSOR_SPRITE(Grab);
				GUI::SelectableInfoBoxX = GameFunctions::ReturnCursorYXCoords().x;
				GUI::SelectableInfoBoxY = GameFunctions::ReturnCursorYXCoords().y;
			}
		}
		if (GameFunctions::IsCursorAtXYPosition({ GUI::guiX - 0.100f, GUI::guiY - 0.156f }, { 0.060f, 0.025f }))
		{
			UI::_SET_CURSOR_SPRITE(PreGrab);
			if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_ACCEPT))
			{
				GUI::BackMenu();
			}
		}
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_UP))
		{
			if (GUI::currentOption > 1)
			{
				GUI::currentOption -= 1;
			}
			Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
		}
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN))
		{
			if (GUI::TotalOptionsCount > GUI::currentOption)
			{
				GUI::currentOption += 1;
			}
			Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
		}
	}
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

void Cheat::CheatFunctions::SaveOption(std::string OptionName, std::string OptionValue, bool IsSavable)
{
	GUI::CurrentOptionIsSavable = IsSavable;
	if (IsKeyCurrentlyPressed(Controls::SaveSelectableKey))
	{
		if (IsSavable)
		{
			std::string LogMessage = "'" + OptionName + "' saved";
			Cheat::GameFunctions::AdvancedMinimapNotification(StringToChar(LogMessage), "Textures", "AdvancedNotificationImage", false, 4, "Config", "", 0.5f, "");
			IniFileWriteString(OptionValue, ReturnConfigFilePath(), "SETTINGS", OptionName);
		}
	}
}

std::string Cheat::CheatFunctions::GetOptionValueFromConfig(std::string OptionName)
{
	return IniFileReturnKeyValueAsString(ReturnConfigFilePath(), "SETTINGS", OptionName);
}

void LoadConfigThreadFunction()
{
	Cheat::Controls::ChangeControlsState(false);
	Cheat::GUI::HideGUIElements = true;
	for (int SubMenuInt = MainMenu; SubMenuInt != SUBMENUS_END; SubMenuInt++)
	{
		Cheat::GUI::MoveMenu(static_cast<SubMenus>(SubMenuInt));
		Sleep(150);
	}
	Cheat::GUI::CloseMenuGUI();
	Cheat::GUI::PreviousMenu = NOMENU;
	Cheat::Controls::ChangeControlsState(true);
	Cheat::GUI::HideGUIElements = false;
	Cheat::CheatFunctions::LoadConfigThreadFunctionCompleted = true;
}

void Cheat::CheatFunctions::LoadConfig()
{
	Cheat::LogFunctions::Message("Loading Configuration");
	std::thread LoadConfigThreadHandle(LoadConfigThreadFunction);
	LoadConfigThreadHandle.detach();

	//Load keys
	std::string MenuGUIKey = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Menu GUI Key");
	if (!MenuGUIKey.empty()) { Controls::OpenGUIKey = StringToInt(MenuGUIKey); }
	
	std::string CursorNavigationKey = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Cursor Navigation Key");
	if (!CursorNavigationKey.empty()) { Controls::OpenGUIKey = StringToInt(CursorNavigationKey); }

	std::string SaveSelectableKey = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Save Selectable Key");
	if (!SaveSelectableKey.empty()) { Controls::OpenGUIKey = StringToInt(SaveSelectableKey); }

	//Load Active Theme
	std::string ActiveThemeSetting = CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Active Theme");
	if (!ActiveThemeSetting.empty()) { GUI::LoadTheme(ActiveThemeSetting, true); }
}

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

void Cheat::CheatFunctions::CreateConsole()
{
	AllocConsole();
	SetConsoleTitleA("GTAV Cheat Console");

	// Set Console Dimensions so all text is properly visible
	HWND ConsoleWindowHandle = GetConsoleWindow();
	RECT CurrentRect;
	GetWindowRect(ConsoleWindowHandle, &CurrentRect);
	MoveWindow(ConsoleWindowHandle, CurrentRect.left, CurrentRect.top, 1100, 500, TRUE);

	//Set Max Window Size
	SetWindowLong(ConsoleWindowHandle, GWL_STYLE, GetWindowLong(ConsoleWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

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

bool Cheat::CheatFunctions::IsKeyCurrentlyPressed(int vKey, bool PressedOnce)
{
	if (IsGameWindowFocussed() && !Controls::ControlsDisabled)
	{
		if (PressedOnce)
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

void Cheat::CheatFunctions::WriteToFile(std::string FilePath, std::string text, std::ios_base::openmode FileOpenMode)
{
	std::ofstream FileHandle;
	FileHandle.open(FilePath, FileOpenMode);
	FileHandle << text;
	FileHandle.close();
}

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out)
{
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}

Json::Value Cheat::CheatFunctions::ReturnOnlineJsonCppDataObject(std::string URL)
{
	int httpCode;
	CURL* CurlHandle;
	std::string HttpData;
	CURLcode res;
	CurlHandle = curl_easy_init();
	if (CurlHandle)
	{
		curl_easy_setopt(CurlHandle, CURLOPT_URL, StringToChar(URL));
		curl_easy_setopt(CurlHandle, CURLOPT_USERAGENT, "request");
		curl_easy_setopt(CurlHandle, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(CurlHandle, CURLOPT_WRITEFUNCTION, callback);
		curl_easy_setopt(CurlHandle, CURLOPT_WRITEDATA, &HttpData);
		res = curl_easy_perform(CurlHandle);
		curl_easy_getinfo(CurlHandle, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(CurlHandle);
	}

	if (httpCode != CURLE_HTTP_RETURNED_ERROR && res == CURLE_OK)
	{
		Json::CharReaderBuilder CharBuilder;
		Json::Value JsonData;
		JSONCPP_STRING JsonError;
		const std::unique_ptr<Json::CharReader> reader(CharBuilder.newCharReader());

		if (reader->parse(StringToConstChar(HttpData), StringToConstChar(HttpData) + HttpData.length(), &JsonData, &JsonError))
		{
			return JsonData;
		}
		else
		{
			Cheat::LogFunctions::DebugMessage(__func__ + (std::string)"() : failed to parse json data. Error message returned by JsonCPP: " + JsonError);
		}
	}
	else
	{
		Cheat::LogFunctions::DebugMessage(__func__ + (std::string)"() : request failed, received the following HTTP status code: " + std::to_string(httpCode));
	}
	return Json::Value();
}

std::string Cheat::CheatFunctions::ReturnLatestCheatBuildNumber()
{
	auto JsonData = ReturnOnlineJsonCppDataObject("https://api.github.com/repos/HatchesPls/GrandTheftAutoV-Cheat/releases/latest");
	return JsonData["name"].asString();
}

void Cheat::CheatFunctions::CheckCheatUpdate()
{
	Cheat::LogFunctions::Message("Checking for newer cheat version");
	std::string CurrentLocalVersionString = RemoveCharactersFromStringAndReturn(CHEAT_BUILD_NUMBER, ".");
	std::string LatestOnlineVersionString = RemoveCharactersFromStringAndReturn(ReturnLatestCheatBuildNumber(), "v.");

	if (StringIsInteger(CurrentLocalVersionString) && StringIsInteger(LatestOnlineVersionString))
	{
		int CurrentLocalVersion = StringToInt(CurrentLocalVersionString);
		int LatestOnlineVersion = StringToInt(LatestOnlineVersionString);

		if (CurrentLocalVersion < LatestOnlineVersion)
		{
			NewerCheatVersionAvailable = true;
			NewCheatVersionString = "v" + LatestOnlineVersionString;
			LogFunctions::DebugMessage("A newer version of the cheat is available on Github");
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
	if (GlobalPtrn != NULL) { memcpy(GlobalPtrn, String.c_str(), String.size() + 1); }
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

	Vector3 LocalPlayerCoords = ENTITY::GET_ENTITY_COORDS(GameFunctions::PlayerPedID, true);
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