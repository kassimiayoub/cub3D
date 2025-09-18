/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:01:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/18 10:24:46 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_it_vert(t_game *game, t_vert vert, t_ray *ray)
{
	while (vert.maxIterations-- > 0 && vert.nextVertTouchX >= 0
		&& vert.nextVertTouchX < (game->m_width * TILE_SIZE)
		&& vert.nextVertTouchY >= 0
		&& vert.nextVertTouchY < (game->m_height * TILE_SIZE))
	{
		vert.xToCheck = vert.nextVertTouchX;
		if (ray->isRayFacingLeft)
			vert.xToCheck = vert.nextVertTouchX - 1;
		vert.yToCheck = vert.nextVertTouchY;
		if (check_for_collision(game, vert.xToCheck, vert.yToCheck))
		{
			ray->foundVertWallHit = 1;
			ray->wallVertHitX = vert.nextVertTouchX;
			ray->wallVertHitY = vert.nextVertTouchY;
			break ;
		}
		else
		{
			vert.nextVertTouchX += vert.xstep;
			vert.nextVertTouchY += vert.ystep;
		}
	}
}

void	init_cast_vert(t_game *game, t_vert vert, t_ray *ray, float rayAngle)
{
	vert.yintercept = game->player.player_y
		+ (vert.xintercept - game->player.player_x) * tan(rayAngle);
	if (ray->isRayFacingLeft)
		vert.xstep = -TILE_SIZE;
	else
		vert.xstep = TILE_SIZE;
	vert.ystep = vert.xstep * tan(rayAngle);
	if ((ray->isRayFacingUp && vert.ystep > 0)
		|| (ray->isRayFacingDown && vert.ystep < 0))
		vert.ystep = -vert.ystep;
	vert.nextVertTouchX = vert.xintercept;
	vert.nextVertTouchY = vert.yintercept;
	vert.maxIterations = 100;
	cast_it_vert(game, vert, ray);
}

void	cast_vertical_ray(t_game *game, float rayAngle, t_ray *ray)
{
	t_vert	vert;

	ray->foundVertWallHit = 0;
	ray->wallVertHitX = 0;
	ray->wallVertHitY = 0;
	vert.xintercept = floor(game->player.player_x / TILE_SIZE) * TILE_SIZE;
	if (ray->isRayFacingRight)
		vert.xintercept += TILE_SIZE;
	if (fabs(cos(rayAngle)) < 0.0001)
	{
		ray->foundVertWallHit = 0;
		ray->wallVertHitX = 0;
		ray->wallVertHitY = 0;
	}
	else
		init_cast_vert(game, vert, ray, rayAngle);
}
