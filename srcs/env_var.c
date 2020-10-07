/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:09:43 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/07 18:35:29 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_find_var_in_av(char **av, char *str)
{
    int     i;
    int     k;
    char    c;

    i = -1;
    while (av[++i])
    {
        k = -1;
        c = 0;
        ft_go_to_char(av[i], &k, '=');
        c = av[i][k];
        av[i][k] = '\0';
        if (!ft_strncmp(av[i], str, ft_strlen(str)))
        {
            av[i][k] = c;
            return (i);
        }
    }
    return (-1);
}

char        *ft_replace_var(char *str, int *i)
{
    int     save;
    int     pos;
    char    c;
    int     k;
    char    *new;

    save = *i;
    ft_go_to_char(str, i, ' ');
    c = str[*i];
    str[*i] = '\0';
    pos = ft_find_var_in_av(g_shell.env, &str[save + 1]);
    if (pos == -1)
    {
        str[save] = '\0';
        new = ft_strdup(str);
        str[save] = '$';
        if (c != '\0')
            new = ft_str_add(new, ft_strdup(&str[*i + 1]));
    }
    else
    {
        k = 0;
        ft_go_to_char(g_shell.env[pos], &k, '=');
        str[save] = '\0';    
        new = ft_str_add(ft_strdup(str), ft_strdup(&g_shell.env[pos][k + 1]));
        str[save] = '$';
        if (c != '\0')
        {
            ft_go_to_char(&str[save + 1], &save, ' ');
            new = c == ' ' ? ft_str_add(new, ft_strdup(" ")) : new;
            new = ft_str_add(new, ft_strdup(&str[*i + 1]));
        } 
   }
    str[*i] = c;
    ft_strdel(&str);
    *i = -1;
    return (new);
}

char        *ft_get_env_var(char *str)
{
    int     i;

    g_shell.check = 0;
    i = -1;
    while (str[++i])
    {
        if ((str[i] == 39 || str[i] == '"') && !g_shell.check)
            g_shell.check = str[i];
        else if (g_shell.check == str[i])
            g_shell.check = 0;
        else if ((!g_shell.check || g_shell.check == '"') &&
                        str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
            str = ft_replace_var(str, &i);
    }
    return (str);
}

void        ft_check_env_var(void)
{
    int     i;

    i = -1;
    while (g_shell.pip_str[++i])
        g_shell.pip_str[i] = ft_get_env_var(g_shell.pip_str[i]);
}