/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyospark <hyospark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 00:31:12 by hyospark          #+#    #+#             */
/*   Updated: 2021/12/16 19:26:02 by hyospark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenlst_add_back(t_token **lst, t_token *new_token)
{
	t_token	*last;

	if (lst == NULL || new_token == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_token;
		return ;
	}
	last = tokenlst_last(*lst);
	new_token->pre = last;
	last->next = new_token;
}

void	tokenlst_clear(t_token *lst)
{
	t_token	*temp;

	while (lst)
	{
		temp = lst->next;
		ft_free(lst->content);
		ft_free(lst);
		lst = temp;
	}
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
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
