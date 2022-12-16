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
#include "../../src/hooking/memory.hpp"
#include "../../src/hooking/types.hpp"
#include "../../src/game/enums.hpp"
#include "../../src/hooking/crossmap.hpp"
#include "../../src/hooking/nativeinvoker.hpp"
#include "../../src/hooking/nativecaller.hpp"
#include "../../src/hooking/natives.hpp"
#include "../../src/hooking/hooking.hpp"
#include "../../src/gui/GUI.h"
#include "../../src/cheat/controls.hpp"
#include "../../src/cheat/cheatfunctions.hpp"
#include "../../src/gui/submenus/submenus.hpp"
#include "../../src/game/gamearrays.hpp"
#include "../../src/hooking/offsets.hpp"
#include "../../src/cheat/Logger.hpp"
#include "../../src/game/cheatfeatures.hpp"
#include "../../src/game/gamefunctions.hpp"

namespace Cheat
{
	void FiberMain(LPVOID lpParameter);
	extern HMODULE CheatModuleHandle;
}