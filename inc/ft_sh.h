/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 15:46:14 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 13:58:41 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H
 // opendir
  // ◦ // readdir // ◦ // closedir // 
  // malloc // ◦ // free // ◦ // exit //
    // getcwd // ◦ // chdir // ◦ // fork 
    // stat // ◦ // lstat // ◦ // fstat // 
     // open // ◦ // close // ◦ // read //
     // write // ◦ // execve // ◦ // access //
     // wait // ◦ // waitpid // ◦ // wait3 // ◦ // wait4 //
      // signal // 

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>

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

# define SING				singleton()
# define SV 				sing_var()

# define FD					0
# define HEAD_SIZE			14
# define K42 		       "\e[42m"
# define MX					24
# define MY					2

# define X					(s->w.ws_col)
# define Y					(s->w.ws_row)
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

typedef struct				s_var
{
	char					*name;
	char					*home;
	char					*pwd;
	char					*oldpwd;
	char					**path;
	char					**env;
	char					**environ;
	char					**arg;
	unsigned int			co;
	unsigned int			li;
}							t_var;

typedef struct				s_core
{
	char					*ck_buf;
	t_var					*v;
	t_select				*s;
	unsigned int			px;
	unsigned int			py;
}							t_core;

void						ft_prompt(t_core *cr);
void						ft_name_prompt(void);
void						ft_gest_var(void);
void						ft_get_right_var(void);
void						ft_get_pwd(void);
int							ft_exit_sh(void);
void						ft_update_env(void);
void						stop_SEing(void);
void						ft_previous_dir(void);
void						ft_create_env(void);

int							ft_point(void);
int							ft_exec(char *path);
int							ft_cd_error(void);
int							ft_go_home(void);
int							ft_tild(int k);
int							ft_change_dir(void);
int							check_current(int k);
int							check_path(char **arg);
int							check_env(void);
int							aff_env(void);
int							set_var(void);
int							ft_unsetenv(void);
int							ft_var_exe(void);
int							ft_tmp_aff(int l, char **tmp);

char						**pre_aff(void);
t_var						*sing_var(void);

void              			ft_init(char **av, t_select *s);
void              			print_list(t_select *s);
void              			print_key(char buf[3]);
void              			sig_exit(int i);
void              			ft_z(int i);
void              			ft_fg(int i);
void              			ft_resize(int i);
void              			get_window_size(t_select *s);
void              			window_too_small(void);
void              			print_front(t_select *s);
void              			ft_move(t_select *s, char buf[3]);
void              			move_next(t_select *s);

int               			tputs_putchar(int c);
int               			modif_term(struct termios *term);
int               			reset(struct termios *term);
int               			get_key(t_select *s);
int               			print_selected(t_select *s);

t_select          			*singleton(void);

int							move_line(t_core *cr, char buf[3]);
#endif
