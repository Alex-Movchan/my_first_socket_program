#include "ft_serv.h"

int		ft_init_client(t_cli *serv, fd_set *fd_read)
{
	int		i;
	int		max = 0;

	i = -1;
	FD_ZERO(fd_read);
	while (++i < MAX_CLI)
	{
		if (serv[i].active != IS_FREE)
		{
			FD_SET(i, fd_read);
			max = max > i ? max : i;
		}
	}
	return (max);
}

void	ft_chek_sock(t_cli *serv, int count, fd_set *fd_read)
{
	int		i;

	i = -1;
	while (++i < MAX_CLI && count > 0)
	{
		if  (FD_ISSET(i, fd_read))
		{
			ft_read(serv, i);
			count--;
		}
	}
}

void	ft_select(t_cli *serv)
{
	fd_set			fd_read;
	int				max;
	int				count;

	while (1)
	{
		max = ft_init_client(serv, &fd_read);
		count = select(max + 1, &fd_read, NULL, NULL, NULL);
		ft_chek_sock(serv, count, &fd_read);
	}
}
