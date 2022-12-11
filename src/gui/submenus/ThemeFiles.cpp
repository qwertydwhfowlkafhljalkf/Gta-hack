#include "../../src/cheat/fibermain.h"
#include "../../src/cheat/file_system.hpp"

using namespace Cheat;
void GUI::Submenus::ThemeFiles()
{
	GUI::Title("Saved Themes");
	if (!GUI::ThemeFilesVector.empty())
	{
		for (auto const& i : GUI::ThemeFilesVector)
		{
			if (GUI::Option(i, ""))
			{
				if (std::filesystem::exists(file_system::paths::ThemesDir + "\\" + i + ".ini"))
				{
					GUI::LoadTheme(CheatFunctions::StringToChar(i), false);
				}
				else
				{
					GameFunctions::MinimapNotification((char*)"~r~Unable to locate theme file");
				}
			}
		}
	}
	else
	{
		GUI::Break("No Theme Files Saved Yet");
	}
}