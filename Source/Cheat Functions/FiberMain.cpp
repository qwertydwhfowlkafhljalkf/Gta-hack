#include "../Header/Cheat Functions/FiberMain.h"

void Cheat::FiberMain()
{
	for (;;)
	{
		CheatFunctions::Loop();
		CheatFeatures::Loop();
		Controls::Loop();
		GameHooking::PauseMainFiber(0, false);
	}
}