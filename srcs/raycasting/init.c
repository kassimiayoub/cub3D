/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:17:03 by iaskour           #+#    #+#             */
/*   Updated: 2025/11/06 13:46:57 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray(t_game **game)
{
	int	i;

	i = 0;
	while (i < (*game)->win_width)
	{
		(*game)->ray[i].distance = FLT_MAX;
		(*game)->ray[i].wall_hitx = 0;
		(*game)->ray[i].wall_hity = 0;
		(*game)->ray[i].was_hit_vertical = 0;
		(*game)->ray[i].is_ray_facing_up = 0;
		(*game)->ray[i].is_ray_facing_down = 0;
		(*game)->ray[i].is_ray_facing_down = 0;
		(*game)->ray[i].is_ray_facing_right = 0;
		i++;
	}
}

void	init_player_position(t_game *game, int x, int y)
{
	if (game->player.player_x == 0 && game->player.player_y == 0)
	{
		game->player.player_x = (x * TILE_SIZE)
			+ (TILE_SIZE / 2);
		game->player.player_y = (y * TILE_SIZE)
			+ (TILE_SIZE / 2);
		game->player.walk_speed = 1.8f;
		game->player.turn_speed = 0.06f;
		game->player.walk_direction = 0;
		game->player.turn_direction = 0;
	}
}

void	init_player_rotation_angle(t_game *game, int x, int y)
{
	init_player_position(game, x, y);
	game->player.is_init = 1;
	if (game->map[y][x] == 'N')
		game->player.rotation_angle = 3 * M_PI / 2;
	else if (game->map[y][x] == 'S')
		game->player.rotation_angle = M_PI / 2;
	else if (game->map[y][x] == 'E')
		game->player.rotation_angle = 0;
	else if (game->map[y][x] == 'W')
		game->player.rotation_angle = M_PI;
}

void	init_player(t_game *game)
{
	int			y;
	int			x;

	y = 0;
	while (y < game->m_height)
	{
		x = 0;
		while (x < game->m_width)
		{
			if (game->player.is_init == 0 && (game->map[y][x] == 'N'
				|| game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W'))
				init_player_rotation_angle(game, x, y);
			x++;
		}
		y++;
	}
}

int	init(t_game **game)
{
	(*game)->player.is_init = 0;
	(*game)->win_width = (*game)->m_width * TILE_SIZE;
	(*game)->win_height = (*game)->m_height * TILE_SIZE;
	(*game)->ray = gc_malloc((*game)->gc, sizeof(t_ray) * (*game)->win_width);
	(*game)->player.player_x = 0;
	(*game)->player.player_y = 0;
	(*game)->player.p_width = 2;
	(*game)->player.p_height = 2;
	(*game)->is_game_started = 0;
	if (!(*game)->ray)
		return (0);
	init_ray(game);
	init_player(*game);
	return (1);
}
