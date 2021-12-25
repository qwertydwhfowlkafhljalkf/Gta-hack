#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::AllPlayers()
{
	GUI::Title("All Players");
	GUI::MenuOption("Exclusions", AllPlayersExclusions);
	GUI::Break("Friendly", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Give All Weapons", "Give all players all weapons"))
	{
		for (int i = 0; i < 32; i++)
		{
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

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
			bool ExcludeSelf = GameFunctions::PlayerID == i && CheatFeatures::AllPlayersExclusionsSelf;
			bool ExcludeFriend = GameFunctions::IsPlayerFriend(i) && CheatFeatures::AllPlayersExclusionsFriends;
			bool ExcludeHost = GameFunctions::PlayerIsFreemodeScriptHost(i) && CheatFeatures::AllPlayersExclusionsHost;

			if (!ExcludeHost && !ExcludeFriend && !ExcludeSelf && GameFunctions::IsPlayerIDValid(i))
			{
				NETWORK::NETWORK_SESSION_KICK_PLAYER(i);
			}
		}
	}
}