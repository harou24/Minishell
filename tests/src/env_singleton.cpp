#include <catch2/catch.hpp>

extern "C" {
# include "env.h"
# include "env_singleton.h"
# include "string.h"
}

TEST_CASE( "init_deinit", "[env_singleton]" ) {
	extern char **environ;

	REQUIRE(env_init(environ));
	env_deinit(NULL);
}

TEST_CASE( "simple_access", "[env_singleton]" ) {
	extern char **environ;

	REQUIRE(env_init(environ));
	CHECK(env_get_s("PATH")); /* assume 'PATH' is defined in environ */
	env_deinit(NULL);
}

TEST_CASE( "adding_values", "[env_singleton]" ) {
	extern char **environ;

	REQUIRE(env_init(environ));
	char *value = ft_strdup("world");
	CHECK(env_set_s("hello", value, SCOPE_ENVIRON));
	CHECK(env_get_s("PATH"));
	CHECK(strcmp(env_get_s("hello"), "world") == 0);
	env_deinit(NULL);
	free(value);
}

TEST_CASE( "adding_values repeated", "[env_singleton]" ) {
	extern char **environ;

	REQUIRE(env_init(environ));
	char *value = ft_strdup("world");
	CHECK(env_set_s("hello", value, SCOPE_ENVIRON));
	CHECK(env_set_s("hello", value, SCOPE_ENVIRON));
	CHECK(env_set_s("hello", value, SCOPE_ENVIRON));
	REQUIRE(env_get_s("hello"));
	CHECK(strcmp(env_get_s("hello"), "world") == 0);
	env_deinit(NULL);
	free(value);
}

TEST_CASE( "unset", "[env_singleton]" ) {
	extern char **environ;

	REQUIRE(env_init(environ));
	char *value = ft_strdup("world");
	CHECK(env_set_s("hello", value, SCOPE_ENVIRON));
	CHECK(env_get_s("hello"));
	CHECK(env_unset_s("hello"));
	CHECK(env_get_s("hello") == NULL);
	env_deinit(NULL);
	free(value);
}
