﻿#include "../../src/cheat/FiberMain.h"

void Cheat::FiberMain(LPVOID lpParameter)
{
	for (;;)
	{
		CheatFunctions::Loop();
		CheatFeatures::Loop();
		Controls::Loop();
		GameHooking::PauseMainFiber(0, false);
	}
}