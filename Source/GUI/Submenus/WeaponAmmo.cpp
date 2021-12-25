#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::WeaponAmmo()
{
	GUI::Title("Ammo Modification");
	GUI::StringVector("Impact Ammo", { "Disabled", "Fire", "Airstrike", "Teleport To", "Explosion", "Show Bullet Coord" }, CheatFeatures::ImpactAmmoVectorPosition, "");
	GUI::StringVector("Custom Ammo", { "Disabled", "Valkyrie", "Rhino Tank", "RPG", "Firework" }, CheatFeatures::CustomAmmoVectorPosition, "");
}