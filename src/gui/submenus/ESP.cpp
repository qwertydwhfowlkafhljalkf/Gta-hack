#include "../../src/cheat/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::ESP()
{
	GUI::Title("Extra-sensory Perception");
	GUI::Toggle("Basic Player ESP", CheatFeatures::PlayerESPBool, "");
}