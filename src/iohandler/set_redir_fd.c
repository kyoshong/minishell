/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:18:22 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 20:22:17 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	d_redir_in(t_bundle *bundle, t_token *token)
{
	if (bundle->token->fd[0] != -1 && token->fd[0] > -1)
		bundle->token->fd[0] = token->fd[0];
	read_here_document(bundle, token);
	tokenlst_delete(token->next);
	return (SUCCESS);
}

int	d_redir_out(t_bundle *bundle, t_token *token, int err_flag)
{
	int	result;

	result = SUCCESS;
	if (token->fd[0] > -1)
		bundle->token->fd[0] = token->fd[0];
	if (token->fd[1] < 0)
	{
		if (!err_flag && \
		bundle->token->fd[0] != -1 && bundle->token->fd[1] != -1)
		{
			token->fd[1] = \
			open(token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (token->fd[1] < 0)
			{
				bundle->error_msg = "d_redir_out open file error";
				result = FAIL;
			}
			bundle->token->fd[1] = token->fd[1];
		}
		tokenlst_delete(token->next);
	}
	else if (bundle->token->fd[1] != -1)
		bundle->token->fd[1] = token->fd[1];
	return (result);
}

int	redir_out(t_bundle *bundle, t_token *token, int err_flag)
{
	int	result;

	result = SUCCESS;
	if (token->fd[0] > -1)
		bundle->token->fd[0] = token->fd[0];
	if (token->fd[1] < 0)
	{
		if (!err_flag && \
		bundle->token->fd[0] != -1 && bundle->token->fd[1] != -1)
		{
			token->fd[1] = \
			open(token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (token->fd[1] < 0)
			{
				bundle->error_msg = "redir_out open file error";
				result = FAIL;
			}
			bundle->token->fd[1] = token->fd[1];
		}
		tokenlst_delete(token->next);
	}
	else if (bundle->token->fd[1] != -1)
		bundle->token->fd[1] = token->fd[1];
	return (result);
}

int	redir_in(t_bundle *bundle, t_token *token, int err_flag)
{
	int	result;

	result = SUCCESS;
	if (token->fd[1] > -1)
		bundle->token->fd[1] = token->fd[1];
	if (token->fd[0] < 0)
	{
		if (!err_flag && \
		bundle->token->fd[0] != -1 && bundle->token->fd[1] != -1)
		{
			token->fd[0] = open(token->next->content, O_RDONLY);
			if (token->fd[0] < 0)
			{
				bundle->error_msg = "redir_in open file error";
				result = FAIL;
			}
			bundle->token->fd[0] = token->fd[0];
		}
		tokenlst_delete(token->next);
	}
	else if (bundle->token->fd[0] != -1)
		bundle->token->fd[0] = token->fd[0];
	return (result);
}
