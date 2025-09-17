/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:01:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/17 11:17:40 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void castVerticalRay(t_game *game, float rayAngle, t_ray *ray) {
    t_vert vert;
    ray->foundVertWallHit = 0;
    ray->wallVertHitX = 0;
    ray->wallVertHitY = 0;

    vert.xintercept = floor(game->player.player_x / TILE_SIZE) * TILE_SIZE;
    vert.xintercept += ray->isRayFacingRight ? TILE_SIZE : 0;
    if (fabs(cos(rayAngle)) < 0.0001) { 
        // For vertical rays, we should skip vertical intersection checking
        // because the ray will never intersect with vertical grid lines
        ray->foundVertWallHit = 0;
        ray->wallVertHitX = 0;
        ray->wallVertHitY = 0;
    } else {
        vert.yintercept = game->player.player_y + (vert.xintercept - game->player.player_x) * tan(rayAngle);
        
        vert.xstep = ray->isRayFacingLeft ? -TILE_SIZE : TILE_SIZE;
        vert.ystep = vert.xstep * tan(rayAngle);
        if (ray->isRayFacingUp && vert.ystep > 0) vert.ystep = -vert.ystep;
        if (ray->isRayFacingDown && vert.ystep < 0) vert.ystep = -vert.ystep;
        
        vert.nextVertTouchX = vert.xintercept;
        vert.nextVertTouchY = vert.yintercept;
        vert.maxIterations = 100;
        while (vert.maxIterations-- > 0 && 
               vert.nextVertTouchX >= 0 && vert.nextVertTouchX < (game->m_width * TILE_SIZE) && 
               vert.nextVertTouchY >= 0 && vert.nextVertTouchY < (game->m_height * TILE_SIZE)) {
            
            vert.xToCheck = vert.nextVertTouchX + (ray->isRayFacingLeft ? -1 : 0);
            vert.yToCheck = vert.nextVertTouchY;
            
            if (check_for_collision(game, vert.xToCheck, vert.yToCheck)) {
                ray->foundVertWallHit = 1;
                ray->wallVertHitX = vert.nextVertTouchX;
                ray->wallVertHitY = vert.nextVertTouchY;
                break;
            } else {
                vert.nextVertTouchX += vert.xstep;
                vert.nextVertTouchY += vert.ystep;
            }
        }
    }
}