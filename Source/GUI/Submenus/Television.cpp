#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
void GUI::Submenus::Television()
{
	GUI::Title("Television");
	GUI::Toggle("Draw TV", CheatFeatures::ShowTVBool, "");
	GUI::Break("Playlist", SELECTABLE_CENTER_TEXT);
	for (auto& pl : GameArrays::TelevisionPlaylists)
	{
		if (GUI::Option(pl.first, ""))
		{
			//GRAPHICS::_IS_TV_PLAYLIST_ITEM_PLAYING(80996397);
			GRAPHICS::SET_TV_CHANNEL(-1);
			GRAPHICS::SET_TV_CHANNEL_PLAYLIST(0, pl.second.c_str(), true);
			GRAPHICS::SET_TV_CHANNEL(0);
		}
	}
}