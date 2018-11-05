/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:57:16 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 19:08:23 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TODO: 27 lines
*/

int		setenv_builtin(t_shell *shell, int argc, char **argv)
{
	size_t	i;

	if (argc == 1)
	{
		print_env(shell);
		return (0);
	}
	else if (argc > 3)
		ft_printf_fd(2, "setenv: Too many arguments.\n");
	if (argc > 3)
		return (0);
	i = 0;
	while (argc <= 3 && argv[1][i])
	{
		if (!ft_isalnum(argv[1][i]))
		{
			ft_printf_fd(2, "setenv: Variable name must contain \
			alphanumeric characters.\n");
			return (0);
		}
		i++;
	}
	if (get_env(shell, argv[1]) != NULL)
		repl_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	else
		add_env(shell, argv[1], argc == 2 ? "" : argv[2]);
	return (0);
}
