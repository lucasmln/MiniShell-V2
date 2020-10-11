/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:23:38 by lucas             #+#    #+#             */
/*   Updated: 2020/10/11 18:19:53 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        ft_final_exec(void)
{
    int     i;
    int     res;
    char    buf[BUF_SIZE + 1];

    i = 0;
    while (i < g_shell.pid.len)
    {
        waitpid(g_shell.pid.id[i], &res, 0);
        if (g_shell.pip.len - 1 > i)
            close(g_shell.pip.id[i][0]);
        i++;
    }
    g_shell.ret = res;
    while ((res = read(g_shell.pip.id[g_shell.pip.len - 1][0], buf, BUF_SIZE)))
    {
        buf[res] = '\0';
        write(1, buf, res);
    }
}