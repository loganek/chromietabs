#ifndef CHROMIETABS_COMMANDS_H
#define CHROMIETABS_COMMANDS_H

#include <chromietabs/rawcommand.h>

#include <string>

namespace ChromieTabs
{

/**
 * @brief The Session command type enumeration.
 */
enum class CommandType : std::uint8_t
{
    SET_TAB_WINDOW = 0, /**< Set a tab in a window */
    SET_TAB_INDEX_IN_WINDOW = 2, /**< Set an index for a tab in a window */
    TAB_NAVIGATION_PATH_PRUNED_FROM_BACK = 5, /**< TODO */
    UPDATE_TAB_NAVIGATION = 6, /**< Update tab navigation details */
    SET_SELECTED_NAVIGATION_INDEX = 7, /**< Select index of navigation in a tab */
    SET_SELECTED_TAB_IN_INDEX = 8, /**< Select index of a tab in a window */
    SET_WINDOW_TYPE = 9, /**< Set window type */
    TAB_NAVIGATION_PATH_PRUNED_FROM_FRONT = 11, /**< TODO */
    SET_PINNED_STATE = 12, /**< Set pinned state */
    SET_EXTENSION_APP_ID = 13, /**< Set extension app ID */
    SET_WINDOW_BOUNDS3 = 14, /**< Set window parameters: position, size and state */
    SET_WINDOW_APP_NAME = 15, /**< Set window application name */
    TAB_CLOSED = 16, /**< Tab closed */
    WINDOW_CLOSED = 17 /**< Window closed */
};

/**
 * @brief The Command class is a base class for the Session commands
 */
class Command
{
protected:
    const CommandType type;
    const content_t content;

public:
    virtual ~Command() {}

    /**
     * @brief Initialize Command object from a raw command.
     * @param raw_cmd The raw command.
     */
    Command(const RawCommand &raw_cmd) : type(static_cast<CommandType>(raw_cmd.type)), content(raw_cmd.content) {}

    CommandType get_command_type() const { return type; }
};

/**
 * The PairStructure class is a helper class that represents data
 * data structure containig two int32 variables.
 */
class PairStructure
{
protected:
    std::int32_t first;
    std::int32_t second;

public:
    /**
     * @brief Initializes the object.
     * @param content A data buffer.
     */
    PairStructure(const content_t & content)
    {
        first = *(std::int32_t*)content.data();
        second = *(std::int32_t*)(content.data() + sizeof(first));
    }
};

class SetTabWindowCommand : public Command, public PairStructure
{
public:
    SetTabWindowCommand(const RawCommand &raw_cmd)
        : Command(raw_cmd), PairStructure(content)
    {}

    std::int32_t get_window_id() const { return first; }
    std::int32_t get_tab_id() const { return second; }
};

class SetTabIndexInWindowCommand : public Command, public PairStructure
{
public:
    SetTabIndexInWindowCommand(const RawCommand &raw_cmd)
        : Command(raw_cmd), PairStructure(content)
    {}

    std::int32_t get_tab_id() const { return first; }
    std::int32_t get_tab_index() const { return second; }
};

class SetSelectedNavigationIndexCommand : public Command, public PairStructure
{
public:
    SetSelectedNavigationIndexCommand(const RawCommand &raw_cmd)
        : Command(raw_cmd), PairStructure(content)
    {}

    std::int32_t get_tab_id() const { return first; }
    std::int32_t get_navigation_index() const { return second; }
};

class SetSelectedTabInIndex : public Command, public PairStructure
{
public:
    SetSelectedTabInIndex(const RawCommand &raw_cmd)
        : Command(raw_cmd), PairStructure(content)
    {}

    std::int32_t get_window_id() const { return first; }
    std::int32_t get_tab_index() const { return second; }
};

class SetWindowBounds3 : public Command
{
    std::int32_t window_id;
    std::int32_t x;
    std::int32_t y;
    std::int32_t width;
    std::int32_t height;
    std::int32_t state;

    std::int32_t read_int32(int offset) { return *reinterpret_cast<const std::int32_t*>(content.data() + offset); }

public:
    SetWindowBounds3(const RawCommand &raw_cmd)
        : Command(raw_cmd)
    {
        window_id = read_int32(0);
        x = read_int32(4);
        y = read_int32(8);
        width = read_int32(12);
        height = read_int32(16);
        state = read_int32(20);
    }

    std::int32_t get_window_id() const { return window_id; }
    std::int32_t get_x() const { return x; }
    std::int32_t get_y() const { return y; }
    std::int32_t get_width() const { return width; }
    std::int32_t get_height() const { return height; }
    std::int32_t get_state() const { return state; }
};

/**
 * The ClosedStructure struct is a helper data structure for
 * Closed commands.
 */
struct ClosedStructure
{
    std::int32_t id;
    std::int64_t closed_time;

public:
    ClosedStructure(const content_t & content)
    {
        id = *(std::int32_t*)content.data();
        closed_time = *(std::int64_t*)(content.data() + sizeof(id));
    }

    std::int32_t get_id() const { return id; }
    std::int64_t get_closed_time() const { return closed_time; }
};

class TabClosedCommand : public Command, public ClosedStructure
{
public:
    TabClosedCommand(const RawCommand &raw_cmd)
        : Command(raw_cmd), ClosedStructure(content)
    {}
};

class WindowClosedCommand : public Command, public ClosedStructure
{
public:
    WindowClosedCommand(const RawCommand &raw_cmd)
        : Command(raw_cmd), ClosedStructure(content)
    {}
};

class UpdateTabNavigationCommand : public Command
{
    std::string url;
    std::int32_t navigation_index;
    std::int32_t tab_id;

public:
    UpdateTabNavigationCommand(const RawCommand &raw_cmd);

    std::string get_url() const { return url; }
    std::int32_t get_navigation_index() const { return navigation_index; }
    std::int32_t get_tab_id() const { return tab_id; }
};


}

#endif // CHROMIETABS_COMMANDS_H
