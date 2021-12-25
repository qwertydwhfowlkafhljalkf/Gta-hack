#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int ShootEntitiesInteger = 0;
void GUI::Submenus::ShootEntities()
{
	GUI::Title("Shoot Entities");
	GUI::Toggle("Toggle", CheatFeatures::ShootEntitiesBool, "", SELECTABLE_DISABLE_SAVE);
	GUI::Break("Current: ~t~" + CheatFeatures::ShootEntitiesCurrent, false);
	GUI::StringVector("Type", { "Vehicle", "Ped" }, ShootEntitiesInteger, ""); // TODO: Entity as well as Vehicle/Ped List
	if (GUI::Option(ShootEntitiesInteger == 0 ? "Custom Vehicle" : "Custom Ped", ""))
	{
		char* Input = GameFunctions::DisplayKeyboardAndReturnInput(25, ShootEntitiesInteger == 0 ? "Set Vehicle" : "Set Ped");
		if (Input != "0")
		{
			CheatFeatures::ShootEntitiesCurrent = Input;
		}
	}
}