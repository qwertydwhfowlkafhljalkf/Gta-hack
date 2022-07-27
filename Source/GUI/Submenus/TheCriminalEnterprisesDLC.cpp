#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::TheCriminalEnterprisesDLC()
{
	GUI::Title("The Criminal Enterprises");
	for (auto const& i : GameArrays::TheCriminalEnterprisesDLC)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}