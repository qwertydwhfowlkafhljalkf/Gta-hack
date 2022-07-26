#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::TheCriminalEnterprisesDLC()
{
	GUI::Title("The Criminal Enterprises");
	for (auto const& i : GameArrays::TheCriminalEnterprisesDLC)
	{
		if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}