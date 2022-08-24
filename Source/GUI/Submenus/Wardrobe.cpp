#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int ComponentIDInt, DrawableIDInt, DrawableTextureIDInt, PaletteIDInt, HairColor;
void GUI::Submenus::Wardrobe()
{
	GUI::Title("Wardrobe");
	if (GUI::Option("Police Uniform", ""))
	{
		if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, MISC::GET_HASH_KEY("mp_m_freemode_01")))
		{
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 0, 45, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 55, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 35, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 10, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 122, 0, 0);
		}
		else if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, MISC::GET_HASH_KEY("mp_f_freemode_01")))
		{
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 0, 45, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 48, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 34, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 29, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 152, 0, 0);
		}
	}
	if (GUI::Option("Default Variation", ""))
	{
		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(GameFunctions::PlayerPedID);
	}
	if (GUI::Option("Random Variation", ""))
	{
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(GameFunctions::PlayerPedID, false);
	}
	if (GUI::Option("Random Accessories", ""))
	{
		PED::SET_PED_RANDOM_PROPS(GameFunctions::PlayerPedID);
	}
	if (GUI::Option("Reset Appearance", ""))
	{
		PED::CLEAR_ALL_PED_PROPS(GameFunctions::PlayerPedID);
		PED::CLEAR_PED_DECORATIONS(GameFunctions::PlayerPedID);
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 1, 0, 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 5, 0, 0, 0);
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 9, 0, 0, 0);
	}
	GUI::Break("Components", SELECTABLE_CENTER_TEXT);
	GUI::StringVector("Component", { "Head", "Beards/Mask", "Hair", "Upper Body", "Lower Body", "Hands/Arms", "Shoes/Feet", "Accessories", "Miscellaneous Clothing", "Gear and equipment", "Overlays", "Miscellaneous" }, ComponentIDInt, "");	
	if (GUI::Int("Drawable", DrawableIDInt, 0, PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(GameFunctions::PlayerPedID, ComponentIDInt) - 1, 1, "", SELECTABLE_RETURN_VALUE_CHANGE))
	{
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, ComponentIDInt, DrawableIDInt, DrawableTextureIDInt, PaletteIDInt);
	}
	if (GUI::Int("Drawable Texture", DrawableTextureIDInt, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(GameFunctions::PlayerPedID, ComponentIDInt, DrawableIDInt) - 1, 1, "", SELECTABLE_RETURN_VALUE_CHANGE))
	{
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, ComponentIDInt, DrawableIDInt, DrawableTextureIDInt, PaletteIDInt);
	}
	if (GUI::Int("Palette", PaletteIDInt, 0, 3, 1, "Optional", SELECTABLE_RETURN_VALUE_CHANGE))
	{
		PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, ComponentIDInt, DrawableIDInt, DrawableTextureIDInt, PaletteIDInt);
	}
	GUI::Break("Hair Color", SELECTABLE_CENTER_TEXT);
	if (GUI::Int("Hair Color", HairColor, 0, PED::_GET_NUM_HAIR_COLORS(), 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE))
	{
		PED::_SET_PED_HAIR_COLOR(GameFunctions::PlayerPedID, HairColor, 0);
	}
}