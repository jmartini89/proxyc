#include "proxyc.h"

static void
	ft_service_args(t_thread *thread, int argc, char **argv)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	while (argv[4][i])
	{
		if (isdigit(argv[4][i]) == 0)
			valid = 0;
		i++;
	}
	if (argc == 6 && valid)
	{
		thread->service_timeout = atoi(argv[4]) * 60;
		thread->service_name = argv[5];
		fprintf(stderr, "----------------------------\n");
		fprintf(stderr, "*** SERVICE MODE ENABLED ***\n");
		fprintf(stderr, "TIMEOUT:\t%d minutes\n", thread->service_timeout / 60);
		fprintf(stderr, "PROCESS:\t%s\n", thread->service_name);
		fprintf(stderr, "----------------------------\n");
	}
	else
	{
		thread->service_timeout = 0;
		thread->service_name = NULL;
	}
}

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_dst;
	int					fd_src;
	unsigned			addrlen;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;
	t_thread			thread;
	pid_t				pid;

	if (argc < 4)
		ft_fail_custom(HOWTO);

	ft_service_args(&thread, argc, argv);

	ft_thread(&thread);

	ft_socket_tcp_listen(argv, &fd_listen, &addr_listen);

	addrlen = sizeof(addr_listen);

	while (1)
	{
		ft_socket_tcp_connect(argv, &fd_dst, &addr_dst);

		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
			ft_fail("accept");

		pid = fork();

		if (pid == -1)
			ft_fail("fork");

		if (!pid)
			ft_proxy(fd_src, fd_dst);

		/* MUTEX PID */
		pthread_mutex_lock(&thread.mutex);
		ft_pid_lst_add(&thread, pid);
		pthread_mutex_unlock(&thread.mutex);

		close (fd_src);
		close (fd_dst);
	}

	return (EXIT_SUCCESS);
}
