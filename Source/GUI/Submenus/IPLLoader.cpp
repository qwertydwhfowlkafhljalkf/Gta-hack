#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::IPLLoader()
{
	GUI::Title("IPL Loader");
	if (GUI::Option("Load MP data", ""))
	{
		DLC::ON_ENTER_MP();
	}
	if (GUI::Option("Unload MP data", ""))
	{
		DLC::ON_ENTER_SP();
	}
	if (GUI::Option("Load North Yankton", ""))
	{
		STREAMING::REQUEST_IPL("plg_01");
		STREAMING::REQUEST_IPL("prologue01");
		STREAMING::REQUEST_IPL("prologue01_lod");
		STREAMING::REQUEST_IPL("prologue01c");
		STREAMING::REQUEST_IPL("prologue01c_lod");
		STREAMING::REQUEST_IPL("prologue01d");
		STREAMING::REQUEST_IPL("prologue01d_lod");
		STREAMING::REQUEST_IPL("prologue01e");
		STREAMING::REQUEST_IPL("prologue01e_lod");
		STREAMING::REQUEST_IPL("prologue01f");
		STREAMING::REQUEST_IPL("prologue01f_lod");
		STREAMING::REQUEST_IPL("prologue01g");
		STREAMING::REQUEST_IPL("prologue01h");
		STREAMING::REQUEST_IPL("prologue01h_lod");
		STREAMING::REQUEST_IPL("prologue01i");
		STREAMING::REQUEST_IPL("prologue01i_lod");
		STREAMING::REQUEST_IPL("prologue01j");
		STREAMING::REQUEST_IPL("prologue01j_lod");
		STREAMING::REQUEST_IPL("prologue01k");
		STREAMING::REQUEST_IPL("prologue01k_lod");
		STREAMING::REQUEST_IPL("prologue01z");
		STREAMING::REQUEST_IPL("prologue01z_lod");
		STREAMING::REQUEST_IPL("plg_02");
		STREAMING::REQUEST_IPL("prologue02");
		STREAMING::REQUEST_IPL("prologue02_lod");
		STREAMING::REQUEST_IPL("plg_03");
		STREAMING::REQUEST_IPL("prologue03");
		STREAMING::REQUEST_IPL("prologue03_lod");
		STREAMING::REQUEST_IPL("prologue03b");
		STREAMING::REQUEST_IPL("prologue03b_lod");
		STREAMING::REQUEST_IPL("prologue03_grv_dug");
		STREAMING::REQUEST_IPL("prologue03_grv_dug_lod");
		STREAMING::REQUEST_IPL("prologue_grv_torch");
		STREAMING::REQUEST_IPL("plg_04");
		STREAMING::REQUEST_IPL("prologue04");
		STREAMING::REQUEST_IPL("prologue04_lod");
		STREAMING::REQUEST_IPL("prologue04b");
		STREAMING::REQUEST_IPL("prologue04b_lod");
		STREAMING::REQUEST_IPL("prologue04_cover");
		STREAMING::REQUEST_IPL("des_protree_end");
		STREAMING::REQUEST_IPL("des_protree_start");
		STREAMING::REQUEST_IPL("des_protree_start_lod");
		STREAMING::REQUEST_IPL("plg_05");
		STREAMING::REQUEST_IPL("prologue05");
		STREAMING::REQUEST_IPL("prologue05_lod");
		STREAMING::REQUEST_IPL("prologue05b");
		STREAMING::REQUEST_IPL("prologue05b_lod");
		STREAMING::REQUEST_IPL("plg_06");
		STREAMING::REQUEST_IPL("prologue06");
		STREAMING::REQUEST_IPL("prologue06_lod");
		STREAMING::REQUEST_IPL("prologue06b");
		STREAMING::REQUEST_IPL("prologue06b_lod");
		STREAMING::REQUEST_IPL("prologue06_int");
		STREAMING::REQUEST_IPL("prologue06_int_lod");
		STREAMING::REQUEST_IPL("prologue06_pannel");
		STREAMING::REQUEST_IPL("prologue06_pannel_lod");
		STREAMING::REQUEST_IPL("prologue_m2_door");
		STREAMING::REQUEST_IPL("prologue_m2_door_lod");
		STREAMING::REQUEST_IPL("plg_occl_00");
		STREAMING::REQUEST_IPL("prologue_occl");
		STREAMING::REQUEST_IPL("plg_rd");
		STREAMING::REQUEST_IPL("prologuerd");
		STREAMING::REQUEST_IPL("prologuerdb");
		STREAMING::REQUEST_IPL("prologuerd_lod");
		GameFunctions::MinimapNotification("North Yankton IPL loaded");
	}
	if (GUI::Option("Unload North Yankton", ""))
	{
		STREAMING::REMOVE_IPL("plg_01");
		STREAMING::REMOVE_IPL("prologue01");
		STREAMING::REMOVE_IPL("prologue01_lod");
		STREAMING::REMOVE_IPL("prologue01c");
		STREAMING::REMOVE_IPL("prologue01c_lod");
		STREAMING::REMOVE_IPL("prologue01d");
		STREAMING::REMOVE_IPL("prologue01d_lod");
		STREAMING::REMOVE_IPL("prologue01e");
		STREAMING::REMOVE_IPL("prologue01e_lod");
		STREAMING::REMOVE_IPL("prologue01f");
		STREAMING::REMOVE_IPL("prologue01f_lod");
		STREAMING::REMOVE_IPL("prologue01g");
		STREAMING::REMOVE_IPL("prologue01h");
		STREAMING::REMOVE_IPL("prologue01h_lod");
		STREAMING::REMOVE_IPL("prologue01i");
		STREAMING::REMOVE_IPL("prologue01i_lod");
		STREAMING::REMOVE_IPL("prologue01j");
		STREAMING::REMOVE_IPL("prologue01j_lod");
		STREAMING::REMOVE_IPL("prologue01k");
		STREAMING::REMOVE_IPL("prologue01k_lod");
		STREAMING::REMOVE_IPL("prologue01z");
		STREAMING::REMOVE_IPL("prologue01z_lod");
		STREAMING::REMOVE_IPL("plg_02");
		STREAMING::REMOVE_IPL("prologue02");
		STREAMING::REMOVE_IPL("prologue02_lod");
		STREAMING::REMOVE_IPL("plg_03");
		STREAMING::REMOVE_IPL("prologue03");
		STREAMING::REMOVE_IPL("prologue03_lod");
		STREAMING::REMOVE_IPL("prologue03b");
		STREAMING::REMOVE_IPL("prologue03b_lod");
		STREAMING::REMOVE_IPL("prologue03_grv_dug");
		STREAMING::REMOVE_IPL("prologue03_grv_dug_lod");
		STREAMING::REMOVE_IPL("prologue_grv_torch");
		STREAMING::REMOVE_IPL("plg_04");
		STREAMING::REMOVE_IPL("prologue04");
		STREAMING::REMOVE_IPL("prologue04_lod");
		STREAMING::REMOVE_IPL("prologue04b");
		STREAMING::REMOVE_IPL("prologue04b_lod");
		STREAMING::REMOVE_IPL("prologue04_cover");
		STREAMING::REMOVE_IPL("des_protree_end");
		STREAMING::REMOVE_IPL("des_protree_start");
		STREAMING::REMOVE_IPL("des_protree_start_lod");
		STREAMING::REMOVE_IPL("plg_05");
		STREAMING::REMOVE_IPL("prologue05");
		STREAMING::REMOVE_IPL("prologue05_lod");
		STREAMING::REMOVE_IPL("prologue05b");
		STREAMING::REMOVE_IPL("prologue05b_lod");
		STREAMING::REMOVE_IPL("plg_06");
		STREAMING::REMOVE_IPL("prologue06");
		STREAMING::REMOVE_IPL("prologue06_lod");
		STREAMING::REMOVE_IPL("prologue06b");
		STREAMING::REMOVE_IPL("prologue06b_lod");
		STREAMING::REMOVE_IPL("prologue06_int");
		STREAMING::REMOVE_IPL("prologue06_int_lod");
		STREAMING::REMOVE_IPL("prologue06_pannel");
		STREAMING::REMOVE_IPL("prologue06_pannel_lod");
		STREAMING::REMOVE_IPL("prologue_m2_door");
		STREAMING::REMOVE_IPL("prologue_m2_door_lod");
		STREAMING::REMOVE_IPL("plg_occl_00");
		STREAMING::REMOVE_IPL("prologue_occl");
		STREAMING::REMOVE_IPL("plg_rd");
		STREAMING::REMOVE_IPL("prologuerd");
		STREAMING::REMOVE_IPL("prologuerdb");
		STREAMING::REMOVE_IPL("prologuerd_lod");
		GameFunctions::MinimapNotification("North Yankton IPL unloaded");
	}
	if (GUI::Option("Load Heist Yacht", ""))
	{
		STREAMING::REQUEST_IPL("hei_yacht_heist");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
		STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
		STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
		STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
		GameFunctions::MinimapNotification("Heist Yacht IPL loaded");
	}
	if (GUI::Option("Unload Heist Yacht", ""))
	{
		STREAMING::REMOVE_IPL("hei_yacht_heist");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bar");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bedrm");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Bridge");
		STREAMING::REMOVE_IPL("hei_yacht_heist_DistantLights");
		STREAMING::REMOVE_IPL("hei_yacht_heist_enginrm");
		STREAMING::REMOVE_IPL("hei_yacht_heist_LODLights");
		STREAMING::REMOVE_IPL("hei_yacht_heist_Lounge");
		GameFunctions::MinimapNotification("Heist Yacht IPL unloaded");
	}
	if (GUI::Option("Load Destroyed hospital", ""))
	{
		STREAMING::REQUEST_IPL("RC12B_Destroyed");
		STREAMING::REQUEST_IPL("RC12B_HospitalInterior");
		GameFunctions::MinimapNotification("Destroyed Hospital IPL Loaded");
	}
	if (GUI::Option("Unload Destroyed hospital", ""))
	{
		STREAMING::REMOVE_IPL("RC12B_Destroyed");
		STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
		GameFunctions::MinimapNotification("Destroyed Hospital IPL unloaded");
	}
	if (GUI::Option("Load Jewelry Store", ""))
	{
		STREAMING::REQUEST_IPL("post_hiest_unload");
		STREAMING::REMOVE_IPL("jewel2fake");
		STREAMING::REMOVE_IPL("bh1_16_refurb");
		GameFunctions::MinimapNotification("Jewelry Store IPL loaded");
	}
	if (GUI::Option("Unload Jewelry Store", ""))
	{
		STREAMING::REMOVE_IPL("post_hiest_unload");
		GameFunctions::MinimapNotification("Jewelry Store IPL unloaded");
	}
	if (GUI::Option("Load Morgue", ""))
	{
		STREAMING::REQUEST_IPL("Coroner_Int_on");
		GameFunctions::MinimapNotification("Morgue IPL loaded");
	}
	if (GUI::Option("Unload Morgue", ""))
	{
		STREAMING::REMOVE_IPL("Coroner_Int_on");
		GameFunctions::MinimapNotification("Morgue IPL unloaded");
	}
	if (GUI::Option("Load Cargoship", ""))
	{
		STREAMING::REQUEST_IPL("cargoship");
		GameFunctions::MinimapNotification("Cargoship IPL loaded");
	}
	if (GUI::Option("Unload Cargoship", ""))
	{
		STREAMING::REMOVE_IPL("cargoship");
		GameFunctions::MinimapNotification("Cargoship IPL unloaded");
	}
}