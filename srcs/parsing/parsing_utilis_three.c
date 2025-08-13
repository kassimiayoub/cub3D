/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:59:53 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 17:52:16 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	detect_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < count_nbr_line(game->map) - 1)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0')
			{
				if (game->map[i][j + 1] == ' ' || game->map[i][j - 1] == ' '
					|| game->map[i - 1][j] == ' ' || game->map[i + 1][j] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	detect_map_is_valid(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (game->map[count_nbr_line(game->map) - 1][i])
	{
		if (game->map[count_nbr_line(game->map) - 1][i] != '1'
			&& game->map[count_nbr_line(game->map) - 1][i] != ' ')
			return (0);
		i++;
	}
	if (!detect_map_walls(game))
		return (0);
	return (1);
}
