#include <cstring>
#include <stdio.h>
#include <catch2/catch.hpp>

extern "C" {
#include "lexer.h"
#include "parser.h"
#include "bash_pattern.h"
}

TEST_CASE( "basic pattern matching", "[bash_pattern]" ) {
	struct							t_tst {
		const char					*str;
		const size_t				match_len;
		const t_bash_pattern_type	type;
	};
	
	const static t_tst tsts[] =	{
									{" ", 1, P_NO_TYPE},
									{"echo", 2, P_COMMAND},
									{"echo ", 2, P_COMMAND},
									{"echo hello world", 5, P_COMMAND},
									{"echo a=5", 5, P_COMMAND},
									{"a=5", 3, P_ASSIGNMENT},
									{"a=5", 2, P_NO_TYPE}
								};
	const size_t tsts_len = sizeof(tsts)/sizeof(tsts[0]);
	
	t_lex *l = lex_create();
	t_parser *p = parser_create();
	for (size_t i = 0; i < tsts_len; i++) {
		t_tst tst = tsts[i];
		REQUIRE(lex(tst.str));
		CHECK(bash_match_pattern(range(0, tst.match_len - 1)) == tst.type);
	}
	lex_destroy(&l);
	parser_destroy(&p);
}
