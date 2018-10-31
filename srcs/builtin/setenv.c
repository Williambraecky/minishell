/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:57:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:10:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setenv_builtin(t_shell *shell, int argc, char **argv)
{
	if (argc == 1)
	{
		print_env(shell);
		return (0);
	}
	else if (argc > 3)
	{
		ft_printf_fd(2, "setenv: Too many arguments.\n");
		return (0);
	}
	if (get_env(shell, argv[1]) != NULL)
		repl_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	else
		add_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	return (0);
}
