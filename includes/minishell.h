/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:35:47 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 14:33:37 by lmoulin          ###   ########.fr       */
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
# include <errno.h>
# include "ft_printf.h"
# include "color.h"
# include "libft.h"
# include "cd_error.h"
# include "dynamic_read.h"

# define BUF_SIZE 2048
# define FD_MAX 512
# define ERR_SEMI_COLONS -2
# define ERR_PIPE -3

typedef struct		s_fd
{
	int		fd[FD_MAX];
	int		i;
	int		len;
}					t_fd;

typedef struct 		s_pid
{
	pid_t	id[FD_MAX];
	int		i;
	int		len;
}					t_pid;

typedef struct		s_pipe
{
	int		id[FD_MAX][2];
	int		i;
	int		len;
}					t_pipe;

typedef struct		s_exe
{
	char	**argv;
	char	*buf;
	char	*path;
	int		end_path;
	int		start_path;
	char	*cmd;
	char	*full_cmd;
	int		error;
}					t_exe;

typedef struct		s_minishell
{
	char			buf[BUF_SIZE + 1];
	char			*str;
	char			*dir;
	char			**env;
	int				len_env;
	int				len_exp;
	char			**sort_env;
	char			**semi_colon;
	char			**pip_str;
	int				last_pip;
	int				i_s;
	int				i_p;
	t_fd			out;
	t_fd			in;
	t_pid			pid;
	t_pipe			pip;
	t_historique	*h;
	t_reader		*r;
	char			check;
	int				tmp_ret;
	int				error;
	int				error_input;
	int				pos_error_in;
	int				ret;
	int				legal_exit;
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
int			ft_len_split(char *buf, char splitter);
void		ft_add_split(char *buf, char **av, char splitter);

/*
 ** cd.c
*/
int			ft_cd(char *buf);
int         ft_cd_directory(char *dir);
int         ft_cd_back(void);
int         ft_cd_home(char *buf);
void        ft_change_env_pwd(char *path);
int         ft_check_error_cd(char *buf);

/*
 ** builtins_error.c
*/
int         ft_error_cd(char *buf, int type);

/*
 ** ft_print_prompt.c
*/
void		ft_print_prompt_2(void);
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
int			ft_go_to_char(char *s, int *i, char c);
char        *ft_get_word(char *buf, char stopper);
int         ft_error_open_fd(char *buf);

/*
 ** quote.c
*/
char        *ft_copy_without_quote(char *buf, int len);
int         ft_len_without_quote(char *buf);
int         ft_find_var_in_av(char **av, char *str);

/*
 ** env_var.c
*/
void        ft_check_env_var(void);
char        *ft_get_env_var(char *str);
char        *ft_replace_var(char *str, int *i);
char        *ft_check_exist_var(char *str, int *i, int save, char c);

/*
 ** export.c
*/
int         ft_export(char *buf);

/*
 ** export_utils.c
*/
void        ft_skip_quote(char *buf, int *i);
int         ft_len_word_with_quote(char *buf);
char        *ft_get_word_with_quote(char *buf);
int         ft_avlen(char **env);
char        **ft_avdup(char **env);

/*
 ** export_error.c
*/
int         ft_error_export(char *buf, int type);
int         ft_check_error_export(char *buf);
int         ft_check_error_var(char *var);
int         ft_check_wrong_char(char *var);

/*
 ** export_printer.c
*/
void        ft_print_env(void);
int         ft_set_print_env(char *buf, char *word);

/*
 ** export_get_var.c
*/
char            **ft_add_var_to_env(char *var, char **env);
void            ft_replace_var_in_all_env(char *var, int check);
int             ft_check_already_exist_var(char *var);
char            *ft_get_pos_var(char *var, int pos[], int *i);
char            *ft_change_var(char *buf);

/*
 ** unset.c
*/
int         ft_unset(char *buf);

/*
 ** env_var_utils.c
*/
int         ft_check_except_env(char *str, int *i);
char        *ft_trim_spaces(char *var);
char        *ft_inexist_var(char *str, int save, char c, int *i);
char        *ft_exist_var(char *str, int save[], char c, int *i);

/*
 ** splitter.c
*/
int			ft_set_parse(char *buf);
int			ft_split_pipe(char *buf);


/*
 ** free.c
*/
void        ft_free_av(char **av);
void        ft_free_all();
void        ft_strdel_av(char ***av);
void        ft_close_fd(void);
int         ft_free_error(int code);

/*
 ** free_2.c
*/
void		ft_free_ex(t_exe ex);

/*
 ** command.c
*/
int			ft_try_cmd(char *buf);
char		*ft_add_path(char *buf);

/*
 ** exit.c
*/
int			ft_check_exit(char *buf);
void        ft_free_exit(void);

/*
 ** exec.c
*/
void        ft_fill_argv(char **av, char *buf);
char        **ft_create_argv(char *buf);
int         ft_exec_cmd(t_exe *ex, int find);
int         ft_loop_all_path(t_exe *ex);
int         ft_get_cmd(char *buf);

/*
 ** exec_utils.c
*/
int	        ft_get_path(t_exe *ex);
int			ft_pass_word(char *buf, int *i);
char        *ft_del_quote_av(char *s);

/*
 ** exec_end.c
*/
void        ft_final_exec(int ret);

/*
 ** redir.c
*/
int         ft_check_redir(char *buf);
int         ft_redir_input(char *buf, int *i);
int			ft_redir_output(char *buf, int *i, int type);
char        *ft_find_good_name_redir(char *buf, int *i);

/*
 ** redir_utils.c
*/
int         ft_check_error_redir(char *buf);
char        *ft_del_redir(char *buf);
void		ft_init_var(int *i, int *len, int *check, int *redir);

#endif
