#include "version.hpp"

namespace Cheat
{
    const char* build_info::VersionString = "2.2.2.0";
    const int build_info::VersionInt = 2200;
    const char* build_info::BuildTime = __TIME__;
    const char* build_info::BuildDate = __DATE__;
}