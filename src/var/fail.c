#include "proxyc.h"

void
	ft_fail(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

void
	ft_fail_custom(char *err)
{
	fprintf(stderr, "%s\n", err);
	exit (EXIT_FAILURE);
}
