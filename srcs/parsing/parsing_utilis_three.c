/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:59:53 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/14 13:34:23 by aykassim         ###   ########.fr       */
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

int	add_line_map(t_game **game, char *line, int *cm, int *i)
{
	(*game)->map[(*i)] = new_updated_line((*game)->gc, (*game)->m_width, line);
	if (!(*game)->map[(*i)])
		return (0);
	(*i)++;
	(*cm)++;
	return (1);
}

int	add_line_path(t_game **game, char *line, int j)
{
	if (line[0] == '\n')
		return (2);
	if (j >= 7)
		return (0);
	(*game)->paths[j] = new_paths_line((*game)->gc, line);
	if (!(*game)->paths[j])
		return (0);
	return (1);
}

int	initial_fillmap(t_game **game, char *map, t_fill_map **tf)
{
	(*tf) = gc_malloc((*game)->gc, sizeof(t_fill_map));
	(*game)->map = (char **)gc_malloc((*game)->gc,
			((*game)->m_height + 1) * sizeof(char *));
	(*game)->paths = (char **)gc_malloc((*game)->gc, 7 * sizeof(char *));
	(*tf)->fd = open(map, O_RDONLY);
	if ((*tf)->fd < 0)
		return (0);
	(*tf)->i = 0;
	(*tf)->j = 0;
	(*tf)->cm = 0;
	return (1);
}
