cmake_minimum_required(VERSION 2.8.7)

project(chromietabs)

set(CHROMIETABS_VERSION 0.1)

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

set (CMAKE_CXX_STANDARD 17)

include_directories("${chromietabs_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(docs)
