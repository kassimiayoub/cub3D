/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:20:15 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 17:44:00 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strjoin(t_gc *gc, char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(gc, s2));
	if (!s2)
		return (ft_strdup(gc, s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = gc_malloc(gc, s1len + s2len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, s1len);
	ft_memcpy(res + s1len, s2, s2len);
	res[s1len + s2len] = '\0';
	return (res);
}

char	*get_buffer(t_gc *gc, int fd, char *buffer)
{
	char	*new_buff;
	int		bytsread;
	char	*tmp;

	new_buff = (char *)gc_malloc(gc, (size_t)BUFFER_SIZE + 1);
	if (!new_buff)
		return (buffer = NULL, NULL);
	bytsread = 1;
	while (bytsread > 0)
	{
		bytsread = read(fd, new_buff, BUFFER_SIZE);
		if (bytsread == -1)
			return (new_buff = NULL, NULL);
		new_buff[bytsread] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(gc, buffer, new_buff);
		if (!buffer)
			return (NULL);
		if (find_newline(new_buff) >= 0)
			break ;
	}
	return (buffer);
}

char	*get_lines(t_gc *gc, char *buffer)
{
	char	*line;
	int		newlindex;

	line = NULL;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	newlindex = find_newline(buffer);
	if (newlindex == -1)
		newlindex = ft_strlen(buffer);
	if (buffer[newlindex] == '\n')
		line = gc_malloc(gc, newlindex + 2);
	else
		line = gc_malloc(gc, newlindex + 1);
	if (!line)
		return (NULL);
	newlindex = 0;
	while (buffer[newlindex] && buffer[newlindex] != '\n')
	{
		line[newlindex] = buffer[newlindex];
		newlindex++;
	}
	if (buffer[newlindex] == '\n')
		line[newlindex++] = '\n';
	line[newlindex] = '\0';
	return (line);
}

char	*get_afterline(t_gc *gc, char *buffer)
{
	char	*line;
	int		j;
	int		newlindex;

	j = 0;
	newlindex = find_newline(buffer);
	if (newlindex == -1)
		return (NULL);
	line = gc_malloc(gc, ft_strlen(buffer) - newlindex + 1);
	if (!line)
		return (NULL);
	newlindex++;
	while (buffer[newlindex])
	{
		line[j] = buffer[newlindex];
		j++;
		newlindex++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(t_gc *gc, int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE > INT_MAX)
		return (buffer = NULL, NULL);
	buffer = get_buffer(gc, fd, buffer);
	if (!buffer)
		return (buffer = NULL, NULL);
	line = get_lines(gc, buffer);
	if (!line)
		return (buffer = NULL, NULL);
	buffer = get_afterline(gc, buffer);
	return (line);
}
