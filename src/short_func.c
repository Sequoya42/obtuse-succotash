/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:20:32 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:12:07 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_select			*singleton(void)
{
	static t_select	*s;

	if (!s)
	{
		if (!(s = malloc(sizeof(t_select))))
			ft_exit("Failed malloc t_select\n");
	}
	return (s);
}

int					tputs_putchar(int c)
{
	write(FD, &c, 1);
	return (1);
}

void				print_key(char buf[3])
{
	ft_putstr(ft_itoa(buf[0]));
	ft_putchar('\t');
	ft_putstr(ft_itoa(buf[1]));
	ft_putchar('\t');
	ft_putstr(ft_itoa(buf[2]));
	ft_putchar('\n');
}

void				get_window_size(t_select *s)
{
	struct winsize	win;
	int				n;

	if (ioctl(s->fd, TIOCGWINSZ, &win) < 0)
		ft_exit("Error with ioctl\n");
	s->w = win;
	n = s->len_max % 4;
	s->co = ((X - 5) / (s->len_max + 4 + n));
	s->co = s->co <= 1 ? 1 : s->co;
}

int					print_selected(t_select *s)
{
	t_member		*tmp;
	int				l;

	tmp = s->first;
	reset(s->term);
	l = 0;
	tputs(tgetstr("me", NULL), FD, tputs_putchar);
	while (tmp != NULL)
	{
		if (tmp->selected == 1)
		{
			l = 1;
			ft_putstr(tmp->name);
			ft_putchar(' ');
		}
		tmp = tmp->next;
		if (tmp == s->last->next)
		{
			if (l == 1)
				ft_putchar('\n');
			break ;
		}
	}
	sig_exit(0);
	return (0);
}
