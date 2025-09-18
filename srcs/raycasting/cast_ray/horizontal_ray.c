/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:38:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/18 10:24:42 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_it_horiz(t_game *game, t_horiz horiz, t_ray *ray)
{
	while (horiz.maxIterations-- > 0 && horiz.nextHorizTouchX >= 0
		&& horiz.nextHorizTouchX < (game->m_width * TILE_SIZE)
		&& horiz.nextHorizTouchY >= 0
		&& horiz.nextHorizTouchY < (game->m_height * TILE_SIZE))
	{
		horiz.xToCheck = horiz.nextHorizTouchX;
		horiz.yToCheck = horiz.nextHorizTouchY;
		if (ray->isRayFacingUp)
			horiz.yToCheck = horiz.nextHorizTouchY - 1;
		if (check_for_collision(game, horiz.xToCheck, horiz.yToCheck))
		{
			ray->horizWallHitX = horiz.nextHorizTouchX;
			ray->horizWallHitY = horiz.nextHorizTouchY;
			ray->foundHorizontalWallHit = 1;
			break ;
		}
		else
		{
			horiz.nextHorizTouchX += horiz.xstep;
			horiz.nextHorizTouchY += horiz.ystep;
		}
	}
}

void	init_cast_horiz(t_game *game, t_horiz horiz, t_ray *ray, float rayAngle)
{
	horiz.xintercept = game->player.player_x
		+ (horiz.yintercept - game->player.player_y) / tan(rayAngle);
	if (ray->isRayFacingUp)
		horiz.ystep = -TILE_SIZE;
	else
		horiz.ystep = TILE_SIZE;
	horiz.xstep = horiz.ystep / tan(rayAngle);
	if ((ray->isRayFacingLeft && horiz.xstep > 0)
		|| (ray->isRayFacingRight && horiz.xstep < 0))
		horiz.xstep = -horiz.xstep;
	horiz.nextHorizTouchX = horiz.xintercept;
	horiz.nextHorizTouchY = horiz.yintercept;
	horiz.maxIterations = 100;
	cast_it_horiz(game, horiz, ray);
}

void	cast_horizontal_ray(t_game *game, float rayAngle, t_ray *ray)
{
	t_horiz	horiz;

	ray->foundHorizontalWallHit = 0;
	ray->horizWallHitX = 0;
	ray->horizWallHitY = 0;
	horiz.yintercept = floor(game->player.player_y / TILE_SIZE) * TILE_SIZE;
	if (ray->isRayFacingDown)
		horiz.yintercept += TILE_SIZE;
	if (fabs(tan(rayAngle)) < 0.0001)
	{
		ray->foundHorizontalWallHit = 0;
		ray->horizWallHitX = 0;
		ray->horizWallHitY = 0;
	}
	else
		init_cast_horiz(game, horiz, ray, rayAngle);
}
