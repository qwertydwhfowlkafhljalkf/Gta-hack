#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::RecoverySubmenuWarning()
{
	if (CheatFunctions::LoadConfigThreadFunctionCompleted)
	{
		if (GameFunctions::ShowFullScreenMessage("Features in this submenu can be risky"))
		{
			GUI::CloseMenuGUI();
			GUI::MoveMenu(Home);
			GUI::MoveMenu(Online);
			GUI::MoveMenu(Recovery);
		}
		else
		{
			GUI::CloseMenuGUI();
			GUI::MoveMenu(Home);
			GUI::MoveMenu(Online);
		}
	}
}