#include "ft_serv.h"

void		ft_get_name(t_cli *cli, int nb, char *name)
{
	if (cli[nb].name[0] != '\0')
		ft_strclr(cli[nb].name);
	ft_strcpy(cli[nb].name, name);
	ft_printf("client №%d has a nickname: %s\n", nb - 3, name);
	ft_strdel(&(cli[nb].r_buff));
}

void		ft_get_chanel(t_cli *cli, int nb, char *chanel)
{
	if (cli[nb].channel[0] != '\0')
		ft_strclr(cli[nb].channel);
	ft_strcpy(cli[nb].channel, chanel);
	ft_msg_info(cli, nb, "join the channel");
	ft_printf("client №%d join the channel: %s\n", nb - 3, cli[nb].channel);
	ft_strdel(&(cli[nb].r_buff));
}