/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 15:46:14 by rbaum             #+#    #+#             */
/*   Updated: 2015/10/24 17:56:35 by rbaum            ###   ########.fr       */
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

# define SE 				SE_env()
# define X					(s->w.ws_col)
# define Y					(s->w.ws_row)
# define CD					(buf[0] == 4 && buf[1] == 0 && buf[2] == 0)
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

typedef struct				s_env
{
	char					*name;
	char					*home;
	char					*pwd;
	char					*oldpwd;
	char					**path;
	char					**env;
	char					**environ;
	char					**arg;
}							t_env;

typedef struct				s_core
{
	t_env					*v;
	t_select				*s;

}							t_core;

void						ft_prompt(void);
void						ft_gest_env(void);
void						ft_get_right_env(void);
void						ft_get_pwd(void);
int							ft_exit_sh(void);
void						ft_update_env(void);
void						stop_SEing(void);
void						ft_previous_dir(void);
void						ft_create_env(void);

int							ft_exec(char *path);
int							ft_cd_error(void);
int							ft_go_home(void);
int							ft_tild(int k);
int							ft_change_dir(void);
int							check_current(int k);
int							check_path(char **arg);
int							check_env(void);
int							aff_env(void);
int							set_env(void);
int							ft_unsetenv(void);
int							ft_env_exe(void);
int							ft_tmp_aff(int l, char **tmp);

char						**pre_aff(void);
t_env						*SE_env(void);

#endif
