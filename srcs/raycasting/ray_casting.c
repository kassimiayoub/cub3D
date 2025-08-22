/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/22 07:36:25 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render(t_game *game){
	(void)game;
}

int init_cub_window(t_game *game) {
	game->m_height = 11;
	game->m_width = 15;

	int window_width = game->m_width * TILE_SIZE;
	int window_height = game->m_height * TILE_SIZE;
	

	game->mlx = mlx_init( window_width, window_height, "CUB3D", true);
	if (!game->mlx){
		printf("mlx failed to init\n");
		return 0;
	}

	mlx_loop(game->mlx);
	return 1;
}
