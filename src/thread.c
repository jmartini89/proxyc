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
		sleep(60);

		pthread_mutex_lock(&thread->mutex);
		ft_supervisor_prog(thread);
		ft_supervisor_pid(thread);
		pthread_mutex_unlock(&thread->mutex);
	}
}

void
	ft_thread(t_thread *thread)
{
	thread->pid_arr = NULL;
	thread->active_conn = 0;
	thread->active_exec = 0;
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_create(&thread->thread, NULL, (void *)ft_thread_sup, thread);
}
