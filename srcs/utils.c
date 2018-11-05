/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:09:13 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 14:49:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strtrimlen(char *str)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	start = i;
	end = i;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			end = i;
		i++;
	}
	return (end - start);
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
