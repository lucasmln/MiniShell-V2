/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:53:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/09 17:06:38 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_get_path(t_exe *ex)
{
    int     pos;

    pos = ft_find_var_in_av(g_shell.env, "PATH=");
    if (pos == -1)
    {
        ex->error = 1;
        ex->path = ft_strdup("");
    }
    else
        ex->path = ft_strdup(&g_shell.env[pos][5]);
}

int        ft_pass_word(char *buf, int *i)
{
    int     check;

    if (!buf[*i])
        return (0);
    check = 0;
    while (buf[*i])
    {
        if (!check && buf[*i] == ' ')
        {
            ft_skip_space(buf, i);
            return (1);
        }
        else if (!check && (buf[*i] == '"' || buf[*i] == 39))
           check = buf[*i];
        else if (check && buf[*i] == check)
            check = 0;
        *i += 1;            
    }
    return (1);
}

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
    ft_printf(1, "av buf = %s\n", buf);
    while (ft_pass_word(buf, &i))
        len++;
    if (!(av = malloc(sizeof(char *) * (len + 1))))
        exit(-1000);
    ft_fill_argv(av, buf);
    i = -1;
    while (av[++i])
        ft_printf(1, "len av = %s\n", av[i]);
    return (av);
}

int         ft_exec_cmd(t_exe *ex)
{
    ex->argv = ft_create_argv(ex->buf);
    pipe(g_shell.pip.id[g_shell.pip.i]);
    g_shell.pid.id[g_shell.pid.i] = fork();
    if (g_shell.pip.id[g_shell.pid.i] == 0)
    {
        close(g_shell.pip.id[g_shell.pip.i][0]);
        exit(execve(ex->full_cmd, ex->argv, g_shell.env));
    }
    else
    {
        close(g_shell.pip.id[g_shell.pip.i][1]);
    }
    return (0);
}

int         ft_loop_all_path(t_exe *ex)
{
    int             i;
    char            *tmp;
    struct stat     info;

    ex->end_path = 0;
    ex->start_path = 0;
    while (ft_go_to_char(ex->path, &ex->end_path, ':'))
    {
        ex->path[ex->end_path] = '\0';
        tmp = ft_str_add(ft_strdup(&ex->path[ex->start_path]), ft_strdup("/"));
        ex->full_cmd = ft_str_add(tmp, ft_strdup(ex->cmd));
        ft_printf(1, "full cmd = |%s|\n", ex->full_cmd);
        ex->path[ex->end_path] = ':';
        ex->start_path = ++ex->end_path;
        if (!stat(ex->full_cmd, &info))
            ft_exec_cmd(ex);
    }
    return (0);
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
    ex.cmd = ft_get_word(buf);
    ft_printf(1, "cmd = |%s|\n", ex.cmd);
    ft_get_path(&ex);
    ex.path = ft_str_add(ex.path, ft_strdup(":"));
    ft_printf(1, "env = %s\n", ex.path);
    ft_loop_all_path(&ex);
    return (0);
}