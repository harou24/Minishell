#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libft.h"

/* standardized API for Unix files, see 'man 7 inode' */
typedef enum	e_filetype
{
	F_SOCK = S_IFSOCK,
	F_LINK = S_IFLNK,
	F_REG = S_IFREG,
	F_BLK = S_IFBLK,
	F_DIR = S_IFDIR,
	F_CHR = S_IFCHR,
	S_FIFO = S_IFIFO
}				t_filetype;

typedef enum	e_filemode
{
	FM_EXEC = S_IXUSR,
	FM_READ = S_IRUSR,
	FM_WRITE = S_IWUSR
}				t_filemode;

t_bool	fs_exists(const char *fname);
t_bool	fs_has_type(const char *fname, t_filetype ftype);
t_bool	fs_has_mode(const char *fname, t_filemode fmode);

t_bool	file_exists(const char *fname);
t_bool	file_is_executable(const char *fname);
t_bool	file_is_readable(const char *fname);
t_bool	file_is_writeable(const char *fname);

t_bool	directory_exists(const char *dname);
t_bool	directory_is_openable(const char *dname);

#endif
