#include "../Header/Cheat Functions/FiberMain.h"

bool Cheat::Logger::LoggerInitialized = false;
bool Cheat::Logger::CheatWindowVisible = true;
bool Cheat::Logger::GameChatWindowVisible = false;

static LoggerStruct MainLoggerObject;
static LoggerStruct GameChatLoggerObject;

void Cheat::Logger::Init()
{
    std::string MessageString = "Build: " + (std::string)CHEAT_BUILD_NUMBER + " | Compile Date & Time: " + __DATE__ + " " + __TIME__ +
        Cheat::CheatFunctions::ReturnDateTimeFormatAsString(" | Load Date & Time: %b %e %Y %H:%M:%S")
        + "\nGitHub Repository: HatchesPls/GrandTheftAutoV-Cheat\n";
    MainLoggerObject.AddLog("Build: %s\n", CHEAT_BUILD_NUMBER);

    // Write spacing to logfile
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n\n\n", true);

    // Write text
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);

    LoggerInitialized = true;
}

void Cheat::Logger::Uninit()
{
    DebugMessage("Logger uninitialized");
    MainLoggerObject.Clear();
    GameChatLoggerObject.Clear();
    LoggerInitialized = false;
}

void Cheat::Logger::Message(std::string Message)
{
    if (LoggerInitialized)
    {
        std::string MessageString = "[INFO] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] ") + MessageString, true);
    }
}

void Cheat::Logger::MessageCustomCategory(std::string CategoryName, std::string Message)
{
    if (LoggerInitialized)
    {
        std::string MessageString = " [" + CategoryName + "] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
    }
}

void Cheat::Logger::DebugMessage(std::string Message)
{
    if (LoggerInitialized)
    {
        std::string MessageString = "[DBG] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] ") + MessageString, true);
    }
}

void Cheat::Logger::Error(char* Message, bool ShowMessageBox)
{
    if (LoggerInitialized)
    {
        std::string MessageString = "[ERR] " + (std::string)Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] ") + MessageString, true);

        if (ShowMessageBox)
        {
            MessageBoxA(NULL, Message, "GTAV Cheat Error", MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
        }
    }
}

void Cheat::Logger::SendMessageToGameChatLogWindow(std::string Message)
{
    GameChatLoggerObject.AddLog(Cheat::CheatFunctions::StringToConstChar(Message + "\n"));
}

bool CheatWindowClosedAtInit = false;
void Cheat::Logger::CheatWindow()
{
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x * 30 / 100, 600), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x * 60 / 100, 0), ImGuiCond_Once);

    if (CheatWindowVisible)
    {
        ImGui::Begin("Cheat Log", &CheatWindowVisible, ImGuiWindowFlags_NoCollapse);
        if (CheatFunctions::LoadConfigThreadFunctionCompleted && !CheatWindowClosedAtInit)
        {
            CheatWindowVisible = false;
            CheatWindowClosedAtInit = true;
        }
        ImGui::End();
        MainLoggerObject.Draw("Cheat Log", &CheatWindowVisible);
    } 
}

void Cheat::Logger::GameChatWindow()
{
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x * 30 / 100, 600), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x * 30 / 100, 0), ImGuiCond_Once);

    if (GameChatWindowVisible)
    {
        ImGui::Begin("Game Chat Log", &GameChatWindowVisible);
        ImGui::End();
        GameChatLoggerObject.Draw("Game Chat Log", &GameChatWindowVisible);
    }
}