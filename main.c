/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:44:40 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/07 19:44:50 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*g_end;
t_list	*g_start;
t_list	*g_rooms;
t_list	*g_info;
t_list	*g_ways;
t_room	g_tmp_room;
int		g_line_nb;

void		throw_error(int line, char *str)
{
	if (line)
	{
		ft_putstr_fd("Error on line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str, 2);
	exit(1);
}

static void	lstadd_end(t_list **head, t_list *new)
{
	static t_list *last = NULL;

	if (last)
	{
		last->next = new;
		last = new;
	}
	else
	{
		*head = new;
		new->next = NULL;
		last = new;
	}
}

int			get_next_line_save(int fd, char **line)
{
	t_list	*tmp;
	int		result;

	if ((result = get_next_line(fd, line)))
	{
		lstadd_end(&g_info, (tmp = ft_lstnew(NULL, 0)));
		tmp->content = *line;
	}
	return (result);
}

static void	display_map(t_list *list)
{
	while (list)
	{
		write(1, list->content, ft_strlen(list->content));
		write(1, "\n", 1);
		list = list->next;
	}
}

int			main(void)
{
	int		ants;
	char	*line;

	g_info = NULL;
	g_rooms = NULL;
	g_ways = NULL;
	g_line_nb = 0;
	ft_bzero(&g_tmp_room, sizeof(t_room));
	g_tmp_room.distance = MAX_DISTANCE;
	if (get_next_line_save(0 * g_line_nb++, &line) == 1 && ft_isnumeric(line))
	{
		ants = ft_atoi(line);
		(ants) ? read_map() : throw_error(0, "There is no ants!");
		(g_end && g_start) ? find_ways()
			: throw_error(0, "Start or end point not found!");
		(g_ways) ? display_map(g_info)
			: throw_error(0, "There is no path to send ants!");
		send_ants(ants);
	}
	else
		throw_error(0, "Error on reading file or at the first line.");
	return (0);
}
