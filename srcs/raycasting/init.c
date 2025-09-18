/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:17:03 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/18 10:26:30 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		game->ray[i].distance = FLT_MAX;
		game->ray[i].wallHitX = 0;
		game->ray[i].wallHitY = 0;
		game->ray[i].wasHitVertical = 0;
		game->ray[i].isRayFacingUp = 0;
		game->ray[i].isRayFacingDown = 0;
		game->ray[i].isRayFacingLeft = 0;
		game->ray[i].isRayFacingRight = 0;
		i++;
	}
}

void	init(t_game *game)
{
	game->m_width = 64;
	game->m_height = 32;
	game->player.is_init = 0;
	game->win_width = game->m_width * TILE_SIZE;
	game->win_height = game->m_height * TILE_SIZE;
	game->mini_map_width = (int)(game->win_width * MINI_MAP_VECTOR);
	game->mini_map_height = (int)(game->win_height * MINI_MAP_VECTOR);
	game->mini_map_tile = (int)(TILE_SIZE * MINI_MAP_VECTOR);
	game->ray = gc_malloc(game->gc, sizeof(t_ray) * NUM_RAYS);
	game->player.player_x = 0;
	game->player.player_y = 0;
	game->player.p_width = 2;
	game->player.p_height = 2;
	game->last_frame_ms = get_current_time();
	if (!game->ray)
		return ;
	init_ray(game);
}

void	init_player_position(t_game *game, int x, int y)
{
	if (game->player.player_x == 0 && game->player.player_y == 0)
	{
		game->player.player_x = (x * TILE_SIZE)
			+ (TILE_SIZE / 2);
		game->player.player_y = (y * TILE_SIZE)
			+ (TILE_SIZE / 2);
		game->player.walkSpeed = 60.0f;
		game->player.turnSpeed = 2.0f;
		game->player.walkDirection = 0;
		game->player.turnDirection = 0;
	}
}
