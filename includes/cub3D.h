#ifndef CUB3D_H
# define CUB3D_H

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> 

typedef struct s_game
{
	char **map;
	int	m_height;
	int	m_width;
	int	is_player;
}	t_game;

//lib
int	ft_isalnum(int c);

//parsing_utilis
int	map_extension(char *str);
int	read_map(t_game **game, char *map);
#endif