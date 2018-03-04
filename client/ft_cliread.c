
#include "ft_client.h"

static void	ft_clearline(size_t len)
{
	size_t	i;

	i = len;
	while (--i)
		ft_putchar('\b');
	i = len;
	while (--i)
		ft_putchar(' ');
	while (--len)
		ft_putchar('\b');
}

void		ft_recv(int sock, char **name)
{
	char	buff[1024];
	ssize_t	len;

	ft_clearline(ft_strlen(*name) + 5);
	if ((len = recv(sock, buff, 1024, 0)) == 0)
	{
		ft_putendl("\033[0;33mconnection to server lost.");
		close(sock);
		exit(EXIT_SUCCESS);
	}
	buff[len] = '\0';
	ft_putstr("\e[34;46m");
	ft_putstr(buff);
}

void		ft_read(int sock, char **name)
{
	char	buff[1024];
	ssize_t len;

	if ((len = read(STDIN_FILENO, buff, 1024)) == -1)
		ft_strerror("Error reading");
	if (buff[0] == '\n')
		return;
	if (buff[len - 1] != '\n')
		ft_putchar('\n');
	buff[len] = '\0';
	if (!ft_strncmp(buff, "/nick ", 6))
	{
		if (!ft_valid(buff + 6, 10))
		{
			ft_putendl("Please enter a nickname between 1 and 9 chars long.");
			return;
		}
		ft_strdel(name);
		*name = ft_strndup(buff + 6, (size_t)len - 7);
	}
	send(sock, buff, (size_t)len, 0);
}