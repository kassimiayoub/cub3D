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

// int	count_xtex(t_ray *ray, int tex_width)
// {
// 	// float	val;
// 	// int		res;

// 	// if (ray->wasHitVertical)
// 	// 	val = fmodf(ray->wallHitY, TILE_SIZE);
// 	// else
// 	// 	val = fmodf(ray->wallHitX, TILE_SIZE);
// 	// res = (int)(val / TILE_SIZE * tex_width);
// 	// return (res);
// }

int	count_xtex(t_ray *ray, int tex_width)
{
	float	offset;
	int		xtex;

	if (ray->wasHitVertical)
	{
		offset = fmodf(ray->wallHitY, TILE_SIZE);
		xtex = (int)(offset / TILE_SIZE * tex_width);
		// Flip for vertical walls facing left
		if (!ray->isRayFacingRight)
			xtex = tex_width - xtex - 1;
	}
	else
	{
		offset = fmodf(ray->wallHitX, TILE_SIZE);
		xtex = (int)(offset / TILE_SIZE * tex_width);
		// Flip for horizontal walls facing up
		if (ray->isRayFacingUp)
			xtex = tex_width - xtex - 1;
	}
	
	// Ensure within bounds
	if (xtex < 0) xtex = 0;
	if (xtex >= tex_width) xtex = tex_width - 1;
	
	return (xtex);
}

int	count_ytex(int wall_top, int projected_height, float tex_height, int index)
{
	int	res;
	float	distfromtop;
	float ratio;

	distfromtop = index - wall_top;
	ratio = distfromtop / projected_height;
	res = ((int)(ratio * tex_height));
	return (res);
}

void draw_3D_textures(t_game *game)
{
	int				x;
	int				y;
	t_ray			*ray;
	float			projected_height;
	int				wall_top;
	int				wall_bottom;
	uint32_t		color;
	mlx_image_t		*texture;
	int				xtex;
	int				ytex;

	x = 0;
	while (x < game->win_width)
	{
		int ray_index = (int)((float)x / game->win_width * NUM_RAYS);
		if (ray_index >= NUM_RAYS)
			ray_index = NUM_RAYS - 1;
		ray = &game->ray[ray_index];

		if (ray->distance >= FLT_MAX)
		{
			y = 0;
			while (y < game->win_height)
			{
				color = (y < game->win_height / 2) ? game->ceil_color : game->floor_color;
				mlx_put_pixel(game->img, x, y, color);
				y++;
			}
			x++;
			continue;
		}

		projected_height = (TILE_SIZE * game->win_height) / ray->distance;
		wall_top = (int)((game->win_height - projected_height) / 2);
		wall_bottom = (int)((game->win_height + projected_height) / 2);
		
		if (wall_top < 0) wall_top = 0;
		if (wall_bottom >= game->win_height) wall_bottom = game->win_height - 1;

		texture = detect_texture(game, ray);
		if (!texture || !texture->pixels)
		{
			x++;
			continue;
		}

		xtex = count_xtex(ray, texture->width);

		// Draw ceiling
		y = 0;
		while (y < wall_top)
		{
			mlx_put_pixel(game->img, x, y, game->ceil_color);
			y++;
		}

		// Draw wall with per-pixel calculation (no stepping)
		y = wall_top;
		while (y <= wall_bottom)
		{
			// Calculate texture Y for each pixel
			float ratio = (float)(y - wall_top) / (wall_bottom - wall_top);
			ytex = (int)(ratio * texture->height);
			
			if (ytex < 0) ytex = 0;
			if (ytex >= (int)texture->height) ytex = texture->height - 1;
			
			color = ((uint32_t *)texture->pixels)[ytex * texture->width + xtex];
			mlx_put_pixel(game->img, x, y, color);
			y++;
		}

		// Draw floor
		y = wall_bottom + 1;
		while (y < game->win_height)
		{
			mlx_put_pixel(game->img, x, y, game->floor_color);
			y++;
		}

		x++;
	}
}

// void draw_3D_textures(t_game *game)
// {
//     int			x;
// 	int			y;
//     uint32_t	color;
// 	t_ray		*ray;
// 	float		projected_height;
//     int			wall_top;
// 	int			wall_bottom;
// 	int			ray_index;
// 	mlx_image_t	*texture;
// 	int			xtex;
// 	int			ytex;
// 	x = 0;
//   	while (x < game->win_width)
//     {
// 		// pick the corresponding ray for this screen column
// 		ray_index = (int)((float)x / game->win_width * NUM_RAYS);
//         if (ray_index >= NUM_RAYS)
//             ray_index = NUM_RAYS - 1;
//         ray = &game->ray[ray_index];

// 		projected_height = (TILE_SIZE * game->win_height) / ray->distance;
//         wall_top = (int)((game->win_height - projected_height) / 2);
//         wall_bottom = (int)((game->win_height + projected_height) / 2);
// 		if (wall_top < 0)
// 			wall_top = 0;
//         if (wall_bottom >= game->win_height)
// 			wall_bottom = game->win_height - 1;
// 		texture = detect_texture(game, ray);
// 		xtex = count_xtex(ray, texture->width);

// 		y = 0;
//         while (y < game->win_height)
// 		{
// 			if (y < game->win_height / 2)
// 				color = game->ceil_color;
//         	else
// 				color = game->floor_color;
//             mlx_put_pixel(game->img, x, y, color);
// 			y++;
// 		}
// 		y = 0;
// 		while (y < game->win_height)
// 		{
// 			if (y >= wall_top && y <= wall_bottom)
// 			{
// 				ytex = count_ytex(wall_top, projected_height, texture->height, y);
//                 color = ((uint32_t*)texture->pixels)[ytex * texture->width + xtex];
// 			}
//             mlx_put_pixel(game->img, x, y, color);
// 			y++;
// 		}
// 		x++;
//     }
// }


// void	draw_3D_textures(t_game *game)
// {
// 	int			x;
// 	int			y;
// 	float		ray_per_pixel;
// 	int			ray_index;
// 	t_ray		*ray;
// 	float		projected_height;
// 	int			wall_top;
// 	int			wall_bottom;
// 	uint32_t	color;
// 	mlx_image_t	*texture;
// 	int xtex;
// 	int ytex;

// 	ray_per_pixel = (float)NUM_RAYS / game->win_width;
// 	x = 0;
// 	while (x < game->win_width)
// 	{
// 		ray_index = (int)(x * ray_per_pixel);
// 		if (ray_index >= NUM_RAYS)
// 			ray_index = NUM_RAYS - 1;
// 		ray = &game->ray[ray_index];
// 		if (ray->distance >= FLT_MAX)
//         {
//             y = 0;
//             while (y < game->win_height)
//             {
//                 if (y < game->win_height / 2)
//                     color = game->ceil_color;
//                 else
//                     color = game->floor_color;
//                 mlx_put_pixel(game->img, x, y, color);
//                 y++;
//             }
//             x++;
//             continue;
//         }
// 		projected_height = (TILE_SIZE * game->win_height) / ray->distance;
// 		wall_top = (int)((game->win_height - projected_height) / 2);
// 		wall_bottom = (int)((game->win_height + projected_height) / 2);
// 		if (wall_top < 0)
// 			wall_top = 0;
// 		if (wall_bottom >= game->win_height)
// 			wall_bottom = game->win_height - 1;
// 		texture = detect_texture(game, ray);
// 		xtex = count_xtex(ray, texture->width);
// 		if (xtex < 0)
//             xtex = 0;
//         if (xtex >= (int)texture->width)
//             xtex = texture->width - 1;
// 		y = 0;
// 		while(y < game->win_height)
// 		{
// 			if (y < wall_top)
// 				color = game->ceil_color;
// 			else if (y >= wall_top && y <= wall_bottom)
// 			{
// 				if (!texture || !texture->pixels)
//                 	color = game->ceil_color;
// 				else
// 				{
// 					ytex = count_ytex(wall_top, projected_height, texture->height, y);
// 					if (ytex < 0)
// 					ytex = 0;
// 					if (ytex >= (int)texture->height)
// 					ytex = (int)texture->height - 1;
// 					color = ((uint32_t *)texture->pixels)[ytex * texture->width + xtex];
// 				}
// 			}
// 			else
// 				color = game->floor_color;
// 			mlx_put_pixel(game->img, x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }
