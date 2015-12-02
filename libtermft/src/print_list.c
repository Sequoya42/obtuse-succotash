/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:50:38 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:12:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term_related.h"

static void				choose_style(t_member *tmp, int fd)
{
	tputs(tgetstr("me", NULL), fd, tputs_putchar);
	if (tmp->is_dir == 1)
		ft_putstr_fd(KLBLU, fd);
	if (tmp->current == 1)
	{
		ft_putstr_fd(KBOLD, fd);
		tputs(tgetstr("us", NULL), fd, tputs_putchar);
	}
	if (tmp->selected == 1)
		tputs(tgetstr("mr", NULL), fd, tputs_putchar);
}

static void				print_complete(int s, int f, int fd)
{
	while (s < f)
	{
		ft_putchar_fd(' ', fd);
		s += 1;
	}
	ft_putchar_fd('\t', fd);
}

static void				print_format(t_member *tmp, int fd, t_select *s)
{
	int					n;
	int					z;

	n = 0;
	ft_putstr_fd(tmp->name, fd);
	tputs(tgetstr("me", NULL), fd, tputs_putchar);
	if ((tmp->index % s->co) == 0)
		ft_putchar_fd('\n', fd);
	else
	{
		n = tmp->len % 4;
		z = n;
		if (tmp->len + n < s->len_max)
		{
			while (n--)
				ft_putchar_fd(' ', fd);
		}
		print_complete((tmp->len + z), s->len_max, fd);
	}
	ft_putstr_fd(KNRM, fd);
}

void					print_list(t_select *s)
{
	t_member		*tmp;
	int				fd;

	tmp = s->first;
	fd = s->fd;
	s->total_size = 0;
	if (!(tmp->len > X || X < HEAD_SIZE || Y < ((s->nb_elem / s->co) + 4)))
	{
		print_front(s);
		while (tmp != NULL)
		{
			choose_style(tmp, fd);
			print_format(tmp, fd, s);
			if (tmp == s->last)
				break ;
			tmp = tmp->next;
		}
	}
	else
		window_too_small();
}
