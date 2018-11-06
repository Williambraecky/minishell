/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:57:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 10:05:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *arg)
{
	while (*arg)
		if (!ft_isalnum(*arg++))
			return (0);
	return (1);
}

int			setenv_builtin(t_shell *shell, int argc, char **argv)
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
	if (!ft_isalpha(argv[1][0]))
		ft_printf_fd(2, "setenv: Variable name must begin with a letter.\n");
	else if (!check_arg(argv[1]))
		ft_printf_fd(2, "setenv: Variable name must contain \
alphanumeric characters.\n");
	else if (get_env(shell, argv[1]) != NULL)
		repl_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	else
		add_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	return (0);
}
