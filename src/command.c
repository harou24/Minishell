#include "command.h"

t_command	*command_create(const char *_input)
{
	t_command *command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->input = ft_strdup(_input);
	/*allocate command->output to store the result of command_execute() ??*/
	command->code_error = command_execute(command);
	return(command);
}

int		command_execute(t_command *_command)
{
	/* execute the command and store the output in command->output*/
	/* return 0 if success, otherwise return CODE_ERROR*/
	(void)_command;
	return (0);
}

int		command_get_code_error(t_command *_command)
{
	return (_command->code_error);
}

void		command_print_output(t_command *_command)
{
	printf("%s/n", _command->output);
}

void		command_destroy(t_command *_command)
{
	if (_command->input)
		free(_command->input);
	if (_command->output)
		free(_command->output);
	if (_command)
		free(_command);
}
