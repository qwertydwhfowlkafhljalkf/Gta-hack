#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Weather()
{
	GUI::Title("Weather");
	if (GUI::Option("Reset", ""))
	{
		GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
	}
	GUI::Break("Types", SELECTABLE_CENTER_TEXT);
	for (int i = 0; i < GameArrays::WeatherTypes.size(); i++)
	{
		if (GUI::Option(GameArrays::WeatherTypes[i].SelectableName, ""))
		{
			GAMEPLAY::SET_OVERRIDE_WEATHER(CheatFunctions::StringToChar(GameArrays::WeatherTypes[i].WeatherType));
		}
	}
}