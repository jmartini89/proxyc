#include "proxyc.h"

int
	ft_exec(t_thread *thread, int cmd)
{
	pid_t	pid;

	char	*start = "start";
	char	*stop = "stop";
	char	*argv[4] = {
	"systemctl",
	NULL,
	thread->service_name,
	NULL
	};

	if (cmd == START)
		argv[1] = start;
	if (cmd == STOP)
		argv[1] = stop;

	pid = fork();

	if (pid == -1)
		ft_fail("fork");

	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
			ft_fail("execvp");
		exit (EXIT_SUCCESS);
	}

	if (waitpid(pid, NULL, 0) == -1)
		ft_fail("waitpid execvp");

	/* LOG */
	if (cmd == START)
		fprintf(stderr, "exec: %s start\n", thread->service_name);
	if (cmd == STOP)
		fprintf(stderr, "exec: %s stop\n", thread->service_name);

	return (cmd);
}
