/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:55:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 15:08:58 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_shell *shell, char *path, char **s)
{
	pid_t	pid;

	shell->running = 1;
	pid = fork();
	if (pid == 0)
		execve(path, s, shell->env);
	wait(&pid);
	shell->running = 0;
}

/*
** Make sure $ENV and ~ are translated correctly
*/

void	preprocess_command(t_shell *shell, char *cmd)
{
	char	**s;
	char	*path;

	if (!(s = parse_cmd(cmd)))
		error_exit_free("Out of memory", shell);
	if (s[0] && ft_strequ(s[0], "exit"))
		exit_builtin(shell, (int)ft_splitlen(s), s);
	path = find_path(shell, s[0]);
	if (!path)
	{
		if (s[0] && ft_strchr(s[0], '/'))
			ft_printf_fd(2, "minishell: no such file or directory: %s\n", s[0]);
		else
			ft_printf_fd(2, "minishell: command not found: %s\n", s[0]);
		free_env(s);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_printf_fd(2, "minishell: permission denied: %s\n", s[0]);
		free_env(s);
		free(path);
	}
	else
		exec_command(shell, path, s);
}

void	display_reader(t_shell *shell)
{
	char	*path;

	path = get_path_for_reader(shell);
	if (get_env(shell, "HOST") && path)
		ft_printf("{yellow}%s{eoc}@{yellow}%s{eoc}:{magenta}%s{eoc} $ ",
		get_env(shell, "USER"), get_env(shell, "HOST"), path);
	else if (path)
		ft_printf("{yellow}%s{eoc}:{magenta}%s{eoc} $ ",
		get_env(shell, "USER"), path);
	else
		ft_printf("{yellow}%s{eoc} $ ", get_env(shell, "USER"));
	free(path);
}

void	display_quote_reader(int quote)
{
	if (quote == '\'')
		ft_printf("quote> ");
	else if (quote == '\"')
		ft_printf("dquote> ");
	else if (quote == '`')
		ft_printf("bquote> ");
}

/*
** Redesign how we handle command reading -> dquote quote and bquote
*/

void	read_commands(t_shell *shell)
{
	char	*str;
	char	*tmp;
	int		ret;

	while ((ret = get_next_line(0, &str)) == 1)
	{
		tmp = shell->cmd;
		shell->cmd = (shell->cmd == NULL) ? ft_strdup(str) :
			ft_strtrijoin(shell->cmd, "\n", str);
		free(str);
		ft_strdel(&tmp);
		if ((ret = is_cmd_complete(shell->cmd)))
		{
			display_quote_reader(ret);
			continue ;
		}
		if (ft_strtrimlen(shell->cmd) > 0)
			preprocess_command(shell, shell->cmd);
		display_reader(shell);
		ft_strdel(&(shell->cmd));
	}
	if (ret == -1)
		ft_printf_fd(2, "minishell: error while reading input");
	return ;
}
