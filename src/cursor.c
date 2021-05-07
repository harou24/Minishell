#include "cursor.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

t_cursor	*cursor_create(void)
{
	t_cursor *curs;

	curs = malloc(sizeof(t_cursor));
	if (!curs)
		return (NULL);
	curs->row = 0;
	curs->col = 0;
	return (curs);
}

void cursor_set_pos(t_cursor *curs)
{
	int		idx;
	char	buf[255];
	int		read_size;

	write(STDIN_FILENO, "\033[6n", ft_strlen("\033[6n"));
	read_size = read(STDIN, buf, 255);
	buf[read_size] = '\0';
	idx = -1;
	while (!ft_isdigit(buf[idx]))
		++idx;
	curs->row = 0;
	while (ft_isdigit(buf[idx]))
		curs->row = curs->row * 10 + buf[idx++] - '0';
	++idx;
	curs->col = 0;
	while (ft_isdigit(buf[idx]))
		curs->col = curs->col * 10 + buf[idx++] - '0';
}

void	cursor_destroy(t_cursor *curs)
{
	free(curs);
}
