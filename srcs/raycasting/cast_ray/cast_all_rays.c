/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:09:05 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/20 10:52:49 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	case_no_wall_hit(t_game *game, float ray_angle, int strip_id)
{
	if (game->horizHitDistance == FLT_MAX && game->vertHitDistance == FLT_MAX)
	{
		game->ray[strip_id].wallHitX = game->player.player_x
			+ cos(ray_angle) * (TILE_SIZE * 20);
		game->ray[strip_id].wallHitY = game->player.player_y
			+ sin(ray_angle) * (TILE_SIZE * 20);
		game->ray[strip_id].distance = TILE_SIZE * 20;
		game->ray[strip_id].wasHitVertical = 0;
		return (1);
	}
	return (0);
}

void	choose_distance(t_game *game, float ray_angle, int strip_id, t_ray *ray)
{
	game->horizHitDistance = FLT_MAX;
	game->vertHitDistance = FLT_MAX;
	if (ray->foundHorizontalWallHit)
		game->horizHitDistance = distance_between_points(game->player.player_x,
				game->player.player_y, ray->horizWallHitX, ray->horizWallHitY);
	if (ray->foundVertWallHit)
		game->vertHitDistance = distance_between_points(game->player.player_x,
				game->player.player_y, ray->wallVertHitX, ray->wallVertHitY);
	if (case_no_wall_hit(game, ray_angle, strip_id) == 0)
	{
		game->ray[strip_id].wallHitX = ray->horizWallHitX;
		game->ray[strip_id].wallHitY = ray->horizWallHitY;
		game->ray[strip_id].distance = game->vertHitDistance;
		game->ray[strip_id].wasHitVertical = 0;
		if (game->horizHitDistance < game->vertHitDistance)
		{
			game->ray[strip_id].wallHitX = ray->wallVertHitX;
			game->ray[strip_id].wallHitY = ray->wallVertHitY;
			game->ray[strip_id].distance = game->horizHitDistance;
			game->ray[strip_id].wasHitVertical = 1;
		}
	}
}

void	cast_ray(t_game *game, float ray_angle, int strip_id, t_ray *ray)
{
	ray_angle = normalize_angle(ray_angle);
	ray->isRayFacingDown = ray_angle > 0 && ray_angle < M_PI;
	ray->isRayFacingUp = !ray->isRayFacingDown;
	ray->isRayFacingRight = ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2;
	ray->isRayFacingLeft = !ray->isRayFacingRight;
	cast_horizontal_ray(game, ray_angle, ray);
	cast_vertical_ray(game, ray_angle, ray);
	choose_distance(game, ray_angle, strip_id, ray);
	game->ray[strip_id].distance *= cos(ray_angle - game->player.rotationAngle);
	game->ray[strip_id].ray_angle = ray_angle;
	game->ray[strip_id].isRayFacingDown = ray->isRayFacingDown;
	game->ray[strip_id].isRayFacingUp = ray->isRayFacingUp;
	game->ray[strip_id].isRayFacingLeft = ray->isRayFacingLeft;
	game->ray[strip_id].isRayFacingRight = ray->isRayFacingRight;
}

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int		strip_id;

	if (!game || !game->map || !game->player.is_init)
		return ;
	ray_angle = game->player.rotationAngle - (FOV_ANGLE / 2);
	angle_step = FOV_ANGLE / NUM_RAYS;
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(game, ray_angle, strip_id, game->ray);
		ray_angle += angle_step;
		strip_id++;
	}
}
