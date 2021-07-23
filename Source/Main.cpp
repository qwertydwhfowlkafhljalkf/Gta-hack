#include "../Header/Main.h"
int Cheat::CheatFeatures::selectedPlayer;
float TeleportFoward = 1.f;																					//Used by Teleport Forward option
int engine_multiplier, torque_multiplier;																	//Used by Vehicle Multipliers options
int SetTimeHour = 0, SetTimeMinutes = 0, SetTimeSeconds = 0;												//Used by World Time options	
int VehiclePrimaryColorRed, VehiclePrimaryColorGreen, VehiclePrimaryColorBlue;								//Used by Vehicle Color features
int VehicleSecondaryColorRed, VehicleSecondaryColorGreen, VehicleSecondaryColorBlue;						//Used by Vehicle Color features	
int VehicleNeonLightRed, VehicleNeonLightGreen, VehicleNeonLightBlue;										//Used by Vehicle Color features	
int WheelColorRed, WheelColorGreen, WheelColorBlue;															//Used by Vehicle Color features
int PlayerWantedLevelInteger = 0;																			//Used by Set Wanted Level Option
int intexploits, intoffensive, REPORTSTRENGTH, OFFENSIVETAGPLATE, OFFENSIVEUGC,								//Used by Report Stats		
    EXPLOITS, GRIEFING, COMMENDSTRENGTH, FRIENDLY, HELPFUL, VCANNOYINGME, VCHATE,						
	BADCREWNAME, BADCREWMOTTO, BADCREWSTATUS, BADCREWEMBLEM, ISPUNISHED;		
int SetPedTexture_Torso = 0, SetPedTexture_TorsoTexture = 0, SetPedTexture_Face = 0,						//Used by SetPedTexture
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
			GUI::MenuOption("Teleport", teleportmenu);
			GUI::MenuOption("World", worldmenu);
			GUI::MenuOption("Miscellaneous", miscmenu);
			GUI::MenuOption("Settings", SettingsMenu);
		}
		break;
		case AllPlayersMenu:
		{
			GUI::Title("All Players");
			GUI::MenuOption("ESP", ESPMenu);
			GUI::MenuOption("Weapon", allplayers_weaponoptionsmenu);
			GUI::MenuOption("Trolling", allplayers_trolloptionsmenu);
			if (GUI::Option("Host Kick All Players", "Kick all players from session - Host only")) 
			{
				for (int i = 1; i <= 32; i++)
				{
					if (GameFunctions::PlayerID != i) { NETWORK::NETWORK_SESSION_KICK_PLAYER(i); }
				}
			}
		}
		break;
		case allplayers_weaponoptionsmenu:
		{
			GUI::Title("All Players -> Weapon");
			if (GUI::Option("Give All Weapons", "Give all players all weapons"))
			{
				for (int i = 0; i < 32; i++)
				{
					if (GameFunctions::PlayerID != i) 
					{
						GameFunctions::SubtitleNotification("Giving all weapons to all players in session, one moment", 2000);
						GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
		}
		break; 
		case allplayers_trolloptionsmenu:
		{
			GUI::Title("Trolling"); 
			GUI::Toggle("Freeze All Players", CheatFeatures::FreezeAllPlayersBool, "Freeze all players in session", false);
			if (GUI::Option("Kick All Out Of Vehicle", "Kick all players from their vehicle"))
			{
				for (int i = 0; i < 32; i++)
				{
					if (GameFunctions::PlayerID != i)
					{
						GameFunctions::RequestNetworkControlOfEntity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
			if (GUI::Option("Airstrike All Players", ""))
			{
				for (int i = 1; i < 32; i++) {
					if (GameFunctions::PlayerID != i) {
						Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
						Coords.z += 15;
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, 1, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1, 1, 500);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 30, Coords.x, Coords.y, Coords.z, 250, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), 0, 1, 1, 500);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 55, Coords.x, Coords.y, Coords.z, 100, false, 0xF8A3939F, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true, true, 600);
					}
				}
			}
			if (GUI::Option("Trap All Players", ""))
			{
				for (int i = 1; i < 32; i++) {
					if (GameFunctions::PlayerID != i) 
					{
						Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0);
						OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
					}
				}
			}
			if (GUI::Option("Attach Beach Fire", "Burn them all!")) 
			{ 
				for (int i = 1; i <= 32; i++) 
				{
					if (GameFunctions::PlayerID != i) 
					{
						GameFunctions::AttachObjectToPed(i, "prop_beach_fire");
					}
				}
			}
		}
		break;
		case OnlineOptionsMenu:
		{
			GUI::Title("Online");
			GUI::MenuOption("Player List", PlayerListMenu);
			GUI::MenuOption("All Players", AllPlayersMenu);
			GUI::MenuOption("Protections", protections);
			GUI::MenuOption("Recovery", statsoptionsmenu);
			GUI::MenuOption("Session", sessionoptionsmenu);
			GUI::Toggle("Off Radar", CheatFeatures::OffRadarBool, "Enables Lester Off Radar Feature");
			GUI::Toggle("No Idle Kick", CheatFeatures::NoIdleKickBool, "Does not work when out of game focus");
			GUI::Toggle("Bribe Authorities", CheatFeatures::BribeAuthoritiesBool, "Enables Bribe Authorities");
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
		case statsoptionsmenu:
		{
			GUI::Title("Recovery"); 
			GUI::MenuOption("Reports", reportsmenu_stats);
			GUI::Break("Rank", true);
			if (GUI::Option("Set Custom Rank", "Input a custom Rank"))
			{
				GameFunctions::SetRankRockstarGift(GameFunctions::DisplayKeyboardAndReturnInputInteger(4, "Enter desired rank (as single digit)"));
			}
			GUI::MenuOption("Unlocks", unlocksmenu);
			GUI::Break("Miscellaneous", true);
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
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_MENTAL_STATE")), 0.0, true);
				GameFunctions::MinimapNotification("Mental State Reset");
			}
		}
		break; 
		case reportsmenu_stats:
		{
			GUI::Title("Reports"); 
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
		case unlocksmenu:
		{
			GUI::Title("Unlocks");
			if (GUI::Option("Unlock All", "Unlocks most unlockable GTA Online items")) 
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
			if (GUI::Option("Max Skills", "Max out all skill levels")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STAM")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STRN")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_LUNG")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_DRIV")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_FLY")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_SHO")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STL")), 100, 0);
				GameFunctions::MinimapNotification("Maxed out all skill values for your current character"); 	
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
			if (GUI::Option("Unlock All Heist Vehicles", "Unlock Heist Vehicles")) 
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
		}
		break;
		case ModelChangerMenu:
		{
			GUI::Title("Model Changer");
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
			GUI::Break("Ped List", true);
			for (auto const& i : GameArrays::PedModels)
			{
				if (GUI::Option(i, ""))
				{
					GameFunctions::ChangePedModelLocalPlayer(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)));
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
					GUI::Break(std::to_string(i), true);
					if (GUI::Option("Teleport To", ""))
					{
						GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, GameFunctions::GetEntityCoords(i), false, false);
					}
					if (GUI::Option("Teleport Into Vehicle", ""))
					{
						PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, i, -1);
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
				GUI::Break("No Vehicles Were Spawned Yet", false);
			}
		}
		break;
		case vehiclespawnermenu:
		{
			GUI::Title("Vehicle Spawn");
			GUI::MenuOption("Settings", VehicleSpawnSettings);
			GUI::MenuOption("Spawned Vehicles", SpawnedVehiclesMenu);
			if (GUI::Option("Custom Input", "Input custom vehicle model name"))
			{
				char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter custom vehicle model name");
				if (KeyboardInput == "0") { break; }
				GameFunctions::SpawnVehicle(KeyboardInput);
			}
			GUI::Break("Categories", true);
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
		case DLCVehiclesMenu:
		{
			GUI::Title("DLC Vehicles");
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
			GUI::MenuOption("Spawn", vehiclespawnermenu);
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
					if (CheatFeatures::UseKMH)
					{
						ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, GameFunctions::KMHToMS(MaxSpeedInput));
						GameFunctions::MinimapNotification("Max Speed Set (KM/H)");
					}
					else
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
			GUI::Toggle("Vehicle God Mode", CheatFeatures::VehicleGodmodeBool, "Makes current vehicle invincible");
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
			if (GUI::Option("Repair & Clean", "Repair & Clean current vehicle"))
			{
				GameFunctions::RepairAndCleanVehicle();
			}
			if (GUI::Option("Max Upgrade", "Max Upgrade current vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) {
					GameFunctions::MaxUpgradeVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
					GameFunctions::AdvancedMinimapNotification("Vehicle Max Upgraded", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (GUI::Option("Max Downgrade", "Max downgrade current vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) {
					GameFunctions::MaxDowngradeVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
					GameFunctions::AdvancedMinimapNotification("Vehicle Max Downgraded", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (GUI::Option("Add Blip Registration", "Add Blip To Current Vehicle")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) {

					GameFunctions::AddBlipToVehicle(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID));
				}
				else
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (GUI::Option("Change License Plate Text", "Input custom vehicle license plate text"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(GameFunctions::PlayerPedID, 0)) {			
					Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID);
					char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(8, "Enter new license plate text");
					if (KeyboardInput == "0") { break; }
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, KeyboardInput);
					GameFunctions::AdvancedMinimapNotification("License Plate Text Updated", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			GUI::MenuOption("Color", VehicleCustomizerColorMenu);
			GUI::MenuOption("Neon", vehicle_lsc_neon_options);
			GUI::MenuOption("Multipliers", vehiclemultipliersmenus);
			GUI::MenuOption("Door", vehicledooroptionsmenu);
		}
		break;
		case VehicleCustomizerColorMenu:
		{
			GUI::Title("Custom Color");
			GUI::Int("Primary Color: Red", VehiclePrimaryColorRed, 0, 255, 1);
			GUI::Int("Primary Color: Green", VehiclePrimaryColorGreen, 0, 255, 1);
			GUI::Int("Primary Color: Blue", VehiclePrimaryColorBlue, 0, 255, 1);
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
			GUI::Int("Secondary Color: Red", VehicleSecondaryColorRed, 0, 255, 1);
			GUI::Int("Secondary Color: Green", VehicleSecondaryColorGreen, 0, 255, 1);
			GUI::Int("Secondary Color: Blue", VehicleSecondaryColorBlue, 0, 255, 1);
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
			GUI::Break("~bold~Color Presets", true);
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
			GUI::Int("Neon Color: Red", VehicleNeonLightRed, 0, 255, 1);
			GUI::Int("Neon Color: Green", VehicleNeonLightGreen, 0, 255, 1);
			GUI::Int("Neon Color: Blue", VehicleNeonLightBlue, 0, 255, 1);
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
			GUI::Break("Neon Presets", true);
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
			GUI::Int("Engine Multiplier", engine_multiplier, 0, 1000, 1, "Set Engine Multiplier value");
			GUI::Int("Engine Torque Multiplier", torque_multiplier, 0, 1000, 1, "Set engine torque multiplier value");
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
		case vehicledooroptionsmenu:
		{
			GUI::Title("Door");
			if (GUI::Option("Open All Doors", "Open All Vehicle Doors"))
			{
				for (int CurrentDoorIndex = 0; CurrentDoorIndex < 8; CurrentDoorIndex++)
				{
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), CurrentDoorIndex, true, false);
				}
			}
			if (GUI::Option("Close All Doors", "Close All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), true); }
			if (GUI::Option("Lock All Doors", "Lock All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), 4); }
			if (GUI::Option("Unlock All Doors", "Unlock All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(GameFunctions::PlayerPedID), 0); }
		}
		break;
		case vehicleweaponsmenu:
		{
			GUI::Title("Vehicle Weapons");
			GUI::Toggle("Toggle Vehicle Weapons", CheatFeatures::VehicleWeaponsBool, "Press horn button to use");
			GUI::Toggle("Show Lines", CheatFeatures::VehicleWeapons_DrawLaser, "Show lines in front of vehicle");
			if (CheatFeatures::VehicleWeapons_TankRounds) 
			{
				GUI::Break("Current: ~c~Tank Rounds", false);
			}
			if (CheatFeatures::VehicleWeapons_VehicleRockets) 
			{
				GUI::Break("Current: ~c~Vehicle Rockets", false);
			}
			if (CheatFeatures::VehicleWeapons_Fireworks) 
			{
				GUI::Break("Current: ~c~Fireworks", false);
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
			GUI::Toggle("Spawn Inside Vehicle", CheatFeatures::VehicleSpawnerSpawnInsideVehicle, "");
			GUI::Toggle("Spawn With God Mode", CheatFeatures::VehicleSpawnerSpawnWithGodmode, "");
			GUI::Toggle("Spawn Max Upgraded", CheatFeatures::VehicleSpawnerSpawnMaxUpgraded, "");
			GUI::Toggle("Delete Old Vehicle", CheatFeatures::VehicleSpawnerDeleteOldVehicle, "");
			GUI::Toggle("Spawn With Blip", CheatFeatures::VehicleSpawnerSpawnWithBlip, "");
		}
		break; 
		case worldmenu:
		{
			GUI::Title("World");
			GUI::MenuOption("Time", timemenu);
			GUI::MenuOption("Weather", weathermenu);
			GUI::MenuOption("Nearby Vehicles", nearbyvehicles_menu);
			GUI::MenuOption("Nearby Peds", nearbypeds_menu); 
			GUI::Toggle("Snow (local)", CheatFeatures::WorldSnowLocalBool, "GTA Online Only");
			if (GUI::Option("Clear Area", "Clear area of vehicles, objects etc")) 
			{
				Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(GameFunctions::PlayerPedID, false);
				GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 250, true, 0, 0, 0);
				GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 250, 0, 0, 0, 0, 0);
				GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_PROJECTILES(MyPos.x, MyPos.y, MyPos.z, 250, 0);

				//Seperate Remove Nearby Vehicles: for spawned vehicles
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
				GameFunctions::MinimapNotification("Area Cleared");
			}
			GUI::Toggle("No Gravity", CheatFeatures::NoGravityBool, "Disable gravity in the world");
			GUI::Toggle("Blackout", CheatFeatures::WorldBlackoutBool, "Disable All Map Lights");
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
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[OffsetID], false);
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
			GUI::Break("~bold~Scenarios", true);
			if (GUI::Option("Paparizzi", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_PAPARAZZI");
			}
			if (GUI::Option("Drug Dealer", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_DRUG_DEALER_HARD");
			}
			if (GUI::Option("Drinking Coffee", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_AA_COFFEE");
			}
			if (GUI::Option("Playing Instruments", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MUSICIAN");
			}
			if (GUI::Option("Flexing", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MUSCLE_FLEX");
			}
			if (GUI::Option("Jogging", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_JOG_STANDING");
			}
			if (GUI::Option("Binoculars", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_BINOCULARS");
			}
			if (GUI::Option("Clipboard", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_CLIPBOARD");
			}
			if (GUI::Option("Bench Press", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS");
			}
			if (GUI::Option("Chin Ups", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_MUSCLE_CHIN_UPS");
			}
			if (GUI::Option("BBQ", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_BBQ");
			}
			if (GUI::Option("Superhero", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SUPERHERO");
			}
			if (GUI::Option("Fishing", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_STAND_FISHING");
			}
			if (GUI::Option("Security", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SECURITY_SHINE_TORCH");
			}
			if (GUI::Option("Leaf Blower", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_GARDENER_LEAF_BLOWER");
			}
			if (GUI::Option("Film Shocking", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MOBILE_FILM_SHOCKING");
			}
			if (GUI::Option("Idle Cop", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_COP_IDLES");
			}
			if (GUI::Option("Drinking", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_DRINKING");
			}
			if (GUI::Option("Golf Player", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_GOLF_PLAYER");
			}
			if (GUI::Option("Welding", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_WELDING");
			}
			if (GUI::Option("Smoking Pot", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SMOKING_POT");
			}
			if (GUI::Option("Hammering", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_HAMMERING");
			}
			if (GUI::Option("Tennis", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_TENNIS_PLAYER");
			}
			if (GUI::Option("Drilling", "")) 
			{
				GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_CONST_DRILL");

			}
			GUI::Break("~bold~Animations", true);
			if (GUI::Option("Sex Receiver", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("rcmpaparazzo_2", "shag_loop_poppy");
			}
			if (GUI::Option("Sex Giver", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("rcmpaparazzo_2", "shag_loop_a");
			}
			if (GUI::Option("Stripper Dance", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1");
			}
			if (GUI::Option("Pole Dance", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
			}
			if (GUI::Option("Push Ups", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("amb@world_human_push_ups@male@base", "base");
			}
			if (GUI::Option("Sit Ups", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("amb@world_human_sit_ups@male@base", "base");
			}
			if (GUI::Option("Celebrate", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("rcmfanatic1celebrate", "celebrate");
			}
			if (GUI::Option("Electrocution", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("ragdoll@human", "electrocute");
			}
			if (GUI::Option("Suicide", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("mp_suicide", "pistol");
			}
			if (GUI::Option("Showering", "")) 
			{
				GameFunctions::ClearNearbyPedAnimations();
				GameFunctions::DoNearbyPedsAnimation("mp_safehouseshower@male@", "male_shower_idle_b");
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
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
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
			if (GUI::Int("Hour", SetTimeHour, 0, 23, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(SetTimeHour, TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS()); }
			if (GUI::Int("Minutes", SetTimeMinutes, 0, 59, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), SetTimeMinutes, TIME::GET_CLOCK_SECONDS()); }
			if (GUI::Int("Seconds", SetTimeSeconds, 0, 59, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), TIME::GET_CLOCK_MINUTES(), SetTimeSeconds); }
			GUI::Break("Current Time", true);
			std::string CurrentGameTimeString = "Game Time: ~c~" + std::to_string(TIME::GET_CLOCK_HOURS()) + ":" + std::to_string(TIME::GET_CLOCK_MINUTES()) + ":" + std::to_string(TIME::GET_CLOCK_SECONDS());
			GUI::Break(CurrentGameTimeString.c_str(), false);
			std::string CurrentSystemTimeString = "System Time: ~c~" + CheatFunctions::ReturnDateTimeFormatAsString("%H:%M:%S");
			GUI::Break(CurrentSystemTimeString.c_str(), false);
			GUI::Break("Misc", true);
			GUI::Toggle("Slow Motion", CheatFeatures::SlowMotionBool, "Slows Down Game Time");
			GUI::Toggle("Pause Time", CheatFeatures::PauseTimeBool, "Pause Game Time");
		}
		break;
		case weathermenu:
		{
			GUI::Title("Weather");
			if (GUI::Option("Extra Sunny", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("EXTRASUNNY"); }
			if (GUI::Option("Sunny", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("CLEAR"); }
			if (GUI::Option("Cloudy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("CLOUDS"); }
			if (GUI::Option("Smoggy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SMOG"); }
			if (GUI::Option("Foggy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("FOGGY"); }
			if (GUI::Option("Overcast", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("OVERCAST"); }
			if (GUI::Option("Stormy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("THUNDER"); }
			if (GUI::Option("Snow", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SNOW"); }
			if (GUI::Option("Snowlight", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SNOWLIGHT"); }
			if (GUI::Option("Blizzard", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("BLIZZARD"); }
		}
		break;
		case miscmenu:
		{
			GUI::Title("Miscellaneous");
			GUI::MenuOption("HUD", hudmenu); 
			GUI::MenuOption("IPL Loader", iplloader);
			GUI::Toggle("Disable Phone", CheatFeatures::DisablePhoneBool, "Disable phone controls");
			GUI::Toggle("Get 6 Fake Wanted Level Stars", CheatFeatures::FakeWantedLevelBool, "");
			GUI::Toggle("No-Clip", CheatFeatures::NoClipBool, "Use W and mouse to control");
			GUI::Toggle("Jump Around Mode", CheatFeatures::JumpAroundModeBool, "Nearby vehicles will 'jump around'");
			GUI::Toggle("Free Cam", CheatFeatures::FreeCamBool, "Use W and S to control. Shift to go faster");
			GUI::Toggle("Show Joining Players Notification", CheatFeatures::ShowJoiningPlayersNotification, "");
			GUI::Toggle("No Orbital Cannon Cooldown", CheatFeatures::OrbitalCannonCooldownBypassBool, "");
			GUI::Toggle("Rockstar Developer Mode", CheatFeatures::GTAODeveloperMode, "Toggles GTAO Spectator Options");
			GUI::Toggle("Auto Teleport To Waypoint", CheatFeatures::AutoTeleportToWaypointBool, "");
			GUI::Toggle("Force Field", CheatFeatures::PlayerForceFieldBool, "Gives your character a force field");
			GUI::Toggle("Show Session Information", CheatFeatures::ShowSessionInformationBool, "Show session info (next to radar)");
			GUI::Toggle("Show FPS", CheatFeatures::ShowFPSBool, "Show game FPS");
			GUI::Toggle("Mobile Radio", CheatFeatures::MobileRadioBool, "");
			if (GUI::Option("Drive To Waypoint", "A NPC drives you to waypoint"))
			{
				int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
				if (UI::DOES_BLIP_EXIST(WaypointHandle))
				{
					std::string VehicleName = "marshall";
					Vector3 waypoint1 = UI::GET_BLIP_COORDS(UI::GET_FIRST_BLIP_INFO_ID(8));
					STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)));
					while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)))) { GameHooking::PauseMainFiber(0); }
					Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0, 5.0, 0);
					Vehicle veh = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(VehicleName)), pos.x, pos.y, pos.z, ENTITY::GET_ENTITY_HEADING(GameFunctions::PlayerPedID), 1, 1);
					if (veh != 0)
					{
						Ped Driver = PED::CREATE_RANDOM_PED_AS_DRIVER(veh, false);
						PED::SET_PED_INTO_VEHICLE(Driver, veh, -1);
						PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, veh, 0);
						AI::TASK_VEHICLE_DRIVE_TO_COORD(Driver, veh, waypoint1.x, waypoint1.y, waypoint1.z, 40, 1, ENTITY::GET_ENTITY_MODEL(veh), 7, 6, -1);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "CRUSADER");
						GameFunctions::MinimapNotification("NPC Driver Spawned");
					}
				}
				else { GameFunctions::MinimapNotification("Please set a waypoint first to use this feature"); }
			}		
			if (GUI::Option("Get Empty Session", "Get Empty (Public) Session")) { Sleep(10000); }
			if (GUI::Option("Exit to Single Player", "")) { NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME(); }
		}
		break;
		case hudmenu:
		{
			GUI::Title("HUD");
			GUI::Toggle("Hide All HUD Elements", CheatFeatures::HideHUDBool, "");
		}
		break; 
		case iplloader:
		{
			GUI::Title("IPL Loader");
			GUI::MenuOption("Go to IPL Teleports submenu", iplteleports);
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
			if (GUI::Option("Remove All Weapons", ""))
			{
				if (CheatFeatures::AutoGiveAllWeaponsBool) { GameFunctions::MinimapNotification("Disable 'Auto Give All Weapons' to use this"); }
				else { WEAPON::REMOVE_ALL_PED_WEAPONS(GameFunctions::PlayerPedID, true); }
			}
			GUI::Break("Upgrades", true);
			if (GUI::Option("Max Upgrade All Weapons", "Max Upgrade All Weapons"))
			{
				GameFunctions::MaxUpgradeAllWeapons();
			}
			GUI::Break("Auto", true);
			GUI::Toggle("Auto Get All Weapons", CheatFeatures::AutoGiveAllWeaponsBool, "");
			GUI::Toggle("Auto Get All Weapon Upgrades", CheatFeatures::AutoGiveAllWeaponUpgradesBool, "");
			GUI::Break("Color", true);
			GUI::Toggle("Rainbow Gun", CheatFeatures::RainbowGunBool, "");
		}
		break;
		case WeaponVisualsMenu:
		{
			GUI::Title("Visuals");
			GUI::Toggle("Crosshair", CheatFeatures::CrossHairBool, "");
			GUI::Toggle("Cartoon Gun", CheatFeatures::CartoonGunBool, "Shows cartoon effects while shooting");
		}
		break;
		case weaponmenu: 
		{
			GUI::Title("Weapon");
			GUI::MenuOption("Weapons", WeaponsMenu);
			GUI::MenuOption("Visuals", WeaponVisualsMenu);
			GUI::MenuOption("Custom Bullets", custombulletsmenu);
			GUI::MenuOption("Vehicle Gun", vehiclegunmenu);
			GUI::MenuOption("Aimbot", aimbotsettingsmenu);		
			GUI::Break("General", true);
			GUI::Toggle("No reload", CheatFeatures::NoWeaponReloadBool, "Always have max amount of ammo");
			GUI::Toggle("Teleport Gun", CheatFeatures::TeleportGunBool, "Teleport to where you shoot");
			GUI::Toggle("Entity Information Gun", CheatFeatures::EntityInformationGunBool, "Shows info about aimed entity");
			GUI::Toggle("Delete Gun", CheatFeatures::DeleteGunBool, "Use SNS Pistol with this option");
			GUI::Toggle("Rapid Fire", CheatFeatures::WeaponRapidFireBool, "Shoot very fast");
			GUI::Toggle("Money Gun", CheatFeatures::MoneyGunBool, "Drops money bags where you shoot");
			GUI::Toggle("One Shot One Kill", CheatFeatures::OneHitKillBool, "Better known as 'one-hit kill'");
			GUI::Toggle("Gravity Gun", CheatFeatures::GravityGunBool, "Use Combat Pistol for this option");
			GUI::Toggle("Airstrike Gun", CheatFeatures::AirstrikeGunBool, "");
		}
		break; 
		case vehiclegunmenu:
		{
			GUI::Title("Vehicle Gun");
			GUI::Toggle("Toggle Vehicle Gun", CheatFeatures::VehicleGunBool, "Toggle Vehicle Gun");
			GUI::Break("Current: ~t~" + CheatFeatures::VehicleGun_VehicleNameString, false);
			GUI::Break("Vehicles", true);
			if (GUI::Option("Custom Input", "Custom Vehicle Gun Input"))
			{
				char* SpawnVehicle = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter custom vehicle model name");
				if (SpawnVehicle == "0") { break; }

				Hash model = GAMEPLAY::GET_HASH_KEY(SpawnVehicle);
				if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_A_VEHICLE(model)) 
				{ 
					GameFunctions::MinimapNotification("~r~Not a valid vehicle model"); 
				}
				else
				{
					CheatFeatures::VehicleGun_VehicleNameString = SpawnVehicle;
					GameFunctions::MinimapNotification("Custom Vehicle Set");
				}
			}
			if (GUI::Option("Rhino Tank", "")) { CheatFeatures::VehicleGun_VehicleNameString = "RHINO"; }
			if (GUI::Option("Hydra", "")) { CheatFeatures::VehicleGun_VehicleNameString = "HYDRA"; }
			if (GUI::Option("Airport Bus", "")) { CheatFeatures::VehicleGun_VehicleNameString = "AIRBUS"; }
			if (GUI::Option("Brickade", "")) { CheatFeatures::VehicleGun_VehicleNameString = "BRICKADE"; }
			if (GUI::Option("Cargo Plane", "")) { CheatFeatures::VehicleGun_VehicleNameString = "CARGOPLANE"; }
			if (GUI::Option("Dump", "")) { CheatFeatures::VehicleGun_VehicleNameString = "DUMP"; }
		}
		break;
		case custombulletsmenu: 
		{
			GUI::Title("Custom Bullets");
			GUI::Toggle("Toggle Custom Bullets", CheatFeatures::CustomWeaponBulletsBool, "");
			GUI::Toggle("Valkyrie Bullets", CheatFeatures::CustomWeaponBullets_ValkyrieGun, "");
			GUI::Toggle("Tank Bullets", CheatFeatures::CustomWeaponBullets_TankBullets, "");
			GUI::Toggle("RPG Bullets", CheatFeatures::CustomWeaponBullets_RpgBullets, "");
			GUI::Toggle("Firework Bullets", CheatFeatures::CustomWeaponBullets_FireworkBullets, "");
		}
		break; 
		case aimbotsettingsmenu:
		{
			GUI::Title("Aimbot");
			GUI::Toggle("Toggle Triggerbot", CheatFeatures::TriggerBotBool, "Toggle Triggerbot");
			GUI::Toggle("Shoot NPC's", CheatFeatures::TriggerBot_ShootNPCBool, "Triggerbot shoots at NPC's");
			GUI::Toggle("Shoot Players", CheatFeatures::TriggerBot_ShootPlayersBool, "Triggerbot shoots at players");
		}
		break;
		case teleportmenu:
		{
			GUI::Title("Teleport");
			if (GUI::Option("Teleport To Waypoint", "")) { GameFunctions::TeleportToBlipCoord(SpriteWaypoint); }
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
				}
				catch (...)
				{
					GameFunctions::MinimapNotification("~r~Invalid float coordinate format inputted");
					break;
				}

			CanceledCustomTeleport:
				GameFunctions::MinimapNotification("Canceled custom coordinate teleporting");
			} 
			if (GUI::Option("Teleport Into Last Used Vehicle", ""))
			{
				PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, VEHICLE::GET_LAST_DRIVEN_VEHICLE(), -1);
			}
			if (GUI::Float("Teleport Forward", TeleportFoward, 1.f, 10.f, 1.f, false, false, "Select to teleport"))
			{
				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0, TeleportFoward, 0.0);
				int Handle = GameFunctions::PlayerPedID;
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) { Handle = PED::GET_VEHICLE_PED_IS_IN(GameFunctions::PlayerPedID, 0); }
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 1);
			}
			GUI::MenuOption("IPL Teleports", iplteleports);
			GUI::MenuOption("Common Locations", CommonTeleportLocations);
		}
		break;
		case CommonTeleportLocations:
		{
			GUI::Title("Common Teleport Locations");	
			if (GUI::Option("High In The Sky", ""))
			{
				Vector3 Coords;
				Coords.x = 240.93f; Coords.y = -765.19f; Coords.z = 2558.83f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Diamond Casino & Resort", ""))
			{
				Vector3 Coords;
				Coords.x = 916.37f; Coords.y = 51.22f; Coords.z = 80.89f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Mount Chiliad", "")) 
			{
				Vector3 Coords;
				Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}		
			if (GUI::Option("Maze Bank", "")) 
			{
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (GUI::Option("Military Base", "")) 
			{
				Vector3 Coords;
				Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Zancudo Tower", "")) 
			{
				Vector3 Coords;
				Coords.x = -2356.0940f; Coords.y = 3248.645f; Coords.z = 101.4505f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Mask Shop", "")) 
			{
				Vector3 Coords;
				Coords.x = -1338.16f; Coords.y = -1278.11f; Coords.z = 4.87f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (GUI::Option("LSC", "")) {
				Vector3 Coords;
				Coords.x = -373.01f; Coords.y = -124.91f; Coords.z = 38.31f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Ammunation", "")) 
			{
				Vector3 Coords;
				Coords.x = 247.3652f; Coords.y = -45.8777f; Coords.z = 69.9411f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (GUI::Option("Airport", "")) 
			{
				Vector3 Coords;
				Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Clothes Store", "")) 
			{
				Vector3 Coords;
				Coords.x = -718.91f; Coords.y = -158.16f; Coords.z = 37.00f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Waterfall", "")) 
			{
				Vector3 Coords;
				Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("FIB", "")) 
			{
				Vector3 Coords;
				Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (GUI::Option("Human Labs", "")) 
			{
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (GUI::Option("MMI", "")) 
			{
				Vector3 Coords;
				Coords.x = -222.1977f; Coords.y = -1185.8500f; Coords.z = 23.0294f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}		
			if (GUI::Option("Sandy Shores Airfield", "")) 
			{
				Vector3 Coords;
				Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
			}
		}
		break;
		case iplteleports:
		{
			GUI::Title("IPL Teleports");
			GUI::MenuOption("Go to IPL Loader submenu", iplloader);
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
		case ESPMenu:
		{
			GUI::Title("Extra-sensory Perception");
			GUI::Toggle("Basic ESP", CheatFeatures::PlayerESPBool, "Toggle Player ESP");
		}
		break; 
		case SelectedPlayerTrollMenu:
		{
			GUI::Title("Trolling");
			GUI::MenuOption("Attachments", SelectedPlayerAttachmentOptions);
			GUI::Toggle("Explode Loop", CheatFeatures::ExplodeLoopSelectedPlayerBool, "Run explode loop on selected player", false);
			GUI::Toggle("Freeze Player", CheatFeatures::FreezeSelectedPlayerBool, "Freeze character of selected player", false);
			GUI::Toggle("Shake Cam", CheatFeatures::ShakeCamSelectedPlayerBool, "Shake selected player character camera", false);
			if (GUI::Option("Set Off Car Alarm", "Enable Car Alarm of Selected Player"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					GameFunctions::SetOffAlarmPlayerVehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer));
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (GUI::Option("Burst Vehicle Tires", "Burst selected player vehicle tires"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					GameFunctions::BurstSelectedPlayerTires(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer));
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}			
			}
			if (GUI::Option("Airstrike Player", "Airstrike selected player"))
			{
				Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), 1);
				Coords.z += 15;
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, 1, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), 1, 1, 500);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 30, Coords.x, Coords.y, Coords.z, 250, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), 0, 1, 1, 500);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 55, Coords.x, Coords.y, Coords.z, 100, false, 0xF8A3939F, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), true, true, 600);
			}
			if (GUI::Option("Attach to player", "Attach to selected player"))
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer) != GameFunctions::PlayerPedID)
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(GameFunctions::PlayerPedID, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
				}
			}
			if (GUI::Option("Detach from player", "Detach from selected player"))
			{
				ENTITY::DETACH_ENTITY(GameFunctions::PlayerPedID, true, true);
			}
			if (GUI::Option("Slingshot Vehicle", "Slingshot selected player vehicle"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), true));
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), true)))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					}
				}
				else 
				{
					GameFunctions::MinimapNotification("~r~Player is not in a vehicle"); 
				}
			}
			if (GUI::Option("Ram With Vehicle", "Ram selected player with vehicle"))
			{
				Hash model = GAMEPLAY::GET_HASH_KEY("trophytruck2");
				if (STREAMING::IS_MODEL_VALID(model))
				{
					for (int i = 0; i < 3; i++)
					{
						STREAMING::REQUEST_MODEL(model);
						while (!STREAMING::HAS_MODEL_LOADED(model)) GameHooking::PauseMainFiber(0);
						Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), false);
						float forward = 10.f;
						float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer));
						float xVector = forward * sin(GameFunctions::DegreesToRadians(heading)) * -1.f;
						float yVector = forward * cos(GameFunctions::DegreesToRadians(heading));
						Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x - xVector, ourCoords.y - yVector, ourCoords.z, heading, true, true);
						GameFunctions::RequestNetworkControlOfEntity(veh);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 250);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					}
				}
			}
			if (GUI::Option("Trap Player", "Trap selected player"))
			{
				Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), 0);
				Object obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
			}
			if (GUI::Option("Clone Player", "Clone selected player"))
			{
				GameFunctions::ClonePed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer));
			}
			if (GUI::Option("Kick out of vehicle", "Kick selected player out of vehicle"))
			{
				Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				GameFunctions::RequestNetworkControlOfEntity(playerPed);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				AI::CLEAR_PED_TASKS(playerPed);
				AI::CLEAR_PED_SECONDARY_TASK(playerPed);
			}
			if (GUI::Option("Spawn Enemy", "Spawn enemy to attack selected player"))
			{
				int eclone[1000];
				int egcount = 1;
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (GUI::Option("Spawn Bodyguard", "Spawn Bodyguard for selected player")) 
			{
				int clone[1000];
				int gcount = 1;
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
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
			GUI::Title("Player List");
			for (int i = 0; i < 32; ++i)
			{
				std::string PlayernameString = PLAYER::GET_PLAYER_NAME(i);
				if (GameFunctions::IsPlayerIDValid(i))
				{
					if (GameFunctions::PlayerIsFreemodeScriptHost(i)) { PlayernameString.append(" ~o~[Host]"); }
					if (GameFunctions::IsPlayerFriend(i)) { PlayernameString.append(" ~b~[Friend]"); }
					if (GameFunctions::IsEntityInInterior(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) { PlayernameString.append(" ~p~[Interior]"); }
					if (GameFunctions::PlayerID == i) { PlayernameString.append(" ~g~[You]"); }
					GUI::MenuOptionPlayerList(PlayernameString, SelectedPlayerMenu) ? CheatFeatures::selectedPlayer = i : NULL;
					if (GUI::currentOption == GUI::optionCount) { GameFunctions::ShowPlayerInformationBox(i); }
				}
			}
		}
		break;
		case SelectedPlayerMenu:
		{
			GUI::Title(PLAYER::GET_PLAYER_NAME(CheatFeatures::selectedPlayer));
			GUI::Toggle("Spectate", CheatFeatures::SpectatePlayerBool, "", false);
			if (GUI::Option("Host Kick", "Kick selected player - Host only")) { NETWORK::NETWORK_SESSION_KICK_PLAYER(CheatFeatures::selectedPlayer); }
			if (GUI::Option("Teleport To", ""))
			{
				GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), false), 
					                                   false, false);
			}
			GUI::MenuOption("Teleport", SelectedPlayerTeleportMenu);
			GUI::MenuOption("Friendly", SelectedPlayerFriendlyMenu);
			GUI::MenuOption("Trolling", SelectedPlayerTrollMenu);
			GUI::MenuOption("Script Events", SelectedPlayerRemoteOptions, true);
			if (GUI::Option("Copy Outfit", "Get Selected Player Outfit")) { GameFunctions::CopySelectedPlayerOutfit(CheatFeatures::selectedPlayer); }
			if (GUI::Option("View Profile", "View Selected Player Social Club Profile")) { int playerHandle; NETWORK::NETWORK_HANDLE_FROM_PLAYER(CheatFeatures::selectedPlayer, &playerHandle, 13); NETWORK::NETWORK_SHOW_PROFILE_UI(&playerHandle); }
		}
		break;
		case SelectedPlayerFriendlyMenu:
		{
			GUI::Title("Friendly");
			GUI::MenuOption("Money", SelectedPlayerMoneyMenu);
			if (GUI::Option("Give All Weapons", "Give all weapons to selected player")) { GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer)); }
		}
		break;
		case SelectedPlayerRemoteOptions:
		{
			GUI::Title("Script Events");
			if (GUI::Option("Kick To Single Player", "Kick Selected Player to SP")) 
			{
				if (NETWORK::NETWORK_IS_SESSION_STARTED())
				{
					//uint64_t kick_sp[4] = { 1667907776, CheatFeatures::selectedPlayer, 0, 0 };
					//SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick_sp, 4, 1 << CheatFeatures::selectedPlayer);
				}
			}
		}
		break; 
		case SelectedPlayerTeleportMenu:
		{
			GUI::Title("Teleport"); 
			if (GUI::Option("Teleport Into Vehicle", "Teleport into Selected Player vehicle"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), false);
				for (int i = -1; i < 16; i++) { if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i)) { PED::SET_PED_INTO_VEHICLE(GameFunctions::PlayerPedID, veh, i); } }
			}
		}
		break; 
		case SelfOptionsMenu:
		{
			GUI::Title("Self");
			GUI::MenuOption("Model Changer", ModelChangerMenu);
			GUI::MenuOption("Animations & Scenarios", AnimationsAndScenariosMenu);
			GUI::MenuOption("Clothing", clothingmenu);
			GUI::Toggle("God Mode", CheatFeatures::GodmodeBool, "Makes your character invincible", true);
			GUI::Toggle("No Ragdoll & Seatbelt", CheatFeatures::NoRagdollAndSeatbeltBool, "Disables ragdoll on your character");
			GUI::Toggle("Super Jump", CheatFeatures::SuperJumpBool, "Makes your character jump higher");
			GUI::Toggle("Super Run", CheatFeatures::SuperRunBool, "Run very fast");
			GUI::Toggle("Fast Run", CheatFeatures::FastRunBool, "Multiplies run speed");
			GUI::Toggle("Ignored By Everyone", CheatFeatures::PlayerIgnoredBool, "NPC's will (mostly) ignore you");
			GUI::Toggle("Never Wanted", CheatFeatures::NeverWantedBool, "Never get a wanted level");
			if (GUI::Int("Wanted Level", PlayerWantedLevelInteger, 0, 5, 1, false, "Set Wanted Level")) { CheatFeatures::NeverWantedBool = false; PLAYER::SET_PLAYER_WANTED_LEVEL(GameFunctions::PlayerID, PlayerWantedLevelInteger, false); PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(GameFunctions::PlayerID, false); }
			GUI::Toggle("Invisibility", CheatFeatures::PlayerInvisibleBool, "Makes your character invisible");
			GUI::Toggle("Explosive Melee", CheatFeatures::ExplosiveMeleeBool, "Objects you hit with melee explode");
			GUI::Toggle("Tiny Player", CheatFeatures::TinyPlayerBool, "Lowers your character's scaling");
			GUI::Toggle("Super Man", CheatFeatures::SuperManBool, "Fly around like a superman!");
			if (GUI::Int("Opacity", CheatFeatures::PlayerOpacityInt, 50, 250, 50, false, "Changes local player opacity")) { ENTITY::SET_ENTITY_ALPHA(GameFunctions::PlayerPedID, (CheatFeatures::PlayerOpacityInt), false); }
			if (GUI::Option("Suicide", "Kill your character")) { PED::APPLY_DAMAGE_TO_PED(GameFunctions::PlayerPedID, 300, true); }
			if (GUI::Option("Give BST", "Get Bull Shark Testosterone - GTAO Only")) { globalHandle(2441237).At(4013).As<int>() = 1; }
			if (GUI::Option("Clean", "Remove any damage from player character")) { PED::CLEAR_PED_BLOOD_DAMAGE(GameFunctions::PlayerPedID); PED::RESET_PED_VISIBLE_DAMAGE(GameFunctions::PlayerPedID); GameFunctions::MinimapNotification("Player Cleaned"); }	
		}
		break;
		case SelectedPlayerMoneyMenu:
		{
			GUI::Title("Money");
			GUI::Toggle("Toggle", CheatFeatures::MoneyDropBool, "Enable Money Drop on selected player", false);
			GUI::Int("Drop Delay", CheatFeatures::MoneyDropDelay, 50, 2000, 50, false, "Set to 1500 to prevent transaction errors");
		} 
		break;
		case clothingmenu:
		{
			GUI::Title("Clothing"); 
			GUI::MenuOption("Outfits", outfitsmenu); 
			GUI::MenuOption("Components Changer", componentschangermenu);
		}
		break; 
		case componentschangermenu:
		{
			GUI::Title("Components Changer");
			if (GUI::Int("Face", SetPedTexture_Face, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, 0); }
			if (GUI::Int("Face Texture", SetPedTexture_FaceTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Face, SetPedTexture_Face); }
			if (GUI::Int("Head", SetPedTexture_Head, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 0, SetPedTexture_Head, 0); }
			if (GUI::Int("Head Texture", SetPedTexture_HeadTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 1, SetPedTexture_Head, SetPedTexture_HeadTexture); }
			if (GUI::Int("Hair", SetPedTexture_Hair, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, 0); }
			if (GUI::Int("Hair Texture", SetPedTexture_HairTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, SetPedTexture_HairTexture); }
			if (GUI::Int("Torso", SetPedTexture_Torso, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, 0); }
			if (GUI::Int("Torso Texture", SetPedTexture_TorsoTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, SetPedTexture_TorsoTexture); }
			if (GUI::Int("Legs", SetPedTexture_Legs, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, 0); }
			if (GUI::Int("Legs Texture", SetPedTexture_LegsTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, SetPedTexture_LegsTexture); }
			if (GUI::Int("Hands", SetPedTexture_Hands, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, 0); }
			if (GUI::Int("Hands Texture", SetPedTexture_HandsTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, SetPedTexture_HandsTexture); }
			if (GUI::Int("Feet", SetPedTexture_Feet, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, 0); }
			if (GUI::Int("Feet Texture", SetPedTexture_FeetTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, SetPedTexture_FeetTexture); }
			if (GUI::Int("Eyes", SetPedTexture_Eyes, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, 0); }
			if (GUI::Int("Eyes Texture", SetPedTexture_EyesTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, SetPedTexture_EyesTexture); }
			if (GUI::Int("Accesories", SetPedTexture_Accesories, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, 0); }
			if (GUI::Int("Accesories Texture", SetPedTexture_AccesoriesTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, SetPedTexture_AccesoriesTexture); }
			if (GUI::Int("Accesories2", SetPedTexture_AccesoriesSec, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, 0); }
			if (GUI::Int("Accesories2 Texture", SetPedTexture_AccesoriesSecTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, SetPedTexture_AccesoriesSecTexture); }
			if (GUI::Int("Torso 2", SetPedTexture_TorsoSec, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, 0); }
			if (GUI::Int("Torso 2 Texture", SetPedTexture_TorsoSecTexture, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, SetPedTexture_TorsoSecTexture); }
			if (GUI::Int("Textures", SetPedTexture_Textures, 0, 255, 1, false, "")) { GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 10, SetPedTexture_Textures, 0); }
			if (GUI::Int("Textures Texture", SetPedTexture_TexturesTexture, 0, 255, 1, false, "")) {  GameFunctions::SetPedTexture(GameFunctions::PlayerPedID, 9, SetPedTexture_Textures, SetPedTexture_TexturesTexture); }
		}
		break;
		case outfitsmenu:
		{
			GUI::Title("Outfits");
			if (GUI::Option("Random Outfit", "Get random outfit")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(GameFunctions::PlayerPedID, true); }
			if (GUI::Option("Police Uniform", "Get police uniform"))
			{
				PED::SET_PED_PROP_INDEX(GameFunctions::PlayerPedID, 0, 45, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 11, 48, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 4, 34, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 3, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 6, 25, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(GameFunctions::PlayerPedID, 8, 35, 0, 0);			
			}
			if (GUI::Option("Default Variation", "Get default pedmodel variation")) 
			{
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(GameFunctions::PlayerPedID);
			}
			if (GUI::Option("Random Variation", "Get random pedmodel variation"))
			{
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(GameFunctions::PlayerPedID, true);
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

		}
		break; 
		case SelectedPlayerAttachmentOptions:
		{
			GUI::Title("Attachments");
			if (GUI::Option("Plate", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "p_oil_slick_01"); }
			if (GUI::Option("EMP", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "hei_prop_heist_emp"); }
			if (GUI::Option("Beach Fire", ""))		{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_beach_fire"); }
			if (GUI::Option("Orange Ball", ""))		{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_juicestand"); }
			if (GUI::Option("Weed", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_weed_01"); }
			if (GUI::Option("Safe", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "p_v_43_safe_s"); }
			if (GUI::Option("UFO", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "p_spinning_anus_s"); }
			if (GUI::Option("Toilet", ""))			{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_ld_toilet_01"); }
			if (GUI::Option("Christmas Tree", ""))	{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_xmas_tree_int"); }
			if (GUI::Option("Windmill", ""))			{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_windmill_01"); }
			if (GUI::Option("Radar", ""))				{ GameFunctions::AttachObjectToPed(CheatFeatures::selectedPlayer, "prop_air_bigradar"); }

			if (GUI::Option("Detach All Objects", "Only detaches above attached objects")) 
			{
				const std::vector<std::string> ObjectsToRemoveArray = { 
					"p_oil_slick_01",  "hei_prop_heist_emp", "prop_beach_fire",  "prop_juicestand",
					"prop_weed_01",  "p_v_43_safe_s",  "p_spinning_anus_s",  "prop_ld_toilet_01",
					"prop_xmas_tree_int",  "prop_windmill_01",  "prop_air_bigradar"
				};
				for (auto const& i : ObjectsToRemoveArray) 
				{ 
					GameFunctions::DetachObjectFromPed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CheatFeatures::selectedPlayer), CheatFunctions::StringToChar(i));
				}			
				GameFunctions::MinimapNotification("Objects Detached & Removed");
			}
		}
		break;
		case protections:
		{
			GUI::Title("Protections");	
			if (GUI::Option("Enable/Disable Anti-Crash Camera", "Changes camera position to prevent crash")) { GameFunctions::EnableDisableAntiCrashCamera(); }
			GUI::Break("Protection", true);
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
			GUI::Toggle("Remote Events -> Block All", CheatFeatures::BlockAllScriptEvents, "Join GTAO before enabling", false);
			GUI::Toggle("Vote Kick", CheatFeatures::ProtectionVoteKickBool, "");
			GUI::Toggle("Freeze", CheatFeatures::ProtectionFreezeBool, "");
			GUI::Toggle("Give/Remove Weapons", CheatFeatures::ProtectionGiveRemoveWeaponsBool, "");
			GUI::Toggle("Alter Wanted Level", CheatFeatures::ProtectionAlterWantedLevelBool, "");
			GUI::Toggle("World Events", CheatFeatures::ProtectionWorldEventsBool, "Fire, explosions and more");
			GUI::Toggle("Vehicle", CheatFeatures::ProtectionVehicleBool, "Control & Explosions");
		}
		break; 
		case AnimationsAndScenariosMenu:
		{
			GUI::Title("Animations & Scenarios");
			if (GUI::Option("Stop Scenarios & Animations", "")) { GameFunctions::ClearAllAnimations(); }
			GUI::Break("Animations", true);
			if (GUI::Option("Sex Receiver", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("rcmpaparazzo_2", "shag_loop_poppy");
			}
			if (GUI::Option("Sex Giver", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("rcmpaparazzo_2", "shag_loop_a");
			}
			if (GUI::Option("Stripper Dance", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1");
			}
			if (GUI::Option("Pole Dance", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
			}
			if (GUI::Option("Push Ups", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("amb@world_human_push_ups@male@base", "base");
			}
			if (GUI::Option("Sit Ups", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("amb@world_human_sit_ups@male@base", "base");
			}
			if (GUI::Option("Celebrate", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("rcmfanatic1celebrate", "celebrate");
			}
			if (GUI::Option("Electrocution", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("ragdoll@human", "electrocute");
			}
			if (GUI::Option("Suicide", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("mp_suicide", "pistol");
			}
			if (GUI::Option("Showering", ""))
			{
				GameFunctions::ClearAllAnimations();
				GameFunctions::DoLocalPedAnimation("mp_safehouseshower@male@", "male_shower_idle_b");
			}
			GUI::Break("Scenarios", true);
			if (GUI::Option("Paparizzi", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_PAPARAZZI", 0, true);
			}
			if (GUI::Option("Drug Dealer", ""))
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true);
			}
			if (GUI::Option("Drinking Coffee", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_AA_COFFEE", 0, true);
			}
			if (GUI::Option("Playing Instruments", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_MUSICIAN", 0, true);
			}
			if (GUI::Option("Flexing", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_MUSCLE_FLEX", 0, true);
			}
			if (GUI::Option("Jogging", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_JOG_STANDING", 0, true);
			}
			if (GUI::Option("Binoculars", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_BINOCULARS", 0, true);
			}
			if (GUI::Option("Clipboard", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_CLIPBOARD", 0, true);
			}
			if (GUI::Option("Bench Press", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true);
			}
			if (GUI::Option("Chin Ups", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true);
			}
			if (GUI::Option("BBQ", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "PROP_HUMAN_BBQ", 0, true);
			}
			if (GUI::Option("Superhero", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_SUPERHERO", 0, true);
			}
			if (GUI::Option("Fishing", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_STAND_FISHING", 0, true);
			}
			if (GUI::Option("Security", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true);
			}
			if (GUI::Option("Leaf Blower", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true);
			}
			if (GUI::Option("Film Shocking", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
			}
			if (GUI::Option("Idle Cop", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_COP_IDLES", 0, true);
			}
			if (GUI::Option("Drinking", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_DRINKING", 0, true);
			}
			if (GUI::Option("Golf Player", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_GOLF_PLAYER", 0, true);
			}
			if (GUI::Option("Welding", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_WELDING", 0, true);
			}
			if (GUI::Option("Smoking Pot", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_SMOKING_POT", 0, true);
			}
			if (GUI::Option("Hammering", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_HAMMERING", 0, true);
			}
			if (GUI::Option("Tennis", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_TENNIS_PLAYER", 0, true);
			}
			if (GUI::Option("Drilling", "")) 
			{
				GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(GameFunctions::PlayerPedID, "WORLD_HUMAN_CONST_DRILL", 0, true);
			}
		}
		break; 
		case SettingsMenu:
		{
			GUI::Title("Settings");
			GUI::MenuOption("GUI", guisettings);
			GUI::MenuOption("Hide Elements", HideElementsMenu);
			GUI::MenuOption("Cheat", CheatSettingsMenu);
			if (GUI::Option("Visit Github Page", ""))
			{
				system("start https://github.com/HatchesPls/GrandTheftAutoV-Cheat");
			}
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
		case CheatSettingsMenu:
		{
			GUI::Title("Cheat");
			GUI::Break("Speed", true);
			GUI::Toggle("Use KM/H", CheatFeatures::UseKMH, "If disabled MP/H is used");
			GUI::Break("Protection", true);
			GUI::Toggle("Blocked Script Notifications", CheatFeatures::ShowBlockedScriptEventNotifications, "");
		}
		break;
		case guisettings:
		{
			GUI::Title("GUI");
			GUI::MenuOption("Theme Loader", ThemeLoaderMenu);
			GUI::Break("General", true);
			GUI::MenuOption("Visuals", GUIVisualsMenu);
			GUI::MenuOption("Header", headeroptionsmenu);
			GUI::Int("Max Visible Menu Options", GUI::maxVisOptions, 5, 16, 1, false);
			GUI::Toggle("Restore To Previous Submenu", GUI::RestorePreviousSubmenu, "When opening restores previous submenu", false);
			GUI::Float("X-Axis", GUI::guiX, 0.11f, 0.86f, 0.01f, true, false, "");
			GUI::Float("Y-Axis", GUI::guiY, 0.10f, 0.90f, 0.01f, true, false, "");
			std::string OpenKeyString = "Open Key: ~c~" + CheatFunctions::VirtualKeyCodeToString(GUI::OpenGUIKey);
			if (GUI::Option(OpenKeyString.c_str(), "Select to change"))
			{
				int PressedKey = CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0) { GUI::OpenGUIKey = PressedKey; GameFunctions::MinimapNotification("Open Key has been set"); }
			}
			std::string GUINavigationKeyString = "Cursor Navigation: ~c~" + CheatFunctions::VirtualKeyCodeToString(GUI::GUINavigationKey);
			if (GUI::Option(GUINavigationKeyString.c_str(), "Select to change"))
			{
				int PressedKey = CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0) { GUI::GUINavigationKey = PressedKey; GameFunctions::MinimapNotification("Cursor Navigation Key has been set"); }
			}
			GUI::Int("Key Press Delay", GUI::keyPressDelay, 1, 250, 1, false);
			if (GUI::Option("Reset Position", ""))
			{
				GUI::guiX = GUI::guiX_Default;
				GUI::guiY = GUI::guiY_Default;
			}
			GUI::Break("Player Information Box", true);
			if (GUI::Option("Reset Position", ""))
			{
				GUI::SelectableInfoBoxX = GUI::SelectableInfoBoxX_Default;
				GUI::SelectableInfoBoxY = GUI::SelectableInfoBoxY_Default;
			}
		}
		break; 
		case headeroptionsmenu:
		{
			GUI::Title("Header");
			GUI::Toggle("Show Header GUI", GUI::ShowHeaderGUI, "Toggle Header GUI", false);
			GUI::Toggle("Show Header Background", GUI::ShowHeaderBackground, "Toggle Header Background", false);
		}
		break;
		case GUIVisualsMenu:
		{
			GUI::Title("Visuals");
			GUI::Break("Colors - [PENDING REWORK]", true);
			GUI::MenuOption("Title Background", GUITitleBackgroundColorMenu);
			GUI::MenuOption("Header Background", settingsheaderbackground);
			GUI::MenuOption("Menu Background", settingsmenubackground);
			GUI::MenuOption("Menu Bottom Background", settingsmenubottombackground);
			GUI::MenuOption("Small Title Background", settingssmalltitlebackground);
			GUI::MenuOption("Options Scroller", settingsscroller);
			GUI::MenuOption("Option Text", settingsoptiontext);
			GUI::Break("Font - WIP", true);
			//GUI::StringVector("Font", { "Chalet London", "House Script", "Monospace", "WingDings", "Chalet Comprime Cologne", "Pricedown" }, CheatFeatures::SpeedometerVectorPosition, "");
		}
		break;
		case settingsmenubottombackground:
		{
			GUI::Title("Menu Bottom Background");
			if (GUI::Option("Set Default", ""))
			{
				GUI::MenuBottomRect.r = 0;
				GUI::MenuBottomRect.g = 0;
				GUI::MenuBottomRect.b = 0;
				GUI::MenuBottomRect.a = 255;
			}		
			GUI::Int("Red", GUI::MenuBottomRect.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::MenuBottomRect.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::MenuBottomRect.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::MenuBottomRect.a, 0, 255, 1, false);
		}
		break;
		case settingsmenubackground:
		{
			GUI::Title("Menu Background");
			if (GUI::Option("Set Default", ""))
			{
				GUI::MenuBackgroundRect.r = 0;
				GUI::MenuBackgroundRect.g = 0;
				GUI::MenuBackgroundRect.b = 0;
				GUI::MenuBackgroundRect.a = 220;
			}
			GUI::Int("Red", GUI::MenuBackgroundRect.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::MenuBackgroundRect.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::MenuBackgroundRect.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::MenuBackgroundRect.a, 0, 255, 1, false);
		}
		break;
		case settingssmalltitlebackground:
		{
			GUI::Title("Small Title Background");
			if (GUI::Option("Set Default", ""))
			{
				GUI::titleRect.r = 0;
				GUI::titleRect.g = 0;
				GUI::titleRect.b = 255;
				GUI::titleRect.a = 255;
			}
			GUI::Int("Red", GUI::titleRect.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::titleRect.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::titleRect.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::titleRect.a, 0, 255, 1, false);
		}
		break;
		case settingsheaderbackground:
		{
			GUI::Title("Header Background");
			if (GUI::Option("Set Default", ""))
			{
				GUI::headerRect.r = 0;
				GUI::headerRect.g = 0;
				GUI::headerRect.b = 255;
				GUI::headerRect.a = 200;
			}
			GUI::Int("Red", GUI::headerRect.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::headerRect.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::headerRect.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::headerRect.a, 0, 255, 1, false);
		}
		break;
		case ThemeLoaderMenu:
		{
			GUI::Title("Theme Loader");
			GUI::MenuOption("Theme Files", ThemeFilesMenu);
			if (!GUI::CurrentTheme.empty())
			{
				GUI::Break("Active Theme: ~c~" + GUI::CurrentTheme, false);
				if (GUI::Option("Save To Current Theme", ""))
				{
					GUI::SaveTheme(GUI::CurrentTheme);
				}
				if (GUI::Option("Delete Current Theme", "Delete active theme"))
				{
					GUI::DeleteCurrentTheme();
				}
			}
			else
			{
				GUI::Break("Active Theme: ~c~None", false);
			}
			if (GUI::Option("Save To New", "Save current GUI to new theme file"))
			{
				char* NewThemeFileName = GameFunctions::DisplayKeyboardAndReturnInput(20, "Enter Theme Name");
				if (NewThemeFileName == "0") { break; }
				GUI::SaveTheme(NewThemeFileName);
			}
		}
		break;
		case ThemeFilesMenu:
		{
			GUI::Title("Theme Files");
			if (!GUI::ThemeFilesVector.empty())
			{
				for (auto const& i : GUI::ThemeFilesVector)
				{
					if (GUI::Option(i, ""))
					{
						std::string ThemeFilePathMenuList = CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + i + ".ini";
						if (!CheatFunctions::FileOrDirectoryExists(ThemeFilePathMenuList)) { GameFunctions::MinimapNotification("~r~Unable to locate theme file"); break; }
						GUI::LoadTheme(CheatFunctions::StringToChar(i), false);
					}
				}
			}
			else
			{
				GUI::Break("No Theme Files Available", false);
			}
		}
		break;
		case GUITitleBackgroundColorMenu:
		{
			GUI::Title("Title Background");
			if (GUI::Option("Set Default", ""))
			{
				GUI::MainTitleRect.r = 0;
				GUI::MainTitleRect.g = 0;
				GUI::MainTitleRect.b = 0;
				GUI::MainTitleRect.a = 255;
			}
			GUI::Int("Red", GUI::MainTitleRect.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::MainTitleRect.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::MainTitleRect.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::MainTitleRect.a, 0, 255, 1, false);
		}
		break;
		case settingsoptiontext:
		{
			GUI::Title("Option Text");
			if (GUI::Option("Set Default", ""))
			{
				GUI::optionText.r = 255;
				GUI::optionText.g = 255;
				GUI::optionText.b = 255;
				GUI::optionText.a = 255;
			}
			GUI::Int("Red", GUI::optionText.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::optionText.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::optionText.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::optionText.a, 0, 255, 1, false);
		}
		break;
		case settingsscroller:
		{
			GUI::Title("Options Scroller");
			if (GUI::Option("Set Default", ""))
			{
				GUI::scroller.r = 0;
				GUI::scroller.g = 0;
				GUI::scroller.b = 255;
				GUI::scroller.a = 255;
			}
			GUI::Int("Red", GUI::scroller.r, 0, 255, 1, false);
			GUI::Int("Green", GUI::scroller.g, 0, 255, 1, false);
			GUI::Int("Blue", GUI::scroller.b, 0, 255, 1, false);
			GUI::Int("Opacity", GUI::scroller.a, 0, 255, 1, false);
		}
		break;
		}
		GUI::End();
		GameHooking::PauseMainFiber(0, false);
	}
}

DWORD WINAPI InitThread(LPVOID lpParam)
{
	Cheat::CheatFunctions::CreateConsole();
	Cheat::LogFunctions::Init();
	GameHooking::DoGameHooking();
	//Hooks created - this thread is no longer needed
	return 0;
}

HMODULE Cheat::CheatModuleHandle;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		Cheat::CheatModuleHandle = hModule;
		//Create 'gtav' directory
		std::string GtavDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(GtavDirectoryPath)) { Cheat::CheatFunctions::CreateNewDirectory(GtavDirectoryPath); }
		//Create 'Logs' directory
		std::string LogsDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(LogsDirectoryPath)) { Cheat::CheatFunctions::CreateNewDirectory(LogsDirectoryPath); }
		//Continue cheat loading
		CreateThread(NULL, NULL, InitThread, hModule, NULL, NULL);
		break;
	}
	return TRUE;
}