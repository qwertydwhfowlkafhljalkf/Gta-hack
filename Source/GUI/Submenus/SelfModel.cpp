#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
std::string ChangeModelPedSearchTerm;
void GUI::Submenus::SelfModel()
{
	GUI::Title("Model");
	if (GUI::Option("Custom Input", "Input custom Ped model"))
	{
		char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter custom ped model name");
		if (KeyboardInput != "0") 
		{ 
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
	}
	GUI::Break("Ped List", SELECTABLE_CENTER_TEXT);
	if (GUI::Option("Search", "Enter keywords to filter peds list"))
	{
		char* KeyboardInput = GameFunctions::DisplayKeyboardAndReturnInput(30, "Enter search term");
		if (KeyboardInput != "0") 
		{ 
			ChangeModelPedSearchTerm = KeyboardInput;
			std::transform(ChangeModelPedSearchTerm.begin(), ChangeModelPedSearchTerm.end(), ChangeModelPedSearchTerm.begin(), tolower);
		}	
	}
	if (!ChangeModelPedSearchTerm.empty())
	{
		if (GUI::Option("Clear Search Results", ""))
		{
			ChangeModelPedSearchTerm.clear();
		}
		GUI::Break("Search Results", SELECTABLE_CENTER_TEXT);
	}
	for (auto const& i : GameArrays::PedModels)
	{
		std::string i_lowercase = i;
		std::transform(i_lowercase.begin(), i_lowercase.end(), i_lowercase.begin(), tolower);
		if (ChangeModelPedSearchTerm.empty() || i_lowercase.find(ChangeModelPedSearchTerm) != std::string::npos)
		{
			if (GUI::Option(i, ""))
			{
				GameFunctions::ChangePedModelLocalPlayer(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)));
			}
		}
	}
}