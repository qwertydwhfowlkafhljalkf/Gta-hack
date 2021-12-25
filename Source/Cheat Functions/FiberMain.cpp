#include "../Header/Cheat Functions/FiberMain.h"

void Cheat::FiberMain()
{
	CheatFunctions::NonLooped();
	for (;;)
	{
		CheatFunctions::LoopedFunctions();
		GameHooking::PauseMainFiber(0, false);
	}
}