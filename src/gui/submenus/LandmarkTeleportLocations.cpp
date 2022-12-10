#include "../../src/Cheat/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::LandmarkTeleportLocations()
{
	GUI::Title("Landmarks");
	GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsLandmarks);
}