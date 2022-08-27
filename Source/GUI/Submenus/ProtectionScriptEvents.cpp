#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::ProtectionScriptEvents()
{
	GUI::Title("Script Events Protection");
	GUI::Toggle("Block All", CheatFeatures::BlockAllScriptEvents, "Blocks ~bold~all~s~ script events send to you - join a session before enabling", SELECTABLE_DISABLE_SAVE);
	GUI::Break("Script Events", SELECTABLE_CENTER_TEXT);
	GUI::Toggle("Kicks", CheatFeatures::ProtectionScriptEvents_Kicks, "");
	GUI::Toggle("CEO Kick", CheatFeatures::ProtectionScriptEvents_CEOKick, "");
	GUI::Toggle("CEO Ban", CheatFeatures::ProtectionScriptEvents_CEOBan, "");
	GUI::Toggle("Property Teleport", CheatFeatures::ProtectionScriptEvents_PropertyTeleport, "");
	GUI::Toggle("Cayo Perico Teleport", CheatFeatures::ProtectionScriptEvents_CayoPericoTeleport, "");
	GUI::Toggle("Force Into Mission", CheatFeatures::ProtectionScriptEvents_ForceIntoMission, "");
}