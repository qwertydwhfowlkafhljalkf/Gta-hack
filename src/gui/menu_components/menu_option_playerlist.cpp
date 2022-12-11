#include "../../cheat/fibermain.h"

using namespace Cheat;

bool GUI::MenuOptionPlayerList(Player Player)
{
	bool IsLocalPlayer = GameFunctions::PlayerID == Player;
	std::string PlayerName = PLAYER::GET_PLAYER_NAME(Player);
	PlayerName = GameFunctions::PlayerID == Player ? "~g~YOU~w~ (" + PlayerName + ")" : PlayerName;

	// Append player tags
	if (GameFunctions::PlayerIsFreemodeScriptHost(Player)) { PlayerName.append(" ~o~[HOST]"); }
	if (GameFunctions::IsPlayerFriend(Player)) { PlayerName.append(" ~b~[FRIEND]"); }
	if (GameFunctions::IsEntityInInterior(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Player))) { PlayerName.append(" ~p~[INTERIOR]"); }

	std::string CurrentOnlinePlayerPictureName = GameFunctions::ReturnOnlinePlayerPictureString(Player);

	if (Option("      " + PlayerName, "", SELECTABLE_HIDE_INFO_BOX))
	{
		GUI::MoveMenu(Submenus::SelectedPlayer);
		return true;
	}

	VECTOR2 Position;
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Position = { GUI::guiX - (GUI::guiWidth * 45 / 100), GUI::guiY + (GUI::optionCount * SelectableHeight - 0.158f) };
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Position = { GUI::guiX - (GUI::guiWidth * 45 / 100), GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.158f };
	}
	DrawSpriteInGame(IsLocalPlayer ? "Textures" : CurrentOnlinePlayerPictureName, IsLocalPlayer ? "AdvancedNotificationImage" : CurrentOnlinePlayerPictureName, Position.x, Position.y, 0.02f, 0.03f, 0.f, 255, 255, 255, OnlinePlayerPictureTransparency);
	return false;
}