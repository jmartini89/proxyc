#include "netc.h"

void
	ft_proxy(int fd_dst, int fd_listen, struct sockaddr_in *addr_listen, int *addrlen)
{
	char		buffer[BUFFER];
	int			buf_size;
	int			fd_src;
	int			pid[2];
	int			id;

	while (1)
	{

		bzero(buffer, BUFFER);
		if ((fd_src = accept(
			fd_listen, (struct sockaddr *)addr_listen, (socklen_t *)addrlen)) == -1)
			ft_fail("Accept");

		id = 0;
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
				while (1)
				{
					bzero(buffer, BUFFER);
					if ((buf_size = recv(fd_src, buffer, BUFFER, 0)) == -1)
						ft_fail("SRC recv");
					if (send(fd_dst, buffer, buf_size, 0) == -1)
						ft_fail("SRC send");
				}
			}
			if (id == 1)	// SERVER TO CLIENT		DST -> SRC
			{
				while (1)
				{
					bzero(buffer, BUFFER);
					if ((buf_size = recv(fd_dst, buffer, BUFFER, 0)) == -1)
						ft_fail("DST recv");
					if (send(fd_src, buffer, buf_size, 0) == -1)
							ft_fail("DST send");
				}
			}
		}

		else
		{
			wait (NULL);
			kill (pid[0], SIGTERM);
			kill (pid[1], SIGTERM);
			close (fd_src);
		}
	}

	close (fd_dst);
	close (fd_listen);

}