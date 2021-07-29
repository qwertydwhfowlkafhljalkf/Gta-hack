#pragma once

enum SubMenus
{
	NOMENU,
	MainMenu,
	SelfOptionsMenu,
	SettingsMenu,
	ThemeMenu,
	ThemeFilesMenu,
	PlayerListMenu,
	SelectedPlayerMenu,
	teleportmenu,
	weaponmenu,
	WeaponsMenu,
	WeaponVisualsMenu,
	WeaponAmmoMenu,
	VehicleCustomizerColorMenu,
	miscmenu,
	worldmenu,
	vehiclemenu,
	AnimationsAndScenariosMenu,
	nearbyvehicles_menu,
	nearbypeds_menu,
	iplloader,
	iplteleports,
	weathermenu,
	VehicleSpawnSettings,
	SpawnedVehiclesMenu,
	AllPlayersMenu,
	ModelChangerMenu,
	vehiclespawnermenu,
	Super,
	Sports,
	smugglersrun,
	SportClassic,
	Offroad,
	Sedans,
	Coupes,
	Muscle,
	Boats,
	Commercial,
	Compacts,
	Cycles,
	Emergency,
	Helicopters,
	Industrial,
	Military,
	Motorcycles,
	Planes,
	Service,
	SUV,
	Trailer,
	Trains,
	vehicle_lsc_neon_options,
	vehicle_lsc_color_options,
	Utility,
	Vans,
	SSASSSDLC,
	doomsdayheistdlc,
	gunrunningdlc,
	CunningStuntsDLCMenu,
	afterhoursdlc,
	arenawardlc,
	casinodlc,
	diamondcasinoheist,
	SummerSpecialDLCMenu,
	CayoPericoHeistDLCMenu,
	LosSantosTunersDLCMenu,
	OnlineOptionsMenu,
	timemenu,
	LandmarkTeleportLocations,
	CustomTeleportLocations,
	SafehousesTeleportLocations,
	HighAltitudeTeleportLocations,
	UnderwaterTeleportLocations,
	SelectedPlayerAttachmentOptions,
	SelectedPlayerTrollMenu,
	SelectedPlayerFriendlyMenu,
	protections,
	ESPMenu,
	clothingmenu,
	outfitsmenu,
	componentschangermenu,
	SelectedPlayerRemoteOptions,
	SessionChatMenu,
	vehicleweaponsmenu,
	allplayers_trolloptionsmenu,
	RecoveryMenu,
	vehicledooroptionsmenu,
	vehiclemultipliersmenus,
	vehiclegunmenu,
	aimbotsettingsmenu,
	SelectedPlayerTeleportMenu,
	sessionoptionsmenu,
	hudmenu,
	HideElementsMenu,
	AboutMenu,
	unlocksmenu,
	reportsmenu_stats,
	allplayers_weaponoptionsmenu,
	VehicleCustomizerMenu,
	DLCVehiclesMenu,
	SUBMENUS_END //Used to get total size of SubMenus (SUBMENUS_END - 2) 
};

typedef struct VECTOR2 { float x, y; };
typedef struct VECTOR2_2 { float w, h; };
typedef struct RGBAF { int r, g, b, a, f; };
typedef struct RGBA { int r, g, b, a; };
typedef struct RGB { int r, g, b; };

namespace Cheat
{
	namespace GUI
	{
		namespace Drawing
		{
			void Text(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool Outline = false);
			void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
			void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
			void InitTextureFile();
		}

		extern void ControlsLoop();

		extern const float SelectableInfoBoxY_Default;
		extern const float SelectableInfoBoxX_Default;
		extern const float guiWidth_Default;
		extern const float guiY_Default;
		extern const float guiX_Default;
		extern float guiX;
		extern float guiY;
		extern float guiWidth;
		extern float SelectableInfoBoxX;
		extern float SelectableInfoBoxY;
		extern std::vector <std::string> ThemeFilesVector;
		extern bool ShowHeaderBackground;
		extern bool ShowHeaderTexture;
		extern bool HideGUIElements;
		extern bool CheatGUIHasBeenOpened;
		extern bool CurrentOptionIsSavable;
		extern std::string CurrentTheme;
		extern bool ControlsDisabled;
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool RestorePreviousSubmenu;
		extern int maxVisOptions;
		extern int currentOption;
		extern int currentOptionVisible;
		extern int previousOption;
		extern int optionCount;
		extern int optionCountVisible;
		extern int TotalOptionsCount;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int PreviousMenuLevel;
		extern SubMenus PreviousMenu;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];
		extern RGBA selectedText;
		extern RGBA scroller;
		extern RGBA PrimaryColor;
		extern RGBAF TextColorAndFont;
		extern int KeyPressDelay;
		extern int KeyPressPreviousTick;
		extern int OpenGUIKey;
		extern int GUINavigationKey;
		extern int SaveItemKey;
		extern void DeleteCurrentTheme();
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseGUI();
		void End();
		void ChangeControlsState(bool State);
		void LoadTheme(std::string ThemeFileName, bool StartUp);
		void SaveTheme(std::string ThemeFileName);
		extern bool SelectableHandler(bool DisabledState);

		void Title(std::string TitleName);
		void AddPlayerInfoBoxTextEntry(std::string text, int Row1 = NULL, int Row2 = NULL, int Row3 = NULL, int Row4 = NULL);
		bool Break(std::string option, bool TextCentered);
		bool Option(std::string option, std::string InformationText, bool Disabled = false);
		bool VehicleOption(std::string option, std::string ModelName);
		bool MenuOption(std::string option, SubMenus newSub, bool Disabled = false);
		bool MenuOptionPlayerList(std::string PlayerName, SubMenus newSub);
		bool Toggle(std::string option, bool& b00l, std::string InformationText, bool IsSavable = true, bool Disabled = false);
		bool Int(std::string option, int& _int, int min, int max, int step, bool IsSavable = true, std::string InformationText = "Select to change", bool Disabled = false);
		bool Float(std::string option, float& _float, float min, float max, float steps, bool ReturnTrueWithValueChange, bool IsSavable = true, std::string InformationText = "", bool Disabled = false);
		bool IntVector(std::string option, std::vector<int> Vector, int& position, bool IsSavable = true, bool Disabled = false);
		bool FloatVector(std::string option, std::vector<float> Vector, int& position, bool IsSavable = true, bool Disabled = false);
		bool StringVector(std::string option, std::vector<std::string> Vector, int& position, std::string InformationText, bool IsSavable = true, bool Disabled = false);
	}
}