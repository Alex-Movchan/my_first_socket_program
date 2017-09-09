#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int			sock;
	int			listener;
	struct sockaddr_in	addr;
	char			buf[1024];
	int			bytes_read;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(av[1]));// или любой другой порт соответствующий клиенту
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
					bytes_read = recv(sock, buf, 1024, 0);
					if (bytes_read <= 0)
						break;
					send(sock, buf, bytes_read, 0);
				}
				close(sock);
				exit (0);
			defult :
				close (sock);
		}
	}
	return (0);
}
