/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:28:28 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/08 21:28:29 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*g_ways;

static void		sort_ants(t_ant *ant, int ants)
{
	t_ant	ant_tmp;
	int		tmp;

	tmp = -1;
	while (++tmp + 1 < ants)
		if (ant[tmp].queue_wait > ant[tmp + 1].queue_wait)
		{
			ant_tmp = ant[tmp];
			ant[tmp] = ant[tmp + 1];
			ant[tmp + 1] = ant_tmp;
			tmp = -1;
		}
}

static t_way	*get_best_way(t_list *way)
{
	t_way			*best_way;
	unsigned int	tmp;
	unsigned int	way_cost;

	best_way = way->content;
	way_cost =
			((t_way*)way->content)->way_len + ((t_way*)way->content)->ants_sent;
	while (way)
	{
		if (way_cost > (tmp = ((t_way*)way->content)->way_len +
				((t_way*)way->content)->ants_sent))
		{
			way_cost = tmp;
			best_way = way->content;
		}
		way = way->next;
	}
	return (best_way);
}

static int		check_move(t_ant *ants, int ant_count)
{
	while (ant_count--)
		if (ants[ant_count].way->way_len > ants[ant_count].progress)
			return (1);
	return (0);
}

static void		move_ants(t_ant *ants, int ant_count)
{
	char	space;
	int		tmp;

	write(1, "\n", 1);
	while (check_move(ants, ant_count))
	{
		space = 0;
		tmp = -1;
		while (++tmp < ant_count)
			if (ants[tmp].queue_wait)
				ants[tmp].queue_wait--;
			else
			{
				if (ants[tmp].way->way_len > ants[tmp].progress)
				{
					ft_printf((space) ? " L%d-%s" : "L%d-%s",
						tmp + 1, ants[tmp].way->way[ants[tmp].progress++]);
					space = ' ';
				}
			}
		write(1, "\n", 1);
	}
}

void			send_ants(int ants)
{
	int		ant_tmp;
	t_ant	ant[ants];

	ant_tmp = -1;
	while (++ant_tmp < ants)
	{
		ant[ant_tmp].way = get_best_way(g_ways);
		ant[ant_tmp].queue_wait = (ant[ant_tmp].way->way_len != 1)
				? ant[ant_tmp].way->ants_sent : 0;
		ant[ant_tmp].way->ants_sent++;
		ant[ant_tmp].progress = 0;
	}
	sort_ants(ant, ants);
	move_ants(ant, ants);
}
