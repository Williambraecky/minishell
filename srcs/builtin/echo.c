/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:12:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:14:54 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_builtin(t_shell *shell, int argc, char **argv)
{
	int	i;

	i = 1;
	(void)shell;
	while (i < argc)
	{
		if (i != 1)
			ft_printf(" ");
		ft_printf("%s", argv[i++]);
	}
	ft_printf("\n");
	return (0);
}
