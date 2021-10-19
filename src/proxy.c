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

void
	ft_proxy(int fd_dst, int fd_listen, struct sockaddr_in *addr_listen, int *addrlen)
{
	char		buffer[BUFFER];
	int			buf_size;
	int			fd_src;
	int			pid;
	int			pid_arr[2];
	int			id;

	signal(SIGTERM, ft_sig_term);
	signal(SIGPIPE, ft_sig_pipe);
	while (1)
	{
		printf("START\n");
		bzero(buffer, BUFFER);
		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)addr_listen, (socklen_t *)addrlen)) == -1)
			ft_fail("Accept");

		id = 0;
		while (id <= 1)
		{
			pid = fork();
			if (pid == -1)
				ft_fail("fork");
			if (!pid)
				break ;
			pid_arr[id] = pid;
			id++;
		}

		if (!pid)
		{
			if (id == 0)	// CLIENT TO SERVER		SRC -> DST
			{
				while (1)
				{
					if ((buf_size = recv(fd_src, buffer, BUFFER, 0)) == -1)
						ft_fail("client recv");
					if (!buf_size)
						ft_fail_custom("client exit");
					if (send(fd_dst, buffer, buf_size, 0) == -1)
						ft_fail("client send");
				}
			}
			if (id == 1)	// SERVER TO CLIENT		DST -> SRC
			{
				while (1)
				{
					if ((buf_size = recv(fd_dst, buffer, BUFFER, 0)) == -1)
						ft_fail("server recv");
					if (!buf_size)
						ft_fail_custom("server exit");
					if (send(fd_src, buffer, buf_size, 0) == -1)
						ft_fail("server send");
				}
			}
		}

		else
		{
			wait(NULL);
			kill(pid_arr[0], SIGTERM);
			kill(pid_arr[1], SIGTERM);
			id = 0;
			while (id <= 1 && waitpid(pid_arr[id], NULL, 0))
				id++;
		}
	}
}