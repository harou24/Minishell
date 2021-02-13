add_executable(minishell-bin minishell.c)

target_link_libraries(minishell-bin PRIVATE minishell ft hashmap vector)
set_target_properties(minishell-bin PROPERTIES OUTPUT_NAME minishell)
