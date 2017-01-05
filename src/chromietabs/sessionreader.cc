#include "sessionreader.h"
#include "fileparser.h"
#include "commandfactory.h"

namespace ChromieTabs
{

SessionReader::SessionReader(const std::string &file_name)
{
    FileParser parser(file_name);

    parser.load_raw_commands();

    for (const auto &raw_cmd : parser.get_raw_commands())
    {
        auto cmd = CommandFactory::create_command(raw_cmd);
        if (cmd)
        {
            commands.push_back(cmd);
        }
    }

    analyze_commands();
}

void SessionReader::analyze_commands()
{
    for (const auto &cmd : commands)
    {
        switch (cmd->get_command_type())
        {
        case CommandType::SET_WINDOW_BOUNDS3:
            current_window_id = std::static_pointer_cast<SetWindowBounds3>(cmd)->get_window_id();
            break;
        case CommandType::SET_TAB_WINDOW:
        {
            auto command = std::static_pointer_cast<SetTabWindowCommand>(cmd);
            tabs[command->get_tab_id()].id = command->get_tab_id();
            tabs[command->get_tab_id()].window_id = command->get_window_id();
        }
            break;
        case CommandType::SET_TAB_INDEX_IN_WINDOW:
        {
            auto command = std::static_pointer_cast<SetTabIndexInWindowCommand>(cmd);
            tabs[command->get_tab_id()].index_in_window = command->get_tab_index();
        }
            break;
        case CommandType::SET_SELECTED_TAB_IN_INDEX:
        {
            auto command = std::static_pointer_cast<SetSelectedTabInIndex>(cmd);
            current_tab_in_window[command->get_window_id()] = command->get_tab_index();
        }
            break;
        case CommandType::SET_SELECTED_NAVIGATION_INDEX:
        {
            auto command = std::static_pointer_cast<SetSelectedNavigationIndexCommand>(cmd);
            tabs[command->get_tab_id()].current_navigation_index = command->get_navigation_index();
        }
            break;
        case CommandType::UPDATE_TAB_NAVIGATION:
        {
            auto command = std::static_pointer_cast<UpdateTabNavigationCommand>(cmd);
            tabs[command->get_tab_id()].navigations[command->get_navigation_index()] = command->get_url();
        }
            break;
        case CommandType::TAB_CLOSED:
        {
            auto command = std::static_pointer_cast<TabClosedCommand>(cmd);
            auto wnd_it = current_tab_in_window.find(tabs[command->get_id()].window_id);
            if (wnd_it != current_tab_in_window.end() && wnd_it->second == tabs[command->get_id()].index_in_window)
            {
                wnd_it->second = -1;
            }
            tabs.erase(command->get_id());
        }
            break;
        case CommandType::WINDOW_CLOSED:
        {
            auto command = std::static_pointer_cast<WindowClosedCommand>(cmd);
            current_tab_in_window.erase(command->get_id());
            if (current_window_id == command->get_id())
            {
                current_window_id = -1;
            }
            auto it = tabs.begin();
            while (it != tabs.end())
            {
                if (it->second.window_id == command->get_id()) it = tabs.erase(it);
                else ++it;
            }
        }
        }
    }
}


std::vector<std::int32_t> SessionReader::get_window_ids() const
{
    std::vector<std::int32_t> keys;
    keys.reserve(current_tab_in_window.size());

    for(const auto& kv : current_tab_in_window)
    {
        keys.push_back(kv.first);
    }
    return keys;
}

std::vector<std::string> SessionReader::get_window_urls(std::int32_t window_id) const
{
    std::vector<std::string> urls;

    for(const auto& tab : tabs)
    {
        if (tab.second.window_id == window_id)
        {
            auto it = tab.second.navigations.find(tab.second.current_navigation_index);
            if (it != tab.second.navigations.end())
            {
                urls.push_back(it->second);
            }
        }
    }

    return urls;
}

std::int32_t SessionReader::get_current_tab_id(std::int32_t window_id) const
{
    auto it = current_tab_in_window.find(window_id);

    if (it == current_tab_in_window.end() || it->second == -1)
    {
        return -1;
    }

    for (const auto &tab : tabs)
    {
        if (tab.second.window_id == window_id && tab.second.index_in_window == it->second)
        {
            return tab.second.id;
        }
    }

    return -1;
}

std::string SessionReader::get_current_url(std::int32_t tab_id) const
{
    auto it = tabs.find(tab_id);

    if (it == tabs.end() || it->second.current_navigation_index == -1)
    {
        return "";
    }

    auto navigation_it = it->second.navigations.find(it->second.current_navigation_index);

    return navigation_it != it->second.navigations.end() ? navigation_it->second : "";
}

}
