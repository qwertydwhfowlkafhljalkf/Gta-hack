#include "../Header/Cheat Functions/FiberMain.h"

using namespace Cheat;
int ChangeSessionInteger = 0;
void GUI::Submenus::Session()
{
	GUI::Title("Session");
	GUI::MenuOption("Chat", SessionChat);
	std::string JoinChangeSessionString;
	if (GUI::StringVector(NETWORK::NETWORK_IS_SESSION_STARTED() ? "Change Session" : "Join Session", { "Join Public", "New Public", "Closed Crew", "Crew", "Closed Friend", "Solo", "Invite Only" }, ChangeSessionInteger, "", SELECTABLE_DISABLE_SAVE))
	{
		SessionTypes SetType;
		if (ChangeSessionInteger == 0)
		{
			SetType = SessionTypeJoinPublic;
		}
		else if (ChangeSessionInteger == 1)
		{
			SetType = SessionTypeNewPublic;
		}
		else if (ChangeSessionInteger == 2)
		{
			SetType = SessionTypeClosedCrew;
		}
		else if (ChangeSessionInteger == 3)
		{
			SetType = SessionTypeCrew;
		}
		else if (ChangeSessionInteger == 4)
		{
			SetType = SessionTypeClosedFriend;
		}
		else if (ChangeSessionInteger == 5)
		{
			SetType = SessionTypeSolo;
		}
		else if (ChangeSessionInteger == 6)
		{
			SetType = SessionTypeInviteOnly;
		}
		GameFunctions::ChangeGTAOSessionType(SetType);
	}
	if (GUI::Option("Join Session Containing Friends", "Searches for and joins a game session with one or more friends"))
	{
		GameFunctions::ChangeGTAOSessionType(SessionTypeFindFriend);
	}
	if (GUI::Option("Join Session Containing Crew Members", "Searches for and joins a game with one or more crew members"))
	{
		GameFunctions::ChangeGTAOSessionType(SessionTypeJoinCrew);
	}
}