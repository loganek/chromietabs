#ifndef CHROMIETABS_PICKLE_H
#define CHROMIETABS_PICKLE_H

#include <chromietabs/rawcommand.h>

#include <string>

namespace ChromieTabs
{

/**
 * @brief The Pickle class provides methods for reading data from binary files.
 *
 * See: https://chromium.googlesource.com/chromium/src/+/master/base/pickle.h
 */
class Pickle
{
    content_t::value_type *raw_ptr;
    std::int32_t payload_size;

public:
    /**
     * @brief Initializes the object.
     * @param content A binary data.
     */
    Pickle(const content_t &content)
        : raw_ptr(const_cast<content_t::value_type*>(content.data()))
    {
        payload_size = *reinterpret_cast<const std::int32_t*>(content.data());
    }

    /**
     * @brief The Iterator class is an iterator class for a Pickle object.
     */
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
        /**
         * @brief Initializes the object.
         * @param pickle A pickle.
         */
        Iterator(const Pickle *pickle);

        /**
         * @brief Reads int value from the Pickle object.
         * @param val An output variable.
         * @return True, if read succeeded; otherwise, false.
         */
        bool read_int(int &val);

        /**
         * @brief Reads int32 value from the Pickle object.
         * @param val An output variable.
         * @return True, if read succeeded; otherwise, false.
         */
        bool read_int32(std::int32_t &val);

        /**
         * @brief Reads string value from the Pickle object.
         * @param val An output variable.
         * @return True, if read succeeded; otherwise, false.
         */
        bool read_string(std::string &val);
    };

    /**
     * @brief Gets an iterator for the object.
     * @return The iterator.
     */
    Iterator get_iterator() const { return Iterator(this); }
};


}

#endif // CHROMIETABS_PICKLE_H
