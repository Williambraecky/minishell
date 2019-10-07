/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:46:05 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/10/07 16:16:23 by wbraeckm         ###   ########.fr       */
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
# include <sys/param.h>

# define BUFF_SIZE 512

typedef struct s_shell	t_shell;

struct		s_shell
{
	char	**env;
	char	*cmd;
	int		running;
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
int			unsetenv_builtin(t_shell *shell, int argc, char **argv);
int			setenv_builtin(t_shell *shell, int argc, char **argv);
int			env_builtin(t_shell *shell, int argc, char **argv);

/*
** Utils
*/

void		error_exit(char *str);
void		destroy_shell(t_shell *shell);
void		error_exit_free(char *str, t_shell *shell);
void		handle_sigint(int signal);
void		display_reader(t_shell *shell);
char		*get_pwd(void);
char		*get_path_for_reader(t_shell *shell);
int			ft_is_quote(char c);
int			is_cmd_complete(char *cmd);
int			ft_contains_alpha(char *str);
char		**parse_cmd(char *cmd);
char		*extract_key(char *str);
int			is_dir(char *str);

/*
** Commands
*/

char		*find_path(t_shell *shell, char *cmd);
void		read_commands(t_shell *shell);
size_t		parse_cmd_count(char *cmd);
char		*copy_parsed_cmd_param(char *str, char *cmd);
char		**cmd_translate_env(t_shell *shell, char **split);
int			cmd_is_builtin(char *cmd);
void		exec_builtin(t_shell *shell, char **s);

#endif
