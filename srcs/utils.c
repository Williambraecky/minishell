/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:09:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/21 13:25:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	char	*ret;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\t' && str[len] != ' ' && str[len] != '\n')
		len++;
	if (!(ret = ft_strnew(len)))
		return (NULL);
	ft_strncpy(ret, str, len);
	return (ret);
}

int		ft_contains_alpha(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (1);
		str++;
	}
	return (0);
}

int		ft_is_quote(char c)
{
	if (c == '\'' || c == '\"' || c == '`')
		return (1);
	return (0);
}

char	*get_pwd(void)
{
	char	*buf;

	if (!(buf = ft_strnew(MAXPATHLEN)))
		return (NULL);
	buf = getcwd(buf, MAXPATHLEN);
	return (buf);
}

void	print_env(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
}
