
#include "cub3D.h"

void	draw_3D_wall(t_game *game)
{
	int			x;
	int			y;
	float		ray_per_pixel;
	int			ray_index;
	t_ray		*ray;
	float		projected_height;
	int			wall_top;
	int			wall_bottom;
	uint32_t	wall_color;
	uint32_t	color;

	ray_per_pixel = (float)NUM_RAYS / game->win_width;
	x = 0;
	while (x < game->win_width)
	{
		ray_index = (int)(x * ray_per_pixel);
		if (ray_index >= NUM_RAYS)
			ray_index = NUM_RAYS - 1;
		ray = &game->ray[ray_index];
		if (ray->distance >= FLT_MAX)
		{
			y = 0;
			while ( y < game->win_height)
			{
				mlx_put_pixel(game->img, x, y, CEILING_COLOR);
				y++;
			}
			continue;
		}
		projected_height = (TILE_SIZE * game->win_height) / ray->distance;
		wall_top = (int)((game->win_height - projected_height) / 2);
		wall_bottom = (int)((game->win_height + projected_height) / 2);
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= game->win_height)
			wall_bottom = game->win_height - 1;
		wall_color = WALL_COLOR_EW;
		if (ray->wasHitVertical)
			wall_color = WALL_COLOR_NR;
		y = 0;
		while(y < game->win_height)
		{
			if (y < wall_top)
				color = CEILING_COLOR;
			else if (y >= wall_top && y <= wall_bottom)
				color = wall_color;
			else
				color = FLOOR_COLOR;
			if (x >= 0 && x < game->win_width && y >= 0 && y < game->win_height)
				mlx_put_pixel(game->img, x, y, color);
			y++;
		}
		x++;
	}
}