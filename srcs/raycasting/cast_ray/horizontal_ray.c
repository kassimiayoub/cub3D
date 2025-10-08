/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:38:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/10/07 17:46:52 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_it_horiz(t_game *game, t_horiz horiz, t_ray *ray)
{
	while (horiz.nextHorizTouchX >= 0
		&& horiz.nextHorizTouchX < game->win_width
		&& horiz.nextHorizTouchY >= 0
		&& horiz.nextHorizTouchY < game->win_height)
	{
		horiz.xToCheck = horiz.nextHorizTouchX;
		horiz.yToCheck = horiz.nextHorizTouchY;
		if (ray->isRayFacingUp)
			horiz.yToCheck -= 1;
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
