#ifndef CHROMIETABS_RAWCOMMAND_H
#define CHROMIETABS_RAWCOMMAND_H

#include <cstdint>
#include <vector>

namespace ChromieTabs
{

using content_t = std::vector<std::uint8_t>;

struct RawCommand
{
    std::uint8_t type;
    content_t content;
};

}

#endif // CHROMIETABS_RAWCOMMAND_H
