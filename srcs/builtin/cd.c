/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 16:51:46 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_builtin(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
		chdir(get_env(shell, "HOME"));
	return (0);
}
