/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:40:31 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:31:13 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_close_fd(void)
{
    g_shell.out.i = -1;
    while (++g_shell.out.i < g_shell.out.len)
    {
        if (g_shell.out.fd[g_shell.out.i] > 1)
            close(g_shell.out.fd[g_shell.out.i]);
        g_shell.out.fd[g_shell.out.i] = 0;
    }
    g_shell.out.fd[0] = 1;
    g_shell.in.i = -1;
    while (++g_shell.in.i < g_shell.in.len)
    {
        if (g_shell.in.fd[g_shell.in.i] > 1)
            close(g_shell.in.fd[g_shell.in.i]);
        g_shell.in.fd[g_shell.in.i] = 0;
    }
    g_shell.in.fd[0] = 1;
}

void        ft_strdel_av(char ***av)
{
    if (*av)
    {
        free(*av);
        *av = NULL;
    }
}

void        ft_free_av(char **av)
{
    int     i;

    i = -1;
    if (av)
    {
        while (av[++i])
            ft_strdel(&av[i]);
       ft_strdel_av(&av);
    }
}

void        ft_free_all()
{
    ft_free_av(g_shell.semi_colon);
    ft_strdel(&g_shell.str);
}

int         ft_free_error(int code)
{
    if (code == ERR_SEMI_COLONS)
    {
        ft_printf(1, "minishell: syntax error ';'\n");
        ft_strdel(&g_shell.str);
        ft_free_av(g_shell.semi_colon);
    }
    else if (code == ERR_PIPE)
    {
        ft_printf(1, "minishell: syntax error '|'\n");
        ft_strdel(&g_shell.str);
        ft_free_av(g_shell.semi_colon);
        ft_free_av(g_shell.pip_str);
    }
    return (0);
}