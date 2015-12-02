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

#include "term_related.h"

int		move_line_left(t_select *cr)
{
	if (cr->px <= MX)
		return (1);
	TMCP("ks");
	TMCP("le");
	TMCP("ke");
	cr->px -= 1;
	return (1);
}

int		move_line_right(t_select *cr, char *name)
{
	if (!(cr->px < MX + ft_strlen(name)))
		return (1);
	TMCP("nd");
	cr->px += 1;
	return (1);
}

int		move_line_down(t_select *cr)
{
	TMCP("do");
	cr->py += 1;
	return (1);
}
int		move_line_up(t_select *cr)
{
	TMCP("up");
	cr->py -= 1;
	return (1);
}

int		move_direction(t_select *cr, char buf[3], char *name)
{
	if (LEFT)// && cr->px >= MX)
		return (move_line_left(cr));
	else if (RIGHT && cr->px < X)
		return (move_line_right(cr, name));
	else if (DOWN && cr->py )
		return (move_line_down(cr));
	else if (UP && cr->py < 20)
		return (move_line_up(cr));
	return (0);
}