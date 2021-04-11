#include <catch2/catch.hpp>

extern "C" {
# include "argv.h"
# include <string.h>
}

#define TEST_SIZE 5;

TEST_CASE( "argv basics", "[argv]" ) {
	const size_t max_size = TEST_SIZE;
	const char *str = "Hello argv.";

	for (size_t size = 1; size < max_size; size++) {
		t_argv *argv = argv_create(size);
		REQUIRE(argv != NULL);
		for (size_t argv_size = 0; argv_size < size; argv_size++) {
			CHECK(argv_push(argv, strdup(str)) == true);
		}
		for (size_t i = 0; i < size; i++) {
			CHECK(strcmp(argv_get(argv, i), str) == 0);
		}
		CHECK(argv->argv[size] == NULL);
		CHECK(argv_destroy(&argv) == NULL);
		CHECK(argv == NULL);
	}
}

