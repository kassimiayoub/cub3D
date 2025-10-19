/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:51:56 by aykassim          #+#    #+#             */
/*   Updated: 2025/10/18 16:07:48 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	float	hit_offset;

	if (ray->wasHitVertical)
		hit_offset = fmod(ray->wallHitY, TILE_SIZE) / TILE_SIZE;
	else
		hit_offset = fmod(ray->wallHitX, TILE_SIZE) / TILE_SIZE;
	xtex = (int)(hit_offset * tex_width);
	return (xtex);
}

int	count_ytex(int wall_top, int wall_bottom, int tex_height, int y)
{
	int		ytex;
	float	wall_height;
	float	tex_pos;

	wall_height = wall_bottom - wall_top;
	tex_pos = (y - wall_top) / wall_height;
	ytex = (int)(tex_pos * tex_height);
	return (ytex);
}

void	draw_walls(t_game *game, t_draw_text *draw)
{
	draw->y = 0;
	while (draw->y < game->win_height)
	{
		if (draw->y < draw->wall_top)
			draw->color = game->ceil_color;
		else if (draw->y >= draw->wall_top && draw->y <= draw->wall_bottom)
		{
			draw->ytex = count_ytex(draw->wall_top, draw->wall_bottom,
					draw->texture->height, draw->y);
			draw->idx = (draw->ytex * draw->texture->width + draw->xtex) * 4;
			draw->color = ft_rgba(draw->texture->pixels[draw->idx],
					draw->texture->pixels[draw->idx + 1],
					draw->texture->pixels[draw->idx + 2],
					draw->texture->pixels[draw->idx + 3]);
		}
		else
			draw->color = game->floor_color;
		mlx_put_pixel(game->img, draw->x, draw->y, draw->color);
		draw->y++;
	}
}

void	draw_3D_textures(t_game *game)
{
	t_draw_text	draw;

	draw.x = 0;
	while (draw.x < game->win_width)
	{
		draw.ray = &game->ray[draw.x];
		draw.proj_height = (TILE_SIZE * game->win_height) / draw.ray->distance;
		draw.wall_top = (int)((game->win_height - draw.proj_height) / 2);
		draw.wall_bottom = (int)((game->win_height + draw.proj_height) / 2);
		if (draw.wall_top < 0)
			draw.wall_top = 0;
		if (draw.wall_bottom >= game->win_height)
			draw.wall_bottom = game->win_height - 1;
		draw.texture = detect_texture(game, draw.ray);
		draw.xtex = count_xtex(draw.ray, draw.texture->width);
		draw_walls(game, &draw);
		draw.x++;
	}
}
