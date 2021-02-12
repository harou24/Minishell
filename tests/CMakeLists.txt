cmake_minimum_required(VERSION 3.5)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

## All unittests
set (TEST "all")
AUX_SOURCE_DIRECTORY(src/ SRC)
add_executable(${TEST}.bin ${SRC})
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2)
target_link_libraries(${TEST}.bin PUBLIC minishell ft hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Specific unittests
set (TEST "lexer")
add_executable(${TEST}.bin src/main.cpp src/lexer.cpp)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2)
target_link_libraries(${TEST}.bin PUBLIC minishell ft hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)
