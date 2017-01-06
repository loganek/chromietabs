#ifndef CHROMIETABS_PATHUTILS_H
#define CHROMIETABS_PATHUTILS_H

#include <string>

namespace ChromieTabs
{

enum class BrowserBuild
{
    CHROMIUM,
    GOOGLE_CHROME
};

class PathUtils
{
    PathUtils() = delete;
    PathUtils(const PathUtils&) = delete;
    PathUtils(PathUtils &&) = delete;
    PathUtils& operator=(const PathUtils &) = delete;

public:
    static std::string get_current_session_path(BrowserBuild browser);
};

}

#endif // CHROMIETABS_PATHUTILS_H
