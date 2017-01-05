#ifndef CHROMIETABS_FILEPARSER_H
#define CHROMIETABS_FILEPARSER_H

#include <chromietabs/rawcommand.h>

#include <string>
#include <fstream>

namespace ChromieTabs
{

class FileParser
{
    std::vector<RawCommand> raw_commands;
    std::string file_name;
    std::ifstream is;

    void check_signature();
    std::size_t get_file_size();

    const std::int32_t snss_magic = 0x53534E53;

public:
    FileParser(const std::string &file_name);

    void load_raw_commands();

    std::vector<RawCommand> get_raw_commands() const;
};

}

#endif // FILEPARSER_H
