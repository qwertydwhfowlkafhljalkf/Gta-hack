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
	AnimationsMenu,
	nearbyvehicles_menu,
	nearbypeds_menu,
	iplloader,
	iplteleports,
	weathermenu,
	VehicleSpawnSettings,
	SpawnedVehiclesMenu,
	AllPlayersMenu,
	AllPlayersExclutionsMenu,
	ModelChangerMenu,
	GlobalsMenu,
	SpawnMenu,
	VehicleSpawnMenu,
	ObjectSpawnMenu,
	PedSpawnMenu,
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
	clothingmenu,
	outfitsmenu,
	componentschangermenu,
	SelectedPlayerRemoteOptions,
	SessionChatMenu,
	vehicleweaponsmenu,
	RecoveryMenu,
	RecoveryMenuWarning,
	vehiclemultipliersmenus,
	ShootEntitiesMenu,
	aimbotsettingsmenu,
	SelectedPlayerTeleportMenu,
	sessionoptionsmenu,
	hudmenu,
	HideElementsMenu,
	AboutMenu,
	reportsmenu_stats,
	ESPMenu,
	VehicleCustomizerMenu,
	DLCVehiclesMenu,
	RadioMenu,
	SUBMENUS_END //Used to get total size of SubMenus (SUBMENUS_END - 2) 
};

enum SelectableBitFlags
{
	SELECTABLE_DUMMY = 1,			//Placeholder
	SELECTABLE_DISABLED = 2,		//The selectable is disabled, if the select key is pressed on the selectable a message appears informing the user about the disable state. When using this flag saving is also blocked (use of SELECTABLE_DISABLE_SAVE not needed).
	SELECTABLE_DISABLE_SAVE = 4,	//The selectable won't save when the corresponding key is pressed.
	SELECTABLE_CENTER_TEXT = 8,		//This currently only applies to the Break selectable. Text will be centered relative to menu GUI.
	SELECTABLE_RETURN_VALUE_CHANGE = 16,  //Currently used by Float and StringVector selectable. Function will also return when a value is changed (e.g. left or right is pressed).
	SELECTABLE_HIDE_INFO_BOX = 32, //Forcefully (ignoring other settings) hides the Selectable Information Box for a given Selectable.
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
		void LoadTextureFile();
		void DrawTextInGame(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool Outline = false);
		void DrawRectInGame(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void DrawSpriterInGame(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);

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
		extern float SelectableHeight;
		extern std::vector <std::string> ThemeFilesVector;
		extern bool ShowHeaderBackground;
		extern bool ShowHeaderTexture;
		extern bool HideGUIElements;
		extern bool CheatGUIHasBeenOpened;
		extern bool CurrentOptionIsSavable;
		extern std::string CurrentTheme;
		//extern bool center;
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
		extern int SelectableTransparency;
		extern int HeaderBackgroundTransparency;
		extern int TitleAndEndTransparency;
		extern int ToggleSelectableTransparency;
		extern int HeaderTextureTransparency;
		extern int EndSmallLogoTransparency;
		extern int MenuArrowAnimationDelay;
		extern bool MenuOptionArrowAnimationState;
		extern void DeleteLoadedTheme();
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseMenuGUI();
		void End();
		void LoadTheme(std::string ThemeFileName, bool StartUp);
		void SaveTheme(std::string ThemeFileName);
		extern bool SelectableHandler(bool DisabledState);

		void Title(std::string TitleName);
		void AddPlayerInfoBoxTextEntry(std::string text, int Row1 = NULL, int Row2 = NULL, int Row3 = NULL, int Row4 = NULL);
		bool Break(std::string option, int BitFlags = NULL);
		bool Option(std::string option, std::string InformationText, int BitFlags = NULL);
		bool VehicleOption(std::string option, std::string ModelName);
		bool MenuOption(std::string option, SubMenus newSub, int BitFlags = NULL);
		bool MenuOptionPlayerList(std::string PlayerName, int BitFlags = NULL);
		bool Toggle(std::string option, bool& TargetBool, std::string InformationText, int BitFlags = NULL);
		bool Int(std::string option, int& _int, int min, int max, int step, std::string InformationText = "Select to change", int BitFlags = NULL);
		bool Float(std::string option, float& _float, float min, float max, float steps, std::string InformationText = "", std::streamsize FloatPrecision = 3, int BitFlags = NULL);
		bool IntVector(std::string option, std::vector<int> Vector, int& position, int BitFlags = NULL);
		bool FloatVector(std::string option, std::vector<float> Vector, int& position, int BitFlags = NULL);
		bool StringVector(std::string option, std::vector<std::string> Vector, int& position, std::string InformationText, int BitFlags = NULL);
	}
}