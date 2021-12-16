#include "../Header/Cheat Functions/FiberMain.h"
int Cheat::CheatFeatures::SelectedPlayer;
int TeleportFoward = 1;																						// Used by Teleport Forward option
int engine_multiplier, torque_multiplier;																	// Used by Vehicle Multipliers options
int SetTimeHour = 0, SetTimeMinutes = 0, SetTimeSeconds = 0;												// Used by World Time options	
int VehiclePrimaryColorRed, VehiclePrimaryColorGreen, VehiclePrimaryColorBlue;								// Used by Vehicle Color features
int VehicleSecondaryColorRed, VehicleSecondaryColorGreen, VehicleSecondaryColorBlue;						// Used by Vehicle Color features	
int VehicleNeonLightRed, VehicleNeonLightGreen, VehicleNeonLightBlue;										// Used by Vehicle Color features
int PlayerWantedLevelInteger = 0;																			// Used by Set Wanted Level Option
int FakeWantedLevelInteger = 0;																				// Used by Fake Wanted Level
float SelfHealth = 200.f;																					// Used by Self Health
int HairColor;																								// Used by Wardrobe
int CustomLocationsAmount;																					// Used by Custom Locations
std::string ChangeModelPedSearchTerm;																		// Used by Model (Self)
std::string ObjectSpawnSearchTerm;																			// Used by Object Spawn
int HUDColorRed, HUDColorGreen, HUDColorBlue, HUDColorAlpha;												// Used by HUD
int intexploits, intoffensive, REPORTSTRENGTH, OFFENSIVETAGPLATE, OFFENSIVEUGC,								// Used by Report Statistics	
    EXPLOITS, GRIEFING, COMMENDSTRENGTH, FRIENDLY, HELPFUL, VCANNOYINGME, VCHATE,						
	BADCREWNAME, BADCREWMOTTO, BADCREWSTATUS, BADCREWEMBLEM, ISPUNISHED;		
int SetPedTexture_Torso = 0, SetPedTexture_TorsoTexture = 0, SetPedTexture_Face = 0,						// Used by SetPedTexture
    SetPedTexture_FaceTexture = 0, SetPedTexture_Head = 0, SetPedTexture_HeadTexture = 0, 
	SetPedTexture_Hair = 0, SetPedTexture_HairTexture = 0, SetPedTexture_Legs = 0, 
	SetPedTexture_LegsTexture = 0, SetPedTexture_Hands = 0, SetPedTexture_HandsTexture = 0, 
	SetPedTexture_Feet = 0, SetPedTexture_FeetTexture = 0, SetPedTexture_Eyes = 0,
	SetPedTexture_EyesTexture = 0, SetPedTexture_Accesories = 0, SetPedTexture_AccesoriesTexture = 0, 
	SetPedTexture_AccesoriesSec = 0, SetPedTexture_AccesoriesSecTexture = 0, SetPedTexture_Textures = 0, 
	SetPedTexture_TexturesTexture = 0, SetPedTexture_TorsoSec = 0,  SetPedTexture_TorsoSecTexture = 0;


void Cheat::FiberMain()
{
	CheatFeatures::NonLooped();
	while (true)
	{
		CheatFunctions::LoopedFunctions();

		switch (GUI::currentMenu) {
		case MainMenu:
		{
			GUI::Title("Home");
			GUI::MenuOption("Self", SelfOptionsMenu);
			GUI::MenuOption("Online", OnlineOptionsMenu);
			GUI::MenuOption("Weapon", weaponmenu);
			GUI::MenuOption("Vehicle", vehiclemenu);
			GUI::MenuOption("Spawn", SpawnMenu);
			GUI::MenuOption("Teleport", teleportmenu);
			GUI::MenuOption("World", worldmenu);
			GUI::MenuOption("Miscellaneous", miscmenu);
			GUI::MenuOption("Settings", SettingsMenu);
		}
		break;
		case AllPlayersExclutionsMenu:
		{
			GUI::Title("Exclutions");
			GUI::Toggle("Exclude Self", CheatFeatures::AllPlayersExclutionsSelf, "");
			GUI::Toggle("Exclude Friends", CheatFeatures::AllPlayersExclutionsFriends, "");
			GUI::Toggle("Exclude Host", CheatFeatures::AllPlayersExclutionsHost, "");
		}
		break;
		case AllPlayersMenu:
		{
			GUI::Title("All Players");
			GUI::MenuOption("Exclutions", AllPlayersExclutionsMenu);
			GUI::Break("Friendly", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Give All Weapons", "Give all players all weapons"))
			{
				for (int i = 0; i < 32; i++)
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						GameFunctions::SubtitleNotification("Giving all weapons to all players in session, one moment", 2000);
						GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
			GUI::Break("Griefing", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Teleport to Eclipse Tower", ""))
			{
				for (int i = 0; i < 32; i++)
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						uint64_t teleport[9] = { TSE_PROPERTY_TELEPORT, i, 0, -1, 1, 1, 0, 0, 0 };
						SCRIPT::TRIGGER_SCRIPT_EVENT(1, teleport, 9, (1 << i));
					}
				}	
			}
			GUI::Toggle("Freeze", CheatFeatures::FreezeAllPlayersBool, "", SELECTABLE_DISABLE_SAVE);
			if (GUI::Option("Kick Out Of Vehicle", ""))
			{
				for (int i = 0; i < 32; i++)
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						GameFunctions::RequestNetworkControlOfEntity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						GameFunctions::StopAllPedAnimations(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
			if (GUI::Option("Airstrike", ""))
			{
				for (int i = 0; i < 32; i++) 
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						Vector3 Coords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35.f, Coords.x, Coords.y, Coords.z, 250, true, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true, false, 500.f);
					}
				}
			}
			if (GUI::Option("Trap", ""))
			{
				for (int i = 0; i < 32; i++) 
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						Vector3 remotePos = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
					}
				}
			}
			if (GUI::Option("Attach Beach Fire", ""))
			{
				for (int i = 0; i < 32; i++)
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{
						GameFunctions::AttachObjectToPed(i, "prop_beach_fire");
					}
				}
			}
			GUI::Break("Miscellaneous", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Host Kick", "Kick all players from session")) 
			{
				for (int i = 0; i < 32; i++)
				{
					bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclutionsSelf;
					bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclutionsFriends;
					bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclutionsHost;

					if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
					{ 
						NETWORK::NETWORK_SESSION_KICK_PLAYER(i); 
					}
				}
			}
		}
		break;
		case OnlineOptionsMenu:
		{
			GUI::Title("Online");
			GUI::MenuOption("Players", PlayerListMenu);
			GUI::MenuOption("All Players", AllPlayersMenu);
			GUI::MenuOption("Protections", protections);
			GUI::MenuOption("Recovery", RecoveryMenuWarning);
			GUI::MenuOption("Session", sessionoptionsmenu);
		}
		break; 
		case sessionoptionsmenu:
		{
			GUI::Title("Session");
			GUI::MenuOption("Chat", SessionChatMenu);
		}
		break;
		case SessionChatMenu:
		{
			GUI::Title("Session Chat");
			GUI::Toggle("Log Chat Messages", CheatFeatures::LogChatMessages, "Chat gets logged to console");
		}
		break;
		case RecoveryMenuWarning:
		{
			if (CheatFunctions::LoadConfigThreadFunctionCompleted)
			{
				if (GameFunctions::ShowFullScreenMessage("Features in this submenu can be risky"))
				{
					GUI::CloseMenuGUI();
					GUI::MoveMenu(MainMenu);
					GUI::MoveMenu(OnlineOptionsMenu);
					GUI::MoveMenu(RecoveryMenu);
				}
				else
				{
					GUI::CloseMenuGUI();
					GUI::MoveMenu(MainMenu);
					GUI::MoveMenu(OnlineOptionsMenu);
				}
			}
		}
		break;
		case RecoveryStatsMenu:
		{
			GUI::Title("Stats");
			std::vector <std::string> SkillStats = { "STAM", "STRN", "LUNG", "DRIV", "FLY", "SHO", "STL" };
			if (GUI::Option("Max All Skills", ""))
			{
				for (const auto& i : SkillStats)
				{
					GameFunctions::SetCharacterSkillStat(i, 100);
				}
				GameFunctions::MinimapNotification("Maxed out all skill stats for your current character");
			}
			if (GUI::Option("Max Stamina", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[0], 100);
			}
			if (GUI::Option("Max Stamina", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[1], 100);
			}
			if (GUI::Option("Max Strength", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[2], 100);
			}
			if (GUI::Option("Max Lung Capacity", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[3], 100);
			}
			if (GUI::Option("Max Driving", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[4], 100);
			}
			if (GUI::Option("Max Flying", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[5], 100);
			}
			if (GUI::Option("Max Shooting", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[6], 100);
			}
			if (GUI::Option("Max Stealth", ""))
			{
				GameFunctions::SetCharacterSkillStat(SkillStats[7], 100);
			}
		}
		break;
		case RecoveryMenu:
		{
			GUI::Title("Recovery");
			GUI::MenuOption("Stats", RecoveryStatsMenu);
			GUI::Break("Unlocks", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Unlock All", "Unlocks many unlockable GTA Online items"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_WEAPON_GV_BS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AIR_LAUNCHES_OVER_40M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_5STAR_WANTED_AVOIDANCE")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ACTIVATE_2_PERSON_KEY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ALL_ROLES_HEIST")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_BUY_EVERY_GUN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CARS_EXPORTED")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CONTROL_CROWDS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJCOMPLETED")), 100, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJMONTHBONUS")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJWEEKBONUS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DO_HEIST_AS_MEMBER")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DO_HEIST_AS_THE_LEADER")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DRIVELESTERCAR5MINS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DROPOFF_CAP_PACKAGES")), 100, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEIST_NO_DAMAGE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEIST_SETUP_JOB")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEISTS")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTDM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTRACES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFITEMSCLOTHES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM6DARTCHKOUT")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_KILLSTREAK")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_STOLENKILL")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_BIRDIES")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_HOLE_IN_1")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GTA_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACE_LAST_FIRST")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACES_FASTEST_LAP")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_CT_WON")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_GRAN_WON")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_RT_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_TG_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_WINS")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_5_SET_WINS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_ACE")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_STASETWIN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_WON")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBASEJMP")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBBETWIN")), 50000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMCRATEDROPS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMDRIVEWITHOUTCRASH")), 30, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMHORDWAVESSURVIVE")), 10, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSGANGHIDE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMPICKUPDLCCRATE1ST")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONDRIVE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONNAV")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMSHOOTDOWNCOPHELI")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMTATTOOALLBODYPARTS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINAIRRACE")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINALLRACEMODES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINCUSTOMRACE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINRACETOPOINTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINSEARACE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_CARRIER_CAPTURE")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_PSYCHOPATHS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_TEAM_YOURSELF_LTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LESTERDELIVERVEHICLES")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_MENTALSTATE_TO_NORMAL")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NIGHTVISION_KILLS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NO_HAIRCUTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ODISTRACTCOPSNOEATH")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ONLY_PLAYER_ALIVE_LTS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_20M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_50M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PASSENGERTIME")), 4, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PICKUP_CAP_PACKAGES")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SPLIT_HEIST_TAKE_EVENLY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_STORE_20_CAR_IN_GARAGES")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TAKEDOWNSMUGPLANE")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TIME_IN_HELICOPTER")), 4, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TRADE_IN_YOUR_PROPERTY")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_VEHICLES_JACKEDR")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_AT_DARTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_CAPTURE_DONT_DYING")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_CAPTURES")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_GOLD_MEDAL_HEISTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_LAST_TEAM_STANDINGS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_BOTTLE_IN_POSSESSION")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CARS_EXPLODED")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_4_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_5_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_6_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_7_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_4_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_5_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_UNLOCKED")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_UNLOCKED2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_10_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_11_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_12_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_1_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_2_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_3_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_4_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_5_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_6_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_7_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_8_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_9_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WANTED_LEVEL_TIME5STAR")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WEAP_FM_PURCHASE")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WEAP_FM_PURCHASE2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_DECL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_OUTFIT")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL2_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TORSO")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_DECL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_OUTFIT")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL2_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TORSO")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_0")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_13")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_14")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_15")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_16")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_17")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_18")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_19")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_20")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_21")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_22")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_23")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_24")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_25")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_26")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_27")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_28")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_29")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_30")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_31")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_32")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_33")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_34")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_35")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_36")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_37")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_38")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_39")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_40")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_GRENADE_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_KILLS_PLAYERS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LONGEST_WHEELIE_DIST")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_ARM_WRESTLING_WINS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_FLIPS_IN_ONE_JUMP")), 5, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_SPINS_IN_ONE_JUMP")), 5, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_SLIPSTREAMS_IN_RACE")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_TURBO_STARTS_IN_RACE")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PASS_DB_PLAYER_KILLS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PISTOL_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SAWNOFF_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_DRIV")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_FLY")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_LUNG")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_MECH")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_SHO")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STAM")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STL")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STRN")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_STKYBMB_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_UNARMED_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_USJS_COMPLETED")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CRDEADLINE")), 10, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BUY_COMPLETE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BUY_UNDERTAKEN")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_SELL_COMPLETE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_SELL_UNDERTAKEN")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_CONTRA_EARNINGS")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS0")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS1")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS2")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS3")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS4")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS5")), 20000000, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_TIER_1_REWARD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_TIER_3_REWARD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_INCREASE_THROW_CAP")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_COMPLET_HEIST_MEM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FLEECA_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_ORDER")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_SAME_TEAM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_ULT_CHAL")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HUMANE_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_PACIFIC_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_PRISON_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_SERIESA_FIN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_HEIST_ACH_TRACKER")), -1, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_IAA")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_SUBMARINE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_ALLINORDER")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_MISSILE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY2")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY3")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD2")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD3")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_SUPPORT")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_YUM_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_HEALTH_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_EPIC_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_OF_ORANGE_BOUGHT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_1_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_2_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_3_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_4_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_5_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_OF_BOURGE_BOUGHT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_DM_MADE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_PLAYED_BY_PEEP")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_RACES_MADE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PHN")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_VEH_TX1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SNIPERRFL_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_HVYSNIPER_ENEMY_KILLS")), 500, true);



				GameFunctions::MinimapNotification("'Unlocked All' completed");
			}
			if (GUI::Option("Unlock Tattoo's", "Unlock most tattoo's"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBBETWIN")), 50000, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_DB_PLAYER_KILLS")), 1000, 1);
			}
			if (GUI::Option("Unlock Heist Vehicles", "Unlock Heist Vehicles"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E2")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E3")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E4")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E5")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E6")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E7")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E8")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E9")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E10")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E11")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E12")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_1_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_2_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_3_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_4_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_5_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_6_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_7_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_8_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_9_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_10_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_11_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_12_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_races_won")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_number_turbo_starts_in_race")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_usjs_found")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_usjs_completed")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmwinairrace")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmwinsearace")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmrallywonnav")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmrallywondrive ")), 500, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fm_races_fastest_lap")), 500, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_0_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_1_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_2_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_3_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_4_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_5_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_6_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_7_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_3_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_1_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_2_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_3_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_4_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_5_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_6_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_7_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_8_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_9_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_HEALTH_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_HEALTH_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_HOLDUPS_BITSET")), -1, 0);
			}
			if (GUI::Option("Unlock Awards & Trophies", ""))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PISTOL_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SAWNOFF_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MICROSMG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SNIPERRFL_ENEMY_KILLS")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_UNARMED_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_STKYBMB_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_GRENADE_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_RPG_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CARS_EXPLODED")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_5STAR_WANTED_AVOIDANCE")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CARS_EXPORTED")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PASS_DB_PLAYER_KILLS")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GTA_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_CT_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_RT_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_TG_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_SPINS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_DM_MADE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMHORDWAVESSURVIVE")), 10, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_ASLTRIFLE_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_ARM_WRESTLING_WINS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NO_HAIRCUTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_VEHICLES_JACKEDR")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_FLIPS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_AT_DARTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PASSENGERTIME")), 4, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TIME_IN_HELICOPTER")), 4, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_3KILLSAMEGUY")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_KILLSTREAK")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_STOLENKILL")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_BIRDIES")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_HOLE_IN_1")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACE_LAST_FIRST")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACES_FASTEST_LAP")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_GRAN_WON")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_ACE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_STASETWIN")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM6DARTCHKOUT")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_20M")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_50M")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AIR_LAUNCHES_OVER_40M")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_BUY_EVERY_GUN")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMDRIVEWITHOUTCRASH")), 255, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMCRATEDROPS")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTDM")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_5_SET_WINS")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_PLAYED_BY_PEEP")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_RACES_MADE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTRACES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFITEMSCLOTHES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_KILLS_PLAYERS")), 1000, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMPICKUPDLCCRATE1ST")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMSHOOTDOWNCOPHELI")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSGANGHIDE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONDRIVE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONNAV")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINAIRRACE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINCUSTOMRACE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINRACETOPOINTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINSEARACE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBASEJMP")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "__AWD_FMWINALLRACEMODES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMTATTOOALLBODYPARTS")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WANTED_LEVEL_TIME5STAR")), 2147483647, 1);
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_LONGEST_WHEELIE_DIST")), 1000, 1);
				GameFunctions::MinimapNotification("GTA Online Awards & Trophies unlocked");
			}
			GUI::Break("Rank", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Set Rank", "Input a custom Rank"))
			{
				int Rank = GameFunctions::DisplayKeyboardAndReturnInputInteger(4, "Enter desired rank");
				if (Rank != 0) { GameFunctions::SetRankRockstarGift(Rank); }
			}
			GUI::Break("Money", SELECTABLE_CENTER_TEXT);
			GUI::Break("Wallet balance: ~g~$~s~" + std::to_string(NETWORKCASH::NETWORK_GET_VC_WALLET_BALANCE(-1)));
			GUI::Break("Bank balance: ~g~$~s~" + std::to_string(NETWORKCASH::NETWORK_GET_VC_BANK_BALANCE()));
			GUI::Break("Miscellaneous", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Set Max Nightclub Popularity", "Set NightClub Popularity to 100%"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_CLUB_POPULARITY")), 9999, false);
				GameFunctions::MinimapNotification("Maxed out Nightclub Popularity");
			}
			if (GUI::Option("Redesign Character Prompt", ""))
			{
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_CHANGECHAR_ASKED")), false, true);
				GameFunctions::MinimapNotification("Leave GTAO and rejoin to receive the notification");
			}
			if (GUI::Option("Clear Badsport", "Clears Badsport status"))
			{
				DWORD date[12];
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT "), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0, 1);
				STATS::STAT_SET_DATE(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_DT"), &date[0], 7, 1);
				GameFunctions::MinimapNotification("Cleared Badsport Status");
			}
			if (GUI::Option("Clear Mental State", "Clear current mental state"))
			{
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_MENTAL_STATE")), 0.0f, true);
				GameFunctions::MinimapNotification("Mental State Reset");
			}
			GUI::Break("ATM", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Move Wallet To Bank", ""))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter amount to move. Type \"all\" to move all money.");
				if (KeyboardInput != "0")
				{
					int Amount = CheatFunctions::StringToInt(KeyboardInput);
					if (KeyboardInput == "all")
					{
						Amount = NETWORKCASH::NETWORK_GET_VC_WALLET_BALANCE(-1);
					}
					UNK3::_NETWORK_TRANSFER_WALLET_TO_BANK(CheatFunctions::StringToInt(GameFunctions::ReturnCurrentGTAOCharacter(true)), Amount);
				}
			}
			if (GUI::Option("Move Bank To Wallet", ""))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter amount to move. Type \"all\" to move all money.");
				if (KeyboardInput != "0") 
				{
					int Amount = CheatFunctions::StringToInt(KeyboardInput);
					if (KeyboardInput == "all")
					{
						Amount = NETWORKCASH::NETWORK_GET_VC_BANK_BALANCE();
					}
					UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(CheatFunctions::StringToInt(GameFunctions::ReturnCurrentGTAOCharacter(true)), Amount);
				}
			}
		}
		break; 
		case reportsmenu_stats:
		{
			GUI::Title("Report Statistics"); 
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"),	&REPORTSTRENGTH,	-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"),		&intexploits,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), &intoffensive,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), &OFFENSIVETAGPLATE, -1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"),		&OFFENSIVEUGC,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"),			&EXPLOITS,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"),			&GRIEFING,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"),	&COMMENDSTRENGTH,	-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"),			&FRIENDLY,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"),			&HELPFUL,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"),		&VCANNOYINGME,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"),			&VCHATE,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"),		&BADCREWNAME,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"),		&BADCREWMOTTO,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"),	&BADCREWSTATUS,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"),	&BADCREWEMBLEM,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"),			&ISPUNISHED,		-1);
			GUI::Option("Report Strength: " + std::to_string(REPORTSTRENGTH), "");
			GUI::Option("Game Exploits: " + std::to_string(intexploits), "");
			GUI::Option("Offensive Language: " + std::to_string(intoffensive), "");
			GUI::Option("Offensive Tagplate: " + std::to_string(OFFENSIVETAGPLATE), "");
			GUI::Option("Offensive UGC: " + std::to_string(OFFENSIVEUGC), "");
			GUI::Option("Exploits: " + std::to_string(EXPLOITS), "");
			GUI::Option("Griefing: " + std::to_string(GRIEFING), "");
			GUI::Option("Friendly: " + std::to_string(FRIENDLY), "");
			GUI::Option("Helpful: " + std::to_string(HELPFUL), "");
			GUI::Option("VC Annoying Me: " + std::to_string(VCANNOYINGME), "");
			GUI::Option("Vchate: " + std::to_string(VCHATE), "");
			GUI::Option("Bad Crew Name: " + std::to_string(BADCREWNAME), "");
			GUI::Option("Bad Crew Motto: " + std::to_string(BADCREWMOTTO), "");
			GUI::Option("Bad Crew Status: " + std::to_string(BADCREWSTATUS), "");
			GUI::Option("Bad Crew Emblem: " + std::to_string(BADCREWEMBLEM), "");
			GUI::Option("Is Punished: " + std::to_string(ISPUNISHED), "");
		}
		break;
		case SelfModelMenu:
		{
			GUI::Title("Model");
			if (GUI::Option("Custom Input", "Input custom Ped model"))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter custom ped model name");
				if (KeyboardInput == "0") { break; }
				DWORD model = GAMEPLAY::GET_HASH_KEY(KeyboardInput);
				if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
				{
					GameFunctions::MinimapNotification("~r~That is not a valid ped model");
				}
				else
				{
					GameFunctions::ChangePedModelLocalPlayer(model);
				}
			}
			GUI::Break("Ped List", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Search", "Enter keywords to filter peds list"))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter search term");
				if (KeyboardInput == "0") { break; }
				ChangeModelPedSearchTerm = KeyboardInput;
				std::transform(ChangeModelPedSearchTerm.begin(), ChangeModelPedSearchTerm.end(), ChangeModelPedSearchTerm.begin(), tolower);
			}
			if (!ChangeModelPedSearchTerm.empty())
			{
				if (GUI::Option("Clear Search Results", ""))
				{
					ChangeModelPedSearchTerm.clear();
				}
				GUI::Break("Search Results", SELECTABLE_CENTER_TEXT);
			}
			for (auto const& i : GameArrays::PedModels)
			{
				std::string i_lowercase = i;
				std::transform(i_lowercase.begin(), i_lowercase.end(), i_lowercase.begin(), tolower);
				if (ChangeModelPedSearchTerm.empty() || i_lowercase.find(ChangeModelPedSearchTerm) != std::string::npos)
				{
					if (GUI::Option(i, ""))
					{
						GameFunctions::ChangePedModelLocalPlayer(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)));
					}
				}
			}
		}
		break;
		case SpawnedVehiclesMenu:
		{
			GUI::Title("Spawned Vehicles");
			if (!GameArrays::SpawnedVehicles.empty())
			{
				for (Vehicle i : GameArrays::SpawnedVehicles)
				{
					if (!ENTITY::DOES_ENTITY_EXIST(i)) { GameArrays::SpawnedVehicles.erase(std::remove(GameArrays::SpawnedVehicles.begin(), GameArrays::SpawnedVehicles.end(), i), GameArrays::SpawnedVehicles.end()); }			
					GUI::Break(std::to_string(i), SELECTABLE_CENTER_TEXT);
					if (GUI::Option("Teleport To", ""))
					{
						GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, GameFunctions::GetEntityCoords(i), false, false);
					}
					if (GUI::Option("Teleport Into Vehicle", ""))
					{
						PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, i, -1);
					}
					if (GUI::Option("Repair & Clean Vehicle", ""))
					{
						GameFunctions::RepairAndCleanVehicle(i);
					}
					if (GUI::Option("Delete", ""))
					{
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(i, true, true);
						VEHICLE::DELETE_VEHICLE(&i);
					}
				}
			}
			else
			{
				GUI::Break("No Vehicles Were Spawned Yet");
			}
		}
		break;
		case VehicleSpawnMenu:
		{
			GUI::Title("Vehicle Spawn");
			GUI::MenuOption("Settings", VehicleSpawnSettings);
			GUI::MenuOption("Spawned Vehicles", SpawnedVehiclesMenu);
			if (GUI::Option("Custom Input", "Input custom vehicle model name"))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter Vehicle Model Name");
				if (KeyboardInput == "0") { break; }
				GameFunctions::SpawnVehicle(KeyboardInput);
			}
			GUI::Break("Categories", SELECTABLE_CENTER_TEXT);
			GUI::MenuOption("DLC Vehicles", DLCVehiclesMenu);
			GUI::MenuOption("Super", Super);
			GUI::MenuOption("Sports", Sports);
			GUI::MenuOption("Sport Classic", SportClassic);
			GUI::MenuOption("Offroad", Offroad);
			GUI::MenuOption("Sedans", Sedans);
			GUI::MenuOption("Coupes", Coupes);
			GUI::MenuOption("Muscle", Muscle);
			GUI::MenuOption("Boats", Boats);
			GUI::MenuOption("Commercial", Commercial);
			GUI::MenuOption("Compacts", Compacts);
			GUI::MenuOption("Cycles", Cycles);
			GUI::MenuOption("Emergency", Emergency);
			GUI::MenuOption("Helicopters", Helicopters);
			GUI::MenuOption("Industrial", Industrial);
			GUI::MenuOption("Military", Military);
			GUI::MenuOption("Motorcycles", Motorcycles);
			GUI::MenuOption("Planes", Planes);
			GUI::MenuOption("Service", Service);
			GUI::MenuOption("SUV", SUV);
			GUI::MenuOption("Trailer", Trailer);
			GUI::MenuOption("Trains", Trains);
			GUI::MenuOption("Utility", Utility);
			GUI::MenuOption("Vans", Vans);
		}
		break;
		case SpawnMenu:
		{
			GUI::Title("Spawn");
			//GUI::MenuOption("Ped", PedSpawnMenu);
			GUI::MenuOption("Vehicle", VehicleSpawnMenu);
			//GUI::MenuOption("Object", ObjectSpawnMenu);
		}
		break;
		case ObjectSpawnMenu:
		{
			GUI::Title("Object Spawn");
			GUI::Break("Object List", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Search", "Enter keywords to filter object list"))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter search term");
				if (KeyboardInput == "0") { break; }
				ObjectSpawnSearchTerm = KeyboardInput;
				std::transform(ObjectSpawnSearchTerm.begin(), ObjectSpawnSearchTerm.end(), ObjectSpawnSearchTerm.begin(), tolower);
			}
			if (!ObjectSpawnSearchTerm.empty())
			{
				if (GUI::Option("Clear Search Results", ""))
				{
					ObjectSpawnSearchTerm.clear();
				}
				GUI::Break("Search Results", SELECTABLE_CENTER_TEXT);
			}
			for (auto& i : GameArrays::Objects)
			{
				std::string i_lowercase = i;
				std::transform(i_lowercase.begin(), i_lowercase.end(), i_lowercase.begin(), tolower);
				if (ObjectSpawnSearchTerm.empty() || i_lowercase.find(ObjectSpawnSearchTerm) != std::string::npos)
				{
					if (GUI::Option(i, "Select to spawn"))
					{
						
					}
				}
			}
		}
		break;
		case PedSpawnMenu:
		{
			GUI::Title("Ped Spawn");
			GUI::Break("WIP");
			/*
			GUI::Break("List", true);
			for (auto const& i : GameArrays::PedModels)
			{
				if (GUI::Option(i, "Select to spawn"))
				{

				}
			}
			*/
		}
		break;
		case DLCVehiclesMenu:
		{
			GUI::Title("DLC Vehicles");
			GUI::MenuOption("The Contract", TheContractDLCMenu);
			GUI::MenuOption("Los Santos Tuners", LosSantosTunersDLCMenu);
			GUI::MenuOption("The Cayo Perico Heist", CayoPericoHeistDLCMenu);
			GUI::MenuOption("2020 Summer Special", SummerSpecialDLCMenu);
			GUI::MenuOption("The Diamond Casino Heist", diamondcasinoheist);
			GUI::MenuOption("The Diamond Casino & Resort", casinodlc);
			GUI::MenuOption("Arena War", arenawardlc);
			GUI::MenuOption("After Hours", afterhoursdlc);
			GUI::MenuOption("SSASSS", SSASSSDLC);
			GUI::MenuOption("The Doomsday Heist", doomsdayheistdlc);
			GUI::MenuOption("Smuggler's Run", smugglersrun);
			GUI::MenuOption("Gunrunning", gunrunningdlc);
			GUI::MenuOption("Cunning Stunts", CunningStuntsDLCMenu);
		}
		break;
		case TheContractDLCMenu:
		{
			GUI::Title("The Contract");
			for (auto const& i : GameArrays::TheContractModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case LosSantosTunersDLCMenu:
		{
			GUI::Title("Los Santos Tuners");
			for (auto const& i : GameArrays::LosSantosTunersModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case CayoPericoHeistDLCMenu:
		{
			GUI::Title("The Cayo Perico Heist");
			for (auto const& i : GameArrays::CayoPericoHeistModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SummerSpecialDLCMenu:
		{
			GUI::Title("2020 Summer Special");
			for (auto const& i : GameArrays::SummerSpecialModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case CunningStuntsDLCMenu:
		{
			GUI::Title("Cunning Stunts");
			for (auto const& i : GameArrays::CunningStuntsDLCModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case diamondcasinoheist:
		{
			GUI::Title("The Diamond Casino Heist");
			for (auto const& i : GameArrays::DiamondCasinoHeistDLCModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case casinodlc:
		{
			GUI::Title("The Diamond Casino & Resort");
			for (auto const& i : GameArrays::CasinoDLCModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case arenawardlc:
		{
			GUI::Title("Arena War");
			for (auto const& i : GameArrays::ArenaWarModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case smugglersrun:
		{
			GUI::Title("Smuggler's Run");
			for (auto const& i : GameArrays::SmugglersRunModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Super:
		{
			GUI::Title("Super");
			for (auto const& i : GameArrays::SuperModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Sports:
		{
			GUI::Title("Sports");
			for (auto const& i : GameArrays::SportModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SportClassic:
		{
			GUI::Title("Sports Classic");
			for (auto const& i : GameArrays::SportClassicModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Offroad:
		{
			GUI::Title("Offroad");
			for (auto const& i : GameArrays::OffRoadModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Sedans:
		{
			GUI::Title("Sedans");
			for (auto const& i : GameArrays::SedanModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Coupes:
		{
			GUI::Title("Coupes");
			for (auto const& i : GameArrays::CoupesModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Muscle:
		{
			GUI::Title("Muscle");
			for (auto const& i : GameArrays::MuscleModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Boats:
		{
			GUI::Title("Boats");
			for (auto const& i : GameArrays::BoatModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Commercial:
		{
			GUI::Title("Commercial");
			for (auto const& i : GameArrays::CommercialModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Compacts:
		{
			GUI::Title("Compacts");
			for (auto const& i : GameArrays::CompactsModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Cycles:
		{
			GUI::Title("Cycles");
			for (auto const& i : GameArrays::CycleModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Emergency:
		{
			GUI::Title("Emergency");
			for (auto const& i : GameArrays::EmergencyModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Helicopters:
		{
			GUI::Title("Helicopters");
			for (auto const& i : GameArrays::HelicopterModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Industrial:
		{
			GUI::Title("Industrial");
			for (auto const& i : GameArrays::IndustrialModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Military:
		{
			GUI::Title("Military");
			for (auto const& i : GameArrays::MilitaryModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Motorcycles:
		{
			GUI::Title("Motorcycles");
			for (auto const& i : GameArrays::MotorcycleModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Planes:
		{
			GUI::Title("Planes");
			for (auto const& i : GameArrays::PlaneModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Service:
		{
			GUI::Title("Service");
			for (auto const& i : GameArrays::ServiceModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SUV:
		{
			GUI::Title("SUV");
			for (auto const& i : GameArrays::SUVModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Trailer:
		{
			GUI::Title("Trailer");
			for (auto const& i : GameArrays::TrailerModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Trains:
		{
			GUI::Title("Trains");
			for (auto const& i : GameArrays::TrainModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Utility:
		{
			GUI::Title("Utility");
			for (auto const& i : GameArrays::UtilityModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Vans:
		{
			GUI::Title("Vans");
			for (auto const& i : GameArrays::VanModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SSASSSDLC:
		{
			GUI::Title("SSASSS");
			for (auto const& i : GameArrays::SSASSSModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case doomsdayheistdlc:
		{
			GUI::Title("The Doomsday Heist");
			for (auto const& i : GameArrays::DoomsdayModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case gunrunningdlc:
		{
			GUI::Title("Gunrunning");
			for (auto const& i : GameArrays::GunrunningModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case afterhoursdlc:
		{
			GUI::Title("After Hours");
			for (auto const& i : GameArrays::AfterHoursModels)
			{
				if (GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case vehiclemenu:
		{
			GUI::Title("Vehicle");
			GUI::MenuOption("Los Santos Customs", VehicleCustomizerMenu);
			GUI::MenuOption("Vehicle Weapons", vehicleweaponsmenu);
			if (GUI::Option("Delete Vehicle", "Delete the current vehicle"))
			{
				if (!GameFunctions::DeleteVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID))) 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}		
			}
			if (GUI::Option("Flip Up", "Flip vehicle up")) { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false)); }
			if (GUI::Option("Set Max Vehicle Speed", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, false)) 
				{
					int MaxSpeedInput = GameFunctions::DisplayKeyboardAndReturnInputInteger(3, "Enter the desired max speed");
					if (MaxSpeedInput == 0) { GameFunctions::MinimapNotification("Canceled setting Max Vehicle Speed"); break; }
					Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID);
					if (CheatFeatures::MeasurementSystemVectorPosition == 0)
					{
						ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, GameFunctions::KMHToMS(MaxSpeedInput));
						GameFunctions::MinimapNotification("Max Speed Set (KM/H)");
					}
					else if (CheatFeatures::MeasurementSystemVectorPosition == 1)
					{
						ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, GameFunctions::MPHToMS(MaxSpeedInput));
						GameFunctions::MinimapNotification("Max Speed Set (MP/H)");
					}
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}	
			GUI::Toggle("Vehicle Invincibility", CheatFeatures::VehicleGodmodeBool, "Makes current vehicle invincible");
			GUI::Toggle("Vehicle Invisibility", CheatFeatures::VehicleInvisibleBool, "Makes current vehicle invisible");
			GUI::Toggle("Vehicle Horn Boost", CheatFeatures::VehicleHornBoostBool, "Press horn button to use");
			GUI::Toggle("Unlimited Rocket Boost", CheatFeatures::UnlimitedRocketBoostBool, "");
			GUI::StringVector("Speedometer", { "Disabled", "On-Screen", "License Plate", "Both" }, CheatFeatures::SpeedometerVectorPosition, "Set speedometer");
			GUI::Toggle("Rainbow Vehicle", CheatFeatures::RainbowVehicleBool, "Loops rainbow colors on current vehicle");
			GUI::Toggle("Drive On Water", CheatFeatures::DriveOnWaterBool, "Drive your vehicle on water");
			GUI::Toggle("Super Brakes", CheatFeatures::SuperBrakesBool, "");
		}
		break; 
		case VehicleCustomizerMenu:
		{
			GUI::Title("Los Santos Customs");
			if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, false))
			{
				if (GUI::Option("Repair & Clean", "Repair & Clean current vehicle"))
				{
					GameFunctions::RepairAndCleanVehicle(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID));
				}
				if (GUI::Option("Max Upgrade", "Max Upgrade current vehicle"))
				{
					GameFunctions::MaxUpgradeVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
					GameFunctions::AdvancedMinimapNotification("Vehicle Max Upgraded", "Textures", "AdvancedNotificationImage", false, 4, "Los Santos Customs", "", 1.0, "");
				}
				if (GUI::Option("Max Downgrade", "Max downgrade current vehicle"))
				{
					GameFunctions::MaxDowngradeVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
					GameFunctions::AdvancedMinimapNotification("Vehicle Max Downgraded", "Textures", "AdvancedNotificationImage", false, 4, "Los Santos Customs", "", 1.0, "");
				}
				if (GUI::Option("Add Blip Registration", "Add Blip To Current Vehicle"))
				{
					GameFunctions::AddBlipToVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
				}
				if (GUI::Option("Change License Plate Text", "Input custom vehicle license plate text"))
				{
					char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(8, "Enter new license plate text");
					if (KeyboardInput == "0") { break; }
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), KeyboardInput);
					GameFunctions::AdvancedMinimapNotification("License Plate Text Updated", "Textures", "AdvancedNotificationImage", false, 4, "Los Santos Customs", "", 1.0, "");
				}
				GUI::MenuOption("Color", VehicleCustomizerColorMenu);
				GUI::MenuOption("Neon", vehicle_lsc_neon_options);
				GUI::MenuOption("Multipliers", vehiclemultipliersmenus);
				GUI::Break("Doors", SELECTABLE_CENTER_TEXT);
				if (GUI::StringVector("Open", { "Front Left", "Front Right", "Back Left", "Back Right", "Hood", "Trunk", "Back", "Back2" }, CheatFeatures::OpenVehicleDoorPosition, "Select to open door"))
				{
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), CheatFeatures::PedMovementVectorPosition, false, false);
				}
				if (GUI::StringVector("Close", { "Front Left", "Front Right", "Back Left", "Back Right", "Hood", "Trunk", "Back", "Back2" }, CheatFeatures::CloseVehicleDoorPosition, "Select to close door"))
				{
					VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), CheatFeatures::PedMovementVectorPosition, true);
				}
			}
			else
			{
				GUI::Break("Player is not in a vehicle");
			}
		}
		break;
		case VehicleCustomizerColorMenu:
		{
			GUI::Title("Custom Color");
			GUI::Int("Primary Color: Red", VehiclePrimaryColorRed, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Primary Color: Green", VehiclePrimaryColorGreen, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Primary Color: Blue", VehiclePrimaryColorBlue, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			if (GUI::Option("Set Primary Color", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, VehiclePrimaryColorRed, VehiclePrimaryColorGreen, VehiclePrimaryColorBlue);
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			GUI::Int("Secondary Color: Red", VehicleSecondaryColorRed, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Secondary Color: Green", VehicleSecondaryColorGreen, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Secondary Color: Blue", VehicleSecondaryColorBlue, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			if (GUI::Option("Set Secondary Color", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, VehicleSecondaryColorRed, VehicleSecondaryColorGreen, VehicleSecondaryColorBlue);
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
		}
		break;
		case vehicle_lsc_color_options:
		{
			GUI::Title("Color");
			if (GUI::Option("Random", "Get random color")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
				{
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				}
			}
			GUI::MenuOption("Custom Color", VehicleCustomizerColorMenu);
			GUI::Break("~bold~Color Presets", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Chrome", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
			}
			if (GUI::Option("Black", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("White", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Red", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Blue", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Orange", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 128, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Yellow", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Purple", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 204, 0, 204);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Grey", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 96, 96, 96);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Brown", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 165, 42, 42);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Pink", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 51, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Cool Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 196);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Hot Pink", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 145);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Lime", "")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 128, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Lava Red", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 60, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Mint Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 119);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (GUI::Option("Neon Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 187, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
		}
		break;
		case vehicle_lsc_neon_options:
		{
			GUI::Title("Neon");
			if (GUI::Option("Enable Neons", "Enable Vehicle Neons")) 
			{
				for (int i = 0; i <= 7; i++)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false), i, true);
				}
			}
			if (GUI::Option("Disable Neons", "Disable Vehicle Neons")) 
			{
				for (int i = 0; i <= 7; i++)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false), i, false);
				}
			}
			GUI::Int("Neon Color: Red", VehicleNeonLightRed, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Neon Color: Green", VehicleNeonLightGreen, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Neon Color: Blue", VehicleNeonLightBlue, 0, 255, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			if (GUI::Option("Set Neon Color", "Set Vehicle Neon Colors")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, VehicleNeonLightRed, VehicleNeonLightGreen, VehicleNeonLightBlue);
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			GUI::Break("Neon Presets", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Red", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 0, 0);
			}
			if (GUI::Option("Green", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 255, 0);
			}
			if (GUI::Option("Blue", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 0, 255);
			}
			if (GUI::Option("Hot Pink", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 226, 35, 157);
			}
			if (GUI::Option("Yellow", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 244, 0);
			}
			if (GUI::Option("Orange", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 91, 0);
			}
			if (GUI::Option("Aqua", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 40, 255, 255);
			}
			if (GUI::Option("White", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 255, 255);
			}
			if (GUI::Option("Magenta", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 102, 0, 35);
			}
			if (GUI::Option("Purple", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 53, 0, 83);
			}
			if (GUI::Option("Dark Green", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 118, 0);
			}
			if (GUI::Option("Rose Red", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 161, 0, 0);
			}
		}
		break;
		case vehiclemultipliersmenus:
		{
			GUI::Title("Multipliers");	
			GUI::Int("Engine Multiplier", engine_multiplier, 0, 1000, 1, "Set Engine Multiplier value", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Engine Torque Multiplier", torque_multiplier, 0, 1000, 1, "Set engine torque multiplier value", SELECTABLE_RETURN_VALUE_CHANGE);
			if (GUI::Option("Set", "Set Multiplier")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle CurrentVehicle = PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID);
					VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(CurrentVehicle, engine_multiplier); // Engine Multiplier
					VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(CurrentVehicle, torque_multiplier); // Engine Torque Multiplier
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
		}
		break;
		case vehicleweaponsmenu:
		{
			GUI::Title("Vehicle Weapons");
			GUI::Toggle("Toggle Vehicle Weapons", CheatFeatures::VehicleWeaponsBool, "Press horn button to use");
			GUI::Toggle("Show Lines", CheatFeatures::VehicleWeapons_DrawLaser, "Show lines in front of vehicle");
			if (CheatFeatures::VehicleWeapons_TankRounds) 
			{
				GUI::Break("Current: ~c~Tank Rounds");
			}
			if (CheatFeatures::VehicleWeapons_VehicleRockets) 
			{
				GUI::Break("Current: ~c~Vehicle Rockets");
			}
			if (CheatFeatures::VehicleWeapons_Fireworks) 
			{
				GUI::Break("Current: ~c~Fireworks");
			}
			if (GUI::Option("Tank Rounds", "")) 
			{
				CheatFeatures::VehicleWeapons_TankRounds = true;
				CheatFeatures::VehicleWeapons_Fireworks = false;
				CheatFeatures::VehicleWeapons_VehicleRockets = false;
			}
			if (GUI::Option("Vehicle Rockets", "")) 
			{
				CheatFeatures::VehicleWeapons_VehicleRockets = true;
				CheatFeatures::VehicleWeapons_Fireworks = false;
				CheatFeatures::VehicleWeapons_TankRounds = false;
			}
			if (GUI::Option("Fireworks", "")) 
			{
				CheatFeatures::VehicleWeapons_Fireworks = true;
				CheatFeatures::VehicleWeapons_TankRounds = false;
				CheatFeatures::VehicleWeapons_VehicleRockets = false;
			}
		}
		break;
		case VehicleSpawnSettings:
		{
			GUI::Title("Vehicle Spawn Settings");
			GUI::Toggle("Spawn Inside", CheatFeatures::VehicleSpawnerSpawnInsideVehicle, "");
			GUI::Toggle("Spawn Invincible", CheatFeatures::VehicleSpawnerSpawnWithGodmode, "");
			GUI::Toggle("Spawn Max Upgraded", CheatFeatures::VehicleSpawnerSpawnMaxUpgraded, "");
			GUI::Toggle("Delete Current", CheatFeatures::VehicleSpawnerDeleteOldVehicle, "");
			GUI::Toggle("Spawn With Blip", CheatFeatures::VehicleSpawnerSpawnWithBlip, "");
			GUI::Toggle("Spawn Air Vehicles In The Air", CheatFeatures::VehicleSpawnerSpawnAirVehicleAir, "");
		}
		break; 
		case worldmenu:
		{
			GUI::Title("World");
			GUI::MenuOption("Time", timemenu);
			GUI::MenuOption("Weather", weathermenu);
			GUI::MenuOption("Nearby Vehicles", nearbyvehicles_menu);
			GUI::MenuOption("Nearby Peds", nearbypeds_menu); 
			GUI::Toggle("Snow", CheatFeatures::WorldSnowLocalBool, "GTA Online Only");
			GUI::Toggle("No Gravity", CheatFeatures::NoGravityBool, "Disable gravity in the world");
			GUI::Toggle("Blackout", CheatFeatures::WorldBlackoutBool, "Disable All Map Lights");
			if (GUI::Option("Clear Area", "Clear area of vehicles, objects etc")) 
			{
				Vector3 MyPos = GameFunctions::GetEntityCoords(GameFunctions::PlayerPedID);
				GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 250, true, false, false, false);
				GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 250, false, false, false, false, false);
				GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_PROJECTILES(MyPos.x, MyPos.y, MyPos.z, 250, false);

				// Seperate Remove Nearby Vehicles: for spawned vehicles
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false))
					{
						GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						ENTITY::DELETE_ENTITY(&vehs[OffsetID]);
					}
				}
				delete[] vehs;
				GameFunctions::MinimapNotification("Area Cleared");
			}
		}
		break; 
		case nearbypeds_menu:
		{
			GUI::Title("Nearby Peds");
			if (GUI::Option("Explode Peds", "Explode nearby peds"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Ped *peds = new Ped[ArrSize];
				peds[0] = ElementAmount;

				int PedFound = PED::GET_PED_NEARBY_PEDS(GameFunctions::PlayerPedID, peds, -1);

				for (int i = 0; i < PedFound; i++)
				{
					int OffsetID = i * 2 + 2;
					GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
					if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && GameFunctions::PlayerPedID != peds[OffsetID])
					{
						Vector3 pos = GameFunctions::GetEntityCoords(peds[OffsetID]);
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 0, 1000.f, true, false, 0.f);
					}
				}
			}
			if (GUI::Option("Kill Peds", "Kill nearby peds"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Ped *peds = new Ped[ArrSize];
				peds[0] = ElementAmount;

				int PedFound = PED::GET_PED_NEARBY_PEDS(GameFunctions::PlayerPedID, peds, -1);

				for (int i = 0; i < PedFound; i++)
				{
					int OffsetID = i * 2 + 2;
					GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
					if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && GameFunctions::PlayerPedID != peds[OffsetID])
					{
						PED::APPLY_DAMAGE_TO_PED(peds[OffsetID], 1000, false);
					}
				}
			}
		}
		break; 
		case nearbyvehicles_menu:
		{
			GUI::Title("Nearby Vehicles");
			if (GUI::Option("Explode Vehicles", "Explode nearby vehicles"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false))
					{
						GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						Vector3 coords = GameFunctions::GetEntityCoords(vehs[OffsetID]);
						FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f);
					}
				}
				delete[] vehs;
			}
			if (GUI::Option("Delete Vehicles", "Delete nearby vehicles"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false))
					{
						GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
					}
				}
				delete[] vehs;
			}
			if (GUI::Option("Boost Vehicles", "Speed boost nearby vehicles"))
			{
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				Vehicle veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_VEHICLES(GameFunctions::PlayerPedID, veh);
				if (veh != NULL)
				{
					for (int i = 1; i <= count; i++)
					{
						int offsettedID = i;
						if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
						{
							GameFunctions::RequestNetworkControlOfEntity(veh[offsettedID]);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh[offsettedID], 10000.0f);
						}
					}
				}
			}
		}
		break;
		case timemenu:
		{
			GUI::Title("Time");
			if (GUI::Int("Hour", SetTimeHour, 0, 23, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(SetTimeHour, TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS()); }
			if (GUI::Int("Minutes", SetTimeMinutes, 0, 59, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), SetTimeMinutes, TIME::GET_CLOCK_SECONDS()); }
			if (GUI::Int("Seconds", SetTimeSeconds, 0, 59, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), TIME::GET_CLOCK_MINUTES(), SetTimeSeconds); }
			GUI::Break("Current Time", SELECTABLE_CENTER_TEXT);
			std::string CurrentGameTimeString = "Game Time: ~c~" + std::to_string(TIME::GET_CLOCK_HOURS()) + ":" + std::to_string(TIME::GET_CLOCK_MINUTES()) + ":" + std::to_string(TIME::GET_CLOCK_SECONDS());
			GUI::Break(CurrentGameTimeString.c_str(), false);
			std::string CurrentSystemTimeString = "System Time: ~c~" + CheatFunctions::ReturnDateTimeFormatAsString("%H:%M:%S");
			GUI::Break(CurrentSystemTimeString.c_str());
			GUI::Break("Miscellaneous", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Slow Motion", CheatFeatures::SlowMotionBool, "Slows Down Game Time");
			GUI::Toggle("Pause Time", CheatFeatures::PauseTimeBool, "Pause Game Time");
		}
		break;
		case weathermenu:
		{
			GUI::Title("Weather");
			if (GUI::Option("Reset Weather", ""))
			{
				GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
			}
			GUI::Break("Types", SELECTABLE_CENTER_TEXT);
			for (int i = 0; i < GameArrays::WeatherTypes.size(); i++)
			{
				if (GUI::Option(GameArrays::WeatherTypes[i].SelectableName, ""))
				{ 
					GAMEPLAY::SET_OVERRIDE_WEATHER(CheatFunctions::StringToChar(GameArrays::WeatherTypes[i].WeatherType));
				}
			}
		}
		break;
		case ESPMenu:
		{
			GUI::Title("Extra-sensory Perception");
			GUI::Toggle("Basic Player ESP", CheatFeatures::PlayerESPBool, "");
		}
		break;
		case RadioMenu:
		{
			GUI::Title("Radio");
			if (GUI::Option("Skip Track", "")) { AUDIO::SKIP_RADIO_FORWARD(); }
			GUI::Toggle("Freeze Station", CheatFeatures::FreezeStationBool, "");
			GUI::Toggle("Mobile Radio", CheatFeatures::MobileRadioBool, "");
		}
		break;
		case miscmenu:
		{
			GUI::Title("Miscellaneous");
			GUI::MenuOption("Report Statistics", reportsmenu_stats);
			GUI::MenuOption("Radio", RadioMenu);
			GUI::MenuOption("Extra-sensory Perception", ESPMenu);
			GUI::MenuOption("HUD", hudmenu); 
			GUI::MenuOption("IPL Loader", iplloader);
			if (GUI::Int("Fake Wanted Level", FakeWantedLevelInteger, 0, 6, 1, "Select to change", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE))
			{
				GAMEPLAY::SET_FAKE_WANTED_LEVEL(FakeWantedLevelInteger);
			}
			GUI::Toggle("Disable Phone", CheatFeatures::DisablePhoneBool, "Disable phone controls");
			GUI::Toggle("No-Clip", CheatFeatures::NoClipBool, "Use W and mouse to control");
			GUI::Toggle("Jump Around Mode", CheatFeatures::JumpAroundModeBool, "Nearby vehicles will 'jump around'");
			GUI::Toggle("Free Cam", CheatFeatures::FreeCamBool, "Use W and S to control. Shift to go faster");
			GUI::Toggle("Show Joining Players Notification", CheatFeatures::ShowJoiningPlayersNotification, "");
			GUI::Toggle("Rockstar Developer Mode", CheatFeatures::GTAODeveloperMode, "Toggles GTAO Spectator Options");
			GUI::Toggle("Show Session Information", CheatFeatures::ShowSessionInformationBool, "Show session info (next to radar)");
			GUI::Toggle("Show FPS", CheatFeatures::ShowFPSBool, "");
			if (GUI::Option("Stop Cutscene", ""))
			{
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			}
			if (GUI::Option("Stop spectating player", ""))
			{
				CheatFeatures::SpectatePlayerBool = false;
			}
			if (GUI::Option("Drive To Waypoint", "A NPC drives you to waypoint"))
			{
				int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(SpriteWaypoint);
				if (UI::DOES_BLIP_EXIST(WaypointHandle))
				{
					std::string VehicleName = "MARSHALL";
					Vector3 WayPointVector = UI::GET_BLIP_COORDS(WaypointHandle);
					STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)));
					while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)))) { GameHooking::PauseMainFiber(0); }
					Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0, 5.0, 0);
					Vehicle VehicleHandle = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)), pos.x, pos.y, pos.z, ENTITY::GET_ENTITY_HEADING(GameFunctions::PlayerPedID), 1, 1);
					if (VehicleHandle != 0)
					{
						Ped Driver = PED::CREATE_RANDOM_PED_AS_DRIVER(VehicleHandle, false);
						PED::SET_PED_INTO_VEHICLE(Driver, VehicleHandle, -1);
						PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, VehicleHandle, 0);
						AI::TASK_VEHICLE_DRIVE_TO_COORD(Driver, VehicleHandle, WayPointVector.x, WayPointVector.y, WayPointVector.z, 40, 1, ENTITY::GET_ENTITY_MODEL(VehicleHandle), 7, 6, -1);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, "CRUSADER");
						GameFunctions::MinimapNotification("NPC Driver Spawned");
					}
				}
				else { GameFunctions::MinimapNotification("Please set a waypoint first to use this feature"); }
			}		
			if (GUI::Option("Get Empty Session", "Get Empty (Public) Session")) { Sleep(10000); }
			if (GUI::Option("Exit to Single Player", "")) { NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME(); }
			if (GUI::Option("Close Game", "You must hold spacebar to prevent accidental closure")) { if (CheatFunctions::IsKeyCurrentlyPressed(VK_SPACE)) { std::exit(EXIT_SUCCESS); } }
		}
		break;
		case hudmenu:
		{
			GUI::Title("HUD");
			GUI::Toggle("Disable HUD", CheatFeatures::DisableHUDBool, "Prevents all HUD elements from being visible");
			GUI::Toggle("Hide Minimap", CheatFeatures::HideMinimapBool, "Not needed when Disable HUD is enabled");
			GUI::Break("Color", SELECTABLE_CENTER_TEXT);
			GUI::Int("Red", HUDColorRed, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Green", HUDColorGreen, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Blue", HUDColorBlue, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Alpha", HUDColorAlpha, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE);
			if (GUI::Option("Change", ""))
			{
				for (int i = 0; i <= 223; i++)
				{
					UI::_SET_HUD_COLOUR(i, HUDColorRed, HUDColorGreen, HUDColorBlue, HUDColorAlpha);
				}		
			}
		}
		break; 
		case iplloader:
		{
			GUI::Title("IPL Loader");
			if (GUI::Option("Load MP data", ""))
			{
				DLC2::ON_ENTER_MP();
			}
			if (GUI::Option("Unload MP data", ""))
			{
				DLC2::ON_ENTER_SP();
			}
			if (GUI::Option("Load North Yankton", ""))
			{
				STREAMING::REQUEST_IPL("plg_01");
				STREAMING::REQUEST_IPL("prologue01");
				STREAMING::REQUEST_IPL("prologue01_lod");
				STREAMING::REQUEST_IPL("prologue01c");
				STREAMING::REQUEST_IPL("prologue01c_lod");
				STREAMING::REQUEST_IPL("prologue01d");
				STREAMING::REQUEST_IPL("prologue01d_lod");
				STREAMING::REQUEST_IPL("prologue01e");
				STREAMING::REQUEST_IPL("prologue01e_lod");
				STREAMING::REQUEST_IPL("prologue01f");
				STREAMING::REQUEST_IPL("prologue01f_lod");
				STREAMING::REQUEST_IPL("prologue01g");
				STREAMING::REQUEST_IPL("prologue01h");
				STREAMING::REQUEST_IPL("prologue01h_lod");
				STREAMING::REQUEST_IPL("prologue01i");
				STREAMING::REQUEST_IPL("prologue01i_lod");
				STREAMING::REQUEST_IPL("prologue01j");
				STREAMING::REQUEST_IPL("prologue01j_lod");
				STREAMING::REQUEST_IPL("prologue01k");
				STREAMING::REQUEST_IPL("prologue01k_lod");
				STREAMING::REQUEST_IPL("prologue01z");
				STREAMING::REQUEST_IPL("prologue01z_lod");
				STREAMING::REQUEST_IPL("plg_02");
				STREAMING::REQUEST_IPL("prologue02");
				STREAMING::REQUEST_IPL("prologue02_lod");
				STREAMING::REQUEST_IPL("plg_03");
				STREAMING::REQUEST_IPL("prologue03");
				STREAMING::REQUEST_IPL("prologue03_lod");
				STREAMING::REQUEST_IPL("prologue03b");
				STREAMING::REQUEST_IPL("prologue03b_lod");
				STREAMING::REQUEST_IPL("prologue03_grv_dug");
				STREAMING::REQUEST_IPL("prologue03_grv_dug_lod");
				STREAMING::REQUEST_IPL("prologue_grv_torch");
				STREAMING::REQUEST_IPL("plg_04");
				STREAMING::REQUEST_IPL("prologue04");
				STREAMING::REQUEST_IPL("prologue04_lod");
				STREAMING::REQUEST_IPL("prologue04b");
				STREAMING::REQUEST_IPL("prologue04b_lod");
				STREAMING::REQUEST_IPL("prologue04_cover");
				STREAMING::REQUEST_IPL("des_protree_end");
				STREAMING::REQUEST_IPL("des_protree_start");
				STREAMING::REQUEST_IPL("des_protree_start_lod");
				STREAMING::REQUEST_IPL("plg_05");
				STREAMING::REQUEST_IPL("prologue05");
				STREAMING::REQUEST_IPL("prologue05_lod");
				STREAMING::REQUEST_IPL("prologue05b");
				STREAMING::REQUEST_IPL("prologue05b_lod");
				STREAMING::REQUEST_IPL("plg_06");
				STREAMING::REQUEST_IPL("prologue06");
				STREAMING::REQUEST_IPL("prologue06_lod");
				STREAMING::REQUEST_IPL("prologue06b");
				STREAMING::REQUEST_IPL("prologue06b_lod");
				STREAMING::REQUEST_IPL("prologue06_int");
				STREAMING::REQUEST_IPL("prologue06_int_lod");
				STREAMING::REQUEST_IPL("prologue06_pannel");
				STREAMING::REQUEST_IPL("prologue06_pannel_lod");
				STREAMING::REQUEST_IPL("prologue_m2_door");
				STREAMING::REQUEST_IPL("prologue_m2_door_lod");
				STREAMING::REQUEST_IPL("plg_occl_00");
				STREAMING::REQUEST_IPL("prologue_occl");
				STREAMING::REQUEST_IPL("plg_rd");
				STREAMING::REQUEST_IPL("prologuerd");
				STREAMING::REQUEST_IPL("prologuerdb");
				STREAMING::REQUEST_IPL("prologuerd_lod");			
				GameFunctions::MinimapNotification("North Yankton IPL loaded");
			}
			if (GUI::Option("Unload North Yankton", ""))
			{
				STREAMING::REMOVE_IPL("plg_01");
				STREAMING::REMOVE_IPL("prologue01");
				STREAMING::REMOVE_IPL("prologue01_lod");
				STREAMING::REMOVE_IPL("prologue01c");
				STREAMING::REMOVE_IPL("prologue01c_lod");
				STREAMING::REMOVE_IPL("prologue01d");
				STREAMING::REMOVE_IPL("prologue01d_lod");
				STREAMING::REMOVE_IPL("prologue01e");
				STREAMING::REMOVE_IPL("prologue01e_lod");
				STREAMING::REMOVE_IPL("prologue01f");
				STREAMING::REMOVE_IPL("prologue01f_lod");
				STREAMING::REMOVE_IPL("prologue01g");
				STREAMING::REMOVE_IPL("prologue01h");
				STREAMING::REMOVE_IPL("prologue01h_lod");
				STREAMING::REMOVE_IPL("prologue01i");
				STREAMING::REMOVE_IPL("prologue01i_lod");
				STREAMING::REMOVE_IPL("prologue01j");
				STREAMING::REMOVE_IPL("prologue01j_lod");
				STREAMING::REMOVE_IPL("prologue01k");
				STREAMING::REMOVE_IPL("prologue01k_lod");
				STREAMING::REMOVE_IPL("prologue01z");
				STREAMING::REMOVE_IPL("prologue01z_lod");
				STREAMING::REMOVE_IPL("plg_02");
				STREAMING::REMOVE_IPL("prologue02");
				STREAMING::REMOVE_IPL("prologue02_lod");
				STREAMING::REMOVE_IPL("plg_03");
				STREAMING::REMOVE_IPL("prologue03");
				STREAMING::REMOVE_IPL("prologue03_lod");
				STREAMING::REMOVE_IPL("prologue03b");
				STREAMING::REMOVE_IPL("prologue03b_lod");
				STREAMING::REMOVE_IPL("prologue03_grv_dug");
				STREAMING::REMOVE_IPL("prologue03_grv_dug_lod");
				STREAMING::REMOVE_IPL("prologue_grv_torch");
				STREAMING::REMOVE_IPL("plg_04");
				STREAMING::REMOVE_IPL("prologue04");
				STREAMING::REMOVE_IPL("prologue04_lod");
				STREAMING::REMOVE_IPL("prologue04b");
				STREAMING::REMOVE_IPL("prologue04b_lod");
				STREAMING::REMOVE_IPL("prologue04_cover");
				STREAMING::REMOVE_IPL("des_protree_end");
				STREAMING::REMOVE_IPL("des_protree_start");
				STREAMING::REMOVE_IPL("des_protree_start_lod");
				STREAMING::REMOVE_IPL("plg_05");
				STREAMING::REMOVE_IPL("prologue05");
				STREAMING::REMOVE_IPL("prologue05_lod");
				STREAMING::REMOVE_IPL("prologue05b");
				STREAMING::REMOVE_IPL("prologue05b_lod");
				STREAMING::REMOVE_IPL("plg_06");
				STREAMING::REMOVE_IPL("prologue06");
				STREAMING::REMOVE_IPL("prologue06_lod");
				STREAMING::REMOVE_IPL("prologue06b");
				STREAMING::REMOVE_IPL("prologue06b_lod");
				STREAMING::REMOVE_IPL("prologue06_int");
				STREAMING::REMOVE_IPL("prologue06_int_lod");
				STREAMING::REMOVE_IPL("prologue06_pannel");
				STREAMING::REMOVE_IPL("prologue06_pannel_lod");
				STREAMING::REMOVE_IPL("prologue_m2_door");
				STREAMING::REMOVE_IPL("prologue_m2_door_lod");
				STREAMING::REMOVE_IPL("plg_occl_00");
				STREAMING::REMOVE_IPL("prologue_occl");
				STREAMING::REMOVE_IPL("plg_rd");
				STREAMING::REMOVE_IPL("prologuerd");
				STREAMING::REMOVE_IPL("prologuerdb");
				STREAMING::REMOVE_IPL("prologuerd_lod");			
				GameFunctions::MinimapNotification("North Yankton IPL unloaded");
			}
			if (GUI::Option("Load Heist Yacht", ""))
			{
				STREAMING::REQUEST_IPL("hei_yacht_heist");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
				STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
				STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
				STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
				GameFunctions::MinimapNotification("Heist Yacht IPL loaded");
			}
			if (GUI::Option("Unload Heist Yacht", ""))
			{
				STREAMING::REMOVE_IPL("hei_yacht_heist");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bar");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bedrm");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bridge");
				STREAMING::REMOVE_IPL("hei_yacht_heist_DistantLights");
				STREAMING::REMOVE_IPL("hei_yacht_heist_enginrm");
				STREAMING::REMOVE_IPL("hei_yacht_heist_LODLights");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Lounge");			
				GameFunctions::MinimapNotification("Heist Yacht IPL unloaded");
			}
			if (GUI::Option("Load Destroyed hospital", ""))
			{
				STREAMING::REQUEST_IPL("RC12B_Destroyed");
				STREAMING::REQUEST_IPL("RC12B_HospitalInterior");			
				GameFunctions::MinimapNotification("Destroyed Hospital IPL Loaded");
			}
			if (GUI::Option("Unload Destroyed hospital", ""))
			{
				STREAMING::REMOVE_IPL("RC12B_Destroyed");
				STREAMING::REMOVE_IPL("RC12B_HospitalInterior");		
				GameFunctions::MinimapNotification("Destroyed Hospital IPL unloaded");
			}
			if (GUI::Option("Load Jewelry Store", ""))
			{
				STREAMING::REQUEST_IPL("post_hiest_unload");
				STREAMING::REMOVE_IPL("jewel2fake");
				STREAMING::REMOVE_IPL("bh1_16_refurb");			
				GameFunctions::MinimapNotification("Jewelry Store IPL loaded");
			}
			if (GUI::Option("Unload Jewelry Store", ""))
			{
				STREAMING::REMOVE_IPL("post_hiest_unload");		
				GameFunctions::MinimapNotification("Jewelry Store IPL unloaded");
			}
			if (GUI::Option("Load Morgue", ""))
			{
				STREAMING::REQUEST_IPL("Coroner_Int_on");			
				GameFunctions::MinimapNotification("Morgue IPL loaded");
			}
			if (GUI::Option("Unload Morgue", ""))
			{
				STREAMING::REMOVE_IPL("Coroner_Int_on");		
				GameFunctions::MinimapNotification("Morgue IPL unloaded");
			}
			if (GUI::Option("Load Cargoship", ""))
			{			
				STREAMING::REQUEST_IPL("cargoship");
				GameFunctions::MinimapNotification("Cargoship IPL loaded");
			}
			if (GUI::Option("Unload Cargoship", ""))
			{		
				STREAMING::REMOVE_IPL("cargoship");
				GameFunctions::MinimapNotification("Cargoship IPL unloaded");
			}
		}
		break; 
		case WeaponsMenu:
		{
			GUI::Title("Weapons");
			if (GUI::Option("Get All Weapons", ""))
			{
				GameFunctions::GiveAllWeaponsToPlayer(GameFunctions::PlayerPedID);
			}
			if (GUI::Option("Clear All Weapons", "Weapons are not permanently removed"))
			{
				if (CheatFeatures::AutoGiveAllWeaponsBool) { GameFunctions::MinimapNotification("Disable 'Auto Give All Weapons' to use this"); }
				else { WEAPON::REMOVE_ALL_PED_WEAPONS(GameFunctions::PlayerPedID, true); }
			}
			GUI::Break("Upgrades", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Max Upgrade All Weapons", "Max Upgrade All Weapons"))
			{
				GameFunctions::MaxUpgradeAllWeapons();
			}
			if (GUI::Option("Max Upgrade Current Weapon", ""))
			{
				Hash CurrentWeapon;
				WEAPON::GET_CURRENT_PED_WEAPON(GameFunctions::PlayerPedID, &CurrentWeapon, true);
				for (auto const& i : GameArrays::MaxUpgradeWeaponComponents)
				{
					if (i.WeaponHash == CurrentWeapon)
					{
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(GameFunctions::PlayerPedID, i.WeaponHash, GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i.UpgradeHash)));
					}
				}
			}
			GUI::Break("Auto", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Auto Get All Weapons", CheatFeatures::AutoGiveAllWeaponsBool, "");
			GUI::Toggle("Auto Get All Weapon Upgrades", CheatFeatures::AutoGiveAllWeaponUpgradesBool, "");
			GUI::Break("Color", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Rainbow Gun", CheatFeatures::RainbowGunBool, "");
		}
		break;
		case WeaponVisualsMenu:
		{
			GUI::Title("Visuals");
			GUI::Toggle("Weapon Invisibility", CheatFeatures::WeaponInvisibilityBool, "");
			GUI::Toggle("Crosshair", CheatFeatures::CrossHairBool, "");
			GUI::Toggle("Crosshair -> ADS only", CheatFeatures::CrossHairADSOnlyBool, "");
			GUI::Toggle("Cartoon Gun", CheatFeatures::CartoonGunBool, "Shows cartoon effects while shooting");
			GUI::Toggle("Entity Information Gun", CheatFeatures::EntityInformationGunBool, "Shows info about aimed entity");
		}
		break;
		case WeaponAmmoMenu:
		{
			GUI::Title("Ammo Modification");
			GUI::StringVector("Impact Ammo", { "Disabled", "Fire", "Airstrike", "Teleport To", "Explosion", "Show Bullet Coord" }, CheatFeatures::ImpactAmmoVectorPosition, "");
			GUI::StringVector("Custom Ammo", { "Disabled", "Valkyrie", "Rhino Tank", "RPG", "Firework" }, CheatFeatures::CustomAmmoVectorPosition, "");
		}
		break;
		case weaponmenu:
		{
			GUI::Title("Weapon");
			GUI::MenuOption("Weapons", WeaponsMenu);
			GUI::MenuOption("Visuals", WeaponVisualsMenu);
			GUI::MenuOption("Ammo Modification", WeaponAmmoMenu);
			GUI::MenuOption("Shoot Entities", ShootEntitiesMenu);
			GUI::MenuOption("Aimbot", aimbotsettingsmenu);		
			GUI::Break("General", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("No Reload", CheatFeatures::NoWeaponReloadBool, "Disables the reload animation of all weapons");
			GUI::Toggle("Infinite Ammo", CheatFeatures::InfiniteAmmoBool, "Never run out of ammo again");
			GUI::Toggle("Delete Gun", CheatFeatures::DeleteGunBool, "Use SNS Pistol with this option");
			GUI::Toggle("Rapid Fire", CheatFeatures::WeaponRapidFireBool, "Shoot very fast");
			GUI::Toggle("One Shot One Kill", CheatFeatures::OneHitKillBool, "");
			GUI::Break("Entity Control", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Gravity Gun", CheatFeatures::GravityGunBool, "");
			GUI::Float("Entity Distance", CheatFeatures::GravityGunEntityDistance, 5.f, 25.f, 1.f, "Changing distance is also possible with the scroll wheel", 0);
		}
		break; 
		case ShootEntitiesMenu:
		{
			GUI::Title("Shoot Entities");
			GUI::Toggle("Toggle", CheatFeatures::ShootEntitiesBool, "", SELECTABLE_DISABLE_SAVE);
			GUI::Break("Current: ~t~" + CheatFeatures::ShootEntitiesCurrent, false);
			GUI::Break("Vehicles", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Rhino Tank", "")) { CheatFeatures::ShootEntitiesCurrent = "RHINO"; }
			if (GUI::Option("Hydra", "")) { CheatFeatures::ShootEntitiesCurrent = "HYDRA"; }
			if (GUI::Option("Airport Bus", "")) { CheatFeatures::ShootEntitiesCurrent = "AIRBUS"; }
			if (GUI::Option("Brickade", "")) { CheatFeatures::ShootEntitiesCurrent = "BRICKADE"; }
			if (GUI::Option("Cargo Plane", "")) { CheatFeatures::ShootEntitiesCurrent = "CARGOPLANE"; }
			if (GUI::Option("Dump", "")) { CheatFeatures::ShootEntitiesCurrent = "DUMP"; }
		}
		break;
		case aimbotsettingsmenu:
		{
			GUI::Title("Aimbot");
			GUI::Toggle("Triggerbot", CheatFeatures::TriggerBotBool, "");
			GUI::StringVector("Bone", { "Head", "Neck", "Right Hand", "Left Hand" }, CheatFeatures::AimbotBoneVectorPosition, "");
			GUI::Break("Target", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Shoot NPC's", CheatFeatures::TriggerBot_ShootNPCBool, "Triggerbot shoots at NPC's");
			GUI::Toggle("Shoot Players", CheatFeatures::TriggerBot_ShootPlayersBool, "Triggerbot shoots at players");
		}
		break;
		case teleportmenu:
		{
			GUI::Title("Teleport");
			if (GUI::Option("Teleport To Waypoint", "")) { GameFunctions::TeleportToBlipCoord(SpriteWaypoint); }
			GUI::Toggle("Auto Teleport To Waypoint", CheatFeatures::AutoTeleportToWaypointBool, "");
			if (GUI::Option("Teleport To Personal Vehicle", "")) { GameFunctions::TeleportToBlipCoord(SpritePersonalVehicleCar);  }
			if (GUI::Option("Teleport To Objective", "")) { GameFunctions::TeleportToObjective(); }
			if (GUI::Option("Teleport to Custom Coordinate", ""))
			{
				Vector3 TargetCoordinates;
				try
				{
					TargetCoordinates.x = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter X-axis coordinate"));
					if (TargetCoordinates.x == 0) { goto CanceledCustomTeleport; }				
					TargetCoordinates.y = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter Y-axis coordinate"));
					if (TargetCoordinates.y == 0) { goto CanceledCustomTeleport; }
					TargetCoordinates.z = std::stof(GameFunctions::DisplayKeyboardAndReturnInput(25, "Enter Z-axis coordinate"));		
					if (TargetCoordinates.z == 0) { goto CanceledCustomTeleport; }
					GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, TargetCoordinates, false,false);
					break;
				}
				catch (...)
				{
					GameFunctions::MinimapNotification("~r~Invalid float coordinate format inputted");
					break;
				}

			CanceledCustomTeleport:
				break;
			} 
			if (GUI::Option("Teleport Into Last Used Vehicle", ""))
			{
				PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, VEHICLE::GET_LAST_DRIVEN_VEHICLE(), -1);
			}
			if (GUI::Int("Teleport Forward", TeleportFoward, 1, 10, 1))
			{
				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0f, static_cast<float>(TeleportFoward), 0.0f);
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, false)) { GameFunctions::PlayerPedID = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, false); }
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(GameFunctions::PlayerPedID, Coords.x, Coords.y, Coords.z, false, false, true);
			}
			GUI::Break("Custom Locations", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Save current location", ""))
			{
				char* NewThemeFileName = GameFunctions::DisplayKeyboardAndReturnInput(20, "Enter Custom Teleport Location Name");
				if (NewThemeFileName != "0")
				{
					CheatFunctions::AddCustomTeleportLocation(NewThemeFileName);
					GameFunctions::MinimapNotification("Custom Location Saved");
				}
			}
			GUI::MenuOption("View locations", CustomTeleportLocations);
			GUI::Break("Presets", SELECTABLE_CENTER_TEXT);
			GUI::MenuOption("Landmarks", LandmarkTeleportLocations);
			GUI::MenuOption("IPL's", iplteleports);
			GUI::MenuOption("Safehouses", SafehousesTeleportLocations);
			GUI::MenuOption("Underwater", UnderwaterTeleportLocations);
			GUI::MenuOption("High Altitude", HighAltitudeTeleportLocations);
		}
		break;
		case CustomTeleportLocations:
		{
			GUI::Title("Custom Locations");
			if (CheatFunctions::FileOrDirectoryExists(CheatFunctions::ReturnCustomTeleportLocationsFilePath()))
			{
				Json::Value JsonHandle = CheatFunctions::ReadJsonFileAndReturnDataObject(CheatFunctions::ReturnCustomTeleportLocationsFilePath());
				for (auto it = JsonHandle.begin(); it != JsonHandle.end(); ++it)
				{
					CustomLocationsAmount++;
					GUI::Break(it.key().asString(), SELECTABLE_CENTER_TEXT);
					if (GUI::Option("Teleport To", ""))
					{
						Vector3 Target;
						Target.x = JsonHandle[it.key().asString()]["X"].asFloat();
						Target.y = JsonHandle[it.key().asString()]["Y"].asFloat();
						Target.z = JsonHandle[it.key().asString()]["Z"].asFloat();
						GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Target, false, false);
					}
					if (GUI::Option("Delete", ""))
					{
						CheatFunctions::DeleteCustomTeleportLocation(it.key().asString());
					}
				}
			}
			if (CustomLocationsAmount == 0)
			{
				GUI::Break("No custom locations have been saved");
			}
			CustomLocationsAmount = 0;
		}
		break;
		case UnderwaterTeleportLocations:
		{
			GUI::Title("Underwater");
			GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsUnderwater);
		}
		break;
		case HighAltitudeTeleportLocations:
		{
			GUI::Title("High Altitude");
			GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsHighAltitude);
		}
		break;
		case SafehousesTeleportLocations:
		{
			GUI::Title("Safehouses");
			GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsSafehouses);
		}
		break;
		case LandmarkTeleportLocations:
		{
			GUI::Title("Landmarks");
			GameFunctions::ShowTeleportLocationsMenu(GameArrays::TeleportLocationsLandmarks);
		}
		break;
		case iplteleports:
		{
			GUI::Title("IPL Teleports");
			if (GUI::Option("North Yankton", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 5309.519f, -5212.37f, 83.522f, true, false, false, true);
			}
			if (GUI::Option("Yacht", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -2045.8f, -1031.2f, 11.9f, true, false, false, true);
			}
			if (GUI::Option("Destroyed Hospital", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 356.8f, -590.1f, 43.3f, true, false, false, true);
			}
			if (GUI::Option("Jewelry Store", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -630.4f, -236.7f, 40.0f, true, false, false, true);
			}
			if (GUI::Option("Morgue", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, 244.9f, -1374.7f, 39.5f, true, false, false, true);
			}
			if (GUI::Option("Cargo Ship", ""))
			{
				ENTITY::SET_ENTITY_COORDS(GameFunctions::PlayerPedID, -90.0f, -2365.8f, 14.3f, true, false, false, true);
			}
		}
		break; 
		case SelectedPlayerTrollMenu:
		{
			GUI::Title("Griefing");
			GUI::MenuOption("Remote Events", SelectedPlayerRemoteOptions);
			GUI::MenuOption("Attachments", SelectedPlayerAttachmentOptions);
			GUI::Toggle("Explode", CheatFeatures::ExplodeLoopSelectedPlayerBool, "", SELECTABLE_DISABLE_SAVE);
			GUI::Toggle("Freeze", CheatFeatures::FreezeSelectedPlayerBool, "", SELECTABLE_DISABLE_SAVE);
			GUI::Toggle("Shake Camera", CheatFeatures::ShakeCamSelectedPlayerBool, "", SELECTABLE_DISABLE_SAVE);
			if (GUI::Option("Set Off Vehicle Alarm", ""))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, false))
				{
					GameFunctions::SetOffAlarmPlayerVehicle(Handle);
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (GUI::Option("Burst Vehicle Tires", ""))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					GameFunctions::BurstSelectedPlayerTires(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}			
			}
			if (GUI::Option("Airstrike", ""))
			{
				Vector3 Coords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35.f, Coords.x, Coords.y, Coords.z, 250, true, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer), true, false, 500.f);
			}
			if (GUI::Option("Attach To", ""))
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer) != GameFunctions::PlayerPedID)
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(GameFunctions::PlayerPedID, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
				}
			}
			if (GUI::Option("Detach From", ""))
			{
				ENTITY::DETACH_ENTITY(GameFunctions::PlayerPedID, true, true);
			}
			if (GUI::Option("Slingshot Vehicle", ""))
			{
				Ped Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, false)) 
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(Handle, true));
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(Handle, true)))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(Handle, true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					}
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle"); 
				}
			}
			if (GUI::Option("Ram With Vehicle", ""))
			{
				Hash model = GAMEPLAY::GET_HASH_KEY("trophytruck2");
				if (STREAMING::IS_MODEL_VALID(model))
				{
					for (int i = 0; i < 3; i++)
					{
						STREAMING::REQUEST_MODEL(model);
						while (!STREAMING::HAS_MODEL_LOADED(model)) { GameHooking::PauseMainFiber(0, false); }
						Vector3 ourCoords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
						float forward = 10.f;
						float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
						float xVector = forward * sin(GameFunctions::DegreesToRadians(heading)) * -1.f;
						float yVector = forward * cos(GameFunctions::DegreesToRadians(heading));
						Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x - xVector, ourCoords.y - yVector, ourCoords.z, heading, true, true);
						GameFunctions::RequestNetworkControlOfEntity(veh);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 250);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					}
				}
			}
			if (GUI::Option("Cage Trap", ""))
			{
				Vector3 remotePos = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
				Object obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
			}
			if (GUI::Option("Clone Ped", ""))
			{
				GameFunctions::ClonePed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
			}
			if (GUI::Option("Kick out of vehicle", ""))
			{
				Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				GameFunctions::RequestNetworkControlOfEntity(playerPed);
				GameFunctions::StopAllPedAnimations(playerPed);
			}
			if (GUI::Option("Spawn Enemy", ""))
			{
				int eclone[1000];
				int egcount = 1;
				Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = GameFunctions::GetEntityCoords(SelectedPlayer);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], SelectedPlayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Bodyguard", "")) 
			{
				int clone[1000];
				int gcount = 1;
				Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(SelectedPlayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = GameFunctions::GetEntityCoords(SelectedPlayer);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				int my_group = PLAYER::GET_PLAYER_GROUP(SelectedPlayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(SelectedPlayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}		
		}
		break;
		case PlayerListMenu:
		{
			GUI::Title("Players");
			GUI::StringVector("Show Selected Player", { "Player List & Menu", "Player List", "Disabled" }, CheatFeatures::PlayerListMarkerPosition, "");
			GUI::Break("List", SELECTABLE_CENTER_TEXT);
			for (int i = 0; i < 32; ++i)
			{
				std::string PlayernameString = PLAYER::GET_PLAYER_NAME(i);
				if (GameFunctions::IsPlayerIDValid(i))
				{		
					if (GameFunctions::PlayerIsFreemodeScriptHost(i)) { PlayernameString.append(" ~o~[HOST]"); }
					if (GameFunctions::IsPlayerFriend(i)) { PlayernameString.append("~b~[FRIEND]"); }
					if (GameFunctions::IsEntityInInterior(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) { PlayernameString.append(" ~p~[INTERIOR]"); }
					if (GameFunctions::PlayerID == i) { PlayernameString.append(" ~g~[SELF]"); }
					GUI::MenuOptionPlayerList(PlayernameString, SELECTABLE_HIDE_INFO_BOX) ? CheatFeatures::SelectedPlayer = i : NULL;
					if (GUI::currentOption == GUI::optionCount) { GameFunctions::ShowPlayerInformationBox(i); }
				}
			}
		}
		break;
		case SelectedPlayerMenu:
		{
			GUI::Title(PLAYER::GET_PLAYER_NAME(CheatFeatures::SelectedPlayer));
			GUI::Toggle("Spectate", CheatFeatures::SpectatePlayerBool, "", SELECTABLE_DISABLE_SAVE);
			if (GUI::Option("Host Kick", "Kick Selected Player - Host only")) { NETWORK::NETWORK_SESSION_KICK_PLAYER(CheatFeatures::SelectedPlayer); }
			GUI::MenuOption("Teleport", SelectedPlayerTeleportMenu);
			GUI::MenuOption("Friendly", SelectedPlayerFriendlyMenu);
			GUI::MenuOption("Griefing", SelectedPlayerTrollMenu);
			if (GUI::Option("View Profile", "View Selected Player Social Club Profile")) { int playerHandle; NETWORK::NETWORK_HANDLE_FROM_PLAYER(CheatFeatures::SelectedPlayer, &playerHandle, 13); NETWORK::NETWORK_SHOW_PROFILE_UI(&playerHandle); }
		}
		break;
		case SelectedPlayerFriendlyMenu:
		{
			GUI::Title("Friendly");
			if (GUI::Option("Give All Weapons", "")) { GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer)); }
			if (GUI::Option("Copy Outfit", "")) { GameFunctions::CopySelectedPlayerOutfit(CheatFeatures::SelectedPlayer); }
			if (GUI::Option("Set Waypoint", "Sets waypoint to Selected player location"))
			{
				Vector3 TargetCoords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
				UI::SET_NEW_WAYPOINT(TargetCoords.x, TargetCoords.y);
			}
		}
		break;
		case SelectedPlayerRemoteOptions:
		{
			GUI::Title("Remote Events");
			if (GUI::Option("Kick To Single Player", "")) 
			{
				uint64_t arguments_aray[4] = { TSE_KICK_TO_SP, CheatFeatures::SelectedPlayer, 0, 0 };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
			}
			GUI::Break("CEO", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Kick", ""))
			{
				uint64_t arguments_aray[4] = { TSE_CEO_KICK, CheatFeatures::SelectedPlayer, 1, 5 };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
			}
			if (GUI::Option("Ban", ""))
			{
				uint64_t arguments_aray[4] = { TSE_CEO_BAN, CheatFeatures::SelectedPlayer, 1, 5 };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, sizeof(arguments_aray) / sizeof(arguments_aray[0]), 1 << CheatFeatures::SelectedPlayer);
			}
			GUI::Break("Teleport", SELECTABLE_CENTER_TEXT);
			GUI::MenuOption("Apartment", SelectedPlayerApartmentTeleport);
			if (GUI::Option("Cayo Perico", ""))
			{
				DWORD64 arguments_aray[2] = { TSE_CAYO_PERICO_TELEPORT, CheatFeatures::SelectedPlayer };
				SCRIPT::TRIGGER_SCRIPT_EVENT(1, arguments_aray, 2, 1 << CheatFeatures::SelectedPlayer);
			}
		}
		break; 
		case SelectedPlayerApartmentTeleport:
		{
			GUI::Title("Teleport to Apartment");
			for (const auto& i : GameArrays::TSEPropertyList)
			{
				if (GUI::Option(i.PropertyName, ""))
				{
					uint64_t teleport[9] = { TSE_PROPERTY_TELEPORT, CheatFeatures::SelectedPlayer, 0, -1, 1, i.Index, 0, 0, 0 };
					SCRIPT::TRIGGER_SCRIPT_EVENT(1, teleport, 9, (1 << CheatFeatures::SelectedPlayer));
				}
			}
		}
		break;
		case SelectedPlayerTeleportMenu:
		{
			GUI::Title("Teleport"); 
			if (GUI::Option("Parachute To", ""))
			{
				int TimeoutTick;
				WEAPON::GIVE_WEAPON_TO_PED(GameFunctions::PlayerPedID, 0xFBAB5776, 0, false, true);
				Vector3 TargetCoords = GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer));
				TargetCoords.z += 50.f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, TargetCoords, false, true);
				while (PED::GET_PED_PARACHUTE_STATE(GameFunctions::PlayerPedID) != 0) 
				{ 
					TimeoutTick++;
					GameHooking::PauseMainFiber(0, false);
					if (TimeoutTick >= 500)
					{
						break;
					}
				}
				PED::FORCE_PED_TO_OPEN_PARACHUTE(GameFunctions::PlayerPedID);
			}
			if (GUI::Option("Teleport To", ""))
			{
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, GameFunctions::GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer)),
					false, false);
			}
			if (GUI::Option("Teleport Into Vehicle", "Teleport into Selected Player vehicle"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer), false);
				for (int i = -1; i < 16; i++) { if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i)) { PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, veh, i); } }
			}
		}
		break; 
		case GlobalsMenu:
		{
			GUI::Title("Globals");
			GUI::Toggle("Off Radar", CheatFeatures::OffRadarBool, "Enables Lester Off Radar Feature");
			GUI::Toggle("No Idle Kick", CheatFeatures::NoIdleKickBool, "Does not work when out of game focus");
			GUI::Toggle("Cops Turn Blind Eye", CheatFeatures::CopsTurnBlindEyeBool, "Enables Bribe Authorities");
			GUI::Toggle("No Orbital Cannon Cooldown", CheatFeatures::OrbitalCannonCooldownBypassBool, "");
		}
		break;
		case VisionMenu:
		{
			GUI::Title("Vision");
			if (GUI::Option("Reset", "")) 
			{
				GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
			}
			GUI::Break("Visions", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Timecycle", ""))
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("CAMERA_secuirity_FUZZ");
			}
			if (GUI::Option("Stoned", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("stoned");
			}
			if (GUI::Option("Orange", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("REDMIST");
			}
			if (GUI::Option("Cocaine", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("drug_flying_base");
			}
			if (GUI::Option("Huffin Gas", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("DRUG_gas_huffin");
			}
			if (GUI::Option("Wobbly", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("drug_wobbly");
			}
			if (GUI::Option("Drunk", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("Drunk");
			}
			if (GUI::Option("Heaven", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("Bloom");
			}
			if (GUI::Option("3D", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("PlayerSwitchPulse");
			}
			if (GUI::Option("Killstreak", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("MP_Killstreak");
			}
			if (GUI::Option("Hallucinations", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("player_transition");
			}
			if (GUI::Option("Low Quality", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("cinema_001");
			}
			if (GUI::Option("Blurry", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("CHOP");
			}
			if (GUI::Option("\"Fucked Up\" Screen", "")) 
			{
				GRAPHICS::SET_TIMECYCLE_MODIFIER("BarryFadeOut");
			}
		}
		break;
		case SelfOptionsMenu:
		{
			GUI::Title("Self");
			GUI::MenuOption("Model", SelfModelMenu);
			GUI::MenuOption("Globals", GlobalsMenu);
			GUI::MenuOption("Animations", AnimationsMenu);
			GUI::MenuOption("Wardrobe", WardrobeMenu);
			GUI::MenuOption("Vision", VisionMenu);
			GUI::Toggle("Invincible", CheatFeatures::GodmodeBool, "Gives your character God Mode");
			if (GUI::Float("Health", SelfHealth, 1.f, ENTITY::GET_ENTITY_MAX_HEALTH(GameFunctions::PlayerPedID), 1.f, "", 2, SELECTABLE_RETURN_VALUE_CHANGE))
			{
				ENTITY::SET_ENTITY_HEALTH(GameFunctions::PlayerPedID, SelfHealth);
			}
			GUI::Toggle("No Ragdoll", CheatFeatures::NoRagdollAndSeatbeltBool, "Disables ragdoll on your character");
			GUI::Toggle("Invisibility", CheatFeatures::PlayerInvisibleBool, "Makes your character invisible");
			if (GUI::Int("Opacity", CheatFeatures::PlayerOpacityInt, 50, 250, 50, "Changes local player opacity", SELECTABLE_RETURN_VALUE_CHANGE)) { ENTITY::SET_ENTITY_ALPHA(GameFunctions::PlayerPedID, (CheatFeatures::PlayerOpacityInt), false); }
			GUI::Toggle("Super Jump", CheatFeatures::SuperJumpBool, "Makes your character jump higher");
			if (GUI::StringVector("Sprint Speed", { "Disabled", "Fast", "Super" }, CheatFeatures::FastSuperRunPosition, "", SELECTABLE_RETURN_VALUE_CHANGE))
			{
				if (CheatFeatures::FastSuperRunPosition == 0)
				{
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(GameFunctions::PlayerID, 1.f);
				}
			}
			GUI::Toggle("Ignored By Everyone", CheatFeatures::PlayerIgnoredBool, "NPC's will (mostly) ignore you");
			GUI::Toggle("Never Wanted", CheatFeatures::NeverWantedBool, "Never get a wanted level");
			if (GUI::Int("Wanted Level", PlayerWantedLevelInteger, 0, 5, 1, "Set Wanted Level", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { CheatFeatures::NeverWantedBool = false; PLAYER::SET_PLAYER_WANTED_LEVEL(GameFunctions::PlayerID, PlayerWantedLevelInteger, false); PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(GameFunctions::PlayerID, false); }
			GUI::Toggle("Explosive Melee", CheatFeatures::ExplosiveMeleeBool, "Objects you hit with melee explode");
			GUI::Toggle("Tiny Player", CheatFeatures::TinyPlayerBool, "Lowers your character's scaling");
			GUI::Toggle("Super Man", CheatFeatures::SuperManBool, "Fly around like a superman!");
			if (GUI::Option("Suicide", "Kill your character")) { PED::APPLY_DAMAGE_TO_PED(GameFunctions::PlayerPedID, 300, true); }
			if (GUI::Option("Give BST", "Get Bull Shark Testosterone - GTAO Only")) { globalHandle(GLOBAL_BULLSHARKTESTOSTERONE[0]).At(GLOBAL_BULLSHARKTESTOSTERONE[1]).As<bool>() = true; }
			if (GUI::Option("Clean", "Remove any damage from player character")) { PED::CLEAR_PED_BLOOD_DAMAGE(GameFunctions::PlayerPedID); PED::RESET_PED_VISIBLE_DAMAGE(GameFunctions::PlayerPedID); GameFunctions::MinimapNotification("Player Cleaned"); }	
		}
		break;
		case WardrobeMenu:
		{
			GUI::Title("Wardrobe"); 
			if (GUI::Option("Police Uniform", ""))
			{
				if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("mp_m_freemode_01")))
				{
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 0, 45, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 55, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 35, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 10, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 122, 0, 0);
				}
				else if (PED::IS_PED_MODEL(GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("mp_f_freemode_01")))
				{
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 0, 45, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 48, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 34, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 29, 0, 0);
					PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 152, 0, 0);
				}
			}
			if (GUI::Option("Default Variation", ""))
			{
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(GameFunctions::PlayerPedID);
			}
			if (GUI::Option("Random Variation", ""))
			{
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(GameFunctions::PlayerPedID, false);
			}
			if (GUI::Option("Random Accessories", ""))
			{
				PED::SET_PED_RANDOM_PROPS(GameFunctions::PlayerPedID);
			}
			if (GUI::Option("Reset Appearance", ""))
			{
				PED::CLEAR_ALL_PED_PROPS(GameFunctions::PlayerPedID);
				PED::CLEAR_PED_DECORATIONS(GameFunctions::PlayerPedID);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 1, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 5, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 9, 0, 0, 0);
			}
			GUI::Break("Components", SELECTABLE_CENTER_TEXT);
			//int ComponentInt;
			//int TextureInt;
			//GUI::StringVector("Component", { "Face", "Mask", "Hair", "Torso", "Leg", "Parachute", "Shoes", "Accessory", "Undershirt", "Kevlar", "Badge", "Torso 2" }, ComponentInt, "", SELECTABLE_RETURN_VALUE_CHANGE);
			//GUI::Int("Texture", TextureInt, 0, PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(GameFunctions::PlayerPedID, ComponentInt, 0), 1);
			if (GUI::Int("Hair Color", HairColor, 0, PED::_GET_NUM_HAIR_COLORS(), 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE))
			{
				PED::_SET_PED_HAIR_COLOR(GameFunctions::PlayerPedID, HairColor, 0);
			}
			if (GUI::Int("Face", SetPedTexture_Face, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, 0); }
			if (GUI::Int("Face Texture", SetPedTexture_FaceTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, SetPedTexture_Face); }
			if (GUI::Int("Head", SetPedTexture_Head, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Head, 0); }
			if (GUI::Int("Head Texture", SetPedTexture_HeadTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 1, SetPedTexture_Head, SetPedTexture_HeadTexture); }
			if (GUI::Int("Hair", SetPedTexture_Hair, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, 0); }
			if (GUI::Int("Hair Texture", SetPedTexture_HairTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, SetPedTexture_HairTexture); }
			if (GUI::Int("Torso", SetPedTexture_Torso, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, 0); }
			if (GUI::Int("Torso Texture", SetPedTexture_TorsoTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, SetPedTexture_TorsoTexture); }
			if (GUI::Int("Legs", SetPedTexture_Legs, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, 0); }
			if (GUI::Int("Legs Texture", SetPedTexture_LegsTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, SetPedTexture_LegsTexture); }
			if (GUI::Int("Hands", SetPedTexture_Hands, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, 0); }
			if (GUI::Int("Hands Texture", SetPedTexture_HandsTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, SetPedTexture_HandsTexture); }
			if (GUI::Int("Feet", SetPedTexture_Feet, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, 0); }
			if (GUI::Int("Feet Texture", SetPedTexture_FeetTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, SetPedTexture_FeetTexture); }
			if (GUI::Int("Eyes", SetPedTexture_Eyes, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, 0); }
			if (GUI::Int("Eyes Texture", SetPedTexture_EyesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, SetPedTexture_EyesTexture); }
			if (GUI::Int("Accesories", SetPedTexture_Accesories, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, 0); }
			if (GUI::Int("Accesories Texture", SetPedTexture_AccesoriesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, SetPedTexture_AccesoriesTexture); }
			if (GUI::Int("Accesories2", SetPedTexture_AccesoriesSec, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, 0); }
			if (GUI::Int("Accesories2 Texture", SetPedTexture_AccesoriesSecTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, SetPedTexture_AccesoriesSecTexture); }
			if (GUI::Int("Torso 2", SetPedTexture_TorsoSec, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, 0); }
			if (GUI::Int("Torso 2 Texture", SetPedTexture_TorsoSecTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, SetPedTexture_TorsoSecTexture); }
			if (GUI::Int("Textures", SetPedTexture_Textures, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 10, SetPedTexture_Textures, 0); }
			if (GUI::Int("Textures Texture", SetPedTexture_TexturesTexture, 0, 255, 1, "", SELECTABLE_DISABLE_SAVE | SELECTABLE_RETURN_VALUE_CHANGE)) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_Textures, SetPedTexture_TexturesTexture); }
		}
		break; 
		case SelectedPlayerAttachmentOptions:
		{
			GUI::Title("Attachments");
			if (GUI::Option("Plate", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "p_oil_slick_01"); }
			if (GUI::Option("EMP", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "hei_prop_heist_emp"); }
			if (GUI::Option("Beach Fire", ""))		{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_beach_fire"); }
			if (GUI::Option("Orange Ball", ""))		{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_juicestand"); }
			if (GUI::Option("Weed", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_weed_01"); }
			if (GUI::Option("Safe", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "p_v_43_safe_s"); }
			if (GUI::Option("UFO", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "p_spinning_anus_s"); }
			if (GUI::Option("Toilet", ""))			{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_ld_toilet_01"); }
			if (GUI::Option("Christmas Tree", ""))	{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_xmas_tree_int"); }
			if (GUI::Option("Windmill", ""))			{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_windmill_01"); }
			if (GUI::Option("Radar", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::SelectedPlayer, "prop_air_bigradar"); }
			if (GUI::Option("Remove All Objects", "Only removes above attached objects")) 
			{
				const std::vector<std::string> ObjectsToRemoveArray = { 
					"p_oil_slick_01",  "hei_prop_heist_emp", "prop_beach_fire",  "prop_juicestand",
					"prop_weed_01",  "p_v_43_safe_s",  "p_spinning_anus_s",  "prop_ld_toilet_01",
					"prop_xmas_tree_int",  "prop_windmill_01",  "prop_air_bigradar"
				};
				for (auto const& i : ObjectsToRemoveArray)
				{ 
					GameFunctions::RemoveObjectFromPed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::SelectedPlayer), CheatFunctions::StringToChar(i));
				}			
				GameFunctions::MinimapNotification("Object(s) Removed");
			}
		}
		break;
		case protections:
		{
			GUI::Title("Protections");	
			if (GUI::Option("Enable/Disable Anti-Crash Camera", "Changes camera position to prevent entity crash")) { GameFunctions::EnableDisableAntiCrashCamera(); }
			GUI::Break("Protection", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Enable All", "Enable all protection options")) {
				CheatFeatures::ProtectionVoteKickBool = true;
				CheatFeatures::ProtectionFreezeBool = true;
				CheatFeatures::ProtectionGiveRemoveWeaponsBool = true;
				CheatFeatures::ProtectionWorldEventsBool = true;
				CheatFeatures::ProtectionAlterWantedLevelBool = true;
				CheatFeatures::ProtectionVehicleBool = true;
				CheatFeatures::BlockMaliciousScriptEvents = true;
			}
			if (GUI::Option("Disable All", "Disable all protection options")) {
				CheatFeatures::ProtectionVoteKickBool = false;
				CheatFeatures::ProtectionFreezeBool = false;
				CheatFeatures::ProtectionGiveRemoveWeaponsBool = false;
				CheatFeatures::ProtectionWorldEventsBool = false;
				CheatFeatures::ProtectionAlterWantedLevelBool = false;
				CheatFeatures::ProtectionVehicleBool = false;
				CheatFeatures::BlockMaliciousScriptEvents = false;
			}
			GUI::Toggle("Remote Events", CheatFeatures::BlockMaliciousScriptEvents, "Some GTAO missions might not work");
			GUI::Toggle("Remote Events -> Block All", CheatFeatures::BlockAllScriptEvents, "Join GTAO before enabling", SELECTABLE_DISABLE_SAVE);
			GUI::Toggle("Vote Kick", CheatFeatures::ProtectionVoteKickBool, "");
			GUI::Toggle("Freeze", CheatFeatures::ProtectionFreezeBool, "");
			GUI::Toggle("Give/Remove Weapons", CheatFeatures::ProtectionGiveRemoveWeaponsBool, "");
			GUI::Toggle("Alter Wanted Level", CheatFeatures::ProtectionAlterWantedLevelBool, "");
			GUI::Toggle("World Events", CheatFeatures::ProtectionWorldEventsBool, "Fire, explosions and more");
			GUI::Toggle("Vehicle", CheatFeatures::ProtectionVehicleBool, "Control & Explosions");
		}
		break; 
		case AnimationsMenu:
		{
			GUI::Title("Animations");
			GUI::Toggle("Controllable", CheatFeatures::ControllableAnimations, "You can move and shoot while an animation is playing");
			if (GUI::Option("Stop Animation", "")) { GameFunctions::StopAllPedAnimations(GameFunctions::PlayerPedID); }
			if (GUI::StringVector("Animations", GameArrays::AnimationsDisplayNames, CheatFeatures::AnimationsVectorPosition, "Select to play animation", SELECTABLE_DISABLE_SAVE))
			{
				int IndexCount = 0;
				for (auto const& i : GameArrays::Animations)
				{ 
					if (IndexCount == CheatFeatures::AnimationsVectorPosition)
					{
						GameFunctions::PlayPedAnimation(GameFunctions::PlayerPedID, CheatFunctions::StringToChar(i.AnimationDictionary), CheatFunctions::StringToChar(i.AnimationName), CheatFeatures::ControllableAnimations);
					}
					IndexCount++;
				}
			}
			if (GUI::StringVector("Scenarios", GameArrays::Scenarios, CheatFeatures::ScenariosVectorPosition, "Select to play scenario. 'Controllable' toggle not applicable.", SELECTABLE_DISABLE_SAVE))
			{
				int IndexCount = 0;
				for (auto const& i : GameArrays::Scenarios)
				{
					if (IndexCount == CheatFeatures::ScenariosVectorPosition)
					{
						AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, CheatFunctions::StringToChar(i), 0, true);
					}
					IndexCount++;
				}
			}
		}
		break; 
		case SettingsMenu:
		{
			GUI::Title("Settings");
			GUI::MenuOption("Theme", ThemeMenu);
			GUI::MenuOption("Hide Elements", HideElementsMenu);
			GUI::Int("Max Visible Menu Options", GUI::maxVisOptions, 5, 16, 1, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Toggle("Restore To Previous Submenu", GUI::RestorePreviousSubmenu, "When opening restores previous submenu");
			GUI::StringVector("Measurement System", { "Metric", "Imperial" }, CheatFeatures::MeasurementSystemVectorPosition, "Metric = KM/H, Imperial = MP/H", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Break("Keys", SELECTABLE_CENTER_TEXT);
			if (GUI::Option("Menu GUI: ~c~" + CheatFunctions::VirtualKeyCodeToString(Controls::OpenGUIKey), "Select to change"))
			{
				int PressedKey = CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0)
				{
					Controls::OpenGUIKey = PressedKey;
					CheatFunctions::IniFileWriteString(std::to_string(PressedKey), CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Menu GUI Key");
					GameFunctions::MinimapNotification("Menu GUI key has been set");
				}
			}
			if (GUI::Option("Cursor Navigation: ~c~" + CheatFunctions::VirtualKeyCodeToString(Controls::GUINavigationKey), "Select to change"))
			{
				int PressedKey = CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0)
				{ 
					Controls::GUINavigationKey = PressedKey;
					CheatFunctions::IniFileWriteString(std::to_string(PressedKey), CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Cursor Navigation Key");
					GameFunctions::MinimapNotification("Cursor Navigation key has been set");
				}
			}
			if (GUI::Option("Save Selectable: ~c~" + CheatFunctions::VirtualKeyCodeToString(Controls::SaveSelectableKey), "Select to change"))
			{
				int PressedKey = CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0)
				{
					Controls::SaveSelectableKey = PressedKey;
					CheatFunctions::IniFileWriteString(std::to_string(PressedKey), CheatFunctions::ReturnConfigFilePath(), "SETTINGS", "Save Selectable Key");
					GameFunctions::MinimapNotification("Cursor Navigation key has been set");
				}
			}
			GUI::Int("Key Press Delay", Controls::GUIKeyPressDelay, 1, 250, 5, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::Int("Menu Arrow Animation Delay", GUI::MenuArrowAnimationDelay, 250, 2500, 25, "", SELECTABLE_RETURN_VALUE_CHANGE);
			GUI::MenuOption("About", AboutMenu);
		}
		break;
		case HideElementsMenu:
		{
			GUI::Title("Hide Elements");
			GUI::Toggle("Hide Selectable Information Box", Cheat::CheatFeatures::HideSelectableInformationBox, "");
			GUI::Toggle("Hide Player Information Box", CheatFeatures::HidePlayerInformationBox, "");
			GUI::Toggle("Hide Vehicle Info & Preview", CheatFeatures::HideVehicleInfoAndPreview, "");
			GUI::Toggle("Hide Own IP Address", CheatFeatures::HideOwnIPAddress, "Hiddes Local IP Address from Player Information Box");
		}
		break;
		case AboutMenu:
		{
			GUI::Title("About");
			GUI::Break("Author: HatchesPls");
			if (GUI::Option("Support this project!", "Select to copy Bitcoin address to clipboard"))
			{
				CheatFunctions::CopyStringToClipboard("3BwCVtcJaNgUovcYQkDYFjrdy5YydTnjwc");
				GameFunctions::SubtitleNotification("~g~Bitcoin address copied to clipboard.~n~Thank you for your support!");
			}
			if (GUI::Option("Visit GitHub Repository", ""))
			{
				system("start https://github.com/HatchesPls/GrandTheftAutoV-Cheat");
			}
			if (GUI::Option("Unload", "WIP"))
			{
				if (GameFunctions::ShowFullScreenMessage("Unloading the cheat is currently ~h~experimental~h~.~n~You won't be able to reinject the cheat."))
				{
					GameHooking::Unload();
				}
			}
		}
		break;
		case ThemeMenu:
		{
			GUI::Title("Theme");
			GUI::MenuOption("Saved Themes", ThemeFilesMenu);
			if (!GUI::CurrentTheme.empty())
			{
				GUI::Break("Loaded Theme: ~c~" + GUI::CurrentTheme);
				if (GUI::Option("Save To Current Theme", ""))
				{
					GUI::SaveTheme(GUI::CurrentTheme);
				}
				if (GUI::Option("Delete Theme", "Delete loaded theme"))
				{
					GUI::DeleteLoadedTheme();
				}
			}
			else
			{
				GUI::Break("Loaded Theme: ~c~None");
			}
			if (GUI::Option("Save To New", ""))
			{
				char* NewThemeFileName = GameFunctions::DisplayKeyboardAndReturnInput(20, "Enter Theme Name");
				if (NewThemeFileName == "0") { break; }
				GUI::SaveTheme(NewThemeFileName);
			}
			GUI::Break("Header", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("Texture", GUI::ShowHeaderTexture, "", SELECTABLE_DISABLE_SAVE);
			GUI::Toggle("Background", GUI::ShowHeaderBackground, "", SELECTABLE_DISABLE_SAVE);
			GUI::Break("Color", SELECTABLE_CENTER_TEXT);
			GUI::Toggle("RGB Disco", CheatFeatures::RGBDiscoBool, "It's party time!", SELECTABLE_DISABLE_SAVE);
			if (GUI::Option("Primary", "Save is disabled while RGB Disco is enabled", CheatFeatures::RGBDiscoBool ? SELECTABLE_DISABLED : SELECTABLE_DUMMY))
			{
				GUI::PrimaryColor.r = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter R-color"));
				GUI::PrimaryColor.g = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter G-color"));
				GUI::PrimaryColor.b = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter B-color"));
				GameFunctions::MinimapNotification("Updated Primary Color");
			}
			if (GUI::Option("Text", "Save is disabled while RGB Disco is enabled", CheatFeatures::RGBDiscoBool ? SELECTABLE_DISABLED : SELECTABLE_DUMMY))
			{
				GUI::TextColorAndFont.r = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter R-color"));
				GUI::TextColorAndFont.g = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter G-color"));
				GUI::TextColorAndFont.b = CheatFunctions::StringToInt(GameFunctions::DisplayKeyboardAndReturnInput(3, "Enter B-color"));
				GameFunctions::MinimapNotification("Updated Text Color");
			}
			GUI::Break("Font", SELECTABLE_CENTER_TEXT);
			if (GUI::StringVector("Type", { "Chalet London", "House Script", "Monospace", "Wing Dings", "Chalet Comprime Cologne", "Pricedown" }, CheatFeatures::FontTypeVectorPosition, "", SELECTABLE_RETURN_VALUE_CHANGE))
			{
				if (CheatFeatures::FontTypeVectorPosition == 0)
				{
					GUI::TextColorAndFont.f = FontChaletLondon;
				}
				else if (CheatFeatures::FontTypeVectorPosition == 1)
				{
					GUI::TextColorAndFont.f = FontHouseScript;
				}
				else if (CheatFeatures::FontTypeVectorPosition == 2)
				{
					GUI::TextColorAndFont.f = FontMonospace;
				}
				else if (CheatFeatures::FontTypeVectorPosition == 3)
				{
					GUI::TextColorAndFont.f = FontWingDings;
				}
				else if (CheatFeatures::FontTypeVectorPosition == 4)
				{
					GUI::TextColorAndFont.f = FontChaletComprimeCologne;
				}
				else if (CheatFeatures::FontTypeVectorPosition == 5)
				{
					GUI::TextColorAndFont.f = FontPricedown;
				}
			}
			GUI::Break("Menu", SELECTABLE_CENTER_TEXT);
			GUI::Float("X-Axis", GUI::guiX, 0.0f, 0.0f, 0.01f, "", 3, SELECTABLE_DISABLE_SAVE);
			GUI::Float("Y-Axis", GUI::guiY, 0.0f, 0.0f, 0.01f, "", 3, SELECTABLE_DISABLE_SAVE);
			GUI::Float("Selectable Height", GUI::SelectableHeight, 0.035f, 0.045f, 0.001f, "This also slightly stretches the header element as a result of the rescale");
			if (GUI::Option("Reset Position", ""))
			{
				GUI::guiX = GUI::guiX_Default;
				GUI::guiY = GUI::guiY_Default;
			}
			GUI::Break("Selectable Information Box", SELECTABLE_CENTER_TEXT);
			GUI::Float("X-Axis", GUI::SelectableInfoBoxX, 0.0f, 0.0f, 0.01f, "", 3, SELECTABLE_DISABLE_SAVE);
			GUI::Float("Y-Axis", GUI::SelectableInfoBoxY, 0.0f, 0.0f, 0.01f, "", 3, SELECTABLE_DISABLE_SAVE);
			if (GUI::Option("Reset Position", ""))
			{
				GUI::SelectableInfoBoxX = GUI::SelectableInfoBoxX_Default;
				GUI::SelectableInfoBoxY = GUI::SelectableInfoBoxY_Default;
			}
		}
		break;
		case ThemeFilesMenu:
		{
			GUI::Title("Saved Themes");
			if (!GUI::ThemeFilesVector.empty())
			{
				for (auto const& i : GUI::ThemeFilesVector)
				{
					if (GUI::Option(i, ""))
					{
						if (CheatFunctions::FileOrDirectoryExists(CheatFunctions::ReturnThemeFilePath(i))) 
						{
							GUI::LoadTheme(CheatFunctions::StringToChar(i), false);
						}
						else
						{
							GameFunctions::MinimapNotification("~r~Unable to locate theme file");
						}
					}
				}
			}
			else
			{
				GUI::Break("No Theme Files Saved Yet");
			}
		}
		break;
		}
		GUI::End();
		GameHooking::PauseMainFiber(0, false);
	}
}