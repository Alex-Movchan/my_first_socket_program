#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


//char message[] = "Hello world!\n";
//char buf[sizeof(message)];

int	main(int ac, char **av)
{
	int			sock;
	struct sockaddr_in	addr;
	char			mess[1024];
	char			*buf;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(av[1]));
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}
	while (1)
	{
		printf("Enter the massege\nIf you want to leave write exit\n");
		gets(mess);
		if (!strcmp(mess, "exit"))
		{
			close(sock);
			exit(0);
		}
		send(sock, mess, sizeof(mess), 0);
		recv(sock, buf, sizeof(mess), 0);
		printf("%s\n", buf);
	}
	return (0);
}
