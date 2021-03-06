/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:49:15 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/29 17:32:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term_related.h"

int					modif_term(struct termios *term)
{
	if (tgetent(NULL, getenv("TERM")) == ERR)
		ft_exit("bad tgetent, please set a correct TERM variable\n");
	if (tcgetattr(0, term) == -1)
		ft_exit("Failed tcgetattr!\n");
	tputs(tgetstr("ti", NULL), 1, tputs_putchar);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (-1);	
	return (0);
}

int					reset(struct termios *term)
{
	int				fd;

	fd = FD;
	if (tcgetattr(0, term) == -1)
		ft_exit("Failed tcgetattr!\n");
	tputs(tgetstr("te", NULL), fd, tputs_putchar);
		term->c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, term) == -1)
		ft_exit("Failed tcsetattr\n");
	close(FD);
	return (0);
}
