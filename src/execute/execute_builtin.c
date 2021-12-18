/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:21:07 by ulee              #+#    #+#             */
/*   Updated: 2021/12/16 17:38:29 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_bundle *bundle)
{
	if (!bundle->token->next || bundle->token->back_space || \
		is_io_token(bundle->token->next))
	{
		if (ft_strcmp(bundle->token->content, "cd") == 0)
			return (builtin_cd(bundle));
		else if (ft_strcmp(bundle->token->content, "pwd") == 0)
			return (builtin_pwd(bundle));
		else if (ft_strcmp(bundle->token->content, "export") == 0)
			return (builtin_export(bundle));
		else if (ft_strcmp(bundle->token->content, "unset") == 0)
			return (builtin_unset(bundle));
		else if (ft_strcmp(bundle->token->content, "echo") == 0)
			return (builtin_echo(bundle));
		else if (ft_strcmp(bundle->token->content, "exit") == 0)
		{
			if (bundle->token == bundle->head)
				builtin_exit(bundle);
			return (FAIL);
		}
	}
	return (NO_BUILTIN);
}
