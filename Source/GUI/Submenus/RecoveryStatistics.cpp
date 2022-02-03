#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::RecoveryStatistics()
{
	GUI::Title("Statistics");
	std::vector <std::string> SkillStats = { "STAM", "STRN", "LUNG", "DRIV", "FLY", "SHO", "STL" };
	if (GUI::Option("Max All Skills", ""))
	{
		for (const auto& i : SkillStats)
		{
			GameFunctions::SetCharacterSkillStat(i, 100);
		}
		GameFunctions::MinimapNotification("Maxed out all skill stats for your current character");
	}
	if (GUI::Option("Max Stamina", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[0], 100);
	}
	if (GUI::Option("Max Strength", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[1], 100);
	}
	if (GUI::Option("Max Lung Capacity", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[2], 100);
	}
	if (GUI::Option("Max Driving", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[3], 100);
	}
	if (GUI::Option("Max Flying", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[4], 100);
	}
	if (GUI::Option("Max Shooting", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[5], 100);
	}
	if (GUI::Option("Max Stealth", ""))
	{
		GameFunctions::SetCharacterSkillStat(SkillStats[6], 100);
	}
}