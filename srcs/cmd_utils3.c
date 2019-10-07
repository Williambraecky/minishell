/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:49:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 16:16:12 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_is_builtin(char *cmd)
{
	if (ft_strequ(cmd, "exit"))
		return (1);
	else if (ft_strequ(cmd, "cd"))
		return (1);
	else if (ft_strequ(cmd, "env"))
		return (1);
	else if (ft_strequ(cmd, "setenv"))
		return (1);
	else if (ft_strequ(cmd, "unsetenv"))
		return (1);
	else if (ft_strequ(cmd, "echo"))
		return (1);
	return (0);
}

void	exec_builtin(t_shell *shell, char **s)
{
	if (ft_strequ(s[0], "exit"))
		exit_builtin(shell, (int)ft_splitlen(s), s);
	else if (ft_strequ(s[0], "cd"))
		cd_builtin(shell, (int)ft_splitlen(s), s);
	else if (ft_strequ(s[0], "env"))
		env_builtin(shell, (int)ft_splitlen(s), s);
	else if (ft_strequ(s[0], "setenv"))
		setenv_builtin(shell, (int)ft_splitlen(s), s);
	else if (ft_strequ(s[0], "unsetenv"))
		unsetenv_builtin(shell, (int)ft_splitlen(s), s);
	else if (ft_strequ(s[0], "echo"))
		echo_builtin(shell, (int)ft_splitlen(s), s);
	free_env(s);
}

int		is_dir(char *str)
{
	struct stat st;

	stat(str, &st);
	return (S_ISDIR(st.st_mode));
}
