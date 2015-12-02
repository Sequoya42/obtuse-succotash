/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:47:19 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 15:12:10 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static t_member		*set_n(int i, char **t)
{
	t_member		*n;
	struct stat		st;

	if (!(n = malloc(sizeof(t_member))))
		ft_exit("Failed malloc\n");
	n->name = ft_strdup(t[i]);
	stat(n->name, &st);
	if (S_ISDIR(st.st_mode))
		n->is_dir = 1;
	else
		n->is_dir = 0;
	n->next = NULL;
	n->prev = NULL;
	n->current = 0;
	n->selected = 0;
	n->index = i;
	n->len = ft_strlen(n->name);
	return (n);
}

static void			fill_first(t_select *s, t_member *n)
{
	n->current = 1;
	s->first = n;
	s->last = n;
	s->cur = s->first;
}

static void			fill_others(t_select *s, t_member *n)
{
	s->last->next = n;
	n->prev = s->last;
	s->last = n;
}

static void			fill_list(char **t, t_select *s)
{
	int				i;
	t_member		*n;

	i = 1;
	while (t[i])
	{
		n = set_n(i, t);
		if (i == 1)
			fill_first(s, n);
		else
			fill_others(s, n);
		i++;
		if (n->len > s->len_max)
			s->len_max = n->len;
	}
	s->last->next = s->first;
	s->first->prev = s->last;
	s->nb_elem = i - 1;
}

void				ft_init(char **av, t_select *s)
{
	s->len_max = 0;
	s->total_size = 0;
	fill_list(av, s);
	if ((s->fd = open("/dev/tty", O_RDWR)) == -1)
		ft_exit("Bad file decriptor struct\n");
	if (modif_term(s->term) == -1)
		ft_exit("failed modifying\n");
	get_window_size(s);
}
