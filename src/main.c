#include "proxyc.h"

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

	ft_thread(&thread);

	ft_init_socket_listen(argv, &fd_listen, &addr_listen);

	addrlen = sizeof(addr_listen);

	signal(SIGCHLD, ft_sig_chld);

	while (1)
	{
		ft_init_socket_connection(argv, &fd_dst, &addr_dst);

		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
			ft_fail("accept");

		pid = fork();

		if (pid == -1)
			ft_fail("fork");

		if (!pid)
			ft_proxy(fd_src, fd_dst);

		pthread_mutex_lock(&thread.mutex);
		ft_pid_lst_add(&thread, pid);
		pthread_mutex_unlock(&thread.mutex);

		close (fd_src);
		close (fd_dst);
	}

	return (EXIT_SUCCESS);
}
