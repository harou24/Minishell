FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.4)
FetchContent_MakeAvailable(Catch2)

## All unittests
set (TEST "test-all")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${TEST}.bin ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Lexer unittest
set (TEST "test-lexer")
set (SRC_LIST "src/lexer.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Journal unittest
set (TEST "test-journal")
set (SRC_LIST "src/journal.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Token unittest
set (TEST "test-token")
set (SRC_LIST "src/token.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Directory unittest
set (TEST "test-directory")
set (SRC_LIST "src/directory.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Prompt unittest
set (TEST "test-prompt")
set (SRC_LIST "src/prompt.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)
