# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amovchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 16:00:29 by amovchan          #+#    #+#              #
#    Updated: 2018/03/05 17:35:26 by amovchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_S = server
NAME_C = client

G = gcc
FLAGS = -Wall -Wextra -Werror

SRC_PATH_S = ./src_server/
SRC_NAME_S =  ft_chek_msg.c \
			ft_func_cli.c \
			ft_nameandchanel.c \
			ft_select.c \
			main.c \
			start_serv.c 

OBJ_PATH_S = ./src_server/
OBJ_NAME_S = $(SRC_NAME_S:.c=.o)
SRC_S = $(addprefix $(SRC_PATH_S), $(SRC_NAME_S))
OBJ_S = $(addprefix $(OBJ_PATH_S), $(OBJ_NAME_S))
GCFLAGS_S = -I./src_server/ -I./libft/

SRC_PATH_C = ./src_client/
SRC_NAME_C = ft_cliread.c \
			ft_createcli.c \
			ft_select.c \
			ft_valid_ip_port.c \
			main.c

OBJ_PATH_C = ./src_client/
OBJ_NAME_C = $(SRC_NAME_C:.c=.o)
SRC_C = $(addprefix $(SRC_PATH_C), $(SRC_NAME_C))
OBJ_C = $(addprefix $(OBJ_PATH_C), $(OBJ_NAME_C))
GCFLAGS_C = -I./src_client/ -I./libft/

LIBFT = libft/libft.a

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJ_S)
		@make -C libft/
		@$(G) $(FLAGS) $(GCFLAGS_S) -o $@ $(OBJ_S) $(LIBFT)

$(NAME_C): $(OBJ_C)
		@$(G) $(FLAGS) $(GCFLAGS_C) -o $@ $(OBJ_C) $(LIBFT)

$(OBJ_PATH_S)%.o: $(SRC_PATH_S)%.c
		@$(G) $(FLAGS) $(GCFLAGS_S) -o $@ -c $<

$(OBJ_PATH_C)%.o: $(SRC_PATH_C)%.c
		@$(G) $(FLAGS) $(GCFLAGS_C) -o $@ -c $<

%.o: %.c
		$(G) $(FLAGS) -c $< -o $@

clean:
		@make -C libft/ clean
			@rm -f $(OBJ_S)
				@rm -f $(OBJ_C)

fclean: clean
		@make -C libft/ fclean
			@rm -f $(NAME_S) $(NAME_C)

re: fclean all
		@make -C libft/ re
