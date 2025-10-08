#include "cub3D.h"

// int load_images(t_game **game)
// {
//     (*game)->no_texture = mlx_load_png((*game)->no_path);
//     if (!(*game)->no_texture)
//         return (0);
//     (*game)->so_texture = mlx_load_png((*game)->so_path);
//     if (!(*game)->so_texture)
//         return (0);
//     (*game)->we_texture = mlx_load_png((*game)->we_path);
//     if (!(*game)->we_texture)
//         return (0);
//     (*game)->ea_texture = mlx_load_png((*game)->ea_path);
//     if (!(*game)->ea_texture)
//         return (0);
//     return (1);
// }

int load_images(t_game **game)
{
    mlx_texture_t *tmp;

    tmp = mlx_load_png((*game)->no_path);
    if (!tmp)
		return (0);
    (*game)->no_texture = mlx_texture_to_image((*game)->mlx, tmp);
	if (!(*game)->no_texture)
    	return (0);
    mlx_delete_texture(tmp);

    tmp = mlx_load_png((*game)->so_path);
    if (!tmp)
		return (0);
    (*game)->so_texture = mlx_texture_to_image((*game)->mlx, tmp);
	if (!(*game)->so_texture)
 		return (0);
    mlx_delete_texture(tmp);

    tmp = mlx_load_png((*game)->we_path);
    if (!tmp)
		return (0);
    (*game)->we_texture = mlx_texture_to_image((*game)->mlx, tmp);
	if (!(*game)->we_texture)
 		return (0);
    mlx_delete_texture(tmp);

    tmp = mlx_load_png((*game)->ea_path);
    if (!tmp)
		return (0);
    (*game)->ea_texture = mlx_texture_to_image((*game)->mlx, tmp);
	if (!(*game)->ea_texture)
 		return (0);
    mlx_delete_texture(tmp);

    return (1);
}


mlx_image_t	*detect_texture(t_game *game, t_ray *ray)
{
	mlx_image_t	*texture;

	if (ray->wasHitVertical)
	{
		if (ray->isRayFacingRight)
			texture = game->ea_texture;
		else
			texture = game->we_texture;
	}
	else
	{
		if (ray->isRayFacingUp)
			texture = game->no_texture;
		else
			texture = game->so_texture;
	}
	return (texture);
}

int	count_xtex(t_ray *ray, int tex_width)
{
	int		xtex;
	float hit_offset;

	if (ray->wasHitVertical)
		hit_offset = fmod(ray->wallHitY, TILE_SIZE) / TILE_SIZE;
	else
		hit_offset = fmod(ray->wallHitX, TILE_SIZE) / TILE_SIZE;
	xtex = (int)(hit_offset * tex_width);
	return (xtex);
}

int	count_ytex(int wall_top, int wall_bottom, int tex_height, int y)
{
	int	ytex;
	float wall_height = wall_bottom - wall_top;
	float tex_pos = (y - wall_top) / wall_height;
	ytex = (int)(tex_pos * tex_height);
	return (ytex);
}

uint32_t ft_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void draw_3D_textures(t_game *game)
{
    int			x;
	int			y;
    uint32_t	color;
	t_ray		*ray;
	float		projected_height;
    int			wall_top;
	int			wall_bottom;
	mlx_image_t	*texture;
	int			xtex;
	int			ytex;

	x = 0;
  	while (x < game->win_width)
    {
        ray = &game->ray[x];
		projected_height = (TILE_SIZE * game->win_height) / ray->distance;
        wall_top = (int)((game->win_height - projected_height) / 2);
        wall_bottom = (int)((game->win_height + projected_height) / 2);
		if (wall_top < 0)
			wall_top = 0;
        if (wall_bottom >= game->win_height)
			wall_bottom = game->win_height - 1;
		texture = detect_texture(game, ray);
		xtex = count_xtex(ray, texture->width);
		y = 0;
        while(y < game->win_height)
		{
			if (y < wall_top)
				color = game->ceil_color;
			else if (y >= wall_top && y <= wall_bottom)
			{
				ytex = count_ytex(wall_top, wall_bottom, texture->height, y);
				int idx = (ytex * texture->width + xtex) * 4;
				color = ft_rgba(texture->pixels[idx], texture->pixels[idx + 1],texture->pixels[idx + 2],texture->pixels[idx + 3]);
			}
			else
				color = game->floor_color;
			mlx_put_pixel(game->img, x, y, color);
			y++;
		}
		x++;
    }
}
