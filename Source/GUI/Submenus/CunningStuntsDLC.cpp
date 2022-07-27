#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::CunningStuntsDLC()
{
	GUI::Title("Cunning Stunts");
	for (auto const& i : GameArrays::CunningStuntsDLCModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}