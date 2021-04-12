#include <catch2/catch.hpp>

extern "C" {
# include "env.h"
# include "libft.h"
}

#include <stdio.h>
#include <string.h>

TEST_CASE( "create_destroy env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	CHECK(env != NULL);
	env_destroy(&env);
}

TEST_CASE( "env size", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	CHECK(ft_array_len((const void **)environ) == env_size(env));
	env_destroy(&env);
}

TEST_CASE( "basic_get_set_unset env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	CHECK(env != NULL);

	//set
	CHECK(env_set(env, "key", (char *)"value", SCOPE_LOCAL));

	char *key = strdup("hello");
	CHECK(env_set(env, key, (char *)"world", SCOPE_LOCAL));
	free(key);

	char *value = strdup("---Hello from unitests---");
	CHECK(env_set(env, "123", value, SCOPE_LOCAL));
	free(value);

	CHECK(env_set(env, "last", (char *)"one", SCOPE_LOCAL));
	
	//get
	CHECK(strcmp(env_get(env, "key"), "value") == 0);
	CHECK(strcmp(env_get(env, "hello"), "world") == 0);
	CHECK(strcmp(env_get(env, "123"), "---Hello from unitests---") == 0);
	CHECK(strcmp(env_get(env, "last"), "one") == 0);

	//unset
	CHECK(env_unset(env, "NON_EXISTING") == 0);
	CHECK(env_unset(env, "key"));
	CHECK(env_unset(env, "hello"));
	CHECK(env_unset(env, "last"));
	env_destroy(&env);
}

TEST_CASE( "env_get_node_for_key", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	CHECK(env != NULL);
	t_env_node *node = env_get_node_for_key(env, "NON_EXISTING");
	CHECK(node == NULL);
	
	CHECK(env_set(env, "key", (char *)"value", SCOPE_LOCAL));
	node = env_get_node_for_key(env, "key");
	CHECK(strcmp(node->key, "key") == 0);
	env_destroy(&env);
}

TEST_CASE( "env_to_array env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	CHECK(env != NULL);
	char **array = env_to_array(env, SCOPE_LOCAL);
	CHECK(array != NULL);
	env_destroy(&env);
	free(array);
}
