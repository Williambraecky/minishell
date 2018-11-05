/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:49:25 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 15:02:01 by wbraeckm         ###   ########.fr       */
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
