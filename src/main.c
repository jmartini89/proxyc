#include "proxyc.h"

static void
	ft_thread(t_thread *thread)
{
	while (1)
	{
		t_list	*tmp;
		int		stat;

		sleep (2);
		pthread_mutex_lock(&thread->mutex);
		tmp = thread->list;
		while (tmp)
		{
			if (waitpid(thread->list->pid, NULL, WNOHANG) == -1)
			{
				printf("%d IS GONE! \n", thread->list->pid);
			}
			tmp = thread->list->next;
		}
		pthread_mutex_unlock(&thread->mutex);
	}
}

int
	main (int argc, char **argv)
{
	int		fd_listen;
	int		fd_dst;
	int		fd_src;

	unsigned			addrlen;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_dst;

	pid_t		pid;
	t_list		*pid_list;
	int			i;
	int			active;

	if (argc < 4)
		ft_fail_custom(HOWTO);

	// if (argc > 4)
	// 	ft_exec(argv);

	t_thread	thread;

	thread.list = NULL;
	pthread_mutex_init(&thread.mutex, NULL);
	pthread_create(&thread.init, NULL, (void *)ft_thread, &thread);

	signal(SIGCHLD, ft_sig_chld);

	ft_init_socket_listen(argv, &fd_listen, &addr_listen);

	addrlen = sizeof(addr_listen);

	i = 0;
	active = 0;
	while (1)
	{
		ft_init_socket_connection(argv, &fd_dst, &addr_dst);

		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
			ft_fail("accept");

		pid = fork();

		pthread_mutex_lock(&thread.mutex);
		ft_lstadd(&thread.list, ft_lstnew(pid));
		pthread_mutex_unlock(&thread.mutex);

		if (pid == -1)
			ft_fail("fork");

		if (!pid)
			ft_proxy(fd_src, fd_dst);

		close (fd_src);
		close (fd_dst);
	}

	return (EXIT_SUCCESS);
}
