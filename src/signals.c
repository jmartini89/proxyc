#include "proxyc.h"

void
	ft_sig_term(int pid)
{
	printf("sigterm exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_pipe(int pid)
{
	printf("sigpipe exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_chld(int pid)
{
	wait(NULL);
}
