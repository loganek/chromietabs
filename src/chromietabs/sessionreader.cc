#include "sessionreader.h"
#include "fileparser.h"
#include "commandfactory.h"

namespace ChromieTabs
{

SessionReader::SessionReader(const std::string &file_name)
{
    FileParser parser(file_name);

    parser.load_raw_commands();

    for (const auto &raw_cmd : parser.get_raw_commands())
    {
        auto cmd = CommandFactory::create_command(raw_cmd);
        if (cmd)
        {
            commands.push_back(cmd);
        }
    }
}

}
