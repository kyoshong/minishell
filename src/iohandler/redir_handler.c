/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:24:11 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/02 04:05:31 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_readline(int fd[], t_token *token)
{
	char	*read_doc;

	close(fd[0]);
	while (fd[1] > 0)
	{
		read_doc = readline("heredoc> ");
		if (!ft_strcmp(read_doc, token->next->content))
			fd[1] = -1;
		else
		{
			write(fd[1], read_doc, ft_strlen(read_doc));
			write(fd[1], "\n", 1);
		}
		free(read_doc);
	}
}

int	read_here_document(t_bundle *bundle, t_token *token)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		get_readline(fd, token);
		child_exit(bundle, status);
	}
	else
	{
		close(fd[1]);
		bundle->token->fd[0] = fd[0];
		waitpid(pid, &status, 0);
	}
	return (0);
}

void	set_fd(t_token *token)
{
	if (token->pre && is_fdnum(token->pre->content, 0) == 1 &&
	token->pre->back_space == 0)
	{
		token->fd[0] = ft_atoi(token->pre->content);
		tokenlst_delete(token->pre);
	}
	else
		token->fd[0] = -1;
	if (token->next && is_fdnum(token->next->content, 1) == 2 && \
	token->back_space == 0 && token->token_type != D_REDIR_IN)
	{
		token->fd[1] = ft_atoi(ft_strndup(token->pre->content, 1));
		tokenlst_delete(token->next);
	}
	else
		token->fd[1] = -1;
}

int	redir_handler(t_bundle *bundle, t_token *token)
{
	if (token->token_type == D_REDIR_OUT)
		return(d_redir_out(bundle, token));
	else if (token->token_type == D_REDIR_IN)
		return (d_redir_in(bundle, token));
	else if (token->token_type == REDIR_IN)
		return (redir_in(bundle, token));
	else if (token->token_type == REDIR_OUT)
		return (redir_out(bundle, token));
	return (FAIL);
}

int	set_redir_fd(t_bundle *bundle, t_token *token)
{
	t_token	*tmp;
	int		result;

	while (token && token->token_type != PIPE)
	{
		result = redir_handler(bundle, token);
		if (is_redir_token(token))
		{
			tmp = token->next;
			tokenlst_delete(token);
			token = tmp;
		}
		else
			token = token->next;
	}
	if (bundle->token->fd[0] == -1 || bundle->token->fd[1] == -1)
	{
		printf("%s\n", bundle->error_msg);
		exit(FAIL);
	}
	else
	{
		if (bundle->token->fd[0] > -1)
			dup2(bundle->token->fd[0], STDIN_FILENO);
		if (bundle->token->fd[1] > -1)
			dup2(bundle->token->fd[1], STDOUT_FILENO);
	}
	return (result);
}
