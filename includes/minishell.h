/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:35:47 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:31:37 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include "ft_printf.h"
# include "color.h"
# include "libft.h"

# define BUF_SIZE 2048
# define FD_MAX 512
# define ERR_SEMI_COLONS -2
# define ERR_PIPE -3
# define EXPORT !ft_strncmp(buf, "export", 6)
# define UNSET !ft_strncmp(buf, "unset", 5)
# define CD !ft_strncmp(buf, "cd", 2)
# define ECHO !ft_strncmp(buf, "echo", 4)
# define PWD !ft_strncmp(buf, "pwd", 3)
# define ENV !ft_strncmp(buf, "env", 3)

typedef struct		s_fd
{
	int		fd[FD_MAX];
	int		i;
	int		len;
}					t_fd;

typedef struct		s_minishell
{
	char	buf[BUF_SIZE + 1];
	char	*str;
	char	*dir;
	char	**env;
	int		len_env;
	int		len_exp;
	char	**sort_env;
	char	**semi_colon;
	char	**pip_str;
	int		i_s;
	int		i_p;
	t_fd	out;
	t_fd	in;
	pid_t	pid[FD_MAX];
	char	check;
	int		error;
	int		ret;
	int		legal_exit;
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
char        *ft_get_word(char *buf);
char        *ft_copy_without_quote(char *buf, int len);
int         ft_len_without_quote(char *buf);

/*
 ** env_var.c
*/

void        ft_check_env_var(void);

/*
 ** splitter.c
*/

int			ft_set_parse(char *buf);

/*
 ** free.c
*/

void        ft_free_av(char **av);
void        ft_free_all();
void        ft_strdel_av(char ***av);
void        ft_close_fd(void);
int         ft_free_error(int code);

/*
 ** command.c
*/
int			ft_get_cmd(char *buf);

/*
 ** exit.c
*/
int			ft_check_exit(char *buf);
void        ft_free_exit(void);

/*
 ** exec.c
*/
int         ft_exec_cmd(char *buf);

/*
 ** redir.c
*/
int         ft_check_redir(char *buf);
int         ft_redir_input(char *buf, int *i);
int			ft_redir_output(char *buf, int *i, int type);

/*
 ** redir_utils.c
*/
int         ft_error_open_fd(char *buf);
int         ft_check_error_redir(char *buf);
char        *ft_del_redir(char *buf);

#endif