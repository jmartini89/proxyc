#include "netc.h"

void
	ft_proxy(int fd_src, int fd_dst)
{
	char	buffer[BUFFER];
	int		pid[2];
	int		id;
	int		fd;

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
		if (id == 0)	// CLIENT TO SERVER		SRC -> DST
		{
			fd = open("./debug/client.txt", O_CREAT | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);		// debug
			while (1)
			{
				if (recv(fd_src, buffer, BUFFER, 0) == -1)
					ft_fail("recv SRC");
				if (write(fd, buffer, BUFFER) == -1)					// debug
					ft_fail("debug SRC");
				if (send(fd_dst, buffer, BUFFER, 0) == -1)
					ft_fail("send SRC");
			}
		}
		if (id == 1)	// SERVER TO CLIENT		DST -> SRC
		{
			fd = open("./debug/server.txt", O_CREAT | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);		// debug
			while (1)
			{
				if (recv(fd_dst, buffer, BUFFER, 0) == -1)
					ft_fail("recv DST");
				if (write(fd, buffer, BUFFER) == -1)					// debug
					ft_fail("debug DST");
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