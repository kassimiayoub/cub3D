/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 17:10:13 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	fill_map_content(t_game **game, char *map)
{
	int		fd;
	char	*line;
	int		flag;
	int	i;
	int	j;
	int	cm;

	(*game)->map = (char **)gc_malloc((*game)->gc,((*game)->m_height + 1) * sizeof(char *));
	(*game)->paths = (char **)gc_malloc((*game)->gc, 7 * sizeof(char *));
	flag = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	j = 0;
	cm = 0;
	line = get_next_line((*game)->gc, fd);
	while (line)
	{
		if (detect_isline_map(line))
		{
			(*game)->map[i] =  new_updated_line((*game)->gc, (*game)->m_width, line);
			if (!(*game)->map[i])
				return (close(fd), 0);
			i++;
			cm++;
		}
		else
		{
			if (line[0] == '\n')
			{
				line = get_next_line((*game)->gc, fd);
				continue ;
			}
			if (j >= 7)
				return (close(fd), 0);
			(*game)->paths[j] = new_paths_line((*game)->gc, line);
			if (!(*game)->paths[j])
				return (close(fd), 0);
			j++;
		}
		line = get_next_line((*game)->gc, fd);
	}
	close(fd);
	(*game)->map[i] = NULL;
	if (j >= 7)
		return (0);
	(*game)->paths[j] = NULL;
	if (cm == 0)
		return (0);
	return (1);
}

int	all_validate_element(t_game *game, char *map)
{
	if (game->is_player > 1)
		return (0);
	if (!fill_map_content(&game, map))
		return (printf("Erreur (fill_map_content!!!)\n"), 0);
	if (!detect_map_is_valid(game))
		return (printf("Erreur (detect_map_is_valid!!!)\n"), 0);
	if (!validate_path(&game))
		return (printf("Erreur (validate_path!!!)\n"), 0);
	return (1);
}

int	read_map(t_game **game, char *map)
{
	int		fd;
	char	*line;
	int		flag;

	flag = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("Erreur (open map!!!)\n"), 0);
	line = get_next_line((*game)->gc, fd);
	while (line)
	{
		if (detect_isline_map(line))
			flag = 1;
		if (flag)
		{
			if (!validat_line(game, line))
				return (close(fd), 0);
		}
		line = get_next_line((*game)->gc, fd);
	}
	close(fd);
	if (!all_validate_element(*game, map))
		return (0);
	return (1);
}
