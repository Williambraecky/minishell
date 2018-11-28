/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:49:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/28 17:44:26 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions check if input is complete and returns the quote needed
** for completion
*/

int		is_cmd_complete(char *cmd)
{
	char	c_quote;

	c_quote = 0;
	while (*cmd)
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
	return (c_quote);
}

char	*copy_parsed_cmd_param(char *str, char *cmd)
{
	char	*end;
	char	c_quote;

	end = str;
	c_quote = 0;
	while (*cmd && ((*cmd != ' ' && *cmd != '\t') || c_quote))
	{
		if (ft_is_quote(*cmd))
		{
			c_quote = *cmd++;
			while (*cmd && *cmd != c_quote)
				*end++ = *cmd++;
			cmd++;
		}
		else
			*end++ = *cmd++;
	}
	return (cmd);
}

char	*find_env_value(t_shell *shell, char *str)
{
	size_t	len;
	size_t	i;
	size_t	x;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	if (len == 1)
		return ("$");
	i = 0;
	while (shell->env[i])
	{
		if (shell->env[i][len - 1] == '=')
		{
			x = len;
			while (x-- > 1)
				if (str[x] != shell->env[i][x - 1])
					break ;
			if (x == 0)
				return (shell->env[i] + len);
		}
		i++;
	}
	return ("");
}

char	*str_translate_env(t_shell *shell, char *str)
{
	char	*ret;
	char	*env;
	char	*tmp;
	char	*key;

	if (str[0] == '~')
		ret = ft_strsrepl(str, "~", get_env(shell, "HOME"));
	else
		ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	env = ft_strchr(ret, '$');
	while (env != NULL)
	{
		tmp = ret;
		if ((key = extract_key(env)))
			ret = ft_strsrepl(ret, key, find_env_value(shell, env));
		free(key);
		free(tmp);
		env = (ret == NULL ? NULL : ft_strchr(ret, '$'));
	}
	return (ret);
}

char	**cmd_translate_env(t_shell *shell, char **split)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '$') || ft_strchr(split[i], '~'))
		{
			tmp = str_translate_env(shell, split[i]);
			if (!tmp)
			{
				free_env(split);
				return (NULL);
			}
			free(split[i]);
			split[i] = tmp;
		}
		i++;
	}
	return (split);
}
