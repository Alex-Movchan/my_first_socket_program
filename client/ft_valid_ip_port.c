#include "ft_client.h"

static bool	ft_validip(char *ip)
{
	int		i;

	i = -1;
	while (ip[++i])
	{
		if (!ft_isdigit(ip[i]) && ip[i] != '.')
			return (false);
	}
	if ( i > 17)
		return (false);
	return (true);
}

static int	ft_validport(char *port)
{
	int		nbr;
	int		i;

	i = -1;
	while (port[++i])
		if (!ft_isdigit(port[i]))
			return (-1);
	if ((nbr = ft_atoi(port)) > 65535 || nbr < 1)
		return (-1);
	return (nbr);
}

static int	ft_conect(struct hostent *host,
						struct protoent *prot, int port, char *ip)
{
	int					sock;
	struct sockaddr_in	adrr;

	sock = socket(PF_INET, SOCK_STREAM, prot->p_proto);
	adrr.sin_family = AF_INET;
	adrr.sin_port = htons(port);
	adrr.sin_addr.s_addr = inet_addr(ip);
	if (connect(sock, (const struct sockaddr *)&adrr, sizeof(adrr)))
		ft_strerror("Error connect to server");
	return (sock);
}

int			ft_valid_ip_port(char *ip, char *src_port)
{
	int					port;
	struct hostent		*host;
	struct protoent		*prot;

	if (!ft_validip(ip))
		ft_strerror("Error ip address");
	if ((port = ft_validport(src_port)) == -1)
		ft_strerror("Error port");
	if (!(prot = getprotobyname("tcp")))
		ft_strerror("could not get protocol 'tcp'");
	if (!(host = gethostbyname(ip)))
        ft_strerror("Error get host by name");
	return (ft_conect(host, prot, port, ip));
}
