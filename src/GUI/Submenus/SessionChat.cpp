#include "../../src/Cheat/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::SessionChat()
{
	GUI::Title("Session Chat");
	GUI::Toggle("Log Messages", CheatFeatures::LogChatMessages, "Chat gets logged to console");
}