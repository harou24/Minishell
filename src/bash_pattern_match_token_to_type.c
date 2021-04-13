#include "bash_pattern.h"

t_bool	match_token_to_type(t_token *token, const t_token_type_e type)
{
	return (token->type == type);
}
