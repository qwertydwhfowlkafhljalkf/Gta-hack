#pragma once

#pragma warning(disable : 4244)			//			'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 26812)		//			The enum type type-name is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(disable : 4091)	

// Cheat version 
#define CHEAT_BUILD_NUMBER "2.2.1.3"

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
#include <json.h>

// Project Header Files
#include "../../src/Hooking/Memory.h"
#include "../../src/Hooking/Types.h"
#include "../../src/Hooking/Enums.h"
#include "../../src/Hooking/CrossMapping.h"
#include "../../src/Hooking/NativeInvoker.h"
#include "../../src/Hooking/NativeCaller.h"
#include "../../src/Hooking/Natives.h"
#include "../../src/Hooking/GameHooking.h"
#include "../../src/GUI/GUI.h"
#include "../../src/Cheat/Controls.h"
#include "../../src/Cheat/CheatFunctions.h"
#include "../../src/GUI/Submenus.h"
#include "../../src/Game/GameArrays.h"
#include "../../src/Hooking/Offsets.h"
#include "../../src/Cheat/Logger.h"
#include "../../src/Game/CheatFeatures.h"
#include "../../src/Cheat/CheatFunctions.h"
#include "../../src/Game/GameFunctions.h"

namespace Cheat
{
	void FiberMain(LPVOID lpParameter);
	extern HMODULE CheatModuleHandle;
}