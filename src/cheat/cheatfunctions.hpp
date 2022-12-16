#pragma once
#include <iostream>
#include <vector>
#include <json/json.h>
#include <Windows.h>

namespace Cheat
{
	namespace CheatFunctions
	{
		extern bool StopThreads;
		extern bool NewerCheatVersionAvailable;
		extern bool CheatInitCompleted;
		extern bool CheatInitEntirelyCompleted;
		extern bool ConfigLoaded;
		extern std::vector <std::string> LoadedSelectablesVector;
		int StringToInt(std::string String);
		bool StringToBool(std::string String);
		void LoadConfig();
		void SaveSelectable(std::string OptionName, std::string OptionValue, bool IsSavable);
		std::string GetSelectableValueFromConfig(std::string OptionName);
		bool IsSelectableRegisteredAsLoaded(std::string SelectableName);
		void LoadSelectableSaveStateBool(std::string SelectableName, bool& ReturnedBool);
		void LoadSelectableSaveStateInt(std::string SelectableName, int& ReturnedInt);
		void LoadSelectableSaveStateFloat(std::string SelectableName, float& ReturnedFloat);
		std::string ReturnCheatModuleDirectoryPath();
		bool IsGameWindowFocussed();
		bool StringIsInteger(std::string String);
		int WaitForAndReturnPressedKey();
		char* StringToChar(std::string String);
		std::string VirtualKeyCodeToString(UCHAR virtualKey);
		int ReturnNumberOfDigitsInValue(double Number);
		void IniFileWriteString(std::string string, std::string FilePath, std::string Section, std::string Key);
		std::string IniFileReturnKeyValueAsString(std::string FilePath, std::string Section, std::string Key);
		void IniFileRemoveKey(std::string FilePath, std::string Section, std::string Key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		std::string ReturnDateTimeFormatAsString(const char* DateTimeFormat);
		bool IsKeyCurrentlyPressed(int vKey, bool RepeatInput = false);
		void WriteToFile(std::string FilePath, std::string text, bool Append);
		int GetLatestCheatBuildNumber();
		void RemoveChars(std::string &String, const char* CharactersToRemove);
		std::string TextWrap(std::string String, int Location);
		bool GetJsonFromFile(std::string Path, Json::Value& Object);
		bool AddCustomTeleportLocation(std::string CustomTeleportLocationName);
		bool DeleteCustomTeleportLocation(std::string CustomTeleportLocationName);
		void UnloadCheat();
	}
}