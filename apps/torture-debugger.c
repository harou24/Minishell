#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <unistd.h>

#define DEBUG 1
#include "debugger.h"

int main (int argc, char **argv)
{
	if (argc >=  2)
	{
		if( access( argv[1], F_OK ) == 0 )
		{
			printf("FILE EXISTS : '%s'\n", argv[1]);
			assert(strncmp("./", argv[1], 2) == 0);
			assert(strncmp("./..", argv[1], 4) != 0);
		}
	
		if (debug_init_tofile(argv[1]) == false)
		{
			printf("FAILED TO INIT\n");
			return (1);
		}

		int i = 2;
		while (i < argc)
		{
			dbg("%s\n", argv[i]);
			i++;
		}
	}
	else
	{
		printf("%s ./OFILE [STRINGS]\n", argv[0]);
		return (1);
	}
}
