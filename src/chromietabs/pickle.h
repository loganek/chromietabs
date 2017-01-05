#ifndef CHROMIETABS_PICKLE_H
#define CHROMIETABS_PICKLE_H

#include <chromietabs/rawcommand.h>

#include <string>

namespace ChromieTabs
{

class Pickle
{
    content_t::value_type *raw_ptr;
    std::int32_t payload_size;

public:
    Pickle(const content_t &content)
        : raw_ptr(const_cast<content_t::value_type*>(content.data()))
    {
        payload_size = *reinterpret_cast<const std::int32_t*>(content.data());
    }

    class Iterator
    {
        content_t::value_type *raw_ptr;
        content_t::value_type *raw_ptr_end;
        std::size_t pos = 0;

        static std::size_t align_int(std::size_t i, int alignment)
        {
            return i + (alignment - (i % alignment)) % alignment;
        }

        template<typename Type>
        inline const content_t::value_type* get_current_pointer_and_advance();

        const content_t::value_type* get_current_pointer_and_advance(int num_bytes);

        template <typename Type>
        inline bool read_builtin_type(Type& result);

    public:
        Iterator(const Pickle *pickle);

        int read_int(int &val);
        int read_int32(std::int32_t &val);
        bool read_string(std::string &val);
    };

    Iterator get_iterator() const { return Iterator(this); }
};


}

#endif // CHROMIETABS_PICKLE_H
