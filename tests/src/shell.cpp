#include <cstring>
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
# include "shell.h"
# include "hashmap.h"
}

#include <stdio.h>

TEST_CASE( "shell-test", "[shell]" ) {
	t_shell *shell = shell_create("username", "hostname");
	char *value = (char *)hm_get(shell->hm_env, "HOME");
	printf("\n\n----------TEST ---------------->HOME---------->%s\n\n\n", value);
	shell_destroy(shell);
}


