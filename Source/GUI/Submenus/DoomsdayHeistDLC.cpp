#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::DoomsdayHeistDLC()
{
	GUI::Title("The Doomsday Heist");
	for (auto const& i : GameArrays::DoomsdayModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}