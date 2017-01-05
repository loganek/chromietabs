#ifndef CHROMIETABS_COMMANDFACTORY_H
#define CHROMIETABS_COMMANDFACTORY_H

#include <chromietabs/commands.h>

#include <memory>

namespace ChromieTabs
{

class CommandFactory
{
public:
    static std::shared_ptr<Command> create_command(const RawCommand &raw_cmd);
};

}

#endif // CHROMIETABS_COMMANDFACTORY_H
