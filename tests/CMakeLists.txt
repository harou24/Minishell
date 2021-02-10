cmake_minimum_required(VERSION 3.5)
project(Unittests.bin)
Include(FetchContent)

AUX_SOURCE_DIRECTORY(./ SRC)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2)
