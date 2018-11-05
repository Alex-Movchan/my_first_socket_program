/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:32:28 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:32:57 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

void	ft_strerror(char *str)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	int		sock;
	char	*name;

	if (ac != 3)
		ft_strerror("Usage: ./cli [ip][port]");
	sock = ft_valid_ip_port(av[1], av[2]);
	name = ft_createcli(sock);
	ft_join_channel(sock);
	ft_select(sock, name);
	return (EXIT_SUCCESS);
}
