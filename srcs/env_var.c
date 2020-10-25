/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:09:43 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/25 17:45:43 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_last_ret(char *str, int *i)
{
	char	*new;

	str[*i] = '\0';
	new = NULL;
	new = ft_str_add(ft_strdup(""), ft_strdup(str));
	new = ft_str_add(new, ft_itoa(g_shell.ret));
	str[*i] = '$';
	new = ft_str_add(new, ft_strdup(&str[*i + 2]));
	ft_strdel(&str);
	return (new);
}

int			ft_exportable_char(char c, int first)
{
	if (ft_isalpha(c) || c == '_' || (ft_isdigit(c) && !first))
		return (1);
	return (0);
}

int			ft_check_replace_var(char *str, int *i, int *save, int *k)
{
	char	*tmp;

	*save = *i;
	if (g_shell.check && str[*i + 1] && (str[*i + 1] == '"' || str[*i + 1] == 39))
		return ((*i += 1));
	if (!g_shell.check && str[*i + 1] && (str[*i + 1] == '"' || str[*i + 1] == 39))
	{
		tmp = ft_del_char(str, *i);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	if (str[*i + 1] && str[*i + 1] == '$')
		return ((*i += 2));
	if (str[*i + 1] && !ft_exportable_char(str[*i + 1], 1))
	{
		tmp = ft_del_char(str, *i);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
		tmp = ft_del_char(str, *i);
		ft_strdel(&str);
		str = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	*k = *i;
	return (0);
}

char		*ft_get_var_name(char *buf)
{
	int		i;
	char	*word;

	i = 1;
	if (!buf[i])
		return (ft_strdup(""));
	while (buf[i] && ft_exportable_char(buf[i], i == 0 ? 1 : 0))
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
		exit(-1000);
	ft_strlcpy(word, &buf[1], i);
	return (word);
}

char		*ft_replace_var(char *str, int *i)
{
	int		save;
	int		pos;
	char	*new;
	char	*word;
	char	*tmp;

	if (str[*i + 1] && str[*i + 1] == '?')
		return (ft_last_ret(str, i));
	if (ft_check_replace_var(str, i, &save, &pos))
		return (str);
	word = ft_get_var_name(&str[*i]);
	word = ft_str_add(word, ft_strdup("="));
	if ((pos = ft_find_var_in_av(g_shell.env, word)) == -1)
	{
		new = ft_strdup(str);
		while (++pos < (int)ft_strlen(word))
		{
			tmp = ft_del_char(new, *i);
			ft_strdel(&new);
			new = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
	else
		new = ft_exist_var(str, word, pos, i);
	ft_strdel(&str);
	ft_strdel(&word);
	return (new);
}

char		*ft_get_env_var(char *str)
{
	int		i;
//	char	*tmp;

	g_shell.check = 0;
	i = -1;
	while (str[++i])
	{
		// condition pour gerer le \ pas parfaitement fonctionnel mais globalement bon.
		// Il faudrait mettre le character qui suit le \ entre simple quote et delete le \ avec ft_del_char
		// Mais j'avoue que là j'ai la flemme donc on verra ca demain matin jpense
		/*if (str[i] == 92 && g_shell.check != 39)
		{
			tmp = ft_del_char(str, i);
			ft_strdel(&str);
			str = ft_strdup(tmp);
			ft_strdel(&tmp);
			if (str[i])
				i++;
		}*/
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

void		ft_check_env_var(void)
{
	int		i;

	i = -1;
	while (g_shell.pip_str[++i])
		g_shell.pip_str[i] = ft_get_env_var(g_shell.pip_str[i]);
}
