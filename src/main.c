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

static void
	ft_sig_chld(int pid)
{
	printf("%d\n", pid);
	wait(NULL);
}

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_dst;
	int					fd_src;
	int					pid;
	unsigned			addrlen;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;

	if (argc < 3)
		ft_fail_custom(HOWTO);

	signal(SIGCHLD, ft_sig_chld);
	signal(SIGTERM, ft_sig_term);
	signal(SIGPIPE, ft_sig_pipe);

	ft_init_socket_listen(argv, &fd_listen, &addr_listen);

	addrlen = sizeof(addr_listen);

	while (1)
	{
		ft_init_socket_connection(argv, &fd_dst, &addr_dst);

		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
			ft_fail("Accept");

		pid = fork();

		if (pid == -1)
			ft_fail("fork");

		if (!pid)
			ft_proxy(fd_src, fd_dst, fd_listen);
	}

	return (EXIT_SUCCESS);
}
