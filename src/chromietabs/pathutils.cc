#include "pathutils.h"

#include <stdexcept>
#include <filesystem>
#include <vector>
#include <algorithm>

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

static std::vector<std::string> find_session_files(const std::string directory_path)
{
    const std::string prefix = "Session_";
    std::vector<std::string> result;

    std::filesystem::path directory(directory_path);

    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        return result;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().filename().string().rfind(prefix, 0) == 0) {
            result.push_back(entry.path().filename().string());
        }
    }

    std::sort(result.rbegin(), result.rend());

   return result;
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

    current_session_dir += "/Default";
    if (std::filesystem::exists(current_session_dir + "Current Session")) {
        return current_session_dir + "Current Session";
    }

    current_session_dir += "/Sessions";
    auto session_files = find_session_files(current_session_dir);
    if (session_files.empty()) {
        throw std::runtime_error("Cannot find session file");
    }
    return current_session_dir + "/" + session_files[0];
}

}
