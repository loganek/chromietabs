#ifndef CHROMIETABS_COMMANDFACTORY_H
#define CHROMIETABS_COMMANDFACTORY_H

#include <chromietabs/commands.h>

#include <memory>

namespace ChromieTabs
{

/**
 * @brief The factory class for the Session commands.
 */
class CommandFactory
{
public:
    /**
     * @brief Creates an instance of the command from the RawCommand.
     * @param raw_cmd The raw command.
     * @return A shared pointer to the command.
     */
    static std::shared_ptr<Command> create_command(const RawCommand &raw_cmd);
};

}

#endif // CHROMIETABS_COMMANDFACTORY_H
