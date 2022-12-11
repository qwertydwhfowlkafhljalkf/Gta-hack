#include "../../src/cheat/fibermain.h"

using namespace Cheat;
void GUI::Submenus::PlayerList()
{
	GUI::Title("Players");
	PlayersSessionForLoop
	{
		if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
		{
			GUI::MenuOptionPlayerList(i) ? CheatFeatures::SelectedPlayer = i : NULL;
			if (GUI::currentOption == GUI::optionCount) 
			{
				GUI::ShowPlayerInformationBox(i);
			}
		}
	}
}