#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::ShootEntities()
{
	GUI::Title("Shoot Entities");
	GUI::Toggle("Toggle", CheatFeatures::ShootEntitiesBool, "", SELECTABLE_DISABLE_SAVE);
	GUI::Break("Current: ~t~" + CheatFeatures::ShootEntitiesCurrent, false);
	if (GUI::Option("Custom Entity", ""))
	{
		char* Input;
		if (GameFunctions::DisplayKeyboardAndReturnInput(25, "Custom Entity Model Name", Input))
		{
			if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(Input)))
			{
				CheatFeatures::ShootEntitiesCurrent = Input;
			}		
			else
			{
				GameFunctions::MinimapNotification("~r~That is not a valid entity name");
			}
		}
	}
}