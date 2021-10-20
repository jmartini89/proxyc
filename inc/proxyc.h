#ifndef PROXYC_H
# define PROXYC_H
# define SRC_PORT 4242
# define BUFFER 1024
# define HOWTO "Usage: [bin] [destination address] [destination port] [proxy port]\nProxy port is optional. Default: 4242"

/* socket */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* fail */
void	ft_fail(char *err);
void	ft_fail_custom(char *err);

/* init sockets */
void	ft_init_socket_listen(char **argv, int *fd_listen, struct sockaddr_in *addr_listen);
void	ft_init_socket_connection(char **argv, int *fd_dst, struct sockaddr_in *addr_dst);

/* signals */
void	ft_sig_term(int pid);
void	ft_sig_pipe(int pid);
void	ft_sig_chld(int pid);

/* proxy */
void	ft_proxy(int fd_src, int fd_dst, int fd_listen);

/* exec */
void	ft_exec(char **argv, char **envp);

#endif