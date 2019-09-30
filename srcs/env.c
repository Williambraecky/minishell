/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:10:38 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/09/30 17:35:37 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *shell, char *key)
{
	size_t	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strstartswith(shell->env[i], key) &&
			shell->env[i][ft_strlen(key)] == '=')
			return (shell->env[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

void	del_env(t_shell *shell, char *key)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**old;

	len = ft_splitlen(shell->env);
	old = shell->env;
	if (!(shell->env = ft_memalloc(sizeof(*(shell->env)) * (len))))
	{
		free_env(old);
		error_exit_free("Out of memory", shell);
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strstartswith(old[i], key) &&
			old[i][ft_strlen(key)] == '=')
			free(old[i]);
		else
			shell->env[j++] = old[i];
		i++;
	}
	free(old);
}

void	repl_env(t_shell *shell, char *key, char *value)
{
	char	*env_str;
	size_t	i;

	if (!(env_str = ft_strtrijoin(key, "=", value)))
		error_exit_free("Out of memory", shell);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strstartswith(shell->env[i], key) &&
			shell->env[i][ft_strlen(key)] == '=')
		{
			free(shell->env[i]);
			shell->env[i] = env_str;
			break ;
		}
		i++;
	}
}

void	add_env(t_shell *shell, char *key, char *value)
{
	char	*env_str;
	char	**old;
	size_t	len;

	if (!(env_str = ft_strtrijoin(key, "=", value)))
		error_exit_free("Out of memory", shell);
	old = shell->env;
	len = ft_splitlen(old);
	if (!(shell->env = ft_memalloc(sizeof(*(shell->env)) * (len + 2))))
	{
		free_env(old);
		error_exit_free("Out of memory", shell);
	}
	shell->env[len] = env_str;
	while (len--)
		shell->env[len] = old[len];
	free(old);
}

void	init_env(t_shell *shell, char **env)
{
	size_t	len;

	len = ft_splitlen(env);
	if (!(shell->env = ft_memalloc(sizeof(*env) * (len + 1))))
		error_exit_free("Out of memory", shell);
	len = 0;
	while (env[len])
	{
		if (!(shell->env[len] = ft_strdup(env[len])))
			error_exit_free("Out of memory", shell);
		len++;
	}
}
