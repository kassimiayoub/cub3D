/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:12:14 by iaskour           #+#    #+#             */
/*   Updated: 2025/10/04 12:56:58 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	init_cub_window(t_game *game)
// {
// 	init(game);
// 	game->mlx = mlx_init(game->win_width, game->win_height, "cub3D", false);
// 	if (!game->mlx)
// 		return (0);
// 	game->img = mlx_new_image(game->mlx,
// 			game->win_width, game->win_height);
// 	if (!game->img)
// 		return (mlx_terminate(game->mlx), 0);
// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// 	mlx_loop_hook(game->mlx, game_loop, game);
// 	mlx_loop(game->mlx);
// 	mlx_terminate(game->mlx);
// 	return (1);
// }
