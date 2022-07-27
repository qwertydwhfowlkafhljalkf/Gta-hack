#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::DiamondCasinoResortDLC()
{
	GUI::Title("The Diamond Casino & Resort");
	for (auto const& i : GameArrays::CasinoDLCModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}