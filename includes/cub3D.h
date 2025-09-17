#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include <math.h>
# include <float.h>
// # include <mlx.h>

#define TILE_SIZE 32
#define MINI_MAP_VECTOR 1
#define FOV_ANGLE (60 * M_PI / 180)
#define NUM_RAYS 800


#define CEILING_COLOR 0x87CEEBFF
#define FLOOR_COLOR 0x8B4513FF
#define WALL_COLOR_NR 0x808080FF
#define WALL_COLOR_EW 0x606060FF


typedef struct s_horiz_var{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	nextHorizTouchX;
	float	nextHorizTouchY;
	float	xToCheck;
	float	yToCheck;
	int		maxIterations;
} t_horiz;

typedef struct s_vert_var{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	nextVertTouchX;
	float	nextVertTouchY;
	float	xToCheck;
	float	yToCheck;
	int		maxIterations;
} t_vert;

typedef struct s_player_var{
	int	i;
	int	j;
	int	px;
	int	py;
} t_player_v;

typedef struct s_line {
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	color;
} t_line;


typedef struct s_line_v {
	int	dx;
	int	dy;
	int	steps;
	float	x;
	float	y;
} t_line_v;

typedef struct s_ray {
	float	rayAngle; 
	float	wallHitX;
	float	wallHitY;
	float	distance; 
	int		wallHitHorizontal;
	int		wallHitVertical; 
	int		isRayFacingUp; 
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int		wasHitVertical; 
	int		wallHitContent;
	int		foundHorizontalWallHit;
	float	horizWallHitX;
	float	horizWallHitY;
	int		foundVertWallHit;
	float	wallVertHitX;
	float	wallVertHitY;
} t_ray;

typedef struct s_player {
	float player_x;
	float player_y;
	float p_width; 
	float p_height;
	float turnDirection;
	int walkDirection; 
	float rotationAngle;
	float walkSpeed; 
	float turnSpeed; 
	int is_init; 
} t_player; 
		 
		 
typedef struct s_game { 
	t_gc *gc; char **map; 
	char **paths; 
	char *no_path; 
	char *so_path; 
	char *we_path; 
	char *ea_path; 
	char *f_color; 
	char *c_color; 
	int is_player; 
	int m_height;
	int m_width;
	int win_width;
	int win_height;
	int mini_map_width; 
	int mini_map_height; 
	int mini_map_tile;
	void *win; 
	void *mlx; 
	mlx_image_t *img;
	long last_frame_ms;
	t_player player;
	t_ray *ray;
	int	isRayFacingDown;
	int	isRayFacingUp;
	int isRayFacingRight;
	int isRayFacingLeft;
} t_game;

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
int		init_cub_window(t_game *game);
void	draw_3D_wall(t_game *game);
void	init(t_game *game);
long	get_current_time(void);
int		check_for_collision(t_game *game, int newPlayerX, int newPlayerY);
float	distance_between_points(float x1, float  y1, float x2, float y2);
int		is_wall(t_game *game, float x, float y);
float	normalize_angle(float rayAngle);
void	draw_line(void *win, t_line line);
void	draw_all_lines(t_game *game);
void	draw_player_direction(t_game *game);
void	draw_player(t_game *game);
void	init_player_position(t_game *game, int x, int y);
void	castHorizontalRay(t_game *game, float rayAngle, t_ray *ray);
void	castVerticalRay(t_game *game, float rayAngle, t_ray *ray);
void	render(t_game *game);
void	draw_mini_map(t_game *game);
void	game_loop(void *param);
void	castAllRays(t_game *game);
void	draw_map(t_game *game);

#endif