/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 15:34:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/03/11 04:21:48 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "libft.h"

# define SING singleton()

typedef struct s_cmd		t_cmd;

struct		s_cmd
{
	char	*name;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	**path;
	char	**env;
	char	**environ;
	char	**arg;
};

void		ft_prompt(void);
void		ft_gest_cmd(void);
void		ft_get_right_cmd(void);
void		ft_get_pwd(void);
int			ft_exit(void);
void		ft_update_env(void);
void		stop_singing(void);
void		ft_previous_dir(void);
void		ft_create_env(void);

int			ft_exec(char *path);
int			ft_cd_error(void);
int			ft_go_home(void);
int			ft_tild(int k);
int			ft_change_dir(void);
int			check_current(int k);
int			check_path(char **arg);
int			check_env(void);
int			aff_env(void);
int			set_env(void);
int			ft_unsetenv(void);
int			ft_nb_tab(char **tab);
int			ft_env_exe(void);
int			ft_tmp_aff(int l, char **tmp);

char		**pre_aff(void);
t_cmd		*singleton(void);
#endif
