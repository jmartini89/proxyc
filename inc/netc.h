#ifndef NETC_H
# define NETC_H
# define DST_ADDRESS "10.0.10.10"
# define DST_PORT 80
# define SRC_PORT 4242
# define BUFFER 4096

/* socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

/**/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

/* functions */
void	ft_fail(char *err);
void	ft_fail_custom(char *err);
void	ft_init(char *argv, int *fd_listen, int *fd_dst,
			struct sockaddr_in *addr_listen, struct sockaddr_in *addr_dst, unsigned int addrlen);
void	ft_proxy(int fd_src, int fd_dst);

#endif