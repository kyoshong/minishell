/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:23:10 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/15 23:48:31 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_fdnum(char *str, int back)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	if (str == NULL)
		return (0);
	if (back && str[i] == '&')
	{
		fd = 2;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (fd);
}

void	dup_redir_fd(t_bundle *bundle)
{
	if (bundle->token->fd[0] == -1 || bundle->token->fd[1] == -1)
	{
		printf("%s\n", bundle->error_msg);
		exit(FAIL);
	}
	if (bundle->token->fd[0] > -1)
	{
		close(STDIN_FILENO);
		dup2(bundle->token->fd[0], STDIN_FILENO);
		close(bundle->token->fd[0]);
	}
	if (bundle->token->fd[1] > -1)
	{
		close(STDOUT_FILENO);
		dup2(bundle->token->fd[1], STDOUT_FILENO);
		close(bundle->token->fd[1]);
	}
}
