/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <jvaquer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:53:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/26 22:46:08 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_create_argv(char *buf)
{
	int		i;
	int		len;
	char	*word;
	char	**av;

	i = 0;
	len = 0;
	word = NULL;
	while (ft_pass_word(buf, &i))
		len++;
	if (!(av = malloc(sizeof(char *) * (len + 1))))
		exit(-1000);
	ft_fill_argv(av, buf);
	i = -1;
	while (av[++i])
		av[i] = ft_del_quote_av(av[i]);
	return (av);
}

int			ft_exec_cmd(t_exe *ex, int find)
{
	ex->argv = ft_create_argv(ex->buf);
	pipe(g_shell.pip.id[g_shell.pip.i]);
	g_shell.pid.id[g_shell.pid.i] = fork();
	if (g_shell.pid.id[g_shell.pid.i] == 0)
	{
		signal(SIGTERM, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(g_shell.pip.id[g_shell.pip.i][0]);
		if (g_shell.in.len > 0)
			dup2(g_shell.in.fd[g_shell.in.len - 1], STDIN_FILENO);
		else if (g_shell.pip.i > 0)
			dup2(g_shell.pip.id[g_shell.pip.i - 1][0], STDIN_FILENO);
		if (g_shell.out.len > 0)
			dup2(g_shell.out.fd[g_shell.out.len - 1], STDOUT_FILENO);
		else if (g_shell.pip_str[g_shell.i_p + 1])
			dup2(g_shell.pip.id[g_shell.pip.i][1], STDOUT_FILENO);
		if (g_shell.error_input)
			exit((g_shell.error_input = 0) + 1);
		exit(execve(ex->full_cmd, ex->argv, g_shell.env));
	}
	close(g_shell.pip.id[g_shell.pip.i][1]);
	!find ? ft_free_av(ex->argv) : 0;
	ft_incremente_pip_and_pid(ex);
	return (find);
}

int			ft_check_loop(t_exe *ex)
{
	ex->end_path = 0;
	ex->start_path = 0;
	if (!ft_strncmp(ex->cmd, "echo", ft_strlen(ex->cmd)) ||
	!ft_strncmp(ex->cmd, "env", ft_strlen(ex->cmd)) ||
							!ft_strncmp(ex->cmd, "pwd", ft_strlen(ex->cmd)))
	{
		ex->full_cmd = ft_add_path(ft_strdup(ex->cmd));
		return (1);
	}
	return (0);
}

int			ft_loop_all_path(t_exe *ex)
{
	int				find;
	char			*tmp;
	struct stat		info;

	find = 0;
	if (ft_check_loop(ex))
		return (ft_exec_cmd(ex, 1));
	if (!(stat(ex->cmd, &info)))
		find = 1;
	ex->full_cmd = ft_strdup(ex->cmd);
	while (ft_go_to_char(ex->path, &ex->end_path, ':') && !find)
	{
		ft_strdel(&ex->full_cmd);
		ex->path[ex->end_path] = '\0';
		tmp = ft_str_add(ft_strdup(&ex->path[ex->start_path]), ft_strdup("/"));
		ex->full_cmd = ft_str_add(tmp, ft_strdup(ex->cmd));
		ex->path[ex->end_path] = ':';
		ex->start_path = ++ex->end_path;
		if (!(stat(ex->full_cmd, &info)))
			find = 1;
		if (find)
			break ;
	}
	return (ft_exec_cmd(ex, find));
}

int			ft_get_cmd(char *buf)
{
	int		i;
	int		k;
	t_exe	ex;

	i = -1;
	k = 0;
	ex.error = 0;
	ex.buf = ft_strdup(buf);
	ex.cmd = ft_get_word(buf, 0);
	ft_get_path(&ex);
	ex.path = ft_str_add(ex.path, ft_strdup(":"));
	if ((k = ft_loop_all_path(&ex)))
		ft_free_av(ex.argv);
	else
	{
		g_shell.tmp_ret = 127;
		ft_printf(1, "minishell: command not found: %s\n", ex.cmd);
	}
	ft_free_ex(ex);
	return (k);
}
