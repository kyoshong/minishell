/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:22:01 by ulee              #+#    #+#             */
/*   Updated: 2021/12/17 10:24:24 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_ps(int child_ps, t_bundle *bundle, int result)
{
	if (child_ps > 0)
		child_exit(bundle, result);
	if (child_ps == 0)
	{
		close(STDIN_FILENO);
		dup2(3, STDIN_FILENO);
		close(3);
	}
}

void	reset_fd(t_bundle *bundle)
{
	dup2(3, STDIN_FILENO);
	dup2(4, STDOUT_FILENO);
	if (bundle->head->fd[0] > -1)
	{
		close(bundle->head->fd[0]);
	}
	if (bundle->head->fd[1] > -1)
	{
		close(bundle->head->fd[1]);
	}
	close(3);
	close(4);
}

int	execute_pipe_cmd(t_bundle *bundle)
{
	int		result;
	pid_t	child_ps;

	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
		{
			child_ps = pipe_cmd(bundle);
			if (!child_ps)
				continue ;
		}
		result = set_redir_fd(bundle, bundle->token);
		result = execute_builtin(bundle);
		if (result == NO_BUILTIN)
			result = execute_bin(bundle);
		if (result == SUCCESS)
			g_global.status = 0;
		bundle->token = bundle->token->next;
		handle_ps(child_ps, bundle, result);
		reset_fd(bundle);
	}
	return (result);
}

int	set_status(int result)
{
	if (result == SUCCESS)
	{
		g_global.status = 0;
		return (SUCCESS);
	}
	else if (result == INVALID_ARG || result == 256)
		g_global.status = 1;
	else if (result == 512 || result == 32512 || result == -1)
		g_global.status = 127;
	else if (result == 2)
		g_global.status = 130;
	else if (result == 3)
		g_global.status = 131;
	return (FAIL);
}

int	execute_cmd(t_bundle *bundle)
{
	int		result;

	result = FAIL;
	if (!bundle->head)
		return (result);
	dup2(STDIN_FILENO, 3);
	dup2(STDOUT_FILENO, 4);
	if (bundle->is_pipe)
		return (execute_pipe_cmd(bundle));
	while (bundle->token)
	{
		result = set_redir_fd(bundle, bundle->token);
		result = execute_builtin(bundle);
		if (result == NO_BUILTIN)
			result = execute_bin(bundle);
		result = set_status(result);
		bundle->token = bundle->token->next;
	}
	reset_fd(bundle);
	return (result);
}
