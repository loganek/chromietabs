#ifndef CHROMIETABS_SESSIONREADER_H
#define CHROMIETABS_SESSIONREADER_H

#include <chromietabs/commands.h>

#include <memory>

namespace ChromieTabs
{

/**
 * @brief The SessionReader class reads the Session file.
 */
class SessionReader
{
    std::vector<std::shared_ptr<Command>> commands;

public:
    /**
     * @brief Initializes the object.
     * @param file_name The SNSS file name.
     */
    SessionReader(const std::string &file_name);
    virtual ~SessionReader() {}

    /**
     * @brief Gets an array of Session commands.
     * @return An array of Session commands.
     */
    std::vector<std::shared_ptr<Command>> get_commands() const { return commands; }
};

}

#endif // CHROMIETABS_SESSIONREADER_H
