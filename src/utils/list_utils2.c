/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:46:34 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/16 19:36:43 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenlst_new(char *content, int token_type, int back_space)
{
	t_token	*new_token;

	if (content == NULL)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = content;
	new_token->pre = NULL;
	new_token->token_type = token_type;
	new_token->back_space = back_space;
	new_token->redir = 0;
	new_token->fd[0] = -2;
	new_token->fd[1] = -2;
	new_token->pipe = 0;
	new_token->next = NULL;
	return (new_token);
}

void	tokenlst_delete(t_token *lst)
{
	if (lst->pre && lst->next)
	{
		lst->pre->next = lst->next;
		lst->next->pre = lst->pre;
	}
	else if (lst->pre)
	{
		lst->pre->next = NULL;
	}
	else if (lst->next)
	{
		lst->next->pre = NULL;
	}
	ft_free(lst->content);
	ft_free(lst);
}
