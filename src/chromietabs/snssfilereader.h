#ifndef CHROMIETABS_SNSSFILEREADER_H
#define CHROMIETABS_SNSSFILEREADER_H

#include <chromietabs/rawcommand.h>

#include <string>
#include <fstream>

namespace ChromieTabs
{

/**
 * @brief The SNSSFileReader class is responsible for reading raw commands from SNSS files.
 */
class SNSSFileReader
{
    std::vector<RawCommand> raw_commands;
    std::ifstream is;

    void check_signature();
    std::size_t get_file_size();

    const std::int32_t snss_magic = 0x53534E53;

    void load_raw_commands(const std::string &file_name);

public:
    /**
     * @brief Initializes an object.
     * @param file_name A file name that will be read.
     */
    SNSSFileReader(const std::string &file_name);

    /**
     * @brief Gets an array of raw commands.
     * @return An array containing raw commands.
     */
    std::vector<RawCommand> get_raw_commands() const;
};

}

#endif // CHROMIETABS_SNSSFILEREADER_H
