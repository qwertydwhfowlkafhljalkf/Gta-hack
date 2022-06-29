#include "../Header/Cheat Functions/FiberMain.h"

bool Cheat::Controls::ControlsDisabled		= false; //All cheat input is ignored when True
bool Cheat::Controls::SelectPressed			= false;
bool Cheat::Controls::LeftPressed			= false;
bool Cheat::Controls::RightPressed			= false;

int Cheat::Controls::GUIKeyPressDelay		= 150;
int Cheat::Controls::KeyPressPreviousTick	= GetTickCount64();
int Cheat::Controls::OpenMenuGUIKey			= VK_F4;
int Cheat::Controls::CursorNavigationKey	= VK_F5;
int Cheat::Controls::SaveSelectableKey		= VK_F12;

void Cheat::Controls::Loop()
{
	if (!ControlsDisabled)
	{
		SelectPressed = false;
		LeftPressed = false;
		RightPressed = false;

		if (GetTickCount64() - KeyPressPreviousTick > GUIKeyPressDelay)
		{
			// Enable/Disable Cursor Control
			if (CheatFunctions::IsKeyCurrentlyPressed(CursorNavigationKey, true)) { GameFunctions::EnableDisableCursorNavigation(); }

			// Logger Window Open/Close
			if (CheatFunctions::IsKeyCurrentlyPressed(VK_OEM_3, true)) { Logger::WindowVisible = !Logger::WindowVisible; }

			// Menu GUI
			if (CheatFunctions::IsKeyCurrentlyPressed(OpenMenuGUIKey))
			{
				GUI::CheatGUIHasBeenOpened = true;
				if (GUI::menuLevel == 0)
				{
					GameFunctions::PlayFrontendSoundDefault("YES");
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
					DoMenuGUIFade(true);	
				}
				else
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NO");
					DoMenuGUIFade(false);
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD0))
			{
				if (GUI::menuLevel > 0)
				{
					GUI::BackMenu();
					Cheat::GameFunctions::PlayFrontendSoundDefault("BACK");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD8))
			{
				GUI::currentOption > 1 ? GUI::currentOption-- : GUI::currentOption = GUI::optionCount;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD2))
			{
				GUI::currentOption < GUI::optionCount ? GUI::currentOption++ : GUI::currentOption = 1;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD6))
			{
				LeftPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD4))
			{
				RightPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("NAV_UP_DOWN");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
			else if (Cheat::CheatFunctions::IsKeyCurrentlyPressed(VK_NUMPAD5))
			{
				SelectPressed = true;
				if (GUI::menuLevel > 0)
				{
					Cheat::GameFunctions::PlayFrontendSoundDefault("SELECT");
				}
				KeyPressPreviousTick = GetTickCount64();
			}
		}
		GUI::optionCount = 0;
		GUI::optionCountVisible = 0;
	}
}

void Cheat::Controls::ChangeControlsState(bool State)
{
	if (State)
	{
		Cheat::Logger::DebugMessage("Enabled Controls");
		Controls::ControlsDisabled = false;
	}
	else
	{
		Cheat::Logger::DebugMessage("Disabled Controls");
		Controls::ControlsDisabled = true;
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