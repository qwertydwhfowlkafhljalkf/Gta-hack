#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int CustomLocationsAmount;
void GUI::Submenus::CustomTeleportLocations()
{
	GUI::Title("Custom Locations");
	if (CheatFunctions::FileOrDirectoryExists(CheatFunctions::ReturnCustomTeleportLocationsFilePath()))
	{
		Json::Value JsonHandle = CheatFunctions::ReadJsonFileAndReturnDataObject(CheatFunctions::ReturnCustomTeleportLocationsFilePath());
		for (auto it = JsonHandle.begin(); it != JsonHandle.end(); ++it)
		{
			CustomLocationsAmount++;
			Vector3 Target;
			Target.x = JsonHandle[it.key().asString()]["X"].asFloat();
			Target.y = JsonHandle[it.key().asString()]["Y"].asFloat();
			Target.z = JsonHandle[it.key().asString()]["Z"].asFloat();
			GUI::Break(it.key().asString(), SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Teleport To", ""))
			{	
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Target, false, false);
			}
			if (GUI::Option("Copy Coordinates To Clipboard", ""))
			{
				CheatFunctions::CopyStringToClipboard("X: " + std::to_string(Target.x) + " Y: " + std::to_string(Target.y) + " Z: " + std::to_string(Target.z));
				GameFunctions::MinimapNotification("Custom Location coordinates copied to clipboard");
			}
			if (GUI::Option("Delete", ""))
			{
				CheatFunctions::DeleteCustomTeleportLocation(it.key().asString());
			}
		}
	}
	if (CustomLocationsAmount == 0)
	{
		GUI::Break("No custom locations have been saved");
	}
	CustomLocationsAmount = 0;
}