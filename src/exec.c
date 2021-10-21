#include "proxyc.h"

int
	ft_exec(t_thread *thread, int cmd)
{
	pid_t	pid;

	char			*start[4] = {
	// "sudo",
	"service",
	thread->service_name,
	"start",
	};
	char			*stop[4] = {
	// "sudo",
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

	if (waitpid(pid, NULL, 0) == -1)
		ft_fail("waitpid execvp");

	if (cmd == START)
		fprintf(stderr, "exec: %s start\n", thread->service_name);
	if (cmd == STOP)
		fprintf(stderr, "exec: %s stop\n", thread->service_name);

	return (cmd);
}
