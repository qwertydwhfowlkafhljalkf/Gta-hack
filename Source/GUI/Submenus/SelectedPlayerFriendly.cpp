#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SelectedPlayerFriendly()
{
	GUI::Title("Friendly");
	if (GUI::Option("Give All Weapons", "")) { GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer)); }
	if (GUI::Option("Copy Outfit", "")) { GameFunctions::CopySelectedPlayerOutfit(CheatFeatures::SelectedPlayer); }
	if (GUI::Option("Set Waypoint", "Sets waypoint to Selected player location"))
	{
		Vector3 TargetCoords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
		UI::SET_NEW_WAYPOINT(TargetCoords.x, TargetCoords.y);
	}
}