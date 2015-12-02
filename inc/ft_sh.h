/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 15:46:14 by rbaum             #+#    #+#             */
/*   Updated: 2015/11/01 19:21:22 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "libft.h"

# include "term_related.h"

# define SING				singleton()
# define SV 				sing_var()

# define FD					0
# define HEAD_SIZE			14
# define K42 		       "\e[42m"
# define MX					25
# define MY					0


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

int							move_line(t_core *cr, char buf[3], int i);
int							move_control(t_core *cr, char buf[3]);
int							move_direction(t_core *cr, char buf[3]);
int							move_line_left(t_core *cr);
void						sig_return(int signo);
t_var						*sing_var(void);
t_core						*get_ready(void);
void						choose(char **envp, t_core *cr);

#endif
