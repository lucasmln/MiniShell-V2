/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <jvaquer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:29:57 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/23 00:51:28 by jvaquer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_add_path(char *buf)
{
	char	*new;

	new = NULL;
	if ((!ft_strncmp(buf, "pwd", 3) && ft_strlen(buf) == 3) ||
			(!ft_strncmp(buf, "pwd", 3) && (buf[3] == '<' ||
				buf[3] == '>' || buf[3] == ' ')))
		new = ft_str_add(ft_strdup("/bin/"), buf);
	else if ((!ft_strncmp(buf, "echo", 4) && ft_strlen(buf) == 4) ||
			(!ft_strncmp(buf, "echo", 4) && (buf[4] == '<' ||
				buf[4] == '>' || buf[4] == ' ')))
		new = ft_str_add(ft_strdup("/bin/"), buf);
	else if ((!ft_strncmp(buf, "env", 3) && ft_strlen(buf) == 3) ||
			(!ft_strncmp(buf, "pwd", 3) && (buf[3] = '<' ||
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

	ret = 0;
	if (ft_check_redir(buf))
		return (g_shell.ret);
	buf = ft_del_redir(buf);
	tmp = ft_strtrim(buf, " ");
	ft_strdel(&buf);
	buf = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (!ft_strncmp(buf, "cd", 2))
		ret = ft_cd(buf);
	else if (!ft_strncmp(buf, "export", ft_strlen("export")))
		ret = ft_export(buf);
	else if (!ft_strncmp(buf, "unset", 5))
		ret = ft_unset(buf);
	else if (ft_check_exit(buf))
		ft_free_exit();
	else if (!g_shell.legal_exit)
		ret = ft_get_cmd(buf);
	ft_strdel(&buf);
	return (ret);
}
