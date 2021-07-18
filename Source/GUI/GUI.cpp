#include "../Header/Main.h"

float Cheat::GUI::guiX					= 0.11f;
float Cheat::GUI::guiY					= 0.30f;
float Cheat::GUI::guiWidth				= 0.21f; //TODO: Text Scaling not implemented
bool Cheat::GUI::ControlsDisabled		= false; //All cheat input is ignored when True
bool Cheat::GUI::selectPressed			= false;
bool Cheat::GUI::leftPressed			= false;
bool Cheat::GUI::rightPressed			= false;
bool Cheat::GUI::ShowHeaderBackground	= true;
bool Cheat::GUI::ShowHeaderGUI			= true;
bool Cheat::GUI::ShowHeaderGlare		= true;
bool Cheat::GUI::HideGUIElements		= false; //Prevents all GUI elements from being visible when True
bool Cheat::GUI::CheatGUIHasBeenOpened	= false;
bool Cheat::GUI::CurrentOptionIsSavable	= false;
bool Cheat::GUI::RestorePreviousSubmenu = true;
std::string OptionInformationText;
std::string Cheat::GUI::CurrentTheme;
int Cheat::GUI::maxVisOptions			= 10;
int Cheat::GUI::currentOption			= 0;
int Cheat::GUI::currentOptionMenuBottom = 0;
int Cheat::GUI::previousOption			= 0;
int Cheat::GUI::optionCount				= 0;
int Cheat::GUI::optionCountMenuBottom	= 0;
int Cheat::GUI::TotalOptionsCount		= 0;
int Cheat::GUI::menuLevel				= 0;
SubMenus Cheat::GUI::PreviousMenu		= NOMENU;
SubMenus Cheat::GUI::currentMenu;
int Cheat::GUI::PreviousMenuLevel;
int Cheat::GUI::optionsArray			[1000];
SubMenus Cheat::GUI::menusArray			[1000];
std::vector <std::string> Cheat::GUI::ThemeFilesVector;
RGBAF Cheat::GUI::count					{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::titleText				{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::optionText			{ 255, 255, 255, 255, FontChaletLondon };
RGBAF Cheat::GUI::breakText				{ 255, 255, 255, 255, FontChaletLondon };
RGBA Cheat::GUI::titleRect				{ 0, 0, 255, 255 };
RGBA Cheat::GUI::MainTitleRect			{ 0, 0, 0, 255 };
RGBA Cheat::GUI::headerRect				{ 0, 0, 255, 200 };                      
RGBA Cheat::GUI::optionRect				{ 0, 0, 0, 255 };
RGBA Cheat::GUI::MenuBackgroundRect		{ 0, 0, 0, 220 }; 
RGBA Cheat::GUI::MenuBottomRect			{ 0, 0, 0, 255 };
RGBA Cheat::GUI::scroller				{ 0, 0, 255, 255 };
RGBA Cheat::GUI::TopAndBottomLine		{ 0, 0, 255, 255 };

int Cheat::GUI::keyPressDelay				= 200;
int Cheat::GUI::keyPressPreviousTick		= GetTickCount64();
int Cheat::GUI::OpenGUIKey					= VK_F4;
int Cheat::GUI::GUINavigationKey			= VK_F5;
int Cheat::GUI::SaveItemKey					= VK_F12;


void Cheat::GUI::Title(std::string title)
{
	GUI::Drawing::Text(title, { GUI::titleText }, { GUI::guiX, GUI::guiY - 0.17f }, { 0.50f, 0.35f }, true);
	if (Cheat::GUI::ShowHeaderBackground) { GUI::Drawing::Rect(GUI::headerRect, { Cheat::GUI::guiX, GUI::guiY - 0.208f }, { Cheat::GUI::guiWidth, 0.084f }); }
	if (GUI::ShowHeaderGlare) { GUI::Drawing::DrawScaleform(Cheat::GUI::guiX + .330f, GUI::guiY + 0.162f, 1.0f, 0.912f, 255, 255, 255); }
	if (Cheat::GUI::ShowHeaderGUI) { Cheat::GUI::Drawing::Spriter("Textures", "HeaderDefaultTransparent", Cheat::GUI::guiX, GUI::guiY - 0.208f, Cheat::GUI::guiWidth, 0.084f, 0, 255, 255, 255, 255); }
	GUI::Drawing::Rect(GUI::MainTitleRect, { Cheat::GUI::guiX, GUI::guiY - 0.154f }, { Cheat::GUI::guiWidth, 0.023f });
	GUI::Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY - 0.142f }, { Cheat::GUI::guiWidth, 0.002f });

	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(false);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);

	//Control Buttons
	if (!GUI::HideGUIElements)
	{
		std::string SaveOptionKeyString = "Press " + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::SaveItemKey) + " to save selected option";
		std::string CloseGUIString = "Press " + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::OpenGUIKey) + " to close GUI";
		std::string CursorNavigationString;
		if (Cheat::CheatFeatures::CursorGUINavigationEnabled) { CursorNavigationString = "Press " + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::GUINavigationKey) + " to disable cursor"; }
		else { CursorNavigationString = "Press " + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::GUINavigationKey) + " to enable cursor"; }
		Cheat::GameFunctions::InstructionalKeysInit();
		Cheat::GameFunctions::InstructionsAdd(CheatFunctions::StringToChar(CloseGUIString), 80);
		Cheat::GameFunctions::InstructionsAdd(CheatFunctions::StringToChar(CursorNavigationString), 80);
		if (GUI::CurrentOptionIsSavable) { Cheat::GameFunctions::InstructionsAdd(CheatFunctions::StringToChar(SaveOptionKeyString), 80); }
		Cheat::GameFunctions::InstructionsAdd("Back", 136);
		Cheat::GameFunctions::InstructionsAdd("Up/Down", 10);
		Cheat::GameFunctions::InstructionsAdd("Change Value", 46);
		Cheat::GameFunctions::InstructionsAdd("Select", 141);
		Cheat::GameFunctions::InstructionsEnd();
	}
}

bool Cheat::GUI::Option(std::string option, std::string InformationText, bool Disabled)
{
	GUI::optionCount++;
	GUI::optionCountMenuBottom++;
	bool OnCurrent = GUI::currentOption == GUI::optionCount ? true : false;
	int OptionCountDifference = GUI::optionCount - GUI::optionCountMenuBottom;
	VECTOR2 TextPosition, RectPosition;
	RGBA RectColor;

	if (Disabled) { option.append(" (Disabled)"); }
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		TextPosition = { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f };
		RectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f };
		OnCurrent ? RectColor = GUI::scroller : RectColor = GUI::MenuBackgroundRect;
		GUI::Drawing::Text(option, GUI::optionText, TextPosition, { 0.35f, 0.35f }, false);
		GUI::Drawing::Rect(RectColor, RectPosition, { Cheat::GUI::guiWidth, 0.035f });
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		TextPosition = { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f };
		RectPosition = { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f };
		OnCurrent ? RectColor = GUI::scroller : RectColor = GUI::MenuBackgroundRect;
		GUI::Drawing::Text(option, GUI::optionText, TextPosition, { 0.35f, 0.35f }, false);
		GUI::Drawing::Rect(RectColor, RectPosition, { Cheat::GUI::guiWidth, 0.035f });
	}
	if (OnCurrent)
	{
		GUI::currentOptionMenuBottom = GUI::optionCount - OptionCountDifference;
		GUI::CurrentOptionIsSavable = false;
		GUI::previousOption = GUI::currentOption;
		if (InformationText == "") { OptionInformationText.clear(); }
		else { OptionInformationText = InformationText; }
		if (GUI::selectPressed)
		{
			if (GUI::SelectableHandler(Disabled))
			{
				return true;
			}
		}
	}
	return false;
}

bool Cheat::GUI::VehicleOption(std::string option, std::string ModelName)
{
	GUI::optionCount++;
	GUI::optionCountMenuBottom++;
	bool OnCurrent = GUI::currentOption == GUI::optionCount ? true : false;
	int OptionCountDifference = GUI::optionCount - GUI::optionCountMenuBottom;
	if (OnCurrent) { GUI::currentOptionMenuBottom = GUI::optionCount - OptionCountDifference; }

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
		GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		OnCurrent ? GUI::Drawing::Rect(GUI::scroller, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f }) : NULL;
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text(option, GUI::optionText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false); // 0.45 0.45
		GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		OnCurrent ? GUI::Drawing::Rect(GUI::scroller, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f }) : NULL;
	}
	if (OnCurrent)
	{
		std::string VehiclePreviewDictName, VehiclePreviewName;
		std::transform(ModelName.begin(), ModelName.end(), ModelName.begin(), tolower);
		VehiclePreviewDictName = "Textures";
		VehiclePreviewName	   = "NoVehiclePreviewAvailable";

		for (int i = 0; i < Cheat::GameArrays::VehicleModelPictures.size(); i++)
		{
			if (Cheat::GameArrays::VehicleModelPictures[i].PreviewName == ModelName)
			{ 
				VehiclePreviewDictName	= CheatFunctions::StringToChar(Cheat::GameArrays::VehicleModelPictures[i].DictName);
				VehiclePreviewName		= CheatFunctions::StringToChar(Cheat::GameArrays::VehicleModelPictures[i].PreviewName);
			}
		}
		
		if (Cheat::CheatFeatures::ShowVehicleInfoAndPreview)
		{
			std::string ModelNameDrawingText = "Model Name: " + ModelName;
			std::ostringstream ModelMaxSpeed;
			if (Cheat::CheatFeatures::UseKMH)
			{
				ModelMaxSpeed << "Max Speed: " << Cheat::GameFunctions::MSToKMH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))) << " KM/H";
			}
			else
			{
				ModelMaxSpeed << "Max Speed: " << Cheat::GameFunctions::MSToMPH(VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ModelName)))) << " MP/H";
			}

			if (Cheat::GUI::guiX < 0.71f)
			{
				GUI::Drawing::Text("Vehicle Info & Preview", GUI::count, { Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.168f }, { 0.50f, 0.35f }, true);
				GUI::Drawing::Text(ModelNameDrawingText, GUI::count, { Cheat::GUI::guiX + 0.111f,  GUI::guiY + 0.008f }, { 0.45f, 0.30f }, false);
				GUI::Drawing::Text(ModelMaxSpeed.str(), GUI::count, { Cheat::GUI::guiX + 0.111f, GUI::guiY + 0.026f }, { 0.45f, 0.30f }, false);
				GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.056f }, { 0.16f, 0.22f });
				GUI::Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Cheat::GUI::guiX + 0.187f, GUI::guiY - 0.068f, 0.15f, 0.15f, 0.f, 255, 255, 255, 255);
			}
			else
			{
				GUI::Drawing::Text("Vehicle Info & Preview", GUI::count, { Cheat::GUI::guiX - 0.187f,GUI::guiY - 0.168f }, { 0.50f, 0.35f }, true);
				GUI::Drawing::Text(ModelNameDrawingText, GUI::count, { Cheat::GUI::guiX - 0.262f, GUI::guiY + 0.008f }, { 0.45f, 0.30f }, false);
				GUI::Drawing::Text(ModelMaxSpeed.str(), GUI::count, { Cheat::GUI::guiX - 0.262f, GUI::guiY + 0.026f }, { 0.45f, 0.30f }, false);
				GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX - 0.187f, GUI::guiY - 0.056f }, { 0.16f, 0.22f });
				GUI::Drawing::Spriter(VehiclePreviewDictName, VehiclePreviewName, Cheat::GUI::guiX - 0.187f, GUI::guiY - 0.068f, 0.15f, 0.15f, 0.f, 255, 255, 255, 255);
			}
		}
		if (GUI::selectPressed)
		{
			return true;
		}
	}
	return false;
}

bool Cheat::GUI::Break(std::string option, bool TextCentered)
{
	GUI::optionCount++;

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (TextCentered) { GUI::Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		else { GUI::Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		if (TextCentered) { GUI::Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		else { GUI::Drawing::Text(option, GUI::breakText, { Cheat::GUI::guiX - 0.100f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, TextCentered); }
		GUI::Drawing::Rect(GUI::MenuBackgroundRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions))*0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
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
	}
	return false;
}

bool Cheat::GUI::MenuOption(std::string option, SubMenus newSub, bool Disabled)
{
	if (Option(option, "", Disabled))
	{
		GUI::MoveMenu(newSub);
		return true;
	}
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(">", GUI::optionText, { Cheat::GUI::guiX + 0.09f, GUI::guiY + (GUI::optionCount) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
	}
	else if (GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions) && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text(">", GUI::optionText, { Cheat::GUI::guiX + 0.09f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, false);
	}
	return false;
}

bool Cheat::GUI::MenuOptionPlayerList(std::string PlayerName, SubMenus newSub)
{
	if (Option("      " + PlayerName, ""))
	{
		GUI::MoveMenu(newSub);
		return true;
	}

	char* CurrentOnlinePlayerPictureName = Cheat::GameFunctions::ReturnOnlinePlayerPictureString(GameFunctions::ReturnPlayerIDFromPlayerName(PlayerName));

	VECTOR2 Position;
	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		Position = { Cheat::GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f) };
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		Position = { Cheat::GUI::guiX - 0.093f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.160f };
	}
	GUI::Drawing::Spriter(CurrentOnlinePlayerPictureName, CurrentOnlinePlayerPictureName, Position.x, Position.y, 0.02f, 0.03f, 0, 255, 255, 255, 255);
	return false;
}

bool Cheat::GUI::Toggle(std::string option, bool & b00l, std::string InformationText, bool IsSavable, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, b00l); }

	if (Option(option, InformationText, Disabled))
	{
		b00l ^= 1;
		return true;
	}

	std::string ToggleTextureNameEnabled, ToggleTextureNameDisabled;
	RGBA ToggleColorEnabled, ToggleColorDisabled;
	if (Cheat::CheatFeatures::BoolOptionVectorPosition == 0)
	{
		ToggleTextureNameEnabled = "shop_box_tick";
		ToggleTextureNameDisabled = "shop_box_blank";
		ToggleColorEnabled = { 255, 255, 255, 255 };
		ToggleColorDisabled = ToggleColorEnabled;
	}
	else if (Cheat::CheatFeatures::BoolOptionVectorPosition == 1)
	{
		ToggleTextureNameEnabled = "common_medal";
		ToggleTextureNameDisabled = ToggleTextureNameEnabled;
		ToggleColorEnabled = { 43, 255, 0, 255 };
		ToggleColorDisabled = { 255, 0, 0, 255 };
	}

	if (b00l)
	{
		if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
		{
			GUI::Drawing::Spriter("commonmenu", ToggleTextureNameEnabled, Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.03f, 0.05f, 0, ToggleColorEnabled.r, ToggleColorEnabled.g, ToggleColorEnabled.b, ToggleColorEnabled.a);
		}
		else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
		{
			GUI::Drawing::Spriter("commonmenu", ToggleTextureNameEnabled, Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.160f, 0.03f, 0.05f, 0, ToggleColorEnabled.r, ToggleColorEnabled.g, ToggleColorEnabled.b, ToggleColorEnabled.a);
		}
	}
	else
	{
		if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
		{
			GUI::Drawing::Spriter("commonmenu", ToggleTextureNameDisabled, Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount * 0.035f - 0.160f), 0.03f, 0.05f, 0, ToggleColorDisabled.r, ToggleColorDisabled.g, ToggleColorDisabled.b, ToggleColorDisabled.a);
		}
		else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
		{
			GUI::Drawing::Spriter("commonmenu", ToggleTextureNameDisabled, Cheat::GUI::guiX + 0.090f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.160f, 0.03f, 0.05f, 0, ToggleColorDisabled.r, ToggleColorDisabled.g, ToggleColorDisabled.b, ToggleColorDisabled.a);
		}
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		CheatFunctions::SaveOption(option, b00l ? "true" : "false", IsSavable && !Disabled ? true : false);
	}
	return false;
}

bool Cheat::GUI::Int(std::string option, int & _int, int min, int max, int step, bool IsSavable, std::string InformationText, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, _int); }

	if (Option(option, InformationText, Disabled))
	{
		int KeyBoardInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInputInteger(CheatFunctions::ReturnNumberOfDigitsInValue(max));
		if (KeyBoardInput >= min && KeyBoardInput <= max)
		{
			_int = KeyBoardInput;
		}
		return true;
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		if (_int < 100)
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.075f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.07f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.06f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
	}
	else if ((GUI::optionCount > (GUI::currentOption - GUI::maxVisOptions)) && GUI::optionCount <= GUI::currentOption)
	{
		if (_int < 100)
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.075f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else if (_int < 999)
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.07f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
		else
		{
			GUI::Drawing::Text("< " + std::to_string(_int) + " >", GUI::optionText, { Cheat::GUI::guiX + 0.06f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.32f, 0.32f }, false);
		}
	}

	if (GUI::optionCount == GUI::currentOption)
	{
		if (GUI::leftPressed && !Disabled)
		{
			if (_int < max)
			{
				if (step == 1) { _int++; }
				else { _int = _int + step; }
			}
			return true;
		}
		if (GUI::rightPressed && !Disabled)
		{
			if (_int > min)
			{
				if (step == 1) { _int--; }
				else { _int = _int - step; }
			}
			return true;
		}

		CheatFunctions::SaveOption(option, std::to_string(_int), IsSavable && !Disabled ? true : false);
	}
	return false;
}

bool Cheat::GUI::Float(std::string option, float & _float, float min, float max, float steps, bool ReturnTrueWithValueChange, bool IsSavable, std::string InformationText, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, _float); }

	if (Option(option, InformationText, Disabled))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{	
		CheatFunctions::SaveOption(option, std::to_string(_float), IsSavable && !Disabled ? true : false);
		if (GUI::leftPressed && !Disabled)
		{
			if (_float < max)
			{
				_float += steps;
			}
			if (ReturnTrueWithValueChange) { return true;  }
		}
		if (GUI::rightPressed && !Disabled)
		{
			if (_float > min)
			{
				_float -= steps;
			}
			if (ReturnTrueWithValueChange) { return true; }
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(std::to_string(_float), GUI::optionText, { Cheat::GUI::guiX + 0.08f, GUI::guiY + GUI::optionCount * 0.035f - 0.172f }, { 0.32f, 0.32f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text(std::to_string(_float), GUI::optionText, { Cheat::GUI::guiX + 0.08f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.172f }, { 0.32f, 0.32f }, true);
	}
	return false;
}

bool Cheat::GUI::IntVector(std::string option, std::vector<int> Vector, int& position, bool IsSavable, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, "", Disabled))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		int max = static_cast<int>(Vector.size()) - 1;
		int min = 0;
		if (GUI::leftPressed && !Disabled)
		{
			position >= 1 ? position-- : position = max;
			return true;
		}
		if (GUI::rightPressed && !Disabled)
		{
			position < max ? position++ : position = min;
			return true;
		}
		CheatFunctions::SaveOption(option, std::to_string(position), IsSavable && !Disabled ? true : false);
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(std::to_string(Vector[position]), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text(std::to_string(Vector[position]), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	return false;
}

bool Cheat::GUI::FloatVector(std::string option, std::vector<float> Vector, int& position, bool IsSavable, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, "", Disabled))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		CheatFunctions::SaveOption(option, std::to_string(position), IsSavable && !Disabled ? true : false);
		size_t max = static_cast<int>(Vector.size()) - 1;
		int min = 0;
		if (GUI::leftPressed && !Disabled)
		{
			position >= 1 ? position-- : position = static_cast<int>(max);
			return true;
		}
		if (GUI::rightPressed && !Disabled)
		{
			position < max ? position++ : position = static_cast<int>(min);
			return true;
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(std::to_string(Vector[position]), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text(std::to_string(Vector[position]), GUI::optionText, { Cheat::GUI::guiX + 0.068f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.5f, 0.5f }, true);
	}
	return false;
}
bool Cheat::GUI::StringVector(std::string option, std::vector<std::string> Vector, int & position, std::string InformationText, bool IsSavable, bool Disabled)
{
	if (IsSavable && !Disabled) { CheatFunctions::LoadConfigOption(option, position); }

	if (Option(option, InformationText, Disabled))
	{
		return true;
	}

	if (GUI::optionCount == GUI::currentOption) 
	{
		CheatFunctions::SaveOption(option, std::to_string(position), IsSavable && !Disabled ? true : false);
		size_t max = static_cast<int>(Vector.size()) - 1;
		int min = 0;
		if (GUI::leftPressed) 
		{
			position >= 1 ? position-- : position = static_cast<int>(max);
			return true;
		}
		if (GUI::rightPressed) 
		{
			position < max ? position++ : position = static_cast<int>(min);
			return true;
		}
	}

	if (GUI::currentOption <= GUI::maxVisOptions && GUI::optionCount <= GUI::maxVisOptions) 
	{
		GUI::Drawing::Text("< " + (Vector[position]) + "", GUI::optionText, { Cheat::GUI::guiX + 0.055f, GUI::guiY + GUI::optionCount * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
	}
	else if (GUI::optionCount > GUI::currentOption - GUI::maxVisOptions && GUI::optionCount <= GUI::currentOption)
	{
		GUI::Drawing::Text("< " + (Vector[position]) + "", GUI::optionText, { Cheat::GUI::guiX + 0.055f, GUI::guiY + (GUI::optionCount - (GUI::currentOption - GUI::maxVisOptions)) * 0.035f - 0.175f }, { 0.35f, 0.35f }, true);
	}
	return false;
}

void Cheat::GUI::End()
{
	GUI::TotalOptionsCount = GUI::optionCount;
	int OptionCount = GUI::optionCount;
	if (OptionCount >= GUI::maxVisOptions)
	{
		GUI::Drawing::Text(std::to_string(GUI::currentOptionMenuBottom) + " / " + std::to_string(GUI::optionCountMenuBottom), GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.172f) }, { 0.30f, 0.30f }, true);
		GUI::Drawing::Text(CHEAT_BUILD_NUMBER, GUI::count, { Cheat::GUI::guiX + 0.085f, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.172f) }, { 0.30f, 0.30f }, true);
		GUI::Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.1585f) }, { Cheat::GUI::guiWidth, 0.035f });
		GUI::Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.1765f) }, { Cheat::GUI::guiWidth, 0.002f });
		GUI::Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 1) * 0.035f - 0.160f), 0.020f, 0.035f, 180, GUI::TopAndBottomLine.r, GUI::TopAndBottomLine.g, GUI::TopAndBottomLine.b, GUI::TopAndBottomLine.a);

		if (!OptionInformationText.empty()) 
		{
			GUI::Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.161f) }, { Cheat::GUI::guiWidth, 0.030f }); // Option Info Rect
			GUI::Drawing::Spriter("shared", "info_icon_32", { Cheat::GUI::guiX - 0.095f }, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.168f), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			GUI::Drawing::Text(OptionInformationText, GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + ((GUI::maxVisOptions + 2) * 0.035f - 0.179f) }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
	else if (OptionCount > 0)
	{
		GUI::Drawing::Text(std::to_string(GUI::currentOptionMenuBottom) + " / " + std::to_string(GUI::optionCountMenuBottom), GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.172f }, { 0.30f, 0.30f }, true);
		GUI::Drawing::Text(CHEAT_BUILD_NUMBER, GUI::count, { Cheat::GUI::guiX + 0.085f, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.172f }, { 0.30f, 0.30f }, true);
		GUI::Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.1585f }, { Cheat::GUI::guiWidth, 0.035f });
		GUI::Drawing::Rect(GUI::TopAndBottomLine, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 1) * 0.035f - 0.1765f }, { Cheat::GUI::guiWidth, 0.002f });
		GUI::Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Cheat::GUI::guiX, GUI::guiY + ((GUI::optionCount + 1) * 0.035f - 0.160f), 0.020f, 0.035f, 180, GUI::TopAndBottomLine.r, GUI::TopAndBottomLine.g, GUI::TopAndBottomLine.b, GUI::TopAndBottomLine.a);

		if (!OptionInformationText.empty())
		{
			GUI::Drawing::Rect(GUI::MenuBottomRect, { Cheat::GUI::guiX, GUI::guiY + (GUI::optionCount + 2) * 0.035f - 0.161f }, { Cheat::GUI::guiWidth, 0.030f }); // Option Info Rect
			GUI::Drawing::Spriter("shared", "info_icon_32", { Cheat::GUI::guiX - 0.095f }, GUI::guiY + ((GUI::optionCount + 2) * 0.035f - 0.168), 0.020f, 0.035f, 0, 255, 255, 255, 255); // Option Info Info Spriter
			GUI::Drawing::Text(OptionInformationText, GUI::count, { Cheat::GUI::guiX - 0.085f, GUI::guiY + (GUI::optionCount + 2) * 0.035f - 0.179f }, { 0.30f, 0.30f }, false); // Option Info Text
		}
	}
}

void Cheat::GUI::ControlsLoop()
{
	if (!ControlsDisabled)
	{
		GUI::selectPressed = false;
		GUI::leftPressed = false;
		GUI::rightPressed = false;

		if (GetTickCount64() - GUI::keyPressPreviousTick > GUI::keyPressDelay)
		{
			if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(GUI::OpenGUIKey))
			{
				Cheat::GUI::CheatGUIHasBeenOpened = true;
				if (GUI::menuLevel == 0)
				{
					if (GUI::PreviousMenu != NOMENU && Cheat::GUI::RestorePreviousSubmenu)
					{
						GUI::MoveMenu(GUI::PreviousMenu);
						GUI::menuLevel = GUI::PreviousMenuLevel;
						GUI::currentOption = GUI::previousOption;
					}
					else
					{
						GUI::MoveMenu(SubMenus::MainMenu);
					}
				}
				else
				{
					if (Cheat::CheatFeatures::CursorGUINavigationEnabled) 
					{ 
						Cheat::GameFunctions::EnableDisableCursorGUINavigation(); 
					}
					GUI::CloseGUI();
				}

				Cheat::GameFunctions::PlayFrontendSoundDefault("SELECT");
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD0))
			{
				if (GUI::menuLevel > 0) 
				{
					GUI::BackMenu(); 
					Cheat::GameFunctions::PlayFrontendSoundDefault("BACK"); 
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD8))
			{
				GUI::currentOption > 1 ? GUI::currentOption-- : GUI::currentOption = GUI::optionCount;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD2))
			{
				GUI::currentOption < GUI::optionCount ? GUI::currentOption++ : GUI::currentOption = 1;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD6))
			{
				GUI::leftPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD4))
			{
				GUI::rightPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD5))
			{
				GUI::selectPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("SELECT");
				}
				GUI::keyPressPreviousTick = GetTickCount64();
			}
		}
		GUI::optionCount = 0;
		GUI::optionCountMenuBottom = 0;
	}
}
void Cheat::GUI::MoveMenu(SubMenus menu)
{
	GUI::menusArray[GUI::menuLevel] = GUI::currentMenu;
	GUI::optionsArray[GUI::menuLevel] = GUI::currentOption;
	GUI::menuLevel++;
	GUI::currentMenu = menu;
	GUI::currentOption = 1;
}

void Cheat::GUI::CloseGUI()
{
	GUI::PreviousMenu = Cheat::GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel = 0;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
}

void Cheat::GUI::BackMenu()
{
	GUI::PreviousMenu = GUI::currentMenu;
	GUI::PreviousMenuLevel = GUI::menuLevel;
	GUI::previousOption = GUI::currentOption;
	GUI::menuLevel--;
	GUI::currentMenu = GUI::menusArray[GUI::menuLevel];
	GUI::currentOption = GUI::optionsArray[GUI::menuLevel];
}

void Cheat::GUI::AddPlayerInfoBoxTextEntry(std::string text, int Row1, int Row2, int Row3, int Row4)
{
	if (Cheat::GUI::guiX < 0.54f)
	{		
		if (Row1 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.110f, GUI::guiY + (Row1 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.205f, GUI::guiY + (Row2 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.295f, GUI::guiY + (Row3 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX + 0.365f, GUI::guiY + (Row4 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
	}
	else
	{
		if (Row1 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.420f, GUI::guiY + (Row1 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row2 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.340f, GUI::guiY + (Row2 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row3 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.260f, GUI::guiY + (Row3 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
		else if (Row4 != NULL)
		{
			GUI::Drawing::Text(text, GUI::count, { Cheat::GUI::guiX - 0.165f, GUI::guiY + (Row4 * 0.020f) - 0.160f }, { 0.30f, 0.30f }, false);
		}
	}
}

void Cheat::GUI::LoadTheme(std::string ThemeFileName, bool StartUp)
{
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	std::string ThemeFilePath = ThemeFolderPath + "\\" + ThemeFileName + ".ini";
	if (!Cheat::CheatFunctions::FileOrDirectoryExists(ThemeFilePath)) { Cheat::GameFunctions::MinimapNotification("~r~Requested Theme File does not exist"); return;  }

	Cheat::GUI::CurrentTheme = ThemeFileName;

	std::string TitleBackgroundRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "title_background_red");
	std::string TitleBackgroundGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "title_background_green");
	std::string TitleBackgroundBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "title_background_blue");
	std::string TitleBackgroundOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "title_background_opacity");

	std::string HeaderBackgroundRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "header_background_red");
	std::string HeaderBackgroundGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "header_background_green");
	std::string HeaderBackgroundBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "header_background_blue");
	std::string HeaderBackgroundOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "header_background_opacity");

	std::string SmallTitleBackgroundRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "small_title_background_red");
	std::string SmallTitleBackgroundGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "small_title_background_green");
	std::string SmallTitleBackgroundBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "small_title_background_blue");
	std::string SmallTitleBackgroundOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "small_title_background_opacity");

	std::string OptionTextRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "option_text_red");
	std::string OptionTextGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "option_text_green");
	std::string OptionTextBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "option_text_blue");
	std::string OptionTextOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "option_text_opacity");

	std::string SelectionBoxRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_red");
	std::string SelectionBoxGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_green");
	std::string SelectionBoxBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_blue");
	std::string SelectionBoxOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_opacity");

	std::string SelectionBoxBackgroundRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_background_red");
	std::string SelectionBoxBackgroundGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_background_green");
	std::string SelectionBoxBackgroundBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_background_blue");
	std::string SelectionBoxBackgroundOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "selection_box_background_opacity");

	std::string BottomLineRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "bottom_line_red");
	std::string BottomLineGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "bottom_line_green");
	std::string BottomLineBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "bottom_line_blue");
	std::string BottomLineOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "bottom_line_opacity");

	std::string MenuBottomBackgroundRed = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "menu_bottom_background_red");
	std::string MenuBottomBackgroundGreen = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "menu_bottom_background_green");
	std::string MenuBottomBackgroundBlue = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "menu_bottom_background_blue");
	std::string MenuBottomBackgroundOpacity = Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	
	if (SmallTitleBackgroundRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SmallTitleBackgroundRed))) { Cheat::GUI::titleRect.r = CheatFunctions::StringToInt(SmallTitleBackgroundRed); } } }
	if (SmallTitleBackgroundGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SmallTitleBackgroundGreen))) { Cheat::GUI::titleRect.g = CheatFunctions::StringToInt(SmallTitleBackgroundGreen); } } }
	if (SmallTitleBackgroundBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SmallTitleBackgroundBlue))) { Cheat::GUI::titleRect.b = CheatFunctions::StringToInt(SmallTitleBackgroundBlue); } } }
	if (SmallTitleBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SmallTitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SmallTitleBackgroundOpacity))) { Cheat::GUI::titleRect.a = CheatFunctions::StringToInt(SmallTitleBackgroundOpacity); } } }
	if (HeaderBackgroundRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(HeaderBackgroundRed))) { Cheat::GUI::headerRect.r = CheatFunctions::StringToInt(HeaderBackgroundRed); } } }
	if (HeaderBackgroundGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(HeaderBackgroundGreen))) { Cheat::GUI::headerRect.g = CheatFunctions::StringToInt(HeaderBackgroundGreen); } } }
	if (HeaderBackgroundBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(HeaderBackgroundBlue))) { Cheat::GUI::headerRect.b = CheatFunctions::StringToInt(HeaderBackgroundBlue); } } }
	if (HeaderBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(HeaderBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(HeaderBackgroundOpacity))) { Cheat::GUI::headerRect.a = CheatFunctions::StringToInt(HeaderBackgroundOpacity); } } }
	if (BottomLineRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(BottomLineRed))) { Cheat::GUI::TopAndBottomLine.r = CheatFunctions::StringToInt(BottomLineRed); } } }
	if (BottomLineGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(BottomLineGreen))) { Cheat::GUI::TopAndBottomLine.g = CheatFunctions::StringToInt(BottomLineGreen); } } }
	if (BottomLineBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(BottomLineBlue))) { Cheat::GUI::TopAndBottomLine.b = CheatFunctions::StringToInt(BottomLineBlue); } } }
	if (BottomLineOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(BottomLineOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(BottomLineOpacity))) { Cheat::GUI::TopAndBottomLine.a = CheatFunctions::StringToInt(BottomLineOpacity); } } }
	if (TitleBackgroundRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(TitleBackgroundRed))) { Cheat::GUI::MainTitleRect.r = CheatFunctions::StringToInt(TitleBackgroundRed); } } }
	if (TitleBackgroundGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(TitleBackgroundGreen))) { Cheat::GUI::MainTitleRect.g = CheatFunctions::StringToInt(TitleBackgroundGreen); } } }
	if (TitleBackgroundBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(TitleBackgroundBlue))) { Cheat::GUI::MainTitleRect.b = CheatFunctions::StringToInt(TitleBackgroundBlue); } } }
	if (TitleBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(TitleBackgroundOpacity))) { Cheat::GUI::MainTitleRect.a = CheatFunctions::StringToInt(TitleBackgroundOpacity); } } }
	if (OptionTextRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(OptionTextRed))) { Cheat::GUI::optionText.r = CheatFunctions::StringToInt(OptionTextRed); } } }
	if (OptionTextGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(OptionTextGreen))) { Cheat::GUI::optionText.g = CheatFunctions::StringToInt(OptionTextGreen); } } }
	if (OptionTextBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(OptionTextBlue))) { Cheat::GUI::optionText.b = CheatFunctions::StringToInt(OptionTextBlue); } } }
	if (OptionTextOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(OptionTextOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(OptionTextOpacity))) { Cheat::GUI::optionText.a = CheatFunctions::StringToInt(OptionTextOpacity); } } }
	if (TitleBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(TitleBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(TitleBackgroundOpacity))) { Cheat::GUI::MainTitleRect.a = CheatFunctions::StringToInt(TitleBackgroundOpacity); } } }
	if (SelectionBoxRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxRed))) { Cheat::GUI::scroller.r = CheatFunctions::StringToInt(SelectionBoxRed); } } }
	if (SelectionBoxGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxGreen))) { Cheat::GUI::scroller.g = CheatFunctions::StringToInt(SelectionBoxGreen); } } }
	if (SelectionBoxBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxBlue))) { Cheat::GUI::scroller.b = CheatFunctions::StringToInt(SelectionBoxBlue); } } }
	if (SelectionBoxOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxOpacity))) { Cheat::GUI::scroller.a = CheatFunctions::StringToInt(SelectionBoxOpacity); } } }
	if (SelectionBoxBackgroundRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxBackgroundRed))) { Cheat::GUI::MenuBackgroundRect.r = CheatFunctions::StringToInt(SelectionBoxBackgroundRed); } } }
	if (SelectionBoxBackgroundGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxBackgroundGreen))) { Cheat::GUI::MenuBackgroundRect.g = CheatFunctions::StringToInt(SelectionBoxBackgroundGreen); } } }
	if (SelectionBoxBackgroundBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxBackgroundBlue))) { Cheat::GUI::MenuBackgroundRect.b = CheatFunctions::StringToInt(SelectionBoxBackgroundBlue); } } }
	if (SelectionBoxBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(SelectionBoxBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(SelectionBoxBackgroundOpacity))) { Cheat::GUI::MenuBackgroundRect.a = CheatFunctions::StringToInt(SelectionBoxBackgroundOpacity); } } }
	if (MenuBottomBackgroundRed != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundRed)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(MenuBottomBackgroundRed))) { Cheat::GUI::MenuBottomRect.r = CheatFunctions::StringToInt(MenuBottomBackgroundRed); } } }
	if (MenuBottomBackgroundGreen != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundGreen)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(MenuBottomBackgroundGreen))) { Cheat::GUI::MenuBottomRect.g = CheatFunctions::StringToInt(MenuBottomBackgroundGreen); } } }
	if (MenuBottomBackgroundBlue != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundBlue)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(MenuBottomBackgroundBlue))) { Cheat::GUI::MenuBottomRect.b = CheatFunctions::StringToInt(MenuBottomBackgroundBlue); } } }
	if (MenuBottomBackgroundOpacity != "NOT_FOUND") { if (Cheat::CheatFunctions::StringIsInteger(MenuBottomBackgroundOpacity)) { if (Cheat::CheatFunctions::IsIntegerInRange(0, 255, CheatFunctions::StringToInt(MenuBottomBackgroundOpacity))) { Cheat::GUI::MenuBottomRect.a = CheatFunctions::StringToInt(MenuBottomBackgroundOpacity); } } }

	if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "show_header_background") == "true") { Cheat::GUI::ShowHeaderBackground = true; }
	if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "show_header_gui") == "true") { Cheat::GUI::ShowHeaderGUI = true; } else { Cheat::GUI::ShowHeaderGUI = false; }
	if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "restore_previous_submenu") == "false") { Cheat::GUI::RestorePreviousSubmenu = false; } else { Cheat::GUI::RestorePreviousSubmenu = true; }
	if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "show_header_glare") == "false") { Cheat::GUI::ShowHeaderGlare = false; } else { Cheat::GUI::ShowHeaderGlare = true; }

	try
	{ 
		float X			= std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_x"));
		float Y			= std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_y"));
		float Width		= std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_width"));

		Cheat::GUI::keyPressDelay = CheatFunctions::StringToInt(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "key_press_delay"));
		Cheat::CheatFeatures::BoolOptionVectorPosition = CheatFunctions::StringToInt(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "boolean_toggle"));

		if (Cheat::CheatFunctions::IsIntegerInRange(0.110000, 0.86000, X))
		{
			Cheat::GUI::guiX = std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_x"));
		}

		if (Cheat::CheatFunctions::IsIntegerInRange(0.100000, 0.80000, Y))
		{
			Cheat::GUI::guiY = std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_y"));
		}

		if (Cheat::CheatFunctions::IsIntegerInRange(0.210000, 0.31000, Width))
		{
			Cheat::GUI::guiWidth = std::stof(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "gui_width"));
		}

		Cheat::GUI::maxVisOptions = CheatFunctions::StringToInt(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "max_vis_options"));
		if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "open_key") != "NOT_FOUND")
		{
			Cheat::GUI::OpenGUIKey = CheatFunctions::StringToInt(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "open_key"));
		}
		if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "cursor_navigation_toggle_key") != "NOT_FOUND")
		{
			Cheat::GUI::GUINavigationKey = CheatFunctions::StringToInt(Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "cursor_navigation_toggle_key"));
		}
	}
	catch (...) {}

	//Check Theme File Version
	if (Cheat::CheatFunctions::IniFileReturnKeyValueAsString(ThemeFilePath, "THEME", "theme_file_version") != "1.5")
	{
		remove(ThemeFilePath.c_str());
		SaveTheme(ThemeFileName);
		Cheat::GameFunctions::SubtitleNotification("~b~Active Theme outdated, it has been resaved to update the changes", 5000);
	}

	//Save New Active Theme Name To Config File
	if (!StartUp) 
	{
		Cheat::CheatFunctions::IniFileWriteString(Cheat::GUI::CurrentTheme, Cheat::CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "active_theme");
		Cheat::GameFunctions::MinimapNotification("Theme Loaded"); 
	}
}


void Cheat::GUI::DeleteCurrentTheme()
{
	std::string ThemeFileNamePath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + Cheat::GUI::CurrentTheme + ".ini";
	if (remove(ThemeFileNamePath.c_str()) != 0) 
	{ 
		Cheat::GameFunctions::MinimapNotification("~r~Failed To Delete Theme File"); 
	}
	else 
	{ 
		Cheat::CheatFunctions::IniFileWriteString("", Cheat::CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "active_theme");
		Cheat::GUI::CurrentTheme.clear(); 
		GUI::currentOption = 1;
		Cheat::GameFunctions::MinimapNotification("Theme File Removed"); 
	}
}

void Cheat::GUI::ChangeControlsState(bool State)
{
	if (State)
	{
		Cheat::LogFunctions::DebugMessage("Enabled Controls");
		ControlsDisabled = false;
	}
	else
	{
		Cheat::LogFunctions::DebugMessage("Disabled Controls");
		ControlsDisabled = true;
	}
}

void Cheat::GUI::SaveTheme(std::string ThemeFileName)
{
	std::string ThemeFolderPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes";
	std::string ThemeFilePath = ThemeFolderPath + "\\" + ThemeFileName + ".ini";
	if (!Cheat::CheatFunctions::FileOrDirectoryExists(Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes"))
	{ 
		Cheat::CheatFunctions::CreateNewDirectory(ThemeFolderPath); 
	}

	Cheat::CheatFunctions::IniFileWriteString("1.5", ThemeFilePath, "THEME", "theme_file_version");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderBackground, ThemeFilePath, "THEME", "show_header_background");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderGUI, ThemeFilePath, "THEME", "show_header_gui");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::RestorePreviousSubmenu, ThemeFilePath, "THEME", "restore_previous_submenu");
	Cheat::CheatFunctions::WriteBoolToIni(Cheat::GUI::ShowHeaderGlare, ThemeFilePath, "THEME", "show_header_glare");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::guiX), ThemeFilePath, "THEME", "gui_x");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::guiY), ThemeFilePath, "THEME", "gui_y");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::guiWidth), ThemeFilePath, "THEME", "gui_width");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::keyPressDelay), ThemeFilePath, "THEME", "key_press_delay");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::maxVisOptions), ThemeFilePath, "THEME", "max_vis_options");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::OpenGUIKey), ThemeFilePath, "THEME", "open_key");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::GUINavigationKey), ThemeFilePath, "THEME", "cursor_navigation_toggle_key");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::CheatFeatures::BoolOptionVectorPosition), ThemeFilePath, "THEME", "boolean_toggle");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MainTitleRect.r), ThemeFilePath, "THEME", "title_background_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MainTitleRect.g), ThemeFilePath, "THEME", "title_background_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MainTitleRect.b), ThemeFilePath, "THEME", "title_background_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MainTitleRect.a), ThemeFilePath, "THEME", "title_background_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::headerRect.r), ThemeFilePath, "THEME", "header_background_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::headerRect.g), ThemeFilePath, "THEME", "header_background_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::headerRect.b), ThemeFilePath, "THEME", "header_background_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::headerRect.a), ThemeFilePath, "THEME", "header_background_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::titleRect.r), ThemeFilePath, "THEME", "small_title_background_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::titleRect.g), ThemeFilePath, "THEME", "small_title_background_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::titleRect.b), ThemeFilePath, "THEME", "small_title_background_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::titleRect.a), ThemeFilePath, "THEME", "small_title_background_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::optionText.r), ThemeFilePath, "THEME", "option_text_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::optionText.g), ThemeFilePath, "THEME", "option_text_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::optionText.b), ThemeFilePath, "THEME", "option_text_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::optionText.a), ThemeFilePath, "THEME", "option_text_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::scroller.r), ThemeFilePath, "THEME", "selection_box_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::scroller.g), ThemeFilePath, "THEME", "selection_box_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::scroller.b), ThemeFilePath, "THEME", "selection_box_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::scroller.a), ThemeFilePath, "THEME", "selection_box_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBackgroundRect.r), ThemeFilePath, "THEME", "selection_box_background_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBackgroundRect.g), ThemeFilePath, "THEME", "selection_box_background_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBackgroundRect.b), ThemeFilePath, "THEME", "selection_box_background_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBackgroundRect.a), ThemeFilePath, "THEME", "selection_box_background_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::TopAndBottomLine.r), ThemeFilePath, "THEME", "bottom_line_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::TopAndBottomLine.g), ThemeFilePath, "THEME", "bottom_line_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::TopAndBottomLine.b), ThemeFilePath, "THEME", "bottom_line_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::TopAndBottomLine.a), ThemeFilePath, "THEME", "bottom_line_opacity");

	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBottomRect.r), ThemeFilePath, "THEME", "menu_bottom_background_red");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBottomRect.g), ThemeFilePath, "THEME", "menu_bottom_background_green");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBottomRect.b), ThemeFilePath, "THEME", "menu_bottom_background_blue");
	Cheat::CheatFunctions::IniFileWriteString(std::to_string(Cheat::GUI::MenuBottomRect.a), ThemeFilePath, "THEME", "menu_bottom_background_opacity");

	Cheat::GameFunctions::MinimapNotification("Theme Saved");
}

bool Cheat::GUI::SelectableHandler(bool DisabledState)
{
	//Handle selectable disable state
	if (DisabledState)
	{
		Cheat::GameFunctions::AdvancedMinimapNotification("This selectable is currently disabled", "Textures", "AdvancedNotificationImage", false, 4, "Cheat", "", 0.5f, "");
		return false;
	}
	return true;
}

static fpFileRegister RegisterTextureFile = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(RegisterTextureFile)>());
void Cheat::GUI::Drawing::InitTextureFile()
{
	Cheat::LogFunctions::Message("Loading Texture File");

	remove(CheatFunctions::StringToChar(Cheat::CheatFunctions::TextureFilePath()));

	//Find and load the resource
	HRSRC hResource = FindResourceA(Cheat::CheatModuleHandle, MAKEINTRESOURCEA(140), "CHEAT_DATA");
	if (!hResource) { goto Error; }
	HGLOBAL hFileResource = LoadResource(Cheat::CheatModuleHandle, hResource);
	if (!hFileResource) { goto Error; }

	//Open and map this to a disk file
	LPVOID lpFile = LockResource(hFileResource);
	DWORD dwSize = SizeofResource(Cheat::CheatModuleHandle, hResource);

	//Open the file and filemap
	HANDLE hFile = CreateFileA(CheatFunctions::StringToChar(Cheat::CheatFunctions::TextureFilePath()), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
	if (!hFileMap) { goto Error; }

	LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (!lpAddress) { goto Error; }

	//Write the file
	CopyMemory(lpAddress, lpFile, dwSize);

	//Un-map the file and close the handles
	UnmapViewOfFile(lpAddress);
	CloseHandle(hFileMap);
	CloseHandle(hFile);


	int textureID;
	if (Cheat::CheatFunctions::FileOrDirectoryExists(Cheat::CheatFunctions::TextureFilePath()))
	{
		RegisterTextureFile(&textureID, Cheat::CheatFunctions::TextureFilePath().c_str(), true, "Textures.ytd", false);
		return;
	}
	else
	{
		goto Error;
	}

	//Error
Error:
	Cheat::GameFunctions::MinimapNotification("~r~Failed to load Texture");
	Cheat::LogFunctions::DebugMessage("Failed to load Textures.ytd");
}

void Cheat::GUI::Drawing::Text(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	if (!GUI::HideGUIElements)
	{
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		UI::SET_TEXT_FONT(rgbaf.f);
		UI::SET_TEXT_SCALE(size.w, size.h);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(CheatFunctions::StringToChar(text));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
	}
}

void Cheat::GUI::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
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

void Cheat::GUI::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	if (!GUI::HideGUIElements)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
	}
}

void Cheat::GUI::Drawing::DrawScaleform(const float x, const float y, const float sx, const float sy, const int r, const int g, const int b)
{
	if (!GUI::HideGUIElements)
	{
		int ScaleFormHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
		GRAPHICS::DRAW_SCALEFORM_MOVIE(ScaleFormHandle, x, y, sx, sy, r, g, b, 255, 0);
	}
}