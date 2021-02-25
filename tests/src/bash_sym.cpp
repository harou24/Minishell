#include <cstring>
#include <stdio.h>
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
#include "bash_sym.h"
}

TEST_CASE( "basics", "[bash_sym]" ) {
	char *str;
	
	str = (char *)"word";
	CHECK(bash_match(str, strlen(str)) == WORD);

	str = (char *)"echo@%^()-+_[]{}:,./?";
	CHECK(bash_match(str, strlen(str)) == WORD);

	str = (char *)"$";
	CHECK(bash_match(str, strlen(str)) == VARIABLE);

	str = (char *)"|";
	CHECK(bash_match(str, strlen(str)) == PIPE);

	str = (char *)" ";
	CHECK(bash_match(str, strlen(str)) == SPACE);

	str = (char *)"\"";
	CHECK(bash_match(str, strlen(str)) == STRING);

	str = (char *)"\'";
	CHECK(bash_match(str, strlen(str)) == LITERAL);

	str = (char *)"=";
	CHECK(bash_match(str, strlen(str)) == ASSIGNMENT);

	str = (char *)"\\";
	CHECK(bash_match(str, strlen(str)) == ESCAPE);

	str = (char *)"|";
	CHECK(bash_match(str, strlen(str)) == PIPE);

	str = (char *)"\n";
	CHECK(bash_match(str, strlen(str)) == NEWLINE);

	str = (char *)";";
	CHECK(bash_match(str, strlen(str)) == SEMICOLON);

	str = (char *)"<";
	CHECK(bash_match(str, strlen(str)) == OP_READ);

	str = (char *)">>";
	CHECK(bash_match(str, strlen(str)) == OP_APPEND);

	str = (char *)">";
	CHECK(bash_match(str, strlen(str)) == OP_WRITE);
}
