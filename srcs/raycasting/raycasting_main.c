/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:12:14 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/18 10:22:49 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_cub_window(t_game *game)
{
	init(game);
	game->mlx = mlx_init(game->win_width, game->win_height, "cub3D", true);
	if (!game->mlx)
		return (0);
	game->img = mlx_new_image(game->mlx,
			game->mini_map_width, game->mini_map_height);
	if (!game->img)
		return (mlx_terminate(game->mlx), 0);
	render(game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (1);
}
