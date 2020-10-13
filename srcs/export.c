/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:36:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/13 18:53:41 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int         ft_error_export(char *buf, int type)
{
    char    *tmp;

    tmp = ft_get_word(buf, 0);
    if (type == NOT_FOUND)
        ft_printf(1, "minishell: %s: command not found\n", tmp);
    ft_strdel(&tmp);
    close(g_shell.pip.id[g_shell.pip.i][1]);
    g_shell.pip.i++;   
    g_shell.pip.len++;
    return (0);
}

int         ft_check_error_export(char *buf)
{
    int     i;
    int     cmp;
    int     check;

    i = 6;
    check = 0;
    if (buf[i] == '"' || buf[i] == 39)
    {
        check = buf[i];
        cmp = 1;
        while (check)
        {
            i++;
            if (check && buf[i] == check)
                check = 0;
            if (check && buf[i] != check)
                check = 0;
            if (!check && (buf[i] == '"' || buf[i] == 39))
                check = buf[i];
            cmp++;
        }
        if (cmp % 2 == 0)
            return (NOT_FOUND);
    }
    else if (buf[i] && buf[i] != ' ')
        return (NOT_FOUND);
    return (0);
}

void        ft_print_env(void)
{
    int     i;

    i = -1;
    while (g_shell.sort_env[++i])
    {
        ft_printf(STDOUT_FILENO, "%s", g_shell.sort_env[i]);
        write(STDOUT_FILENO, "\n", 1);
    }
}

int         ft_set_print_env(char *buf)
{
    int     i;
    int     check;
    pid_t   pid;

    i = -1;
    check = 0;
    while (buf[++i] && !check)
        if (buf[i] != ' ')
            check = 1;
    pid = fork();
    if (pid == 0)
    {
        close(g_shell.pip.id[g_shell.pip.i][0]);
        if (g_shell.out.len > 0)
            dup2(g_shell.out.fd[g_shell.out.len - 1], STDOUT_FILENO);
        else if (!g_shell.pip_str[g_shell.i_p + 1])
            ;
        else
            dup2(g_shell.pip.id[g_shell.pip.i][1], STDOUT_FILENO);
        if (!g_shell.error_input)
            ft_print_env();
        exit(g_shell.error_input);
    }
    close(g_shell.pip.id[g_shell.pip.i][1]);
    g_shell.pip.i++;   
    g_shell.pip.len++;   
    return (1);
}

void        ft_skip_quote(char *buf, int *i)
{
    int     check;

    check = 0;
    while (buf[*i])
    {
        if (buf[*i] == '"' || buf[*i] == 39)
        {
            check = buf[*i];
            *i += 1;
            if (buf[*i] == check)
                *i += 1;
            else
                return ; 
        }
        else if (buf[*i] != '"' && buf[*i] != 39)
        {
            *i += 1;
            return ;
        }
        else
         *i += 1;
    }
}

int         ft_len_word_with_quote(char *buf)
{
    int     len;
    int     i;
    int     check;

    i = 0;
    check = 0;
    len = 0;
    while (buf[i])
    {
        len++;
        if (!check && (buf[i] == '"' || buf[i] == 39))
            check = buf[i++];
        else if (check && (buf[i] == '"' || buf[i] == 39))
        {
            check = 0;
            i++;
        }
        else if (!check && buf[i] == ' ')
            break ;
        else
            i++;
    }
    return (len);
}

char        *ft_get_word_with_quote(char *buf)
{
    int     len;
    char    *new;
    int     i;

    i = 0;
    ft_skip_space(buf, &i);

    ft_printf(1, "buf = %s, buf[i] = |%c| %d\n", buf, buf[i], i);
    len = ft_len_word_with_quote(&buf[i]);
    if (!(new = malloc(sizeof(char) * (len + 1))))
        exit(-1000);
    ft_strlcpy(new, &buf[i], len + 1);
    return (new);
}

int             ft_check_wrong_char(char *var)
{
    int     i;

    i = 0;
    while (var[i] == '"' || var[i] == 39)
        i++;
    if (!ft_isalpha(var[i]) && var[i] != '_')
        return (1);
    while (var[i])
    {
        if (var[i] == '=')
            return (0);
        if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '"' && var[i] != 39)
            return (1);
        i++;
    }
    return (0);
}

int             ft_avlen(char **env)
{
    int     i;

    i = 0;
    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

char            **ft_add_var_to_env(char *var, char **env)
{
    int     i;
    char    **new;

    if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 2))))
        exit(-1000);
    i = -1;
    while (env[++i])
        new[i] = ft_strdup(env[i]);
    new[i++] = ft_strdup(var);
    new[i] = NULL;
    return (new);
}

char            **ft_avdup(char **env)
{
    char    **new;
    int     i;

    if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 1))))
        exit(-1000);
    i = -1;
    while (env[++i])
        new[i] = ft_strdup(env[i]);
    new[i] = NULL;
    return (new);
}

char            *ft_change_var(char *buf)
{
    char       *new;
    int         i;
    char        c;
    char        tmp[2];

    i = 0;
    tmp[0] = '"';
    tmp[1] = 0;
    ft_go_to_char(buf, &i, '=');
    c = buf[i];
    buf[i] = '\0';
    new = ft_copy_without_quote(buf, ft_strlen(buf));
    buf[i] = c;
    new = ft_str_add(new, ft_strdup("="));
    if (buf[i])
        ft_skip_quote(buf, &i);
    if (buf[i] != '"')
        new = ft_str_add(new, ft_strdup(tmp));
    new = ft_str_add(new, ft_strdup(&buf[i]));
    new = ft_str_add(new, ft_strdup(tmp));
    ft_printf(1, "new = |%s|\n", new);
    return (new);
}

int             ft_check_error_var(char *var)
{
    int     i;
    char    *buf;
    char    **tmp;

    i = 0;
    ft_skip_quote(var, &i);
    if (ft_check_wrong_char(var) || !var[i])
    {
        ft_printf(1, "minishell: export: %s: not a valid identifier\n", var);
        return (1);
    }
    i = 0;
    buf = ft_strdup(var);
    ft_change_var(buf);
    ft_go_to_char(var, &i, '=');
    ft_printf(1, "find '=' : %d\n", var[i]);
    if (var[i] == '=')
    {
        tmp = ft_add_var_to_env(var, g_shell.env);
        ft_free_av(g_shell.env);
        g_shell.env = ft_avdup(tmp);
        ft_free_av(tmp);
    }
    tmp = ft_add_var_to_env(var, g_shell.sort_env);
    ft_free_av(g_shell.sort_env);
    g_shell.sort_env = ft_avdup(tmp);
    ft_free_av(tmp);
    return (1);
}

void           ft_add_var(char *buf, int start)
{
    char    *word;

    word = ft_get_word_with_quote(&buf[start]);
    ft_printf(1, "word add = |%s|\n", word);
//    while (word[0])
//    {
    ft_check_error_var(word);
    ft_strdel(&word);
//    }
}

int         ft_export(char *buf)
{
    int     start;
    int     end;
    char    *word;

    pipe(g_shell.pip.id[g_shell.pip.i]);
    if (ft_check_error_export(buf))
        return (ft_error_export(buf, NOT_FOUND));
    start = 6;
    ft_skip_quote(buf, &start);
    word = ft_get_word_with_quote(&buf[start]);
    if (!word[0] && buf[start] != '"' && buf[start] != 39)
    {
        ft_strdel(&word);
        return (ft_set_print_env(&buf[start]));
    }
    ft_add_var(buf, start);
    ft_strdel(&word);
    return (2);
}