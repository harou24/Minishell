#include <catch2/catch.hpp>

extern "C" {
# include "environ.h"
# include "string.h"
# include "libft.h"
# include <stdio.h>
}

extern char **environ;

char **environ_malloced(char **environ)
{
	char **buf = (char **)calloc(sizeof(char *), ft_arraylen((const void **)environ) + 1);
	printf("environ length : %zu\n", ft_arraylen((const void **)environ));
	REQUIRE(buf);

	for (size_t i = 0; environ[i] != NULL; i++) {
		buf[i] = strdup(environ[i]);
	}
	return (buf);
}

TEST_CASE( "init_deinit", "[environ]" ) {
	char **buf = environ_malloced(environ);

	REQUIRE(environ_init(buf) == true);
	CHECK(environ_deinit() == true);
}

TEST_CASE( "environ_add", "[environ]" ) {
	char **buf = environ_malloced(environ);
	REQUIRE(environ_init(buf) == true);
	
	CHECK(environ_add(strdup("hello")));
	
	CHECK(environ_deinit() == true);
}

TEST_CASE( "environ_set", "[environ]" ) {
	char **buf = environ_malloced(environ);
	REQUIRE(environ_init(buf) == true);
	
	CHECK(environ_set(0, strdup("hello")));
	
	CHECK(environ_deinit() == true);
}
