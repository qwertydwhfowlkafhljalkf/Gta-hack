#pragma once

#pragma warning(disable : 4244)			//			'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 26812)		//			The enum type type-name is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(disable : 4091)	

#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <atlstr.h>
#include <functional>
#include <timeapi.h>
#include <time.h>
#include <conio.h>
#include <filesystem>
#include <fcntl.h>
#include <array>
#include <thread>
#include <mutex>
#include <WinINet.h>
#pragma comment(lib, "WinINet.lib")
#pragma comment(lib, "Winmm.lib")

// MinHook
#include <MinHook.h>

// mINI
#include <ini.h>

// JsonCpp
#include <json/json.h>

// Project Header Files
#include "../../src/hooking/Memory.h"
#include "../../src/hooking/Types.h"
#include "../../src/game/Enums.h"
#include "../../src/hooking/crossmap.hpp"
#include "../../src/hooking/NativeInvoker.h"
#include "../../src/hooking/NativeCaller.h"
#include "../../src/hooking/Natives.h"
#include "../../src/hooking/GameHooking.h"
#include "../../src/gui/GUI.h"
#include "../../src/cheat/Controls.h"
#include "../../src/cheat/CheatFunctions.h"
#include "../../src/gui/submenus/submenus.hpp"
#include "../../src/game/GameArrays.h"
#include "../../src/hooking/Offsets.h"
#include "../../src/cheat/Logger.hpp"
#include "../../src/game/CheatFeatures.h"
#include "../../src/cheat/CheatFunctions.h"
#include "../../src/game/GameFunctions.h"

namespace Cheat
{
	void FiberMain(LPVOID lpParameter);
	extern HMODULE CheatModuleHandle;
}