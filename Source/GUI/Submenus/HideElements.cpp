#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::HideElements()
{
	GUI::Title("Hide Elements");
	GUI::Toggle("Selectable Information Box", Cheat::CheatFeatures::HideSelectableInformationBox, "");
	GUI::Toggle("Player Information Box", CheatFeatures::HidePlayerInformationBox, "");
	GUI::Toggle("Vehicle Info & Preview", CheatFeatures::HideVehicleInfoAndPreview, "");
	GUI::Toggle("Own/local IP Address", CheatFeatures::HideOwnIPAddress, "");
	GUI::Toggle("On-screen Game & Cheat Info", CheatFeatures::HideOnScreenGameAndCheatInfo, "");
	GUI::Toggle("Transaction Error Warnings", CheatFeatures::DisableTransactionErrorWarning, "");
}