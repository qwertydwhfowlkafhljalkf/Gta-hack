#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Vehicle()
{
	GUI::Title("Vehicle");
	GUI::MenuOption("Los Santos Customs", Submenus::VehicleCustomizer);
	GUI::MenuOption("Vehicle Weapons", Submenus::VehicleWeapons);
	if (GUI::Option("Delete Current", ""))
	{
		if (!GameFunctions::DeleteVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID)))
		{
			GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
		}
	}
	if (GUI::Option("Flip Up", "Flip vehicle up")) { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false)); }
	if (GUI::Option("Set Max Vehicle Speed", ""))
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, false))
		{
			int MaxSpeedInput = GameFunctions::DisplayKeyboardAndReturnInputInteger(3, "Enter the desired max speed");
			if (MaxSpeedInput != 0)
			{ 	
				::Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID);
				if (CheatFeatures::MeasurementSystemVectorPosition == 0)
				{
					ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, GameFunctions::KMHToMS(MaxSpeedInput));
					GameFunctions::MinimapNotification("Max Speed Set (KM/H)");
				}
				else if (CheatFeatures::MeasurementSystemVectorPosition == 1)
				{
					ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, GameFunctions::MPHToMS(MaxSpeedInput));
					GameFunctions::MinimapNotification("Max Speed Set (MP/H)");
				}
			}
			else
			{
				GameFunctions::MinimapNotification("Canceled setting Max Vehicle Speed");
			}		
		}
		else
		{
			GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
		}
	}
	GUI::Toggle("Vehicle Invincibility", CheatFeatures::VehicleGodmodeBool, "Makes current vehicle invincible");
	GUI::Toggle("Vehicle Invisibility", CheatFeatures::VehicleInvisibleBool, "Makes current vehicle invisible");
	GUI::Toggle("Vehicle Horn Boost", CheatFeatures::VehicleHornBoostBool, "Press horn button to use");
	GUI::Toggle("Unlimited Rocket Boost", CheatFeatures::UnlimitedRocketBoostBool, "");
	GUI::StringVector("Speedometer", { "Disabled", "On-Screen", "License Plate", "Both" }, CheatFeatures::SpeedometerVectorPosition, "Set speedometer");
	GUI::Toggle("Rainbow Vehicle", CheatFeatures::RainbowVehicleBool, "Loops rainbow colors on current vehicle");
	GUI::Toggle("Drive On Water", CheatFeatures::DriveOnWaterBool, "Drive your vehicle on water");
	GUI::Toggle("Super Brakes", CheatFeatures::SuperBrakesBool, "");
}