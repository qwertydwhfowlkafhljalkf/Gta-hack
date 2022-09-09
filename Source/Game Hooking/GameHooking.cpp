#include "../Header/Cheat Functions/FiberMain.h"
#include "../../ThirdParty/kiero/kiero.h"

using namespace Cheat;

HANDLE MainFiber;
IsDLCPresent														GameHooking::is_dlc_present;
TextureFileRegister													GameHooking::texture_file_register;
GetEventData														GameHooking::get_event_data;
GetLabelText														GameHooking::get_label_text;
GetScriptHandlerIfNetworked											GameHooking::get_script_handler_if_networked;
GetScriptHandler													GameHooking::get_script_handler;
GetPlayerAddress													GameHooking::get_player_address;
GetChatData														    GameHooking::get_chat_data;

static eGameState* 													m_gameState;
static uint64_t														m_worldPtr;
static PVOID														m_ownedExplosionBypass;
static PUSHORT														m_requestEntityControlSpectateBypass;
static GameHooking::NativeRegistrationNew**							m_registrationTable;
static std::unordered_map<uint64_t, GameHooking::NativeHandler>		m_handlerCache;
static __int64**													m_globalPtr;
ScriptThread* (*GetActiveThread)()									= nullptr;
const int EventCountInteger											= 85;
static char EventRestore[EventCountInteger]							= {};
static std::vector<void*> EventPtr;

// Function and variable definitions hooks
IsDLCPresent IsDLCPresentOriginal									= nullptr;
GetScriptHandlerIfNetworked GetScriptHandlerIfNetworkedOriginal		= nullptr;
GetChatData GetChatDataOriginal										= nullptr;
GetLabelText GetLabelTextOriginal									= nullptr;
GetEventData GetEventDataOriginal									= nullptr;
bool IsDLCPresentHooked												(std::uint32_t DLCHash);
bool GetEventDataHooked												(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
void* GetScriptHandlerIfNetworkedHooked								();
__int64 GetChatDataHooked											(__int64 a1, __int64 a2, __int64 a3, const char* origText, BOOL isTeam);
const char* GetLabelTextHooked										(void* this_, const char* label);

void GameHooking::Init()
{
	// Load pointers

	Logger::DebugMessage("Getting is_dlc_present pointer");
	GameHooking::is_dlc_present = static_cast<IsDLCPresent>(Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 81 F9 ? ? ? ?").count(1).get(0).get<void>(0));

	Logger::DebugMessage("Getting get_label_text pointer");
	GameHooking::get_label_text = static_cast<GetLabelText>(Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").count(1).get(0).get<void>(0));
	
	Logger::DebugMessage("Getting get_script_handler_if_networked pointer");
	GameHooking::get_script_handler_if_networked = static_cast<GetScriptHandlerIfNetworked>(Memory::pattern("40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12 48 8B 10 48 8B C8").count(1).get(0).get<void>(0));
	
	Logger::DebugMessage("Getting get_script_handler pointer");
	GameHooking::get_script_handler = static_cast<GetScriptHandler>(Memory::pattern("48 83 EC 28 E8 ? ? ? ? 33 C9 48 85 C0 74 0C E8 ? ? ? ? 48 8B 88 ? ? ? ?").count(1).get(0).get<void>(0));
	
	Logger::DebugMessage("Getting get_event_data pointer");
	GameHooking::get_event_data = static_cast<GetEventData>(Memory::pattern("48 85 C0 74 14 4C 8B 10").count(1).get(0).get<void>(-28));
	
	Logger::DebugMessage("Getting texture_file_register pointer");
	GameHooking::texture_file_register = static_cast<TextureFileRegister>(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<void>());
	
	Logger::DebugMessage("Getting get_player_address pointer");
	GameHooking::get_player_address = static_cast<GetPlayerAddress>(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
	
	Logger::DebugMessage("Getting get_chat_data pointer");
	GameHooking::get_chat_data = static_cast<GetChatData>(Memory::pattern("4D 85 C9 0F 84 ? ? ? ? 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 48 20 55 41 54 41 55 41 56 41 57 48 8D A8").count(1).get(0).get<void>(0));

	Logger::DebugMessage("Getting owned explosion bypass pointer");
	m_ownedExplosionBypass = Memory::pattern("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8").count(1).get(0).get<void>(0);

	Logger::DebugMessage("Getting network_request_control_of_entity pointer & execute spectate patch");
	m_requestEntityControlSpectateBypass = Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? ? ? ? ? 8B CB").count(1).get(0).get<USHORT>(0x13);
	*m_requestEntityControlSpectateBypass = 0x9090; // Set to 0x6A75 after changing to undo the patch

	char* c_location = nullptr;
	void* v_location = nullptr;

	// Load GameState
	Logger::DebugMessage("Getting game state pointer");
	c_location = Memory::pattern("83 3D ? ? ? ? ? 75 17 8B 43 20 25").count(1).get(0).get<char>(2);
	c_location == nullptr ? Logger::Error("Failed to load GameState", true) : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);

	// Load Vector3 Result Fix
	Logger::DebugMessage("Getting vector3 result fix pointer");
	v_location = Memory::pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18").count(1).get(0).get<void>(0);
	if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

	// Load Native Registration Table
	Logger::DebugMessage("Getting native registration table pointer");
	c_location = Memory::pattern("76 32 48 8B 53 40 48 8D 0D").count(1).get(0).get<char>(9);
	c_location == nullptr ? Logger::Error("Failed to load Native Registration Table", true) : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	// Load Game World Pointer
	Logger::DebugMessage("Getting world pointer");
	c_location = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07").count(1).get(0).get<char>(0);
	c_location == nullptr ? Logger::Error("Failed to load World Pointer", true) : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	// Get Global Pointer
	Logger::DebugMessage("Getting global pointer");
	c_location = Memory::pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11").count(1).get(0).get<char>(0);
	__int64 patternAddr = NULL;
	c_location == nullptr ? Logger::Error("Failed to load Global Pointer", true) : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
	m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

	// Get Event Hook -> Used by defuseEvent
	Logger::DebugMessage("Loading event hook");
	if ((c_location = Memory::pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03").count(1).get(0).get<char>(0)))
	{
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EventCountInteger)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}

	// Initialize Natives
	Logger::DebugMessage("Initialized game natives");
	CrossMapping::initNativeMap();

	bool WaitingGameLoadLogPrinted = false;
	while (*m_gameState != GameStatePlaying)
	{
		if (!WaitingGameLoadLogPrinted)
		{
			Logger::Message("Waiting for the game to have finished loading");
			WaitingGameLoadLogPrinted = true;
		}
		Sleep(100);
	}
	if (WaitingGameLoadLogPrinted)
	{
		Logger::Message("Game completed loading");
	}

	// Hook Game Functions
	Logger::DebugMessage("Hook get_event_data");
	auto status = MH_CreateHook(GameHooking::get_event_data, GetEventDataHooked, (void**)&GetEventDataOriginal);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(GameHooking::get_event_data) != MH_OK) { Logger::Error("Failed to hook GET_EVENT_DATA", true);  std::exit(EXIT_FAILURE); }

	Logger::DebugMessage("Hook get_script_handler_if_networked");
	status = MH_CreateHook(GameHooking::get_script_handler_if_networked, GetScriptHandlerIfNetworkedHooked, (void**)&GetScriptHandlerIfNetworkedOriginal);
	if (status != MH_OK || MH_EnableHook(GameHooking::get_script_handler_if_networked) != MH_OK) { Logger::Error("Failed to hook GET_SCRIPT_HANDLER_IF_NETWORKED", true);  std::exit(EXIT_FAILURE); }

	Logger::DebugMessage("Hook get_label_text");
	status = MH_CreateHook(GameHooking::get_label_text, GetLabelTextHooked, (void**)&GetLabelTextOriginal);
	if (status != MH_OK || MH_EnableHook(GameHooking::get_label_text) != MH_OK) { Logger::Error("Failed to hook GET_LABEL_TEXT", true);  std::exit(EXIT_FAILURE); }

	Logger::DebugMessage("Hook get_chat_data");
	status = MH_CreateHook(GameHooking::get_chat_data, GetChatDataHooked, (void**)&GetChatDataOriginal);
	if (status != MH_OK || MH_EnableHook(GameHooking::get_chat_data) != MH_OK) { Logger::Error("Failed to hook GET_CHAT_DATA", true);  std::exit(EXIT_FAILURE); }

	Logger::DebugMessage("Hook is_dlc_present");
	status = MH_CreateHook(GameHooking::is_dlc_present, IsDLCPresentHooked, (void**)&IsDLCPresentOriginal);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(GameHooking::is_dlc_present) != MH_OK) { Logger::Error("Failed to hook IS_DLC_PRESENT", true);  std::exit(EXIT_FAILURE); }
}

bool IsDLCPresentHooked(std::uint32_t DLCHash)
{
	static uint64_t	Last = 0;
	uint64_t Current = MISC::GET_FRAME_COUNT();
	if (Last != Current)
	{
		Last = Current;
		GameHooking::OnTickInit();
	}
	return IsDLCPresentOriginal(DLCHash);
}

void* GetScriptHandlerIfNetworkedHooked()
{
	return GameHooking::get_script_handler();
}

std::string GameFunctions::InGameHelpTextMessage;
const char* GetLabelTextHooked(void* this_, const char* label)
{
	if (std::strcmp(label, "HUD_MPREENTER") == 0)	{ return "Joining a New GTA Online Session with GTAV Cheat"; }
	if (std::strcmp(label, "HUD_JOINING") == 0)		{ return "Loading GTA Online with GTAV Cheat"; }
	if (std::strcmp(label, "HUD_QUITTING") == 0)	{ return "Leaving GTA Online with GTAV Cheat"; }
	if (std::strcmp(label, "PM_QUIT_MP") == 0)		{ return "Leave GTA Online with GTAV Cheat"; }
	if (std::strcmp(label, "PM_ENTER_MP") == 0)		{ return "Join GTA Online with GTAV Cheat"; }
	if (std::strcmp(label, "PM_EXIT_GAME") == 0)	{ return "Exit Game with GTAV Cheat"; }
	if (std::strcmp(label, "PM_GO") == 0)			{ return "Go Online with GTAV Cheat"; }
	if (std::strcmp(label, "PM_FRIEND_FM") == 0)	{ return "Join Friend with GTAV Cheat"; }
	if (std::strcmp(label, "PM_FIND_SESS") == 0)	{ return "Find New Session with GTAV Cheat"; }
	if (!GameFunctions::InGameKeyboardWindowTitle.empty())
	{
		if (std::strcmp(label, "FMMC_KEY_TIP8") == 0) { return CheatFunctions::StringToChar(GameFunctions::InGameKeyboardWindowTitle); }
	}
	if (!GameFunctions::InGameHelpTextMessage.empty())
	{
		if (std::strcmp(label, "LETTERS_HELP2") == 0) { return CheatFunctions::StringToChar(GameFunctions::InGameHelpTextMessage); }
	}
	return GetLabelTextOriginal(this_, label);
}

bool GetEventDataHooked(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
{
	auto result = static_cast<decltype(&GetEventDataHooked)>(GetEventDataOriginal)(eventGroup, eventIndex, args, argCount);
	if (result)
	{
		bool BlockScriptEvent = false;
		std::string ScriptEventIDType;
		const auto EventHash = static_cast<eRemoteEvents>(args[0]);

		// Check whether the incoming event needs to be blocked
		if (CheatFeatures::BlockAllScriptEvents)
		{
			BlockScriptEvent = true;
		}
		else
		{
			switch (EventHash)
			{
			case eRemoteEvents::KickToSP:
			case eRemoteEvents::KickToSP2:
				if (CheatFeatures::ProtectionScriptEvents_Kicks)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "session kick";
				}
				break;
			case eRemoteEvents::CeoKick:
				if (CheatFeatures::ProtectionScriptEvents_CEOKick)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "CEO kick";
				}
				break;
			case eRemoteEvents::CeoBan:
				if (CheatFeatures::ProtectionScriptEvents_CEOBan)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "CEO ban";
				}
				break;
			case eRemoteEvents::CeoMoney:
				if (CheatFeatures::ProtectionScriptEvents_CEOMoney)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " giving CEO money";
				}
				break;
			case eRemoteEvents::PropertyTeleport:
				if (CheatFeatures::ProtectionScriptEvents_PropertyTeleport)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "property teleport";
				}
				break;
			case eRemoteEvents::CayoPericoTeleport:
				if (CheatFeatures::ProtectionScriptEvents_CayoPericoTeleport)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "cayo perico teleport";
				}
				break;
			case eRemoteEvents::ForceIntoMission:
			case eRemoteEvents::ForceIntoMission2:
				if (CheatFeatures::ProtectionScriptEvents_ForceIntoMission)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "force into mission";
				}
				break;
			case eRemoteEvents::Bounty:
				if (CheatFeatures::ProtectionScriptEvents_Bounty)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = "setting bounty";
				}
				break;
			case eRemoteEvents::ClearWantedLevel:
				if (CheatFeatures::ProtectionScriptEvents_ClearWantedlevel)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " clearing wanted level";
				}
				break;
			case eRemoteEvents::GameBanner:
				if (CheatFeatures::ProtectionScriptEvents_GameBanner)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " showing a banner";
				}
				break;
			case eRemoteEvents::NetworkBail:
			case eRemoteEvents::NetworkBail2:
				if (CheatFeatures::ProtectionScriptEvents_NetworkBail)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " network bail";
				}
				break;
			case eRemoteEvents::Crash:
			case eRemoteEvents::Crash2:
			case eRemoteEvents::Crash3:
			case eRemoteEvents::Crash4:
			case eRemoteEvents::Crash5:
				if (CheatFeatures::ProtectionScriptEvents_Crash)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " game crash";
				}
				break;
			case eRemoteEvents::PersonalVehicleDestroyed:
				if (CheatFeatures::ProtectionScriptEvents_PersonalVehicleDestroyed)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " showing personal vehicle destroyed msg";
				}
				break;
			case eRemoteEvents::RemoteOffradar:
				if (CheatFeatures::ProtectionScriptEvents_RemoteOffradar)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " activating off the radar";
				}
				break;
			case eRemoteEvents::SendToCutscene:
				if (CheatFeatures::ProtectionScriptEvents_SendToCutscene)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " sending you to a cutscene";
				}
				break;
			case eRemoteEvents::SendToLocation:
				if (CheatFeatures::ProtectionScriptEvents_SendToLocation)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " sending you to a location";
				}
				break;
			case eRemoteEvents::SoundSpam:
				if (CheatFeatures::ProtectionScriptEvents_SoundSpam)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " sound spam";
				}
				break;
			case eRemoteEvents::Spectate:
				if (CheatFeatures::ProtectionScriptEvents_Spectate)
				{
					BlockScriptEvent = true;
					ScriptEventIDType = " spectating";
				}
				break;
			}
		}

		// Do the actual event block and show a notification
		if (BlockScriptEvent)
		{
			if (!CheatFeatures::BlockAllScriptEvents)
			{
				std::string MessageString = "Event ID: " + std::to_string(args[0]);
				if (!ScriptEventIDType.empty())
				{
					MessageString.append(" ~n~Block reason: attempted " + ScriptEventIDType);
				}
				GameFunctions::AdvancedMinimapNotification(MessageString.data(), "Textures", "AdvancedNotificationImage", false, 4, "Script Events Protection", "", 0.8f, "");
			}			
			return false;
		}
	}
	return result;
}

__int64 GetChatDataHooked(__int64 a1, __int64 a2, __int64 a3, const char* origText, BOOL isTeam)
{
	if (CheatFeatures::LogChatMessages)
	{
		CheatFunctions::WriteToFile(CheatFunctions::ReturnChatLogFilePath(), CheatFunctions::ReturnDateTimeFormatAsString("[%H:%M:%S] Message: ") + (std::string)origText + "\n", true);
		Logger::SendMessageToGameChatLogWindow("Message: " + (std::string)origText);
	}
	return GetChatDataOriginal(a1, a2, a3, origText, isTeam);
}


DWORD WakeTime;
void GameHooking::OnTickInit()
{
	static HANDLE scriptFiber;
	if (MainFiber == nullptr) { MainFiber = ConvertThreadToFiber(nullptr); }
	if (timeGetTime() < WakeTime) { return; }
	if (scriptFiber) { SwitchToFiber(scriptFiber); } else  { scriptFiber = CreateFiber(NULL, FiberMain, nullptr); }
}

void GameHooking::PauseMainFiber(DWORD ms, bool ShowMessage)
{
	if (ShowMessage) { GUI::DrawTextInGame("One Moment Please", { 255, 255, 255, 255 }, { 0.525f, 0.400f }, { 1.5f, 1.5f }, true, true); }
	WakeTime = timeGetTime() + ms;
	SwitchToFiber(MainFiber);
}

static GameHooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0)
	{
		return nullptr;
	}

	GameHooking::NativeRegistrationNew * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration())
	{
		for (uint32_t i = 0; i < table->getNumEntries(); i++)
		{
			if (newHash == table->getHash(i))
			{
				return table->handlers[i];
			}
		}
	}
	return nullptr;
}

GameHooking::NativeHandler GameHooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];
	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}
	return handler;
}

uint64_t GameHooking::getWorldPtr()
{
	return m_worldPtr;
}

void GameHooking::defuseEvent(GameEvents e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = (char*)EventPtr[e];
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			*p = EventRestore[e];
	}
}

__int64** GameHooking::getGlobalPtr()
{
	return m_globalPtr;
}

void GameHooking::SetOwnedExplosionBypassState(bool toggle)
{
	*(unsigned short*)m_ownedExplosionBypass = toggle ? 0xE990 : 0x850F;
}