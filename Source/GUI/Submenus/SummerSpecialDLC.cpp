#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SummerSpecialDLC()
{
	GUI::Title("2020 Summer Special");
	for (auto const& i : GameArrays::SummerSpecialModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}