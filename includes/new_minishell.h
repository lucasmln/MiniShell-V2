/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minishell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:17:15 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/07 16:52:18 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_MINISHELL
# define NEW_MINISHELL

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include "../../../libft/ft_printf/ft_printf.h"
# include "color.h"
# include "../../../libft/libft/libft.h"

# define BUF_SIZE 2048
# define FD_MAX 512
# define ERR_SEMI_COLONS -2
# define ERR_PIPE -3

typedef struct		s_minishell
{
	char	buf[BUF_SIZE + 1];
	char	*dir;
	char	**env;
	int		len_env;
	int		len_exp;
	char	**sort_env;
	char	**semi_colon;
	char	**pip_str;
	int		i_s;
	int		i_p;
	char	**buf_pip;
	int		fd[FD_MAX];
	char	check;
	int		error;
}					t_minishell;

t_minishell			g_shell;

/*
 ** main.c
*/

void		ft_get_signal(int code);

/*
 ** parse.c
*/

void		ft_split_semi_colons(char *buf);
int			ft_check_parse(char *buf);
void		ft_split_pipe(char *buf);
int			ft_len_split(char *buf, char splitter);
void		ft_add_split(char *buf, char **av, char splitter);

/*
 ** ft_print_prompt.c
*/

int			ft_print_prompt(void);

/*
 ** init.c
*/

void		ft_init_fd_tab(void);
int			ft_copy_env(const char **env);
void		ft_sort_env(void);
void		ft_copy_env_utils(const char **env, int i);

/*
 ** utils.c
*/

char        *ft_str_add(char *s1, char *s2);
void		ft_go_to_char(char *s, int *i, char c);
int         ft_free_error(int code);

/*
 ** env_var.c
*/

void        ft_check_env_var(void);

/*
 ** splitter.c
*/

char		*ft_set_parse(char *buf);

#endif
