#include "proxyc.h"

int
	ft_exec(t_thread *thread, int cmd)
{
	pid_t	pid;

	char			*start[5] = {
	"sudo",
	"service",
	thread->service_name,
	"start",
	};
	char			*stop[5] = {
	"sudo",
	"service",
	thread->service_name,
	"stop",
	};

	pid = fork();

	if (pid == -1)
		ft_fail("fork");

	if (pid == 0)
	{
		if (cmd == START)
			if (execvp(start[0], start) == -1)
				ft_fail("execvp");
		if (cmd == STOP)
			if (execvp(stop[0], stop) == -1)
				ft_fail("execvp");
		exit (EXIT_SUCCESS);
	}

	if (cmd == START)
		fprintf(stderr, "%s start\n", start[2]);
	if (cmd == STOP)
		fprintf(stderr, "%s stop\n", stop[2]);

	return (cmd);
}
