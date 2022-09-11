#include "../Header/Cheat Functions/FiberMain.h"

bool Cheat::Logger::LoggerInitialized = false;

HANDLE Console;
void Cheat::Logger::Init()
{
    if (!AllocConsole() || !freopen("CONIN$", "r", stdin) || !freopen("CONOUT$", "w", stdout) ||
        !freopen("CONOUT$", "w", stderr) || !SetConsoleTitleA("GTAV Cheat"))
    {
        Logger::Error("Failed to allocate console", true);
    }
    Console = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string MessageString = "Build: " + (std::string)CHEAT_BUILD_NUMBER + " | Compile Date & Time: " + __DATE__ + " " + __TIME__ +
        Cheat::CheatFunctions::ReturnDateTimeFormatAsString(" | Load Date & Time: %b %e %Y %H:%M:%S")
        + "\nGitHub Repository: HatchesPls/GrandTheftAutoV-Cheat\n";
    std::cout << "Build: " << CHEAT_BUILD_NUMBER << std::endl;

    // Write spacing to logfile
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n", true);

    // Write text
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);

    LoggerInitialized = true;
}

enum class LoggerMsgTypes {
    LOGGER_INFO_MSG,
    LOGGER_WARNING_MSG,
    LOGER_ERROR_MSG,
    LOGGER_FATAL_MSG,
    LOGGER_DBG_MSG
};

void Cheat::Logger::Message(std::string Message)
{
    if (LoggerInitialized)
    {
        std::cout << CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]");
        SetConsoleTextAttribute(Console, FOREGROUND_GREEN);
        std::cout << " [INFO] ";
        SetConsoleTextAttribute(Console, 7);
        std::cout << Message << std::endl;
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] [INFO] ") + Message, true);
    }
}

void Cheat::Logger::MessageCustomCategory(std::string CategoryName, std::string Message)
{
    if (LoggerInitialized)
    {
        std::string MessageString = " [" + CategoryName + "] " + Message + "\n";
        std::cout << MessageString;
    }
}

void Cheat::Logger::DebugMessage(std::string Message)
{
    if (LoggerInitialized)
    {
        std::string MessageString = "[DBG] " + Message + "\n";
        std::cout << MessageString;
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] ") + MessageString, true);
    }
}

void Cheat::Logger::Error(char* Message, bool ShowMessageBox)
{
    if (LoggerInitialized)
    {
        std::string MessageString = "[ERR] " + (std::string)Message + "\n";
        std::cout << MessageString;
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] ") + MessageString, true);

        if (ShowMessageBox)
        {
            MessageBoxA(NULL, Message, "GTAV Cheat Error", MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
        }
    }
}

void Cheat::Logger::SendMessageToGameChatLogWindow(std::string Message)
{
    std::cout << "[Game Chat]:" << Message;
}