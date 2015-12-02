/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_related.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:37:33 by rbaum             #+#    #+#             */
/*   Updated: 2015/12/02 17:37:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_RELATED_H
# define TERM_RELATED_H


# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include "libft.h"



# define TPS(x)				tputs(x, 0, tputs_putchar)
# define TMCP(x)			tputs(tgetstr(x, NULL), 1, tputs_putchar)
# define TGT(c, x, y)		tputs(tgoto(tgetstr(c, NULL), x, y), 1, tputs_putchar)


# define X					(SING->w.ws_col)
# define Y					(SING->w.ws_row)
# define CD					(buf[0] == 4 && buf[1] == 0 && buf[2] == 0)
# define CA					(buf[0] == 1 && buf[1] == 0 && buf[2] == 0)
# define CE					(buf[0] == 5 && buf[1] == 0 && buf[2] == 0)
# define CL					(buf[0] == 12 && buf[1] == 0 && buf[2] == 0)
# define CK					(buf[0] == 11 && buf[1] == 0 && buf[2] == 0)
# define CY					(buf[0] == 15 && buf[1] == 0 && buf[2] == 0)

# define ESC				(buf[0] == 27 && buf[1] == 0 && buf[2] == 0)
# define DEL				(buf[0] == 127 && buf[1] == 0 && buf[2] == 0)
# define DEL2				(buf[0] == 126 && buf[1] == 0 && buf[2] == 0)
# define SPACE				(buf[0] == 32 && buf[1] == 0 && buf[2] == 0)
# define RET				(buf[0] == 10 && buf[1] == 0 && buf[2] == 0)
# define LEFT				(buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
# define UP					(buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
# define DOWN				(buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
# define RIGHT				(buf[0] == 27 && buf[1] == 91 && buf[2] == 67)

typedef struct				s_member
{
	char					*name;
	struct s_member			*next;
	struct s_member			*prev;
	int						selected;
	int						current;
	unsigned int			len;
	unsigned int			index;
	unsigned int			is_dir;
}							t_member;

typedef struct				s_select
{
	t_member				*first;
	t_member				*last;
	t_member				*cur;
	struct winsize			w;
	struct termios			*term;
	unsigned int			co;
	int						fd;
	unsigned int			len_max;
	unsigned int			tx;
	unsigned int			ty;
	unsigned int			total_size;
	unsigned int			nb_elem;
}							t_select;

#endif
