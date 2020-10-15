/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:09:43 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/09 13:08:25 by lmoulin          ###   ########.fr       */
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

int         ft_check_except_env(char *str, int *i)
{
    int     k;

    k = *i + 1;
 //   if (g_shell.check == '"')
  //  {
        while (str[k] == ' ')
            k++;
        if (str[k] == '"')
        {
            *i = k + 1;
            return (1);
        }
  //  }
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

char        *ft_replace_var(char *str, int *i)
{
    int     save;
    int     pos;
    char    c;
    int     k;
    char    *new;
    pid_t   pid;

    save = *i;
    if (str[*i + 1] && str[*i + 1] == '"')
    {
        *i += 1;
        return (str);
    }
    if (str[*i + 1] && str[*i + 1] == '$')
    {
        str[save] = '\0';
        new = ft_strdup(str);
        new = ft_str_add(new, ft_itoa(getpid()));
        new = ft_str_add(new, ft_strdup(&str[*i + 2]));
        str[save] = '$';
        ft_strdel(&str);
        return (new);
    }
    k = *i;
    ft_go_to_char(str, i, ' ');
    ft_go_to_char(str, &k, '"');
    *i = k < *i ? k : *i;
    k = save + 1;
    ft_go_to_char(str, &k, '$');
    *i = k < *i ? k : *i;
    if (g_shell.check == str[*i - 1])
        *i -= 1;
    c = str[*i];
    str[*i] = '\0';
    ft_printf(1, "c = %c\n", c);
    ft_printf(1, "save =  %d, i = %d\n", save, *i);
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
        new = ft_str_add(ft_strdup(str), (!g_shell.check ?
            ft_trim_spaces(&g_shell.env[pos][k + 1]) : ft_strdup(&g_shell.env[pos][k + 1])));
        str[save] = '$';
        if (c != '\0')
        {
            ft_go_to_char(&str[save + 1], &save, c);
            new = c == ' ' ? ft_str_add(new, ft_strdup(" ")) : new;
            ft_printf(1, "mid new = %s\n", new);
            str[*i] = c;
            new = ft_str_add(new, ft_strdup(&str[*i]));
        } 
   }
    str[*i] = c;
    ft_strdel(&str);
    *i = save - 1;
    ft_printf(1, "new = %s\n", new);
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