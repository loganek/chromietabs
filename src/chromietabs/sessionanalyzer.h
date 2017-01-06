#ifndef CHROMIETABS_SESSIONANALYZER_H
#define CHROMIETABS_SESSIONANALYZER_H

#include <chromietabs/sessionreader.h>

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

class SessionAnalyzer
{
    std::unordered_map<std::int32_t, TabInfo> tabs;
    std::unordered_map<std::int32_t, std::int32_t> current_tab_in_window;

    std::int32_t current_window_id = - 1;

    void analyze_command(const std::shared_ptr<Command> &cmd);

public:
    SessionAnalyzer(const SessionReader &reader);
    virtual ~SessionAnalyzer() {}

    std::int32_t get_current_window_id() const { return current_window_id; }
    std::int32_t get_current_tab_id(std::int32_t window_id) const;
    std::string get_current_url(std::int32_t tab_id) const;
    std::vector<std::int32_t> get_window_ids() const;
    std::vector<std::string> get_window_urls(std::int32_t window_id) const;
};

}

#endif // CHROMIETABS_SESSIONANALYZER_H
