#include "../../src/cheat/fibermain.h"

using namespace Cheat;
void GUI::Submenus::About()
{
	GUI::Title("About");
	GUI::Break("Author: HatchesPls");
	if (GUI::Option("Visit GitHub Repository", ""))
	{
		system("start https://github.com/HatchesPls/GrandTheftAutoV-Cheat");
	}
	if (GUI::Option("Unload Cheat", ""))
	{
		// Remove console window
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		FreeConsole();

		// Stop MainFiber
		Cheat::c_running = false;
	}
}