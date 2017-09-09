NAME_P = server
NAME_C = clien
G = gcc
FLAGS = -Wall -Wextra -Werror
SRC_P = server.c \

OBJ_P = $(SRC_P:.c=.o)

SRC_C = client.c \

OBJ_C = $(SRC_C:.c=.o)

all: $(NAME_P) $(NAME_C)
$(NAME_P): $(OBJ_P)
	@$(G) $(FLAGS) -o $@ $(OBJ_P)
$(NAME_C): $(OBJ_C)
	@$(G) $(FLAGS) -o $@ $(OBJ_C)

clean:
	@rm -f $(OBJ_P)
	@rm -f $(OBJ_C)

fclean: clean
	@rm -f $(NAME_P) $(NAME_C)

re: fclean all

