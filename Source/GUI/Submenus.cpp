#include "../Header/Cheat Functions/FiberMain.h"
using namespace Cheat;
using namespace GUI;

void (*Submenus::FunctionPointers[])() = {
	Submenus::Home, Submenus::Self, Submenus::AllPlayersExclusions, Submenus::AllPlayers,
	Submenus::Online, Submenus::Session, Submenus::SessionChat, Submenus::RecoverySubmenuWarning,
	Submenus::RecoveryStatistics, Submenus::Recovery, Submenus::ReportStatistics, Submenus::SelfModel,
	Submenus::SpawnedVehicles, Submenus::Spawn, Submenus::PlayerList, Submenus::PedSpawn, Submenus::DLCVehicles,
	Submenus::ThemeFiles, Submenus::Theme, Submenus::About, Submenus::Settings,
	Submenus::World, Submenus::NearbyPeds, Submenus::NearbyVehicles, Submenus::Time,
	Submenus::Vehicle, Submenus::VehicleCustomizer, Submenus::VehicleCustomizerColor,
	Submenus::VehicleCustomizerNeon, Submenus::VehicleMultipliers, Submenus::Miscellaneous,
	Submenus::Globals, Submenus::Vision, Submenus::HideElements, Submenus::Protections,
	Submenus::Wardrobe, Submenus::IPLLoader, Submenus::Weapons, Submenus::Weapon, Submenus::ShootEntities,
	Submenus::VehicleWeapons, Submenus::VehicleSpawnSettings, Submenus::VehicleSpawn, Submenus::Teleport, Submenus::HUD,
	Submenus::CustomTeleportLocations, Submenus::Weather, Submenus::ESP, Submenus::Radio,
	Submenus::WeaponVisuals, Submenus::Animations, Submenus::SelectedPlayerTeleport, Submenus::SelectedPlayer,
	Submenus::SelectedPlayerRemote, Submenus::SelectedPlayerApartmentTeleport, Submenus::SelectedPlayerAttachments,
	Submenus::SelectedPlayerFriendly, Submenus::SelectedPlayerGriefing, Submenus::Aimbot, Submenus::IPLTeleports,
	Submenus::WeaponAmmo, Submenus::LandmarkTeleportLocations, Submenus::SafehousesTeleportLocations,
	Submenus::HighAltitudeTeleportLocations, Submenus::UnderwaterTeleportLocations, Submenus::TheContractDLC, 
	Submenus::LosSantosTunersDLC, Submenus::CayoPericoHeistDLC, Submenus::SummerSpecialDLC, Submenus::CunningStuntsDLC,
	Submenus::DiamondCasinoHeistDLC, Submenus::DiamondCasinoResortDLC, Submenus::ArenaWarDLC, Submenus::SmugglersRunDLC,
	Submenus::AfterHoursDLC, Submenus::GunrunningDLC, Submenus::DoomsdayHeistDLC, Submenus::SSASSSDLC, Submenus::VanVehicles,
	Submenus::UtilityVehicles, Submenus::TrainVehicles, Submenus::TrailerVehicles, Submenus::SuperVehicles,
	Submenus::SportVehicles, Submenus::SUVVehicles, Submenus::ServiceVehicles, Submenus::PlaneVehicles,
	Submenus::MotorcycleVehicles, Submenus::MilitaryVehicles, Submenus::IndustrialVehicles, Submenus::HelicopterVehicles,
	Submenus::EmergencyVehicles, Submenus::SportClassicVehicles, Submenus::OffroadVehicles, Submenus::SedanVehicles,
	Submenus::CoupesVehicles, Submenus::MuscleVehicles, Submenus::BoatVehicles, Submenus::CommercialVehicles,
	Submenus::CompactVehicles, Submenus::CycleVehicles
};
int Submenus::NumberOfSubmenus = sizeof(Submenus::FunctionPointers) / sizeof(Submenus::FunctionPointers[0]);