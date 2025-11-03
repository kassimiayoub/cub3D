/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:38:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/03 10:59:59 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#include "cub3D.h"

void	cast_it_horiz(t_game *game, t_horiz horiz, t_ray *ray)
{
	while (horiz.next_horiz_touchx >= 0
		&& horiz.next_horiz_touchx < game->win_width
		&& horiz.next_horiz_touchy >= 0
		&& horiz.next_horiz_touchy < game->win_height)
	{
		horiz.x_to_check = horiz.next_horiz_touchx;
		horiz.y_to_check = horiz.next_horiz_touchy;
		if (ray->is_ray_facing_up)
			horiz.y_to_check -= 1;
		if (check_for_collision_1(game, horiz.x_to_check, horiz.y_to_check))
		{
			ray->horiz_wall_hitx = horiz.next_horiz_touchx;
			ray->horiz_wall_hity = horiz.next_horiz_touchy;
			ray->found_horizontal_wall_hit = 1;
			break ;
		}
		else
		{
			horiz.next_horiz_touchx += horiz.xstep;
			horiz.next_horiz_touchy += horiz.ystep;
		}
	}
}

void	init_cast_horiz(t_game *game, t_horiz horiz, t_ray *ray, float rayAngle)
{
	horiz.xintercept = game->player.player_x
		+ (horiz.yintercept - game->player.player_y) / tan(rayAngle);
	if (ray->is_ray_facing_up)
		horiz.ystep = -TILE_SIZE;
	else
		horiz.ystep = TILE_SIZE;
	horiz.xstep = horiz.ystep / tan(rayAngle);
	horiz.next_horiz_touchx = horiz.xintercept;
	horiz.next_horiz_touchy = horiz.yintercept;
	cast_it_horiz(game, horiz, ray);
}

void	cast_horizontal_ray(t_game *game, float rayAngle, t_ray *ray)
{
	t_horiz	horiz;

	ray->found_horizontal_wall_hit = 0;
	ray->horiz_wall_hitx = 0;
	ray->horiz_wall_hity = 0;
	horiz.yintercept = floor(game->player.player_y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_ray_facing_down)
		horiz.yintercept += TILE_SIZE;
	init_cast_horiz(game, horiz, ray, rayAngle);
}
