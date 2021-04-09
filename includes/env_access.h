#ifndef ENV_ACCESS_H
# define ENV_ACCESS_H

# include "env_singleton.h"

char	*env_get_user(void);
char	*env_get_host(void);
char	*env_get_current_dir(void);
char	*env_get_prev_dir(void);
char	*env_get_home(void);
char	*env_get_path(void);
char	*env_get_cdpath(void);

#endif
