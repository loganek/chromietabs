#ifndef CHROMIETABS_SESSIONREADER_H
#define CHROMIETABS_SESSIONREADER_H

#include <chromietabs/commands.h>

#include <memory>
#include <unordered_map>

namespace ChromieTabs
{

struct TabInfo
{
    std::int32_t id = -1;
    std::int32_t window_id = -1;
    std::int32_t index_in_window = -1;
    std::int32_t current_navigation_index = -1;
    std::unordered_map<std::int32_t, std::string> navigations;
};

class SessionReader
{
    std::vector<std::shared_ptr<Command>> commands;

    std::unordered_map<std::int32_t, TabInfo> tabs;
    std::unordered_map<std::int32_t, std::int32_t> current_tab_in_window;

    std::int32_t current_window_id = - 1;

    void analyze_commands();

public:
    SessionReader(const std::string &file_name);

    std::int32_t get_current_window_id() const { return current_window_id; }
    std::int32_t get_current_tab_id(std::int32_t window_id) const;
    std::string get_current_url(std::int32_t tab_id) const;
    std::vector<std::int32_t> get_window_ids() const;
    std::vector<std::string> get_window_urls(std::int32_t window_id) const;
};

}

#endif // CHROMIETABS_SESSIONREADER_H
