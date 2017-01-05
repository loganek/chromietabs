#include "commandfactory.h"

namespace ChromieTabs
{

std::shared_ptr<Command> CommandFactory::create_command(const RawCommand &raw_cmd)
{
    CommandType type = static_cast<CommandType>(raw_cmd.type);

    switch (type)
    {
    case CommandType::SET_TAB_WINDOW:
        return std::make_shared<SetTabWindowCommand>(raw_cmd);
    case CommandType::SET_TAB_INDEX_IN_WINDOW:
        return std::make_shared<SetTabIndexInWindowCommand>(raw_cmd);
    case CommandType::UPDATE_TAB_NAVIGATION:
        return std::make_shared<UpdateTabNavigationCommand>(raw_cmd);
    case CommandType::SET_SELECTED_NAVIGATION_INDEX:
        return std::make_shared<SetSelectedNavigationIndexCommand>(raw_cmd);
    case CommandType::SET_SELECTED_TAB_IN_INDEX:
        return std::make_shared<SetSelectedTabInIndex>(raw_cmd);
    case CommandType::SET_WINDOW_BOUNDS3:
        return std::make_shared<SetWindowBounds3>(raw_cmd);
    case CommandType::TAB_CLOSED:
        return std::make_shared<TabClosedCommand>(raw_cmd);
    case CommandType::WINDOW_CLOSED:
        return std::make_shared<WindowClosedCommand>(raw_cmd);
    case CommandType::TAB_NAVIGATION_PATH_PRUNED_FROM_BACK:
    case CommandType::SET_WINDOW_TYPE:
    case CommandType::TAB_NAVIGATION_PATH_PRUNED_FROM_FRONT:
    case CommandType::SET_PINNED_STATE:
    case CommandType::SET_EXTENSION_APP_ID:
    case CommandType::SET_WINDOW_APP_NAME:
        return std::make_shared<Command>(raw_cmd);
    default:
        return std::shared_ptr<Command>();
    }
}

}

