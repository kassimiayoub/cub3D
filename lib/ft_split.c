/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:46:07 by aykassim          #+#    #+#             */
/*   Updated: 2025/08/13 15:53:41 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	*free_strings(char **strings, int j)
{
	while (j >= 0)
	{
		free(strings[j]);
		j--;
	}
	free(strings);
	return (NULL);
}

static int	count_words(char const *str, char charset)
{
	int	i;
	int	cm;

	cm = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0')
			cm++;
		while (str[i] != '\0' && str[i] != charset)
			i++;
	}
	return (cm);
}

static char	*ft_strcpy(t_gc *gc, char const *str, char charset)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (str[len] != '\0' && str[len] != charset)
		len++;
	res = gc_malloc(gc, len + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**allwork(t_gc *gc, char **strings, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			strings[j] = ft_strcpy(gc, &s[i], c);
			if (!strings[j])
				return (free_strings(strings, j - 1));
			j++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(t_gc *gc, char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)gc_malloc(gc, (count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	strings = allwork(gc, strings, s, c);
	return (strings);
}
