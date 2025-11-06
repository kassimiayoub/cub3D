/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:09:05 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/03 11:07:16 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	distance_checker(t_game *game, t_ray *ray)
{
	if (ray->found_horizontal_wall_hit)
		game->horiz_hit_distance = distance_between_points(
				game->player.player_x,
				game->player.player_y,
				ray->horiz_wall_hitx,
				ray->horiz_wall_hity
				);
	if (ray->found_vert_wall_hit)
		game->vert_hit_distance = distance_between_points(
				game->player.player_x,
				game->player.player_y,
				ray->wall_vert_hitx,
				ray->wall_vert_hity
				);
}

void	choose_distance(t_game *game, int strip_id, t_ray *ray)
{
	game->horiz_hit_distance = FLT_MAX;
	game->vert_hit_distance = FLT_MAX;
	distance_checker(game, ray);
	game->ray[strip_id].wall_hitx = ray->horiz_wall_hitx;
	game->ray[strip_id].wall_hity = ray->horiz_wall_hity;
	game->ray[strip_id].distance = game->horiz_hit_distance;
	game->ray[strip_id].was_hit_vertical = 0;
	if (game->vert_hit_distance < game->horiz_hit_distance)
	{
		game->ray[strip_id].wall_hitx = ray->wall_vert_hitx;
		game->ray[strip_id].wall_hity = ray->wall_vert_hity;
		game->ray[strip_id].distance = game->vert_hit_distance;
		game->ray[strip_id].was_hit_vertical = 1;
	}
}

void	cast_ray(t_game *game, float ray_angle, int strip_id, t_ray *ray)
{
	ray_angle = normalize_angle(ray_angle);
	ray->is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2;
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
	cast_horizontal_ray(game, ray_angle, ray);
	cast_vertical_ray(game, ray_angle, ray);
	choose_distance(game, strip_id, ray);
	game->ray[strip_id].distance
		*= cos(ray_angle - game->player.rotation_angle);
}

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int		strip_id;
	int		numrays;

	numrays = game->win_width;
	if (!game || !game->map || !game->player.is_init)
		return ;
	ray_angle = game->player.rotation_angle - (FOV_ANGLE / 2);
	angle_step = FOV_ANGLE / numrays;
	strip_id = 0;
	while (strip_id < numrays)
	{
		cast_ray(game, ray_angle, strip_id, &game->ray[strip_id]);
		ray_angle += angle_step;
		strip_id++;
	}
}
