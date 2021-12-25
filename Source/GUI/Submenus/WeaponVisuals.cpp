#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::WeaponVisuals()
{
	GUI::Title("Visuals");
	GUI::Toggle("Weapon Invisibility", CheatFeatures::WeaponInvisibilityBool, "");
	GUI::Toggle("Crosshair", CheatFeatures::CrossHairBool, "");
	GUI::Toggle("Crosshair -> ADS only", CheatFeatures::CrossHairADSOnlyBool, "");
	GUI::Toggle("Cartoon Gun", CheatFeatures::CartoonGunBool, "Shows cartoon effects while shooting");
	GUI::Toggle("Entity Information Gun", CheatFeatures::EntityInformationGunBool, "Shows info about aimed entity");
}