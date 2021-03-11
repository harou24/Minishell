#include <catch2/catch.hpp>

/*
 * Catch2: examples
 * for more examples checkout:
 *   https://github.com/catchorg/Catch2/tree/devel/examples
 *
 * Catch has two natural expression assertion macro's:
 * - REQUIRE() stops at first failure.
 * - CHECK() continues after failure.
 *
 * There are two variants to support decomposing negated expressions:
 * - REQUIRE_FALSE() stops at first failure.
 * - CHECK_FALSE() continues after failure.
 *
 * TEST_CASE( "Title here", "[short name]" ) {
 *     REQUIRE( [BOOLEAN CONDITION] ) ;
 * }
 */

extern "C" {
# include "env_access.h"
# include "env_singleton.h"
# include "path.h"
}

#include <string.h>
#include <stdio.h>

TEST_CASE( "checking for existing bins", "[path]" ) {
	extern char **environ;

	env_init(environ);

	/* assuming ls is found on any test system.. */
	char *path_string = env_get_path();
	REQUIRE(path_string);
	printf("%30s : %s\n", "PATH_STRING", path_string);
	char *abspath = path_expand(path_string, "ls");
	printf("%30s for %s : '%s'\n", "ABSPATH", "ls", abspath);
	REQUIRE(abspath);

	char *end = strrchr(abspath, '/');
	REQUIRE(end);
	CHECK(strcmp(end + 1, "ls") == 0);
	free(abspath);

	CHECK(path_contains(path_string, "ls") == true);

	env_deinit(NULL);
}

