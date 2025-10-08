/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_and_minimap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 07:11:01 by iaskour           #+#    #+#             */
/*   Updated: 2025/10/06 14:06:05 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_mini_map(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (i < game->m_height)
	{
		j = 0;
		while (j< game->m_width)
		{
			uint32_t color;

			if (game->map[i][j] == '1') {
				color = 0x000000FF;
			} else if (game->player.is_init == 0 && (game->map[i][j] == 'N' || game->map[i][j] == 'S' || 
					  game->map[i][j] == 'E' || game->map[i][j] == 'W')) {
				init_player_position(game, i, j);
				game->player.is_init = 1;
				if (game->map[i][j] == 'N') game->player.rotationAngle = 3 * M_PI / 2;
				else if (game->map[i][j] == 'S') game->player.rotationAngle = M_PI / 2;
				else if (game->map[i][j] == 'E') game->player.rotationAngle = 0;
				else if (game->map[i][j] == 'W') game->player.rotationAngle = M_PI;
			}
			else 
				color = 0xFFFFFFFF;
			k = 0;
			while (k < game->mini_map_tile) {
				l = 0;
				while(l < game->mini_map_tile)
				{
					int px = i * game->mini_map_tile + i;
					int py = j * game->mini_map_tile + j;
					if (px < game->mini_map_width && py < game->mini_map_height) {
						mlx_put_pixel(game->img, px, py, color);
					}
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}
	cast_all_rays(game);
	draw_all_lines(game);
	draw_player_direction(game);
	draw_player(game);
}

void	start_drawing_map(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			px = x * TILE_SIZE + i;
			py = y * TILE_SIZE + j;
			if (px < game->win_width && py < game->win_height)
				mlx_put_pixel(game->img, px, py, color);
			j++;
		}
		i++;
	}
}

void	init_player_rotation_angle(t_game *game, int x, int y)
{
	init_player_position(game, x, y);
	game->player.is_init = 1;
	if (game->map[y][x] == 'N')
		game->player.rotationAngle = 3 * M_PI / 2;
	else if (game->map[y][x] == 'S')
		game->player.rotationAngle = M_PI / 2;
	else if (game->map[y][x] == 'E')
		game->player.rotationAngle = 0;
	else if (game->map[y][x] == 'W')
		game->player.rotationAngle = M_PI;
}

void	init_map(t_game *game)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < game->m_height)
	{
		x = 0;
		while (x < game->m_width)
		{
			if (game->map[y][x] == '1')
				color = 0x000000FF;
			else if (game->player.is_init == 0 && (game->map[y][x] == 'N'
				|| game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W'))
				init_player_rotation_angle(game, x, y);
			else
				color = 0xFFFFFFFF;
			start_drawing_map(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	
	init_map(game);
	cast_all_rays(game);
	draw_player(game);
}
