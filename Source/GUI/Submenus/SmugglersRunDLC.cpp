#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SmugglersRunDLC()
{
	GUI::Title("Smuggler's Run");
	for (auto const& i : GameArrays::SmugglersRunModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}