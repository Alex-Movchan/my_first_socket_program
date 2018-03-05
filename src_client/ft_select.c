/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:29:33 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:30:11 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

static void	ft_initcli(int sock, fd_set *fd_read)
{
	FD_ZERO(fd_read);
	FD_SET(STDIN_FILENO, fd_read);
	FD_SET(sock, fd_read);
}

static void	ft_chek_fd(int sock, fd_set *fd, char **name)
{
	if (FD_ISSET(STDIN_FILENO, fd))
		ft_read(sock, name);
	else if (FD_ISSET(sock, fd))
		ft_recv(sock, name);
}

void		ft_chat_invitation(char *name)
{
	ft_putstr("\033[0;32m");
	ft_putstr(name);
	ft_putstr(": $>");
}

void		ft_select(int sock, char *name)
{
	fd_set	fd_read;

	while (1)
	{
		ft_chat_invitation(name);
		ft_initcli(sock, &fd_read);
		if (select(sock + 1, &fd_read, NULL, NULL, NULL) != 0)
			ft_chek_fd(sock, &fd_read, &name);
	}
}
