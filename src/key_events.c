/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:42:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:12:09 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int			ft_del(t_select *s)
{
	t_member		*tmp;

	tmp = s->cur;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	s->cur = s->cur->next;
	s->cur->current = 1;
	if (tmp->next == tmp)
		return (0);
	else if (tmp == s->first)
	{
		s->first = s->first->next;
		s->last->prev = s->first;
	}
	else if (tmp == s->last)
	{
		s->last = s->last->prev;
		s->last->next = s->first;
	}
	free(tmp);
	return (1);
}

int					get_key(t_select *s)
{
	char			buf[3];

	ft_bzero(buf, 3);
	read(FD, buf, 3);
	ft_move(s, buf);
	if (CD)
		sig_exit(0);
	else if (ESC)
		sig_exit(0);
	else if (SPACE)
	{
		s->cur->selected = s->cur->selected == 1 ? 0 : 1;
		move_next(s);
	}
	else if (DEL || DEL2)
	{
		if (ft_del(s) == 0)
			return (reset(s->term));
	}
	else if (RET)
		return (print_selected(s));
	return (1);
}
