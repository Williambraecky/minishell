/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:19:39 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/10/29 14:53:31 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_shell(t_shell *shell)
{
	free_env(shell->env);
	ft_memdel((void **)&shell);
}

void	free_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		ft_strdel(&(env[i++]));
	ft_memdel((void **)&env);
}
