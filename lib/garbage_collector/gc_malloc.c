/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:36 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/13 15:23:40 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*new;

	ptr = malloc(size);
	if (!ptr)
	{
		gc_clear(gc);
		exit(1);
	}
	if (gc_exist(gc, ptr))
		return (ptr);
	new = malloc(sizeof(t_gc_node));
	if (!new)
	{
		free(ptr);
		gc_clear(gc);
		exit(1);
	}
	new->ptr = ptr;
	new->next = gc->head;
	gc->head = new;
	return (ptr);
}
