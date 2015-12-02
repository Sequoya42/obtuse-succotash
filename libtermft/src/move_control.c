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

#include "term_related.h"

int		move_ca(t_select *cr)
{
	(void)cr;
	TMCP("cr");
	int i = 0;
	while (i++ <= MX)
	TMCP("nd");		// move_line_right(cr);
	cr->px = MX;
	return (1);
}

int		move_ce(t_select *cr, char *name)
{
	cr->px = MX + ft_strlen(name);
	TMCP("cr");
	unsigned int i = 0;
	while (i++ <= cr->px)
		TMCP("nd");
	return (1);
}

int		move_ck(void)
{

	return (1);
}

int		move_cy(void)
{
	return (1);
}

int		move_cl(t_select *cr)
{
		TMCP("cl");
		ft_name_prompt();
		cr->px = MX;
		cr->py = MY;
		return (1);
}

int			move_control(t_select *cr, char buf[3], char *name)
{
	if (CA)
		return (move_ca(cr));
	else if (CE)
		return move_ce(cr, name);
	else if (CL)
		move_cl(cr);
	else if (CK)
		return (move_ck());
	else if (CY)
		return (move_cy());
	return (0);
}