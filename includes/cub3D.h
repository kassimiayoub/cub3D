#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
// # include <mlx.h>

#define TILE_SIZE 32

typedef struct s_game
{
	t_gc	*gc;
	char	**map;
	char	**paths;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_color;
	char	*c_color;
	int		is_player;
	int		m_height;
	int		m_width;
	void	*win;
	void	*mlx;
}	t_game;

//fil map struct 
typedef struct s_fill_map
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		cm;
}	t_fill_map;

//lib
int		ft_isalnum(int c);
char	**ft_split(t_gc *gc, char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
long	ft_atoi(const char *str);

//garbage collector
void	*gc_malloc(t_gc *gc, size_t size);
int		gc_exist(t_gc *gc, void *ptr);
void	gc_clear(t_gc *gc);

//parsing_utilis
int		read_map(t_game **game, char *map);

//parsing_utilis_One
int		map_extension(char *str);
int		detect_isline_map(char *str);
char	*new_updated_line(t_gc *gc, int size, char *line);
char	*new_paths_line(t_gc *gc, char *line);
int		count_nbr_line(char **map);

//parsing_utilis_Two
int		validate_color(t_gc *gc, char *color);
int		validat_line(t_game **game, char *line);
int		validate_path(t_game **game);

//parsing_utilis_Three
int		detect_map_is_valid(t_game *game);
int		initial_fillmap(t_game **game, char *map, t_fill_map **tf);
int		add_line_path(t_game **game, char *line, int j);
int		add_line_map(t_game **game, char *line, int *cm, int *i);




// recasting
int init_cub_window(t_game *game);

#endif