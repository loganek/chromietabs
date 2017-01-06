#ifndef CHROMIETABS_RAWCOMMAND_H
#define CHROMIETABS_RAWCOMMAND_H

#include <cstdint>
#include <vector>

namespace ChromieTabs
{

using content_t = std::vector<std::uint8_t>;

/**
 * @brief The RawCommand struct represents a data structure of the SNSS file.
 */
struct RawCommand
{
    /**
     * A command type.
     */
    std::uint8_t type;
    /**
     * A command content.
     */
    content_t content;
};

}

#endif // CHROMIETABS_RAWCOMMAND_H
