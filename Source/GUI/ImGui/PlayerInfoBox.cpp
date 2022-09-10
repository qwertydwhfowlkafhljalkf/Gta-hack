#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;

// Player Information Box
void GUI::DearImGui::PlayerInfoBox()
{
	if (CheatFunctions::ShowPlayerInformationBoxNow && CheatFunctions::CheatInitEntirelyCompleted)
	{
		ImGui::Begin("Player Information", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::BeginTable("PlayerInfoBoxTable", 4, ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_SizingFixedFit))
		{
			// Row #1
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Name");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.PlayerName.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Distance");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Distance.c_str());

			// Row #2
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Rank");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Rank).c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Modded Model");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.ModdelModel ? "Yes" : "No");

			// Row #3
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Money");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Money).c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("In Interior");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.InInterior ? "Yes" : "No");

			// Row #4
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Health");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Health).c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Cutscene");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Cutscene ? "Yes" : "No");

			// Row #5
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Armor");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Armor).c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Rockstar ID");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.RockstarID).c_str());

			// Row #6
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Status");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Status.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("IP Address");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.IPAddress.c_str());

			// Row #7
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Vehicle");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Vehicle.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Invisible");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Invisible ? "Yes" : "No");

			// Row #9
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("K/D");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.KD).c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Gender");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Gender.c_str());

			// Row #10
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Vehicle/Movement Speed");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.MovementSpeed.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Wanted Level");

			ImGui::TableSetColumnIndex(3);
			std::string WantedLevel = std::to_string(CheatFunctions::PlayerInfoBoxDataObject.WantedLevel) + "/5";
			ImGui::Text(WantedLevel.c_str());

			// Row #11
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Weapon");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Weapon.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("X-coord");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.X).c_str());

			// Row #12
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Zone");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Zone.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Y-coord");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Y).c_str());

			// Row #13
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Street");

			ImGui::TableSetColumnIndex(1);
			ImGui::Text(CheatFunctions::PlayerInfoBoxDataObject.Street.c_str());

			ImGui::TableSetColumnIndex(2);
			ImGui::Text("Z-coord");

			ImGui::TableSetColumnIndex(3);
			ImGui::Text(std::to_string(CheatFunctions::PlayerInfoBoxDataObject.Z).c_str());

			ImGui::EndTable();
		}
		ImGui::End();
	}
}