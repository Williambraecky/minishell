/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:15:52 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 14:21:34 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *str)
{
	if (str)
		ft_printf_fd(2, "An error occured: %s\n", str);
	else
		ft_printf_fd(2, "An error occured\n");
	exit(0);
}

void	error_exit_free(char *str, t_shell *shell)
{
	if (str)
		ft_printf_fd(2, "An error occured: %s\n", str);
	else
		ft_printf_fd(2, "An error occured\n");
	destroy_shell(shell);
	exit(0);
}
