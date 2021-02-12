cmake_minimum_required(VERSION 3.5)
project(minishell)

include(CTest)

if(BUILD_TESTING)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address")
endif()

add_subdirectory(lib/libft)
add_subdirectory(lib/libvector)
add_subdirectory(lib/libhashmap)

if(BUILD_TESTING)
	add_subdirectory(tests)
endif()

include_directories(inc
					lib/libft
					lib/libvector
					lib/libhashmap
					)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic")

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")

AUX_SOURCE_DIRECTORY(src/ MINISHELL_SRC) 
add_executable(minishell-bin ${MINISHELL_SRC})
target_link_libraries(minishell-bin PUBLIC ft vector hashmap)
set_target_properties(minishell-bin PROPERTIES OUTPUT_NAME minishell)


list(REMOVE_ITEM ${MINISHELL_SRC} "main.c")
add_library(minishell STATIC ${MINISHELL_SRC})
target_include_directories(minishell PUBLIC inc)
target_link_libraries(minishell ft vector hashmap)
