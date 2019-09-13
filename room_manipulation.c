/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:15:56 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/07 20:16:01 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*g_end;
t_list	*g_start;
t_list	*g_rooms;

static int	valid_room(char *line, t_room *room)
{
	char *space1;
	char *space2;

	space1 = ft_strchr(line, ' ');
	space2 = ft_strrchr(line, ' ');
	if (*line == 'L' || space1 == space2 || !space1 || !space2
		|| !ft_isnumeric(space1 + 1) || !ft_isnumeric(space2 + 1))
		throw_error(g_line_nb, "invalid name or coordinates.");
	room->point = (t_point){ft_atoi(space1 + 1), ft_atoi(space2 + 1)};
	room->room_name = ft_strsub(line, 0, space1 - line);
	if (ft_lstfind(g_rooms, &room->point, cord_cmp)
		|| ft_lstfind(g_rooms, room->room_name, name_cmp))
		throw_error(g_line_nb, "name or coordinates are repeating");
	return (1);
}

static void	collect_start_end(unsigned int mode, char **line)
{
	t_list	*lst;

	if (!ft_strcmp(*line, "##start") || !ft_strcmp(*line, "##end"))
	{
		get_next_line_save(0 * g_line_nb++, line);
		if ((mode == START && g_start) || (mode == END && g_end))
			throw_error(g_line_nb, "start or end point repeats.");
		valid_room(*line, &g_tmp_room);
		ft_lstadd(&g_rooms, (lst = ft_lstnew(&g_tmp_room, sizeof(t_room))));
		if (mode == START)
			g_start = lst;
		else
			g_end = lst;
	}
}

static void	collect_link(char *line, char *hyphen, size_t line_len)
{
	char	tmp[line_len];
	t_list	*lst1;
	t_list	*lst2;

	if (line == hyphen || !hyphen || !hyphen[1])
		throw_error(g_line_nb, "invalid link!");
	ft_bzero(tmp, line_len);
	ft_memcpy(tmp, line, hyphen - line);
	lst1 = ft_lstfind(g_rooms, tmp, name_cmp);
	ft_memcpy(tmp, hyphen + 1, line_len - (hyphen - line));
	lst2 = ft_lstfind(g_rooms, tmp, name_cmp);
	if (lst1 && lst2)
	{
		if (!ft_lstfind(((t_room*)lst1->content)->direction,
						lst2->content, room_cmp))
		{
			ft_lstadd(&((t_room*)lst1->content)->direction, ft_lstnew(lst2, 8));
			ft_lstadd(&((t_room*)lst2->content)->direction, ft_lstnew(lst1, 8));
		}
	}
	else
		throw_error(g_line_nb, "link error: room doesn't exist.");
}

void		read_map(void)
{
	char *line;

	g_end = NULL;
	g_start = NULL;
	while (get_next_line_save(0 * g_line_nb++, &line)
		&& (ft_strchr(line, '#') || !ft_strchr(line, '-')))
	{
		if (*line == '#' && line[1] != '#')
			;
		else if (*line == '#' && line[1] == '#')
			collect_start_end(ft_strstr(line, "##start") ? START : END, &line);
		else if (valid_room(line, &g_tmp_room))
			ft_lstadd(&g_rooms, ft_lstnew(&g_tmp_room, sizeof(t_room)));
	}
	collect_link(line, ft_strchr(line, '-'), ft_strlen(line));
	while (get_next_line_save(0 * g_line_nb++, &line))
		if (*line == '#')
			if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
				throw_error(g_line_nb, "room can't be declared whithin links!");
			else
				;
		else
			collect_link(line, ft_strrchr(line, '-'), ft_strlen(line));
}
