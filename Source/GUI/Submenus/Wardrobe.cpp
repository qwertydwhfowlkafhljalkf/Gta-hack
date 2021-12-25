#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int SetPedTexture_Torso = 0, SetPedTexture_TorsoTexture = 0, SetPedTexture_Face = 0,
SetPedTexture_FaceTexture = 0, SetPedTexture_Head = 0, SetPedTexture_HeadTexture = 0,
SetPedTexture_Hair = 0, SetPedTexture_HairTexture = 0, SetPedTexture_Legs = 0,
SetPedTexture_LegsTexture = 0, SetPedTexture_Hands = 0, SetPedTexture_HandsTexture = 0,
SetPedTexture_Feet = 0, SetPedTexture_FeetTexture = 0, SetPedTexture_Eyes = 0,
SetPedTexture_EyesTexture = 0, SetPedTexture_Accesories = 0, SetPedTexture_AccesoriesTexture = 0,
SetPedTexture_AccesoriesSec = 0, SetPedTexture_AccesoriesSecTexture = 0, SetPedTexture_Textures = 0,
SetPedTexture_TexturesTexture = 0, SetPedTexture_TorsoSec = 0, SetPedTexture_TorsoSecTexture = 0;
int HairColor;
void GUI::Submenus::Wardrobe()
{
	GUI::Title("Wardrobe");
	if (GUI::Option("Police Uniform", ""))
	{
		if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("mp_m_freemode_01")))
		{
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 0, 45, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 55, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 35, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 10, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 122, 0, 0);
		}
		else if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("mp_f_freemode_01")))
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
	//int ComponentInt;
	//int TextureInt;
	//GUI::StringVector("Component", { "Face", "Mask", "Hair", "Torso", "Leg", "Parachute", "Shoes", "Accessory", "Undershirt", "Kevlar", "Badge", "Torso 2" }, ComponentInt, "", SELECTABLE_RETURN_VALUE_CHANGE);
	//GUI::Int("Texture", TextureInt, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(GameFunctions::PlayerPedID, ComponentInt, 0), 1);
	if (GUI::Int("Hair Color", HairColor, 0, PED::_GET_NUM_HAIR_COLORS(), 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE))
	{
		PED::_SET_PED_HAIR_COLOR(GameFunctions::PlayerPedID, HairColor, 0);
	}
	if (GUI::Int("Face", SetPedTexture_Face, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, 0); }
	if (GUI::Int("Face Texture", SetPedTexture_FaceTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, SetPedTexture_Face); }
	if (GUI::Int("Head", SetPedTexture_Head, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Head, 0); }
	if (GUI::Int("Head Texture", SetPedTexture_HeadTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 1, SetPedTexture_Head, SetPedTexture_HeadTexture); }
	if (GUI::Int("Hair", SetPedTexture_Hair, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, 0); }
	if (GUI::Int("Hair Texture", SetPedTexture_HairTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, SetPedTexture_HairTexture); }
	if (GUI::Int("Torso", SetPedTexture_Torso, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, 0); }
	if (GUI::Int("Torso Texture", SetPedTexture_TorsoTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, SetPedTexture_TorsoTexture); }
	if (GUI::Int("Legs", SetPedTexture_Legs, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, 0); }
	if (GUI::Int("Legs Texture", SetPedTexture_LegsTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, SetPedTexture_LegsTexture); }
	if (GUI::Int("Hands", SetPedTexture_Hands, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, 0); }
	if (GUI::Int("Hands Texture", SetPedTexture_HandsTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, SetPedTexture_HandsTexture); }
	if (GUI::Int("Feet", SetPedTexture_Feet, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, 0); }
	if (GUI::Int("Feet Texture", SetPedTexture_FeetTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, SetPedTexture_FeetTexture); }
	if (GUI::Int("Eyes", SetPedTexture_Eyes, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, 0); }
	if (GUI::Int("Eyes Texture", SetPedTexture_EyesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, SetPedTexture_EyesTexture); }
	if (GUI::Int("Accesories", SetPedTexture_Accesories, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, 0); }
	if (GUI::Int("Accesories Texture", SetPedTexture_AccesoriesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, SetPedTexture_AccesoriesTexture); }
	if (GUI::Int("Accesories2", SetPedTexture_AccesoriesSec, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, 0); }
	if (GUI::Int("Accesories2 Texture", SetPedTexture_AccesoriesSecTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, SetPedTexture_AccesoriesSecTexture); }
	if (GUI::Int("Torso 2", SetPedTexture_TorsoSec, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, 0); }
	if (GUI::Int("Torso 2 Texture", SetPedTexture_TorsoSecTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, SetPedTexture_TorsoSecTexture); }
	if (GUI::Int("Textures", SetPedTexture_Textures, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 10, SetPedTexture_Textures, 0); }
	if (GUI::Int("Textures Texture", SetPedTexture_TexturesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_Textures, SetPedTexture_TexturesTexture); }
}