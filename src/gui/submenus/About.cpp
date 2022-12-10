#include "../../src/cheat/FiberMain.h"

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
		CheatFunctions::UnloadCheat();
	}
}