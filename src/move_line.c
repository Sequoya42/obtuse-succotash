/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 16:41:09 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 18:10:28 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		move_line_left(t_core *cr)
{
	TMCP("ks");
	TMCP("le");
	TMCP("ke");
	cr->px -= 1;
}

void		move_line_right(t_core *cr)
{
	TMCP("nd");
	cr->px += 1;
}

void		move_line_down(t_core *cr)
{
	TMCP("do");
	cr->py += 1;
}
void		move_line_up(t_core *cr)
{
	TMCP("up");
	cr->py -= 1;
}

void		move_ca()
{
	TMCP("cr");
}

void		move_ce()
{
	TMCP("bc");
}

void		move_line(t_core *cr, char buf[3])
{
	if (LEFT && cr->px > MX)
		move_line_left(cr);
	else if (RIGHT)
		move_line_right(cr);
	else if (DOWN && cr->py )
		move_line_down(cr);
	else if (UP && cr->py < 20)
		move_line_up(cr);
	else if (CA)
		move_ca();
	else if (CE)
		move_ce();
	 else if (DEL || DEL2)
	 {
	 		tputs(tgetstr("BC", NULL), 1, tputs_putchar);
	 }

}