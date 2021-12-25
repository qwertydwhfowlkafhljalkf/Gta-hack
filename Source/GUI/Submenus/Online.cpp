#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Online()
{
	GUI::Title("Online");
	GUI::MenuOption("Players", Submenus::PlayerList);
	GUI::MenuOption("All Players", Submenus::AllPlayers);
	GUI::MenuOption("Protections", Submenus::Protections);
	GUI::MenuOption("Recovery", Submenus::RecoverySubmenuWarning);
	GUI::MenuOption("Session", Submenus::Session);
}