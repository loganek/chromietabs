/*
 * Example application that demonstrates how to use chromietabs library.
 * Program reads and displays information about currently open and active
 * tabs and windows of Google Chrome or Chromium application.
 */
#include <chromietabs/sessionanalyzer.h>
#include <chromietabs/pathutils.h>

#include <cstring>
#include <iostream>

static void print_usage(const char *app_name)
{
    std::cout << "Usage: " << app_name << " [FILE|OPTION]" << std::endl << std::endl
              << "FILE   Path to the Google Chrome / Chromium Session file" << std::endl << std::endl
              << "Available options:" << std::endl
              << "  -g, --google-chrome  use google-chrome Current Session file" << std::endl
              << "  -c, --chromium       use chromium Current Session file" << std::endl;
}

static std::string get_session_path(const std::string &arg)
{
    if (arg == "-g" || arg == "--google-chrome")
    {
        return ChromieTabs::PathUtils::get_current_session_path(ChromieTabs::BrowserType::GOOGLE_CHROME);
    }
    else if (arg == "-c" || arg == "--chromium")
    {
        return ChromieTabs::PathUtils::get_current_session_path(ChromieTabs::BrowserType::CHROMIUM);
    }
    else
    {
        return arg;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }

    std::string session_path = get_session_path(argv[1]);
    ChromieTabs::SessionAnalyzer analyzer{ChromieTabs::SessionReader(session_path)};

    std::cout << "Windows count: " << analyzer.get_window_ids().size() << std::endl;
    std::cout << "Current window: " << analyzer.get_current_window_id() << std::endl;
    std::cout << "Current tab ID: " << analyzer.get_current_tab_id(analyzer.get_current_window_id()) << std::endl;
    std::cout << "Current URL: " << analyzer.get_current_url(analyzer.get_current_tab_id(analyzer.get_current_window_id())) << std::endl;

    std::cout << "Tabs:" << std::endl;
    for (auto wnd_id : analyzer.get_window_ids())
    {
        for (auto url : analyzer.get_window_urls(wnd_id))
        {
            std::cout << "   [Window " << wnd_id << "] Url: " << url << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
