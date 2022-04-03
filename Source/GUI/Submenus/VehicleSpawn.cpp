#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::VehicleSpawn()
{
	GUI::Title("Vehicle Spawn");
	GUI::MenuOption("Settings", Submenus::VehicleSpawnSettings);
	GUI::MenuOption("Previously Spawned", SpawnedVehicles);
	if (GUI::Option("Custom Input", "Input custom vehicle model name"))
	{
		char* KeyboardInput;
		if (GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter Vehicle Model Name", KeyboardInput))
		{  
			GameFunctions::SpawnVehicle(KeyboardInput);
		}	
	}
	GUI::Break("Categories", SELECTABLE_CENTER_TEXT);
	GUI::MenuOption("DLC Vehicles", Submenus::DLCVehicles);
	GUI::MenuOption("Super", Submenus::SuperVehicles);
	GUI::MenuOption("Sports", Submenus::SportVehicles);
	GUI::MenuOption("Sport Classic", Submenus::SportClassicVehicles);
	GUI::MenuOption("Offroad", Submenus::OffroadVehicles);
	GUI::MenuOption("Sedans", Submenus::SedanVehicles);
	GUI::MenuOption("Coupes", Submenus::CoupesVehicles);
	GUI::MenuOption("Muscle", Submenus::MuscleVehicles);
	GUI::MenuOption("Boats", Submenus::BoatVehicles);
	GUI::MenuOption("Commercial", Submenus::CommercialVehicles);
	GUI::MenuOption("Compacts", Submenus::CompactVehicles);
	GUI::MenuOption("Cycles", Submenus::CycleVehicles);
	GUI::MenuOption("Emergency", Submenus::EmergencyVehicles);
	GUI::MenuOption("Helicopters", Submenus::HelicopterVehicles);
	GUI::MenuOption("Industrial", Submenus::IndustrialVehicles);
	GUI::MenuOption("Military", Submenus::MilitaryVehicles);
	GUI::MenuOption("Motorcycles", Submenus::MotorcycleVehicles);
	GUI::MenuOption("Planes", Submenus::PlaneVehicles);
	GUI::MenuOption("Service", Submenus::ServiceVehicles);
	GUI::MenuOption("SUV", Submenus::SUVVehicles);
	GUI::MenuOption("Trailer", Submenus::TrailerVehicles);
	GUI::MenuOption("Trains", Submenus::TrainVehicles);
	GUI::MenuOption("Utility", Submenus::UtilityVehicles);
	GUI::MenuOption("Vans", Submenus::VanVehicles);
}