#include "pickle.h"

#include <cstring>

namespace ChromieTabs
{

Pickle::Iterator::Iterator(const Pickle *pickle)
    : raw_ptr(pickle->raw_ptr + sizeof(pickle->payload_size)),
      raw_ptr_end(pickle->raw_ptr + pickle->payload_size + sizeof(pickle->payload_size))
{}

template<typename Type>
const content_t::value_type* Pickle::Iterator::get_current_pointer_and_advance()
{
    const auto* current_ptr = raw_ptr;
    if (raw_ptr + sizeof(Type) > raw_ptr_end)
    {
        return nullptr;
    }
    if (sizeof(Type) < sizeof(std::uint32_t))
    {
        raw_ptr += align_int(sizeof(Type), sizeof(std::uint32_t));
    }
    else
    {
        raw_ptr += sizeof(Type);
    }
    return current_ptr;
}

const content_t::value_type* Pickle::Iterator::get_current_pointer_and_advance(int num_bytes)
{
    if (num_bytes < 0 || raw_ptr_end - raw_ptr < num_bytes)
    {
        return nullptr;
    }
    const auto* current_ptr = raw_ptr;
    raw_ptr += align_int(num_bytes, sizeof(std::uint32_t));
    return current_ptr;
}


template <typename Type>
bool Pickle::Iterator::read_builtin_type(Type& result)
{
    const auto* read_from = get_current_pointer_and_advance<Type>();
    if (!read_from)
    {
        return false;
    }
    if (sizeof(Type) > sizeof(std::int32_t))
    {
        std::memcpy(&result, read_from, sizeof(result));
    }
    else
    {
        result = *reinterpret_cast<const Type*>(read_from);
    }
    return true;
}

bool Pickle::Iterator::read_int(int &val)
{
    return read_builtin_type(val);
}

bool Pickle::Iterator::read_int32(std::int32_t &val)
{
    return read_builtin_type(val);
}

bool Pickle::Iterator::read_string(std::string &val)
{
    int str_len;
    if (!read_int(str_len))
    {
        return false;
    }
    const auto* read_from = get_current_pointer_and_advance(str_len);
    if (!read_from)
    {
        return false;
    }

    val.assign(reinterpret_cast<const char*>(read_from), str_len);
    return true;
}

}
