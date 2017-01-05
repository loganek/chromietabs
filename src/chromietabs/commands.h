#ifndef CHROMIETABS_COMMANDS_H
#define CHROMIETABS_COMMANDS_H

#include <chromietabs/rawcommand.h>

#include <string>

namespace ChromieTabs
{

enum class CommandType : std::uint8_t
{
    SET_TAB_WINDOW = 0,
    SET_TAB_INDEX_IN_WINDOW = 2,
    TAB_NAVIGATION_PATH_PRUNED_FROM_BACK = 5,
    UPDATE_TAB_NAVIGATION = 6,
    SET_SELECTED_NAVIGATION_INDEX = 7,
    SET_SELECTED_TAB_IN_INDEX = 8,
    SET_WINDOW_TYPE = 9,
    TAB_NAVIGATION_PATH_PRUNED_FROM_FRONT = 11,
    SET_PINNED_STATE = 12,
    SET_EXTENSION_APP_ID = 13,
    SET_WINDOW_BOUNDS3 = 14,
    SET_WINDOW_APP_NAME = 15,
    TAB_CLOSED = 16,
    WINDOW_CLOSED = 17
};

class Command
{
protected:
    const CommandType type;
    const content_t content;

public:
    virtual ~Command() {}
    Command(const RawCommand &raw_cmd) : type(static_cast<CommandType>(raw_cmd.type)), content(raw_cmd.content) {}

    CommandType get_command_type() const { return type; }
};

class PairStructure
{
protected:
    std::int32_t first;
    std::int32_t second;

public:
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
