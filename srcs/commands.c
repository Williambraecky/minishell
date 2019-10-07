/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:55:07 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 16:17:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_shell *shell, char *path, char **s)
{
	pid_t	pid;
	int		status;

	shell->running = 1;
	pid = fork();
	if (pid == -1)
	{
		error_exit_free("Could not create fork process", shell);
	}
	if (pid == 0)
	{
		execve(path, s, shell->env);
		return ;
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	shell->running = 0;
}

/*
** Execute builtins
*/

void	preprocess_command(t_shell *shell, char *cmd)
{
	char	**s;
	char	*path;

	if (!(s = parse_cmd(cmd)))
		error_exit_free("Out of memory", shell);
	if (!(s = cmd_translate_env(shell, s)))
		error_exit_free("Out of memory", shell);
	if (s[0] && cmd_is_builtin(s[0]))
		return (exec_builtin(shell, s));
	path = find_path(shell, s[0]);
	if (!path)
	{
		if (s[0] && ft_strchr(s[0], '/'))
			ft_printf_fd(2, "minishell: no such file or directory: %s\n", s[0]);
		else
			ft_printf_fd(2, "minishell: command not found: %s\n", s[0]);
	}
	else if (access(path, X_OK) == -1)
		ft_printf_fd(2, "minishell: permission denied: %s\n", s[0]);
	else if (is_dir(path))
		ft_printf_fd(2, "minishell: %s: is a directory\n", s[0]);
	else
		exec_command(shell, path, s);
	free_env(s);
	free(path);
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
		if (ft_contains_alpha(shell->cmd))
			preprocess_command(shell, shell->cmd);
		display_reader(shell);
		ft_strdel(&(shell->cmd));
	}
	if (ret == -1)
		ft_printf_fd(2, "minishell: error while reading input\n");
	return ;
}
