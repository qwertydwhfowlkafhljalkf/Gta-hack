#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;

bool WhatsNewDataInitialized = false;
void GUI::DearImGui::WhatsNewPopup()
{
	/*
	What's new popup - TODO

	const char* ChangelogText = "";
	if (!WhatsNewDataInitialized)
	{
		Json::Value JsonDataObject = CheatFunctions::ReturnGithubAPIJsonDataCheat("v" + (std::string)CHEAT_BUILD_NUMBER);
		if (JsonDataObject.isMember("body"))
		{
			ChangelogText = JsonDataObject["body"].asCString();

		}
		else
		{
			ChangelogText = "Changelog text is unavailable";
		}
		WhatsNewDataInitialized = true;
	}
	else
	{
		ImGui::SetNextWindowSize(ImVec2(800, 800));
		ImGui::OpenPopup("GTAV Cheat - What's New");
		if (ImGui::BeginPopupModal("GTAV Cheat - What's New", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
			ImGui::Text(ChangelogText);

			if (ImGui::Button("Close", ImVec2(200, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
	*/
}