add_executable(minishell-bin minishell.c)
target_link_libraries(minishell-bin PRIVATE minishell ft hashmap vector)
set_target_properties(minishell-bin PROPERTIES OUTPUT_NAME minishell)

# standalone test libraries
if(BUILD_TESTING)
	add_executable(torture-bash_sym.bin torture-bash_sym.c)
	target_link_libraries(torture-bash_sym.bin PRIVATE minishell ft hashmap vector)
	
	add_executable(torture-lexer.bin torture-lexer.c)
	target_link_libraries(torture-lexer.bin PRIVATE minishell ft hashmap vector)

	add_executable(torture-parser.bin torture-parser.c)
	target_link_libraries(torture-parser.bin PRIVATE minishell ft hashmap vector)

	add_executable(torture-bash_pattern.bin torture-bash_pattern.c)
	target_link_libraries(torture-bash_pattern.bin PRIVATE minishell ft hashmap vector)

	add_executable(prompt.bin prompt.c)
	target_link_libraries(prompt.bin PRIVATE minishell ft hashmap vector)
endif()
