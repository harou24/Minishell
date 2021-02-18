#ifndef PARSER_H
# define PARSER_H

#include "execscheme.h"

typedef struct		s_parser
{
	t_execscheme	*scheme;
}					t_parser;

t_execscheme		*parse(t_journal *journal);

t_parser			*parser_create();
t_parser			*parser_destroy();

#endif
