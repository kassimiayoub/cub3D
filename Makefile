CC = cc 

FLAGS = -Wall -Werror -Wextra -Iincludes -Ilib/MLX42/include -I$(HOME)/glfw/include #-fsanitize=address -g

MLX42_LIB = $(HOME)/MLX42_build/libmlx42.a 
GLFW_DIR = /mnt/homes/iaskour/Desktop/glfw-3.4.bin.MACOS

LIBS = $(MLX42_LIB) -L$(HOME)/glfw/lib-universal -lglfw3

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm -framework CoreVideo

NAME = cub3D

HEADER = includes/cub3D.h

HEADERGNL = includes/get_next_line.h

SRCP = srcs/parsing/main.c srcs/parsing/parsing_utilis.c srcs/parsing/parsing_utilis_one.c \
	srcs/parsing/parsing_utilis_two.c srcs/parsing/parsing_utilis_three.c \
	lib/ft_isalnum.c lib/ft_split.c lib/ft_strcmp.c lib/ft_isdigit.c lib/ft_atoi.c\
	lib/garbage_collector/gc_malloc.c lib/garbage_collector/gc_exist.c \
	lib/garbage_collector/gc_clear.c \


SRCSGNL = lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

SRCR = srcs/raycasting/ray_casting.c

OBJP = $(SRCP:%.c=%.o)

OBJSGNL = $(SRCSGNL:%.c=%.o)

OBJR = $(SRCR:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJP) $(OBJR) $(OBJSGNL)
	$(CC) $(FLAGS) $(OBJP) $(OBJR) $(OBJSGNL) $(LIBS) $(FRAMEWORKS) -o $(NAME) 

%.o: %.c $(HEADER) $(HEADERGNL)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJP) $(OBJR) $(OBJSGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all