/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:07:04 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/18 10:28:28 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_game *game)
{
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	if (!game->img)
		return ;
	draw_map(game);
	draw_3D_wall(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	update_player(t_game *game, float delta_time)
{
	float	move_step;
	float	new_x;
	float	new_y;

	if (game->player.turnDirection != 0)
	{
		game->player.rotationAngle += game->player.turnDirection
			* game->player.turnSpeed * delta_time;
		while (game->player.rotationAngle < 0)
			game->player.rotationAngle += 2 * M_PI;
		while (game->player.rotationAngle >= 2 * M_PI)
			game->player.rotationAngle -= 2 * M_PI;
	}
	if (game->player.walkDirection != 0)
	{
		move_step = game->player.walkDirection
			* game->player.walkSpeed * delta_time;
		new_x = game->player.player_x + cos(game->player.rotationAngle)
			* move_step;
		new_y = game->player.player_y + sin(game->player.rotationAngle)
			* move_step;
		if (!check_for_collision(game, new_x, new_y))
		{
			game->player.player_x = new_x;
			game->player.player_y = new_y;
		}
	}
}

void	process_input(t_game *game)
{
	game->player.walkDirection = 0;
	game->player.turnDirection = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player.walkDirection = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player.walkDirection = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.turnDirection = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.turnDirection = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	game_loop(void *param)
{
	// long	now;
	float	delta_time;
	t_game	*game;

	game = (t_game *)param;
	// now = get_current_time();
	// delta_time = (now - game->last_frame_ms) / 1000.0f;
	// if (delta_time < 0.016f)
	// 	return ;
	// game->last_frame_ms = now;
	delta_time = 0.06;
	process_input(game);
	update_player(game, delta_time);
	render(game);
}
