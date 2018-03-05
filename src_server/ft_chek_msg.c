/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chek_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:33:31 by amovchan          #+#    #+#             */
/*   Updated: 2018/03/05 15:36:26 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_serv.h"

static void	ft_leave_chanel(t_cli *cli, int nbr, bool flag)
{
	char	*tmp;

	if (flag)
	{
		if (ft_strcmp(cli[nbr].r_buff + ft_strlen(FT_LEAVE) + 1,
				cli[nbr].channel))
		{
			send(nbr, "You do not belong to this channel", 33, 0);
			ft_strdel(&cli[nbr].r_buff);
			return ;
		}
	}
	tmp = ft_strdup(cli[nbr].r_buff);
	ft_msg_info(cli, nbr, "left the channel");
	cli[nbr].r_buff = tmp;
	ft_strclr(cli[nbr].channel);
}

void		ft_personal_message(t_cli *cli, int nbr)
{
	int		i;
	int		count;
	char	*msg;

	i = (int)ft_strlen(FT_MSF) + 1;
	count = -1;
	while (++count < MAX_CLI)
	{
		if (cli[count].active == IS_CLI && !ft_strncmp(cli[nbr].r_buff + i,
						cli[count].name, ft_strlen(cli[count].name)))
		{
			msg = ft_msg(cli[nbr].name,
					cli[nbr].r_buff + i + ft_strlen(cli[count].name) + 1);
			send(count, "<personal message: ", 19, 0);
			send(count, msg, ft_strlen(msg), 0);
			send(count, ">\n", 2, 0);
			ft_strdel(&msg);
		}
	}
	ft_strdel(&(cli[nbr].r_buff));
}

static void	ft_who(t_cli *cli, int nb)
{
	int		i;

	i = -1;
	send(nb, "logged users on this channel :\n", 31, 0);
	while (++i < MAX_CLI)
	{
		if (cli[i].active == IS_CLI &&
				!ft_strcmp(cli[nb].channel, cli[i].channel))
		{
			send(nb, cli[i].name, ft_strlen(cli[i].name), 0);
			send(nb, "\n", 1, 0);
		}
	}
	ft_strdel(&(cli[nb].r_buff));
}

static void	do_command(t_cli *cli, int nbr, size_t len)
{
	if (!ft_strncmp(cli[nbr].r_buff, FT_NICK, len))
		ft_get_name(cli, nbr, cli[nbr].r_buff + len + 1);
	else if (!ft_strncmp(cli[nbr].r_buff, FT_LEAVE, len))
		ft_leave_chanel(cli, nbr, true);
	else if (!ft_strncmp(cli[nbr].r_buff, FT_JOIN, len))
	{
		ft_leave_chanel(cli, nbr, false);
		ft_get_chanel(cli, nbr, cli[nbr].r_buff + len + 1);
	}
	else if (!ft_strcmp(cli[nbr].r_buff, FT_WHO))
		ft_who(cli, nbr);
	else if (!ft_strncmp(cli[nbr].r_buff, FT_MSF, len))
		ft_personal_message(cli, nbr);
	else
	{
		send(nbr, "Invalid command\n", 16, 0);
		ft_strdel(&(cli[nbr].r_buff));
	}
}

void		ft_chek_msg(t_cli *cli, int nb)
{
	int		len;

	if (cli[nb].r_buff[0] == '/')
	{
		len = 0;
		while (cli[nb].r_buff[len] && cli[nb].r_buff[len] > 33)
			len++;
		do_command(cli, nb, (size_t)len);
	}
	else
		w_cli(cli, nb);
}
