/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:04:19 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 19:22:24 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_error_unset(char *buf)
{
    char    *tmp;

    tmp = ft_get_word(buf, 0);
    ft_printf(1, "minishell: %s: command not found\n", tmp);
    ft_strdel(&tmp);
    return (1);
}

int         ft_check_error_unset(char *buf, int *start)
{
    int     i;
    char    check;

    i = 5;
    if (!buf[i] || buf[i] == ' ')
        return (0);
    if (buf[i] != '"' && buf[i] != 39)
        return (1);
    check = buf[i];
    while (buf[++i])
    {
        if (!check && buf[i] == ' ')
            break ;
        if (!check && (buf[i] == '"' || buf[i] == 39))
            check = buf[i++];
        if (buf[i] != check)
            return (1);
        if (check == buf[i])
            check = 0;
    }
    *start = i;
    ft_printf(1, "&buf[i] = |%s|\n", &buf[i]);
    return (0);
}

void        ft_del_word_in_env(int pos)
{
    int     i;
    int     k;
    char    **tmp;

    i = -1;
    k = 0;
    if (!(tmp = malloc(sizeof(char *) * (ft_avlen(g_shell.env)))))
        exit(-1000);
    while (g_shell.env[++i])
        if (i != pos)
            tmp[k++] = ft_strdup(g_shell.env[i]);
    tmp[k] = NULL;
    ft_free_av(g_shell.env);
    g_shell.env = tmp;    
}

void        ft_del_word_in_export(int pos)
{
    int     i;
    int     k;
    char    **tmp;

    i = -1;
    k = 0;
    if (!(tmp = malloc(sizeof(char *) * (ft_avlen(g_shell.sort_env)))))
        exit(-1000);
    while (g_shell.sort_env[++i])
        if (i != pos)
            tmp[k++] = ft_strdup(g_shell.sort_env[i]);
    tmp[k] = NULL;
    ft_free_av(g_shell.sort_env);
    g_shell.sort_env = tmp;    
}

int         ft_find_pos_in_av(char *word)
{
    int     pos[2];
    char    **tmp;
    char    *equal;
    int     i;
    int     k;

    equal = ft_str_add(ft_strdup(word), ft_strdup("="));
    pos[0] = ft_find_var_in_av(g_shell.env, equal);
    pos[1] = ft_find_var_in_av(g_shell.sort_env, equal);
    ft_strdel(&equal);
    if (pos[0] != -1)
        ft_del_word_in_env(pos[0]);
    if (pos[1] != -1)
        ft_del_word_in_export(pos[1]);
    return (1);
}
      
int             ft_check_wrong_char_unset(char *var)
{
    int     i;

    i = 0;
    while (var[i] == '"' || var[i] == 39)
        i++;
    if (!ft_isalpha(var[i]) && var[i] != '_')
        return (1);
    while (var[i])
    {
        if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"' && var[i] != 39)
            return (1);
        i++;
    }
    return (0);
}

int         ft_unset(char *buf)
{
    int     i;
    char    *word;
    char    *tmp;
    int     start;

    pipe(g_shell.pip.id[g_shell.pip.i]);
    if (ft_check_error_unset(buf, &start))
        return (ft_error_unset(buf));
    i = 0;
    word = ft_get_word(buf, 0);
    tmp = ft_strtrim(word, " ");
    ft_strdel(&word);
    word = tmp;
    while (word[0])
    {
        if (ft_check_wrong_char_unset(word))
            ft_printf(1, "minishell: export: %s: not a valid identifier\n", word);
        else        
            ft_find_pos_in_av(word);
        start += ft_strlen(word) + 1;
        ft_strdel(&word);
        ft_skip_space(buf, &start);
        word = ft_get_word(&buf[start], 0);
        tmp = ft_strtrim(word, " ");
        ft_strdel(&word);
        word = tmp;    
    }
        ft_strdel(&word);
    close(g_shell.pip.id[g_shell.pip.i][1]);
    g_shell.pip.i++;   
    g_shell.pip.len++; 
    return (3);
}