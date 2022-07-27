#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::CayoPericoHeistDLC()
{
	GUI::Title("The Cayo Perico Heist");
	for (auto const& i : GameArrays::CayoPericoHeistModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}