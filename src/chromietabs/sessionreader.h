#ifndef CHROMIETABS_SESSIONREADER_H
#define CHROMIETABS_SESSIONREADER_H

#include <chromietabs/commands.h>

#include <memory>

namespace ChromieTabs
{

class SessionReader
{
    std::vector<std::shared_ptr<Command>> commands;

public:
    SessionReader(const std::string &file_name);
    virtual ~SessionReader() {}

    std::vector<std::shared_ptr<Command>> get_commands() const { return commands; }
};

}

#endif // CHROMIETABS_SESSIONREADER_H
