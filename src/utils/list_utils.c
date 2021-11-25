/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:31:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/25 22:43:06 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenlst_new(char *content, int token_type, int back_space)
{
	t_token	*new;

	if (content == NULL)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->pre = NULL;
	new->token_type = token_type;
	new->back_space = back_space;
	new->redir = 0;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->pipe = 0;
	new->next = 0;
	return (new);
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
	free(lst->content);
	free(lst);
}

void	tokenlst_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = tokenlst_last(*lst);
	new->pre = last;
	last->next = new;
}

void	tokenlst_clear(t_token *lst)
{
	t_token	*temp;

	while (lst != NULL)
	{
		temp = lst->next;
		free(lst->content);
		free(lst);
		lst = temp;
	}
	lst = NULL;
}

int	tokenlst_size(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_token	*tokenlst_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}
