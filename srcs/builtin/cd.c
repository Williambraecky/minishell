/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:44:30 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/21 14:14:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_3_args(char *pwd, char **argv)
{
	char	*ret;

	if (!ft_strstr(pwd, argv[1]))
	{
		ft_printf_fd(2, "cd: string not in pwd: %s\n", argv[1]);
		return (NULL);
	}
	ret = ft_strsrepl(pwd, argv[1], argv[2]);
	if (!ret)
	{
		free(pwd);
		ft_printf_fd(2, "cd: Out of memory\n");
	}
	return (ret);
}

static int	exec_cd(t_shell *shell, char *old_pwd, char *path, int fr)
{
	struct stat	st;
	char		buff[4097];

	if (path && stat(path, &st) == -1)
		return (ft_printf_fd(2, "cd: no such file or directory: %s\n", path));
	else if (path && !S_ISDIR(st.st_mode))
		return (ft_printf_fd(2, "cd: not a directory: %s\n", path));
	else if (path && access(path, R_OK) == -1)
		return (ft_printf_fd(2, "cd: permission denied: %s\n", path));
	else
	{
		if (get_env(shell, "OLDPWD"))
			repl_env(shell, "OLDPWD", old_pwd);
		else
			add_env(shell, "OLDPWD", old_pwd);
		chdir(path);
		if (get_env(shell, "PWD"))
			repl_env(shell, "PWD", getcwd(buff, 4096));
		else
			add_env(shell, "PWD", getcwd(buff, 4096));
	}
	if (fr)
		free(path);
	return (0);
}

int			cd_builtin(t_shell *shell, int argc, char **argv)
{
	char		*old_pwd;
	char		*path;
	int			ret;

	if (!(old_pwd = get_pwd()))
		ft_printf_fd(2, "cd: Out of memory\n");
	else if (argc == 1)
		path = get_env(shell, "HOME");
	else if (argc == 2)
	{
		if (ft_strequ(argv[1], "-") && !(path = get_env(shell, "OLDPWD")))
			ret = ft_printf_fd(2, "cd: no OLDPWD env set\n");
		else
			path = argv[1];
	}
	else if (argc == 3)
		path = handle_3_args(old_pwd, argv);
	else if (argc > 3)
		ft_printf_fd(2, "cd: too many arguments\n");
	ret = 0;
	if (old_pwd && path && argc <= 3)
		ret = exec_cd(shell, old_pwd, path, argc == 3);
	free(old_pwd);
	return (ret != 0);
}
