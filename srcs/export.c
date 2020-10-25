/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:36:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/25 17:27:38 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_replace_quote(char *var)
{
	int		i;
	int		check;
	char	*tmp;

	check = 0;
	i = 0;
	while (var[i])
	{
		if ((!g_shell.check && (var[i] == 39 || var[i] == '"')) || g_shell.check == var[i])
		{
			tmp = ft_del_char(var, i);
			ft_strdel(&var);
			var = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else if (!g_shell.check && (var[i] == '"' || var[i] == 39))
			g_shell.check = var[i++];
		else
			i++;
	}
	return (var);
}

void		ft_add_var_2(char *var, int pos[], int equal)
{
	char	**tmp;

	var = ft_replace_quote(var);
	if (pos[0] == -1 && equal)
	{
		tmp = ft_add_var_to_env(var, g_shell.env);
		ft_free_av(g_shell.env);
		g_shell.env = ft_avdup(tmp);
		ft_free_av(tmp);
	}
	if (pos[1] == -1)
	{
		tmp = ft_add_var_to_env(var, g_shell.sort_env);
		ft_free_av(g_shell.sort_env);
		g_shell.sort_env = ft_avdup(tmp);
		ft_free_av(tmp);
	}
	if (pos[0] != -1 && equal)
	{
		ft_strdel(&g_shell.env[pos[1]]);
		g_shell.env[pos[1]] = ft_strdup(var);
	}
	if (pos[1] != -1 && equal)
	{
		ft_strdel(&g_shell.sort_env[pos[1]]);
		g_shell.sort_env[pos[1]] = ft_strdup(var);
	}
}

void		ft_add_var(char *buf, char *var, int start)
{
	char	*word;
	int		i;
	int		pos[2];

	i = 0;
	(void)buf;
	while (var[i])
	{
		if (var[i] == '=' && i > 0)
			break ;
		else if (!ft_exportable_char(var[i], i /*== 0 ? 1 : 0*/))
		{
			ft_printf(1, "minishell: export: %s: not a valid identifier\n", var);
			return ;
		}
		i++;
	}
	start = var[i] == '=' ? 1 : 0;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		exit(-1000);
	ft_strlcpy(word, var, i + 1);
	word = ft_str_add(word, ft_strdup("="));
	pos[0] = ft_find_var_in_av(g_shell.env, word);
	pos[1] = ft_find_var_in_av(g_shell.sort_env, word);
	ft_add_var_2(var, pos, start);
	ft_printf(1, "word cut = %s, i = %d\n", word, i);
	ft_strdel(&word);
}

char		*ft_switch_word(char *word)
{
	char		*tmp;

	tmp = ft_strtrim(word, " ");
	ft_strdel(&word);
	return (tmp);
}

int			ft_incremente_export(char *word)
{
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	ft_strdel(&word);
	return (1);
}

int			ft_export(char *buf)
{
	int		start;
	char	*word;

	pipe(g_shell.pip.id[g_shell.pip.i]);
	if (ft_check_error_export(buf))
		return (ft_error_export(buf, NOT_FOUND));
	start = 6;
	ft_skip_quote(buf, &start);
	word = ft_get_word_with_quote(&buf[start]);
	if (!word[0] && buf[start] != '"' && buf[start] != 39)
		return (ft_set_print_env(&buf[start], word));
	while (1)
	{
		word = ft_switch_word(word);
		if (!word[0])
			break ;
		ft_add_var(buf, word, start);
		start += ft_strlen(word) + 1;
		ft_strdel(&word);
		ft_skip_quote(buf, &start);
		word = ft_get_word_with_quote(&buf[start]);
	}
	return (ft_incremente_export(word));
}