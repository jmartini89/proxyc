#include "proxyc.h"

void
	ft_sig_term_proxy(int sig)
{
	fprintf(stderr, "proxy: sigterm exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_pipe_proxy(int sig)
{
	fprintf(stderr, "proxy: sigpipe exit\n");
	exit (EXIT_SUCCESS);
}

void
	ft_sig_chld(int sig)
{
	wait(NULL);
}
