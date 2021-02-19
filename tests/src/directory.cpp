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
# include "directory.h"
}

#include <string.h>
#include <unistd.h>

 TEST_CASE( "directory_get_current_dir", "[dir]" ) {
	 char *cur_dir = directory_get_current_dir();
	 char buffer[1024];
	 getcwd(buffer, 1024);
	 REQUIRE(strcmp(cur_dir, buffer) == 0);
	 free(cur_dir);
 }

 TEST_CASE( "directory_change_dir", "[dir]" ) {
	REQUIRE(directory_change_dir("non_existing_dir") != 0);
 }
