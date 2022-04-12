#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::PedSpawn()
{
	GUI::Title("Ped Spawn");
	GUI::Break("List", SELECTABLE_CENTER_TEXT);
	for (auto const& i : GameArrays::PedModels)
	{
		if (GUI::Option(i, "Select to spawn"))
		{
			Hash PedHash = GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i));
			if (ENTITY::IS_ENTITY_A_PED(PedHash))
			{
				STREAMING::REQUEST_MODEL(PedHash);
				while (!STREAMING::HAS_MODEL_LOADED(PedHash)) { GameHooking::PauseMainFiber(0); }
				Vector3 NewPedPosition = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GameFunctions::PlayerPedID, 0.0f, 5.0f, 0.0f);
				Ped NewPedHandle = PED::CREATE_PED(0, PedHash, NewPedPosition.x, NewPedPosition.y, NewPedPosition.z, 0, true, true);
				ENTITY::SET_ENTITY_VISIBLE(NewPedHandle, true, false);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
			}	
		}
	}
}