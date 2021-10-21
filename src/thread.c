#include "proxyc.h"

static void
	ft_supervisor_prog(t_thread *thread)
{
	static int	status;

	if (thread->active_conn && thread->prog_exec == 0)
	{
		printf("PROGRAM START\n");
		thread->prog_exec = 1;
	}
	if (!thread->active_conn && thread->prog_exec == 1)
	{
		printf("PROGRAM STOP\n");
		thread->prog_exec = 0;
	}
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
			if (errno == ECHILD)
			{
				printf("%d REMOVED\n", thread->pid_arr[i]);
				ft_pid_lst_remove(thread, thread->pid_arr[i]);
			}
		}
		i++;
	}
}

void
	ft_routine(t_thread *thread)
{

	while (1)
	{
		usleep(500);	// DEBUG STOOPED FAST

		/* MUTEX */
		pthread_mutex_lock(&thread->mutex);
		ft_supervisor_pid(thread);
		ft_supervisor_prog(thread);
		pthread_mutex_unlock(&thread->mutex);
	}
}

void
	ft_thread(t_thread *thread)
{
	thread->pid_arr = NULL;
	thread->active_conn = 0;
	thread->prog_exec = 0;
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_create(&thread->thread, NULL, (void *)ft_routine, thread);
}
