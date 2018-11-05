/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cliread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:25:14 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:26:33 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static void	ft_clearline(size_t len)
{
	size_t	i;

	i = len;
	while (--i)
		ft_putchar('\b');
	i = len;
	while (--i)
		ft_putchar(' ');
	while (--len)
		ft_putchar('\b');
}

void		ft_recv(int sock, char **name)
{
	char	buff[1024];
	ssize_t	len;

	ft_clearline(ft_strlen(*name) + 5);
	if ((len = recv(sock, buff, 1024, 0)) == 0)
	{
		ft_putendl("\033[0;33mconnection to server lost.");
		close(sock);
		exit(EXIT_SUCCESS);
	}
	buff[len] = '\0';
	ft_putstr("\e[34;46m");
	ft_putstr(buff);
}

void		ft_dell_arrey(char **av)
{
	int		i;

	if (!av)
		return ;
	i = -1;
	while (av[++i])
		ft_strdel(&av[i]);
	free(av);
}

void		ft_reconnect(int *sock, char **name, char *buff)
{
	char	**av;
	int		ac;
	size_t	len;

	ac = 0;
	len = ft_strlen(buff);
	buff[len - 1] = (buff[len - 1] == '\n' ? '\0' : buff[len - 1]);
	if (!(av = ft_strsplit(buff, ' ')))
		ft_strerror("Error malloc.");
	while(av[ac])
		ac++;
	if (ac != 3)
		return ft_putendl_fd("Usage: ./connect [ip][port]", STDERR_FILENO);
	close(*sock);
	*sock = ft_valid_ip_port(av[1], av[2]);
	ft_dell_arrey(av);
	send(*sock, *name, ft_strlen(*name), 0);
	send(*sock, "\n", 1, 0);
	ft_join_channel(*sock);
}

void		ft_read(int *sock, char **name)
{
	char	buff[1024];
	ssize_t len;

	if ((len = read(STDIN_FILENO, buff, 1024)) == -1)
		ft_strerror("Error reading");
	if (len == 0)
		return ;
	if (buff[0] == '\n')
		return ;
	if (buff[len - 1] != '\n')
		ft_putchar('\n');
	buff[len] = '\0';
	if (!ft_strncmp(buff, "/help", 5))
		return (ft_putendl("Help msg."));
	if (!ft_strncmp(buff, "/exit", 5))
			exit(EXIT_SUCCESS);
	if (!ft_strncmp(buff, "/connect", 8))
		return	ft_reconnect(sock, name, buff);
	if (!ft_strncmp(buff, "/nick ", 6))
	{
		if (!ft_valid(buff + 6, 10))
		{
			ft_putendl("Please enter a nickname between 1 and 9 chars long.");
			return ;
		}
		ft_strdel(name);
		*name = ft_strndup(buff + 6, (size_t)len - 7);
	}
	send(*sock, buff, (size_t)len, 0);
}
