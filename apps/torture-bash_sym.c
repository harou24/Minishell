#include <stdio.h>
#include <string.h>

#include "bash_sym.h"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		e_token_type t = bash_match(argv[1], atoi(argv[2]));
		printf("found token : \"%s\"\n", token_dump_type(t));
		return (0);
	}
	return (1);
}
