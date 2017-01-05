#include "chromietabs/sessionreader.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <Current Session File>" << std::endl;
        return EXIT_FAILURE;
    }

    ChromieTabs::SessionReader reader(argv[1]);

    std::cout << "Windows count: " << reader.get_window_ids().size() << std::endl;

    for (auto wnd_id : reader.get_window_ids())
    {
        for (auto url : reader.get_window_urls(wnd_id))
        {
            std::cout << "[Window " << wnd_id << "] Url: " << url << std::endl;
        }
    }

    std::cout << "Current window: " << reader.get_current_window_id() << std::endl;
    std::cout << "Current tab ID: " << reader.get_current_tab_id(reader.get_current_window_id()) << std::endl;
    std::cout << "Current URL: " << reader.get_current_url(reader.get_current_tab_id(reader.get_current_window_id())) << std::endl;

    return EXIT_SUCCESS;
}
