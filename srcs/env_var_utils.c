/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:55:18 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/09 14:56:50 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_check_except_env(char *str, int *i)
{
    int     k;

    k = *i + 1;
    while (str[k] == ' ')
        k++;
    if (str[k] == '"')
    {
        *i = k + 1;
        return (1);
    }
    return (0);

}

char        *ft_trim_spaces(char *var)
{
    char    *str;
    int     len;
    int     i;

    len = 0;
    i = 0;
    while (var[i])
    {
        if (var[i] == ' ')
            while (var[i] == ' ')
                i++;
        else
            i++;
        len++;
    }
    if (!(str = malloc(sizeof(char) * (len + 1))))
        exit(-1000);
    i = 0;
    len = 0;
    while (var[i])
    {
        str[len++] = var[i];
        if (var[i] == ' ')
            while (var[i] == ' ')
                i++;
        else
            i++;
    }
    return (str);
}

char        *ft_inexist_var(char *str, int save, char c, int *i)
{
    char    *new;

    str[save] = '\0';
    new = ft_strdup(str);
    str[save] = '$';
    if (c != '\0')
        new = ft_str_add(new, ft_strdup(&c));
    if (c != '\0')
        new = ft_str_add(new, ft_strdup(&str[*i + 1]));
    return (new);
}

char        *ft_exist_var(char *str, int save[], char c, int *i)
{
    int     k;
    char    *new;
    
    k = 0;
    ft_go_to_char(g_shell.env[save[1]], &k, '=');
    str[save[0]] = '\0';    
    new = ft_str_add(ft_strdup(str), (!g_shell.check ?
        ft_trim_spaces(&g_shell.env[save[1]][k + 1]) : ft_strdup(&g_shell.env[save[1]][k + 1])));
    str[save[0]] = '$';
    if (c != '\0')
    {
        ft_go_to_char(&str[save[0] + 1], &save[0], c);
        new = c == ' ' ? ft_str_add(new, ft_strdup(" ")) : new;
        str[*i] = c;
        new = ft_str_add(new, ft_strdup(&str[*i]));
    }
    return (new);
}