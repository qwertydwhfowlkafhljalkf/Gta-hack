#include "../Header/Cheat Functions/FiberMain.h"

void Cheat::LogFunctions::Init()
{
	std::string MessageString = "Build: " + (std::string)CHEAT_BUILD_NUMBER + " | Compile Date & Time: " + __DATE__ + " " + __TIME__ + 
								Cheat::CheatFunctions::ReturnDateTimeFormatAsString(" | Load Date & Time: %b %e %Y %H:%M:%S")
								+ "\nInitializing GTAV Cheat" + " | Github Repository: https://github.com/HatchesPls/GrandTheftAutoV-Cheat\n";
	std::cout << MessageString;

	//Write divider line to logfile
	CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n------------------------------------------------------------------------------------------------------------------------------------------------------", std::ofstream::out | std::ofstream::app);

	//Write text
	CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), "\n" + MessageString, std::ofstream::out | std::ofstream::app);
}

void Cheat::LogFunctions::Message(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Info] " + Message + "\n";
	std::cout << MessageString;
	CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, std::ofstream::out | std::ofstream::app);
}

void Cheat::LogFunctions::MessageCustomCategory(std::string CategoryName, std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [" + CategoryName + "] " + Message + "\n";
	std::cout << MessageString;
}

void Cheat::LogFunctions::DebugMessage(std::string Message)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Debug] " + Message + "\n";
	std::cout << MessageString;
	CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, std::ofstream::out | std::ofstream::app);
}

void Cheat::LogFunctions::Error(char* Message, bool ShowMessageBox)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::string MessageString = CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S]") + " [Error] " + Message + "\n";
	std::cout << MessageString;
	CheatFunctions::WriteToFile(CheatFunctions::ReturnMainLogFilePath(), MessageString, std::ofstream::out | std::ofstream::app);
	
	if (ShowMessageBox)
	{
		MessageBoxA(NULL, Message, "GTAV Cheat Error", MB_TOPMOST | MB_ICONERROR | MB_SETFOREGROUND);
	}
}