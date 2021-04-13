#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "debugger.h"

#define HOSTNAME_MAXLEN	128

static char	*g_hostname__ = NULL;

char	*ft_gethostname(void)
{
	if (!g_hostname__)
	{
		g_hostname__ = malloc(HOSTNAME_MAXLEN + 1);
		if (g_hostname__)
		{
			if (gethostname(g_hostname__, HOSTNAME_MAXLEN + 1) == -1)
			{
				dbg("Failed retreiving hostname!\n%s", "");
				g_hostname__ = NULL;
			}
		}
	}
	return (g_hostname__);
}
