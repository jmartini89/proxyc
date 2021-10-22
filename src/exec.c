#include "proxyc.h"

void
	ft_exec(t_thread *thread, char *cmd)
{
	pid_t	pid;

	char	*argv[4] = {
	"systemctl",
	cmd,
	thread->service_name,
	NULL
	};

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
	fprintf(stderr, "exec: %s %s\n", thread->service_name, cmd);
}
