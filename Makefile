CC = cc 

FLAGS = -Wall -Werror -Wextra -Iincludes -fsanitize=address -g

NAME = cub3D

HEADER = includes/cub3D.h

HEADERGNL = includes/get_next_line.h

SRCP = srcs/parsing/main.c srcs/parsing/parsing_utilis.c \
	lib/ft_isalnum.c

SRCSGNL = lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

OBJP = $(SRCP:%.c=%.o)

OBJSGNL = $(SRCSGNL:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJP) $(OBJSGNL)
	$(CC) $(FLAGS) $(OBJP) $(OBJSGNL) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJP) $(OBJSGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all