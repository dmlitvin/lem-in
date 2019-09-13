/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:46:09 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/07 19:46:54 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H

# define LEMIN_H
# include "libft/libft.h"

# define START 1
# define END 2
# define MAX_DISTANCE 9223372036854775807
# define IS_REACHED(x) x != MAX_DISTANCE

typedef struct			s_room
{
	unsigned int		is_blocked : 1;
	unsigned long int	distance : 63;
	t_list				*direction;
	char				*room_name;
	struct s_room		*parent;
	t_point				point;
}						t_room;

typedef struct			s_way
{
	char				**way;
	unsigned int		way_len;
	unsigned int		ants_sent;
}						t_way;

typedef struct			s_ant
{
	t_way				*way;
	unsigned int		queue_wait;
	unsigned int		progress;
}						t_ant;

extern t_list			*g_info;
extern t_list			*g_ways;
extern t_list			*g_start;
extern t_list			*g_end;
extern t_list			*g_rooms;
extern int				g_line_nb;
extern t_room			g_tmp_room;

void					throw_error(int line, char *str);
int						get_next_line_save(int fd, char **line);
void					read_map(void);
int						cord_cmp(void *content1, void *content2);
int						name_cmp(void *content1, void *content2);
int						room_cmp(void *content1, void *content2);
void					clear_room(t_list *element);
void					find_ways(void);
void					send_ants(int ants);

#endif
