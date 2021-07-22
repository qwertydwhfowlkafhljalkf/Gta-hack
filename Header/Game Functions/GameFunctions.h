#pragma once

namespace Cheat
{
	namespace GameFunctions
	{
		extern Player PlayerID;
		extern Ped PlayerPedID;
		extern std::string InGameKeyboardWindowTitle;
		void GiveAllWeaponsToPlayer(Ped Player);
		void RepairAndCleanVehicle();
		void SubtitleNotification(char* Message, int ShowDuration = 4000);
		void TeleportToBlipCoord(Blip TargetBlip);
		void TeleportToObjective();
		void BurstSelectedPlayerTires(Ped selectedPed);
		void SetOffAlarmPlayerVehicle(Ped selectedPed);
		bool IsPlayerFriend(Player player);
		double DegreeToRadian(double n);
		Vector3 MultiplyVector(Vector3 vector, float inc);
		Vector3 AddVector(Vector3 vector, Vector3 vector2);
		Vector3 RotationToDirection(Vector3 rot);
		void SetRankRockstarGift(int RPValue);
		Vector3 RotToDirection(Vector3* rot);
		Vector3 AddTwoVectors(Vector3* vectorA, Vector3* vectorB);
		Vector3 MultiplyVector(Vector3* vector, float x);
		float GetDistanceBetweenTwoVectors(Vector3* pointA, Vector3* pointB);
		void TeleportToCoords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight, bool IgnoreCurrentPedVehicle);
		int ReturnRandomInteger(int start, int end);
		float GetDistanceBetweenTwoPoints(Vector3 A, Vector3 B);
		Vector3 GetEntityCoords(Entity entity);
		float DegreesToRadians(float degs);
		void GetCameraDirection(float* dirX, float* dirY, float* dirZ);
		void RequestNetworkControlOfEntity(Entity entity);
		void ClonePed(Ped ped);
		char* DisplayKeyboardAndReturnInput(int MaxInput, std::string Title);
		int DisplayKeyboardAndReturnInputInteger(int MaxInput, std::string Title);
		void ClearAllAnimations();
		void ShowPlayerInformationBox(Player PlayerID);
		float Get3DDistance(Vector3 a, Vector3 b);
		void ApplyForceToEntity(Entity e, float x, float y, float z);
		void SpawnVehicle(char* ModelHash);
		void SetPedTexture(Ped Ped, int ComponentID, int DrawableID, int TextureID);
		void MaxDowngradeVehicle(int VehicleHandle);
		void MaxUpgradeVehicle(int VehicleHandle);
		void EnableDisableAntiCrashCamera();
		void CheckNewSessionMembersLoop();
		bool IsEntityInInterior(Entity Entity);
		void InstructionalKeysInit();
		void InstructionsAdd(char* text, int button);
		void InstructionsEnd();
		void ClearNearbyPedAnimations();
		void DoNearbyPedsAnimation(char* AnimationName, char* AnimationID);
		void DoLocalPedAnimation(char* AnimationName, char* AnimationID);
		void AttachObjectToPed(Ped Ped, char* ObjectName);
		void DetachObjectFromPed(Ped Ped, char* ObjectName);
		void MinimapNotification(char* Message);
		void AdvancedMinimapNotification(char* Message, char* PicName1, char* PicName2, bool Flash, int IconType, char* Sender, char* Subject, float Duration, char* ClanTag);
		void AddBlipToVehicle(Vehicle Vehicle);
		bool DeleteVehicle(Vehicle Vehicle);
		float MSToKMH(float MS);
		float MSToMPH(float MS);
		float KMHToMS(float MS);
		float MPHToMS(float MS);
		void ChangeEntityInvincibilityState(Entity EntityHandle, bool Enable);
		char* ReturnOnlinePlayerPictureString(Player PlayerHandle);
		VECTOR2 ReturnCursorYXCoords();
		void CursorGUINavigationLoop();
		void EnableDisableCursorGUINavigation();
		bool IsCursorAtXYPosition(VECTOR2 const& boxCentre, VECTOR2 const& boxSize);
		void ChangePedModelLocalPlayer(Hash PedModel);
		bool PlayerIsFreemodeScriptHost(Player Player);
		void CopySelectedPlayerOutfit(Player SelectedPlayer);
		int ReturnPlayerRockstarID(Player PlayerHandle);
		std::string ReturnPlayerIPAddressAsString(Player PlayerHandle);
		std::string ReturnCurrentGTAOCharacter();
		void PlayFrontendSoundDefault(char* SoundName);
		void PlayScenarioNearbyPeds(char* Scenario);
		bool IsPlayerIDValid(Player ID);
		Player ReturnPlayerIDFromPlayerName(std::string PlayerName);
	}
}