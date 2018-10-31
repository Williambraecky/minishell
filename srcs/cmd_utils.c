/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 09:33:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/31 09:49:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Retrieve path from command, send command only not parameters
*/

char	*extract_path(char *str)
{
	char	*ret;
	char	*slash;
	size_t	len;

	if (!str || !(slash = ft_strrchr(str, '/')))
		return (NULL);
	len = slash - str;
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (len--)
		ret[len] = str[len];
	return (ret);
}

/*
** Finds path for command from $PATH
*/

char	*find_path(t_shell *shell, char *cmd)
{
	char		**paths;
	char		*tmp;
	struct stat	st;
	size_t		i;

	if (!cmd || !get_env(shell, "PATH") ||
		!(paths = ft_strsplit(get_env(shell, "PATH"), ':')))
		return (NULL);
	tmp = NULL;
	i = 0;
	while (paths[i] && !tmp)
	{
		tmp = ft_strtrijoin(paths[i++], "/", cmd);
		if (stat(tmp, &st) == -1 || !S_ISDIR(st.st_mode))
			ft_strdel(&tmp);
		else
		{
			ft_strdel(&tmp);
			tmp = ft_strdup(paths[i - 1]);
		}
	}
	free_env(paths);
	return (tmp);
}
