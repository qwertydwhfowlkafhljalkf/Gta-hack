#include "../Header/Cheat Functions/FiberMain.h"
#include "../../ThirdParty/color-console/color.hpp"
//#include <syncstream> // Used for std::osyncstream

bool Cheat::Logger::LoggerInitialized = false;

void Cheat::Logger::Init()
{
    if (!AllocConsole() || !freopen("CONIN$", "r", stdin) || !freopen("CONOUT$", "w", stdout) ||
        !freopen("CONOUT$", "w", stderr) || !SetConsoleTitleA("GTAV Cheat") || SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS))
    {
        Logger::LogMsg(LOGGER_FATAL_MSG, "Failed to allocate console - %i", GetLastError());
    }

    std::string MessageString = "\nVersion: " + (std::string)CHEAT_BUILD_NUMBER + " | Compile Date & Time: " + __DATE__ + " " + __TIME__ +
        Cheat::CheatFunctions::ReturnDateTimeFormatAsString(" | Load Date & Time: %b %e %Y %H:%M:%S")
        + "\nGitHub Repository: HatchesPls/GrandTheftAutoV-Cheat\n";
    std::cout << "Version: " << CHEAT_BUILD_NUMBER << std::endl;

    // Write text
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);

    LoggerInitialized = true;
}

// NOTE: this function is NOT thread-safe at the moment - TODO
const std::vector<std::string> LogMsgTypeStrings = { " [INFO] ", " [WARN] ", " [ERR] ", " [FATAL] ", " [DBG] " };
void Cheat::Logger::LogMsg(LoggerMsgTypes Type, const char* Message, ...)
{
    if (LoggerInitialized)
    {
        std::string Time = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]");
        if (Type == LoggerMsgTypes::LOGGER_INFO_MSG)
        {
            //std::osyncstream(std::cout) << Time << dye::green(LogMsgTypeStrings[0]) << Message << std::endl;
            va_list args;
            va_start(args, Message);
            char buf[1024];
            vsnprintf_s(buf, sizeof(buf), Message, args);
            va_end(args);
            std::cout << Time << dye::green(LogMsgTypeStrings[0]) << buf << std::endl;
            CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), Time + LogMsgTypeStrings[0] + Message, true);
        }
        else if (Type == LoggerMsgTypes::LOGGER_WARNING_MSG)
        {
            va_list args;
            va_start(args, Message);
            char buf[1024];
            vsnprintf_s(buf, sizeof(buf), Message, args);
            va_end(args);
            std::cout << Time << dye::yellow(LogMsgTypeStrings[1]) << buf << std::endl;
            CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), Time + LogMsgTypeStrings[1] + Message, true);
        }
        else if (Type == LoggerMsgTypes::LOGGER_ERROR_MSG)
        {
            va_list args;
            va_start(args, Message);
            char buf[1024];
            vsnprintf_s(buf, sizeof(buf), Message, args);
            va_end(args);
            std::cout << Time << dye::red(LogMsgTypeStrings[2]) << buf << std::endl;
            CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), Time + LogMsgTypeStrings[2] + Message, true);
        }
        else if (Type == LoggerMsgTypes::LOGGER_FATAL_MSG)
        {
            va_list args;
            va_start(args, Message);
            char buf[1024];
            vsnprintf_s(buf, sizeof(buf), Message, args);
            va_end(args);
            std::cout << Time << dye::red(LogMsgTypeStrings[3]) << buf << std::endl;
            CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), Time + LogMsgTypeStrings[3] + Message, true);
            if (MessageBoxA(NULL, buf, "GTAV Cheat", MB_ICONSTOP | MB_OK | MB_SETFOREGROUND | MB_APPLMODAL) == IDOK)
            {
                std::exit(EXIT_FAILURE);
            }
        }
        else if (Type == LoggerMsgTypes::LOGGER_DBG_MSG)
        {
            va_list args;
            va_start(args, Message);
            char buf[1024];
            vsnprintf_s(buf, sizeof(buf), Message, args);
            va_end(args);
            std::cout << Time << dye::grey(LogMsgTypeStrings[4] + buf) << std::endl;
            CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), Time + LogMsgTypeStrings[4] + Message, true);
        }
    }
}