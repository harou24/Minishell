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
	REQUIRE(env != NULL);
	env_destroy(&env);
}

TEST_CASE( "env size", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	REQUIRE(ft_arraylen((const void **)environ) == env_size(env));
	env_destroy(&env);
}

TEST_CASE( "basic_get_set_unset env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	REQUIRE(env != NULL);

	//set
	REQUIRE(env_set(env, "key", (char *)"value", SCOPE_LOCAL));

	char *key = strdup("hello");
	REQUIRE(env_set(env, key, (char *)"world", SCOPE_LOCAL));
	free(key);

	char *value = strdup("---Hello from unitests---");
	REQUIRE(env_set(env, "123", value, SCOPE_LOCAL));
	free(value);

	REQUIRE(env_set(env, "last", (char *)"one", SCOPE_LOCAL));
	
	//get
	REQUIRE(strcmp(env_get(env, "key"), "value") == 0);
	REQUIRE(strcmp(env_get(env, "hello"), "world") == 0);
	REQUIRE(strcmp(env_get(env, "123"), "---Hello from unitests---") == 0);
	REQUIRE(strcmp(env_get(env, "last"), "one") == 0);

	//unset
	REQUIRE(env_unset(env, "NON_EXISTING") == 0);
	REQUIRE(env_unset(env, "key"));
	REQUIRE(env_unset(env, "hello"));
	REQUIRE(env_unset(env, "last"));
	env_destroy(&env);
}

TEST_CASE( "env_get_node_for_key", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	REQUIRE(env != NULL);
	t_env_node *node = env_get_node_for_key(env, "NON_EXISTING");
	REQUIRE(node == NULL);
	
	REQUIRE(env_set(env, "key", (char *)"value", SCOPE_LOCAL));
	node = env_get_node_for_key(env, "key");
	REQUIRE(strcmp(node->key, "key") == 0);
	env_destroy(&env);
}

TEST_CASE( "env_to_array env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	REQUIRE(env != NULL);
	char **array = env_to_array(env, SCOPE_LOCAL);
	REQUIRE(array != NULL);
	env_destroy(&env);
	free(array);
}
