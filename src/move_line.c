/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 16:41:09 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 19:29:03 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		move_return(t_core *cr)
{

	ft_get_right_var();
	ft_point();
	stop_SEing();
	ft_clear_tab(&cr->v->arg);
	ft_bzero(SV->name, ft_strlen(SV->name));
	ft_name_prompt();
	cr->px = 0;
	// cr->py += 1;
	return (1);

}
void get_name_right(char *n, int i)
{
	while (n[i])
	{
		n[i] = n[i + 1];
		i++;
	}
}

int		move_del(t_core *cr, int i)
{
	if (cr->px < MX)
	{
		// ft_putendl("da");
		return (1);
	}
	i = cr->px - MX - 1;
	if (i < 0)
	{
		return (1);
	}
		move_line_left(cr);
		TMCP("cr");
		TMCP("ce");
		get_name_right(SV->name, i);
		ft_name_prompt();
		ft_putstr(SV->name);
		return (1);

}

int		move_line(t_core *cr, char buf[3], int i)
{
	if (RET)
		return (move_return(cr));
	else if (move_direction(cr, buf) == 1)
		return (1);
	else if (move_control(cr, buf) == 1)
		return (1);
	else if (DEL)
		return (move_del(cr, i));
	return (0);
}