/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:26:53 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/06 13:47:05 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include <float.h>

# define TILE_SIZE 32
# define FOV_ANGLE 1.0471975512

typedef struct s_horiz_var
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	next_horiz_touchx;
	float	next_horiz_touchy;
	float	x_to_check;
	float	y_to_check;
	int		max_iterations;
}	t_horiz;

typedef struct s_vert_var
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	next_vert_touchx;
	float	next_vert_touchy;
	float	x_to_check;
	float	y_to_check;
	int		max_iterations;
}	t_vert;

typedef struct s_player_var
{
	int	i;
	int	j;
	int	px;
	int	py;
}	t_player_v;

typedef struct s_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	color;
}	t_line;

typedef struct s_line_v
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;
}	t_line_v;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hitx;
	float	wall_hity;
	float	distance;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		was_hit_vertical;
	int		found_horizontal_wall_hit;
	float	horiz_wall_hitx;
	float	horiz_wall_hity;
	int		found_vert_wall_hit;
	float	wall_vert_hitx;
	float	wall_vert_hity;
}	t_ray;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	p_width;
	float	p_height;
	float	turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	int		is_init;
}	t_player;

typedef struct s_game
{
	t_gc		*gc;
	char		**map;
	char		**paths;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*f_color;
	char		*c_color;
	uint32_t	ceil_color;
	uint32_t	floor_color;
	mlx_image_t	*no_texture;
	mlx_image_t	*so_texture;
	mlx_image_t	*we_texture;
	mlx_image_t	*ea_texture;
	int			is_player;
	int			m_height;
	int			m_width;
	int			win_width;
	int			win_height;
	void		*win;
	void		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_ray		*ray;
	float		horiz_hit_distance;
	float		vert_hit_distance;
	int			is_game_started;
}	t_game;

typedef struct s_fill_map
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	int		cm;
}	t_fill_map;

typedef struct s_draw_text
{
	int			x;
	int			y;
	uint32_t	color;
	t_ray		*ray;
	float		proj_height;
	int			wall_top;
	int			wall_bottom;
	mlx_image_t	*texture;
	int			xtex;
	int			ytex;
	int			idx;
}	t_draw_text;

int			ft_isalnum(int c);
char		**ft_split(t_gc *gc, char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
long		ft_atoi(const char *str);
void		*gc_malloc(t_gc *gc, size_t size);
int			gc_exist(t_gc *gc, void *ptr);
void		gc_clear(t_gc *gc);
int			read_map(t_game **game, char *map);
int			map_extension(char *str);
int			detect_isline_map(char *str);
char		*new_updated_line(t_gc *gc, int size, char *line);
char		*new_paths_line(t_gc *gc, char *line);
int			count_nbr_line(char **map);
int			validate_color(t_gc *gc, char *color);
int			validat_line(t_game **game, char *line);
int			validate_path(t_game **game);
int			convert_color_to_rgb(t_game **game);
int			check_first_args(t_game **game, char *str, char *str1);
int			detect_map_is_valid(t_game *game);
int			initial_fillmap(t_game **game, char *map, t_fill_map **tf);
int			add_line_path(t_game **game, char *line, int j);
int			add_line_map(t_game **game, char *line, int *cm, int *i);
void		draw_3d_textures(t_game *game);
int			load_images(t_game **game);
int			check_all_pathimg(t_game *game);
uint32_t	ft_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int			init(t_game **game);
int			check_for_collision(t_game *game, int newPlayerX, int newPlayerY);
float		distance_between_points(float x1, float y1, float x2, float y2);
float		normalize_angle(float rayAngle);
void		init_player_position(t_game *game, int x, int y);
void		cast_horizontal_ray(t_game *game, float rayAngle, t_ray *ray);
void		cast_vertical_ray(t_game *game, float rayAngle, t_ray *ray);
void		render(t_game *game);
void		game_loop(void *param);
void		cast_all_rays(t_game *game);
int			check_for_collision_1(t_game *game, int newPlayerX, int newPlayerY);
int			checker(t_game *game, int map_x, int map_y);
void		free_all(t_game *game);

#endif