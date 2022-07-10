#pragma once

namespace Cheat
{
	namespace CheatFunctions
	{
		extern bool SendThreadTerminateSignal;
		extern std::string NewCheatVersionString;
		extern bool LoadConfigThreadFunctionCompleted;
		extern std::vector <std::string> LoadedSelectablesVector;
		const std::string ReturnConfigFilePath();
		const std::string ReturnMainLogFilePath();
		const std::string ReturnChatLogFilePath();
		const std::string ReturnHUDColorsFilePath();
		const std::string ReturnCustomTeleportLocationsFilePath();
		const std::string ReturnThemeFilePath(std::string ThemeName);
		void LoadConfig();
		bool IsSelectableRegisteredAsLoaded(std::string OptionName);
		template<typename T> void LoadConfigOption(std::string OptionName, T& ReturnedVariable)
		{
			if (!CheatFunctions::IsSelectableRegisteredAsLoaded(OptionName))
			{
				std::string TypeName = typeid(ReturnedVariable).name();

				if (TypeName == "bool")
				{
					std::string ConfigFileValue = GetSelectableValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = CheatFunctions::StringToBool(CheatFunctions::GetSelectableValueFromConfig(OptionName));
						Cheat::Logger::DebugMessage("Loaded savable selectable (Boolean) '" + OptionName + "'");
					}
					LoadedSelectablesVector.push_back(OptionName);
				}
				else if (TypeName == "int")
				{
					std::string ConfigFileValue = GetSelectableValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = CheatFunctions::StringToInt(CheatFunctions::GetSelectableValueFromConfig(OptionName));
						Cheat::Logger::DebugMessage("Loaded savable selectable (Integer) '" + OptionName + "'");
					}
					LoadedSelectablesVector.push_back(OptionName);
				}
				else if (TypeName == "float")
				{
					std::string ConfigFileValue = GetSelectableValueFromConfig(OptionName);
					if (!ConfigFileValue.empty())
					{
						ReturnedVariable = std::stof(CheatFunctions::GetSelectableValueFromConfig(OptionName));
						Cheat::Logger::DebugMessage("Loaded savable selectable (Float) '" + OptionName + "'");
					}
					LoadedSelectablesVector.push_back(OptionName);
				}
			}
		}
		std::string ReturnCheatModuleDirectoryPath();
		void SaveSelectable(std::string OptionName, std::string OptionValue, bool IsSavable);
		std::string GetSelectableValueFromConfig(std::string OptionName);
		bool FileOrDirectoryExists(std::string Path);
		void CreateNewDirectory(std::string Path);
		void Loop();
		void NonLooped();
		bool IsGameWindowFocussed();
		bool StringIsInteger(std::string String);
		std::string ReturnTextureFilePath();
		int WaitForAndReturnPressedKey();
		char* StringToChar(std::string String);
		const char* StringToConstChar(std::string String);
		std::string VirtualKeyCodeToString(UCHAR virtualKey);
		int ReturnNumberOfDigitsInValue(double Number);
		void IniFileWriteString(std::string string, std::string FilePath, std::string Section, std::string Key);
		std::string IniFileReturnKeyValueAsString(std::string FilePath, std::string Section, std::string Key);
		void IniFileRemoveKey(std::string FilePath, std::string Section, std::string Key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		std::string ReturnDateTimeFormatAsString(const char* DateTimeFormat);
		bool StringToBool(std::string String);
		bool IsKeyCurrentlyPressed(int vKey, bool PressedOnce = false);
		void WriteToFile(std::string FilePath, std::string text, bool Append);
		Json::Value ReturnGithubAPIJsonDataCheat(std::string Build);
		std::string GetLatestCheatBuildNumber();
		void CheckCheatUpdate();
		std::string RemoveCharactersFromStringAndReturn(std::string String, char* CharactersToRemove);
		int StringToInt(std::string String);
		std::string TextWrap(std::string String, int Location);
		void CopyStringToClipboard(const std::string& String);
		Json::Value ReadJsonFileAndReturnDataObject(std::string FilePath);
		void AddCustomTeleportLocation(std::string CustomTeleportLocationName);
		void DeleteCustomTeleportLocation(std::string CustomTeleportLocationName);
	}
}