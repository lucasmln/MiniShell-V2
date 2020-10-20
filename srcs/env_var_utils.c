/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:55:18 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/20 18:03:16 by lmoulin          ###   ########.fr       */
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

int			ft_len_without_space(char *var)
{
	int		len;
	int		i;

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
	return (len);
}

char		*ft_trim_spaces(char *var)
{
	char	*str;
	int		len;
	int		i;

	len = ft_len_without_space(var);
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
	str[len] = '\0';
	return (str);
}

char		*ft_inexist_var(char *str, int save, char c, int *i)
{
	char	*new;

	str[save] = '\0';
	new = ft_strdup(str);
	str[save] = '$';
	if (c != '\0')
		new = ft_str_add(new, ft_strdup(&c));
	if (c != '\0')
		new = ft_str_add(new, ft_strdup(&str[*i + 1]));
	return (new);
}

char		ft_choose_good_quote(char *buf)
{
	int		i;

	i = 0;
	while (buf[i + 1])
	{
		if (buf[i] == 39)
			return ('"');
		else if (buf[i] == '"')
			return (39);
		i++;
	}
	return ('"');
}

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

void		ft_init_exist_var(char *str, char quote[], int save[], int *k)
{
	*k = 0;
	ft_go_to_char(g_shell.env[save[1]], k, '=');
	quote[0] = ft_choose_good_quote(&g_shell.env[save[1]][*k + 2]);
	quote[1] = '\0';
	str[save[0]] = '\0';
}

char		*ft_exist_var(char *str, int save[], char c, int *i)
{
	int		k;
	char	*new;
	char	*tmp;
	char	quote[2];

	ft_init_exist_var(str, quote, save, &k);
	new = ft_strdup(str);
	if ((!g_shell.check && quote[0] == '"') || (quote[0] == 39))
		new = ft_str_add(new, ft_strdup(quote));
	tmp = !g_shell.check ? ft_trim_spaces(&g_shell.env[save[1]][k + 1]) :
										ft_strdup(&g_shell.env[save[1]][k + 1]);
	tmp = ft_copy_env_var_without_quote(tmp);
	if ((!g_shell.check && quote[0] == '"') || (quote[0] == 39))
		tmp = ft_str_add(tmp, ft_strdup(quote));
	new = ft_str_add(new, tmp);
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
