#include <chromietabs/sessionanalyzer.h>

#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Current Session File>" << std::endl;
        return EXIT_FAILURE;
    }

    ChromieTabs::SessionAnalyzer analyzer{ChromieTabs::SessionReader(argv[1])};

    std::cout << "Windows count: " << analyzer.get_window_ids().size() << std::endl;

    for (auto wnd_id : analyzer.get_window_ids())
    {
        for (auto url : analyzer.get_window_urls(wnd_id))
        {
            std::cout << "[Window " << wnd_id << "] Url: " << url << std::endl;
        }
    }

    std::cout << "Current window: " << analyzer.get_current_window_id() << std::endl;
    std::cout << "Current tab ID: " << analyzer.get_current_tab_id(analyzer.get_current_window_id()) << std::endl;
    std::cout << "Current URL: " << analyzer.get_current_url(analyzer.get_current_tab_id(analyzer.get_current_window_id())) << std::endl;

    return EXIT_SUCCESS;
}
