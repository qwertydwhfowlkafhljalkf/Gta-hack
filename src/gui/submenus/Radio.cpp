#include "../../src/cheat/fibermain.h"

using namespace Cheat;
void GUI::Submenus::Radio()
{
	GUI::Title("Radio");
	if (GUI::Option("Skip Track", "")) { AUDIO::SKIP_RADIO_FORWARD(); }
	GUI::Toggle("Freeze Station", CheatFeatures::FreezeStationBool, "");
	GUI::Toggle("Mobile Radio", CheatFeatures::MobileRadioBool, "");
}