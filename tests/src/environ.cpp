/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:12:34 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:12:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <catch2/catch.hpp>
#include <vector>

extern "C" {
# include "environ.h"
# include "string.h"
# include "libft.h"
# include <stdio.h>
}

extern char **environ;

char **environ_malloced(char **environ)
{
	char **buf = (char **)calloc(sizeof(char *), ft_array_len((const void **)environ) + 1);
	printf("environ length : %zu\n", ft_array_len((const void **)environ));
	REQUIRE(buf);

	for (size_t i = 0; environ[i] != NULL; i++) {
		buf[i] = strdup(environ[i]);
	}
	return (buf);
}

char **test_array(std::vector<const char *> vec)
{
	char **buf = (char **)calloc(sizeof(char *), vec.size() + 1);
	for (size_t i = 0; i < vec.size(); i++)
		buf[i] = strdup(vec.at(i));
	buf[vec.size()] = NULL;
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

TEST_CASE( "environ_add special array", "[environ]" ) {
	char **buf = test_array({"a=1", "b=2", "c=3"});
	REQUIRE(environ_init(buf) == true);
	buf = NULL;
	
	CHECK(environ_add(strdup("d=4")));
	buf = environ_get();
	CHECK(strcmp(buf[0], "a=1") == 0);
	CHECK(strcmp(buf[1], "b=2") == 0);
	CHECK(strcmp(buf[2], "c=3") == 0);
//	CHECK(strcmp(buf[3], "d=4") == 0);
	return ;
	CHECK(buf[4] == NULL);

	size_t i = 0;
	while (buf[i]) {
		printf("buf content : %s\n", buf[i]);
		i++;
	}
	printf("buf content : %s\n", buf[i]);

	CHECK(environ_deinit() == true);
}

