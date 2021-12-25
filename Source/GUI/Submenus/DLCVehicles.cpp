#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::DLCVehicles()
{
	GUI::Title("DLC Vehicles");
	GUI::MenuOption("The Contract", Submenus::TheContractDLC);
	GUI::MenuOption("Los Santos Tuners", Submenus::LosSantosTunersDLC);
	GUI::MenuOption("The Cayo Perico Heist", Submenus::CayoPericoHeistDLC);
	GUI::MenuOption("2020 Summer Special", Submenus::SummerSpecialDLC);
	GUI::MenuOption("The Diamond Casino Heist", Submenus::DiamondCasinoHeistDLC);
	GUI::MenuOption("The Diamond Casino & Resort", Submenus::DiamondCasinoResortDLC);
	GUI::MenuOption("Arena War", Submenus::ArenaWarDLC);
	GUI::MenuOption("After Hours", Submenus::AfterHoursDLC);
	GUI::MenuOption("SSASSS", Submenus::SSASSSDLC);
	GUI::MenuOption("The Doomsday Heist", Submenus::DoomsdayHeistDLC);
	GUI::MenuOption("Smuggler's Run", Submenus::SmugglersRunDLC);
	GUI::MenuOption("Gunrunning", Submenus::GunrunningDLC);
	GUI::MenuOption("Cunning Stunts", Submenus::CunningStuntsDLC);
}