/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createcli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:28:08 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:29:17 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

bool		ft_valid(char const *name, int len)
{
	int		i;

	i = -1;
	while (name[++i])
	{
		if ((name[i] < 33 || name[i] > 125) && name[i] != '\n')
			return (false);
	}
	if (i >= len || i == 1)
		return (false);
	return (true);
}

static void	ft_join_channel(int sock)
{
	char channel[52];

	ft_bzero(channel, 52);
	ft_putstr("choose a channel to join : #");
	if (read(STDIN_FILENO, channel, 52) == -1)
		ft_strerror("Error reading");
	while (!ft_valid(channel, 50))
	{
		ft_bzero(channel, 52);
		ft_putendl("Please enter a channel between 1 and 49 chars long.");
		ft_putstr("choose a channel to join : #");
		if (read(STDIN_FILENO, channel, 52) == -1)
			ft_strerror("Error reading");
	}
	send(sock, channel, ft_strlen(channel), 0);
}

char		*ft_createcli(int sock)
{
	char	name[12];

	ft_bzero(name, 12);
	ft_putstr("nickname : ");
	if (read(STDIN_FILENO, name, 12) == -1)
		ft_strerror("Error reading");
	while (!ft_valid(name, 10))
	{
		ft_bzero(name, 12);
		ft_putendl("Please enter a nickname between 1 and 9 chars long.");
		ft_putstr("nickname : ");
		if (read(STDIN_FILENO, name, 12) == -1)
			ft_strerror("Error reading");
	}
	send(sock, name, ft_strlen(name), 0);
	ft_join_channel(sock);
	return (ft_strndup(name, ft_strlen(name) - 1));
}
