#include "../../cheat/fibermain.h"

using namespace Cheat;

bool GUI::MenuOptionPlayerList(Player Player)
{
	std::string PlayerName = PLAYER::GET_PLAYER_NAME(Player);
	bool IsLocalPlayer = GameFunctions::PlayerID == Player;
	std::string PlayerNameString = IsLocalPlayer ? "~g~YOU~s~ (" + PlayerName + ")" : PlayerName;
	const char* CurrentOnlinePlayerPictureName = "AdvancedNotificationImage";
	if (!IsLocalPlayer)
	{
		CurrentOnlinePlayerPictureName = GameFunctions::ReturnOnlinePlayerPictureString(Player);
	}

	if (Option("      " + PlayerNameString, "", SELECTABLE_HIDE_INFO_BOX))
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
	DrawSpriteInGame(IsLocalPlayer ? "Textures" : CurrentOnlinePlayerPictureName, CurrentOnlinePlayerPictureName, Position.x, Position.y, 0.02f, 0.03f, 0.f, 255, 255, 255, OnlinePlayerPictureTransparency);
	return false;
}