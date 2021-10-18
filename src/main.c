/*
*	socket
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
/*
*	signal
*/
#include <signal.h>
/*
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void
	ft_fail(char *err)
{
	perror(err);
	exit (EXIT_FAILURE);
}

int
	main (int argc, char **argv)
{
	int					fd_listen;
	int					fd_connect;
	unsigned int		addrlen;
	struct sockaddr_in	addr_listen;
	struct sockaddr_in	addr_connect;
	int					port_listen;
	int					port_connect;

	if (argc < 3)
	{
		fprintf(stderr, "Usage: listen port, connect port\n");
		exit (EXIT_FAILURE);
	}

	port_listen = atoi(argv[1]);
	port_connect = atoi(argv[2]);

	/*
	*	LISTEN
	*/
	fd_listen = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_listen == -1)
		ft_fail("Socket");
	
	addr_listen.sin_family = AF_INET;
	addr_listen.sin_port = htons(port_listen);
	addr_listen.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd_listen, (struct sockaddr *)&addr_listen, sizeof(addr_listen)) == -1)
		ft_fail("Bind");

	if (listen(fd_listen, 10) == -1)
		ft_fail("Listen");

	/*
	*	CONNECT
	*/
	fd_connect = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_connect == -1)
		ft_fail("Socket");

	addr_connect.sin_family = AF_INET;
	addr_connect.sin_port = htons(port_connect);
	inet_pton(AF_INET, "127.0.0.1", &addr_connect.sin_addr);

	/*
	*	ACCEPT
	*/
	addrlen = sizeof(addr_listen);
	int new_fd;
	char buffer[1024];
	bzero(buffer, 1024);
	while (1)
	{
		new_fd = accept(fd_listen, (struct sockaddr *)&addr_listen, (socklen_t *)&addrlen);
		if (new_fd == -1)
			ft_fail("Accept");
		printf("Activity detected on port %d from %s\n", port_listen, inet_ntoa(addr_listen.sin_addr));
		if (read(new_fd, buffer, 1024) && *buffer);
		{
			printf("RELAY: \"%.*s\" to port %d\n",
					(int)strlen(buffer) - 1, buffer, port_connect);
			if (connect(fd_connect, (struct sockaddr *)&addr_connect, sizeof(addr_listen)) == -1)
				ft_fail("Connect");
			if (write(fd_connect, buffer, strlen(buffer)) == -1)
				ft_fail("Write");
		}
		bzero(buffer, 1024);
		close (new_fd);
	}
}
