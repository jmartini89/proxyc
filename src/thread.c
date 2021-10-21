#include "proxyc.h"

void
	ft_routine(t_thread *thread)
{
	int	i;

	while (1)
	{

		usleep(500);	// DEBUG STOOPED FAST
		pthread_mutex_lock(&thread->mutex);
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
		pthread_mutex_unlock(&thread->mutex);
	}
}

void
	ft_thread(t_thread *thread)
{
	thread->pid_arr = NULL;
	thread->active_conn = 0;
	pthread_mutex_init(&thread->mutex, NULL);
	pthread_create(&thread->thread, NULL, (void *)ft_routine, thread);
}
