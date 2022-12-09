#include "../../src/Cheat/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::HighAltitudeTeleportLocations()
{
	GUI::Title("High Altitude");
	GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsHighAltitude);
}