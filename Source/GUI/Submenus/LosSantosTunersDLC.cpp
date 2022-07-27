#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::LosSantosTunersDLC()
{
	GUI::Title("Los Santos Tuners");
	for (auto const& i : GameArrays::LosSantosTunersModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}