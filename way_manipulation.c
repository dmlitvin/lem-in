/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:59:09 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/08 12:59:10 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_list	*extract_way(t_room *end)
{
	unsigned int	counter;
	t_way			way;

	counter = (unsigned int)end->distance;
	way.way_len = counter;
	way.ants_sent = 0;
	way.way = malloc(8 * counter--);
	way.way[counter] = NULL;
	while (end->parent)
	{
		way.way[counter--] = end->room_name;
		end = end->parent;
		end->is_blocked = 1;
	}
	return (ft_lstnew(&way, sizeof(t_way)));
}

static void		put_distance(t_room *room, unsigned int distance, void *parent)
{
	t_list	*lst;

	lst = room->direction;
	room->parent = parent;
	room->distance = distance;
	while (lst)
	{
		if (((t_room*)((t_list*)lst->content)->content)->distance > distance
			&& ((t_room*)((t_list*)lst->content)->content)->is_blocked == 0)
			put_distance(((t_list*)lst->content)->content, distance + 1, room);
		lst = lst->next;
	}
}

void			find_ways(void)
{
	g_ways = NULL;
	while (!((t_room*)g_end->content)->is_blocked)
	{
		put_distance(g_start->content, 0, NULL);
		if (!(IS_REACHED(((t_room*)g_end->content)->distance)))
			((t_room*)g_end->content)->is_blocked = 1;
		if (!((t_room*)g_end->content)->is_blocked)
			ft_lstadd(&g_ways, extract_way(g_end->content));
		ft_lstiter(g_rooms, clear_room);
		if (ft_lstfind(((t_room*)g_end->content)->direction,
			g_start->content, room_cmp))
			return ;
	}
}
