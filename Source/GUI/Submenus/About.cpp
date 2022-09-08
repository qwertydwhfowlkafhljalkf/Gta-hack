#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::About()
{
	GUI::Title("About");
	GUI::Break("Author: HatchesPls");
	if (GUI::Option("Support this project!", "Select to copy Bitcoin address to clipboard"))
	{
		CheatFunctions::CopyStringToClipboard("3BwCVtcJaNgUovcYQkDYFjrdy5YydTnjwc");
		GameFunctions::SubtitleNotification("~g~Bitcoin address copied to clipboard.~n~Thank you for your support!");
	}
	if (GUI::Option("Visit GitHub Repository", ""))
	{
		system("start https://github.com/HatchesPls/GrandTheftAutoV-Cheat");
	}
}