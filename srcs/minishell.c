/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:45:18 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/31 18:05:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

void	handle_sigint(int signal)
{
	(void)signal;
	ft_printf("\n");
	display_reader(g_shell);
}

int		main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	if (!(shell = ft_memalloc(sizeof(*shell))))
		error_exit("Out of memory");
	g_shell = shell;
	signal(SIGINT, handle_sigint);
	init_env(shell, env);
	read_commands(shell);
	destroy_shell(shell);
	return (0);
}
