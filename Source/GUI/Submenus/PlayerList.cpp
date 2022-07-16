#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::PlayerList()
{
	GUI::Title("Players");
	GUI::StringVector("Show Selected Player", { "Player List & Menu", "Player List", "Disabled" }, CheatFeatures::PlayerListMarkerPosition, "");
	GUI::Break("List", SELECTABLE_CENTER_TEXT);
	for (int i = 0; i < 32; ++i)
	{
		if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
		{
			std::string PlayernameString = PLAYER::GET_PLAYER_NAME(i);
			if (GameFunctions::PlayerIsFreemodeScriptHost(i)) { PlayernameString.append(" ~o~[HOST]"); }
			if (GameFunctions::IsPlayerFriend(i)) { PlayernameString.append("~b~[FRIEND]"); }
			if (GameFunctions::IsEntityInInterior(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) { PlayernameString.append(" ~p~[INTERIOR]"); }
			if (GameFunctions::PlayerID == i) { PlayernameString.append(" ~g~[SELF]"); }
			GUI::MenuOptionPlayerList(PlayernameString, SELECTABLE_HIDE_INFO_BOX) ? CheatFeatures::SelectedPlayer = i : NULL;
			if (GUI::currentOption == GUI::optionCount) { GameFunctions::ShowPlayerInformationBox(i); }
		}
	}
}