#include "pathutils.h"

#include <stdexcept>

namespace ChromieTabs
{

static std::string get_config_dir()
{
    const char *xdg_config_dir = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_dir != nullptr && xdg_config_dir[0] != 0)
    {
        return xdg_config_dir;
    }

    const char *home_dir = std::getenv("HOME");
    if (home_dir == nullptr || !home_dir[0])
    {
        throw std::runtime_error("Cannot read home directory");
    }

    return std::string(home_dir) + "/.config";
}

std::string PathUtils::get_current_session_path(BrowserType browser)
{
#ifndef __linux__
    throw std::runtime_error("The method is implemented only for linux platform");
#endif
    auto current_session_dir = get_config_dir() + "/";

    switch (browser) {
    case BrowserType::GOOGLE_CHROME:
        current_session_dir += "google-chrome";
        break;
    case BrowserType::CHROMIUM:
        current_session_dir += "chromium";
        break;
    }

    current_session_dir += "/Default/Current Session";

    return current_session_dir;
}

}
