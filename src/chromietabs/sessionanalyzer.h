#ifndef CHROMIETABS_SESSIONANALYZER_H
#define CHROMIETABS_SESSIONANALYZER_H

#include <chromietabs/sessionreader.h>

#include <memory>
#include <unordered_map>

namespace ChromieTabs
{

/**
 * @brief The NavigationEntry struct represents single navigation entry.
 */
struct NavigationEntry
{
    /**
     * Navigation URL.
     */
    std::string url;
    /**
     * Navigation window title.
     */
    std::u16string title;
};

/**
 * @brief The TabInfo struct is a helper data structure for representing Tab.
 */
struct TabInfo
{
    /**
     * Tab identifier.
     */
    std::int32_t id = -1;
    /**
     * Identifier of the parent window.
     */
    std::int32_t window_id = -1;
    /**
     * Tab index in a parent window.
     */
    std::int32_t index_in_window = -1;
    /**
     * Active navigation index in a tab.
     */
    std::int32_t current_navigation_index = -1;
    /**
     * @brief Collection of tab navigations.
     */
    std::unordered_map<std::int32_t, NavigationEntry> navigations;

    /**
     * @brief Gets a current navigation entry of the tab.
     * @return The navigation entry.
     * @throw std::out_of_range if current navigation doesn't exist in the tab.
     */
    const NavigationEntry& get_current_navigation_entry() const;
};

/**
 * @brief The SessionAnalyzer class is responsible for analyzing sequence of Session commands.
 */
class SessionAnalyzer
{
    std::unordered_map<std::int32_t, TabInfo> tabs;
    std::unordered_map<std::int32_t, std::int32_t> current_tab_in_window;

    std::int32_t current_window_id = - 1;

    void analyze_command(const std::shared_ptr<Command> &cmd);

public:
    /**
     * @brief Initializes the object.
     * @param reader A Session reader.
     */
    SessionAnalyzer(const SessionReader &reader);
    virtual ~SessionAnalyzer() {}

    /**
     * @brief Gets an identifier of currently active window.
     * @return The window identifier.
     */
    std::int32_t get_current_window_id() const { return current_window_id; }

    /**
     * @brief Gets currently active tab in a specific window.
     * @param window_id The window identifier.
     * @return The tab.
     * @throw std::out_of_range if current tab doesn't exist in the window.
     */
    const TabInfo& get_current_tab(std::int32_t window_id) const;

    /**
     * @brief Gets a collection of identifiers of the open windows.
     * @return The collection of open window identifiers.
     */
    std::vector<std::int32_t> get_window_ids() const;

    /**
     * @brief Gets a collection of currently open navigation entries in the specific window.
     * @param window_id The window identifier.
     * @return The collection of navigation entries.
     */
    std::vector<NavigationEntry> get_window_navigation_entries(std::int32_t window_id) const;
};

}

/*! A ChromieTabs::SessionAnalyzer example.
 * @example example/main.cc
 */

#endif // CHROMIETABS_SESSIONANALYZER_H
