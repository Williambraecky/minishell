/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 09:33:55 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 10:08:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	parse_cmd_count(char *cmd)
{
	size_t	len;
	char	c_quote;

	len = 0;
	c_quote = 0;
	while (*cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		len += *cmd != '\0';
		while (*cmd && ((*cmd != ' ' && *cmd != '\t') || c_quote))
		{
			if (ft_is_quote(*cmd))
			{
				if (c_quote == *cmd)
					c_quote = 0;
				else if (c_quote == 0)
					c_quote = *cmd;
			}
			cmd++;
		}
	}
	return (len);
}

size_t	cmd_word_len(char *cmd)
{
	size_t	len;
	char	c_quote;

	len = 0;
	c_quote = 0;
	while (*cmd && ((*cmd != ' ' && *cmd != '\t') || c_quote))
	{
		if (ft_is_quote(*cmd))
		{
			c_quote = *cmd++;
			while (*cmd && *cmd != c_quote)
			{
				len++;
				cmd++;
			}
			cmd++;
		}
		len++;
		cmd++;
	}
	return (len);
}

char	**parse_cmd(char *cmd)
{
	char	**ret;
	size_t	i;
	size_t	len;
	size_t	c_len;

	len = parse_cmd_count(cmd);
	if (!(ret = ft_memalloc(sizeof(*ret) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		c_len = cmd_word_len(cmd);
		if (!(ret[i] = ft_strnew(c_len)))
		{
			free_env(ret);
			return (NULL);
		}
		cmd = copy_parsed_cmd_param(ret[i++], cmd);
	}
	return (ret);
}

char	*get_path_for_reader(t_shell *shell)
{
	char	*path;
	char	*ret;

	if (!(path = get_pwd()))
		return (NULL);
	if (ft_strequ(path, get_env(shell, "HOME")))
	{
		free(path);
		return (ft_strdup("~"));
	}
	ret = ft_strrchr(path, '/');
	if (ret)
		ret = ft_strdup((ret == path) ? ret : ret + 1);
	free(path);
	return (ret);
}

char	*find_path(t_shell *shell, char *cmd)
{
	char		**paths;
	char		*tmp;
	struct stat	st;
	size_t		i;

	if (!cmd || ft_strequ(cmd, "..") || ft_strequ(cmd, "."))
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (stat(cmd, &st) == -1 ? NULL : ft_strdup(cmd));
	if (!get_env(shell, "PATH") ||
		!(paths = ft_strsplit(get_env(shell, "PATH"), ':')))
		return (NULL);
	tmp = NULL;
	i = 0;
	while (paths[i] && !tmp)
	{
		tmp = ft_strtrijoin(paths[i++], "/", cmd);
		if (stat(tmp, &st) == -1)
			ft_strdel(&tmp);
	}
	free_env(paths);
	return (tmp);
}
