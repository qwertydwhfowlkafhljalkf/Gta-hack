#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SSASSSDLC()
{
	GUI::Title("SSASSS");
	for (auto const& i : GameArrays::SSASSSModels)
	{
		if (GUI::VehicleOption(i, i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}