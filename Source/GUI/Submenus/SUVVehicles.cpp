#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SUVVehicles()
{
	GUI::Title("SUV");
	for (auto const& i : GameArrays::SUVModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}