/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:53:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/11 18:05:45 by lucas            ###   ########.fr       */
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

int         ft_exec_cmd(t_exe *ex)
{
    ex->argv = ft_create_argv(ex->buf);
    int  k = -1;
    while (ex->argv[++k])
        ft_printf(1, "av[%d] = : |%s|\n", k, ex->argv[k]);
    pipe(g_shell.pip.id[g_shell.pip.i]);
    ft_printf(1, "cmd exec = |%s|\n", ex->full_cmd);
    g_shell.pid.id[g_shell.pid.i] = fork();
    if (g_shell.pid.id[g_shell.pid.i] == 0)
    {
        ft_printf(1, "len fd = %d\n", g_shell.out.fd[g_shell.out.len]);
        close(g_shell.pip.id[g_shell.pip.i][0]);
        if (g_shell.pip.i > 0)
            dup2(g_shell.pip.id[g_shell.pip.i - 1][0], STDIN_FILENO);
        if (g_shell.out.len > 0)
            dup2(g_shell.out.fd[g_shell.out.len - 1], STDOUT_FILENO);
        else
            dup2(g_shell.pip.id[g_shell.pip.i][1], STDOUT_FILENO);
        exit(execve(ex->full_cmd, ex->argv, g_shell.env));
    }
    close(g_shell.pip.id[g_shell.pip.i][1]);
    g_shell.pip.i++;   
    g_shell.pip.len++;   
    g_shell.pid.i++;   
    g_shell.pid.len++;
    ft_strdel(&ex->full_cmd); 
    return (1);
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
        ex->path[ex->end_path] = ':';
        ex->start_path = ++ex->end_path;
        if (!(stat(ex->full_cmd, &info)))
            return (ft_exec_cmd(ex));
        ft_strdel(&ex->full_cmd); 
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
    ft_get_path(&ex);
    ex.path = ft_str_add(ex.path, ft_strdup(":"));
    if (ft_loop_all_path(&ex))
        ft_free_av(ex.argv);
    ft_free_ex(ex);
    return (0);
}