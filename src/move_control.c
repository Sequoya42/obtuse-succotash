/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 14:44:42 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 19:02:52 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
int		move_line_right(t_core *cr);
int		move_ca(t_core *cr)
{
	(void)cr;
	TMCP("cr");
	int i = 0;
	while (i++ <= MX)
	TMCP("nd");		// move_line_right(cr);
	cr->px = MX;
	return (1);
}

int		move_ce(t_core *cr)
{
	cr->px = MX + ft_strlen(SV->name);
	TMCP("cr");
	unsigned int i = 0;
	while (i++ <= cr->px)
		TMCP("nd");
	return (1);
}

int		move_ck()
{

	return (1);
}

int		move_cy()
{
	return (1);
}

int		move_cl(t_core *cr)
{
		TMCP("cl");
		ft_name_prompt();
		cr->px = MX;
		cr->py = MY;
		return (1);
}

int			move_control(t_core *cr, char buf[3])
{
	if (CA)
		return (move_ca(cr));
	else if (CE)
		return move_ce(cr);
	else if (CL)
		move_cl(cr);
	else if (CK)
		return (move_ck());
	else if (CY)
		return (move_cy());
	return (0);
}