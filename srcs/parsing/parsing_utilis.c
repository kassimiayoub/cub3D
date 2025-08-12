/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:02:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/12 16:14:38 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] != 'b' || str[i - 2] != 'u'
		|| str[i - 3] != 'c' || str[i - 4] != '.')
		return (0);
	return (1);
}

int	detect_isline_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			break;
	}
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}


int	validat_line(t_game **game, char *line)
{
	int	i;
	int	flag;

	flag = 0;
	(*game)->m_height++;
	if ((*game)->m_width < (int)ft_strlen(line))
		(*game)->m_width = ft_strlen(line);
	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			(*game)->is_player++;
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' 
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*new_updated_line(int size, char *line)
{
	char	*new_line;
	int		i;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_line = malloc(size);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < size - 1)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	fill_map_content(t_game **game, char *map)
{
	int		fd;
	char	*line;
	int		flag;
	int	i;

	(*game)->map = (char **)malloc(((*game)->m_height + 1) * sizeof(char *));
	if (!(*game)->map)
		return (printf("Erreur (map alloction!!!)\n"), 0);
	flag = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("Erreur (open map!!!)\n"), 0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (detect_isline_map(line))
		{
			(*game)->map[i] =  new_updated_line((*game)->m_width, line);
			if (!(*game)->map[i])
				return (free(line), close(fd), 0);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	(*game)->map[i] = NULL;
	close(fd);
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
	line = get_next_line(fd);
	while (line)
	{
		if (detect_isline_map(line))
			flag = 1;
		if (flag)
		{
			if (!validat_line(game, line))
				return (free(line), close(fd), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if ((*game)->is_player > 1)
		return (0);
	if (!fill_map_content(game, map))
		return (printf("Erreur (fill_map_content!!!)\n"), 0);
	return (1);
}
