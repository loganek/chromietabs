#include "sessionanalyzer.h"
#include "sessionreader.h"

#include <algorithm>
#include <stdexcept>

namespace ChromieTabs
{

SessionAnalyzer::SessionAnalyzer(const SessionReader &reader)
{
    for (const auto &cmd : reader.get_commands())
    {
        analyze_command(cmd);
    }
}

void SessionAnalyzer::analyze_command(const std::shared_ptr<Command> &cmd)
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
        tabs[command->get_tab_id()].navigations[command->get_navigation_index()] = {command->get_url(), command->get_title()};
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
        break;
    default:
        break;
    }
}


std::vector<std::int32_t> SessionAnalyzer::get_window_ids() const
{
    std::vector<std::int32_t> keys;
    keys.reserve(current_tab_in_window.size());

    for(const auto& kv : current_tab_in_window)
    {
        keys.push_back(kv.first);
    }
    return keys;
}

std::vector<NavigationEntry> SessionAnalyzer::get_window_navigation_entries(std::int32_t window_id) const
{
    std::vector<NavigationEntry> urls;

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

const TabInfo& SessionAnalyzer::get_current_tab(std::int32_t window_id) const
{
    const auto& current_tab_id = current_tab_in_window.at(window_id);

    auto it = std::find_if(tabs.begin(), tabs.end(), [window_id, current_tab_id, this] (const decltype(tabs)::value_type& tab) {
        return tab.second.index_in_window == current_tab_id && tab.second.window_id == window_id;
    });

    if (it == tabs.end())
        throw std::out_of_range("get_current_tab");

    return it->second;
}

const NavigationEntry& TabInfo::get_current_navigation_entry() const
{
    return navigations.at(current_navigation_index);
}

}
