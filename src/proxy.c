#include "netc.h"

void
	ft_proxy(int fd_src, int fd_dst)
{
	char	buffer[BUFFER];
	int		pid[2];
	int		id;

	id = 0;
	bzero(pid, sizeof(*pid) * 2);
	while (id <= 1)
	{
		pid[id] = fork();
		if (!pid[id])
			break ;
		id++;
	}
	if (!pid[id])
	{
		if (id == 0) // CLIENT TO DST
		{
			while (1)
			{
				if (recv(fd_src, buffer, BUFFER, 0) == -1)
					ft_fail("recv SRC");
				if (send(fd_dst, buffer, BUFFER, 0) == -1)
					ft_fail("send SRC");
			}
		}
		if (id == 1) // DST TO CLIENT
		{
			while (1)
			{
				if (recv(fd_dst, buffer, BUFFER, 0) == -1)
					ft_fail("recv DST");
				if (send(fd_src, buffer, BUFFER, 0) == -1)
						ft_fail("send DST");
			}
		}
	}
	else
	{
		wait (NULL);
		close (fd_src);
		close (fd_dst);
		kill (pid[0], SIGTERM);
		kill (pid[1], SIGTERM);
	}
}