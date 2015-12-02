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

# define SING				singleton()

# define FD					0
# define HEAD_SIZE			14
# define K42 		       "\e[42m"
# define MX					25
# define MY					0

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
	unsigned int			px;
	unsigned int			py;
}							t_select;

int							modif_term(struct termios *term);
int							reset(struct termios *term);
void						move_next(t_select *s);
void						ft_move(t_select *s, char buf[3]);

int							move_ca(t_select *cr);
int							move_ce(t_select *cr, char *name);
int							move_ck(void);
int							move_cy(void);
int							move_cl(t_select *cr);
int							move_control(t_select *cr, char buf[3], char *name);
int							move_line_left(t_select *cr);
int							move_line_right(t_select *cr, char *name);
int							move_line_down(t_select *cr);
int							move_line_up(t_select *cr);
int							move_direction(t_select *cr, char buf[3], char *name);
int							move_line_left(t_select *cr);

void						print_front(t_select *s);
void						print_list(t_select *s);
t_select					*singleton(void);
int							tputs_putchar(int c);
void						print_key(char buf[3]);
void						get_window_size(t_select *s);
int							print_selected(t_select *s);
void						sig_exit(int i);
void						ft_z(int i);
void						ft_fg(int i);
void						window_too_small(void);
void						ft_resize(int i);
int							get_key(t_select *s);
void		                ft_name_prompt(void);

#endif
