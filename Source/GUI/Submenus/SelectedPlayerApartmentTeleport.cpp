#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SelectedPlayerApartmentTeleport()
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