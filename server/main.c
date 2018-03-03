#include "ft_serv.h"

void			ft_error(char *str)
{
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void			ft_clean_cli(t_cli *cli)
{
	cli->active = IS_FREE;
	ft_bzero(cli->name, 10);
	ft_bzero(cli->channel, 50);
	if (cli->r_buff)
		ft_strdel(&(cli->r_buff));
	cli->r_buff = NULL;
}

static t_cli	*init_cli(void)
{
	int		i;
	t_cli	*cli;

	i = 2;
	if (!(cli = (t_cli*)malloc(sizeof(t_cli) * MAX_CLI)))
		ft_error("Error: malloc");
	while (++i < MAX_CLI)
		ft_clean_cli(&(cli[i]));
	return (cli);
}

static int		valid_port(int count, char **av)
{
	int		i;

	i = -1;
	if (count != 2)
		ft_error("Usage: ./server [port]");
	while (av[1][++i])
	{
		if (!ft_isdigit(av[1][i]))
			ft_error("Error: port must be a number");
	}
	return (ft_atoi(av[1]));
}

int				main(int ac, char **av)
{
	t_cli	*serv;
	int		port;

	if ((port = valid_port(ac, av)) == -1)
		return (EXIT_FAILURE);
	serv = init_cli();
	start_serv(port, &serv);
	ft_select(serv);
	return (0);
}
