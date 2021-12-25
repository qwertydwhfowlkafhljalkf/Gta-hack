#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::VehicleSpawnSettings()
{
	GUI::Title("Vehicle Spawn Settings");
	GUI::Toggle("Spawn Inside", CheatFeatures::VehicleSpawnerSpawnInsideVehicle, "");
	GUI::Toggle("Spawn Invincible", CheatFeatures::VehicleSpawnerSpawnWithGodmode, "");
	GUI::Toggle("Spawn Max Upgraded", CheatFeatures::VehicleSpawnerSpawnMaxUpgraded, "");
	GUI::Toggle("Delete Current", CheatFeatures::VehicleSpawnerDeleteOldVehicle, "");
	GUI::Toggle("Spawn With Blip", CheatFeatures::VehicleSpawnerSpawnWithBlip, "");
	GUI::Toggle("Spawn Air Vehicles In The Air", CheatFeatures::VehicleSpawnerSpawnAirVehicleAir, "");
}