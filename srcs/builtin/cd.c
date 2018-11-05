/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/05 18:32:03 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_3_args(char **argv)
{
	char	*pwd;
	char	*ret;

	if (!(pwd = get_pwd()))
	{
		ft_printf_fd(2, "cd: Out of memory\n");
		return (NULL);
	}
	if (!ft_strstr(pwd, argv[1]))
	{
		ft_printf_fd(2, "cd: string not in pwd: %s\n", argv[1]);
		return (NULL);
	}
	ret = ft_strsrepl(pwd, argv[1], argv[2]);
	free(pwd);
	if (!ret)
		ft_printf_fd(2, "cd: Out of memory\n");
	return (ret);
}

int			cd_builtin(t_shell *shell, int argc, char **argv)
{
	struct stat	st;
	char		*path;

	if (argc == 1)
		path = get_env(shell, "HOME");
	else if (argc == 2)
		path = argv[1];
	else if (argc == 3)
		path = handle_3_args(argv);
	else if (argc > 3)
		ft_printf_fd(2, "cd: too many arguments\n");
	if (argc <= 3 && path)
	{
		if (stat(path, &st) == -1)
			ft_printf_fd(2, "cd: no such file or directory: %s\n", path);
		else if (access(argv[1], R_OK) == -1)
			ft_printf_fd(2, "cd: permission denied: %s\n", path);
		else
			chdir(path);
		if (argc == 3)
			free(path);
	}
	return (0);
}
