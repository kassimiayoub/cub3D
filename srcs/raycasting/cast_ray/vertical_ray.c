/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:01:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/03 11:07:34 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_it_vert(t_game *game, t_vert vert, t_ray *ray)
{
	while (vert.next_vert_touchx >= 0
		&& vert.next_vert_touchx < game->win_width
		&& vert.next_vert_touchy >= 0
		&& vert.next_vert_touchy < game->win_height)
	{
		vert.x_to_check = vert.next_vert_touchx;
		if (ray->is_ray_facing_left)
			vert.x_to_check -= 1;
		vert.y_to_check = vert.next_vert_touchy;
		if (check_for_collision_1(game, vert.x_to_check, vert.y_to_check))
		{
			ray->found_vert_wall_hit = 1;
			ray->wall_vert_hitx = vert.next_vert_touchx;
			ray->wall_vert_hity = vert.next_vert_touchy;
			break ;
		}
		else
		{
			vert.next_vert_touchx += vert.xstep;
			vert.next_vert_touchy += vert.ystep;
		}
	}
}

void	init_cast_vert(t_game *game, t_vert vert, t_ray *ray, float rayAngle)
{
	vert.yintercept = game->player.player_y
		+ (vert.xintercept - game->player.player_x) * tan(rayAngle);
	if (ray->is_ray_facing_left)
		vert.xstep = -TILE_SIZE;
	else
		vert.xstep = TILE_SIZE;
	vert.ystep = vert.xstep * tan(rayAngle);
	vert.next_vert_touchx = vert.xintercept;
	vert.next_vert_touchy = vert.yintercept;
	cast_it_vert(game, vert, ray);
}

void	cast_vertical_ray(t_game *game, float rayAngle, t_ray *ray)
{
	t_vert	vert;

	ray->found_vert_wall_hit = 0;
	ray->wall_vert_hitx = 0;
	ray->wall_vert_hity = 0;
	vert.xintercept = floor(game->player.player_x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_right)
		vert.xintercept += TILE_SIZE;
	init_cast_vert(game, vert, ray, rayAngle);
}
