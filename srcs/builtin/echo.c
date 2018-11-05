/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:12:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 18:06:20 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_builtin(t_shell *shell, int argc, char **argv)
{
	int	i;
	int	j;

	(void)shell;
	i = 1;
	j = 0;
	if (argc > 1 && ft_strequ(argv[i], "-n"))
	{
		j = 1;
		i++;
	}
	while (i < argc)
	{
		if (i != 1)
			ft_printf(" ");
		ft_printf("%s", argv[i++]);
	}
	if (j)
		ft_printf("\n");
	return (0);
}
