/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 18:40:31 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/07 19:56:39 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    if (av[0])
    {
        while (av[++i])
         ft_strdel(&av[i]);
        ft_strdel_av(&av);
    }
}

void        ft_free_all()
{
    ft_free_av(g_shell.semi_colon);
    ft_free_av(g_shell.pip_str);
    ft_strdel(&g_shell.str);
}