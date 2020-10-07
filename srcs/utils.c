/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:00 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/07 19:58:40 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char        *ft_str_add(char *s1, char *s2)
{
    char    *new;
    int     i;
    int     k;

    if (!s1 && !s2)
        return (ft_strdup(""));
    if (!s1 || !s2)
    {
        new = !s2 ? ft_strdup(s1) : ft_strdup(s1);
        !s2 ? ft_strdel(&s1) : ft_strdel(&s2);
        return (new);
    }
    if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
        exit(-1000);
    i = -1;
    while (s1[++i])
        new[i] = s1[i];
    k = -1;
    while (s2[++k])
        new[i + k] = s2[k];
    new[i + k] = '\0';
    ft_strdel(&s1);
    ft_strdel(&s2);
    return (new);
}

void        ft_go_to_char(char *s, int *i, char c)
{
    while (s[*i])
    {
        if (s[*i] == c)
            break ;
        *i += 1;
    }
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