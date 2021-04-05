#include "bash_pattern.h"

t_bool	match_token_to_type(t_token *token, const e_token_type type)
{
	return (token->type == type);
}
