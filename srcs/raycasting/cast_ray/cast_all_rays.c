/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:09:05 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/17 11:40:35 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	chooseDistance(t_game *game, float rayAngle, int stripId, t_ray *ray)
{
	float horizHitDistance;
	float vertHitDistance;
	// Calculate distances and choose the closer hit
	horizHitDistance = ray->foundHorizontalWallHit ? 
		distance_between_points(game->player.player_x, game->player.player_y, ray->horizWallHitX, ray->horizWallHitY) : FLT_MAX;
	vertHitDistance = ray->foundVertWallHit ? 
		distance_between_points(game->player.player_x, game->player.player_y, ray->wallVertHitX, ray->wallVertHitY) : FLT_MAX;

	// ADDED: Handle case where no wall is hit
	if (horizHitDistance == FLT_MAX && vertHitDistance == FLT_MAX) {
		// No wall hit - set a far distance in the ray direction
		game->ray[stripId].wallHitX = game->player.player_x + cos(rayAngle) * (TILE_SIZE * 20);
		game->ray[stripId].wallHitY = game->player.player_y + sin(rayAngle) * (TILE_SIZE * 20);
		game->ray[stripId].distance = TILE_SIZE * 20;
		game->ray[stripId].wasHitVertical = 0;
	} else if (vertHitDistance < horizHitDistance) {
		game->ray[stripId].wallHitX = ray->wallVertHitX;
		game->ray[stripId].wallHitY = ray->wallVertHitY;
		game->ray[stripId].distance = vertHitDistance;
		game->ray[stripId].wasHitVertical = 1;
	} else {
		game->ray[stripId].wallHitX = ray->horizWallHitX;
		game->ray[stripId].wallHitY = ray->horizWallHitY;
		game->ray[stripId].distance = horizHitDistance;
		game->ray[stripId].wasHitVertical = 0;
	}
}

void castRay(t_game *game, float rayAngle, int stripId, t_ray *ray)
{
	rayAngle = normalize_angle(rayAngle);

	ray->isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	ray->isRayFacingUp = !ray->isRayFacingDown;
	ray->isRayFacingRight = rayAngle < M_PI / 2 || rayAngle > 3 * M_PI / 2;
	ray->isRayFacingLeft = !ray->isRayFacingRight;

	castHorizontalRay(game, rayAngle, ray);
	castVerticalRay(game, rayAngle, ray);
	chooseDistance(game, rayAngle, stripId, ray);

	// Apply fisheye correction
	game->ray[stripId].distance *= cos(rayAngle - game->player.rotationAngle);
	
	// Store ray properties
	game->ray[stripId].rayAngle = rayAngle;
	game->ray[stripId].isRayFacingDown = ray->isRayFacingDown;
	game->ray[stripId].isRayFacingUp = ray->isRayFacingUp;
	game->ray[stripId].isRayFacingLeft = ray->isRayFacingLeft;
	game->ray[stripId].isRayFacingRight = ray->isRayFacingRight;
}

void	castAllRays(t_game *game)
{
	float	rayAngle;
	float	angleStep;
	int		stripId;

	if (!game || !game->map || !game->player.is_init)
		return ;
	rayAngle = game->player.rotationAngle - (FOV_ANGLE / 2);
	angleStep = FOV_ANGLE / NUM_RAYS;
	stripId = 0;
	while (stripId < NUM_RAYS)
	{
		castRay(game, rayAngle, stripId, game->ray);
		rayAngle += angleStep;
		stripId++;
	}
}
