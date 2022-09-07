#pragma once

namespace Cheat
{
	namespace Controls
	{
		void Loop();
		void ChangeControlsState(bool State);
		void MenuGUIFadeFunction(int Type, bool FadeIn);
		void DoMenuGUIFade(bool FadeIn);
		extern bool KeyInputDisabled;
		extern int KeyPressDelay;
		extern int KeyPressDelayPreviousTick;
		extern int OpenMenuGUIKey;
		extern int CursorNavigationKey;
		extern int SaveSelectableKey;
		extern bool SelectPressed;
		extern bool LeftPressed;
		extern bool RightPressed;
	}
}