/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:11:32 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:11:33 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <catch2/catch.hpp>

extern "C" {
# include "argv.h"
# include <string.h>
}

#define TEST_SIZE 5;

TEST_CASE( "argv basics", "[argv]" ) {
	const size_t max_size = TEST_SIZE;
	const char *str = "Hello argv.";
	const char *path = "I am path.";

	for (size_t size = 1; size < max_size; size++) {
		t_argv *argv = argv_create(strdup(path));
		REQUIRE(argv != NULL);
		for (size_t i = 1; i < size; i++) {
			CHECK(argv_push(argv, strdup(str)) == true);
		}
		CHECK(strcmp(argv_get(argv, 0), path) == 0);
		for (size_t i = 1; i < size; i++) {
			CHECK(strcmp(argv_get(argv, i), str) == 0);
		}
		CHECK(argv_get_size(argv) == size);
		CHECK(argv_get_array(argv)[size + 1] == NULL);
		CHECK(argv_destroy(&argv) == NULL);
		CHECK(argv == NULL);
	}
}

