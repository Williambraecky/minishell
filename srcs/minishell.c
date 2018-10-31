/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:45:18 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:53:14 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	if (!(shell = ft_memalloc(sizeof(*shell))))
		error_exit("Out of memory");
	init_env(shell, env);
	char	buffer[512];
	//cd_builtin(shell, 1, NULL);
	getcwd(buffer, 512);
	ft_printf("%s\n", buffer);
	destroy_shell(shell);
	return (0);
}
