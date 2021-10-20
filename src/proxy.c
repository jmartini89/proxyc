#include "netc.h"

void
	ft_proxy(int fd_src, int fd_dst, int fd_listen)
{
	char	buffer[BUFFER];
	int		buf_size;
	int		pid;
	int		pid_arr[2];
	int		id;

	signal(SIGCHLD, ft_sig_chld);

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
		signal(SIGTERM, ft_sig_term);
		signal(SIGPIPE, ft_sig_pipe);
		if (id == 0)	// CLIENT TO SERVER		SRC -> DST
		{
			while (1)
			{
				if ((buf_size = recv(fd_src, buffer, BUFFER, 0)) == -1)
					ft_fail("client recv");
				if (!buf_size)
					exit (EXIT_SUCCESS);
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
					exit (EXIT_SUCCESS);
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

	close(fd_src);
	close(fd_dst);
	exit (EXIT_SUCCESS);
}
