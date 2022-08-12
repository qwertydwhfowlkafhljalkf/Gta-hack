#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Spawn()
{
	GUI::Title("Spawn");
	//GUI::MenuOption("Ped", Submenus::PedSpawn); WIP
	GUI::MenuOption("Vehicle", Submenus::VehicleSpawn);
	//GUI::MenuOption("Object", ObjectSpawnMenu); TODO
}