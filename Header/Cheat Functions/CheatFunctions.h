#pragma once

namespace Cheat
{
	namespace CheatFunctions
	{
		extern bool NewerCheatVersionAvailable;
		extern std::string NewCheatVersionString;
		extern bool LoadConfigThreadFunctionCompleted;
		extern std::vector <std::string> LoadedOptionsVector;
		const std::string ReturnConfigFilePath();
		const std::string ReturnMainLogFilePath();
		const std::string ReturnChatLogFilePath();
		const std::string ReturnCustomTeleportLocationsFilePath();
		const std::string ReturnThemeFilePath(std::string ThemeName);
		void LoadConfig();
		bool IsOptionRegisteredAsLoaded(std::string OptionName);
		template<typename T> void LoadConfigOption(std::string OptionName, T& ReturnedVariable)
		{
			if (!CheatFunctions::IsOptionRegisteredAsLoaded(OptionName))
			{
				std::string TypeName = typeid(ReturnedVariable).name();

				if (TypeName == "bool")
				{
					std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = CheatFunctions::StringToBool(CheatFunctions::GetOptionValueFromConfig(OptionName));
						Cheat::LogFunctions::DebugMessage("Loaded savable option (Boolean) '" + OptionName + "'");
					}
					LoadedOptionsVector.push_back(OptionName);
				}
				else if (TypeName == "int")
				{
					std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = CheatFunctions::StringToInt(CheatFunctions::GetOptionValueFromConfig(OptionName));
						Cheat::LogFunctions::DebugMessage("Loaded savable option (Integer) '" + OptionName + "'");
					}
					LoadedOptionsVector.push_back(OptionName);
				}
				else if (TypeName == "float")
				{
					std::string ConfigFileValue = GetOptionValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = std::stof(CheatFunctions::GetOptionValueFromConfig(OptionName));
						Cheat::LogFunctions::DebugMessage("Loaded savable option (Float) '" + OptionName + "'");
					}
					LoadedOptionsVector.push_back(OptionName);
				}
			}
		}
		std::string ReturnCheatModuleDirectoryPath();
		void SaveOption(std::string OptionName, std::string OptionValue, bool IsSavable);
		std::string GetOptionValueFromConfig(std::string OptionName);
		bool FileOrDirectoryExists(std::string Path);
		void CreateNewDirectory(std::string Path);
		std::string GetLastErrorAsString();
		void LoopedFunctions();
		bool IsGameWindowFocussed();
		bool StringIsInteger(const std::string& s);
		bool IsIntegerInRange(unsigned low, unsigned high, unsigned x);
		std::string TextureFilePath();
		int WaitForAndReturnPressedKey();
		char* StringToChar(std::string string);
		std::string VirtualKeyCodeToString(UCHAR virtualKey);
		void CreateConsole();
		int ReturnNumberOfDigitsInValue(double Number);
		void IniFileWriteString(std::string string, std::string FilePath, std::string Section, std::string Key);
		std::string IniFileReturnKeyValueAsString(std::string FilePath, std::string Section, std::string Key);
		void IniFileRemoveKey(std::string FilePath, std::string Section, std::string Key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		std::string ReturnDateTimeFormatAsString(const char* DateTimeFormat);
		bool StringToBool(std::string String);
		bool IsKeyCurrentlyPressed(int vKey, bool PressedOnce = false);
		void WriteToFile(std::string FilePath, std::string text, std::ios_base::openmode FileOpenMode);
		Json::Value ReturnOnlineJsonCppDataObject(std::string URL);
		std::string ReturnLatestCheatBuildNumber();
		void CheckCheatUpdate();
		std::string RemoveCharactersFromStringAndReturn(std::string String, char* CharactersToRemove);
		int StringToInt(std::string String);
		std::string TextWrap(std::string String, int Location);
		void CopyStringToClipboard(const std::string& String);
		Json::Value ReadJsonFileAndReturnDataObject(std::string FilePath);
		void AddCustomTeleportLocation(std::string CustomTeleportLocationName);
		void DeleteCustomTeleportLocation(std::string CustomTeleportLocationName);
		DWORD WINAPI MenuSelectableAnimationThread(LPVOID lpParam);
	}
}