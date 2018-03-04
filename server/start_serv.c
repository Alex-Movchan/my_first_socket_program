#include "ft_serv.h"

void	ft_msg_info(t_cli *cli, int nbr, char *option)
{
	if (cli[nbr].channel[0] == '\0')
		return ;
	ft_strdel(&cli[nbr].r_buff);
	cli[nbr].r_buff = ft_strdup(option);
	w_cli(cli, nbr);
}

void	serv_read(t_cli **cli, int sock)
{
	int					sock_cli;
	socklen_t			len;
	struct sockaddr_in	adrr;

	len = sizeof(adrr);
	if ((sock_cli = accept(sock, (struct sockaddr*)&adrr, &len)) == -1)
		ft_error("Error: accept");
	ft_printf("New client №%d from %s:%d\n", sock_cli - 3,
			inet_ntoa(adrr.sin_addr), ntohs(adrr.sin_port));
	if ((*cli)[sock_cli].active)
		ft_clean_cli(&((*cli)[sock_cli]));
	(*cli)[sock_cli].active = IS_CLI;
}

void	start_serv(int port_nbr, t_cli **cli)
{
	int					sock;
	struct sockaddr_in	sin;
	struct protoent		*prot;

	if (!(prot = getprotobyname("tcp")))
		ft_error("Error: getprotobyname");
	if ((sock = socket(PF_INET, SOCK_STREAM, prot->p_proto)) == -1)
		ft_error("Error: socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port_nbr);
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		ft_error("Error: bind");
	ft_putendl(inet_ntoa(sin.sin_addr));
	if (listen(sock, MAX_CLI) == -1)
		ft_error("Error: listen");
	(*cli)[sock].active = IS_SERV;
}