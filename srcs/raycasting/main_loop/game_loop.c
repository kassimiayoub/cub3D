/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:03:07 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/06 11:11:52 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_for_collision(t_game *game, int newPlayerX, int newPlayerY)
{
	int	map_x;
	int	map_y;

	map_x = newPlayerX / TILE_SIZE;
	map_y = newPlayerY / TILE_SIZE;
	if (
		checker(game, (newPlayerX + 1) / TILE_SIZE, map_y) == 1
		|| checker(game, (newPlayerX - 1) / TILE_SIZE, map_y) == 1
		|| checker(game, map_x, (newPlayerY + 1) / TILE_SIZE) == 1
		|| checker(game, map_x, (newPlayerY - 1) / TILE_SIZE) == 1
	)
		return (1);
	return (0);
}

void	render(t_game *game)
{
	cast_all_rays(game);
	draw_3d_textures(game);
}

void	update_player(t_game *game)
{
	float	move_step;
	float	new_x;
	float	new_y;

	if (game->player.turn_direction != 0)
	{
		game->player.rotation_angle += game->player.turn_direction
			* game->player.turn_speed;
	}
	if (game->player.walk_direction != 0)
	{
		move_step = game->player.walk_direction
			* game->player.walk_speed;
		new_x = game->player.player_x + cos(game->player.rotation_angle)
			* move_step;
		new_y = game->player.player_y + sin(game->player.rotation_angle)
			* move_step;
		if (check_for_collision(game, new_x, new_y) == 0)
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}
}

void	process_input(t_game *game)
{
	game->player.walk_direction = 0;
	game->player.turn_direction = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player.walk_direction = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player.walk_direction = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.turn_direction = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.turn_direction = 1;
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	process_input(game);
	update_player(game);
	render(game);
}
