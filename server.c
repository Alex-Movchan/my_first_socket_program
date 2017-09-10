#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int     sendtoall(char *msg, int *socks, int len_sock, int len_msg)
{
        int     n;
        int     i;

        i = -1;
        while (++i < len_sock)
        {
                if (socks[i] > 0)
                {
                        if ((n = send(socks[i], msg, len_msg, 0)) == -1)
                                return (-1);
                }
        }
        return (n);
}

void	closeall(int *socks, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		close (socks[i]);
}

int	main(int ac, char **av)
{
	int			socks[10];
	int			listener;
	struct sockaddr_in	addr;
	char			buf[1024];
	int			bytes_read;
	int			i;
	int			sock;

	i = 0;
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(av[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind");
		exit(2);
	}
	listen(listener, 2);
 	while (1)
	{
		sock = accept(listener, NULL, NULL);
		socks[i] = sock;
		i++;
		if (sock < 0)
		{
			perror("accept");
			exit(3);
		}
		switch (fork())
		{
			case (-1) :
				perror("fork");
				break ;
			case (0) :
				close (listener);
				while (1)
				{
					bytes_read = recv(sock,  buf, 1024, 0);
					if (bytes_read <= 0)
						break;
					sendtoall( buf, socks, i, bytes_read);
					buf[0] = '\0';
				}
				close(sock);
				exit (0);
			defult :
				closeall(socks, i);
		}
	}
	return (0);
}
