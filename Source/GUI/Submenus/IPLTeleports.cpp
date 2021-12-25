#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::IPLTeleports()
{
	GUI::Title("IPL Teleports");
	if (GUI::Option("North Yankton", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 5309.519f, -5212.37f, 83.522f, true, false, false, true);
	}
	if (GUI::Option("Yacht", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -2045.8f, -1031.2f, 11.9f, true, false, false, true);
	}
	if (GUI::Option("Destroyed Hospital", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 356.8f, -590.1f, 43.3f, true, false, false, true);
	}
	if (GUI::Option("Jewelry Store", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -630.4f, -236.7f, 40.0f, true, false, false, true);
	}
	if (GUI::Option("Morgue", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 244.9f, -1374.7f, 39.5f, true, false, false, true);
	}
	if (GUI::Option("Cargo Ship", ""))
	{
		ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -90.0f, -2365.8f, 14.3f, true, false, false, true);
	}
}