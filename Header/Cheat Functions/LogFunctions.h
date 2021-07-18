#pragma once

namespace Cheat
{
	namespace LogFunctions
	{
		void Init();
		void Message(char* Message);
		void MessageCustomCategory(std::string CategoryName, std::string Message);
		void Error(char* Message, bool ShowMessageBox);
		void DebugMessage(std::string Message);
	}
}