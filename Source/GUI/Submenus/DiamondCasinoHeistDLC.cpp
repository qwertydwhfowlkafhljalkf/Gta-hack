#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::DiamondCasinoHeistDLC()
{
	GUI::Title("The Diamond Casino Heist");
	for (auto const& i : GameArrays::DiamondCasinoHeistDLCModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}