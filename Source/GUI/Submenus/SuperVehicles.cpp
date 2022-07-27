#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SuperVehicles()
{
	GUI::Title("Super");
	for (auto const& i : GameArrays::SuperModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}