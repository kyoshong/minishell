/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:30:02 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 23:39:08 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	passing_pipe_token(t_bundle *bundle)
{
	while (bundle->token->next)
	{
		bundle->token = bundle->token->next;
		if (bundle->token->pre->token_type == PIPE)
			return ;
	}
}

int	pipe_cmd(t_bundle *bundle)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		print_error_exit("pipe function error", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		print_error_exit("pipe fork error", EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		return (1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		passing_pipe_token(bundle);
		waitpid(pid, &status, 0);
		return (0);
	}
}
