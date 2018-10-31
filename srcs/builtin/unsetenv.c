/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:02:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:05:48 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_builtin(t_shell *shell, int argc, char **argv)
{
	int	i;

	if (argc == 1)
	{
		ft_printf_fd(2, "unsetenv: Too few arguments.\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (get_env(shell, argv[i]) != NULL)
			del_env(shell, argv[i]);
		i++;
	}
	return (0);
}
