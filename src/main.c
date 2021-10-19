#include "netc.h"

static void
	ft_fail(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

static void
	ft_fail_custom(char *err)
{
	fprintf(stderr, "%s\n", err);
	exit (EXIT_FAILURE);
}


int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_connect;
	int					fd_user;
	int					port_listen;
	int					port_connect;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_connect;
	unsigned int		addrlen;
	char				buffer[1024];

	if (argc < 2)
		ft_fail_custom("Usage: port");

	port_listen = atoi(argv[1]);
	port_connect = 80;

	/* LISTEN */
	if ((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("Socket Listen");
	addr_listen.sin_family = AF_INET;
	addr_listen.sin_port = htons(port_listen);
	addr_listen.sin_addr.s_addr = htonl(INADDR_ANY);

	/* CONNECT */
	if ((fd_connect = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_fail("Socket Connect");
	addr_connect.sin_family = AF_INET;
	addr_connect.sin_port = htons(port_connect);
	if (inet_pton(AF_INET, "172.217.21.78", &addr_connect.sin_addr) != 1)
		ft_fail_custom("Address conversion: Error");


	if (bind(fd_listen, (struct sockaddr *)&addr_listen, sizeof(addr_listen)) == -1)
		ft_fail("Bind");

	if (listen(fd_listen, 1024) == -1)
		ft_fail("Listen");

	if (connect(fd_connect, (struct sockaddr *)&addr_connect, sizeof(addr_listen)) == -1)
		ft_fail("Connect");
		
	/* ACCEPT */
	addrlen = sizeof(addr_listen);
	if ((fd_user = accept(fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen)) == -1)
		ft_fail("Accept");

	int	pid;
	int	id = 0;
	while (id <= 1)
	{
		pid = fork();
		if (!pid)
			break ;
		id++;
	}

	if (!pid)
	{
		if (id == 0)
		{
			while (1)
			{
				if (read(fd_user, buffer, 1024) == -1)
					ft_fail("read 0");
				else
				{
					// printf("\e[32mUSER\e[0m\n%.*s\n", (int)strlen(buffer), buffer);
					if (write(fd_connect, buffer, strlen(buffer)) == -1)
						ft_fail("Write");
				}
			}
		}
		if (id == 1)
		{
			while (1)
			{
				if (read(fd_connect, buffer, 1024) == -1)
					ft_fail("read 1");
				else
				{
					// printf("\e[34mCONNECT\e[0m\n%.*s\n", (int)strlen(buffer), buffer);
					if (write(fd_user, buffer, strlen(buffer)) == -1)
						ft_fail("Write");
				}
			}
		}
	}
	else
		pause ;
}
