/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_sym.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:11:39 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:11:57 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <stdio.h>
#include <catch2/catch.hpp>

extern "C" {
#include "bash_sym.h"
}

TEST_CASE( "basics", "[bash_sym]" ) {
	struct					t_tst {
		const char			*str;
		const t_token_type_e	type;
	};
	
	const static t_tst tsts[] =	{
									{"word", 					WORD},
									{"wordWORD", 				WORD},
									{"WORD", 					WORD},
									{"_W", 						WORD},
									{"_", 						WORD},
									{"@%^()-+[]{}:,./?",		SYM},
									{"$",						VARIABLE},
									{"|",						PIPE},
									{" ",						SPACE},
									{"\"",						STRING},
									{"\'",						LITERAL},
									{"=",						ASSIGNMENT},
									{"\\",						ESCAPE},
									{"\\ ",						ESCAPE_SPACE},
									//{"\\n",						NEWLINE}, // no longer a lexing object
									{";",						SEMICOLON},
									{"<",						LEFTSHIFT},
									{">>",						DOUBLERIGHTSHIFT},
									{">",						RIGHTSHIFT}
								};
	const size_t tsts_len = sizeof(tsts)/sizeof(tsts[0]);

	for (size_t i = 0; i < tsts_len; i++) {
		t_tst tst = tsts[i];
		if (bash_match(tst.str, strlen(tst.str)) != tst.type)
			printf("Failed matcing teststring : '%s' to type %s\n", tst.str, token_dump_type(tst.type));
		CHECK(bash_match(tst.str, strlen(tst.str)) == tst.type);
	}
}
