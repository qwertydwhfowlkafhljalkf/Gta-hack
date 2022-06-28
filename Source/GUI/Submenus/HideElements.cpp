#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::HideElements()
{
	GUI::Title("Hide Elements");
	GUI::Toggle("Hide Selectable Information Box", Cheat::CheatFeatures::HideSelectableInformationBox, "");
	GUI::Toggle("Hide Player Information Box", CheatFeatures::HidePlayerInformationBox, "");
	GUI::Toggle("Hide Vehicle Info & Preview", CheatFeatures::HideVehicleInfoAndPreview, "");
	GUI::Toggle("Hide Own/local IP Address", CheatFeatures::HideOwnIPAddress, "");
	GUI::Toggle("Hide On-screen Game & Cheat Info", CheatFeatures::HideOnScreenGameAndCheatInfo, "");
}