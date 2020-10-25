/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:35:47 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/24 14:03:57 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define LLMAX "9223372036854775807"
# define LLMIN "9223372036854775808"
# define ARG_NUM "minishell: exit: %s argument numerique necessaire\n"

typedef struct		s_fd
{
	int		fd[FD_MAX];
	int		i;
	int		len;
}					t_fd;

typedef struct		s_pid
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
 ** builtins_error.c
*/
int					ft_error_cd(char *buf, int type);
int					ft_check_wrong_char_unset(char *var);
int					ft_error_unset(char *buf);
int					ft_check_error_unset(char *buf, int *start);

/*
 ** builtins_utils.c
*/
void				ft_change_env_pwd_utils(char *tmp, int i, char *path);
void				ft_change_env_pwd(char *path);

/*
 ** cd.c
*/
int					ft_cd_home(char *buf);
int					ft_cd_back(void);
int					ft_cd_directory(char *dir);
void				ft_change_env_pwd(char *path);
int					ft_cd(char *buf);

/*
 ** command.c
*/
char				*ft_add_path(char *buf);
int					ft_try_cmd(char *buf);

/*
 ** env_var.c
*/
char				*ft_last_ret(char *str, int *i);
int					ft_check_replace_var(char *str, int *i, int *save, int *k);
char				*ft_replace_var(char *str, int *i);
char				*ft_get_env_var(char *str);
void				ft_check_env_var(void);
int					ft_exportable_char(char c, int first);

/*
 ** env_var_utils.c
*/
int					ft_check_except_env(char *str, int *i);
char				*ft_inexist_var(char *str, int *i);
char				*ft_copy_env_var_without_quote(char *var);
void				ft_init_exist_var(char *str, char quote[], int save[],
																		int *k);
char				*ft_exist_var(char *str, char *word, int pos, int *i);

/*
 ** exec.c
*/
char				**ft_create_argv(char *buf);
int					ft_exec_cmd(t_exe *ex, int find);
int					ft_check_loop(t_exe *ex);
int					ft_loop_all_path(t_exe *ex);
int					ft_get_cmd(char *buf);

/*
 ** exec_end.c
*/
void				ft_error_ctr_c(int *res);
void				ft_final_exec(int ret);

/*
 ** exec_utils.c
*/
int					ft_get_path(t_exe *ex);
int					ft_pass_word(char *buf, int *i);
char				*ft_del_quote_av(char *s);
void				ft_incremente_pip_and_pid(t_exe *ex);
void				ft_fill_argv(char **av, char *buf);

/*
 ** exit.c
*/
void				ft_free_exit(void);
int					ft_check_exit_utils(char *buf, int i);
int					ft_check_exit(char *buf);

/*
 ** export.c
*/
void				ft_add_var(char *buf, char *word, int start);
char				*ft_switch_word(char *word);
int					ft_incremente_export(char *word);
int					ft_export(char *buf);

/*
 ** export_error.c
*/
int					ft_error_export(char *buf, int type);
int					ft_check_error_export(char *buf);
int					ft_check_error_var(char *var);
int					ft_check_wrong_char(char *var);
int					ft_check_error_redir(char *buf);

/*
 ** export_get_var.c
*/
char				**ft_add_var_to_env(char *var, char **env);
void				ft_replace_var_in_all_env(char *var);
int					ft_check_already_exist_var(char *var);
char				*ft_get_pos_var(char *var, int pos[], int *i);
char				*ft_change_var(char *buf);

/*
 ** export_printer.c
*/
void				ft_print_env(void);
void				ft_init_set_printer(char *word, char *buf, int *check);
int					ft_set_print_env(char *buf, char *word);

/*
 ** main.c
*/
void				ft_get_signal(int code);

/*
 ** parse.c
*/
void				ft_split_semi_colons(char *buf);
int					ft_check_parse(void);
int					ft_len_split(char *buf, char splitter);
void				ft_add_split(char *buf, char **av, char splitter);

/*
 ** export_utils.c
*/
void				ft_skip_quote(char *buf, int *i);
int					ft_len_word_with_quote(char *buf);
char				*ft_get_word_with_quote(char *buf);
int					ft_avlen(char **env);
char				**ft_avdup(char **env);

/*
 ** free.c
*/
void				ft_close_fd(void);
void				ft_strdel_av(char ***av);
void				ft_free_av(char **av);
void				ft_free_all();
int					ft_free_error(int code);

/*
 ** free_2.c
*/
void				ft_free_ex(t_exe ex);

/*
 ** ft_print_prompt.c
*/
void				ft_print_prompt_2(void);
int					ft_print_prompt(void);

/*
 ** get_var_utils.c
*/
void				ft_add_to_export(char **tmp, char *var);
char				*ft_change_var_utils(char *buf, char *now, int k,
																	int check);

/*
 ** init.c
*/
void				ft_init_fd_tab(void);
void				ft_copy_env_utils(const char **env, int i);
void				ft_sort_env(void);
int					ft_copy_env(const char **env);

/*
 ** quote.c
*/
char				*ft_copy_without_quote(char *buf, int len);
int					ft_len_without_quote(char *buf);

/*
 ** redir.c
*/
int					ft_redir_output(char *buf, int *i, int type);
char				*ft_find_good_name_redir(char *buf, int *i);
int					ft_redir_input(char *buf, int *i);
int					ft_cond_chekc_redir(char *buf, int *i, int check);
int					ft_check_redir(char *buf);

/*
 ** redir_utils.c
*/
void				ft_skip_redir(char *buf, int *i);
void				ft_init_var(int *i, int *len, int *check, int *redir);
int					ft_len_without_redir(char *buf);
char				*ft_copy_without_redir(char *buf, char *now);
char				*ft_del_redir(char *buf);

/*
 ** splitter.c
*/
int					ft_set_parse(char *buf);
int					ft_split_pipe(char *buf);
void				ft_add_split(char *buf, char **av, char splitter);
void				ft_split_semi_colons(char *buf);
int					ft_check_parse(void);

/*
 ** splitter_utils.c
*/
int					ft_init_set_parse(char *buf, int *ret);
int					ft_len_split(char *buf, char splitter);
int					ft_check_empty_redir(void);

/*
 ** unset.c
*/
void				ft_del_word_in_env(int pos);
void				ft_del_word_in_export(int pos);
int					ft_find_pos_in_av(char *word);
void				ft_loop_unset(char *word, char *buf, char *tmp, int start);
int					ft_unset(char *buf);

/*
 ** utils.c
*/
char				*ft_str_add(char *s1, char *s2);
int					ft_go_to_char(char *s, int *i, char c);
char				*ft_get_word(char *buf, char stopper);
int					ft_find_var_in_av(char **av, char *str);
int					ft_error_open_fd(char *buf);

/*
 ** utils_2.c
*/
char				*ft_trim_spaces(char *var);
char				ft_choose_good_quote(char *buf);
int					ft_len_without_space(char *var);
char				*ft_check_exist_var(char *str, char *word, int i);
int					ft_init_redir(char *buf, int *i, int *check);
char				*ft_del_char(char *s, int pos);

#endif
