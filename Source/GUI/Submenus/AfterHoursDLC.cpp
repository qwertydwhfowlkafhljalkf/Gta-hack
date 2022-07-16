#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::AfterHoursDLC()
{
	GUI::Title("After Hours");
	for (auto const& i : GameArrays::AfterHoursModels)
	{
		if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(MISC::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
		{
			GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
		}
	}
}