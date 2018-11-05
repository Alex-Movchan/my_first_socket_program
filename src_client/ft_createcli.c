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

bool	ft_valid(char const *name, int len)
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

void	ft_join_channel(int sock)
{
	char	channel[50];
	ssize_t	len;

	ft_bzero(channel, 50);
	ft_putstr("choose a channel to join : #");
	while (true)
	{
		if ((len = read(STDIN_FILENO, channel, 50)) == -1)
			ft_strerror("Error reading");
		if (len > 0 && ft_valid(channel, 49))
			break ;
		if (len == 50)
		{
			while (channel[len - 1] != '\n')
			{
				if ((len = read(STDIN_FILENO, channel, 50)) == -1)
					ft_strerror("Error reading");
			}
		}
		ft_bzero(channel, 50);
		ft_putendl_fd("Please enter a channel between 1 and 49 chars long.", STDERR_FILENO);
		ft_putstr("choose a channel to join : #");
	}
	send(sock, channel, ft_strlen(channel), 0);
}

char		*ft_createcli(int sock)
{
	char	name[10];
	ssize_t	len;

	ft_bzero(name, 10);
	ft_putstr("nickname : ");
	while (true)
	{
		if ((len = read(STDIN_FILENO, name, 10)) == -1)
			ft_strerror("Error reading");
		if (len > 0 && len < 10 && ft_valid(name, 9))
			break ;
		if (len == 10)
		{
			while (name[len - 1] != '\n')
			{
				if ((len = read(STDIN_FILENO, name, 10)) == -1)
					ft_strerror("Error reading");
			}
		}
		ft_bzero(name, 10);
		ft_putendl_fd("Please enter a nickname between 1 and 9 chars long.", STDERR_FILENO);
		ft_putstr("nickname : ");
	}
	send(sock, name, ft_strlen(name), 0);
	return (ft_strndup(name, ft_strlen(name) - 1));
}
