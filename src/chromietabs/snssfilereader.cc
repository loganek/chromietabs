#include "snssfilereader.h"

#include <fstream>

namespace ChromieTabs
{

SNSSFileReader::SNSSFileReader(const std::string &file_name)
{
    load_raw_commands(file_name);
}

void SNSSFileReader::load_raw_commands(const std::string &file_name)
{
    raw_commands.clear();
    is.open(file_name, std::ios::binary);

    if (!is.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }

    auto file_size = get_file_size();

    check_signature();

    std::int32_t version;
    is.read(reinterpret_cast<char*>(&version), sizeof(version));

    while (is.tellg() < file_size)
    {
        std::int16_t size;
        is.read(reinterpret_cast<char*>(&size), sizeof(size));

        RawCommand cmd;
        cmd.content.resize(size);
        is.read(reinterpret_cast<char*>(&cmd.type), sizeof(cmd.type));
        is.read(reinterpret_cast<char*>(cmd.content.data()), size - sizeof(cmd.type));
        raw_commands.push_back(cmd);
    }

    is.close();
}

std::ifstream::pos_type SNSSFileReader::get_file_size()
{
    is.seekg(0, std::ios::end);
    std::size_t file_size = is.tellg();
    is.seekg(0, std::ios::beg);

    return file_size;
}

void SNSSFileReader::check_signature()
{
    std::int32_t signature;
    is.read(reinterpret_cast<char*>(&signature), sizeof(signature));

    if (signature != snss_magic)
    {
        throw std::runtime_error("invalid SNSS file signature");
    }
}

std::vector<RawCommand> SNSSFileReader::get_raw_commands() const
{
    return raw_commands;
}

}
