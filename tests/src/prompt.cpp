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
# include "prompt.h"
}

#include <stdio.h>

TEST_CASE( "create_destroy prompt", "[prompt]" ) {
	t_prompt *prompt;
	prompt = prompt_create("user", "host");
	REQUIRE(prompt != NULL);
	printf("---------------PRONT-----------------\n");
	prompt_print(prompt);
	prompt_destroy(prompt);
}

