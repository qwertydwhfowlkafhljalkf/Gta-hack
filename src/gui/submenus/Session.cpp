#include "../../src/cheat/fibermain.h"

using namespace Cheat;
void GUI::Submenus::Session()
{
	GUI::Title("Session");
	GUI::MenuOption("Players", Submenus::PlayerList);
	GUI::MenuOption("All Players", Submenus::AllPlayers);
	GUI::MenuOption("Session Starter", Submenus::SessionStarter);
}