#ifndef CHROMIETABS_PATHUTILS_H
#define CHROMIETABS_PATHUTILS_H

#include <string>

namespace ChromieTabs
{

/**
 * @brief The BrowserType enum represents supported browsers.
 */
enum class BrowserType
{
    CHROMIUM, /**< Chromium browser */
    GOOGLE_CHROME /**< Google Chrome */
};

/**
 * @brief The PathUtils class is an utility class for getting paths of the Chromium browser files.
 */
class PathUtils
{
    PathUtils() = delete;
    PathUtils(const PathUtils&) = delete;
    PathUtils(PathUtils &&) = delete;
    PathUtils& operator=(const PathUtils &) = delete;

public:
    /**
     * @brief Gets a path to a Current Session file.
     * @param browser A type of a browser.
     * @return A path to the Current Session file.
     */
    static std::string get_current_session_path(BrowserType browser);
};

}

/*! A ChromieTabs::PathUtils example.
 * @example src/readerapp/main.cc
 */

#endif // CHROMIETABS_PATHUTILS_H
