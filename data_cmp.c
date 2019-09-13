/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:10:51 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/07 20:10:52 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		name_cmp(void *content1, void *content2)
{
	return (!ft_strcmp(((t_room*)content1)->room_name, content2));
}

int		cord_cmp(void *content1, void *content2)
{
	return (((t_room*)content1)->point.x == ((t_point*)content2)->x
			&& (((t_room*)content1)->point.y == ((t_point*)content2)->y));
}

int		room_cmp(void *content1, void *content2)
{
	return (((t_list*)content1)->content == content2);
}

void	clear_room(t_list *element)
{
	((t_room*)element->content)->distance = MAX_DISTANCE;
}
