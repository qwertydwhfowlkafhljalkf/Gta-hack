#pragma once

//Offsets
#define OFFSET_PLAYER					0x08
#define OFFSET_PLAYER_INFO				0x10C8
#define OFFSET_PLAYER_INFO_EXTERNAL_IP	0x6C
#define OFFSET_PLAYER_INFO_FRAMEFLAGS	0x219

//Globals (These change with each major patch, see <Project Root>/Resources/TSE Globals folder for information on function location within game scripts)
#define GLOBAL_PLAYER_PICTURE_INDEX		1656661
#define GLOBAL_LEVEL_TO_RP				294354
#define GLOBAL_DISABLE_MOBILE_PHONE		19937
const int GLOBAL_SNOW[]					= { 262145, 4723 };
const int GLOBAL_BULLSHARKTESTOSTERONE[] = { 2703660, 3576 };

//Script Events
#define TSE_KICK_TO_SP					998716537
#define TSE_CEO_KICK					248967238
#define TSE_CEO_BAN						-764524031
#define TSE_PROPERTY_TELEPORT			603406648
#define TSE_CAYO_PERICO_TELEPORT		-621279188