/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 15:20:24 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/26 17:51:12 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term_related.h"

void                print_front(t_select *s)
{
    int             i;
    int             siz;

    i = 0;
    siz = (X / 2) - 4;
    tputs(tgetstr("me", NULL), s->fd, tputs_putchar);
    tputs(tgoto(tgetstr("cm", NULL), 0, 0), s->fd, tputs_putchar);
    tputs(tgetstr("cd", NULL), s->fd, tputs_putchar);
    while (i < siz)
    {
        ft_putstr_fd(" ", s->fd);
        i += 1;
    }
    ft_putstr_fd(KBOLD, s->fd);
    ft_putstr_fd(K42, s->fd);
    ft_putstr_fd(KCYN, s->fd);
    ft_putendl_fd("Ft_select\n", s->fd);
    tputs(tgetstr("me", NULL), s->fd, tputs_putchar);
}
