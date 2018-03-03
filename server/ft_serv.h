
#ifndef FT_SERV_H
#define FT_SERV_H

#include "../libft/libft.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define MAX_CLI 1000
#define BUF_SIZE 1024

#define FT_WHO	"/who"
#define FT_MSF "/msg"
#define FT_JOIN "/join"
#define FT_LEAVE "/leave"
#define FT_NICK "/nick"
#define IS_FREE 0
#define IS_SERV 1
#define IS_CLI 2

typedef struct		s_cli
{
	char			*r_buff;
	short			active;
	char			name[10];
	char			channel[50];
}					t_cli;

void				ft_error(char *str);
void				ft_clean_cli(t_cli *cli);
void				start_serv(int port, t_cli **cli);
void				w_cli(t_cli *cli, int nbr);
void				ft_get_name(t_cli *cli, int nb, char *name);
void				ft_get_chanel(t_cli *cli, int nb, char *chanel);
void				ft_chek_msg(t_cli *cli, int nb);
void				ft_msg_info(t_cli *cli, int nbr, char *option);
void				serv_read(t_cli **cli, int sock);
char				*ft_msg(char *name, char *buf);
void				ft_read(t_cli *cli, int nbr);
void				ft_select(t_cli *serv);

#endif
