/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 18:44:08 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:12:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void			move_prev(t_select *s)
{
	s->cur->current = 0;
	s->cur = s->cur->prev;
	s->cur->current = 1;
}

void				move_next(t_select *s)
{
	s->cur->current = 0;
	s->cur = s->cur->next;
	s->cur->current = 1;
}

static void			move_up(t_select *s)
{
	unsigned int	i;
	unsigned int	max;

	i = 0;
	max = s->co % s->cur->index;
	s->cur->current = 0;
	while (i++ < s->co)
		s->cur = s->cur->prev;
	s->cur->current = 1;
}

static void			move_down(t_select *s)
{
	unsigned int	i;
	unsigned int	max;

	i = 0;
	max = s->co % s->cur->index;
	s->cur->current = 0;
	while (i++ < s->co)
		s->cur = s->cur->next;
	s->cur->current = 1;
}

void				ft_move(t_select *s, char buf[3])
{
	if (RIGHT)
		move_next(s);
	else if (LEFT)
		move_prev(s);
	else if (UP)
		move_up(s);
	else if (DOWN)
		move_down(s);
}
