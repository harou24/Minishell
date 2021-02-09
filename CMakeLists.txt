cmake_minimum_required(VERSION 3.5)
project(minishell)

add_subdirectory(lib/libft)
add_subdirectory(lib/libvector)
add_subdirectory(lib/libhashmap)
include_directories(inc lib/libft lib/libvector lib/libhashmap)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -pedantic")

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic")

AUX_SOURCE_DIRECTORY(src/ MINISHELL_SRC) 
add_executable(minishell ${MINISHELL_SRC})

target_link_libraries(minishell PUBLIC ft vector hashmap)
