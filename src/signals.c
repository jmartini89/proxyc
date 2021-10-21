#include "proxyc.h"

void
	ft_sig_term(int sig)
{
	printf("sigterm exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_pipe(int sig)
{
	printf("sigpipe exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_chld(int sig)
{
	wait(NULL);
}
