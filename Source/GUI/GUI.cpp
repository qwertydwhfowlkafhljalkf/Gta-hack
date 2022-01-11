#include "../Header/Cheat Functions/FiberMain.h"
using namespace Cheat;

const float GUI::guiX_Default				= 0.11f;
const float GUI::guiY_Default				= 0.30f;
const float GUI::guiWidth_Default			= 0.21f;
const float GUI::SelectableInfoBoxX_Default	= 0.50f;
const float GUI::SelectableInfoBoxY_Default	= 0.840f;
float GUI::guiX					= 0.11f;
float GUI::guiY					= 0.30f;
float GUI::guiWidth				= 0.21f; //Do not use (scalling not properly implemented yet)
float GUI::SelectableInfoBoxX	= 0.50f;
float GUI::SelectableInfoBoxY	= 0.840f;
float GUI::SelectableHeight		= 0.040f;
bool GUI::ShowHeaderBackground	= true;
bool GUI::ShowHeaderTexture		= true;
bool GUI::HideGUIElements		= false; //Prevents all GUI elements from being visible when True
bool GUI::CheatGUIHasBeenOpened	= false;
bool GUI::CurrentOptionIsSavable	= false;
bool GUI::RestorePreviousSubmenu = true;
std::string SelectableInformationText;
std::string GUI::CurrentTheme;
int GUI::maxVisOptions			= 10;
int GUI::currentOption			= 0;
int GUI::currentOptionVisible    = 0;	//This has GUI::Break excluded
int GUI::previousOption			= 0;
int GUI::optionCount				= 0;
int GUI::optionCountVisible		= 0;	//This has GUI::Break excluded
int GUI::TotalOptionsCount		= 0;
int GUI::menuLevel				= 0;
void* GUI::PreviousMenu			= nullptr;
void* GUI::currentMenu			= nullptr;
int GUI::PreviousMenuLevel		= 0;
int GUI::optionsArray			[1000];
void* GUI::menusArray			[1000];
std::vector <std::string> GUI::ThemeFilesVector;
                 
RGBA GUI::PrimaryColor               { 0, 0, 255, 255 };
RGBAF GUI::TextColorAndFont			{ 255, 255, 255, 255, FontChaletLondon };
int GUI::SelectableTransparency		= 150;
int GUI::HeaderBackgroundTransparency  = 200;
int GUI::TitleAndEndTransparency		= 210;
int GUI::ToggleSelectableTransparency = 255;
int GUI::HeaderTextureTransparency	 = 255;
int GUI::EndSmallLogoTransparency	 = 255;
int GUI::OnlinePlayerPictureTransparency = 255;

int GUI::MenuArrowAnimationDelay		= 1000;


void GUI::Title(std::string TitleName)
{
	if (ShowHeaderBackground) { DrawRectInGame({ PrimaryColor.r, PrimaryColor.g, PrimaryColor.b, HeaderBackgroundTransparency }, { guiX, GUI::guiY - SelectableHeight - 0.181f }, { guiWidth, SelectableHeight + 0.045f }); }
	if (ShowHeaderTexture) { DrawSpriterInGame("Textures", "HeaderDefaultTransparent", guiX, GUI::guiY - SelectableHeight - 0.181f, guiWidth, SelectableHeight + 0.045f, 0, 255, 255, 255, HeaderTextureTransparency); }
	DrawTextInGame(TitleName, TextColorAndFont, { GUI::guiX, GUI::guiY - 0.174f }, { 0.40f, 0.38f }, true, true);
	DrawRectInGame({ 0, 0, 0, TitleAndEndTransparency }, { guiX, GUI::guiY - 0.1585f }, { guiWidth, SelectableHeight });

	if (CheatFeatures::CursorGUINavigationEnabled)
	{
		std::string CursorBackCloseString;
		if (GUI::currentMenu == GUI::Submenus::Home) { CursorBackCloseString = "Close"; }
		else { CursorBackCloseString = "Back"; }
		DrawSpriterInGame("commonmenu", "arrowleft", GUI::guiX - 0.100f, GUI::guiY - 0.160f, 0.015f, 0.025f, 0, 255, 255, 255, 255);
		DrawTextInGame(CursorBackCloseString, TextColorAndFont, { GUI::guiX - 0.094f, GUI::guiY - 0.174f }, { 0.35f, 0.37f }, false, true);
	}

	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(false);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
}

bool GUI::Option(std::string option, std::string InformationText, int BitFlags)
{
	GUI::optionCount++;
	GUI::optionCountVisible++;
	bool OnCurrent = GUI::currentOption == GUI::optionCount ? true : false;
	VECTOR2 TextPosition, RectPosition;
	RGBA RectColor;

	if(BitFlags & SELECTABLE_DISABLED) { option.append(" (Disabled)"); }
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		TextPosition = { GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * SelectableHeight - 0.174f };
		RectPosition = { GUI::guiX, GUI::guiY + (GUI::optionCount) * SelectableHeight - 0.1585f };
		OnCurrent ? RectColor = PrimaryColor : RectColor = { 0, 0, 0, SelectableTransparency };
		DrawTextInGame(option, TextColorAndFont, TextPosition, { 0.35f, 0.35f }, false);
		DrawRectInGame(RectColor, RectPosition, { GUI::guiWidth, SelectableHeight });
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		TextPosition = { GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f };
		RectPosition = { GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.1585f };
		OnCurrent ? RectColor = PrimaryColor : RectColor = { 0, 0, 0, SelectableTransparency };
		DrawTextInGame(option, TextColorAndFont, TextPosition, { 0.35f, 0.35f }, false);
		DrawRectInGame(RectColor, RectPosition, { GUI::guiWidth, SelectableHeight });
	}
	if (OnCurrent)
	{
		//Selectable Information Box
		if (!CheatFeatures::HideSelectableInformationBox && !(BitFlags & SELECTABLE_HIDE_INFO_BOX))
		{
			DrawRectInGame({ GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b, 210 }, { SelectableInfoBoxX, SelectableInfoBoxY + 0.042f }, { 0.25f, 0.003f });			
			DrawRectInGame({ 0, 0, 0, 210 }, { SelectableInfoBoxX, SelectableInfoBoxY }, { 0.25f, 0.080f });
			DrawTextInGame(SelectableInformationText != "" ? CheatFunctions::TextWrap(SelectableInformationText, 30) : option, TextColorAndFont, { SelectableInfoBoxX - 0.12f, SelectableInfoBoxY - 0.033f }, { 0.30f, 0.30f }, false);
			if (GUI::CurrentOptionIsSavable) { DrawTextInGame("Save Option: " + CheatFunctions::VirtualKeyCodeToString(Controls::SaveSelectableKey), TextColorAndFont, { SelectableInfoBoxX + 0.04f, SelectableInfoBoxY - 0.033f }, { 0.30f, 0.30f }, false); }
		}
		
		GUI::currentOptionVisible = GUI::optionCount - (GUI::optionCount - GUI::optionCountVisible);
		GUI::CurrentOptionIsSavable = false;
		GUI::previousOption = GUI::currentOption;
		if (InformationText == "") { SelectableInformationText.clear(); }
		else { SelectableInformationText = InformationText; }
		if (Controls::SelectPressed)
		{
			SelectAction:
			if (BitFlags & SELECTABLE_DISABLED)
			{
				GameFunctions::AdvancedMinimapNotification("This selectable is currently disabled", "Textures", "AdvancedNotificationImage", false, 4, "Cheat", "", 0.5f, "");
				return false;
			}
			return true;
		}
	}

	if (GameFunctions::IsCursorAtXYPosition(RectPosition, { GUI::guiWidth, SelectableHeight }) && CheatFeatures::CursorGUINavigationEnabled)
	{
		UI::_SET_CURSOR_SPRITE(PreGrab);
		if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, INPUT_CURSOR_ACCEPT))
		{
			goto SelectAction;
		}
	}
	return false;
}

bool GUI::VehicleOption(std::string option, std::string ModelName)
{
	bool OnCurrent = GUI::currentOption == GUI::optionCount ? true : false;
	if (Option(option, ""))
	{
		return true;
	}
	if (OnCurrent)
	{
		std::string VehiclePreviewDictName, VehiclePreviewName;
		std::transform(ModelName.begin(), ModelName.end(), ModelName.begin(), tolower);
		VehiclePreviewDictName = "Textures";
		VehiclePreviewName	   = "NoVehiclePreviewAvailable";

		for (auto& Vector : GameArrays::VehicleModelPictures)
		{
			if (Vector.PreviewName == ModelName)
			{
				VehiclePreviewDictName = Vector.DictName;
				VehiclePreviewName = Vector.PreviewName;
			}
		}
		
		if (!CheatFeatures::HideVehicleInfoAndPreview)
		{
			std::ostringstream ModelMaxSpeed;
			if (CheatFeatures::MeasurementSystemVectorPosition == 0)
			{
				ModelMaxSpeed << "Max Speed: " << GameFunctions::MSToKMH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))) << " KM/H";
			}
			else if (CheatFeatures::MeasurementSystemVectorPosition == 1)
			{
				ModelMaxSpeed << "Max Speed: " << GameFunctions::MSToMPH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))) << " MP/H";
			}

			if (guiX < 0.71f)
			{
				DrawTextInGame("Model Name: " + ModelName, TextColorAndFont, { guiX + 0.111f,  guiY - 0.004f }, { 0.45f, 0.30f }, false);
				DrawTextInGame(ModelMaxSpeed.str(), TextColorAndFont, { guiX + 0.111f, guiY + 0.010f }, { 0.45f, 0.30f }, false);
				DrawTextInGame("Seats: " + std::to_string(VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))), TextColorAndFont, { guiX + 0.111f, guiY + 0.025f}, {0.45f, 0.30f}, false);
				DrawRectInGame({ 0, 0, 0, 150 }, { guiX + 0.187f, GUI::guiY - 0.061f }, { 0.16f, 0.22f });
				DrawSpriterInGame(VehiclePreviewDictName, VehiclePreviewName, guiX + 0.187f, guiY - 0.085f, 0.15f, 0.15f, 0.f, 255, 255, 255, 255);
			}
			else
			{
				DrawTextInGame("Model Name: " + ModelName, TextColorAndFont, { guiX - 0.262f, guiY - 0.004f }, { 0.45f, 0.30f }, false);
				DrawTextInGame(ModelMaxSpeed.str(), TextColorAndFont, { guiX - 0.262f, guiY + 0.010f }, { 0.45f, 0.30f }, false);
				DrawTextInGame("Seats: " + std::to_string(VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))), TextColorAndFont, { guiX - 0.262f, guiY + 0.025f }, { 0.45f, 0.30f }, false);
				DrawRectInGame({ 0, 0, 0, 150 }, { guiX - 0.187f, guiY - 0.061f }, { 0.16f, 0.22f });
				DrawSpriterInGame(VehiclePreviewDictName, VehiclePreviewName, guiX - 0.187f, guiY - 0.085f, 0.15f, 0.15f, 0.f, 255, 255, 255, 255);
			}
		}
	}
	return false;
}

bool GUI::Break(std::string option, int BitFlags)
{
	GUI::optionCount++;

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (BitFlags & SELECTABLE_CENTER_TEXT) 
		{ 
			DrawTextInGame("[ ~c~" + option + " ~s~]", { PrimaryColor.r, PrimaryColor.g, PrimaryColor.b, PrimaryColor.a, TextColorAndFont.f }, {GUI::guiX, GUI::guiY + (GUI::optionCount) * SelectableHeight - 0.174f}, {0.35f, 0.35f}, true, true); 
		}
		else
		{ 
			DrawTextInGame(option, TextColorAndFont, { GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount)*SelectableHeight - 0.174f }, { 0.35f, 0.35f }, false); 
		}
		DrawRectInGame({ 0, 0, 0, SelectableTransparency }, { GUI::guiX, GUI::guiY + (GUI::optionCount) * SelectableHeight - 0.1585f }, { GUI::guiWidth, SelectableHeight });
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		if (BitFlags & SELECTABLE_CENTER_TEXT)
		{ 
			DrawTextInGame("[ ~c~" + option + " ~s~]", { PrimaryColor.r, PrimaryColor.g, PrimaryColor.b, PrimaryColor.a, TextColorAndFont.f }, { GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.35f, 0.35f }, true, true); 
		}
		else
		{ 
			DrawTextInGame(option, TextColorAndFont, { GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.35f, 0.35f }, false); 
		}
		DrawRectInGame({ 0, 0, 0, SelectableTransparency }, { GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*SelectableHeight - 0.1585f }, { GUI::guiWidth, SelectableHeight });
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		GUI::CurrentOptionIsSavable = false;
		if (GUI::previousOption < GUI::currentOption && GUI::optionCount > 1)
		{
			GUI::currentOption++;
			if (GUI::TotalOptionsCount < GUI::currentOption)
			{
				GUI::currentOption = 1;
			}
		}
		else if (GUI::previousOption > GUI::currentOption && GUI::optionCount > 1)
		{
			GUI::currentOption--;
			if (GUI::TotalOptionsCount < 1)
			{
				GUI::currentOption = GUI::optionCount;
			}
		}
		else if (GUI::currentOption == 1 && GUI::TotalOptionsCount > 1)
		{
			GUI::currentOption++;
		}
	}
	return false;
}

bool GUI::MenuOptionArrowAnimationState = false;
bool GUI::MenuOption(std::string option, void* NewSubmenu, int BitFlags)
{
	if (Option(option, "", BitFlags))
	{
		GUI::MoveMenu(NewSubmenu);
		return true;
	}
	
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		DrawTextInGame(MenuOptionArrowAnimationState ? ">" : " >", TextColorAndFont, {GUI::guiX + 0.09f, GUI::guiY + (GUI::optionCount) * SelectableHeight - 0.174f}, {0.35f, 0.35f}, false);
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		DrawTextInGame(MenuOptionArrowAnimationState ? ">" : " >", TextColorAndFont, { GUI::guiX + 0.09f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.35f, 0.35f }, false);
	}
	return false;
}

bool GUI::MenuOptionPlayerList(std::string PlayerName, int BitFlags)
{
	if (Option("      " + PlayerName, "", BitFlags))
	{
		GUI::MoveMenu(Submenus::SelectedPlayer);
		return true;
	}

	char* CurrentOnlinePlayerPictureName = GameFunctions::ReturnOnlinePlayerPictureString(GameFunctions::ReturnPlayerIDFromPlayerName(PlayerName));

	VECTOR2 Position;
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Position = { GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount * SelectableHeight - 0.158f) };
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Position = { GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.158f };
	}
	DrawSpriterInGame(CurrentOnlinePlayerPictureName, CurrentOnlinePlayerPictureName, Position.x, Position.y, 0.02f, 0.03f, 0, 255, 255, 255, OnlinePlayerPictureTransparency);
	return false;
}

bool GUI::Toggle(std::string option, bool & TargetBool, std::string InformationText, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, TargetBool); }

	if (Option(option, InformationText, BitFlags))
	{
		TargetBool ^= 1;
		return true;
	}

	std::string ToggleString;
	TargetBool ? ToggleString = "ToggleOn" : ToggleString = "ToggleOff";

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		DrawSpriterInGame("Textures", ToggleString, GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * SelectableHeight - 0.159f), 0.025f, 0.025f, 0, 255, 255, 255, ToggleSelectableTransparency);
	}
	else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
	{
		DrawSpriterInGame("Textures", ToggleString, GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.159f, 0.025f, 0.025f, 0, 255, 255, 255, ToggleSelectableTransparency);
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		CheatFunctions::SaveOption(option, TargetBool ? "true" : "false", !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
	}
	return false;
}

bool GUI::Int(std::string option, int & _int, int min, int max, int step, std::string InformationText, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, _int); }

	if (Option(option, InformationText, BitFlags))
	{
		int KeyBoardInput = GameFunctions::DisplayKeyboardAndReturnInputInteger(CheatFunctions::ReturnNumberOfDigitsInValue(max), "Enter number");
		if (KeyBoardInput >= min && KeyBoardInput <= max)
		{
			_int = KeyBoardInput;
		}
		return true;
	}

	std::string Text;
	if (_int > min)
	{
		Text.append("< ");
	}
	Text.append(std::to_string(_int));
	if (_int < max)
	{
		Text.append(" >");
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (_int < 100)
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.075f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
		else if (_int < 999)
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.07f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
		else
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.06f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
	}
	else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
	{
		if (_int < 100)
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.075f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
		else if (_int < 999)
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.07f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
		else
		{
			DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.06f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.32f, 0.32f }, false, true);
		}
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		if (Controls::LeftPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			if (_int < max)
			{
				if (step == 1) { _int++; }
				else { _int = _int + step; }
			}
			if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true; }
		}
		if (Controls::RightPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			if (_int > min)
			{
				if (step == 1) { _int--; }
				else { _int = _int - step; }
			}
			if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true; }
		}

		CheatFunctions::SaveOption(option, std::to_string(_int), !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
	}
	return false;
}

bool GUI::Float(std::string option, float& _float, float min, float max, float steps, std::string InformationText, std::streamsize FloatPrecision, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, _float); }

	if (Option(option, InformationText, BitFlags))
	{
		return true;
	}

	bool IgnoreMinMax = min == 0.0f && max == 0.0f;
	if (GUI::optionCount == GUI::currentOption)
	{	
		CheatFunctions::SaveOption(option, std::to_string(_float), !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
		if (Controls::LeftPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			if (_float < max || IgnoreMinMax)
			{
				_float += steps;
			}
			if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true;  }
		}
		if (Controls::RightPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			if (_float > min || IgnoreMinMax)
			{
				_float -= steps;
			}
			if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true; }
		}
	}

	std::ostringstream DisplayFloat;
	DisplayFloat.precision(FloatPrecision);
	DisplayFloat << std::fixed << _float;
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		DrawTextInGame("< " + DisplayFloat.str() + " >", TextColorAndFont, {GUI::guiX + 0.08f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.172f}, {0.32f, 0.32f}, true, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		DrawTextInGame("< " + DisplayFloat.str() + " >", TextColorAndFont, { GUI::guiX + 0.08f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.172f }, { 0.32f, 0.32f }, true, true);
	}
	return false;
}

bool GUI::IntVector(std::string option, std::vector<int> Vector, int& position, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, "", BitFlags))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		int max = static_cast<int>(Vector.size()) - 1;
		int min = 0;
		if (Controls::LeftPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			position >= 1 ? position-- : position = max;
			return true;
		}
		if (Controls::RightPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			position < max ? position++ : position = min;
			return true;
		}
		CheatFunctions::SaveOption(option, std::to_string(position), !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		DrawTextInGame(std::to_string(Vector[position]), TextColorAndFont, { GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.5f, 0.5f }, true, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		DrawTextInGame(std::to_string(Vector[position]), TextColorAndFont, { GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.5f, 0.5f }, true, true);
	}
	return false;
}

bool GUI::FloatVector(std::string option, std::vector<float> Vector, int& position, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, "", BitFlags))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		CheatFunctions::SaveOption(option, std::to_string(position), !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
		size_t max = static_cast<int>(Vector.size()) - 1;
		int min = 0;
		if (Controls::LeftPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			position >= 1 ? position-- : position = static_cast<int>(max);
			return true;
		}
		if (Controls::RightPressed && !(BitFlags & SELECTABLE_DISABLED))
		{
			position < max ? position++ : position = static_cast<int>(min);
			return true;
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		DrawTextInGame(std::to_string(Vector[position]), TextColorAndFont, { GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.5f, 0.5f }, true, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		DrawTextInGame(std::to_string(Vector[position]), TextColorAndFont, { GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.5f, 0.5f }, true, true);
	}
	return false;
}

bool GUI::StringVector(std::string option, std::vector<std::string> Vector, int& position, std::string InformationText, int BitFlags)
{
	if (!(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED)) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, InformationText, BitFlags))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		CheatFunctions::SaveOption(option, std::to_string(position), !(BitFlags & SELECTABLE_DISABLE_SAVE) && !(BitFlags & SELECTABLE_DISABLED) ? true : false);
		if (Controls::LeftPressed)
		{
			if (position < Vector.size() - 1)
			{
				position++;
				if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true; }
			}
		}
		if (Controls::RightPressed)
		{
			if (position > 0)
			{
				position--;
				if (BitFlags & SELECTABLE_RETURN_VALUE_CHANGE) { return true; }
			}
		}
	}

	std::string Text;
	if (position > 0)
	{
		Text.append("< ");
	}
	Text.append(Vector[position]);
	std::stringstream Total;
	Total << " [" << position + 1 << "/" << Vector.size() << "]";
	Text.append(Total.str());
	
	if (position < Vector.size() - 1)
	{
		Text.append(" >");
	}
	
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions) 
	{
		DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.075f, GUI::guiY + GUI::optionCount * SelectableHeight - 0.174f }, { 0.35f, 0.35f }, true, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		DrawTextInGame(Text, TextColorAndFont, { GUI::guiX + 0.075f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * SelectableHeight - 0.174f }, { 0.35f, 0.35f }, true, true);
	}
	return false;
}

void GUI::MenuGUIBottom()
{
	if (GUI::menuLevel > 0)
	{
		GUI::TotalOptionsCount = GUI::optionCount;
		float OptionCountPositionX = GUI::guiX - 0.088f;
		float BuildNumberPositionX = GUI::guiX + 0.085f;
		float OptionCountAndBuildNumberY, RectY, LogoSmall;
		if (GUI::optionCount >= GUI::maxVisOptions)
		{
			OptionCountAndBuildNumberY = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.172f);
			RectY = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.1585f);
			LogoSmall = GUI::guiY + ((GUI::maxVisOptions + 1) * SelectableHeight - 0.159f);
		}
		else if (GUI::optionCount > 0)
		{
			OptionCountAndBuildNumberY = GUI::guiY + (GUI::optionCount + 1) * SelectableHeight - 0.172f;
			RectY = GUI::guiY + (GUI::optionCount + 1) * SelectableHeight - 0.1585f;
			LogoSmall = GUI::guiY + ((GUI::optionCount + 1) * SelectableHeight - 0.159f);
		}

		if (GUI::currentOptionVisible != 0 && GUI::optionCountVisible != 0)
		{
			DrawTextInGame(std::to_string(GUI::currentOptionVisible) + "/" + std::to_string(GUI::optionCountVisible), TextColorAndFont, { OptionCountPositionX, OptionCountAndBuildNumberY }, { 0.30f, 0.30f }, true);
		}
		DrawTextInGame(CHEAT_BUILD_NUMBER, TextColorAndFont, { BuildNumberPositionX, OptionCountAndBuildNumberY }, { 0.30f, 0.30f }, true);
		DrawRectInGame({ 0, 0, 0, TitleAndEndTransparency }, { GUI::guiX, RectY }, { GUI::guiWidth, SelectableHeight });
		DrawSpriterInGame("Textures", "LogoSmall", GUI::guiX, LogoSmall, 0.030f, 0.045f, 0, GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b, EndSmallLogoTransparency);
	}
}

void GUI::MoveMenu(void* Submenu)
{
	GUI::menusArray[GUI::menuLevel] = GUI::currentMenu;
	GUI::optionsArray[GUI::menuLevel] = GUI::currentOption;
	GUI::menuLevel++;
	GUI::currentMenu = Submenu;
	GUI::currentOption = 1;
}

void GUI::CloseMenuGUI()
{
	if (CheatFeatures::CursorGUINavigationEnabled) { GameFunctions::EnableDisableCursorGUINavigation(); }
	GUI::PreviousMenu = GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel = 0;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
}

void GUI::BackMenu()
{
	if (GUI::currentMenu == GUI::Submenus::Home)
	{
		CloseMenuGUI();
	}
	else
	{
		GUI::PreviousMenu = GUI::currentMenu;
		GUI::PreviousMenuLevel = GUI::menuLevel;
		GUI::previousOption = GUI::currentOption;
		GUI::menuLevel--;
		GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
		GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
	}
}

void GUI::AddPlayerInfoBoxTextEntry(std::string text, int Row1, int Row2, int Row3, int Row4)
{
	if (GUI::guiX < 0.54f)
	{		
		if (Row1 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX + 0.110f, GUI::guiY + (Row1 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX + 0.205f, GUI::guiY + (Row2 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX + 0.295f, GUI::guiY + (Row3 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX + 0.365f, GUI::guiY + (Row4 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
	}
	else
	{
		if (Row1 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX - 0.420f, GUI::guiY + (Row1 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX - 0.340f, GUI::guiY + (Row2 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX - 0.260f, GUI::guiY + (Row3 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			DrawTextInGame(text, TextColorAndFont, { GUI::guiX - 0.165f, GUI::guiY + (Row4 * 0.020f) - 0.158f }, { 0.30f, 0.30f }, false);
		}
	}
}

void GUI::LoadTheme(std::string ThemeFileName, bool StartUp)
{
	if (!CheatFunctions::FileOrDirectoryExists(CheatFunctions::ReturnThemeFilePath(ThemeFileName))) 
	{ 
		GameFunctions::MinimapNotification("Requested Theme does not exist. Auto load entry removed from config file."); 
		CheatFunctions::IniFileRemoveKey(CheatFunctions::ReturnConfigFilePath(), "Settings", "Active Theme");
		return;
	}

	GUI::CurrentTheme = ThemeFileName;
	try
	{
		GUI::guiX = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "menu_gui_x"));
		GUI::guiY = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "menu_gui_y"));
		GUI::SelectableInfoBoxX = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_information_box_x"));
		GUI::SelectableInfoBoxY = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_information_box_y"));
		GUI::SelectableHeight = std::stof(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_height"));

		GUI::ShowHeaderTexture = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Header", "header_texture"));
		GUI::ShowHeaderBackground = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Header", "header_background"));
	
		CheatFeatures::RGBDiscoBool = CheatFunctions::StringToBool(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "rgb_disco"));

		if (!CheatFeatures::RGBDiscoBool)
		{
			GUI::PrimaryColor.r = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_r"));
			GUI::PrimaryColor.g = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_g"));
			GUI::PrimaryColor.b = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_b"));

			GUI::TextColorAndFont.r = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_r"));
			GUI::TextColorAndFont.g = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_g"));
			GUI::TextColorAndFont.b = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_b"));
		}

		GUI::TextColorAndFont.f = CheatFunctions::StringToInt(CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Font", "text_font"));
	}
	catch (...) {}

	//Check Theme File Version
	if (CheatFunctions::IniFileReturnKeyValueAsString(CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Theme", "theme_file_version") != "2.1")
	{
		GameFunctions::SubtitleNotification("The loaded Theme is outdated. Please resave it", 5000);
	}

	//Save New Active Theme Name To Config File
	if (!StartUp) 
	{
		CheatFunctions::IniFileWriteString(GUI::CurrentTheme, CheatFunctions::ReturnConfigFilePath(), "Settings", "Active Theme");
		GameFunctions::MinimapNotification("Theme Loaded"); 
	}
}

void GUI::DeleteLoadedTheme()
{
	remove(CheatFunctions::StringToChar(CheatFunctions::ReturnThemeFilePath(CurrentTheme)));
	CheatFunctions::IniFileRemoveKey(CheatFunctions::ReturnConfigFilePath(), "Settings", "Active Theme");
	GUI::CurrentTheme.clear();
	GUI::currentOption = 1;
	GameFunctions::MinimapNotification("Theme Removed");
}

void GUI::SaveTheme(std::string ThemeFileName)
{
	CheatFunctions::IniFileWriteString("2.1", CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Theme", "theme_file_version");

	CheatFunctions::IniFileWriteString(std::to_string(GUI::guiX), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "menu_gui_x");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::guiY), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "menu_gui_y");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableInfoBoxX), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_information_box_x");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableInfoBoxY), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_information_box_y");
	CheatFunctions::IniFileWriteString(std::to_string(GUI::SelectableHeight), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Positioning", "selectable_height");

	CheatFunctions::WriteBoolToIni(GUI::ShowHeaderTexture, CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Header", "header_texture");
	CheatFunctions::WriteBoolToIni(GUI::ShowHeaderBackground, CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Header", "header_background");

	CheatFunctions::WriteBoolToIni(CheatFeatures::RGBDiscoBool, CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "rgb_disco");
	if (!CheatFeatures::RGBDiscoBool)
	{
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.r), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_r");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.g), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_g");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::PrimaryColor.b), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "primary_color_b");

		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.r), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_r");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.g), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_g");
		CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.b), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Color", "text_color_b");
	}

	CheatFunctions::IniFileWriteString(std::to_string(GUI::TextColorAndFont.f), CheatFunctions::ReturnThemeFilePath(ThemeFileName), "Font", "text_font");

	GameFunctions::MinimapNotification("Theme Saved");
}

static FileRegister RegisterTextureFile = (FileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(RegisterTextureFile)>());
void GUI::LoadTextureFile()
{
	LogFunctions::Message("Loading Texture File");
	remove(CheatFunctions::StringToChar(CheatFunctions::ReturnTextureFilePath()));

	// Find and load the resource
	HRSRC hResource = FindResourceA(CheatModuleHandle, MAKEINTRESOURCEA(140), "CHEAT_DATA");
	if (!hResource) { goto Error; }
	HGLOBAL hFileResource = LoadResource(CheatModuleHandle, hResource);
	if (!hFileResource) { goto Error; }

	// Open and map this to a disk file
	LPVOID lpFile = LockResource(hFileResource);
	DWORD dwSize = SizeofResource(CheatModuleHandle, hResource);

	// Open the file and filemap
	HANDLE hFile = CreateFileA(CheatFunctions::StringToChar(CheatFunctions::ReturnTextureFilePath()), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
	if (!hFileMap) { goto Error; }

	LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (!lpAddress) { goto Error; }

	// Write the file
	CopyMemory(lpAddress, lpFile, dwSize);

	// Un-map the file and close the handles
	UnmapViewOfFile(lpAddress);
	CloseHandle(hFileMap);
	CloseHandle(hFile);

	int textureID;
	if (CheatFunctions::FileOrDirectoryExists(CheatFunctions::ReturnTextureFilePath()))
	{
		RegisterTextureFile(&textureID, CheatFunctions::StringToChar(CheatFunctions::ReturnTextureFilePath()), true, "Textures.ytd", false);
		return;
	}
	else
	{
		goto Error;
	}

	//Error
Error:
	GameFunctions::MinimapNotification("~r~Failed to load Texture");
	LogFunctions::DebugMessage("Failed to load Texture");
}

void GUI::DrawTextInGame(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool Outline)
{
	if (!GUI::HideGUIElements)
	{
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		UI::SET_TEXT_FONT(rgbaf.f);
		if (Outline) { UI::SET_TEXT_OUTLINE(); }
		UI::SET_TEXT_SCALE(size.w, size.h);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(CheatFunctions::StringToChar(text));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
	}
}

void GUI::DrawSpriterInGame(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GUI::HideGUIElements)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(CheatFunctions::StringToChar(Streamedtexture)))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(CheatFunctions::StringToChar(Streamedtexture.c_str()), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE(CheatFunctions::StringToChar(Streamedtexture), CheatFunctions::StringToChar(textureName), x, y, width, height, rotation, r, g, b, a);
		}
	}
}

void GUI::DrawRectInGame(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	if (!GUI::HideGUIElements)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
	}
}