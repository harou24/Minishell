# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    CMakeLists.txt                                     :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/13 21:15:57 by sverschu      #+#    #+#                  #
#    Updated: 2021/04/13 21:15:58 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.4
  GIT_PROGRESS   TRUE
  USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_FILES src/*.cpp)

foreach(SRC_FILE ${TEST_FILES})
	get_filename_component(TEST ${SRC_FILE} NAME)
	
	add_executable(${TEST}.bin ${SRC_FILE})
	target_compile_features(${TEST}.bin PRIVATE cxx_std_17)
	target_link_libraries(${TEST}.bin PRIVATE Catch2::Catch2WithMain)
  	target_link_libraries(${TEST}.bin PRIVATE	minishell
												ft
												vector
												hashmap
												gnl
												printf
												pair)
	add_test(NAME ${TEST}
			COMMAND ${TEST}.bin)
endforeach(SRC_FILE)
