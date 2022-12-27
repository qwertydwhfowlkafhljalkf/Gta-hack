#include "../../src/cheat/fibermain.h"
#include "../../src/cheat/file_system.hpp"
#include "../../src/game/features/custom_teleport_locations.hpp"

using namespace Cheat;
mINI::INIFile File(file_system::paths::CusTelLocFile);
mINI::INIStructure StructData;
void GUI::Submenus::CustomTeleportLocations()
{
	GUI::Title("Custom Teleport Locations");
	File.read(StructData);
	if (std::filesystem::exists(file_system::paths::CusTelLocFile) && StructData.size() > 0)
	{
		for (auto const& it : StructData)
		{
			Vector3 Coordinates;
			try
			{
				Coordinates.x = std::stof(it.second.get("x"));
				Coordinates.y = std::stof(it.second.get("y"));
				Coordinates.z = std::stof(it.second.get("z"));
			}
			catch (...) {}

			GUI::Break(it.first, SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Teleport To", ""))
			{
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coordinates, false, false);
			}
			if (GUI::Option("Remove", ""))
			{
				CheatFeatures::custom_tel_locations::Remove(it.first);
			}
		}
	}
	else
	{
		GUI::Break("No custom locations have been saved");
	}
}