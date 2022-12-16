#include "file_system.hpp"

namespace Cheat
{
	namespace file_system
	{
		const std::string paths::UserprofileDir = std::getenv("userprofile");
		const std::string paths::UserDocumentsDir = UserprofileDir + "\\Documents";
		const std::string paths::DataDir = UserDocumentsDir + "\\GTAV Cheat";
		const std::string paths::LogDir = DataDir + "\\Logs";
		const std::string paths::ThemesDir = DataDir + "\\Themes";
		const std::string paths::ConfigFile = DataDir + "\\Config.ini";
		const std::string paths::CusTelLocFile = DataDir + "\\CustomTeleportLocations.json";
		const std::string paths::HUDColorsFile = DataDir + "\\HUDColors.ini";
		const std::string paths::TextureFile = DataDir + "\\Textures.ytd";
	}
}