/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:06:19 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:11:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TODO: Execute args as command if argc > 1
*/

int		env_builtin(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		print_env(shell);
		return (0);
	}
	return (0);
}
