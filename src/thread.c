#include "proxyc.h"

static void
	ft_supervisor_prog(t_thread *thread)
{
	struct timeval	t1;
	time_t			elapsed;

	if (!thread->active_conn && thread->active_exec == 1)
	{
		gettimeofday(&t1, NULL);
		elapsed = t1.tv_sec - thread->t0.tv_sec;
		if (elapsed > thread->service_timeout)
			thread->active_exec = ft_exec(thread, STOP);
	}
	if (thread->active_conn && thread->active_exec == 0)
		thread->active_exec = ft_exec(thread, START);
}

static void
	ft_supervisor_pid(t_thread *thread)
{
	int	i;

	i = 0;
	while (i < thread->active_conn)
	{
		if ((waitpid(thread->pid_arr[i], NULL, WNOHANG)) == -1)
		{
			gettimeofday(&thread->t0, NULL);
			if (errno == ECHILD)
				ft_pid_lst_remove(thread, thread->pid_arr[i]);
		}
		i++;
	}
}

static void
	ft_thread_sup(t_thread *thread)
{
	while (1)
	{
		usleep(500);	// DEBUG STOOPED FAST

		pthread_mutex_lock(&thread->mutex);
		ft_supervisor_pid(thread);
		ft_supervisor_prog(thread);
		pthread_mutex_unlock(&thread->mutex);
	}
}

// static void
// 	ft_thread_sig(t_thread *thread)
// {
// 	sigset_t	set;
// 	int			sig;

// 	sigaddset(&set, SIGINT);
// 	if (sigwait(&set, &sig))
// 		ft_fail("sigwait");
// 	fprintf(stderr, "SIGINT INTERCEPTED\n");
// 	exit (EXIT_SUCCESS);
// }

void
	ft_thread(t_thread *thread)
{
	// pthread_t	thread_sig;

	thread->pid_arr = NULL;
	thread->active_conn = 0;
	thread->active_exec = 0;
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_create(&thread->thread, NULL, (void *)ft_thread_sup, thread);
	// pthread_create(&thread_sig, NULL, (void *)ft_thread_sig, thread);
}
