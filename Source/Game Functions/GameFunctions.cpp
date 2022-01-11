#include "../Header/Cheat Functions/FiberMain.h"
Player Cheat::GameFunctions::PlayerID;
Ped Cheat::GameFunctions::PlayerPedID;

void Cheat::GameFunctions::GiveAllWeaponsToPlayer(Ped Player)
{
	for (auto const& i : GameArrays::WeaponsHashList)
	{
		WEAPON::GIVE_WEAPON_TO_PED(Player, i.WeaponHash, 9999, false, false);
	}
}

void Cheat::GameFunctions::RepairAndCleanVehicle(Vehicle vehicle)
{
	ENTITY::SET_ENTITY_HEALTH(vehicle, ENTITY::GET_ENTITY_MAX_HEALTH(vehicle));
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f);
	VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
	VEHICLE::SET_VEHICLE_FIXED(vehicle);
	VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, true, true, false);
	Cheat::GameFunctions::AdvancedMinimapNotification("Vehicle Repaired & Cleaned", "Textures", "AdvancedNotificationImage", false, 4, "Los Santos Customs", "", 1.0, "");
}

void Cheat::GameFunctions::SetPedTexture(Ped Ped, int ComponentID, int DrawableID, int TextureID)
{ 
	PED::SET_PED_COMPONENT_VARIATION(Ped, ComponentID, DrawableID, TextureID, 0);
}

void Cheat::GameFunctions::TeleportToBlipCoord(Blip TargetBlip)
{
	if (TargetBlip == SpriteWaypoint && !UI::IS_WAYPOINT_ACTIVE())
	{
		Cheat::GameFunctions::MinimapNotification("~r~No Waypoint has been set"); 
		return;
	}

	Blip BlipHandle = UI::GET_FIRST_BLIP_INFO_ID(TargetBlip);
	if (UI::DOES_BLIP_EXIST(BlipHandle))
	{
		GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, UI::GET_BLIP_INFO_ID_COORD(BlipHandle), true, false);
		return;
	}
	GameFunctions::MinimapNotification("~r~Target Blip does not exist");
}

void Cheat::GameFunctions::TeleportToObjective()
{
	Vector3 wayp{};
	Ped e = Cheat::GameFunctions::PlayerPedID;
	bool blipFound = false;
	for (int i = 0; i <= 1000; i++)
	{
		int blipIterator = UI::IS_WAYPOINT_ACTIVE() ? UI::_GET_BLIP_INFO_ID_ITERATOR() : SpriteStandard;    
		for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator);
			UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator)) {
			if (UI::GET_BLIP_INFO_ID_TYPE(i) == ColorPlayer && UI::GET_BLIP_COLOUR(i) == ColorYellow && UI::GET_BLIP_COLOUR(i) != ColorBlue && UI::IS_BLIP_ON_MINIMAP(i) == ColorRed)
			{
				wayp = UI::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				Cheat::GameFunctions::TeleportToCoords(e, wayp, false, false);
			}
			GameFunctions::TeleportToCoords(e, wayp, true, false);
		}
		break;
	}
	if (!blipFound) 
	{
		Blip i = UI::GET_FIRST_BLIP_INFO_ID(SpriteRaceFinish);
		if (UI::DOES_BLIP_EXIST(i)) 
		{
			wayp = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
		}
	}
	blipFound ? Cheat::GameFunctions::TeleportToCoords(e, wayp, false, false) : Cheat::GameFunctions::MinimapNotification("~r~Objective not found");
}

void Cheat::GameFunctions::BurstSelectedPlayerTires(Ped selectedPed)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, false))
	{
		RequestNetworkControlOfEntity(PED::GET_VEHICLE_PED_IS_USING(selectedPed));
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_USING(selectedPed), true);
		static int tireID = 0;
		for (tireID = 0; tireID < 8; tireID++)
		{
			VEHICLE::SET_VEHICLE_TYRE_BURST(PED::GET_VEHICLE_PED_IS_USING(selectedPed), tireID, true, 1000.0);
		}
	}
}

void Cheat::GameFunctions::SetOffAlarmPlayerVehicle(Ped selectedPed)
{
	Entity selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
	RequestNetworkControlOfEntity(PED::GET_VEHICLE_PED_IS_USING(selectedPed));
	VEHICLE::SET_VEHICLE_ALARM(selectedVehicle, true);
	VEHICLE::START_VEHICLE_ALARM(selectedVehicle);
	Cheat::GameFunctions::MinimapNotification("~g~Set off alarm of vehicle!");
}

bool Cheat::GameFunctions::IsPlayerFriend(Player player)
{
	int handle[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		if (NETWORK::NETWORK_IS_FRIEND(&handle[0]))
		{
			return true;
		}
	}
	return false;
}

Vector3 Cheat::GameFunctions::MultiplyVector(Vector3 vector, float inc) 
{
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}

Vector3 Cheat::GameFunctions::AddVector(Vector3 vector, Vector3 vector2) 
{
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}

void Cheat::GameFunctions::SetRankRockstarGift(int Rank)
{
	if (Rank > 0 && Rank <= 8000)
	{ 
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ReturnCurrentGTAOCharacter() + "_CHAR_SET_RP_GIFT_ADMIN")), ReturnReputationPointsAmount(Rank), true);
		MinimapNotification("Join a new GTAO session for the new Rank to be applied");
	}
	else
	{
		MinimapNotification("Invalid Rank Inputted");
	}
}

int Cheat::GameFunctions::ReturnReputationPointsAmount(int Level)
{
	return globalHandle(GLOBAL_LEVEL_TO_RP).At(1, Level).As<int>();
}

Vector3 Cheat::GameFunctions::RotationToDirection(Vector3* rot)
{
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}

Vector3 Cheat::GameFunctions::AddTwoVectors(Vector3* vectorA, Vector3* vectorB) 
{
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}

Vector3 Cheat::GameFunctions::MultiplyVector(Vector3* vector, float x) 
{
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

float Cheat::GameFunctions::GetDistanceBetweenTwoVectors(Vector3* pointA, Vector3* pointB) 
{
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return (float)sqrt(sum_2 + z_ba);
}

void Cheat::GameFunctions::SubtitleNotification(char* Message, int ShowDuration)
{
	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
	UI::END_TEXT_COMMAND_PRINT(ShowDuration, true);
}

float Cheat::GameFunctions::DegreesToRadians(float degs)
{
	return degs * 3.141592653589793f / 180.f;
}

Vector3 Cheat::GameFunctions::GetEntityCoords(Entity entity) 
{
	return ENTITY::GET_ENTITY_COORDS(entity, false);
}

float Cheat::GameFunctions::GetDistanceBetweenTwoPoints(Vector3 A, Vector3 B) 
{
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
}

int Cheat::GameFunctions::ReturnRandomInteger(int start, int end) 
{
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}

void Cheat::GameFunctions::TeleportToCoords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight, bool IgnoreCurrentPedVehicle)
{
	Entity TargetEntity = e;

	if (ENTITY::IS_ENTITY_A_PED(TargetEntity))
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(TargetEntity, false) && !IgnoreCurrentPedVehicle)
		{ 
			TargetEntity = PED::GET_VEHICLE_PED_IS_USING(TargetEntity);
		}
	}
	if (ENTITY::IS_AN_ENTITY(TargetEntity))
	{
		GameFunctions::RequestNetworkControlOfEntity(TargetEntity);
	}

	if (!AutoCorrectGroundHeight)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
	}
	else
	{
		bool GroundFound = false;
		static std::array<float, 21> GroundCheckHeight = { 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.00 };

		for (const float& CurrentHeight : GroundCheckHeight)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, CurrentHeight, false, false, true);
			GameHooking::PauseMainFiber(50, false);
			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, CurrentHeight, &coords.z, false))
			{
				GroundFound = true;
				coords.z += 3.0f;
				break;
			}
		}

		if (!GroundFound)
		{ 
			Vector3 ClosestRoadCoord;
			if (PATHFIND::GET_CLOSEST_ROAD(coords.x, coords.y, coords.z, 1.0f, 1, 
										   &ClosestRoadCoord, &ClosestRoadCoord, NULL, NULL, NULL, NULL))
			{
				coords = ClosestRoadCoord;
			}
			GameFunctions::SubtitleNotification("~r~Ground not found, teleporting to nearby road", 4000);
		}
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
	}
}

void Cheat::GameFunctions::GetCameraDirection(float* dirX, float* dirY, float* dirZ)
{
	float tX, tZ, num;
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);

	tZ = rot.z * 0.0174532924f;
	tX = rot.x * 0.0174532924f;
	num = abs(cos(tX));

	*dirX = (-sin(tZ)) * num;
	*dirY = (cos(tZ)) * num;
	*dirZ = sin(tX);
}

void Cheat::GameFunctions::RequestNetworkControlOfEntity(Entity entity)
{
	int EntityTick = 0;
	int IdTick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && EntityTick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		EntityTick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netID) && IdTick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netID);
			IdTick++;
		}
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, true);
	}
}

void Cheat::GameFunctions::ClonePed(Ped ped)
{
	if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped))
	{
		PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), true, true);
	}
}

void Cheat::GameFunctions::MinimapNotification(char* Message)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
	UI::_DRAW_NOTIFICATION(false, false);
}

void Cheat::GameFunctions::AdvancedMinimapNotification(char* Message, char* PicName1, char* PicName2, bool Flash, int IconType, char* Sender, char* Subject, float Duration, char* ClanTag)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
	UI::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(PicName1, PicName2, Flash, IconType, Sender, Subject, Duration, ClanTag);
	UI::_DRAW_NOTIFICATION(false, false);
}

std::string Cheat::GameFunctions::InGameKeyboardWindowTitle;
char* Cheat::GameFunctions::DisplayKeyboardAndReturnInput(int MaxInput, std::string Title)
{
	InGameKeyboardWindowTitle = Title;
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", "", "", "", "", MaxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) { GameHooking::PauseMainFiber(0, false); }
	InGameKeyboardWindowTitle.clear();
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "0";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

int Cheat::GameFunctions::DisplayKeyboardAndReturnInputInteger(int MaxInput, std::string Title)
{	
	return CheatFunctions::StringToInt(DisplayKeyboardAndReturnInput(MaxInput, Title));
}

void Cheat::GameFunctions::StopAllPedAnimations(Ped TargetPed)
{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(TargetPed);
}

void Cheat::GameFunctions::ClearNearbyPedAnimations()
{
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Ped* peds = new Ped[ArrSize];
	peds[0] = ElementAmount;

	int PedFound = PED::GET_PED_NEARBY_PEDS(PlayerPedID, peds, -1);

	for (int i = 0; i < PedFound; i++)
	{
		int OffsetID = i * 2 + 2;
		Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
		if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PlayerPedID != peds[OffsetID])
		{
			StopAllPedAnimations(peds[OffsetID]);
		}
	}
}

void Cheat::GameFunctions::PlayPedAnimation(Ped TargetPed, char* AnimationName, char* AnimationID, bool Controllable)
{
	Cheat::GameFunctions::RequestNetworkControlOfEntity(TargetPed);
	while (!STREAMING::HAS_ANIM_DICT_LOADED((AnimationName))) { STREAMING::REQUEST_ANIM_DICT(AnimationName); GameHooking::PauseMainFiber(0, false); }
	int Flags = 0;
	if (Controllable) { Flags = ANIM_FLAG_UPPERBODY | ANIM_FLAG_ENABLE_PLAYER_CONTROL | ANIM_FLAG_STOP_LAST_FRAME;  }
	AI::TASK_PLAY_ANIM(TargetPed, AnimationName, AnimationID, 8.0f, 0.0f, -1, Flags, 0, false, false, false);
}

void Cheat::GameFunctions::DoNearbyPedsAnimation(char* AnimationName, char* AnimationID)
{
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Ped* peds = new Ped[ArrSize];
	peds[0] = ElementAmount;

	int PedFound = PED::GET_PED_NEARBY_PEDS(Cheat::GameFunctions::PlayerPedID, peds, -1);

	for (int i = 0; i < PedFound; i++)
	{
		int OffsetID = i * 2 + 2;
		Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
		if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && Cheat::GameFunctions::PlayerPedID != peds[OffsetID])
		{
			Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
			STREAMING::REQUEST_ANIM_DICT(AnimationName);
			if (STREAMING::HAS_ANIM_DICT_LOADED((AnimationName)))
			{
				AI::TASK_PLAY_ANIM(peds[OffsetID], AnimationName, AnimationID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			}
		}
	}
}

void Cheat::GameFunctions::PlayScenarioNearbyPeds(char* Scenario)
{
	const int ElementAmount = 10;
	const int ArrSize = ElementAmount * 2 + 2;

	Ped* peds = new Ped[ArrSize];
	peds[0] = ElementAmount;

	int PedFound = PED::GET_PED_NEARBY_PEDS(Cheat::GameFunctions::PlayerPedID, peds, -1);

	for (int i = 0; i < PedFound; i++)
	{
		int OffsetID = i * 2 + 2;
		Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
		if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && Cheat::GameFunctions::PlayerPedID != peds[OffsetID])
		{
			StopAllPedAnimations(peds[OffsetID]);
			AI::TASK_START_SCENARIO_IN_PLACE(peds[OffsetID], Scenario, 0, true);
		}
	}
}

void Cheat::GameFunctions::ShowPlayerInformationBox(Player PlayerID)
{
	if (!Cheat::CheatFeatures::HidePlayerInformationBox)
	{
		//Definitions
		Ped SelectedPlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PlayerID);
		RequestNetworkControlOfEntity(SelectedPlayerPed);

		//Draw Player Marker
		if (CheatFeatures::PlayerListMarkerPosition == 0 || CheatFeatures::PlayerListMarkerPosition == 1 && GUI::currentMenu == GUI::Submenus::AllPlayers)
		{
			Vector3 coords = GetEntityCoords(SelectedPlayerPed);
			GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords.x, coords.y, coords.z + 2.f, 255, 255, 255, 5.f, 10.f);
		}

		//Draw Title and Background
		if (Cheat::GUI::guiX < 0.54f)
		{
			GUI::DrawRectInGame(GUI::PrimaryColor, { Cheat::GUI::guiX + 0.266f, GUI::guiY + 0.014f }, { 0.32f, 0.31f }); //Main Background Rect
			GUI::DrawTextInGame("Player Information", { GUI::TextColorAndFont }, { Cheat::GUI::guiX + 0.260f, GUI::guiY - 0.170f }, { 0.50f, 0.37f }, true);
			GUI::DrawRectInGame({ 0, 0, 0, 210 }, { Cheat::GUI::guiX + 0.266f, GUI::guiY - 0.156f }, { 0.32f, 0.030f });
		}
		else
		{
			GUI::DrawRectInGame(GUI::PrimaryColor, { Cheat::GUI::guiX - 0.266f, GUI::guiY + 0.014f }, { 0.32f, 0.31f }); //Main Background Rect
			GUI::DrawTextInGame("Player Information", { GUI::TextColorAndFont }, { Cheat::GUI::guiX - 0.260f, GUI::guiY - 0.170f }, { 0.50f, 0.37f }, true);
			GUI::DrawRectInGame({ 0, 0, 0, 210 }, { Cheat::GUI::guiX - 0.266f,GUI::guiY - 0.156f }, { 0.32f, 0.030f });
		}

		//Draw World Map
		//GUI::DrawSpriterInGame("mp_freemode_mc", "debugmap", 0.60f, 0.50f, 0.15f, 0.4f, 0, 255, 255, 255, 255);

		//Text Entry's
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Name", 1);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(PLAYER::GET_PLAYER_NAME(PlayerID), NULL, 1);

		Cheat::GUI::AddPlayerInfoBoxTextEntry("Rank", 2);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Money", 3);
		if (NETWORK::NETWORK_IS_SESSION_STARTED()) 
		{
			std::ostringstream PlayerRank;
			PlayerRank << globalHandle(1853128 + 1).At(PlayerID, 874).At(205).At(5).As<int>();
			Cheat::GUI::AddPlayerInfoBoxTextEntry(PlayerRank.str(), NULL, 2);

			std::ostringstream PlayerMoney;
			PlayerMoney << "$" << globalHandle(1853128 + 1).At(PlayerID, 874).At(205).At(56).As<__int64>();
			Cheat::GUI::AddPlayerInfoBoxTextEntry(PlayerMoney.str(), NULL, 3);
		}
		else
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Unavailable", NULL, 2);
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Unavailable", NULL, 3);
		}

		//Health
		std::ostringstream Health;
		float health = ENTITY::GET_ENTITY_HEALTH(SelectedPlayerPed);
		float HealthValue = health * 100 / ENTITY::GET_ENTITY_MAX_HEALTH(SelectedPlayerPed);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Health", 4);
		if (HealthValue == 100) 
		{ 
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Full", NULL, 4);
		}
		else 
		{ 
			Health << HealthValue << "%";
			Cheat::GUI::AddPlayerInfoBoxTextEntry(Health.str(), NULL, 4);
		}
		
		//Armor
		std::ostringstream Armor;
		int ArmorValue = PED::GET_PED_ARMOUR(SelectedPlayerPed) * 100 / PLAYER::GET_PLAYER_MAX_ARMOUR(PlayerID);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Armor", 5);
		if (ArmorValue == 99 || ArmorValue == 100) 
		{ 		
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Full", NULL, 5);
		}
		else 
		{ 
			Armor << ArmorValue; 
			Cheat::GUI::AddPlayerInfoBoxTextEntry(Armor.str(), NULL, 5);
		}

		//Status
		std::ostringstream Status;
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Status", 6);
		if (AI::IS_PED_STILL(SelectedPlayerPed)) { Status << "Player is still"; }
		else if (AI::IS_PED_WALKING(SelectedPlayerPed)) { Status << "Player is walking"; }
		else if (AI::IS_PED_RUNNING(SelectedPlayerPed)) { Status << "Player is running"; }
		else if (AI::IS_PED_SPRINTING(SelectedPlayerPed)) { Status << "Player is sprinting"; }
		else if (PED::IS_PED_CLIMBING(SelectedPlayerPed)) { Status << "Player is climbing"; }
		else if (PED::IS_PED_DIVING(SelectedPlayerPed)) { Status << "Player is diving"; }
		else if (PED::IS_PED_FALLING(SelectedPlayerPed)) { Status << "Player is falling"; }
		else if (PED::IS_PED_DEAD_OR_DYING(SelectedPlayerPed, true)) { Status << "Player is dead"; }
		else { Status << "~c~Unknown"; }
		Cheat::GUI::AddPlayerInfoBoxTextEntry(Status.str(), NULL, 6);


		//Vehicle
		bool InAnyVehicle = PED::IS_PED_IN_ANY_VEHICLE(SelectedPlayerPed, 0);
		std::ostringstream Vehicle;
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Vehicle", 7);
		if (InAnyVehicle)
		{
			Vehicle << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(SelectedPlayerPed, 0))));
		}
		else
		{
			Vehicle << "~c~Not in a vehicle";
		}
		Cheat::GUI::AddPlayerInfoBoxTextEntry(Vehicle.str(), NULL, 7);


		//Speed
		std::ostringstream Speed;
		if (InAnyVehicle)
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Vehicle Speed", 8);
			float VehicleSpeed = round(ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(SelectedPlayerPed, false)) * 100) / 100;
			if (CheatFeatures::MeasurementSystemVectorPosition == 0)
			{
				Speed << MSToKMH(VehicleSpeed) << " KM/H";
			}
			else if (CheatFeatures::MeasurementSystemVectorPosition == 1)
			{
				Speed << MSToMPH(VehicleSpeed) << " MP/H";
			}
			Cheat::GUI::AddPlayerInfoBoxTextEntry(Speed.str(), NULL, 8);
		}
		else
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Movement Speed", 8);
			Speed << round(ENTITY::GET_ENTITY_SPEED(SelectedPlayerPed) * 100) / 100 << " M/S";
			Cheat::GUI::AddPlayerInfoBoxTextEntry(Speed.str(), NULL, 8);
		}


		//Wanted Level
		std::ostringstream WantedLevel;
		int PlayerWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(PlayerID);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Wanted Level", 9);
		WantedLevel << PlayerWantedLevel << "/5";
		Cheat::GUI::AddPlayerInfoBoxTextEntry(WantedLevel.str(), NULL, 9);


		Hash WeaponHash;
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Weapon", 10);
		std::string WeaponName;
		if (WEAPON::GET_CURRENT_PED_WEAPON(SelectedPlayerPed, &WeaponHash, true))
		{
			for (auto const& i : GameArrays::WeaponsHashList)
			{
				if (WeaponHash == i.WeaponHash)
				{
					WeaponName = i.WeaponName;
				}
			}
			
		}
		else
		{
			WeaponName = "Unarmed";
		}
		Cheat::GUI::AddPlayerInfoBoxTextEntry(WeaponName, NULL, 10);


		//Coords
		Vector3 SelectedPlayerPedCoords = GetEntityCoords(SelectedPlayerPed);
		std::ostringstream CoordX;
		std::ostringstream CoordY;
		std::ostringstream CoordZ;

		CoordX << SelectedPlayerPedCoords.x;
		CoordY << SelectedPlayerPedCoords.y;
		CoordZ << SelectedPlayerPedCoords.z;

		Cheat::GUI::AddPlayerInfoBoxTextEntry("X", 11);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Y", 12);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Z", 13);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(CoordX.str(), NULL, 11);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(CoordY.str(), NULL, 12);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(CoordZ.str(), NULL, 13);


		std::ostringstream Zone; 
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Zone", 14);
		Zone << UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(SelectedPlayerPedCoords.x, SelectedPlayerPedCoords.y, SelectedPlayerPedCoords.z));
		Cheat::GUI::AddPlayerInfoBoxTextEntry(Zone.str(), NULL, 14);


		Hash streetName, crossingRoad;
		PATHFIND::GET_STREET_NAME_AT_COORD(SelectedPlayerPedCoords.x, SelectedPlayerPedCoords.y, SelectedPlayerPedCoords.z, &streetName, &crossingRoad);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Street", 15);
		std::ostringstream Street; 
		Street << UI::GET_STREET_NAME_FROM_HASH_KEY(streetName);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(Street.str(), NULL, 15);

		float distance = Get3DDistance(SelectedPlayerPedCoords, GetEntityCoords(Cheat::GameFunctions::PlayerPedID));
		std::ostringstream Distance;

		if (PlayerID != GameFunctions::PlayerID)
		{
			if (distance > 1000)
			{
				distance = round((distance / 1000) * 100) / 100;
				Distance << distance << " KM";
			}
			else
			{
				distance = round(distance * 1000) / 100;
				Distance << distance << " M";
			}
		}
		else
		{
			Distance << "N/A";
		}
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Distance", NULL, NULL, 1);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(Distance.str(), NULL, NULL, NULL, 1);


		//Modded Model
		Hash SelectedPlayerPedModel = ENTITY::GET_ENTITY_MODEL(SelectedPlayerPed);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Modded Model", NULL, NULL, 2);
		if (NETWORK::NETWORK_IS_SESSION_STARTED() && SelectedPlayerPedModel != GAMEPLAY::GET_HASH_KEY("mp_m_freemode_01") && SelectedPlayerPedModel != GAMEPLAY::GET_HASH_KEY("mp_f_freemode_01"))
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 2);
		}
		else
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 2);
		}

		//Is in interior
		Cheat::GUI::AddPlayerInfoBoxTextEntry("In Interior", NULL, NULL, 3);
		if (Cheat::GameFunctions::IsEntityInInterior(SelectedPlayerPed))
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 3);
		}
		else
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 3);
		}

		//Cutscene
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Cutscene", NULL, NULL, 4);
		if (NETWORK::IS_PLAYER_IN_CUTSCENE(PlayerID))
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("Yes", NULL, NULL, NULL, 4);
		}
		else
		{
			Cheat::GUI::AddPlayerInfoBoxTextEntry("No", NULL, NULL, NULL, 4);
		}

		//Rockstar ID
		Cheat::GUI::AddPlayerInfoBoxTextEntry("Rockstar ID", NULL, NULL, 5);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(std::to_string(Cheat::GameFunctions::ReturnPlayerRockstarID(PlayerID)), NULL, NULL, NULL, 5);

		//IP Address
		std::string PlayerIPString = Cheat::GameFunctions::ReturnPlayerIPAddressAsString(PlayerID);
		Cheat::GUI::AddPlayerInfoBoxTextEntry("IP Address", NULL, NULL, 6);
		Cheat::GUI::AddPlayerInfoBoxTextEntry(PlayerIPString, NULL, NULL, NULL, 6);
	}
}

void Cheat::GameFunctions::MaxUpgradeVehicle(int VehicleHandle)
{
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PlayerPedID, false);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}
	VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, true); //Set turbo on vehicle
	VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, true); //Enable xeon headlights
}

void Cheat::GameFunctions::MaxDowngradeVehicle(int VehicleHandle)
{
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PlayerPedID, false);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
	}
	VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 18); //Remove turbo on vehicle
	VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 22); //Remove xeon headlights
}

float Cheat::GameFunctions::Get3DDistance(Vector3 a, Vector3 b)
{
	float x = pow((a.x - b.x), 2);
	float y = pow((a.y - b.y), 2);
	float z = pow((a.z - b.z), 2);
	return sqrt(x + y + z);
}

void Cheat::GameFunctions::ApplyForceToEntity(Entity e, float x, float y, float z)
{
	if (e != Cheat::GameFunctions::PlayerPedID && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == false) { RequestNetworkControlOfEntity(e); }
	ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
}

void Cheat::GameFunctions::RemoveObjectFromPed(Ped Ped, char* ObjectName)
{
	Vector3 PedCoords = GetEntityCoords(Ped);
	Object Object = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(PedCoords.x, PedCoords.y, PedCoords.z, 4.0, GAMEPLAY::GET_HASH_KEY(ObjectName), false, false, true);
	if (ENTITY::DOES_ENTITY_EXIST(Object) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(Object, Ped))
	{
		Cheat::GameFunctions::RequestNetworkControlOfEntity(Object);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Object, true, true);
		ENTITY::DELETE_ENTITY(&Object);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Object);
	}
}

void Cheat::GameFunctions::AttachObjectToPed(Ped Ped, char* ObjectName)
{
	int attachobj[100];
	int nuattach = 1;
	Vector3 pos = GetEntityCoords(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Ped));
	int hash = GAMEPLAY::GET_HASH_KEY(ObjectName);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash))
	{
		if (STREAMING::IS_MODEL_VALID(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			while (!STREAMING::HAS_MODEL_LOADED(hash)) GameHooking::PauseMainFiber(0);

			if (STREAMING::HAS_MODEL_LOADED(hash))
			{
				attachobj[nuattach] = OBJECT::CREATE_OBJECT(hash, pos.x, pos.y, pos.z, 1, 1, 1);
				if (ENTITY::DOES_ENTITY_EXIST(attachobj[nuattach]))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(attachobj[nuattach], PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Ped), 31086, 0, 0, 0, 0, 0, 0, true, false, false, false, 2, true);
					nuattach++;
					if (nuattach >= 101) { nuattach = 1; }
				}
			}
		}
	}
}

std::vector<Vehicle> Cheat::GameArrays::SpawnedVehicles;
void Cheat::GameFunctions::SpawnVehicle(char* ModelHash)
{
	Hash VehicleModel = GAMEPLAY::GET_HASH_KEY(ModelHash);
	if (STREAMING::IS_MODEL_A_VEHICLE(VehicleModel))
	{
		if (CheatFeatures::VehicleSpawnerDeleteOldVehicle)
		{
			Cheat::GameFunctions::DeleteVehicle(PED::GET_VEHICLE_PED_IS_IN(PlayerPedID, false));
		}

		while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(ModelHash)))
		{
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(ModelHash));
			GameHooking::PauseMainFiber(0);
		}

		Vector3 NewVehiclePosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PlayerPedID, 0.0f, 5.0f, 0.0f);
		if (CheatFeatures::VehicleSpawnerSpawnAirVehicleAir)
		{
			if (VEHICLE::IS_THIS_MODEL_A_PLANE(VehicleModel) || VEHICLE::IS_THIS_MODEL_A_HELI(VehicleModel))
			{
				NewVehiclePosition.z += 100.f;
			}
		}
		Vehicle NewVehicleHandle = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY(ModelHash), NewVehiclePosition.x, NewVehiclePosition.y, NewVehiclePosition.z, ENTITY::GET_ENTITY_HEADING(PlayerPedID), true, true);

		if (NewVehicleHandle != 0)
		{
			NETWORK::NETWORK_FADE_IN_ENTITY(NewVehicleHandle, true);

			if (CheatFeatures::VehicleSpawnerSpawnInsideVehicle)
			{
				PED::SET_PED_INTO_VEHICLE(PlayerPedID, NewVehicleHandle, -1);
			}
			if (CheatFeatures::VehicleSpawnerSpawnWithGodmode)
			{
				GameFunctions::ChangeEntityInvincibilityState(NewVehicleHandle, true);
			}
			if (CheatFeatures::VehicleSpawnerSpawnMaxUpgraded)
			{ 
				MaxUpgradeVehicle(NewVehicleHandle); 
			}
			if (CheatFeatures::VehicleSpawnerSpawnWithBlip)
			{ 
				AddBlipToVehicle(NewVehicleHandle);
			}
			
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(NewVehicleHandle, "Vehicle");
			VEHICLE::SET_VEHICLE_ENGINE_ON(NewVehicleHandle, true, true, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(NewVehicleHandle, false);
			VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(NewVehicleHandle, true);
			VEHICLE::SET_VEHICLE_IS_WANTED(NewVehicleHandle, false);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(NewVehicleHandle, true, true);
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NET_TO_VEH(NewVehicleHandle), true);
			DECORATOR::DECOR_SET_INT(NewVehicleHandle, "MPBitset", 0);
			ENTITY::_SET_ENTITY_SOMETHING(NewVehicleHandle, true);
			Cheat::GameFunctions::MinimapNotification("Vehicle Spawned");
			GameArrays::SpawnedVehicles.push_back(NewVehicleHandle);
		}
	}
	else
	{
		Cheat::GameFunctions::MinimapNotification("~r~That is not a valid Vehicle model");
	}
}

Cam antiCrashCam;
void Cheat::GameFunctions::EnableDisableAntiCrashCamera()
{
	if (CAM::DOES_CAM_EXIST(antiCrashCam))
	{
		CAM::SET_CAM_ACTIVE(antiCrashCam, false);
		CAM::RENDER_SCRIPT_CAMS(0, 1, 10, 0, 0);
		CAM::DESTROY_CAM(antiCrashCam, false);
		PLAYER::SET_PLAYER_CONTROL(Cheat::GameFunctions::PlayerID, true, 0);
	}
	else
	{
		antiCrashCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 9999.0f, 9999.0f, 9999.0f, 9999.0f, 9999.0f, 9999.0f, 9999.0f, true, 1);
		CAM::RENDER_SCRIPT_CAMS(1, 1, 1, 0, 0);
		CAM::SET_CAM_ACTIVE(antiCrashCam, true);
		PLAYER::SET_PLAYER_CONTROL(Cheat::GameFunctions::PlayerID, false, 0);
	}
}

std::vector<std::string> CurrentPlayerNamesSession;
std::vector<std::string> CurrentPlayerNamesSession2;
bool SecondCall = false;
void Cheat::GameFunctions::CheckNewSessionMembersLoop()
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED() && CheatFeatures::ShowJoiningPlayersNotification)
	{
		if (!SecondCall) { CurrentPlayerNamesSession.clear(); CurrentPlayerNamesSession2.clear(); }

		for (int i = 0; i < 32; ++i)
		{
			char* PlayernameString = PLAYER::GET_PLAYER_NAME(i);
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
			{
				if (!SecondCall) 
				{ 
					CurrentPlayerNamesSession.push_back(PlayernameString); 
				}
				else
				{
					CurrentPlayerNamesSession2.push_back(PlayernameString);
				}
			}
		}

		if (SecondCall)
		{
			for (const auto& var : CurrentPlayerNamesSession2)
			{
				if (!std::count(CurrentPlayerNamesSession.begin(), CurrentPlayerNamesSession.end(), var))
				{
					std::string NewPlayerString = "<C>" + var + "</C> joined the session.";
					Cheat::GameFunctions::MinimapNotification(CheatFunctions::StringToChar(NewPlayerString));
				}
			}
			SecondCall = false;
		}
		else
		{
			SecondCall = true;
		}
	}
}

bool Cheat::GameFunctions::IsEntityInInterior(Entity Entity)
{
	if (INTERIOR::GET_INTERIOR_FROM_ENTITY(Entity) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Cheat::GameFunctions::AddBlipToVehicle(Vehicle Vehicle)
{
	RequestNetworkControlOfEntity(Vehicle);
	ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Vehicle, true, true);
	for (int i = 0; i < 350; i++)NETWORK::SET_NETWORK_ID_CAN_MIGRATE(Vehicle, 0);
	VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle, true);
	int BlipHandle = UI::ADD_BLIP_FOR_ENTITY(Vehicle);
	UI::SET_BLIP_SPRITE(BlipHandle, 60);
	UI::SET_BLIP_NAME_FROM_TEXT_FILE(BlipHandle, "Vehicle");
}

bool Cheat::GameFunctions::DeleteVehicle(Vehicle Vehicle)
{
	RequestNetworkControlOfEntity(Vehicle);
	if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, false) && ENTITY::DOES_ENTITY_EXIST(Vehicle))
	{
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Vehicle, true, true);
		VEHICLE::DELETE_VEHICLE(&Vehicle);
		return true;
	}
	return false;
}

float Cheat::GameFunctions::MSToKMH(float MS)
{
	return roundf(MS * 3.6);
}

float Cheat::GameFunctions::MSToMPH(float MS)
{
	return roundf(MS * 2.2);
}

float Cheat::GameFunctions::KMHToMS(float MS)
{
	return roundf(MS * 0.27);
}

float Cheat::GameFunctions::MPHToMS(float MS)
{
	return roundf(MS * 0.44);
}

void Cheat::GameFunctions::ChangeEntityInvincibilityState(Entity EntityHandle, bool Enable)
{
	if (Enable)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(EntityHandle, true);
		ENTITY::SET_ENTITY_PROOFS(EntityHandle, false, false, false, false, false, false, false, false);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(EntityHandle, false);
		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(EntityHandle, false);
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(EntityHandle, false);
	}
	else
	{
		ENTITY::SET_ENTITY_INVINCIBLE(EntityHandle, false);
		ENTITY::SET_ENTITY_PROOFS(EntityHandle, false, false, false, false, false, false, false, false);
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(EntityHandle, true);
	}
}

char* Cheat::GameFunctions::ReturnOnlinePlayerPictureString(Player PlayerHandle)
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int Index = GLOBAL_PLAYER_PICTURE_INDEX + 2;
		for (int x = 0; x <= 150; x += 5)
		{
			int playerId = globalHandle(Index).At(x).As<int>();
			if (playerId == PlayerHandle)
			{
				int PedHeadshotHandle = globalHandle(Index).At(x).At(1).As<int>();
				if (PED::IS_PEDHEADSHOT_VALID(PedHeadshotHandle))
				{
					return PED::GET_PEDHEADSHOT_TXD_STRING(PedHeadshotHandle);
				}
			}
			if (playerId == -1)
			{
				break;
			}
		}
	}
	return "CHAR_DEFAULT";
}

VECTOR2 Cheat::GameFunctions::ReturnCursorYXCoords()
{
	return { CONTROLS::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_X), CONTROLS::GET_DISABLED_CONTROL_NORMAL(2, INPUT_CURSOR_Y) };
}

//https://github.com/MAFINS/MenyooSP/blob/v1.3.0/Solution/source/Menu/Menu.cpp
bool Cheat::GameFunctions::IsCursorAtXYPosition(VECTOR2 const& boxCentre, VECTOR2 const& boxSize)
{
	return (ReturnCursorYXCoords().x >= boxCentre.x - boxSize.x / 2 && ReturnCursorYXCoords().x <= boxCentre.x + boxSize.x / 2)
		&& (ReturnCursorYXCoords().y > boxCentre.y - boxSize.y / 2 && ReturnCursorYXCoords().y < boxCentre.y + boxSize.y / 2);
}

bool Cheat::CheatFeatures::CursorGUINavigationEnabled = false;
void Cheat::GameFunctions::EnableDisableCursorGUINavigation()
{
	if (GUI::menuLevel != 0 && !Controls::ControlsDisabled)
	{
		if (CheatFeatures::CursorGUINavigationEnabled)
		{
			CheatFeatures::CursorGUINavigationEnabled = false;
			PLAYER::SET_PLAYER_CONTROL(GameFunctions::PlayerID, true, 0);
		}
		else
		{
			CheatFeatures::CursorGUINavigationEnabled = true;
			PLAYER::SET_PLAYER_CONTROL(GameFunctions::PlayerID, false, 0);
		}
	}
}

void Cheat::GameFunctions::ChangePedModelLocalPlayer(Hash PedModel)
{
	if (STREAMING::IS_MODEL_VALID(PedModel))
	{
		while (!STREAMING::HAS_MODEL_LOADED(PedModel)) { STREAMING::REQUEST_MODEL(PedModel); GameHooking::PauseMainFiber(0); }
		PLAYER::SET_PLAYER_MODEL(PlayerID, PedModel);
		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PlayerPedID);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedModel);
	}
}

bool Cheat::GameFunctions::PlayerIsFreemodeScriptHost(Player Player)
{
	if (Player == NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", 4294967295, 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cheat::GameFunctions::CopySelectedPlayerOutfit(Player SelectedPlayer)
{
	if (SelectedPlayer != PlayerID)
	{
		Ped SelectedPlayerPedHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(SelectedPlayer);
		for (int i = 0; i < 12; i++)
		{
			PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, i, PED::GET_PED_DRAWABLE_VARIATION(SelectedPlayerPedHandle, i), PED::GET_PED_TEXTURE_VARIATION(SelectedPlayerPedHandle, i), PED::GET_PED_PALETTE_VARIATION(SelectedPlayerPedHandle, i));
			GameHooking::PauseMainFiber(0, true);
		}
	}
}

int Cheat::GameFunctions::ReturnPlayerRockstarID(Player PlayerHandle)
{
	char* RockstarIDBuffer;
	int NETWORK_HANDLE[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(PlayerHandle, &NETWORK_HANDLE[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13))
	{
		RockstarIDBuffer = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&NETWORK_HANDLE[0]);
	}
	else  { RockstarIDBuffer = "0"; }
	return CheatFunctions::StringToInt(RockstarIDBuffer);
}

std::string Cheat::GameFunctions::ReturnPlayerIPAddressAsString(Player PlayerHandle)
{
	char IPBuffer[256];
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		if (PlayerHandle == GameFunctions::PlayerID && CheatFeatures::HideOwnIPAddress) { return "Hidden"; }
		auto InfoLong	 = *reinterpret_cast<std::uintptr_t*>(GameHooking::get_player_address(PlayerHandle) + OFFSET_PLAYER_INFO);
		auto IPAddress   = reinterpret_cast<std::uint8_t*>(InfoLong + OFFSET_PLAYER_INFO_EXTERNAL_IP);
		IPAddress ? sprintf_s(IPBuffer, "%i.%i.%i.%i", IPAddress[3], IPAddress[2], IPAddress[1], IPAddress[0]) : sprintf_s(IPBuffer, "Unknown");
	}
	else
	{
		sprintf_s(IPBuffer, "Unavailable");
	}
	return IPBuffer;
}

std::string Cheat::GameFunctions::ReturnCurrentGTAOCharacter(bool NumberOnly)
{
	int CharacterID;
	STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &CharacterID, -1);
	if (NumberOnly) { return std::to_string(CharacterID); }
	return "MP" + std::to_string(CharacterID);
}

void Cheat::GameFunctions::PlayFrontendSoundDefault(char* SoundName)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, SoundName, "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
}

bool Cheat::GameFunctions::IsPlayerIDValid(Player ID)
{
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(ID)))
	{
		return true;
	}
	return false;
}

Player Cheat::GameFunctions::ReturnPlayerIDFromPlayerName(std::string PlayerName)
{
	for (int i = 0; i < 32; ++i)
	{
		if (PLAYER::GET_PLAYER_NAME(i) == PlayerName)
		{
			return i;
		}
	}
	return NULL;
}

void Cheat::GameFunctions::MaxUpgradeAllWeapons()
{
	for (auto const& i : GameArrays::MaxUpgradeWeaponComponents)
	{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(GameFunctions::PlayerPedID, i.WeaponHash, GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i.UpgradeHash)));
	}
}

void Cheat::GameFunctions::ShowTeleportLocationsMenu(std::vector<TeleportLocationStruct> category)
{
	for (int i = 0; i < category.size(); i++)
	{
		Vector3 Coords;
		Coords.x = category[i].coordinateX;
		Coords.y = category[i].coordinateY;
		Coords.z = category[i].coordinateZ;
		if (GUI::Option(category[i].Name, ""))
		{
			GameFunctions::TeleportToCoords(GameFunctions::PlayerPedID, Coords, false, false);
		}
	}
}

void Cheat::GameFunctions::ToggleOffRadar(bool state)
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		globalHandle(2689156).At(1 + (Cheat::GameFunctions::PlayerID * 453)).At(209).As<bool>() = state;
		globalHandle(2703656).At(70).As<int>() = NETWORK::GET_NETWORK_TIME();
	}
}

void Cheat::GameFunctions::ToggleCopsTurnBlindEye(bool state)
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		globalHandle(2544210).At(4622).As<int>() = 5;
		globalHandle(2544210).At(4623).As<int>() = 1;
		globalHandle(2544210).At(4625).As<int>() = NETWORK::GET_NETWORK_TIME();
	}
}

//https://codepen.io/Codepixl/pen/ogWWaK
void Cheat::GameFunctions::FadeRGB(int& r, int& g, int& b)
{
	if (r > 0 && b == 0)
	{
		r--;
		g++;
	}
	if (g > 0 && r == 0)
	{
		g--;
		b++;
	}
	if (b > 0 && g == 0) 
	{
		r++;
		b--;
	}
}

/*
Description: Shows a full-screen message with background rectangle.
Note(s): Used by Recovery warning and Unload, needs work to be used for other purposes.
*/
bool Cheat::GameFunctions::ShowFullScreenMessage(std::string Message)
{
	while (true)
	{
		GUI::DrawRectInGame({ GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b, 210 }, { 0.500f, 0.372f }, { 0.30f, 0.005f });
		GUI::DrawRectInGame({ 0, 0, 0, 210 }, { 0.50f, 0.45f }, { 0.30f, 0.15f });
		Cheat::GUI::DrawTextInGame("WARNING", { 255, 255, 255, 255, FontPricedown }, { 0.355f, 0.375f }, { 0.50f, 0.50f }, false);
		Cheat::GUI::DrawTextInGame(Message, { 255, 255, 255, 255}, { 0.500f, 0.410f}, { 0.40f, 0.40f }, true, true);
		Cheat::GUI::DrawTextInGame("Press ENTER to accept or BACKSPACE to decline", { 255, 255, 255, 255 }, { 0.355f, 0.495f }, { 0.30f, 0.30f }, false);
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT))
		{
			return true;
		}
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_CANCEL))
		{
			return false;
		}
		GameHooking::PauseMainFiber(0, false);
	}
}

void Cheat::GameFunctions::SetCharacterSkillStat(std::string Skill, int Level)
{
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_" + Skill)), Level, true);
}

void Cheat::GameFunctions::ChangeGTAOSessionType(SessionTypes SessionType)
{
	if (SessionType != NULL)
	{
		if (SessionType == SessionTypeLeaveOnline)
		{
			if (NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				globalHandle(1574587).At(2).As<int>() = SessionTypeLeaveOnline;
			}
		}
		else
		{
			globalHandle(1575004).As<int>() = (int)SessionType;
		}
		globalHandle(1574587).As<int>() = 1;
		GameHooking::PauseMainFiber(50, false);
		globalHandle(1574587).As<int>() = 0;
		GUI::CloseMenuGUI();
	}	
}