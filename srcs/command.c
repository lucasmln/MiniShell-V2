/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:29:57 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 18:05:35 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_add_path(char *buf)
{
	char	*new;
	char	*tmp;

	new = NULL;
	if ((PWD && ft_strlen(buf) == 3) || (PWD && (buf[3] == '<' ||
											buf[3] == '>' || buf[3] == ' ')))
		new = ft_str_add(ft_strdup("/bin/"), buf);
	else if ((ECHO && ft_strlen(buf) == 4) || (ECHO && (buf[4] == '<' ||
											buf[4] == '>' || buf[4] == ' ')))
		new = ft_str_add(ft_strdup("/bin/"), buf);
	else if ((ENV && ft_strlen(buf) == 3) || (ENV && (buf[3] = '<' ||
											buf[3] == '>' || buf[3] == ' ')))
		new = ft_str_add(ft_strdup("/usr/bin/"), buf);
	if (new)
	{
		if (buf)
			buf = NULL;
		buf = new;
	}
	return (buf);
}

int			ft_try_cmd(char *buf)
{
	int		ret;
	char	*tmp;

	if (ft_check_redir(buf))
		return (g_shell.ret);
	buf = ft_del_redir(buf);
	tmp = ft_strtrim(buf, " ");
	ft_strdel(&buf);
	buf = tmp;
	if (!ft_strncmp(buf, "cd", 2))
		ret = ft_cd(buf);
	else if (!ft_strncmp(buf, "export", 6))
		ret = ft_export(buf);
	else if (UNSET)
		ret = ft_unset(buf);
	else if (ft_check_exit(buf))
		ft_free_exit();
	else if (!g_shell.legal_exit)
		ret = ft_get_cmd(buf);
	ft_strdel(&buf);
	return (ret);
}