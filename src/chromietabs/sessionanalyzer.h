#ifndef CHROMIETABS_SESSIONANALYZER_H
#define CHROMIETABS_SESSIONANALYZER_H

#include <chromietabs/sessionreader.h>

#include <memory>
#include <unordered_map>

namespace ChromieTabs
{

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
    std::unordered_map<std::int32_t, std::string> navigations;
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
     * @brief Gets currently active tab identifier in a specific window.
     * @param window_id The window identifier.
     * @return The tab identifier.
     */
    std::int32_t get_current_tab_id(std::int32_t window_id) const;

    /**
     * @brief Gets URL address of the specified tab.
     * @param tab_id The tab identifier.
     * @return The URL address.
     */
    std::string get_current_url(std::int32_t tab_id) const;

    /**
     * @brief Gets a collection of identifiers of the opened windows.
     * @return The collection of opened window identifiers.
     */
    std::vector<std::int32_t> get_window_ids() const;

    /**
     * @brief Gets a collection of currently opened URL addresses in the specific window.
     * @param window_id The window identifier.
     * @return The collection of URLs.
     */
    std::vector<std::string> get_window_urls(std::int32_t window_id) const;
};

}

#endif // CHROMIETABS_SESSIONANALYZER_H
