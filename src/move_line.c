/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 16:41:09 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/28 17:12:14 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		move_line_left()
{
	TMCP("ks");
	tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, tputs_putchar);
	TMCP("ke");
	// TMCP("le");
}

void		move_line_right()
{
	tputs(tgoto(tgetstr("nd", NULL), 0, 0), 1, tputs_putchar);
	// TMCP("nd");
}

void		move_line_down()
{
	TMCP("do");
}
void		move_line_up()
{
	TMCP("up");
}


void		move_line(t_core *cr, char buf[3])
{
	(void)cr;
	if (LEFT)
		move_line_left();
	else if (RIGHT)
		move_line_right();
	else if (DOWN)
		move_line_down();
	else if (UP)
		move_line_up();
}