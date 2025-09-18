CC = cc 

FLAGS = -Wall -Werror -Wextra -Iincludes -I$(HOME)/Desktop/MLX42/include -I$(HOME)/Desktop/glfw/include -fsanitize=address -g

MLX42_LIB = $(HOME)/Desktop/MLX42/build/libmlx42.a 
GLFW_DIR = $(HOME)/Desktop/glfw/build/src

LIBS = $(MLX42_LIB) -L$(GLFW_DIR) -lglfw3 -lm -ldl -pthread

# FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm -framework CoreVideo

NAME = cub3D

HEADER = includes/cub3D.h

HEADERGNL = includes/get_next_line.h

SRCP = srcs/parsing/main.c srcs/parsing/parsing_utilis.c srcs/parsing/parsing_utilis_one.c \
	srcs/parsing/parsing_utilis_two.c srcs/parsing/parsing_utilis_three.c \
	lib/ft_isalnum.c lib/ft_split.c lib/ft_strcmp.c lib/ft_isdigit.c lib/ft_atoi.c\
	lib/garbage_collector/gc_malloc.c lib/garbage_collector/gc_exist.c \
	lib/garbage_collector/gc_clear.c \


SRCSGNL = lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

SRCR = srcs/raycasting/init.c srcs/raycasting/raycasting_main.c srcs/raycasting/utils.c \
	srcs/raycasting/cast_ray/cast_all_rays.c srcs/raycasting/cast_ray/horizontal_ray.c srcs/raycasting/cast_ray/vertical_ray.c \
	srcs/raycasting/drawing/draw_3D_walls.c srcs/raycasting/drawing/draw_line_and_player.c srcs/raycasting/drawing/draw_map_and_minimap.c \
	srcs/raycasting/main_loop/game_loop.c

OBJP = $(SRCP:%.c=%.o)

OBJSGNL = $(SRCSGNL:%.c=%.o)

OBJR = $(SRCR:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJP) $(OBJR) $(OBJSGNL)
	$(CC) $(FLAGS) $(OBJP) $(OBJR) $(OBJSGNL) $(LIBS) -o $(NAME) 

%.o: %.c $(HEADER) $(HEADERGNL)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJP) $(OBJR) $(OBJSGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all