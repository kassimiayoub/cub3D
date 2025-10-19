/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_and_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:22:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/10/07 15:15:31 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(void *win, t_line line)
{
	t_line_v	line_v;
	int			i;

	line_v.dx = line.x2 - line.x1;
	line_v.dy = line.y2 - line.y1;
	line_v.steps = abs(line_v.dy);
	if (abs(line_v.dx) > abs(line_v.dy))
		line_v.steps = abs(line_v.dx);
	i = 0;
	if (line_v.steps == 0)
	{
		mlx_put_pixel(win, line.x1, line.y1, line.color);
		return ;
	}
	line_v.x = line.x1;
	line_v.y = line.y1;
	while (i <= line_v.steps)
	{
		if (round(line_v.x) >= 0 && round(line_v.x) < 800
			&& round(line_v.y) >= 0 && round(line_v.y) < 600)
			mlx_put_pixel(win, round(line_v.x), round(line_v.y), line.color);
		line_v.x += line_v.dx / (float)line_v.steps;
		line_v.y += line_v.dy / (float)line_v.steps;
		i++;
	}
}

void	draw_all_lines(t_game *game)
{
	int			rays_drawn;
	t_line		line;
	int			i;

	rays_drawn = 0;
	i = 0;
	while (i < game->win_width)
	{
		if (game->ray[i].distance < FLT_MAX)
		{
			line.color = 0xFF0000FF;
			line.x1 = (int)game->player.player_x;
			line.x2 = (int)game->ray[i].wallHitX;
			line.y1 = (int)game->player.player_y;
			line.y2 = (int)game->ray[i].wallHitY;
			draw_line(game->img, line);
			rays_drawn++;
		}
		i++;
	}
}

void	draw_player_direction(t_game *game)
{
	float		ray_len;
	int			end_x;
	int			end_y;
	t_line		line;

	ray_len = 20;
	end_x = (int)(game->player.player_x
			+ (cos(game->player.rotationAngle) * ray_len));
	end_y = (int)(game->player.player_y
			+ (sin(game->player.rotationAngle) * ray_len));
	line.color = 0x0000FF;
	line.x1 = (int)game->player.player_x;
	line.x2 = end_x;
	line.y1 = (int)game->player.player_y;
	line.y2 = end_y;
	draw_line(game->img, line);
}

void	draw_player(t_game *game)
{
	int			player_size;
	uint32_t	player_color;
	t_player_v	player_v;

	player_color = 0x0000FF;
	player_size = game->player.p_height * game->player.p_width;
	player_v.i = -player_size;
	while (player_v.i <= player_size)
	{
		player_v.j = -player_size;
		while (player_v.j <= player_size)
		{
			player_v.px = (int)game->player.player_x + player_v.i;
			player_v.py = (int)game->player.player_y + player_v.j;
			if (player_v.px >= 0 && player_v.px < game->m_width
				&& player_v.py >= 0 && player_v.py < game->m_height)
				mlx_put_pixel(game->img, player_v.px,
					player_v.py, player_color);
			player_v.j++;
		}
		player_v.i++;
	}
}
