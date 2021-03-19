#include <catch2/catch.hpp>

extern "C" {
# include "env.h"
}

#include <stdio.h>

TEST_CASE( "create_destroy env", "[env]" ) {
	extern char **environ;

	t_env *env = env_create((const char **)environ);
	REQUIRE(env != NULL);
	env_destroy(env);
}

