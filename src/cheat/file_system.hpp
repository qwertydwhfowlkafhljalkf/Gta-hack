#pragma once
#include <iostream>

namespace Cheat
{
	namespace file_system
	{
		struct paths
		{
			static const std::string UserprofileDir;		// Default: <SystemDriveLetter>:\Users\<username>
			static const std::string UserDocumentsDir;		// Default: <SystemDriveLetter>:\Users\<username>\Documents
			static const std::string DataDir;				// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat
			static const std::string LogDir;				// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\Logs
			static const std::string ThemesDir;				// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\Themes
			static const std::string ConfigFile;			// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\Config.ini
			static const std::string ChatLogFile;			// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\Logs\Chats.log
			static const std::string CusTelLocFile;			// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\CustomTeleportLocations.json
			static const std::string HUDColorsFile;			// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\HUDColors.ini
			static const std::string TextureFile;			// Default: <SystemDriveLetter>:\Users\<username>\Documents\GTAV Cheat\Textures.ytd
		};
	}
}