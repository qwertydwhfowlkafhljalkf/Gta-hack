#include "../Header/Cheat Functions/FiberMain.h"

bool Cheat::Logger::LoggerInitialized = false;

struct LoggerStruct
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;
    bool                AutoScroll;

    LoggerStruct()
    {
        AutoScroll = true;
        Clear();
    }

    void Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void Draw(const char* title, bool* p_open = NULL)
    {
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = Buf.begin();
        const char* buf_end = Buf.end();
        if (Filter.IsActive())
        {
            for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                if (Filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
        ImGui::End();
    }
};

static LoggerStruct MainLoggerObject;

void Cheat::Logger::Init()
{
    std::string MessageString = "Build: " + (std::string)CHEAT_BUILD_NUMBER + " | Compile Date & Time: " + __DATE__ + " " + __TIME__ +
        Cheat::CheatFunctions::ReturnDateTimeFormatAsString(" | Load Date & Time: %b %e %Y %H:%M:%S")
        + "\nGitHub Repository: HatchesPls/GrandTheftAutoV-Cheat\n";
    MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));

    //Write divider line to logfile
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n------------------------------------------------------------------------------------------------------------------------------------------------------", true);

    //Write text
    CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n" + MessageString, true);

    LoggerInitialized = true;
}

void Cheat::Logger::Uninit()
{
    DebugMessage("Logger uninitialized");
    LoggerInitialized = false;
}

void Cheat::Logger::Message(std::string Message)
{
    if (LoggerInitialized)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Info] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);
    }
}

void Cheat::Logger::MessageCustomCategory(std::string CategoryName, std::string Message)
{
    if (LoggerInitialized)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [" + CategoryName + "] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
    }
}

void Cheat::Logger::DebugMessage(std::string Message)
{
    if (LoggerInitialized)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
        std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Debug] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);
    }
}

void Cheat::Logger::Error(char* Message, bool ShowMessageBox)
{
    if (LoggerInitialized)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Error] " + Message + "\n";
        MainLoggerObject.AddLog(CheatFunctions::StringToConstChar(MessageString));
        CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, true);

        if (ShowMessageBox)
        {
            MessageBoxA(NULL, Message, "GTAV Cheat Error", MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
        }
    }
}

void Cheat::Logger::ShowLoggerWindow()
{
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x * 30 / 100, 600));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->Size.x * 60 / 100, 0));

    ImGui::Begin("Log", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    if (CheatFunctions::LoadConfigThreadFunctionCompleted)
    {
        ImGui::SetWindowCollapsed(true, ImGuiCond_Once);
    }
    ImGui::End();

    MainLoggerObject.Draw("Log", NULL);
}