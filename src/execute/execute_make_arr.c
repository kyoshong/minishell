/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_make_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 20:22:13 by ulee              #+#    #+#             */
/*   Updated: 2021/12/14 21:15:27 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*make_list(t_bundle *bundle)
{
	char	*token_content;
	t_list	*list;

	list = NULL;
	while (bundle->token->next && bundle->token->next->token_type != PIPE)
	{
		bundle->token = bundle->token->next;
		token_content = ft_strdup(bundle->token->content);
		if (ft_strchr(token_content, '*'))
			ft_lstadd_back(&list, execute_wildcard(token_content));
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(token_content)));
		ft_free(token_content);
	}
	return (list);
}

char	**make_arr(char *cmd, t_list *list)
{
	char	**ret;
	int		len;
	int		i;
	t_list	*temp;

	len = ft_lstsize(list);
	ret = (char **)malloc(sizeof(char *) * (len + 2));
	if (ret == NULL)
		return (NULL);
	ret[len + 1] = NULL;
	ret[0] = ft_strdup(cmd);
	i = 1;
	temp = list;
	while (i <= len)
	{
		ret[i++] = ft_strdup(temp->content);
		temp = temp->next;
	}
	return (ret);
}

char	**execute_make_arr(t_bundle *bundle)
{
	char	**arg_arr;
	t_list	*arg_list;
	char	*cmd;

	cmd = ft_strdup(bundle->token->content);
	arg_list = make_list(bundle);
	arg_arr = make_arr(cmd, arg_list);
	ft_free(cmd);
	ft_lstclear(&arg_list);
	return (arg_arr);
}
