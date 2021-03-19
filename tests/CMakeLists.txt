FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.4)
FetchContent_MakeAvailable(Catch2)


#### Combined unittest

if((CMAKE_PROJECT_NAME STREQUAL minishell OR MODERN_CMAKE_BUILD_TESTING))
  set (TEST "test-all")
  file(GLOB SRC_LIST CONFIGURE_DEPENDS "src/*.cpp")
  
  add_executable(${TEST}.bin ${SRC_LIST})
  target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
  target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
  target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
  add_test(NAME ${TEST}
  		COMMAND ${TEST}.bin)
endif()

#### Individual unittests

## Lexer unittest
set (TEST "test-lexer")
set (SRC_LIST "src/lexer.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Parser unittest
set (TEST "test-parser")
set (SRC_LIST "src/parser.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Journal unittest
set (TEST "test-journal")
set (SRC_LIST "src/journal.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Token unittest
set (TEST "test-token")
set (SRC_LIST "src/token.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Bash symbols unittest
set (TEST "test-bash_sym")
set (SRC_LIST "src/bash_sym.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Bash pattern unittest
set (TEST "test-bash_pattern")
set (SRC_LIST "src/bash_pattern.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)
    
## Filesystem traversal unittest
set (TEST "test-filesystem_traversal")
set (SRC_LIST "src/filesystem_traversal.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Prompt unittest
set (TEST "test-prompt")
set (SRC_LIST "src/prompt.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Env unittest
set (TEST "test-env")
set (SRC_LIST "src/env.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Env Singleton unittest
set (TEST "test-env_singleton")
set (SRC_LIST "src/env_singleton.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)

## Path unittest
set (TEST "test-path")
set (SRC_LIST "src/path.cpp")

add_executable(${TEST}.bin ${MAIN} ${SRC_LIST})
target_compile_features(${TEST}.bin PRIVATE cxx_std_14)
target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST}.bin PRIVATE minishell ft vector hashmap gnl printf pair)
add_test(NAME ${TEST}
		COMMAND ${TEST}.bin)
