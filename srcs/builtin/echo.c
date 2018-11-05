/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:12:26 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 18:58:18 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_builtin(t_shell *shell, int argc, char **argv)
{
	int	i;
	int	n_opt;

	(void)shell;
	i = 1;
	n_opt = 0;
	if (argc > 1 && ft_strequ(argv[i], "-n"))
	{
		n_opt = 1;
		i++;
	}
	while (i < argc)
	{
		if (i != 1 + n_opt)
			ft_printf(" ");
		ft_printf("%s", argv[i++]);
	}
	if (n_opt == 0)
		ft_printf("\n");
	return (0);
}
