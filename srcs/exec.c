/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:53:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/12 15:59:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_fill_argv(char **av, char *buf)
{
    int     i;
    int     start;
    int     l;
    char    c;

    i = 0;
    start = 0;
    l = 0;
    while (ft_pass_word(buf, &i))
    {
        c = buf[i];
        buf[i] = '\0';
        av[l++] = ft_strdup(&buf[start]);
        start = i;
        buf[i] = c;
    }
    av[l] = NULL;
}

char        **ft_create_argv(char *buf)
{
    int     i;
    int     len;
    char    *word;
    char    **av;

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

int         ft_exec_cmd(t_exe *ex, int find)
{
    ex->argv = ft_create_argv(ex->buf);
    pipe(g_shell.pip.id[g_shell.pip.i]);
    g_shell.pid.id[g_shell.pid.i] = fork();
    if (g_shell.pid.id[g_shell.pid.i] == 0)
    {
        close(g_shell.pip.id[g_shell.pip.i][0]);
        if (g_shell.in.len > 0)
            dup2(g_shell.in.fd[g_shell.in.len - 1], STDIN_FILENO);
        else if (g_shell.pip.i > 0)
            dup2(g_shell.pip.id[g_shell.pip.i - 1][0], STDIN_FILENO);
        if (g_shell.out.len > 0)
            dup2(g_shell.out.fd[g_shell.out.len - 1], STDOUT_FILENO);
        else if (!g_shell.pip_str[g_shell.i_p + 1])
            ;
        else
            dup2(g_shell.pip.id[g_shell.pip.i][1], STDOUT_FILENO);
        exit(execve(ex->full_cmd, ex->argv, g_shell.env));
    }
    close(g_shell.pip.id[g_shell.pip.i][1]);
    if (!find)
        ft_free_av(ex->argv);
    g_shell.pip.i++;   
    g_shell.pip.len++;   
    g_shell.pid.i++;   
    g_shell.pid.len++;
    ft_strdel(&ex->full_cmd); 
    return (find);
}

int         ft_loop_all_path(t_exe *ex)
{
    int             i;
    int             find;
    char            *tmp;
    struct stat     info;

    ex->end_path = 0;
    ex->start_path = 0;
    if (!ft_strncmp(ex->cmd, "echo", 4) || !ft_strncmp(ex->cmd, "env", 3) || !ft_strncmp(ex->cmd, "pwd", 3))
    {
        ex->full_cmd = ft_add_path(ft_strdup(ex->cmd));
        return (ft_exec_cmd(ex, 1));
    }
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

int         ft_get_cmd(char *buf)
{
    int     i;
    int     k;
    int     pos;
    t_exe   ex;

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
        ft_printf(1, "minishell: command not found: %s\n", ex.cmd);
    ft_free_ex(ex);
    return (k);
}