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
									{"echo", 2, P_PATH},
									{" echo", 3, P_PATH},
									{"echo ", 2, P_COMMAND},
									{" echo ", 3, P_COMMAND},
									{"echo hello world", 5, P_COMMAND},
									{" echo hello world", 6, P_COMMAND},
									{"echo a=5", 5, P_COMMAND},
									{" echo a=5", 6, P_COMMAND},
									{"a=5", 3, P_ASSIGNMENT},
									{" a=5", 4, P_ASSIGNMENT},
									{"a=5", 2, P_ASSIGNMENT},
									{" a=5", 3, P_ASSIGNMENT}
								};
	const size_t tsts_len = sizeof(tsts)/sizeof(tsts[0]);
	
	t_lex *l = lex_create();
	t_parser *p = parser_create();
	for (size_t i = 0; i < tsts_len; i++) {
		t_tst tst = tsts[i];
		REQUIRE(lex(tst.str));
		t_bash_pattern_type matched_type = bash_match_pattern(range(0, tst.match_len - 1));
		if (matched_type != tst.type) {
			const char *ours = pattern_dump_type(tst.type);
			const char *yours = pattern_dump_type(matched_type);
			printf("MISMATCH: ours:%s vs yours:%s, with matchlen:%zu\n", ours, yours, tst.match_len);
			CHECK(matched_type == tst.type);
		}
	}
	lex_destroy(&l);
	parser_destroy(&p);
}
