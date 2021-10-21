#include "proxyc.h"

void
	ft_pid_lst_add(t_thread *thread, pid_t pid)
{
	int	*tmp;

	thread->active_conn++;

	tmp = malloc((thread->active_conn) * sizeof(thread->active_conn));
	if (tmp == NULL)
		ft_fail("malloc");

	memcpy(tmp, thread->pid_arr, (thread->active_conn - 1) * sizeof(*tmp));
	tmp[thread->active_conn - 1] = pid;
	free (thread->pid_arr);
	thread->pid_arr = tmp;
	fprintf(stderr, "%d added to supervisor\n", pid);
}

void
	ft_pid_lst_remove(t_thread *thread, pid_t pid)
{
	int	i;
	int	j;
	int	*tmp;

	thread->active_conn--;

	tmp = malloc((thread->active_conn) * sizeof(thread->active_conn));
	if (tmp == NULL)
		ft_fail("malloc");

	i = 0;
	j = 0;
	while (i < (thread->active_conn + 1))
	{
		if (thread->pid_arr[i] != pid)
		{
			tmp[j] = thread->pid_arr[i];
			j++;
		}
		i++;
	}
	free (thread->pid_arr);
	if (thread->active_conn == 0)
		thread->pid_arr = NULL;
	thread->pid_arr = tmp;
	fprintf(stderr, "%d removed from supervisor\n", pid);
}
