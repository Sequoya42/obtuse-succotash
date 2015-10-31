/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 19:37:59 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/30 15:25:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			sig_exit(int i)
{
	reset(SING->term);
	exit(0);
	(void)i;
}

void			ft_z(int i)
{
	char		arg[2];

	arg[0] = SING->term->c_cc[VSUSP];
	arg[1] = '\0';
	if (isatty(FD))
	{
		tputs(tgetstr("ke", NULL), FD, tputs_putchar);
		tputs(tgetstr("te", NULL), FD, tputs_putchar);
		tputs(tgetstr("ve", NULL), FD, tputs_putchar);
		signal(SIGTSTP, SIG_DFL);
		ioctl(FD, TIOCSTI, arg);
	}
	(void)i;
}

void			ft_fg(int i)
{
	struct termios *term;

	term = SING->term;
	modif_term(SING->term);
	signal(SIGTSTP, ft_z);
	print_list(SING);
	(void)i;
}

void			window_too_small(void)
{
	int			fd;

	fd = FD;
	ft_putendl_fd("WINDOW TOO SMALL !", fd);
}

void			ft_resize(int i)
{
	t_select	*s;

	s = SING;
	get_window_size(s);
	SV->co = s->w.ws_col;
	SV->li = s->w.ws_row;
	(void)i;
}
