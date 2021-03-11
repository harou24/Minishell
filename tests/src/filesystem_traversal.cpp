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
# include "filesystem.h"
# include "filesystem_traversal.h"
}

#include <string.h>
#include <unistd.h>

 TEST_CASE( "fs_get_cur_dir_name", "[dir]" ) {
	 char *cur_dir = fs_get_cur_dir_name();
	 char buffer[1024];
	 getcwd(buffer, 1024);
	 CHECK(strcmp(cur_dir, buffer) == 0);
	 free(cur_dir);
 }

 TEST_CASE( "fs_change_dir", "[dir]" ) {
	CHECK(fs_change_dir("non_existing_dir__________________") != 0);
 }

 TEST_CASE("directory_exist", "dir") {
	CHECK(directory_exists("non_existing_dir______________________") == FALSE);
 }
