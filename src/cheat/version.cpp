#include "version.hpp"
#include <vector>

namespace Cheat
{
    const char* build_info::VersionString = "2.2.1.3";
    const int build_info::VersionInt = 2213;
    const char* build_info::BuildTime = __TIME__;
    const char* build_info::BuildDate = __DATE__;
}