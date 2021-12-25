#pragma once

#pragma warning(disable : 4244)			//			'argument' : conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 26812)		//			The enum type type-name is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning(disable : 26495)		//			Variable '%variable%' is uninitialized. Always initialize a member variable.
#pragma warning(disable : 4091)	
#pragma warning(disable : 6262)

#define CHEAT_BUILD_NUMBER "2.1.0.1"

#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <atlstr.h>
#include <map>
#include <set>
#include <functional>
#include <winioctl.h>
#include <timeapi.h>
#include <time.h>
#include <conio.h>
#include <filesystem>
#include <fcntl.h>
#include <io.h>
#include <array>
#include <thread>
#pragma comment(lib, "Winmm.lib")

//MinHook
#pragma comment(lib, "ThirdParty/MinHook/libMinHook-x64-v141-md.lib")
#include "../ThirdParty/MinHook/MinHook.h"

//mINI
#include "../ThirdParty/mINI/ini.h"

//Libcurl
#define CURL_STATICLIB
#pragma comment(lib, "ThirdParty/libcurl/libcurl_a.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "advapi32.lib")
#include "../ThirdParty/libcurl/curl.h"

//JsonCpp
#include "../ThirdParty/JsonCpp/json.h"

//Project Header Files
#include "../Header/Game Hooking/Memory.h"
#include "../Header/Game Hooking/Types.h"
#include "../Header/Game Hooking/Enums.h"
#include "../Header/Game Hooking/CrossMapping.h"
#include "../Header/Game Hooking/NativeInvoker.h"
#include "../Header/Game Hooking/NativeCaller.h"
#include "../Header/Game Hooking/Natives.h"
#include "../Header/Game Hooking/GameHooking.h"
#include "../Header/GUI/GUI.h"
#include "../Header/GUI/Controls.h"
#include "../Header/GUI/Submenus.h"
#include "../Header/Game Hooking/Types.h"
#include "../Header/Game Functions/GameArrays.h"
#include "../Header/Game Hooking/Offsets.h"
#include "../Header/Game Functions/CheatFeatures.h"
#include "../Header/Cheat Functions/CheatFunctions.h"
#include "../Header/Game Functions/GameFunctions.h"
#include "../Header/Cheat Functions/LogFunctions.h"



namespace Cheat
{
	void FiberMain();
	extern HMODULE CheatModuleHandle;
}