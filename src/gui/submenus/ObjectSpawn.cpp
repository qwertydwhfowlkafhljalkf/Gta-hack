#include "../../src/cheat/FiberMain.h"

using namespace Cheat;
std::string ObjectSpawnSearchTerm;
void GUI::Submenus::ObjectSpawn()
{
	/* TODO
	GUI::Title("Object Spawn");
	GUI::Break("Object List", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Search", "Enter keywords to filter object list"))
	{
		const char* KeyboardInput;
		if (GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter search term", KeyboardInput))
		{
			ObjectSpawnSearchTerm = KeyboardInput;
			std::transform(ObjectSpawnSearchTerm.begin(), ObjectSpawnSearchTerm.end(), ObjectSpawnSearchTerm.begin(), tolower);
		}
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
	*/
}