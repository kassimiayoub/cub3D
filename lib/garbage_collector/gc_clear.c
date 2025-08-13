/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:55:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/08/13 15:22:00 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gc_clear(t_gc *gc)
{
	t_gc_node	*curr;

	curr = gc->head;
	while (curr)
	{
		free(curr->ptr);
		curr = curr->next;
	}
	free(curr);
}
