#pragma once

namespace Cheat
{
	namespace Logger
	{
		extern bool LoggerInitialized;
		extern bool WindowVisible;
		void Init();
		void Uninit();
		void Message(std::string Message);
		void MessageCustomCategory(std::string CategoryName, std::string Message);
		void Error(char* Message, bool ShowMessageBox);
		void DebugMessage(std::string Message);
		void Window();
	}
}