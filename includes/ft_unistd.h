#ifndef FT_UNISTD_H
# define FT_UNISTD_H

# define		PIPE_READ	0
# define		PIPE_WRITE	1

int				ft_pipe(int pipefd[2]);
char			*ft_gethostname(void);

#endif
