#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Protection()
{
	GUI::Title("Protection");
	if (GUI::Option("Toggle Anti-Crash Camera", "Changes camera position to prevent entity crash")) { GameFunctions::EnableDisableAntiCrashCamera(); }
	GUI::Break("Protection", SELECTABLE_CENTER_TEXT);
	GUI::MenuOption("Script Events", Submenus::ProtectionScriptEvents);
	GUI::Toggle("Vote Kick", CheatFeatures::ProtectionVoteKickBool, "");
	GUI::Toggle("Freeze", CheatFeatures::ProtectionFreezeBool, "");
	GUI::Toggle("Give/Remove Weapons", CheatFeatures::ProtectionGiveRemoveWeaponsBool, "");
	GUI::Toggle("Alter Wanted Level", CheatFeatures::ProtectionAlterWantedLevelBool, "");
	GUI::Toggle("World Events", CheatFeatures::ProtectionWorldEventsBool, "Fire, explosions and more");
	GUI::Toggle("Vehicle", CheatFeatures::ProtectionVehicleBool, "Control & Explosions");
}