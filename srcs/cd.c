/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:08:37 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/19 19:03:52 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_check_error_cd(char *buf)
{
	int		i;

	i = 2;
	g_shell.tmp_ret = !g_shell.pip_str[g_shell.i_p + 1] ? 0 : g_shell.tmp_ret;
	if (!buf[i])
		return (0);
	if (buf[i] == '"' && buf[i + 1] && buf[i + 1] == '"')
		return (0);
	if (buf[i] == 39 && buf[i + 1] && buf[i + 1] == 39)
		return (0);
	if (buf[i] == ' ')
		return (0);
	g_shell.tmp_ret = 127;
	return (1);
}

int			ft_cd_home(char *buf)
{
	int		i;
	int		pos;
	char	*home;

	i = 0;
	ft_skip_space(buf, &i);
	if (buf[i] == 39 || buf[i] == '"')
		return (1);
	pos = ft_find_var_in_av(g_shell.env, "HOME=");
	if (pos == -1)
		return (ft_error_cd(buf, NO_HOME));
	home = ft_strdup(&g_shell.env[pos][5]);
	pos = ft_find_var_in_av(g_shell.env, "OLDPWD=");
	if (pos == -1)
		return (ft_error_cd(buf, NO_PWD));
	ft_change_env_pwd(ft_strdup(home));
	chdir(home);
	ft_strdel(&home);
	return (1);
}

int			ft_cd_back(void)
{
	int		i;
	int		k;
	char	*tmp;
	char	*path;

	i = ft_find_var_in_av(g_shell.env, "OLDPWD=");
	k = ft_find_var_in_av(g_shell.env, "PWD=");
	if (i == -1 || k == -1)
		return (ft_error_cd("PWD", NO_PWD));
	path = ft_strdup(&g_shell.env[i][7]);
	ft_change_env_pwd(ft_strdup(path));
	chdir(path);
	ft_strdel(&path);
	return (1);
}

int			ft_cd_directory(char *dir)
{
	struct stat		info;
	char			*path;

	path = NULL;
	if (stat(dir, &info))
		return (ft_error_cd(dir, NOT_FOUND));
	if (S_ISREG(info.st_mode))
		return (ft_error_cd(dir, NOT_DIR));
	chdir(dir);
	path = getcwd(path, 0);
	ft_change_env_pwd(ft_strdup(path));
	ft_strdel(&g_shell.dir);
	g_shell.dir = ft_strdup(path);
	ft_strdel(&path);
	return (1);
}

int			ft_cd(char *buf)
{
	char	*tmp;
	int		i;
	int		k;
	int		ret;

	pipe(g_shell.pip.id[g_shell.pip.i]);
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.pip.i++;
	g_shell.pip.len++;
	if (ft_check_error_cd(buf))
		return (ft_error_cd(buf, NOT_FOUND));
	tmp = ft_get_word(buf, 0);
	i = ft_strlen(tmp);
	ft_strdel(&tmp);
	tmp = ft_get_word(&buf[i], 0);
	k = g_shell.pip_str[g_shell.i_p + 1] == NULL &&
			!g_shell.error_input ? 1 : 0;
	if (!tmp[0] && k)
		ret = ft_cd_home(&buf[i]);
	else if (!ft_strncmp(tmp, "-", ft_strlen(tmp)) && k)
		ret = ft_cd_back();
	else if (k)
		ret = ft_cd_directory(tmp);
	ft_strdel(&tmp);
	return (1);
}
