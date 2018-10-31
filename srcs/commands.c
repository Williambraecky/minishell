/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:55:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/31 18:05:00 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TODO: parse arguments with ""
*/

void	exec_command(t_shell *shell, char *cmd)
{
	char	**split;
	char	*path;
	pid_t	pid;

	if (!(split = ft_strsplit(cmd, ' ')))
		error_exit_free("Out of memory", shell);
	if (split[0] && ft_strequ(split[0], "exit"))
		exit_builtin(shell, (int)ft_splitlen(split), split);
	if (!(path = extract_path(split[0])))
		path = find_path(shell, split[0]);
	if (!path)
	{
		if (split[0] && ft_strchr(split[0], '/'))
			ft_printf_fd(2, "minishell:\
			no such file or directory: %s\n", split[0]);
		else
			ft_printf_fd(2, "minishell: command not found: %s\n", split[0]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execve(path, split, shell->env);
		wait(&pid);
	}
}

void	display_reader(t_shell *shell)
{
	ft_printf("{yellow}%s@%s{eoc} $ ",
	get_env(shell, "USER"), get_env(shell, "HOST"));
}

void	read_commands(t_shell *shell)
{
	char	*str;
	char	*tmp;
	int		ret;

	display_reader(shell);
	while ((ret = get_next_line(0, &str)) == 1)
	{
		tmp = ft_strtrim(str);
		free(str);
		if (ft_strlen(tmp) > 0)
			exec_command(shell, tmp);
		free(tmp);
		display_reader(shell);
	}
	if (ret == -1)
		return ;
	return ;
}
