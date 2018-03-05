/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_cli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:36:41 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:38:02 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_serv.h"

char	*ft_msg(char *name, char *buf)
{
	char	*msg;
	int		len;

	len = (int)ft_strlen(name) + (int)ft_strlen(buf) + 2;
	msg = ft_strnew((size_t)len);
	msg[0] = '<';
	ft_strcat(msg, name);
	ft_strcat(msg, ">");
	ft_strcat(msg, buf);
	return (msg);
}

void	w_cli(t_cli *cli, int nbr)
{
	char	*msg;
	int		i;

	if (cli[nbr].channel[0] == '\0')
	{
		send(nbr, "Please join the channel", 24, 0);
		ft_strdel(&(cli[nbr].r_buff));
		return ;
	}
	msg = ft_msg(cli[nbr].name, cli[nbr].r_buff);
	ft_strdel(&(cli[nbr].r_buff));
	i = -1;
	while (++i < MAX_CLI)
	{
		if (i == nbr || cli[i].active == IS_FREE)
			continue ;
		if (!ft_strcmp(cli[nbr].channel, cli[i].channel))
		{
			send(i, msg, ft_strlen(msg), 0);
			send(i, "\n", 1, 0);
		}
	}
	ft_strdel(&msg);
}

int		ft_recvmsg(int sock, char **line)
{
	char	buff[1024];
	ssize_t len;
	char	*leaks;

	ft_bzero(buff, 1024);
	leaks = *line;
	if (!(len = recv(sock, buff, 1023, 0)))
		return (0);
	*line = ft_strjoin(*line, buff);
	ft_strdel(&leaks);
	if (buff[len - 1] != '\n')
		return (1);
	(*line)[ft_strlen(*line) - 1] = '\0';
	return (2);
}

void	ft_read(t_cli *cli, int nbr)
{
	int		res;

	if (cli[nbr].active == IS_SERV)
		return (serv_read(&cli, nbr));
	if (!(res = ft_recvmsg(nbr, &cli[nbr].r_buff)))
	{
		ft_msg_info(cli, nbr, "left the channel");
		ft_printf("client №%d <%s> gone away\n", nbr - 2, cli[nbr].name);
		ft_strdel(&cli[nbr].r_buff);
		ft_clean_cli(&(cli[nbr]));
		close(nbr);
		return ;
	}
	if (res == 1)
		return ;
	if (cli[nbr].name[0] == '\0')
		ft_get_name(cli, nbr, cli[nbr].r_buff);
	else if (cli[nbr].channel[0] == '\0')
		ft_get_chanel(cli, nbr, cli[nbr].r_buff);
	else
		ft_chek_msg(cli, nbr);
}
