#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SelectedPlayerRemote()
{
	GUI::Title("Script Events");
	if (GUI::Option("Kick To Single Player", ""))
	{
		GameFunctions::TriggerScriptEvent(KICK_TO_SINGLE_PLAYER, CheatFeatures::SelectedPlayer);
	}
	if (GUI::Option("Force Into Mission", ""))
	{
		GameFunctions::TriggerScriptEvent(FORCE_INTO_MISSION, CheatFeatures::SelectedPlayer);
	}
	GUI::Break("CEO", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Kick", ""))
	{
		GameFunctions::TriggerScriptEvent(CEO_KICK, CheatFeatures::SelectedPlayer);
	}
	if (GUI::Option("Ban", ""))
	{
		GameFunctions::TriggerScriptEvent(CEO_BAN, CheatFeatures::SelectedPlayer);
	}
	GUI::Break("Teleport", SELECTABLE_CENTER_TEXT);
	GUI::MenuOption("Apartment", SelectedPlayerApartmentTeleport);
	if (GUI::Option("Cayo Perico Island", ""))
	{
		GameFunctions::TriggerScriptEvent(CAYO_PERICO_TELEPORT, CheatFeatures::SelectedPlayer);
	}
}