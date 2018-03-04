#ifndef FT_CLIENT_H
#define FT_CLIENT_H

#include <stdbool.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
#include "../libft/libft.h"

void	ft_select(int sock, char *name);
void	ft_strerror(char *str);
int		ft_valid_ip_port(char *ip, char *port);
char	*ft_createcli(int sock);
void	ft_read(int sock, char **name);
void	ft_recv(int sock, char **name);
bool	ft_valid(char const *name, int len);

#endif
