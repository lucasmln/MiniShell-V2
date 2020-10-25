/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:55:18 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/25 17:51:36 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_check_except_env(char *str, int *i)
{
	int		k;

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
/*
char		*ft_inexist_var(char *str, int *i)
{
	char	*new;

//	str[save] = '\0';
	new = ft_strdup(str);
	*i += 1;
	str[save] = '$';
	if (c != '\0')
		new = ft_str_add(new, ft_strdup(&c));
	if (c != '\0')
		new = ft_str_add(new, ft_strdup(&str[*i + 1]));
	return (new);
}
*/
char		*ft_copy_env_var_without_quote(char *var)
{
	char	*new;
	int		i;
	int		k;

	if (!(new = malloc(sizeof(char) * (ft_strlen(var) - 2 + 1))))
		exit(-1000);
	i = 1;
	k = 0;
	while (var[i + 1])
		new[k++] = var[i++];
	new[k] = '\0';
	ft_strdel(&var);
	return (new);
}

char		*ft_exist_var(char *str, char *word, int pos, int *i)
{
	char	*new;
	char	*var;
	char	*tmp;

	if (!(new = malloc(sizeof(char) * (*i + 1))))
		exit(-1000);
	ft_strlcpy(new, str, *i + 1);
	var = ft_strdup(&g_shell.env[pos][ft_strlen(word)]);
	if (!g_shell.check)
	{
		tmp = ft_trim_spaces(var);
		ft_strdel(&var);
		var = tmp;
	}
	new = ft_str_add(new, var);
	new = ft_str_add(new, ft_strdup(&str[*i + ft_strlen(word)]));
	return (new);
}