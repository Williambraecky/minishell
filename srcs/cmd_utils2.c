/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:49:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/09/25 17:26:33 by wbraeckm         ###   ########.fr       */
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
	while (*cmd && *cmd != ' ' && *cmd != '\t')
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
	char	*ret;

	if (ft_strequ(str, "$"))
		return ("$");
	if ((ret = get_env(shell, str + 1)))
		return (ret);
	return ("");
}

char	*str_translate_env(t_shell *shell, char *str)
{
	char	*ret;
	char	*tmp;
	char	*key;
	size_t	env_pos;

	if (str[0] == '~' && get_env(shell, "HOME"))
		ret = ft_strsrepl(str, "~", get_env(shell, "HOME"));
	else
		ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	env_pos = ft_strfind(ret, '$');
	while (ret && ret[env_pos])
	{
		tmp = ret;
		if ((key = extract_key(ret + env_pos)))
		{
			ret = ft_strsrepl(ret, key, find_env_value(shell, key));
			env_pos += ft_strlen(find_env_value(shell, key));
			free(key);
			free(tmp);
		}
		env_pos += ft_strfind(ret ? ret + env_pos : "", '$');
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
