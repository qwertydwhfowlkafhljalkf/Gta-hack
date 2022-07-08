#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int HUDColorRed, HUDColorGreen, HUDColorBlue, HUDColorAlpha;
void GUI::Submenus::HUD()
{
	GUI::Title("HUD");
	GUI::Toggle("Disable HUD", CheatFeatures::DisableHUDBool, "Prevents all HUD elements from being visible");
	GUI::Toggle("Hide Minimap", CheatFeatures::HideMinimapBool, "Not needed when Disable HUD is enabled");
	GUI::Break("Color", SELECTABLE_CENTER_TEXT);
	GUI::Int("Red", HUDColorRed, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
	GUI::Int("Green", HUDColorGreen, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
	GUI::Int("Blue", HUDColorBlue, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
	GUI::Int("Alpha", HUDColorAlpha, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
	if (GUI::Option("Change", ""))
	{
		for (int i = 0; i <= GameArrays::HUDColors.size(); i++)
		{
			UI::_SET_HUD_COLOUR(i, HUDColorRed, HUDColorGreen, HUDColorBlue, HUDColorAlpha);
		}
	}
	if (GUI::Option("Reset all to default", ""))
	{
		int index = 0;
		for (auto const& data : GameArrays::DefaultHUDColors)
		{
			UI::_SET_HUD_COLOUR(index, data.R, data.G, data.B, data.A);
			index++;
		}
	}
}