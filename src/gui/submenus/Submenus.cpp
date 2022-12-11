#include "../../src/cheat/fibermain.h"
#include "../../src/cheat/file_system.hpp"
using namespace Cheat;
using namespace GUI;

void (*Submenus::FunctionPointers[])() = {
	Submenus::Home, Submenus::Self, Submenus::AllPlayersExclusions, Submenus::AllPlayers, Submenus::Session, Submenus::RecoverySubmenuWarning,
	Submenus::RecoveryStatistics, Submenus::Recovery, Submenus::ReportStatistics, Submenus::SelfModel,
	Submenus::SpawnedVehicles, Submenus::Spawn, Submenus::PlayerList, Submenus::PedSpawn,
	Submenus::ThemeFiles, Submenus::Theme, Submenus::About, Submenus::Settings,
	Submenus::World, Submenus::NearbyPeds, Submenus::NearbyVehicles, Submenus::Time,
	Submenus::Vehicle, Submenus::VehicleCustomizer, Submenus::VehicleCustomizerColor,
	Submenus::VehicleCustomizerNeon, Submenus::VehicleMultipliers, Submenus::Miscellaneous,
	Submenus::Globals, Submenus::Vision, Submenus::HideElements, Submenus::Protection,
	Submenus::Wardrobe, Submenus::IPLLoader, Submenus::Weapons, Submenus::Weapon, Submenus::ShootEntities,
	Submenus::VehicleWeapons, Submenus::VehicleSpawnSettings, Submenus::VehicleSpawn, Submenus::Teleport, Submenus::HUD,
	Submenus::CustomTeleportLocations, Submenus::Weather, Submenus::ESP, Submenus::Radio,
	Submenus::WeaponVisuals, Submenus::Animations, Submenus::SelectedPlayerTeleport, Submenus::SelectedPlayer,
	Submenus::SelectedPlayerRemote, Submenus::SelectedPlayerApartmentTeleport, Submenus::SelectedPlayerAttachments,
	Submenus::SelectedPlayerFriendly, Submenus::SelectedPlayerGriefing, Submenus::Aimbot, Submenus::IPLTeleports,
	Submenus::WeaponAmmo, Submenus::LandmarkTeleportLocations, Submenus::SafehousesTeleportLocations,
	Submenus::HighAltitudeTeleportLocations, Submenus::UnderwaterTeleportLocations, Submenus::SessionStarter,
	Submenus::ProtectionScriptEvents, Submenus::ProtectionNetworkEvents, Submenus::Disables, Submenus::Television
};
int Submenus::NumberOfSubmenus = sizeof(Submenus::FunctionPointers) / sizeof(Submenus::FunctionPointers[0]);

void Submenus::Loop()
{
	for (int FuncPointerIndex = 0; FuncPointerIndex < Submenus::NumberOfSubmenus; ++FuncPointerIndex)
	{
		if (currentMenu == (*Submenus::FunctionPointers[FuncPointerIndex]))
		{
			(*Submenus::FunctionPointers[FuncPointerIndex])();
		}
	}
	if (currentMenu == Submenus::SelectedPlayer ||
		currentMenu == Submenus::SelectedPlayerFriendly ||
		currentMenu == Submenus::SelectedPlayerRemote ||
		currentMenu == Submenus::SelectedPlayerTeleport ||
		currentMenu == Submenus::SelectedPlayerAttachments ||
		currentMenu == Submenus::SelectedPlayerGriefing ||
		currentMenu == Submenus::SelectedPlayerApartmentTeleport ||
		currentMenu == Submenus::SelectedPlayerRemote)
	{
		if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(CheatFeatures::SelectedPlayer))
		{
			ShowPlayerInformationBox(CheatFeatures::SelectedPlayer);
		}
		else
		{
			PreviousMenu = nullptr;
			MoveMenu(Submenus::Home);
			MoveMenu(Submenus::Session);
		}
	}
	if (currentMenu == Submenus::ThemeFiles)
	{
		ThemeFilesVector.clear();
		for (const auto& file : std::filesystem::directory_iterator(file_system::paths::ThemesDir))
		{
			ThemeFilesVector.push_back(file.path().stem().string());
		}
	}
}