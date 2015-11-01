/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 14:48:31 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 18:51:34 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		move_line_left(t_core *cr)
{
	if (cr->px <= MX)
		return (1);
	TMCP("ks");
	TMCP("le");
	TMCP("ke");
	cr->px -= 1;
	return (1);
}

int		move_line_right(t_core *cr)
{
	if (!(cr->px < MX + ft_strlen(cr->v->name)))
		return (1);
	TMCP("nd");
	cr->px += 1;
	return (1);
}

int		move_line_down(t_core *cr)
{
	TMCP("do");
	cr->py += 1;
	return (1);
}
int		move_line_up(t_core *cr)
{
	TMCP("up");
	cr->py -= 1;
	return (1);
}

int		move_direction(t_core *cr, char buf[3])
{
	if (LEFT)// && cr->px >= MX)
		return (move_line_left(cr));
	else if (RIGHT && cr->px < X)
		return (move_line_right(cr));
	else if (DOWN && cr->py )
		return (move_line_down(cr));
	else if (UP && cr->py < 20)
		return (move_line_up(cr));
	return (0);
}