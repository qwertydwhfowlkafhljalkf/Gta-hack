#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::MotorcycleVehicles()
{
	GUI::Title("Motorcycles");
	for (auto const& i : GameArrays::MotorcycleModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}