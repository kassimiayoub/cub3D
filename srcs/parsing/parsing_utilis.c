/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/22 08:42:19 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	assis_func(t_game **game, t_fill_map **tf)
{
	close((*tf)->fd);
	if ((*tf)->j >= 7 || (*tf)->cm == 0)
		return (0);
	(*game)->map[(*tf)->i] = NULL;
	(*game)->paths[(*tf)->j] = NULL;
	return (1);
}

int	fill_map_content(t_game **game, char *map)
{
	t_fill_map	*tf;

	initial_fillmap(game, map, &tf);
	tf->line = get_next_line((*game)->gc, tf->fd);
	while (tf->line)
	{
		if (detect_isline_map(tf->line))
		{
			if (!add_line_map(game, tf->line, &tf->cm, &tf->i))
				return (close(tf->fd), 0);
		}
		else
		{
			if (add_line_path(game, tf->line, tf->j) == 2)
			{
				tf->line = get_next_line((*game)->gc, tf->fd);
				continue ;
			}
			else if (add_line_path(game, tf->line, tf->j) == 0)
				return (close(tf->fd), 0);
			tf->j++;
		}
		tf->line = get_next_line((*game)->gc, tf->fd);
	}
	return (assis_func(game, &tf));
}

int	all_validate_element(t_game *game, char *map)
{
	// if (game->is_player != 1)
	// 	return (printf("asdfasfadsfadsfds"), 0);
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
				return (printf("am over her 2"), close(fd), 0);
		}
		line = get_next_line((*game)->gc, fd);
	}
	close(fd);
	if (!all_validate_element(*game, map))
		return (printf("am over her 1"), 0);
	return (1);
}
