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
	struct					t_tst {
		const char			*str;
		const e_token_type	type;
	};
	
	const static t_tst tsts[] =	{
									{"word", 					WORD},
									{"wordWORD", 				WORD},
									{"WORD", 					WORD},
									{"@%^()-+_[]{}:,./?",		SYM},
									{"$",						VARIABLE},
									{"|",						PIPE},
									{" ",						SPACE},
									{"\"",						STRING},
									{"\'",						LITERAL},
									{"=",						ASSIGNMENT},
									{"\\",						ESCAPE},
									{"\n",						NEWLINE},
									{";",						SEMICOLON},
									{"<",						OP_READ},
									{">>",						OP_APPEND},
									{">",						OP_WRITE}
								};
	const size_t tsts_len = sizeof(tsts)/sizeof(tsts[0]);

	for (size_t i = 0; i < tsts_len; i++) {
		t_tst tst = tsts[i];
		CHECK(bash_match(tst.str, strlen(tst.str)) == tst.type);
	}
}
