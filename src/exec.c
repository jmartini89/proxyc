#include "proxyc.h"

void
	ft_exec(char **argv)
{
	unsigned	timeout;
	int			pid;

	if (argv[4])
		timeout = atoi(argv[4]);

	pid = fork();

	if (pid == -1)
		ft_fail("fork");

	if (!pid)
	{
		if (execvp(argv[5], &argv[5]) == -1)
			ft_fail("execvp");
	}

	waitpid(pid, NULL, WUNTRACED);

	printf("Process \"%s\" launched, sleeping for %us\n", argv[5], timeout);

	sleep(timeout);
}
