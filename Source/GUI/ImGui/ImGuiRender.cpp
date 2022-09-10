#include "../Header/Cheat Functions/FiberMain.h"

void Cheat::GUI::DearImGui::Render()
{
	ImGuiIO& io = ImGui::GetIO();

	// Show/hide cursor
	if (!CheatFeatures::CursorNavigationState)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
	}
	else
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
	}

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_TitleBg] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_TitleBgActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
	colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);
	colors[ImGuiCol_Button] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ButtonHovered] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ButtonActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGripHovered] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGrip] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGripActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_CheckMark] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);

	// Windows
	Logger::CheatWindow();
	Logger::GameChatWindow();

	// Cheat initialization menu
	if (!CheatFunctions::ConfigLoaded && CheatFunctions::CheatInitCompleted)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
		ImGui::Begin("CheatInitLoadingMenu", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("GTAV Cheat is loading, one moment please %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]); //TODO; add a better-looking spinner/progress indicator
		ImGui::SetWindowPos(ImVec2(io.DisplaySize.x - ImGui::GetWindowWidth() - 4.f, io.DisplaySize.y - ImGui::GetWindowHeight() - 4.f));
		ImGui::End();
		ImGui::PopStyleVar();
	}

	// Player Info Box
	DearImGui::PlayerInfoBox();
}