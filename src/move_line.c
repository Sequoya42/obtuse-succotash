/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 16:41:09 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/31 16:10:21 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		move_line_left(t_core *cr)
{
	TMCP("ks");
	TMCP("le");
	TMCP("ke");
	cr->px -= 1;
	return (1);
}

int		move_line_right(t_core *cr)
{
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

int		move_ca(t_core *cr)
{
	(void)cr;
	TMCP("cr");//, cr->px, 1);
	return (1);
}

int		move_ce()
{
	TMCP("nw");
	return (1);
}

int		move_line(t_core *cr, char buf[3], int *i)
{
	(void)i;
		if (RET)
	{
		ft_get_right_var();
		ft_point();
		stop_SEing();
		ft_clear_tab(&SV->arg);
		ft_bzero(SV->name, ft_strlen(SV->name));
		// *i = 0;
		TPS("\n");
		ft_name_prompt();
		return (1);
	}
	else if (LEFT && cr->px > MX)
	return 		move_line_left(cr);
	else if (RIGHT)
	return 		move_line_right(cr);
	else if (DOWN && cr->py )
	return 		move_line_down(cr);
	else if (UP && cr->py < 20)
	return 		move_line_up(cr);
	else if (CA)
	return 		move_ca(cr);
	else if (CE)
		return move_ce();
	 else if (DEL || DEL2)
	 {
	 	TMCP("bc");
	 	return (1);
	 }
	 else if (CL)
	 {
	 	TMCP("cl");
	 	ft_name_prompt();
	 	return (1);
	 }
	 return (0);
}