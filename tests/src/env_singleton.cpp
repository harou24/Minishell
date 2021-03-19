#include <catch2/catch.hpp>

extern "C" {
# include "env.h"
# include "env_singleton.h"
}

#include <stdio.h>

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


