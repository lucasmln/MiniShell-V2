/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:36:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/26 17:08:28 by lucas            ###   ########.fr       */
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
		if ((!g_shell.check && (var[i] == 39 || var[i] == '"')) ||
													g_shell.check == var[i])
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

void		ft_add_var_utils(char *var, int pos[], int equal)
{
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

char		*ft_add_var_2(char *var, int pos[], int equal)
{
	char	**tmp;
	char	*temp;

	temp = ft_replace_quote(ft_strdup(var));
	if (pos[0] == -1 && equal)
	{
		tmp = ft_add_var_to_env(temp, g_shell.env);
		ft_free_av(g_shell.env);
		g_shell.env = ft_avdup(tmp);
		ft_free_av(tmp);
	}
	if (pos[1] == -1)
	{
		tmp = ft_add_var_to_env(temp, g_shell.sort_env);
		ft_free_av(g_shell.sort_env);
		g_shell.sort_env = ft_avdup(tmp);
		ft_free_av(tmp);
	}
	ft_add_var_utils(temp, pos, equal);
	return (temp);
}

char		*ft_add_var(char *var, int start)
{
	char	*word;
	int		i;
	int		pos[2];

	i = 0;
	while (var[i])
	{
		if (var[i] == '=' && i > 0)
			break ;
		else if (!ft_exportable_char(var[i], i == 0 ? 1 : 0))
		{
			ft_printf(1, "minishell: export: %s: not valid identifier\n", var);
			return (ft_strdup(var));
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
	ft_strdel(&word);
	return (ft_add_var_2(var, pos, start));
}

int			ft_export(char *buf)
{
	int		start;
	char	*word;
	char	*tmp;

	pipe(g_shell.pip.id[g_shell.pip.i]);
	if (ft_check_error_export(buf))
		return (ft_error_export(buf, NOT_FOUND));
	ft_incremente_start(buf, &start, 1);
	word = ft_get_word_with_quote(&buf[start]);
	if (!word[0] && buf[start] != '"' && buf[start] != 39)
		return (ft_set_print_env(&buf[start], word));
	while (1)
	{
		tmp = ft_strtrim(word, " ");
		ft_switch_word(&word, &tmp);
		start += ft_strlen(word);
		tmp = ft_add_var(word, start);
		ft_switch_word(&word, &tmp);
		ft_strdel(&word);
		if (!buf[start])
			break ;
		ft_incremente_start(buf, &start, 0);
		word = ft_get_word_with_quote(&buf[start]);
	}
	return (ft_incremente_export(word));
}
