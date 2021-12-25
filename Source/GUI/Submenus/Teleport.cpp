#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int TeleportFoward = 1;
void GUI::Submenus::Teleport()
{
	GUI::Title("Teleport");
	if (GUI::Option("Teleport To Waypoint", "")) { GameFunctions::TeleportToBlipCoord(SpriteWaypoint); }
	GUI::Toggle("Auto Teleport To Waypoint", CheatFeatures::AutoTeleportToWaypointBool, "");
	if (GUI::Option("Teleport To Personal Vehicle", "")) { GameFunctions::TeleportToBlipCoord(SpritePersonalVehicleCar); }
	if (GUI::Option("Teleport To Objective", "")) { GameFunctions::TeleportToObjective(); }
	if (GUI::Option("Teleport to Custom Coordinate", ""))
	{
		Vector3 TargetCoordinates;
		try
		{
			TargetCoordinates.x = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter X-axis coordinate"));
			if (TargetCoordinates.x != 0) 
			{ 
				TargetCoordinates.y = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter Y-axis coordinate"));
				if (TargetCoordinates.y != 0) 
				{ 
					TargetCoordinates.z = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter Z-axis coordinate"));
					if (TargetCoordinates.z != 0) 
					{ 
						GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, TargetCoordinates, false, false);
					}
				}
			}		
		}
		catch (...)
		{
			GameFunctions::MinimapNotification("~r~Invalid float coordinate format inputted");
		}
	}
	if (GUI::Option("Teleport Into Last Used Vehicle", ""))
	{
		PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, VEHICLE::GET_LAST_DRIVEN_VEHICLE(), -1);
	}
	if (GUI::Int("Teleport Forward", TeleportFoward, 1, 10, 1))
	{
		Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0f, static_cast<float>(TeleportFoward), 0.0f);
		if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, false)) { GameFunctions::PlayerPedID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false); }
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(GameFunctions::PlayerPedID, Coords.x, Coords.y, Coords.z, false, false, true);
	}
	GUI::Break("Custom Locations", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Save current location", ""))
	{
		char* NewThemeFileName = GameFunctions::DisplayKeyboardAndReturnInput(20, "Enter Custom Teleport Location Name");
		if (NewThemeFileName != "0")
		{
			CheatFunctions::AddCustomTeleportLocation(NewThemeFileName);
			GameFunctions::MinimapNotification("Custom Location Saved");
		}
	}
	GUI::MenuOption("View locations", Submenus::CustomTeleportLocations);
	GUI::Break("Presets", SELECTABLE_CENTER_TEXT);
	GUI::MenuOption("Landmarks", Submenus::LandmarkTeleportLocations);
	GUI::MenuOption("IPL's", Submenus::IPLTeleports);
	GUI::MenuOption("Safehouses", Submenus::SafehousesTeleportLocations);
	GUI::MenuOption("Underwater", Submenus::UnderwaterTeleportLocations);
	GUI::MenuOption("High Altitude", Submenus::HighAltitudeTeleportLocations);
}