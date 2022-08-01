#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Protection()
{
	GUI::Title("Protection");
	if (GUI::Option("Toggle Anti-Crash Camera", "Changes camera position to prevent entity crash")) { GameFunctions::EnableDisableAntiCrashCamera(); }
	GUI::Break("Protection", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Enable All", "")) {
		CheatFeatures::ProtectionVoteKickBool = true;
		CheatFeatures::ProtectionFreezeBool = true;
		CheatFeatures::ProtectionGiveRemoveWeaponsBool = true;
		CheatFeatures::ProtectionWorldEventsBool = true;
		CheatFeatures::ProtectionAlterWantedLevelBool = true;
		CheatFeatures::ProtectionVehicleBool = true;
		CheatFeatures::BlockMaliciousScriptEvents = true;
	}
	if (GUI::Option("Disable All", "")) {
		CheatFeatures::ProtectionVoteKickBool = false;
		CheatFeatures::ProtectionFreezeBool = false;
		CheatFeatures::ProtectionGiveRemoveWeaponsBool = false;
		CheatFeatures::ProtectionWorldEventsBool = false;
		CheatFeatures::ProtectionAlterWantedLevelBool = false;
		CheatFeatures::ProtectionVehicleBool = false;
		CheatFeatures::BlockMaliciousScriptEvents = false;
	}
	GUI::Toggle("Script Events", CheatFeatures::BlockMaliciousScriptEvents, "Some GTAO missions might not work");
	GUI::Toggle("Script Events -> Block All", CheatFeatures::BlockAllScriptEvents, "Join GTAO before enabling", SELECTABLE_DISABLE_SAVE);
	GUI::Toggle("Vote Kick", CheatFeatures::ProtectionVoteKickBool, "");
	GUI::Toggle("Freeze", CheatFeatures::ProtectionFreezeBool, "");
	GUI::Toggle("Give/Remove Weapons", CheatFeatures::ProtectionGiveRemoveWeaponsBool, "");
	GUI::Toggle("Alter Wanted Level", CheatFeatures::ProtectionAlterWantedLevelBool, "");
	GUI::Toggle("World Events", CheatFeatures::ProtectionWorldEventsBool, "Fire, explosions and more");
	GUI::Toggle("Vehicle", CheatFeatures::ProtectionVehicleBool, "Control & Explosions");
}