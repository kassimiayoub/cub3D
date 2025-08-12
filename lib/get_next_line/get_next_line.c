/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:20:15 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/11 17:20:17 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = malloc(s1len + s2len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, s1len);
	ft_memcpy(res + s1len, s2, s2len);
	res[s1len + s2len] = '\0';
	return (res);
}

char	*get_buffer(int fd, char *buffer)
{
	char	*new_buff;
	int		bytsread;
	char	*tmp;

	new_buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!new_buff)
		return (free(buffer), buffer = NULL, NULL);
	bytsread = 1;
	while (bytsread > 0)
	{
		bytsread = read(fd, new_buff, BUFFER_SIZE);
		if (bytsread == -1)
			return (free(new_buff), new_buff = NULL, NULL);
		new_buff[bytsread] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(buffer, new_buff);
		free(tmp);
		if (!buffer)
			return (free (new_buff), NULL);
		if (find_newline(new_buff) >= 0)
			break ;
	}
	free(new_buff);
	return (buffer);
}

char	*get_lines(char *buffer)
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
		line = malloc(newlindex + 2);
	else
		line = malloc(newlindex + 1);
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

char	*get_afterline(char *buffer)
{
	char	*line;
	int		j;
	int		newlindex;

	j = 0;
	newlindex = find_newline(buffer);
	if (newlindex == -1)
	{
		free(buffer);
		return (NULL);
	}
	line = malloc(ft_strlen(buffer) - newlindex + 1);
	if (!line)
		return (free(buffer), NULL);
	newlindex++;
	while (buffer[newlindex])
	{
		line[j] = buffer[newlindex];
		j++;
		newlindex++;
	}
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE > INT_MAX)
		return (free (buffer), buffer = NULL, NULL);
	buffer = get_buffer(fd, buffer);
	if (!buffer)
		return (free(buffer), buffer = NULL, NULL);
	line = get_lines(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = get_afterline(buffer);
	return (line);
}
