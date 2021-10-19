#include "netc.h"

static void
	ft_sig_term(int pid)
{
	printf("sigterm exit\n");
	exit (EXIT_SUCCESS);
}

static void
	ft_sig_pipe(int pid)
{
	printf("sigpipe exit\n");
	exit (EXIT_SUCCESS);
}

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_dst;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;

	if (argc < 3)
		ft_fail_custom(HOWTO);

	signal(SIGTERM, ft_sig_term);
	signal(SIGPIPE, ft_sig_pipe);

	ft_init_socket_listen(argv, &fd_listen, &addr_listen);

	while (1)
	{
		ft_init_socket_connection(argv, &fd_dst, &addr_dst);
		ft_proxy(fd_dst, fd_listen, &addr_listen);
		close(fd_dst);
	}

	return (EXIT_SUCCESS);
}
