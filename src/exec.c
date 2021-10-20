#include "proxyc.h"

void
	ft_exec(char **argv, char **envp)
{
	int	timeout;

	if (argv[5])
		timeout = atoi(argv[5]);
	
	sleep (timeout);
}
