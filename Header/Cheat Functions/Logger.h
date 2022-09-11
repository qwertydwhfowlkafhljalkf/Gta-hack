#pragma once

namespace Cheat
{
    namespace Logger
    {
        extern bool LoggerInitialized;
        void Init();
        void Message(std::string Message);
        void MessageCustomCategory(std::string CategoryName, std::string Message);
        void Error(char* Message, bool ShowMessageBox);
        void DebugMessage(std::string Message);
        void SendMessageToGameChatLogWindow(std::string Message);
    }
}