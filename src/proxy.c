#include "proxyc.h"

static void
	ft_io(int fd_src, int fd_dst)
{
	char	buffer[BUFFER];
	int		in;
	int		out;

	while (1)
	{
		if ((in = recv(fd_src, buffer, BUFFER, 0)) == -1)
			ft_fail("client recv");
		if ((out = send(fd_dst, buffer, in, 0)) == -1)
			ft_fail("client send");
		if (out != in)
			printf("I/O DISCREPANCY");
		if (!in)
			exit (EXIT_SUCCESS);
	}
}

void
	ft_proxy(int fd_src, int fd_dst, int fd_listen)
{
	int	pid;
	int	pid_arr[2];
	int	id;
	int	err;

	signal(SIGCHLD, SIG_IGN);

	printf("PID %d start\n", getpid());

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
		if (id == 0)	// client to server
			ft_io(fd_src, fd_dst);
		if (id == 1)	// server to client
			ft_io(fd_dst, fd_src);
	}
	else
	{
		wait(NULL);
		kill(pid_arr[0], SIGTERM);
		kill(pid_arr[1], SIGTERM);
		waitpid(pid_arr[0], NULL, 0);
		waitpid(pid_arr[1], NULL, 0);
	}

	close(fd_src);
	close(fd_dst);
	printf("PID %d exit\n", getpid());
	exit (EXIT_SUCCESS);
}
