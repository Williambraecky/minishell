/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:41:59 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:44:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_builtin(t_shell *shell, int argc, char **argv)
{
	if (argc == 1)
	{
		destroy_shell(shell);
		exit(0);
	}
	else if (argc >= 2)
	{
		if (!ft_strisnumber(argv[1]))
			ft_printf_fd(2, "exit: Badly formed number.\n");
		else
			exit((unsigned char)ft_atoi(argv[1]));
	}
	return (0);
}
