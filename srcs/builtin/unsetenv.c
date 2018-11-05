/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:02:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 18:11:55 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_builtin(t_shell *shell, int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf_fd(2, "unsetenv: Too few arguments.\n");
		return (0);
	}
	while (argc-- > 1)
		if (get_env(shell, argv[argc]) != NULL)
			del_env(shell, argv[argc]);
	return (0);
}
