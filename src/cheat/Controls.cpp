#include "../../src/cheat/fibermain.h"

bool Cheat::Controls::KeyInputDisabled			= false; // All cheat-provided control inputs are disabled when True
bool Cheat::Controls::AllowGameplayWithCursorNavigationActive = false;
bool Cheat::Controls::DisableCursorNavigationWhenMenuGUIIsClosed = false;
bool Cheat::Controls::SelectPressed				= false; // Internal boolean used by logic - do not manually modify
bool Cheat::Controls::LeftPressed				= false; // Internal boolean used by logic - do not manually modify
bool Cheat::Controls::RightPressed				= false; // Internal boolean used by logic - do not manually modify

int Cheat::Controls::KeyPressDelay				= 150;
int Cheat::Controls::KeyPressDelayPreviousTick	= GetTickCount64();
int Cheat::Controls::OpenMenuGUIKey				= VK_F4;
int Cheat::Controls::CursorNavigationKey		= VK_F5;
int Cheat::Controls::SaveSelectableKey			= VK_F12;

void Cheat::Controls::Loop()
{
	if (!KeyInputDisabled)
	{
		SelectPressed = false;
		LeftPressed = false;
		RightPressed = false;

		if (GetTickCount64() - KeyPressDelayPreviousTick > KeyPressDelay)
		{
			// Enable/Disable Cursor Control
			if (CheatFunctions::IsKeyCurrentlyPressed(CursorNavigationKey)) 
			{ 
				GameFunctions::EnableDisableCursorNavigation(); 
				KeyPressDelayPreviousTick = GetTickCount64();
			}

			// Menu GUI
			if (CheatFunctions::IsKeyCurrentlyPressed(OpenMenuGUIKey))
			{
				GUI::MenuGUIHasBeenOpened = true;
				if (GUI::menuLevel == 0)
				{
					GameFunctions::PlayFrontendSoundDefault((char*)"YES");
					if (GUI::PreviousMenu != nullptr && GUI::RestorePreviousSubmenu)
					{
						GUI::MoveMenu(GUI::PreviousMenu);
						GUI::menuLevel = GUI::PreviousMenuLevel;
						GUI::currentOption = GUI::previousOption;
					}
					else
					{
						GUI::MoveMenu(GUI::Submenus::Home);
					}
					if (!GUI::DisableMenuGUIOpenCloseFade)
					{
						DoMenuGUIFade(true);
					}
				}
				else
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"NO");
					if (!GUI::DisableMenuGUIOpenCloseFade)
					{
						DoMenuGUIFade(false);
					}
					else
					{
						GUI::CloseMenuGUI();
					}
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL))
			{
				if (GUI::menuLevel > 0)
				{
					GUI::BackMenu();
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"BACK");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_UP))
			{
				GUI::currentOption > 1 ? GUI::currentOption-- : GUI::currentOption = GUI::optionCount;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_DOWN))
			{
				GUI::currentOption < GUI::optionCount ? GUI::currentOption++ : GUI::currentOption = 1;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_RIGHT))
			{
				LeftPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_LEFT))
			{
				RightPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT))
			{
				SelectPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault((char*)"SELECT");
				}
				KeyPressDelayPreviousTick = GetTickCount64();
			}
		}
		GUI::optionCount = 0;
		GUI::optionCountVisible = 0;
	}

	// Cursor Navigation Handler
	if (CheatFeatures::CursorNavigationState)
	{
		// Handle menu GUI navigation - only when the menu is actually open/visible
		UI::_SET_MOUSE_CURSOR_ACTIVE_THIS_FRAME();
		UI::_SET_MOUSE_CURSOR_SPRITE(CursorType::Normal);

		if (GUI::menuLevel > 0)
		{
			if (GameFunctions::IsCursorAtXYPosition({ GUI::guiX, GUI::guiY - GUI::SelectableHeight - 0.181f }, { GUI::guiWidth, GUI::SelectableHeight + 0.045f }))
			{
				UI::_SET_MOUSE_CURSOR_SPRITE(CursorType::PreGrab);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
				{
					GUI::guiX = GameFunctions::ReturnCursorYXCoords().x;
					GUI::guiY = GameFunctions::ReturnCursorYXCoords().y + 0.20f;
				}
			}
			if (GameFunctions::IsCursorAtXYPosition({ GUI::SelectableInfoBoxX, GUI::SelectableInfoBoxY }, { 0.25f, 0.080f }))
			{
				UI::_SET_MOUSE_CURSOR_SPRITE(CursorType::PreGrab);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_ACCEPT))
				{
					GUI::SelectableInfoBoxX = GameFunctions::ReturnCursorYXCoords().x;
					GUI::SelectableInfoBoxY = GameFunctions::ReturnCursorYXCoords().y;
				}
			}
			// Menu GUI Close/Back Button
			if (GameFunctions::IsCursorAtXYPosition({ GUI::guiX - 0.100f, GUI::guiY - 0.156f }, { 0.060f, 0.025f }))
			{
				UI::_SET_MOUSE_CURSOR_SPRITE(CursorType::PreGrab);
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, INPUT_CURSOR_ACCEPT))
				{
					GUI::BackMenu();
				}
			}
			// Scroll Up
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_UP))
			{
				if (GUI::currentOption > 1)
				{
					GUI::currentOption -= 1;
				}
				else
				{
					GUI::currentOption = GUI::TotalOptionsCount;
				}
				GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
			}
			// Scroll Down
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, INPUT_CURSOR_SCROLL_DOWN))
			{
				if (GUI::TotalOptionsCount > GUI::currentOption)
				{
					GUI::currentOption += 1;
				}
				else
				{
					GUI::currentOption = 1;
				}
				GameFunctions::PlayFrontendSoundDefault((char*)"NAV_UP_DOWN");
			}
		}
	}
}

void Cheat::Controls::DoMenuGUIFade(bool FadeIn)
{
	if (FadeIn)
	{
		GUI::TextColorAndFont.a = 0;
		GUI::PrimaryColor.a = 0;
		GUI::SelectableTransparency = 0;
		GUI::HeaderBackgroundTransparency = 0;
		GUI::TitleAndEndTransparency = 0;
		GUI::ToggleSelectableTransparency = 0;
		GUI::HeaderTextureTransparency = 0;
		GUI::EndSmallLogoTransparency = 0;
		GUI::OnlinePlayerPictureTransparency = 0;
	}
	for (int i = 0; i <= 3; ++i)
	{
		std::thread MenuGUIFadeThread(MenuGUIFadeFunction, i, FadeIn);
		MenuGUIFadeThread.detach();
	}
}

void Cheat::Controls::MenuGUIFadeFunction(int Type, bool FadeIn)
{
	int Delay = 1;
	if (Type == 0)
	{
		if (FadeIn)
		{
			for (int i = 0; i <= 255; ++i)
			{
				GUI::TextColorAndFont.a = i;
				GUI::PrimaryColor.a = i;
				GUI::ToggleSelectableTransparency = i;
				GUI::HeaderTextureTransparency = i;
				GUI::EndSmallLogoTransparency = i;
				GUI::OnlinePlayerPictureTransparency = i;
				Sleep(Delay);
			}
		}
		else
		{
			for (int i = 255; i >= 0; --i)
			{
				GUI::TextColorAndFont.a = i;
				GUI::PrimaryColor.a = i;
				GUI::ToggleSelectableTransparency = i;
				GUI::HeaderTextureTransparency = i;
				GUI::EndSmallLogoTransparency = i;
				GUI::OnlinePlayerPictureTransparency = i;
				Sleep(Delay);
			}
		}
	}
	else if (Type == 1)
	{
		if (FadeIn)
		{
			for (int i = 0; i <= 150; ++i)
			{
				GUI::SelectableTransparency = i;
				Sleep(Delay);
			}
		}
		else
		{
			for (int i = 150; i >= 0; --i)
			{
				GUI::SelectableTransparency = i;
				Sleep(Delay);
			}
		}
	}
	else if (Type == 2)
	{
		if (FadeIn)
		{
			for (int i = 0; i <= 200; ++i)
			{
				GUI::HeaderBackgroundTransparency = i;
				Sleep(Delay);
			}
		}
		else
		{
			for (int i = 200; i >= 0; --i)
			{
				GUI::HeaderBackgroundTransparency = i;
				Sleep(Delay);
			}
		}
	}
	else if (Type == 3)
	{
		if (FadeIn)
		{
			for (int i = 0; i <= 210; ++i)
			{
				GUI::TitleAndEndTransparency = i;
				Sleep(Delay);
			}
		}
		else
		{
			for (int i = 210; i >= 0; --i)
			{
				GUI::TitleAndEndTransparency = i;
				Sleep(Delay);
			}
			GUI::CloseMenuGUI();
		}
	}
}


const std::map<int, std::string> Cheat::Controls::VirtualKeyToString
{
	{ VK_LBUTTON, "Left mouse button" },
	{ VK_RBUTTON, "Right mouse button"},
	{ VK_CANCEL, "Control-break"},
	{ VK_MBUTTON, "Middle mouse button" },
	{ VK_BACK, "Backspace" },
	{ VK_TAB, "Tab" },
	{ VK_CLEAR, "Clear" },
	{ VK_RETURN, "Enter" },
	{ VK_SHIFT, "Shift (L/R)" },
	{ VK_CONTROL, "Control (L/R)" },
	{ VK_MENU, "Alt" },
	{ VK_PAUSE, "Pause" },
	{ VK_CAPITAL, "Caps Lock" },
	{ VK_ESCAPE, "Escape" },
	{ VK_SPACE, "Spacebar" },
	{ VK_PRIOR, "Page Up" },
	{ VK_NEXT, "Page Down" },
	{ VK_END, "End" },
	{ VK_HOME, "Home" },
	{ VK_LEFT, "Left Arrow" },
	{ VK_UP, "Up Arrow" },
	{ VK_RIGHT, "Right Arrow" },
	{ VK_DOWN, "Down Arroow" },
	{ VK_SELECT, "Select" },
	{ VK_PRINT, "Print" },
	{ VK_EXECUTE, "Execute" },
	{ VK_SNAPSHOT, "Print Screen" },
	{ VK_INSERT, "Insert" },
	{ VK_DELETE, "Delete" },
	{ VK_HELP, "Help" },
	{ 48, "0" },
	{ 49, "1" },
	{ 50, "2" },
	{ 51, "3" },
	{ 52, "4" },
	{ 53, "5" },
	{ 54, "6" },
	{ 55, "7" },
	{ 56, "8" },
	{ 57, "9" },
	{ 65, "A" },
	{ 66, "B" },
	{ 67, "C" },
	{ 68, "D" },
	{ 69, "E" },
	{ 70, "F" },
	{ 71, "G" },
	{ 72, "H" },
	{ 73, "I" },
	{ 74, "J" },
	{ 75, "K" },
	{ 76, "L" },
	{ 77, "M" },
	{ 78, "N" },
	{ 79, "O" },
	{ 80, "P" },
	{ 81, "Q" },
	{ 82, "R" },
	{ 83, "S" },
	{ 84, "T" },
	{ 85, "U" },
	{ 86, "V" },
	{ 87, "W" },
	{ 88, "X" },
	{ 89, "Y" },
	{ 90, "Z" },
	{ VK_LWIN, "Left Windows Key" },
	{ VK_RWIN, "Right Windows Key" },
	{ VK_SLEEP, "Sleep" },
	{ VK_NUMPAD0, "Numpad 0" },
	{ VK_NUMPAD1, "Numpad 1" },
	{ VK_NUMPAD2, "Numpad 2" },
	{ VK_NUMPAD3, "Numpad 3" },
	{ VK_NUMPAD4, "Numpad 4" },
	{ VK_NUMPAD5, "Numpad 5" },
	{ VK_NUMPAD6, "Numpad 6" },
	{ VK_NUMPAD7, "Numpad 7" },
	{ VK_NUMPAD8, "Numpad 8" },
	{ VK_NUMPAD9, "Numpad 9" },
	{ VK_MULTIPLY, "Numpad *" },
	{ VK_ADD, "Add" },
	{ VK_SEPARATOR, "Seperator" },
	{ VK_SUBTRACT, "Substract" },
	{ VK_DECIMAL, "Decimal" },
	{ VK_DIVIDE, "Divide" },
	{ VK_F1, "F1" },
	{ VK_F2, "F2" },
	{ VK_F3, "F3" },
	{ VK_F4, "F4" },
	{ VK_F5, "F5" },
	{ VK_F6, "F6" },
	{ VK_F7, "F7" },
	{ VK_F8, "F8" },
	{ VK_F9, "F9" },
	{ VK_F10, "F10" },
	{ VK_F11, "F11" },
	{ VK_F12, "F12" },
	{ VK_NUMLOCK, "Num Lock" },
	{ VK_SCROLL, "Scroll Lock" },
	{ VK_LSHIFT, "Left Shift" },
	{ VK_RSHIFT, "Right Shift" },
	{ VK_LCONTROL, "Left Control" },
	{ VK_RCONTROL, "Right Control" }
};