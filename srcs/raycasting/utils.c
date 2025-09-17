/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:16:14 by iaskour           #+#    #+#             */
/*   Updated: 2025/09/17 11:23:39 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_for_collision(t_game *game, int newPlayerX, int newPlayerY)
{
	int	map_x;
	int	map_y;

	map_x = newPlayerX / game->mini_map_tile;
	map_y = newPlayerY / game->mini_map_tile;
	if (map_x < 0 || map_x >= game->m_width
		|| map_y < 0 || map_y >= game->m_height)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / game->mini_map_tile);
	map_y = (int)(y / game->mini_map_tile);
	if (map_x < 0 || map_x >= game->m_width
		|| map_y < 0 || map_y >= game->m_height)
		return (1);
	return (game->map[map_y][map_x] == '1');
}

float	normalize_angle(float rayAngle)
{
	rayAngle = remainder(rayAngle, 2 * M_PI);
	if (rayAngle < 0)
		rayAngle = (2 * M_PI) + rayAngle;
	return (rayAngle);
}
