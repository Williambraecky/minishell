/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:46:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/31 18:05:16 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_shell	t_shell;

struct		s_shell
{
	char	**env;
	int		current_cmd;
};

/*
** Env
*/

char		*get_env(t_shell *shell, char *key);
void		free_env(char **env);
void		add_env(t_shell *shell, char *key, char *value);
void		init_env(t_shell *shell, char **env);
void		del_env(t_shell *shell, char *key);
void		repl_env(t_shell *shell, char *key, char *value);
void		print_env(t_shell *shell);

/*
** Builtin
*/

int			echo_builtin(t_shell *shell, int argc, char **argv);
int			cd_builtin(t_shell *shell, int argc, char **argv);
int			exit_builtin(t_shell *shell, int argc, char **argv);

/*
** Utils
*/

void		error_exit(char *str);
void		destroy_shell(t_shell *shell);
void		error_exit_free(char *str, t_shell *shell);
void		handle_sigint(int signal);
void		display_reader(t_shell *shell);

/*
** Commands
*/

char		*extract_path(char *str);
char		*find_path(t_shell *shell, char *cmd);
void		read_commands(t_shell *shell);

#endif
