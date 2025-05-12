SRC=main.c

NAME=cub

all: $(NAME)

$(NAME):
	cc -lmlx -framework OpenGL -framework AppKit $(SRC)  -o $(NAME)
re:
	rm -f $(NAME)
	make all