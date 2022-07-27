#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::TheContractDLC()
{
	GUI::Title("The Contract");
	for (auto const& i : GameArrays::TheContractModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}