#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SelectedPlayerRemote()
{
	GUI::Title("Remote Events");
	if (GUI::Option("Kick To Single Player", ""))
	{
		uint64_t arguments_aray[4] = { TSE_KICK_TO_SP, CheatFeatures::SelectedPlayer, 0, 0 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
	}
	GUI::Break("CEO", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Kick", ""))
	{
		uint64_t arguments_aray[4] = { TSE_CEO_KICK, CheatFeatures::SelectedPlayer, 1, 5 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
	}
	if (GUI::Option("Ban", ""))
	{
		uint64_t arguments_aray[4] = { TSE_CEO_BAN, CheatFeatures::SelectedPlayer, 1, 5 };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
	}
	GUI::Break("Teleport", SELECTABLE_CENTER_TEXT);
	GUI::MenuOption("Apartment", SelectedPlayerApartmentTeleport);
	if (GUI::Option("Cayo Perico", ""))
	{
		DWORD64 arguments_aray[2] = { TSE_CAYO_PERICO_TELEPORT, CheatFeatures::SelectedPlayer };
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, 2, 1 << CheatFeatures::SelectedPlayer);
	}
}