/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:29:57 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:58:37 by lmoulin          ###   ########.fr       */
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

int			ft_get_cmd(char *buf)
{
//	ft_printf(1, "arrived buf = %s\n", buf);
	if (ft_check_redir(buf))
		return (g_shell.ret);
	buf = ft_del_redir(buf);
//	printf("buf without redir = %s\n", buf);
	if (ECHO || PWD || ENV)
	{
		buf = ft_add_path(buf);
	}
//	printf("buf modified = %s\n", buf);
	if (CD)
		g_shell.ret = 1;//ft_cd(&buf[i + 2]);
	else if (EXPORT)
		g_shell.ret = 2;//ft_export(&buf[i + ft_strlen("export")]);
	else if (UNSET)
		g_shell.ret = 3;//ft_unset(&buf[i + ft_strlen("unset")]);
	else if (ft_check_exit(buf))
		ft_free_exit();
	else if (!g_shell.legal_exit)
		ft_exec_cmd(buf);
	ft_strdel(&buf);
	return (1/*(g_shell.ret)*/);
}
