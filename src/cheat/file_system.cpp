#include "file_system.hpp"
#include <ini.h>

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
		bool ini_file::write(std::string data, std::string FilePath, std::string Section, std::string Key)
		{
			mINI::INIFile File(FilePath);
			mINI::INIStructure StructData;
			File.read(StructData);
			StructData[Section][Key] = data;
			if (File.write(StructData, true))
				return true;
			return false;
		}
		bool ini_file::write_bool(bool State, std::string FilePath, std::string Section, std::string Key)
		{
			if (file_system::ini_file::write(State ? "true" : "false", FilePath, Section, Key))
				return true;
			return false;
		}
		bool ini_file::remove_key(std::string FilePath, std::string Section, std::string Key)
		{
			mINI::INIFile File(FilePath);
			mINI::INIStructure StructData;
			File.read(StructData);
			if (StructData[Section].has(Key))
			{
				StructData[Section].remove(Key);
				File.write(StructData);
				return true;
			}
			return false;
		}
		std::string ini_file::get(std::string FilePath, std::string Section, std::string Key)
		{
			mINI::INIFile File(FilePath);
			mINI::INIStructure StructData;
			File.read(StructData);
			if (StructData[Section].has(Key))
				return StructData.get(Section).get(Key);
			return std::string();
		}
		bool write_file(std::string FilePath, std::string data)
		{
			std::ofstream file_handle;
			file_handle.open(FilePath, std::ofstream::app | std::ofstream::out);
			if (file_handle.is_open())
			{
				file_handle << data;
				file_handle.close();
			}
			if (file_handle.bad())
				return false;
			return true;
		}
	}
}